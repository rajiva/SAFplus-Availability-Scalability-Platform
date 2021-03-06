/*
 * Copyright (C) 2002-2012 OpenClovis Solutions Inc.  All Rights Reserved.
 *
 * This file is available  under  a  commercial  license  from  the
 * copyright  holder or the GNU General Public License Version 2.0.
 * 
 * The source code for  this program is not published  or otherwise 
 * divested of  its trade secrets, irrespective  of  what  has been 
 * deposited with the U.S. Copyright office.
 * 
 * This program is distributed in the  hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied  warranty  of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 * 
 * For more  information, see  the file  COPYING provided with this
 * material.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <sys/poll.h>
#include <sys/ioctl.h>

#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <clCommon.h>
#include <clOsalApi.h>
#include <clBufferApi.h>
#include <clDebugApi.h>
#include <clHeapApi.h>
#include <clIocErrors.h>
#include <clIocIpi.h>
#include "clUdpNotification.h"
#include <clIocUserApi.h>
#include "clUdpSetup.h"
#include <clIocNeighComps.h>
#include <clTransport.h>
#include <clTaskPool.h>

#define CL_UDP_HANDLER_MAX_SOCKETS            2
#define UDP_CLUSTER_SYNC_WAIT_TIME 2 /* in seconds*/
static struct {
    ClOsalMutexT lock;
    ClOsalCondT condVar;
} gIocEventHandlerClose;

static ClUint8T buffer[0xffff + 1];

typedef ClIocLogicalAddressT ClIocLocalCompsAddressT;

static ClCharT pTaskName[] = { "clUdpNoficationHandler" };
static ClUint32T numHandlers = CL_UDP_HANDLER_MAX_SOCKETS;
static ClInt32T handlerFd[CL_UDP_HANDLER_MAX_SOCKETS];
static ClOsalMutexT gIocEventHandlerSendLock;
static ClOsalCondT  gIocEventHandlerSendCond;
static ClIocCommPortT dummyCommPort;
static ClIocLocalCompsAddressT allLocalComps;
static ClIocAddressT allNodeReps = {
        .iocPhyAddress = { CL_IOC_BROADCAST_ADDRESS, CL_IOC_XPORT_PORT }
};

static ClUint32T threadContFlag = 1;
static ClUint32T gNumDiscoveredPeers;
static ClCharT eventHandlerInited = 0;
static struct cmsghdr *gClMcastCmsgHdr;
static ClInt32T gClMcastCmsgHdrLen;
static ClInt32T gClMcastPort, gClMcastNotifPort;
static ClIocAddrMapT *gClMcastPeers;
static ClUint32T gClNumMcastPeers;
static ClBoolT gClMcastSupport;

static ClRcT udpEventSubscribe(ClBoolT pollThread);

static void udpSyncCallback(ClIocPhysicalAddressT *srcAddr, ClPtrT arg)
{
    if(srcAddr->nodeAddress != gIocLocalBladeAddress)
    {
        clLogNotice("SYNC", "CALLBACK", 
                    "UDP cluster sync for node [%d], port [%#x], ip [%s]",
                    srcAddr->nodeAddress, srcAddr->portId,
                    inet_ntoa( ((struct sockaddr_in*)arg)->sin_addr) );
        ++gNumDiscoveredPeers;
        /*
         * Peer node arrival mean it is already come up
         */
        clIocCompStatusSet(*srcAddr, CL_IOC_NODE_UP);
        clIocUdpMapAdd((struct sockaddr*)arg, srcAddr->nodeAddress);
    }
}

