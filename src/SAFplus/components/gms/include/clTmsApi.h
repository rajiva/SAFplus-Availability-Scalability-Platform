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
/*******************************************************************************
 * ModuleName  : gms
 * File        : clTmsApi.h
 *******************************************************************************/

/*******************************************************************************
 * Description :
 *
 * This client API extends the SA Forum compliant cluster membership
 * query and tracking API with group view management.
 *
 * Special applications can use this service to create and manage
 * group (views) on top of the cluster (views).
 * 
 *
 * Synchronization of the group with the cluster group view is provided
 * by the implementation of this service and it works as follows: 
 * An application can create a group and join the group if its node is also
 * part of the cluster group. If a cluster node leaves (or is removed) from
 * the cluster, any process on the removed node that participates in any 
 * group(s) is also removed from the respective group(s).
 *
 * An instance of this service (instantiated by the clTmsInitialize()
 * API and identified by the svcHandle) can view and manage any group. 
 *
 *
 * FIXME/TODO:
 * - Need to make sure all error codes are defined (here or in clCommon.h)
 * - Need to address group address synchronization issue.  If this service
 *   is to synchronize group address with group membership, then this has
 *   to be requested explicitely (and the address provided too).
 *  
 *
 *****************************************************************************/

/**
 *  \file
 *  \brief Header file of Group Membership Service APIs.
 *  \ingroup gms_apis
 */

/**
 *  \addtogroup gms_apis
 *  \{
 */

#ifndef _CL_TMS_API_H
#define _CL_TMS_API_H

