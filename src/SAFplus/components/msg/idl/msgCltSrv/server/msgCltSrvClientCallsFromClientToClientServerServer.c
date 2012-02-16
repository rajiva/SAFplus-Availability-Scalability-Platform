/*********************************************************************
* ModuleName  : idl
*********************************************************************/
/*********************************************************************
* Description :Server Stub routines
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/
#include <netinet/in.h>
#include <clBufferApi.h>
#include <clRmdApi.h>
#include <clEoApi.h>
#include <ipi/clRmdIpi.h>
#include <string.h>
#include "msgCltSrvClientCallsFromClientToClientServerServer.h"
#include "msgCltSrvServer.h"

extern ClUint32T  msgCltSrvidlSyncKey;
extern ClHandleDatabaseHandleT  msgCltSrvidlDatabaseHdl;



ClRcT clMsgQueueStatusGetServer_4_0_0(ClEoDataT eoData, ClBufferHandleT inMsgHdl, ClBufferHandleT outMsgHdl)
{
    ClIdlContextInfoT *pIdlCtxInfo = NULL;
    ClRcT rc = CL_OK;
    ClNameT  pQueueName;
    SaMsgQueueStatusT_4_0_0  pQueueStatus;

    memset(&(pQueueName), 0, sizeof(ClNameT));
    memset(&(pQueueStatus), 0, sizeof(SaMsgQueueStatusT_4_0_0));


    rc = clXdrUnmarshallClNameT( inMsgHdl,&(pQueueName));
    if (CL_OK != rc)
    {
        goto LL0;
    }

    pIdlCtxInfo = (ClIdlContextInfoT *)clHeapAllocate(sizeof(ClIdlContextInfoT));
    if(pIdlCtxInfo == NULL)
    {
       return CL_IDL_RC(CL_ERR_NO_MEMORY);
    }
    memset(pIdlCtxInfo, 0, sizeof(ClIdlContextInfoT));
    pIdlCtxInfo->idlDeferMsg = outMsgHdl; 
    pIdlCtxInfo->inProgress  = CL_FALSE;
    rc = clIdlSyncPrivateInfoSet(msgCltSrvidlSyncKey, (void *)pIdlCtxInfo);
    if (CL_OK != rc)
    {
        clHeapFree(pIdlCtxInfo);
        goto L0;
    }
    rc = clMsgQueueStatusGet_4_0_0(&(pQueueName), &(pQueueStatus));
    if(pIdlCtxInfo->inProgress == CL_FALSE)
    {
      clHeapFree(pIdlCtxInfo);
      pIdlCtxInfo = NULL;
    }
    if (CL_OK != rc)
    {
       goto L0;
    }
    
    rc = clXdrMarshallClNameT(&(pQueueName), 0, 1);
    if (CL_OK != rc)
    {
        goto L1;
    }

    if(pIdlCtxInfo != NULL)
    {
      clHeapFree(pIdlCtxInfo);
      return rc;
    }
    
    rc = clXdrMarshallSaMsgQueueStatusT_4_0_0(&(pQueueStatus), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L2;
    }

L2:    return rc;

LL0:  clXdrMarshallClNameT(&(pQueueName), 0, 1);

    return rc;

L0:  clXdrMarshallClNameT(&(pQueueName), 0, 1);

L1:  clXdrMarshallSaMsgQueueStatusT_4_0_0(&(pQueueStatus), 0, 1);

    return rc;
}

ClRcT clMsgQueueStatusGetResponseSend_4_0_0(ClIdlHandleT idlHdl,ClRcT retCode,CL_OUT  SaMsgQueueStatusT_4_0_0  pQueueStatus)
{
    ClIdlSyncInfoT    *pIdlSyncDeferInfo = NULL;
    ClRcT              rc                = CL_OK;
    ClBufferHandleT outMsgHdl     = 0;
    
    rc = clHandleCheckout(msgCltSrvidlDatabaseHdl,idlHdl,(void **)&pIdlSyncDeferInfo);
    if( rc != CL_OK)
    {
      goto Label0; 
    }
    outMsgHdl = pIdlSyncDeferInfo->idlRmdDeferMsg;
    
    rc = clXdrMarshallSaMsgQueueStatusT_4_0_0(&(pQueueStatus), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L2;
    }

    rc = clIdlSyncResponseSend(pIdlSyncDeferInfo->idlRmdDeferHdl,outMsgHdl,
                                retCode);
    goto Label1; 
L2:  clXdrMarshallSaMsgQueueStatusT_4_0_0(&(pQueueStatus), 0, 1);

    clHandleCheckin(msgCltSrvidlDatabaseHdl, idlHdl);
    clHandleDestroy(msgCltSrvidlDatabaseHdl, idlHdl);
    return rc;
Label1:
    clHandleCheckin(msgCltSrvidlDatabaseHdl, idlHdl);
    clHandleDestroy(msgCltSrvidlDatabaseHdl, idlHdl);
Label0:
    return rc;
}

ClRcT clMsgQueueUnlinkServer_4_0_0(ClEoDataT eoData, ClBufferHandleT inMsgHdl, ClBufferHandleT outMsgHdl)
{
    ClIdlContextInfoT *pIdlCtxInfo = NULL;
    ClRcT rc = CL_OK;
    ClNameT  pQueueName;

    memset(&(pQueueName), 0, sizeof(ClNameT));


    rc = clXdrUnmarshallClNameT( inMsgHdl,&(pQueueName));
    if (CL_OK != rc)
    {
        goto LL0;
    }

    pIdlCtxInfo = (ClIdlContextInfoT *)clHeapAllocate(sizeof(ClIdlContextInfoT));
    if(pIdlCtxInfo == NULL)
    {
       return CL_IDL_RC(CL_ERR_NO_MEMORY);
    }
    memset(pIdlCtxInfo, 0, sizeof(ClIdlContextInfoT));
    pIdlCtxInfo->idlDeferMsg = outMsgHdl; 
    pIdlCtxInfo->inProgress  = CL_FALSE;
    rc = clIdlSyncPrivateInfoSet(msgCltSrvidlSyncKey, (void *)pIdlCtxInfo);
    if (CL_OK != rc)
    {
        clHeapFree(pIdlCtxInfo);
        goto L0;
    }
    rc = clMsgQueueUnlink_4_0_0(&(pQueueName));
    if(pIdlCtxInfo->inProgress == CL_FALSE)
    {
      clHeapFree(pIdlCtxInfo);
      pIdlCtxInfo = NULL;
    }
    if (CL_OK != rc)
    {
       goto L0;
    }
    
    rc = clXdrMarshallClNameT(&(pQueueName), 0, 1);
    if (CL_OK != rc)
    {
        goto L1;
    }

    if(pIdlCtxInfo != NULL)
    {
      clHeapFree(pIdlCtxInfo);
      return rc;
    }
    
L1:    return rc;

LL0:  clXdrMarshallClNameT(&(pQueueName), 0, 1);

    return rc;

L0:  clXdrMarshallClNameT(&(pQueueName), 0, 1);


    return rc;
}

ClRcT clMsgQueueUnlinkResponseSend_4_0_0(ClIdlHandleT idlHdl,ClRcT retCode)
{
    ClIdlSyncInfoT    *pIdlSyncDeferInfo = NULL;
    ClRcT              rc                = CL_OK;
    ClBufferHandleT outMsgHdl     = 0;
    
    rc = clHandleCheckout(msgCltSrvidlDatabaseHdl,idlHdl,(void **)&pIdlSyncDeferInfo);
    if( rc != CL_OK)
    {
      goto Label0; 
    }
    outMsgHdl = pIdlSyncDeferInfo->idlRmdDeferMsg;
    
    rc = clIdlSyncResponseSend(pIdlSyncDeferInfo->idlRmdDeferHdl,outMsgHdl,
                                retCode);
    

    

    clHandleCheckin(msgCltSrvidlDatabaseHdl, idlHdl);
    clHandleDestroy(msgCltSrvidlDatabaseHdl, idlHdl);
Label0:
    return rc;
}

ClRcT clMsgQueueInfoGetServer_4_0_0(ClEoDataT eoData, ClBufferHandleT inMsgHdl, ClBufferHandleT outMsgHdl)
{
    ClIdlContextInfoT *pIdlCtxInfo = NULL;
    ClRcT rc = CL_OK;
    ClNameT  pQName;
    SaMsgQueueCreationAttributesT_4_0_0  pQAttrs;

    memset(&(pQName), 0, sizeof(ClNameT));
    memset(&(pQAttrs), 0, sizeof(SaMsgQueueCreationAttributesT_4_0_0));


    rc = clXdrUnmarshallClNameT( inMsgHdl,&(pQName));
    if (CL_OK != rc)
    {
        goto LL0;
    }

    pIdlCtxInfo = (ClIdlContextInfoT *)clHeapAllocate(sizeof(ClIdlContextInfoT));
    if(pIdlCtxInfo == NULL)
    {
       return CL_IDL_RC(CL_ERR_NO_MEMORY);
    }
    memset(pIdlCtxInfo, 0, sizeof(ClIdlContextInfoT));
    pIdlCtxInfo->idlDeferMsg = outMsgHdl; 
    pIdlCtxInfo->inProgress  = CL_FALSE;
    rc = clIdlSyncPrivateInfoSet(msgCltSrvidlSyncKey, (void *)pIdlCtxInfo);
    if (CL_OK != rc)
    {
        clHeapFree(pIdlCtxInfo);
        goto L0;
    }
    rc = clMsgQueueInfoGet_4_0_0(&(pQName), &(pQAttrs));
    if(pIdlCtxInfo->inProgress == CL_FALSE)
    {
      clHeapFree(pIdlCtxInfo);
      pIdlCtxInfo = NULL;
    }
    if (CL_OK != rc)
    {
       goto L0;
    }
    
    rc = clXdrMarshallClNameT(&(pQName), 0, 1);
    if (CL_OK != rc)
    {
        goto L1;
    }

    if(pIdlCtxInfo != NULL)
    {
      clHeapFree(pIdlCtxInfo);
      return rc;
    }
    
    rc = clXdrMarshallSaMsgQueueCreationAttributesT_4_0_0(&(pQAttrs), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L2;
    }

L2:    return rc;

LL0:  clXdrMarshallClNameT(&(pQName), 0, 1);

    return rc;

L0:  clXdrMarshallClNameT(&(pQName), 0, 1);

L1:  clXdrMarshallSaMsgQueueCreationAttributesT_4_0_0(&(pQAttrs), 0, 1);

    return rc;
}

ClRcT clMsgQueueInfoGetResponseSend_4_0_0(ClIdlHandleT idlHdl,ClRcT retCode,CL_OUT  SaMsgQueueCreationAttributesT_4_0_0  pQAttrs)
{
    ClIdlSyncInfoT    *pIdlSyncDeferInfo = NULL;
    ClRcT              rc                = CL_OK;
    ClBufferHandleT outMsgHdl     = 0;
    
    rc = clHandleCheckout(msgCltSrvidlDatabaseHdl,idlHdl,(void **)&pIdlSyncDeferInfo);
    if( rc != CL_OK)
    {
      goto Label0; 
    }
    outMsgHdl = pIdlSyncDeferInfo->idlRmdDeferMsg;
    
    rc = clXdrMarshallSaMsgQueueCreationAttributesT_4_0_0(&(pQAttrs), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L2;
    }

    rc = clIdlSyncResponseSend(pIdlSyncDeferInfo->idlRmdDeferHdl,outMsgHdl,
                                retCode);
    goto Label1; 
L2:  clXdrMarshallSaMsgQueueCreationAttributesT_4_0_0(&(pQAttrs), 0, 1);

    clHandleCheckin(msgCltSrvidlDatabaseHdl, idlHdl);
    clHandleDestroy(msgCltSrvidlDatabaseHdl, idlHdl);
    return rc;
Label1:
    clHandleCheckin(msgCltSrvidlDatabaseHdl, idlHdl);
    clHandleDestroy(msgCltSrvidlDatabaseHdl, idlHdl);
Label0:
    return rc;
}

ClRcT clMsgQueueMoveMessagesServer_4_0_0(ClEoDataT eoData, ClBufferHandleT inMsgHdl, ClBufferHandleT outMsgHdl)
{
    ClIdlContextInfoT *pIdlCtxInfo = NULL;
    ClRcT rc = CL_OK;
    ClNameT  pQName;
    ClUint32T  openFlags;
    ClUint16T  qDelete;

    memset(&(pQName), 0, sizeof(ClNameT));
    memset(&(openFlags), 0, sizeof(ClUint32T));
    memset(&(qDelete), 0, sizeof(ClUint16T));


    rc = clXdrUnmarshallClNameT( inMsgHdl,&(pQName));
    if (CL_OK != rc)
    {
        goto LL0;
    }

    rc = clXdrUnmarshallClUint32T( inMsgHdl,&(openFlags));
    if (CL_OK != rc)
    {
        goto LL1;
    }

    rc = clXdrUnmarshallClUint16T( inMsgHdl,&(qDelete));
    if (CL_OK != rc)
    {
        goto LL2;
    }

    pIdlCtxInfo = (ClIdlContextInfoT *)clHeapAllocate(sizeof(ClIdlContextInfoT));
    if(pIdlCtxInfo == NULL)
    {
       return CL_IDL_RC(CL_ERR_NO_MEMORY);
    }
    memset(pIdlCtxInfo, 0, sizeof(ClIdlContextInfoT));
    pIdlCtxInfo->idlDeferMsg = outMsgHdl; 
    pIdlCtxInfo->inProgress  = CL_FALSE;
    rc = clIdlSyncPrivateInfoSet(msgCltSrvidlSyncKey, (void *)pIdlCtxInfo);
    if (CL_OK != rc)
    {
        clHeapFree(pIdlCtxInfo);
        goto L0;
    }
    rc = clMsgQueueMoveMessages_4_0_0(&(pQName), openFlags, qDelete);
    if(pIdlCtxInfo->inProgress == CL_FALSE)
    {
      clHeapFree(pIdlCtxInfo);
      pIdlCtxInfo = NULL;
    }
    if (CL_OK != rc)
    {
       goto L0;
    }
    
    rc = clXdrMarshallClNameT(&(pQName), 0, 1);
    if (CL_OK != rc)
    {
        goto L1;
    }

    rc = clXdrMarshallClUint32T(&(openFlags), 0, 1);
    if (CL_OK != rc)
    {
        goto L2;
    }

    rc = clXdrMarshallClUint16T(&(qDelete), 0, 1);
    if (CL_OK != rc)
    {
        goto L3;
    }

    if(pIdlCtxInfo != NULL)
    {
      clHeapFree(pIdlCtxInfo);
      return rc;
    }
    
L3:    return rc;

LL2:  clXdrMarshallClUint16T(&(qDelete), 0, 1);
LL1:  clXdrMarshallClUint32T(&(openFlags), 0, 1);
LL0:  clXdrMarshallClNameT(&(pQName), 0, 1);

    return rc;

L0:  clXdrMarshallClNameT(&(pQName), 0, 1);
L1:  clXdrMarshallClUint32T(&(openFlags), 0, 1);
L2:  clXdrMarshallClUint16T(&(qDelete), 0, 1);


    return rc;
}

ClRcT clMsgQueueMoveMessagesResponseSend_4_0_0(ClIdlHandleT idlHdl,ClRcT retCode)
{
    ClIdlSyncInfoT    *pIdlSyncDeferInfo = NULL;
    ClRcT              rc                = CL_OK;
    ClBufferHandleT outMsgHdl     = 0;
    
    rc = clHandleCheckout(msgCltSrvidlDatabaseHdl,idlHdl,(void **)&pIdlSyncDeferInfo);
    if( rc != CL_OK)
    {
      goto Label0; 
    }
    outMsgHdl = pIdlSyncDeferInfo->idlRmdDeferMsg;
    
    rc = clIdlSyncResponseSend(pIdlSyncDeferInfo->idlRmdDeferHdl,outMsgHdl,
                                retCode);
    

    

    clHandleCheckin(msgCltSrvidlDatabaseHdl, idlHdl);
    clHandleDestroy(msgCltSrvidlDatabaseHdl, idlHdl);
Label0:
    return rc;
}

ClRcT clMsgMessageReceivedServer_4_0_0(ClEoDataT eoData, ClBufferHandleT inMsgHdl, ClBufferHandleT outMsgHdl)
{
    ClIdlContextInfoT *pIdlCtxInfo = NULL;
    ClRcT rc = CL_OK;
    ClUint32T  sendType;
    ClNameT  pDestination;
    SaMsgMessageT_4_0_0  pMessage;
    ClInt64T  sendTime;
    ClHandleT  senderHandle;
    ClInt64T  timeout;

    memset(&(sendType), 0, sizeof(ClUint32T));
    memset(&(pDestination), 0, sizeof(ClNameT));
    memset(&(pMessage), 0, sizeof(SaMsgMessageT_4_0_0));
    memset(&(sendTime), 0, sizeof(ClInt64T));
    memset(&(senderHandle), 0, sizeof(ClHandleT));
    memset(&(timeout), 0, sizeof(ClInt64T));


    rc = clXdrUnmarshallClUint32T( inMsgHdl,&(sendType));
    if (CL_OK != rc)
    {
        goto LL0;
    }

    rc = clXdrUnmarshallClNameT( inMsgHdl,&(pDestination));
    if (CL_OK != rc)
    {
        goto LL1;
    }

    rc = clXdrUnmarshallSaMsgMessageT_4_0_0( inMsgHdl,&(pMessage));
    if (CL_OK != rc)
    {
        goto LL2;
    }

    rc = clXdrUnmarshallClInt64T( inMsgHdl,&(sendTime));
    if (CL_OK != rc)
    {
        goto LL3;
    }

    rc = clXdrUnmarshallClHandleT( inMsgHdl,&(senderHandle));
    if (CL_OK != rc)
    {
        goto LL4;
    }

    rc = clXdrUnmarshallClInt64T( inMsgHdl,&(timeout));
    if (CL_OK != rc)
    {
        goto LL5;
    }

    pIdlCtxInfo = (ClIdlContextInfoT *)clHeapAllocate(sizeof(ClIdlContextInfoT));
    if(pIdlCtxInfo == NULL)
    {
       return CL_IDL_RC(CL_ERR_NO_MEMORY);
    }
    memset(pIdlCtxInfo, 0, sizeof(ClIdlContextInfoT));
    pIdlCtxInfo->idlDeferMsg = outMsgHdl; 
    pIdlCtxInfo->inProgress  = CL_FALSE;
    rc = clIdlSyncPrivateInfoSet(msgCltSrvidlSyncKey, (void *)pIdlCtxInfo);
    if (CL_OK != rc)
    {
        clHeapFree(pIdlCtxInfo);
        goto L0;
    }
    rc = clMsgMessageReceived_4_0_0(sendType, &(pDestination), &(pMessage), sendTime, senderHandle, timeout);
    if(pIdlCtxInfo->inProgress == CL_FALSE)
    {
      clHeapFree(pIdlCtxInfo);
      pIdlCtxInfo = NULL;
    }
    if (CL_OK != rc)
    {
       goto L0;
    }
    
    rc = clXdrMarshallClUint32T(&(sendType), 0, 1);
    if (CL_OK != rc)
    {
        goto L1;
    }

    rc = clXdrMarshallClNameT(&(pDestination), 0, 1);
    if (CL_OK != rc)
    {
        goto L2;
    }

    rc = clXdrMarshallSaMsgMessageT_4_0_0(&(pMessage), 0, 1);
    if (CL_OK != rc)
    {
        goto L3;
    }

    rc = clXdrMarshallClInt64T(&(sendTime), 0, 1);
    if (CL_OK != rc)
    {
        goto L4;
    }

    rc = clXdrMarshallClHandleT(&(senderHandle), 0, 1);
    if (CL_OK != rc)
    {
        goto L5;
    }

    rc = clXdrMarshallClInt64T(&(timeout), 0, 1);
    if (CL_OK != rc)
    {
        goto L6;
    }

    if(pIdlCtxInfo != NULL)
    {
      clHeapFree(pIdlCtxInfo);
      return rc;
    }
    
L6:    return rc;

LL5:  clXdrMarshallClInt64T(&(timeout), 0, 1);
LL4:  clXdrMarshallClHandleT(&(senderHandle), 0, 1);
LL3:  clXdrMarshallClInt64T(&(sendTime), 0, 1);
LL2:  clXdrMarshallSaMsgMessageT_4_0_0(&(pMessage), 0, 1);
LL1:  clXdrMarshallClNameT(&(pDestination), 0, 1);
LL0:  clXdrMarshallClUint32T(&(sendType), 0, 1);

    return rc;

L0:  clXdrMarshallClUint32T(&(sendType), 0, 1);
L1:  clXdrMarshallClNameT(&(pDestination), 0, 1);
L2:  clXdrMarshallSaMsgMessageT_4_0_0(&(pMessage), 0, 1);
L3:  clXdrMarshallClInt64T(&(sendTime), 0, 1);
L4:  clXdrMarshallClHandleT(&(senderHandle), 0, 1);
L5:  clXdrMarshallClInt64T(&(timeout), 0, 1);


    return rc;
}

ClRcT clMsgMessageReceivedResponseSend_4_0_0(ClIdlHandleT idlHdl,ClRcT retCode)
{
    ClIdlSyncInfoT    *pIdlSyncDeferInfo = NULL;
    ClRcT              rc                = CL_OK;
    ClBufferHandleT outMsgHdl     = 0;
    
    rc = clHandleCheckout(msgCltSrvidlDatabaseHdl,idlHdl,(void **)&pIdlSyncDeferInfo);
    if( rc != CL_OK)
    {
      goto Label0; 
    }
    outMsgHdl = pIdlSyncDeferInfo->idlRmdDeferMsg;
    
    rc = clIdlSyncResponseSend(pIdlSyncDeferInfo->idlRmdDeferHdl,outMsgHdl,
                                retCode);
    

    

    clHandleCheckin(msgCltSrvidlDatabaseHdl, idlHdl);
    clHandleDestroy(msgCltSrvidlDatabaseHdl, idlHdl);
Label0:
    return rc;
}