ClRcT clUdpNodeNotification(ClIocNodeAddressT node, ClIocNotificationIdT event)
{
    ClRcT rc = CL_OK;
    ClIocNotificationIdT id = event;

    /* This is for NODE ARRIVAL/DEPARTURE */
    if(id == CL_IOC_COMP_ARRIVAL_NOTIFICATION || id == CL_IOC_NODE_LINK_UP_NOTIFICATION )
        id = CL_IOC_NODE_ARRIVAL_NOTIFICATION;

    if(id == CL_IOC_COMP_DEATH_NOTIFICATION || id == CL_IOC_NODE_LINK_DOWN_NOTIFICATION)
        id = CL_IOC_NODE_LEAVE_NOTIFICATION;

    clLogInfo("UDP", "NOTIF", "Got node [%s] notification for node [0x%x]",
              id == CL_IOC_NODE_ARRIVAL_NOTIFICATION ? "arrival" : "death", node);

    rc = clIocNotificationNodeStatusSend((ClIocCommPortHandleT)&dummyCommPort,
                                         event,
                                         node,
                                         (ClIocAddressT*)&allLocalComps,
                                         (ClIocAddressT*)&allNodeReps,
                                         gClUdpXportType);
                
    if(id == CL_IOC_NODE_LEAVE_NOTIFICATION)
    {
        if (node == gIocLocalBladeAddress)
        {
            threadContFlag = 0;
        }
        else
        {
            clIocUdpMapDel(node); /*remove entry from the map*/
        }
    }

    return rc;
}

static ClRcT clUdpReceivedPacket(ClUint32T socketType, struct msghdr *pMsgHdr) {
    ClRcT rc = CL_OK;
    ClUint8T *pRecvBase = (ClUint8T*) pMsgHdr->msg_iov->iov_base;

    switch (socketType) {
    case 0:
        {
            ClIocNotificationT notification = { 0 };
            ClIocPhysicalAddressT compAddr = { 0 };
            ClIocNotificationIdT id = 0;
            memcpy((ClPtrT) &notification, pRecvBase, sizeof(notification));

            compAddr.nodeAddress = ntohl(
                    notification.nodeAddress.iocPhyAddress.nodeAddress);
            compAddr.portId = ntohl(notification.nodeAddress.iocPhyAddress.portId);
            id = ntohl(notification.id);

            if(id == CL_IOC_NODE_DISCOVER_NOTIFICATION)
            {
                clIocCompStatusSet(compAddr, CL_IOC_NODE_UP);
                if(compAddr.nodeAddress == gIocLocalBladeAddress)
                    return rc; /*ignore self discover*/
                ClIocPhysicalAddressT destAddress = {.nodeAddress = compAddr.nodeAddress,
                                                     .portId = compAddr.portId,
                };
                notification.nodeAddress.iocPhyAddress.nodeAddress = htonl(gIocLocalBladeAddress);
                notification.nodeAddress.iocPhyAddress.portId = htonl(CL_IOC_XPORT_PORT);
                clLogDebug("UDP", "DISCOVER", "Sending udp discover packet to node [%d], port [%#x]",
                           compAddr.nodeAddress, compAddr.portId);
                return clIocNotificationPacketSend((ClIocCommPortHandleT)&dummyCommPort,
                                                   &notification, (ClIocAddressT*)&destAddress, 
                                                   CL_FALSE, gClUdpXportType);
            }

            if (compAddr.portId == CL_IOC_XPORT_PORT)
            {
                /* This is for NODE ARRIVAL/DEPARTURE */
                if(compAddr.nodeAddress != gIocLocalBladeAddress)
                    rc = clUdpNodeNotification(compAddr.nodeAddress, id);
            }
            else
            {
                /* This is for LOCAL COMPONENT ARRIVAL/DEPARTURE */
                clLogInfo("UDP", "NOTIF", "Got component [%s] notification for node [0x%x] commport [0x%x]",
                          id == CL_IOC_COMP_ARRIVAL_NOTIFICATION ? "arrival" : "death", compAddr.nodeAddress, compAddr.portId);
                ClUint8T status = (id == CL_IOC_COMP_ARRIVAL_NOTIFICATION) ? CL_IOC_NODE_UP : CL_IOC_NODE_DOWN;

                clIocCompStatusSet(compAddr, status);

                if (compAddr.nodeAddress == gIocLocalBladeAddress) {
                    rc = clIocNotificationCompStatusSend((ClIocCommPortHandleT)&dummyCommPort,
                                                         id == CL_IOC_COMP_ARRIVAL_NOTIFICATION ? 
                                                         CL_IOC_NODE_UP : CL_IOC_NODE_DOWN,
                                                         compAddr.portId, (ClIocAddressT*)&allLocalComps,
                                                         (ClIocAddressT*)&allNodeReps,
                                                         gClUdpXportType);

                    if ( id == CL_IOC_COMP_DEATH_NOTIFICATION
                         && compAddr.portId == CL_IOC_CPM_PORT)
                    {
                        /*
                         * self shutdown.
                         */
                        clTransportNotificationClose(NULL, gIocLocalBladeAddress, 
                                                     CL_IOC_XPORT_PORT, CL_IOC_COMP_DEATH_NOTIFICATION);
                        threadContFlag = 0;
                    }
                }
            }
        }
        break;
    case 1:
        {

            /* Packet is received from the other node amfs/NODE-REPS*/
            rc = clIocNotificationPacketRecv((ClIocCommPortHandleT) &dummyCommPort,
                                             (ClUint8T*) pMsgHdr->msg_iov->iov_base,
                                             (ClUint32T) pMsgHdr->msg_iov->iov_len,
                                             (ClIocAddressT*) &allLocalComps, (ClIocAddressT*) &allNodeReps,
                                             udpSyncCallback, (ClPtrT)pMsgHdr->msg_name,
                                             gClUdpXportType);
        }
        break;

    default:
        break;
    }

    return rc;
}