# ifdef __cplusplus
extern "C" {
# endif

#include <clCommon.h>
#include <clClmApi.h>
#include <clTmsApi.h>

/*=========================================================================
 * Type/constant definitions:
 *=======================================================================*/

/**
 *  Handle to be associated with each group 
 */
#define clTmsInitialize                 clGmsInitialize
#define clTmsFinalize                   clGmsFinalize

typedef ClGmsHandleT                    ClTmsHandleT;
typedef ClGmsGroupNameT                 ClTmsGroupNameT;
typedef ClGmsGroupIdT                   ClTmsGroupIdT;
typedef ClGmsGroupParamsT               ClTmsGroupParamsT;
typedef ClGmsMemberIdT                  ClTmsMemberIdT;
typedef ClGmsMemberNameT                ClTmsMemberNameT;
typedef ClGmsLeadershipCredentialsT     ClTmsLeadershipCredentialsT;
typedef ClGmsGroupNotificationBufferT   ClTmsGroupNotificationBufferT;
typedef ClGmsGroupInfoListT             ClTmsGroupInfoListT;
typedef ClGmsGroupInfoT                 ClTmsGroupInfoT;
typedef ClGmsGroupMemberT               ClTmsGroupMemberT;

/*=========================================================================
 * Callback Functions:
 *=======================================================================*/
typedef void (*ClTmsGroupMessageDeliveryCallbackT) (ClTmsGroupIdT    groupId,
                                                    ClTmsMemberIdT   senderId,
                                                    ClUint32T        messageSize,
                                                    void            *message);


/*=========================================================================
 * API Functions:
 *=======================================================================*/

/**
 ************************************
 *  \brief Create a group.
 *
 *  \param svcHandle svcHandle provided during clTmsInitialize
 *  \param groupName Name of the group. Specify the value and length
 *  \param groupId Pointer to the memory to store groupId generated by GMS.
 *  \param groupParams Includes parameters such as isIocGroup etc. By default all
 *                the groups are Ioc Groups.
 *
 *  \retval CL_ERR_TRY_AGAIN  Server is not ready to serve group functionality
 *  \retval CL_ERR_VERSION_MISMATCH Client version not supported
 *  \retval CL_ERR_INVALID_HANDLE svcHandle is invalid
 *  \retval CL_ERR_NULL_POINTER groupName or groupId params are NULL
 *  \retval CL_ERR_NO_MEMORY Could not allocate memory to create groups.
 *  \retval CL_ERR_NO_RESOURCE  Could not allocate resource to create groups.
 *  \retval CL_ERR_ALREADY_EXIST Group is already created. At this point the created
 *                               groupId is returned in groupId parameter.
 *  \retval CL_ERR_TIMEOUT Group Creation timeout.
 *  \retval CL_ERR_UNSPECIFIED Group creation failed with unknown error.
 *
 *  \par Description:
 *  Create a group. User needs to pass groupName and groupId pointer. GMS will
 *  generate a groupId which will be unique across the cluster, and it will be
 *  returned through groupId pointer.
 */
extern ClRcT clTmsGroupCreate(
        CL_IN    ClTmsHandleT                        svcHandle,
        CL_IN    ClTmsGroupNameT                    *groupName,
        CL_INOUT ClTmsGroupParamsT                  *groupParams,
        CL_OUT   ClTmsGroupIdT                      *groupId);


/**
 ************************************
 *  \brief Destroy a group.
 * 
 *  \param svcHandle svcHandle provided during gmsInitialize.
 *  \param groupId groupId provided during GroupCreate
 *
 *  \retval CL_ERR_TRY_AGAIN Server is not ready to serve group functionality
 *  \retval CL_ERR_VERSION_MISMATCH Client version not supported
 *  \retval CL_ERR_INVALID_HANDLE svcHandle is invalid
 *  \retval CL_ERR_DOESNT_EXIST  Requested group with groupId doesnt exist.
 *  \retval CL_ERR_INUSE  Group is not empty. However in this case, 
 *                        the group will be set inActive and hence
 *                        no further joins can happen.
 *
 *  \par Description:
 *  Destroy a group. The group will be destroyed on all nodes
 *  across the cluster.
 */
extern ClRcT clTmsGroupDestroy(
        CL_IN   ClTmsHandleT                    svcHandle,
        CL_IN   ClTmsGroupIdT                   groupId);

/**
 ************************************
 *  \brief Join the group as a member.
 *
 *  \param svcHandle svcHandle provided during clTmsInitialize
 *  \param groupId groupId provided during group creation.
 *  \param memberId Id of the member joining the group.
 *  \param memberName Name of the memebr joining the group. This is optional
 *  \param credentials Leadership credentials of the group member [Currently not used]
 *  \param timeout Join timeout
 *
 *  \retval CL_ERR_TRY_AGAIN  Server is not ready to serve group functionality
 *  \retval CL_ERR_VERSION_MISMATCH Client version not supported
 *  \retval CL_ERR_INVALID_HANDLE svcHandle is invalid
 *  \retval CL_ERR_TIMEOUT Groupjoin timeout
 *  \retval CL_ERR_DOESNT_EXIST requested group does not exist.
 *  \retval CL_ERR_NULL_POINTER memberName is not provided.
 *  \retval CL_ERR_ALREADY_EXIST The application is an existing member of the group.
 *  \retval CL_ERR_INVALID_OPERATION Join is denied as the group is marked to be destroyed.
 *
 *  \par Description:
 *  Join the group as a member.  Success is reported to caller
 *  via return value.  Others get notified by tracking callback.
 */
extern ClRcT clTmsGroupJoin(
        CL_IN ClTmsHandleT                        svcHandle,
        CL_IN ClTmsGroupIdT                       groupId,
        CL_IN ClTmsMemberIdT                      memberId,
        CL_IN ClTmsMemberNameT                   *memberName,
        CL_IN ClTmsLeadershipCredentialsT         credentials,
        CL_IN ClTmsGroupMessageDeliveryCallbackT  msgDeliveryCallback,
        CL_IN ClTimeT                             timeout);


/**
 ************************************
 *  \brief Leave the group. 
 *
 *  \param svcHandle svcHandle provided during clTmsInitialize
 *  \param groupId  groupId provided during group creation.
 *  \param memberId  Id of the member Leaving the group.
 *  \param timeout  Leave timeout
 *
 *  \retval CL_ERR_TRY_AGAIN Server is not ready to serve group functionality
 *  \retval CL_ERR_VERSION_MISMATCH Client version not supported
 *  \retval CL_ERR_INVALID_HANDLE svcHandle is invalid
 *  \retval CL_ERR_TIMEOUT  GroupLeave timeout
 *  \retval CL_ERR_DOESNT_EXIST  requested memberId does not exist.
 *  \retval CL_ERR_GROUP_DOESNT_EXIST requested group does not exist.
 *
 *  \par Description:
 *  Leave the group. Success is retured to caller via return value. Others
 *  will be notified through track callback.
 */

extern ClRcT clTmsGroupLeave(
        CL_IN ClTmsHandleT                      svcHandle,
        CL_IN ClTmsGroupIdT                     groupId,
        CL_IN ClTmsMemberIdT                    memberId,
        CL_IN ClTimeT                           timeout);

/**
 ************************************
 *  \brief Send a Totally ordered multicast messages to all members of a given group.
 *
 *  \param svcHandle svcHandle provided during clTmsInitialize
 *  \param groupId Group Id of the destination group
 *  \param memberId memberId of the sender
 *  \param timeout  timeout value of the API call
 *  \param dataSize size of the data being sent in data pointer
 *  \param data void pointer pointing to the data to be sent.
 *
 *  \retval CL_ERR_TRY_AGAIN  Server is not ready to serve group functionality
 *  \retval CL_ERR_VERSION_MISMATCH Client version not supported
 *  \retval CL_ERR_INVALID_HANDLE svcHandle is invalid
 *  \retval CL_ERR_NOT_EXIST  Destination group does not exist
 *  \retval CL_ERR_NULL_POINTER data pointer is NULL
 *  \retval CL_ERR_NO_MEMORY Could not allocate memory while sending the message
 *  \retval CL_ERR_NO_RESOURCE  Could not allocate resource to send the message
 *  \retval CL_ERR_TIMEOUT timeout occurred while sending the message
 *  \retval CL_ERR_UNSPECIFIED Group creation failed with unknown error.
 *
 *  \par Description:
 *  Create a group. User needs to pass groupName and groupId pointer. GMS will
 *  generate a groupId which will be unique across the cluster, and it will be
 *  returned through groupId pointer.
 */
extern ClRcT   clTmsSendAll(
        CL_IN   ClGmsHandleT        svcHandle,
        CL_IN   ClGmsGroupIdT       groupId,
        CL_IN   ClGmsMemberIdT      memberId,
        CL_IN   ClTimeT             timeout,
        CL_IN   ClUint32T           dataSize,
        CL_IN   ClPtrT              data);

/**
 ************************************
 *  \brief Configures the group tracking mode.
 * 
 *  \par Header File:
 *  clTmsApi.h
 *
 *  \param svcHandle Handle of the GMS service session.
 *  \param groupId Id of the group.
 *  \param trackFlags Requested tracking mode.
 *  \param notificationBuffer Notification buffer provided by you while making a 
 *  request for the \c CURRENT view. This is an optional parameter.
 *
 *  \retval CL_ERR_INVALID_HANDLE On passing an invalid handle.
 *  \retval CL_GMS_ERR_GROUP_DOES_NOT_EXIST If the requested group does not exist.
 *  \retval CL_ERR_INVALID_PARAMETER On passing an invalid parameter. 
 *  \retval CL_ERR_NULL_POINTER On passing a NULL pointer.
 *
 *  \par Description:
 *  This API is used to configure the group tracking mode for a given group. It 
 *  can be called subsequently to modify the requested tracking mode.
 *
 */
extern ClRcT clTmsGroupTrack(
        CL_IN    ClTmsHandleT           svcHandle,
        CL_IN    ClTmsGroupIdT          groupId,
        CL_IN    ClUint8T               trackFlags,
        CL_INOUT ClTmsGroupNotificationBufferT *notificationBuffer);

/**
 ************************************
 *  \brief Stops all the group tracking.
 * 
 *  \par Header File:
 *  clTmsApi.h
 * 
 *  \param svcHandle Handle of the GMS service session.
 *  \param groupId Id of the group.
 *
 *  \retval CL_ERR_INVALID_HANDLE On passing an invalid handle.
 *  \retval CL_GMS_ERR_GROUP_DOES_NOT_EXIST If the requested group does not exist.
 *
 *  \par Description:
 *  This API is used to immediately stop all the group tracking for a group.
 *      
 *  \par Library File:
 *  libClGms
 * 
 */
extern ClRcT clTmsGroupTrackStop(
        CL_IN ClTmsHandleT              svcHandle,
        CL_IN ClTmsGroupIdT             groupId);

/**
 ************************************
 *  \brief Returns the information on all the groups.
 * 
 *  \par Header File:
 *  clTmsApi.h
 *
 *  \param svcHandle Handle of the GMS service session.
 *  \param groupInfo Pointer to the structure holding noOfGroups param and a pointer.
 *
 *  The user should specify the pointer to the structure of type clGmsGroupInfoT,
 *  in which GMS will allocate the memory for groupInfo pointer and fills the noOfGroups
 *  value. The user should deallocate the memory given with groupInfo pointer.
 *
 *  \retval CL_ERR_INVALID_HANDLE On passing an invalid handle.
 *  \retval CL_ERR_INVALID_PARAMETER On passing an invalid parameter. 
 *  \retval CL_ERR_NULL_POINTER On passing a NULL pointer.
 *
 *  \par Description:
 *  This API is used to retrieve the information on all the groups existing on the node.
 *  The user should pass the pointer to the ClGmsGroupInfoListT data structer. GMS
 *  will allocate the memory for all the groups info and fills in the noOfGroups param
 *
 *  \par Library File:
 *  libClGms
 * 
 */

extern ClRcT clTmsListGroups(
        CL_IN     ClTmsHandleT             svcHandle,
        CL_IN     ClTimeT                  timeout,
        CL_INOUT  ClTmsGroupInfoListT     *groups);


/**
 ************************************
 *  \brief Returns the information of a group specified by the groupName
 * 
 *  \par Header File:
 *  clTmsApi.h
 *
 *  \param svcHandle Handle of the GMS service session.
 *  \param groupName Pointer to ClGmsGroupNameT structure holding the value and 
 *                   length for the name of the group for which info is requested.
 *  \param timeout   Max timeout value for the API.
 *  \param groupInfo Pointer to ClGmsGroupInfoT structure. User has to allocate
 *                   memory for the ClGmsGroupInfoT structure and pass the
 *                   address of the memory location throught groupInfo pointer.
 *                   GMS will fill-in the values in the memory pointed by groupInfo
 *
 *
 *  \retval CL_ERR_INVALID_HANDLE On passing an invalid handle.
 *  \retval CL_ERR_NULL_POINTER   groupName or groupInfo pointers are NULL
 *  \retval CL_ERR_TIMEOUT        Operation Timed out.
 *  \retval CL_ERR_DOESNT_EXIST   Group indicated by the groupName doesnt exist.
 *  \retval CL_ERR_TRY_AGAIN      Server is not ready to serve the request.
 *
 *  \par Description:
 *  This API is used to retrieve the information on a given group member. 
 *  The space for the member node must be allocated by you.
 * 
 *  \par Library File:
 *  libClGms
 *
 */

extern ClRcT clTmsGetGroupInfo(
        CL_IN     ClTmsHandleT             svcHandle,
        CL_IN     ClTmsGroupNameT         *groupName,
        CL_IN     ClTimeT                  timeout,
        CL_INOUT  ClTmsGroupInfoT         *groupInfo);

#ifdef  __cplusplus
}
#endif

#endif  /* _CL_TMS_API_H_ */

/** \} */