static void clUdpEventHandler(ClPtrT pArg) {
    ClUint32T i = 0;
    ClInt32T fd[CL_UDP_HANDLER_MAX_SOCKETS];
    struct pollfd pollfds[CL_UDP_HANDLER_MAX_SOCKETS];
    struct msghdr msgHdr;
    struct iovec ioVector[1];
    struct sockaddr_in peerAddress;
    struct 
    {
        ClUint8T *cMsgHdr;
        ClInt32T cMsgHdrLen;
    } cMsgHdrMap[CL_UDP_HANDLER_MAX_SOCKETS] = {
        { (ClUint8T*)gClMcastCmsgHdr, gClMcastCmsgHdrLen},
        { (ClUint8T*)gClCmsgHdr, gClCmsgHdrLen },
    };
    ClInt32T pollStatus;
    ClInt32T bytes;
    ClUint32T timeout = CL_IOC_TIMEOUT_FOREVER;
    ClUint32T recvErrors = 0;

    retry: 
    memset(&peerAddress, 0, sizeof(peerAddress));
    memset(pollfds, 0, sizeof(pollfds));
    pollfds[0].fd = fd[0] = handlerFd[0];
    pollfds[1].fd = fd[1] = handlerFd[1];
    pollfds[0].events = pollfds[1].events = POLLIN | POLLRDNORM;

    memset(&msgHdr, 0, sizeof(msgHdr));
    memset(ioVector, 0, sizeof(ioVector));
    ioVector[0].iov_base = (ClPtrT) buffer;
    ioVector[0].iov_len = sizeof(buffer);
    memset(&peerAddress, 0, sizeof(peerAddress));
    msgHdr.msg_name = &peerAddress;
    msgHdr.msg_namelen = sizeof(peerAddress);
    msgHdr.msg_iov = ioVector;
    msgHdr.msg_iovlen = sizeof(ioVector)/sizeof(ioVector[0]);

    while (threadContFlag) 
    {
        pollStatus = poll(pollfds, numHandlers, timeout);
        if (pollStatus > 0) 
        {
            for (i = 0; i < numHandlers; i++) 
            {
                if ((pollfds[i].revents & (POLLIN | POLLRDNORM))) 
                {
                    msgHdr.msg_control = cMsgHdrMap[i].cMsgHdr;
                    msgHdr.msg_controllen = cMsgHdrMap[i].cMsgHdrLen;

                    recv: bytes = recvmsg(fd[i], &msgHdr, 0);
                    if (bytes < 0) {
                        if (errno == EINTR)
                            goto recv;
                        if (!(recvErrors++ & 255)) 
                        {
                            CL_DEBUG_PRINT(
                                           CL_DEBUG_ERROR,
                                           ("Recvmsg failed with [%s]\n", strerror(errno)));
                            sleep(1);
                        }
                        if (errno == ENOTCONN) 
                        {
                            if (udpEventSubscribe(CL_FALSE) != CL_OK) 
                            {
                                CL_DEBUG_PRINT(
                                               CL_DEBUG_CRITICAL,
                                               ("UDP topology subsciption retry failed. "
                                                "Shutting down the notification thread and process\n"));
                                threadContFlag = 0;
                                exit(0);
                                continue; /*unreached*/
                            }
                            goto retry;
                        }
                        continue;
                    }
                    clUdpReceivedPacket(i, &msgHdr);
                } 
                else if ((pollfds[i].revents & (POLLHUP | POLLERR | POLLNVAL))) 
                {
                    CL_DEBUG_PRINT(CL_DEBUG_ERROR,
                                   ("Error : Handler \"poll\" hangup.\n"));
                }
            }
        } 
        else if (pollStatus < 0) 
        {
            if (errno != EINTR) /* If the system call is interrupted just loop, its not an error */
                CL_DEBUG_PRINT(CL_DEBUG_ERROR,
                               ("Error : poll failed. errno=%d\n",errno));
        }
    }
    close(handlerFd[0]);

    clOsalMutexLock(&gIocEventHandlerClose.lock);
    clOsalCondSignal(&gIocEventHandlerClose.condVar);
    clOsalMutexUnlock(&gIocEventHandlerClose.lock);
}

static ClRcT udpMcastSetup(void)
{
    ClRcT rc = CL_OK;
    
    if(gClMcastNotifPort) 
        return CL_OK;

    if(!gClMcastPort)
        gClMcastPort = clTransportMcastPortGet();

    gClMcastNotifPort = gClMcastPort;

    if(gClMcastPeers)
    {
        clHeapFree(gClMcastPeers);
        gClMcastPeers = NULL;
        gClNumMcastPeers = 0;
    }

    gClMcastSupport = clTransportMcastSupported(&gClNumMcastPeers);
    if(!gClMcastSupport)
    {
        if(!gClNumMcastPeers)
        {
            gClMcastSupport = CL_TRUE;
        }
        else
        {
            if(gClSimulationMode)
                gClMcastNotifPort += gIocLocalBladeAddress;
        }
    }

    if(gClMcastSupport)
    {
        gClMcastCmsgHdr = NULL;
        gClMcastCmsgHdrLen = 0;
    }
    else
    {
        gClMcastCmsgHdr = gClCmsgHdr;
        gClMcastCmsgHdrLen = gClCmsgHdrLen;
    }

    if(gClMcastSupport)
    {
        ClCharT *mcastAddr = clTransportMcastAddressGet();
        gClMcastPeers = clHeapCalloc(1, sizeof(*gClMcastPeers));
        CL_ASSERT(gClMcastPeers != NULL);
        gClMcastPeers->family = PF_INET;
        gClMcastPeers->_addr.sin_addr.sin_family = PF_INET;
        gClMcastPeers->_addr.sin_addr.sin_addr.s_addr = inet_addr(mcastAddr);
        gClMcastPeers->_addr.sin_addr.sin_port = htons(gClMcastNotifPort);
        strncat(gClMcastPeers->addrstr, mcastAddr, sizeof(gClMcastPeers->addrstr)-1);
        gClNumMcastPeers = 1;
    }
    else
    {
        gClMcastPeers = clHeapCalloc(gClNumMcastPeers, sizeof(*gClMcastPeers));
        CL_ASSERT(gClMcastPeers !=  NULL);
        rc = clTransportMcastPeerListGet(gClMcastPeers, &gClNumMcastPeers);
        if(rc != CL_OK)
        {
            clLogError("UDP", "NOTIFY", "Mcast peer list get failed with [%#x]", rc);
            clHeapFree(gClMcastPeers);
            gClMcastPeers = NULL;
            gClNumMcastPeers = 0;
            goto out;
        }
    }

    out:
    return rc;
}

static ClInt32T clUdpSubscriptionSocketCreate(void) 
{
    static ClInt32T sd = -1;
    ClRcT rc = CL_OK;
    int reuse = 1;
    
    if(!gClMcastPort)
        gClMcastPort = clTransportMcastPortGet();

    if( (rc = udpMcastSetup() ) != CL_OK)
        return -1;

    if(sd != -1)
        close(sd);
        
    /*
     * Setup mcast send socket
     */
    if(gClMcastSupport)
    {
        sd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    }
    else
    {
        sd = socket(PF_INET, gClSockType, gClProtocol);
    }

    if (sd < 0) 
    {
        clLogError(
                   "UDP",
                   "NOTIF",
                   "open socket failed with error [%s]", strerror(errno));
        return -1;
    }

    rc = fcntl(sd, F_SETFD, FD_CLOEXEC);

    if (rc == -1) 
    {
        goto out_close;
    }

    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *) &reuse, sizeof(reuse)) < 0) 
    {
        clLogError(
                   "UDP",
                   "NOTIF",
                   "setsockopt SO_REUSEADDR failed with error [%s]", strerror(errno));
        goto out_close;
    }

    struct sockaddr_in localSock;
    memset((char *) &localSock, 0, sizeof(localSock));
    localSock.sin_family = PF_INET;
    localSock.sin_port = htons(gClMcastNotifPort);
    localSock.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sd, (struct sockaddr*) &localSock, sizeof(localSock))) 
    {
        clLogError(
                   "UDP",
                   "NOTIF",
                   "setsockopt for SO_REUSEADDR failed with error [%s]", strerror(errno));
        goto out_close;
    }

    if(gClMcastSupport)
    {
        /*
         * Join group membership on socket
         */
        struct ip_mreq group;
        group.imr_multiaddr.s_addr = inet_addr(clTransportMcastAddressGet());
        group.imr_interface.s_addr = htonl(INADDR_ANY);
        if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *) &group,
                       sizeof(group)) < 0) 
        {
            clLogError(
                       "UDP",
                       "NOTIF",
                       "setsockopt IP_ADD_MEMBERSHIP failed with error [%s]", strerror(errno));
            goto out_close;
        }

        /*
         * Set outbound interface
         */
        struct in_addr iaddr;
        iaddr.s_addr = INADDR_ANY;
        if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, &iaddr, sizeof(iaddr)) < 0) {
            clLogError(
                       "UDP",
                       "NOTIF",
                       "setsockopt IP_MULTICAST_IF failed with error [%s]", strerror(errno));
            goto out_close;
        }
    }
    else if(gClMcastCmsgHdr)
    {
        if(listen(sd, CL_IOC_MAX_NODES) < 0)
        {
            clLogError("UDP", "NOTIF", "Socket listen failed with error [%s]",
                       strerror(errno));
            goto out_close;
        }
    }
    return sd;

    out_close:
    close(sd);
    sd = -1;
    return -1;
}

static ClRcT udpEventSubscribe(ClBoolT pollThread) {
    ClRcT retCode = CL_OK;

    /* Creating a socket for handling the subscription events */
    handlerFd[0] = clUdpSubscriptionSocketCreate();
    if (handlerFd[0] < 0)
        return CL_IOC_RC(CL_ERR_LIBRARY);

    if (pollThread) {
        retCode = clOsalTaskCreateDetached(pTaskName, CL_OSAL_SCHED_OTHER,
                CL_OSAL_THREAD_PRI_NOT_APPLICABLE, 0,
                (void* (*)(void*)) &clUdpEventHandler, NULL);
        if (retCode != CL_OK) {
            clLogError(
                    "UDP",
                    "NOTIF",
                    "Error : Event Handle thread did not start. error code 0x%x",retCode);
            goto out;
        }
    }

    out:
    return retCode;
}

ClRcT clUdpNotify(ClIocNodeAddressT nodeAddress, ClUint32T portId, ClIocNotificationIdT notifyId) 
{
    ClRcT rc = CL_OK;
    ClIocNotificationT notification = { 0 };
    ClUint32T i;
    static ClUint32T nodeVersion = CL_VERSION_CODE(5, 0, 0);
    static int fd = -1; 

    if( (rc = udpMcastSetup() ) != CL_OK)
        return rc;

    if(fd < 0)
    {
        if(gClMcastSupport)
        {
            if( (fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP) ) < 0)
                return CL_ERR_LIBRARY;
        }
        else
        {
            if( (fd = socket(PF_INET, gClSockType, gClProtocol) ) < 0)
                return CL_ERR_LIBRARY;

        }
    }

    notification.id = htonl(notifyId);
    notification.protoVersion = htonl(CL_IOC_NOTIFICATION_VERSION);
    notification.nodeVersion = htonl(nodeVersion);
    notification.nodeAddress.iocPhyAddress.portId = htonl(portId);
    notification.nodeAddress.iocPhyAddress.nodeAddress = htonl(nodeAddress);

    struct iovec ioVector[1];
    ioVector[0].iov_base = (ClPtrT) &notification;
    ioVector[0].iov_len = sizeof(notification);

    for(i = 0; i < gClNumMcastPeers; ++i)
    {
        struct msghdr msg;
        ClInt32T mcastNotifPort = gClMcastPort;
        if(!gClMcastSupport && gClSimulationMode)
        {
            ClCharT *pLastOctet = strrchr(gClMcastPeers[i].addrstr, '.');
            if(pLastOctet)
            {
                ClInt32T portOffset = atoi(pLastOctet+1);
                mcastNotifPort += portOffset;
            }
        }
        if(gClMcastPeers[i].family == PF_INET)
        {
            if(!gClMcastSupport && gClSimulationMode)
            {
                gClMcastPeers[i]._addr.sin_addr.sin_port = htons(mcastNotifPort);
            }
            msg.msg_name = (struct sockaddr*) &gClMcastPeers[i]._addr.sin_addr;
            msg.msg_namelen = sizeof(gClMcastPeers[i]._addr.sin_addr);
        }
        else
        {
            if(!gClMcastSupport && gClSimulationMode)
            {
                gClMcastPeers[i]._addr.sin6_addr.sin6_port = htons(mcastNotifPort);
            }
            msg.msg_name = (struct sockaddr*)&gClMcastPeers[i]._addr.sin6_addr;
            msg.msg_namelen = sizeof(gClMcastPeers[i]._addr.sin6_addr);
        }
        msg.msg_iov = ioVector;
        msg.msg_iovlen = sizeof(ioVector) / sizeof(ioVector[0]);
        msg.msg_control = gClMcastCmsgHdr;
        msg.msg_controllen = gClMcastCmsgHdrLen;
        msg.msg_flags = 0;

        if (sendmsg(fd, &msg, 0) < 0) 
        {
            clLogError(
                       "UDP",
                       "NOTIF",
                       "sendmsg failed with error [%s] for destination [%s]", 
                       strerror(errno), gClMcastPeers[i].addrstr);
            rc = CL_ERR_NO_RESOURCE;
            goto out;
        }
        else
        {
            clLogDebug("UDP", "NOTIF", "Notification [%d] sent to node [%s], port [%d]",
                       notifyId, gClMcastPeers[i].addrstr, mcastNotifPort);
        }
    }

    out:
    return rc;
}

static ClRcT udpDiscoverWait(void *arg)
{
    sleep(UDP_CLUSTER_SYNC_WAIT_TIME);
    clOsalMutexLock(&gIocEventHandlerSendLock);
    clOsalCondSignal(&gIocEventHandlerSendCond);
    clOsalMutexUnlock(&gIocEventHandlerSendLock);
    return CL_OK;
}

static ClRcT udpDiscoverPeers(void)
{
    ClRcT rc = CL_ERR_UNSPECIFIED;
    static ClTaskPoolHandleT task;
    static ClTimerTimeOutT delay;
    clOsalMutexLock(&gIocEventHandlerSendLock);
    /*
     * We could send multiple discovery packets to avoid loss or to play it safe. 
     * But not required for now ...
     */
    clUdpNotify(gIocLocalBladeAddress, CL_IOC_XPORT_PORT, CL_IOC_NODE_DISCOVER_NOTIFICATION);
    if(!task)
    {
        clTaskPoolCreate(&task, 1, 0, 0);
    }
    if(!task)
    {
        clOsalMutexUnlock(&gIocEventHandlerSendLock);
        clLogError("UDP", "DISCOVER", "Unable to initialize task pool should for UDP discover sync phase");
        clLogError("UDP", "DISCOVER", "Cluster view could be inconsistent");
        goto out;
    }
    clTaskPoolRun(task, udpDiscoverWait, NULL);
    clOsalCondWait(&gIocEventHandlerSendCond, &gIocEventHandlerSendLock, delay);
    clOsalMutexUnlock(&gIocEventHandlerSendLock);
    clLogNotice("UDP", "DISCOVER", "Cluster view sync complete. Discovered [%d] peers",
                gNumDiscoveredPeers);
    rc = CL_OK;
    out:
    return rc;
}

ClRcT clUdpEventHandlerInitialize(void) {
    ClRcT rc;

    allLocalComps =
            CL_IOC_ADDRESS_FORM(CL_IOC_INTRANODE_ADDRESS_TYPE, gIocLocalBladeAddress, CL_IOC_BROADCAST_ADDRESS);

    rc = clOsalMutexInit(&gIocEventHandlerSendLock);
    CL_ASSERT(rc == CL_OK);
    rc = clOsalCondInit(&gIocEventHandlerSendCond);
    CL_ASSERT(rc == CL_OK);
    rc = clOsalMutexInit(&gIocEventHandlerClose.lock);
    CL_ASSERT(rc == CL_OK);
    rc = clOsalCondInit(&gIocEventHandlerClose.condVar);
    CL_ASSERT(rc == CL_OK);

    rc = clIocNotificationInitialize();
    CL_ASSERT(rc == CL_OK);

    /* Creating a socket for handling the data packets sent by other node CPM/amf. */
    rc = clIocCommPortCreateStatic(CL_IOC_XPORT_PORT, CL_IOC_RELIABLE_MESSAGING,
                                   &dummyCommPort, gClUdpXportType);
    if (rc != CL_OK) {
        clLogError(
                "UDP",
                "NOTIF",
                "Comm port create for notification port [%#x] returned with [%#x]", CL_IOC_XPORT_PORT, rc);
        goto out;
    }

    rc = clIocPortNotification(CL_IOC_XPORT_PORT, CL_IOC_NOTIFICATION_ENABLE);
    if (rc != CL_OK)
        goto out;

    rc = clUdpFdGet(CL_IOC_XPORT_PORT, &handlerFd[1]);
    if (rc != CL_OK) {
        clLogError(
                "UDP",
                "NOTIF",
                "UDP notification fd for port [%#x] returned with [%#x]", CL_IOC_XPORT_PORT, rc);
        goto out;
    }

    rc = udpEventSubscribe(CL_TRUE);

    if (rc != CL_OK)
        goto out;

    eventHandlerInited = 1;

    udpDiscoverPeers(); /* shouldn't return till cluster sync interval */

    clUdpNotify(gIocLocalBladeAddress, CL_IOC_XPORT_PORT, CL_IOC_COMP_ARRIVAL_NOTIFICATION);

    out:
    return rc;
}

ClRcT clUdpEventHandlerFinalize(void) {
    ClTimerTimeOutT timeout = { .tsSec = 0, .tsMilliSec =
            CL_IOC_MAIN_THREAD_WAIT_TIME };

    /* If service was never initialized, don't finalize */
    if (!eventHandlerInited)
        return CL_OK;

    eventHandlerInited = 0;
    clIocNotificationFinalize();

    /* Closing only the data socket so the the event socket can get the event of this and it will comeout of the recview thread */

    clOsalMutexLock(&gIocEventHandlerSendLock);
    close(handlerFd[1]);
    numHandlers = numHandlers - 1;
    handlerFd[1] = -1;
    clOsalMutexUnlock(&gIocEventHandlerSendLock);

    clOsalMutexLock(&gIocEventHandlerClose.lock);
    clOsalCondWait(&gIocEventHandlerClose.condVar, &gIocEventHandlerClose.lock,
            timeout);
    clOsalMutexUnlock(&gIocEventHandlerClose.lock);

    return CL_OK;
}
