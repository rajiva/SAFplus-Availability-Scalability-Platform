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
#include "LogPortStreamOwnerServer.h"
#include "LogServer.h"

extern ClUint32T  LogidlSyncKey;
extern ClHandleDatabaseHandleT  LogidlDatabaseHdl;



ClRcT clLogStreamOwnerStreamOpenServer_4_0_0(ClEoDataT eoData, ClBufferHandleT inMsgHdl, ClBufferHandleT outMsgHdl)
{
    ClIdlContextInfoT *pIdlCtxInfo = NULL;
    ClRcT rc = CL_OK;
    ClUint8T  logOpenFlags;
    ClUint32T  nodeAddr;
    ClNameT  pStreamName;
    ClUint32T  pStreamScope;
    ClNameT  pStreamScopeNode;
    ClUint32T  compId;
    ClLogStreamAttrIDLT_4_0_0  pStreamAttr;
    ClUint64T  pStreamMastAddr;
    ClLogFilterT_4_0_0  pStreamFilter;
    ClUint32T  pAckerCnt;
    ClUint32T  pNonAckerCnt;
    ClUint16T  pStreamId;

    memset(&(logOpenFlags), 0, sizeof(ClUint8T));
    memset(&(nodeAddr), 0, sizeof(ClUint32T));
    memset(&(pStreamName), 0, sizeof(ClNameT));
    memset(&(pStreamScope), 0, sizeof(ClUint32T));
    memset(&(pStreamScopeNode), 0, sizeof(ClNameT));
    memset(&(compId), 0, sizeof(ClUint32T));
    memset(&(pStreamAttr), 0, sizeof(ClLogStreamAttrIDLT_4_0_0));
    memset(&(pStreamMastAddr), 0, sizeof(ClUint64T));
    memset(&(pStreamFilter), 0, sizeof(ClLogFilterT_4_0_0));
    memset(&(pAckerCnt), 0, sizeof(ClUint32T));
    memset(&(pNonAckerCnt), 0, sizeof(ClUint32T));
    memset(&(pStreamId), 0, sizeof(ClUint16T));


    rc = clXdrUnmarshallClUint8T( inMsgHdl,&(logOpenFlags));
    if (CL_OK != rc)
    {
        goto LL0;
    }

    rc = clXdrUnmarshallClUint32T( inMsgHdl,&(nodeAddr));
    if (CL_OK != rc)
    {
        goto LL1;
    }

    rc = clXdrUnmarshallClNameT( inMsgHdl,&(pStreamName));
    if (CL_OK != rc)
    {
        goto LL2;
    }

    rc = clXdrUnmarshallClUint32T( inMsgHdl,&(pStreamScope));
    if (CL_OK != rc)
    {
        goto LL3;
    }

    rc = clXdrUnmarshallClNameT( inMsgHdl,&(pStreamScopeNode));
    if (CL_OK != rc)
    {
        goto LL4;
    }

    rc = clXdrUnmarshallClUint32T( inMsgHdl,&(compId));
    if (CL_OK != rc)
    {
        goto LL5;
    }

    rc = clXdrUnmarshallClLogStreamAttrIDLT_4_0_0( inMsgHdl,&(pStreamAttr));
    if (CL_OK != rc)
    {
        goto LL6;
    }

    rc = clXdrUnmarshallClUint16T( inMsgHdl,&(pStreamId));
    if (CL_OK != rc)
    {
        goto LL7;
    }

    pIdlCtxInfo = (ClIdlContextInfoT *)clHeapAllocate(sizeof(ClIdlContextInfoT));
    if(pIdlCtxInfo == NULL)
    {
       return CL_IDL_RC(CL_ERR_NO_MEMORY);
    }
    memset(pIdlCtxInfo, 0, sizeof(ClIdlContextInfoT));
    pIdlCtxInfo->idlDeferMsg = outMsgHdl; 
    pIdlCtxInfo->inProgress  = CL_FALSE;
    rc = clIdlSyncPrivateInfoSet(LogidlSyncKey, (void *)pIdlCtxInfo);
    if (CL_OK != rc)
    {
        clHeapFree(pIdlCtxInfo);
        goto L0;
    }
    rc = clLogStreamOwnerStreamOpen_4_0_0(logOpenFlags, nodeAddr, &(pStreamName), &(pStreamScope), &(pStreamScopeNode), &(compId), &(pStreamAttr), &(pStreamMastAddr), &(pStreamFilter), &(pAckerCnt), &(pNonAckerCnt), &(pStreamId));
    if(pIdlCtxInfo->inProgress == CL_FALSE)
    {
      clHeapFree(pIdlCtxInfo);
      pIdlCtxInfo = NULL;
    }
    if (CL_OK != rc)
    {
       goto L0;
    }
    
    rc = clXdrMarshallClUint8T(&(logOpenFlags), 0, 1);
    if (CL_OK != rc)
    {
        goto L1;
    }

    rc = clXdrMarshallClUint32T(&(nodeAddr), 0, 1);
    if (CL_OK != rc)
    {
        goto L2;
    }

    if(pIdlCtxInfo != NULL)
    {
      clHeapFree(pIdlCtxInfo);
      return rc;
    }
    
    rc = clXdrMarshallClNameT(&(pStreamName), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L3;
    }

    rc = clXdrMarshallClUint32T(&(pStreamScope), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L4;
    }

    rc = clXdrMarshallClNameT(&(pStreamScopeNode), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L5;
    }

    rc = clXdrMarshallClUint32T(&(compId), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L6;
    }

    rc = clXdrMarshallClLogStreamAttrIDLT_4_0_0(&(pStreamAttr), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L7;
    }

    rc = clXdrMarshallClUint16T(&(pStreamId), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L8;
    }

    rc = clXdrMarshallClUint64T(&(pStreamMastAddr), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L9;
    }

    rc = clXdrMarshallClLogFilterT_4_0_0(&(pStreamFilter), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L10;
    }

    rc = clXdrMarshallClUint32T(&(pAckerCnt), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L11;
    }

    rc = clXdrMarshallClUint32T(&(pNonAckerCnt), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L12;
    }

L12:    return rc;

LL7:  clXdrMarshallClUint16T(&(pStreamId), 0, 1);
LL6:  clXdrMarshallClLogStreamAttrIDLT_4_0_0(&(pStreamAttr), 0, 1);
LL5:  clXdrMarshallClUint32T(&(compId), 0, 1);
LL4:  clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);
LL3:  clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
LL2:  clXdrMarshallClNameT(&(pStreamName), 0, 1);
LL1:  clXdrMarshallClUint32T(&(nodeAddr), 0, 1);
LL0:  clXdrMarshallClUint8T(&(logOpenFlags), 0, 1);

    return rc;

L0:  clXdrMarshallClUint8T(&(logOpenFlags), 0, 1);
L1:  clXdrMarshallClUint32T(&(nodeAddr), 0, 1);

L2:  clXdrMarshallClNameT(&(pStreamName), 0, 1);
L3:  clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
L4:  clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);
L5:  clXdrMarshallClUint32T(&(compId), 0, 1);
L6:  clXdrMarshallClLogStreamAttrIDLT_4_0_0(&(pStreamAttr), 0, 1);
L7:  clXdrMarshallClUint16T(&(pStreamId), 0, 1);
L8:  clXdrMarshallClUint64T(&(pStreamMastAddr), 0, 1);
L9:  clXdrMarshallClLogFilterT_4_0_0(&(pStreamFilter), 0, 1);
L10:  clXdrMarshallClUint32T(&(pAckerCnt), 0, 1);
L11:  clXdrMarshallClUint32T(&(pNonAckerCnt), 0, 1);

    return rc;
}

ClRcT clLogStreamOwnerStreamOpenResponseSend_4_0_0(ClIdlHandleT idlHdl,ClRcT retCode,CL_INOUT  ClNameT  pStreamName,CL_INOUT  ClUint32T  pStreamScope,CL_INOUT  ClNameT  pStreamScopeNode,CL_INOUT  ClUint32T  compId,CL_INOUT  ClLogStreamAttrIDLT_4_0_0  pStreamAttr,CL_OUT  ClUint64T  pStreamMastAddr,CL_OUT  ClLogFilterT_4_0_0  pStreamFilter,CL_OUT  ClUint32T  pAckerCnt,CL_OUT  ClUint32T  pNonAckerCnt,CL_INOUT  ClUint16T  pStreamId)
{
    ClIdlSyncInfoT    *pIdlSyncDeferInfo = NULL;
    ClRcT              rc                = CL_OK;
    ClBufferHandleT outMsgHdl     = 0;
    
    rc = clHandleCheckout(LogidlDatabaseHdl,idlHdl,(void **)&pIdlSyncDeferInfo);
    if( rc != CL_OK)
    {
      goto Label0; 
    }
    outMsgHdl = pIdlSyncDeferInfo->idlRmdDeferMsg;
    
    rc = clXdrMarshallClNameT(&(pStreamName), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L3;
    }

    rc = clXdrMarshallClUint32T(&(pStreamScope), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L4;
    }

    rc = clXdrMarshallClNameT(&(pStreamScopeNode), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L5;
    }

    rc = clXdrMarshallClUint32T(&(compId), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L6;
    }

    rc = clXdrMarshallClLogStreamAttrIDLT_4_0_0(&(pStreamAttr), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L7;
    }

    rc = clXdrMarshallClUint16T(&(pStreamId), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L8;
    }

    rc = clXdrMarshallClUint64T(&(pStreamMastAddr), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L9;
    }

    rc = clXdrMarshallClLogFilterT_4_0_0(&(pStreamFilter), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L10;
    }

    rc = clXdrMarshallClUint32T(&(pAckerCnt), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L11;
    }

    rc = clXdrMarshallClUint32T(&(pNonAckerCnt), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L12;
    }

    rc = clIdlSyncResponseSend(pIdlSyncDeferInfo->idlRmdDeferHdl,outMsgHdl,
                                retCode);
    goto Label1; 
L3:  clXdrMarshallClNameT(&(pStreamName), 0, 1);
L4:  clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
L5:  clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);
L6:  clXdrMarshallClUint32T(&(compId), 0, 1);
L7:  clXdrMarshallClLogStreamAttrIDLT_4_0_0(&(pStreamAttr), 0, 1);
L8:  clXdrMarshallClUint16T(&(pStreamId), 0, 1);
L9:  clXdrMarshallClUint64T(&(pStreamMastAddr), 0, 1);
L10:  clXdrMarshallClLogFilterT_4_0_0(&(pStreamFilter), 0, 1);
L11:  clXdrMarshallClUint32T(&(pAckerCnt), 0, 1);
L12:  clXdrMarshallClUint32T(&(pNonAckerCnt), 0, 1);

    clHandleCheckin(LogidlDatabaseHdl, idlHdl);
    clHandleDestroy(LogidlDatabaseHdl, idlHdl);
    return rc;
Label1:
    clHandleCheckin(LogidlDatabaseHdl, idlHdl);
    clHandleDestroy(LogidlDatabaseHdl, idlHdl);
Label0:
    return rc;
}

ClRcT clLogStreamOwnerStreamCloseServer_4_0_0(ClEoDataT eoData, ClBufferHandleT inMsgHdl, ClBufferHandleT outMsgHdl)
{
    ClIdlContextInfoT *pIdlCtxInfo = NULL;
    ClRcT rc = CL_OK;
    ClNameT  pStreamName;
    ClUint32T  pStreamScope;
    ClNameT  pStreamScopeNode;
    ClUint32T  nodeAddress;
    ClUint32T  compId;

    memset(&(pStreamName), 0, sizeof(ClNameT));
    memset(&(pStreamScope), 0, sizeof(ClUint32T));
    memset(&(pStreamScopeNode), 0, sizeof(ClNameT));
    memset(&(nodeAddress), 0, sizeof(ClUint32T));
    memset(&(compId), 0, sizeof(ClUint32T));


    rc = clXdrUnmarshallClNameT( inMsgHdl,&(pStreamName));
    if (CL_OK != rc)
    {
        goto LL0;
    }

    rc = clXdrUnmarshallClUint32T( inMsgHdl,&(pStreamScope));
    if (CL_OK != rc)
    {
        goto LL1;
    }

    rc = clXdrUnmarshallClNameT( inMsgHdl,&(pStreamScopeNode));
    if (CL_OK != rc)
    {
        goto LL2;
    }

    rc = clXdrUnmarshallClUint32T( inMsgHdl,&(nodeAddress));
    if (CL_OK != rc)
    {
        goto LL3;
    }

    rc = clXdrUnmarshallClUint32T( inMsgHdl,&(compId));
    if (CL_OK != rc)
    {
        goto LL4;
    }

    pIdlCtxInfo = (ClIdlContextInfoT *)clHeapAllocate(sizeof(ClIdlContextInfoT));
    if(pIdlCtxInfo == NULL)
    {
       return CL_IDL_RC(CL_ERR_NO_MEMORY);
    }
    memset(pIdlCtxInfo, 0, sizeof(ClIdlContextInfoT));
    pIdlCtxInfo->idlDeferMsg = outMsgHdl; 
    pIdlCtxInfo->inProgress  = CL_FALSE;
    rc = clIdlSyncPrivateInfoSet(LogidlSyncKey, (void *)pIdlCtxInfo);
    if (CL_OK != rc)
    {
        clHeapFree(pIdlCtxInfo);
        goto L0;
    }
    rc = clLogStreamOwnerStreamClose_4_0_0(&(pStreamName), pStreamScope, &(pStreamScopeNode), nodeAddress, compId);
    if(pIdlCtxInfo->inProgress == CL_FALSE)
    {
      clHeapFree(pIdlCtxInfo);
      pIdlCtxInfo = NULL;
    }
    if (CL_OK != rc)
    {
       goto L0;
    }
    
    rc = clXdrMarshallClNameT(&(pStreamName), 0, 1);
    if (CL_OK != rc)
    {
        goto L1;
    }

    rc = clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
    if (CL_OK != rc)
    {
        goto L2;
    }

    rc = clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);
    if (CL_OK != rc)
    {
        goto L3;
    }

    rc = clXdrMarshallClUint32T(&(nodeAddress), 0, 1);
    if (CL_OK != rc)
    {
        goto L4;
    }

    rc = clXdrMarshallClUint32T(&(compId), 0, 1);
    if (CL_OK != rc)
    {
        goto L5;
    }

    if(pIdlCtxInfo != NULL)
    {
      clHeapFree(pIdlCtxInfo);
      return rc;
    }
    
L5:    return rc;

LL4:  clXdrMarshallClUint32T(&(compId), 0, 1);
LL3:  clXdrMarshallClUint32T(&(nodeAddress), 0, 1);
LL2:  clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);
LL1:  clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
LL0:  clXdrMarshallClNameT(&(pStreamName), 0, 1);

    return rc;

L0:  clXdrMarshallClNameT(&(pStreamName), 0, 1);
L1:  clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
L2:  clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);
L3:  clXdrMarshallClUint32T(&(nodeAddress), 0, 1);
L4:  clXdrMarshallClUint32T(&(compId), 0, 1);


    return rc;
}

ClRcT clLogStreamOwnerStreamCloseResponseSend_4_0_0(ClIdlHandleT idlHdl,ClRcT retCode)
{
    ClIdlSyncInfoT    *pIdlSyncDeferInfo = NULL;
    ClRcT              rc                = CL_OK;
    ClBufferHandleT outMsgHdl     = 0;
    
    rc = clHandleCheckout(LogidlDatabaseHdl,idlHdl,(void **)&pIdlSyncDeferInfo);
    if( rc != CL_OK)
    {
      goto Label0; 
    }
    outMsgHdl = pIdlSyncDeferInfo->idlRmdDeferMsg;
    
    rc = clIdlSyncResponseSend(pIdlSyncDeferInfo->idlRmdDeferHdl,outMsgHdl,
                                retCode);
    

    

    clHandleCheckin(LogidlDatabaseHdl, idlHdl);
    clHandleDestroy(LogidlDatabaseHdl, idlHdl);
Label0:
    return rc;
}

ClRcT clLogStreamOwnerFilterSetServer_4_0_0(ClEoDataT eoData, ClBufferHandleT inMsgHdl, ClBufferHandleT outMsgHdl)
{
    ClIdlContextInfoT *pIdlCtxInfo = NULL;
    ClRcT rc = CL_OK;
    ClNameT  pStreamName;
    ClUint32T  pStreamScope;
    ClNameT  pStreamScopeNode;
    ClUint8T  filterFlags;
    ClLogFilterT_4_0_0  pFilter;

    memset(&(pStreamName), 0, sizeof(ClNameT));
    memset(&(pStreamScope), 0, sizeof(ClUint32T));
    memset(&(pStreamScopeNode), 0, sizeof(ClNameT));
    memset(&(filterFlags), 0, sizeof(ClUint8T));
    memset(&(pFilter), 0, sizeof(ClLogFilterT_4_0_0));


    rc = clXdrUnmarshallClNameT( inMsgHdl,&(pStreamName));
    if (CL_OK != rc)
    {
        goto LL0;
    }

    rc = clXdrUnmarshallClUint32T( inMsgHdl,&(pStreamScope));
    if (CL_OK != rc)
    {
        goto LL1;
    }

    rc = clXdrUnmarshallClNameT( inMsgHdl,&(pStreamScopeNode));
    if (CL_OK != rc)
    {
        goto LL2;
    }

    rc = clXdrUnmarshallClUint8T( inMsgHdl,&(filterFlags));
    if (CL_OK != rc)
    {
        goto LL3;
    }

    rc = clXdrUnmarshallClLogFilterT_4_0_0( inMsgHdl,&(pFilter));
    if (CL_OK != rc)
    {
        goto LL4;
    }

    pIdlCtxInfo = (ClIdlContextInfoT *)clHeapAllocate(sizeof(ClIdlContextInfoT));
    if(pIdlCtxInfo == NULL)
    {
       return CL_IDL_RC(CL_ERR_NO_MEMORY);
    }
    memset(pIdlCtxInfo, 0, sizeof(ClIdlContextInfoT));
    pIdlCtxInfo->idlDeferMsg = outMsgHdl; 
    pIdlCtxInfo->inProgress  = CL_FALSE;
    rc = clIdlSyncPrivateInfoSet(LogidlSyncKey, (void *)pIdlCtxInfo);
    if (CL_OK != rc)
    {
        clHeapFree(pIdlCtxInfo);
        goto L0;
    }
    rc = clLogStreamOwnerFilterSet_4_0_0(&(pStreamName), pStreamScope, &(pStreamScopeNode), filterFlags, &(pFilter));
    if(pIdlCtxInfo->inProgress == CL_FALSE)
    {
      clHeapFree(pIdlCtxInfo);
      pIdlCtxInfo = NULL;
    }
    if (CL_OK != rc)
    {
       goto L0;
    }
    
    rc = clXdrMarshallClNameT(&(pStreamName), 0, 1);
    if (CL_OK != rc)
    {
        goto L1;
    }

    rc = clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
    if (CL_OK != rc)
    {
        goto L2;
    }

    rc = clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);
    if (CL_OK != rc)
    {
        goto L3;
    }

    rc = clXdrMarshallClUint8T(&(filterFlags), 0, 1);
    if (CL_OK != rc)
    {
        goto L4;
    }

    rc = clXdrMarshallClLogFilterT_4_0_0(&(pFilter), 0, 1);
    if (CL_OK != rc)
    {
        goto L5;
    }

    if(pIdlCtxInfo != NULL)
    {
      clHeapFree(pIdlCtxInfo);
      return rc;
    }
    
L5:    return rc;

LL4:  clXdrMarshallClLogFilterT_4_0_0(&(pFilter), 0, 1);
LL3:  clXdrMarshallClUint8T(&(filterFlags), 0, 1);
LL2:  clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);
LL1:  clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
LL0:  clXdrMarshallClNameT(&(pStreamName), 0, 1);

    return rc;

L0:  clXdrMarshallClNameT(&(pStreamName), 0, 1);
L1:  clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
L2:  clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);
L3:  clXdrMarshallClUint8T(&(filterFlags), 0, 1);
L4:  clXdrMarshallClLogFilterT_4_0_0(&(pFilter), 0, 1);


    return rc;
}

ClRcT clLogStreamOwnerFilterSetResponseSend_4_0_0(ClIdlHandleT idlHdl,ClRcT retCode)
{
    ClIdlSyncInfoT    *pIdlSyncDeferInfo = NULL;
    ClRcT              rc                = CL_OK;
    ClBufferHandleT outMsgHdl     = 0;
    
    rc = clHandleCheckout(LogidlDatabaseHdl,idlHdl,(void **)&pIdlSyncDeferInfo);
    if( rc != CL_OK)
    {
      goto Label0; 
    }
    outMsgHdl = pIdlSyncDeferInfo->idlRmdDeferMsg;
    
    rc = clIdlSyncResponseSend(pIdlSyncDeferInfo->idlRmdDeferHdl,outMsgHdl,
                                retCode);
    

    

    clHandleCheckin(LogidlDatabaseHdl, idlHdl);
    clHandleDestroy(LogidlDatabaseHdl, idlHdl);
Label0:
    return rc;
}

ClRcT clLogStreamOwnerHandlerRegisterServer_4_0_0(ClEoDataT eoData, ClBufferHandleT inMsgHdl, ClBufferHandleT outMsgHdl)
{
    ClIdlContextInfoT *pIdlCtxInfo = NULL;
    ClRcT rc = CL_OK;
    ClNameT  pStreamName;
    ClUint32T  pStreamScope;
    ClNameT  pStreamScopeNode;
    ClUint8T  handlerFlags;
    ClUint32T  localAddr;
    ClUint32T  compId;

    memset(&(pStreamName), 0, sizeof(ClNameT));
    memset(&(pStreamScope), 0, sizeof(ClUint32T));
    memset(&(pStreamScopeNode), 0, sizeof(ClNameT));
    memset(&(handlerFlags), 0, sizeof(ClUint8T));
    memset(&(localAddr), 0, sizeof(ClUint32T));
    memset(&(compId), 0, sizeof(ClUint32T));


    rc = clXdrUnmarshallClNameT( inMsgHdl,&(pStreamName));
    if (CL_OK != rc)
    {
        goto LL0;
    }

    rc = clXdrUnmarshallClUint32T( inMsgHdl,&(pStreamScope));
    if (CL_OK != rc)
    {
        goto LL1;
    }

    rc = clXdrUnmarshallClNameT( inMsgHdl,&(pStreamScopeNode));
    if (CL_OK != rc)
    {
        goto LL2;
    }

    rc = clXdrUnmarshallClUint8T( inMsgHdl,&(handlerFlags));
    if (CL_OK != rc)
    {
        goto LL3;
    }

    rc = clXdrUnmarshallClUint32T( inMsgHdl,&(localAddr));
    if (CL_OK != rc)
    {
        goto LL4;
    }

    rc = clXdrUnmarshallClUint32T( inMsgHdl,&(compId));
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
    rc = clIdlSyncPrivateInfoSet(LogidlSyncKey, (void *)pIdlCtxInfo);
    if (CL_OK != rc)
    {
        clHeapFree(pIdlCtxInfo);
        goto L0;
    }
    rc = clLogStreamOwnerHandlerRegister_4_0_0(&(pStreamName), pStreamScope, &(pStreamScopeNode), handlerFlags, localAddr, compId);
    if(pIdlCtxInfo->inProgress == CL_FALSE)
    {
      clHeapFree(pIdlCtxInfo);
      pIdlCtxInfo = NULL;
    }
    if (CL_OK != rc)
    {
       goto L0;
    }
    
    rc = clXdrMarshallClNameT(&(pStreamName), 0, 1);
    if (CL_OK != rc)
    {
        goto L1;
    }

    rc = clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
    if (CL_OK != rc)
    {
        goto L2;
    }

    rc = clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);
    if (CL_OK != rc)
    {
        goto L3;
    }

    rc = clXdrMarshallClUint8T(&(handlerFlags), 0, 1);
    if (CL_OK != rc)
    {
        goto L4;
    }

    rc = clXdrMarshallClUint32T(&(localAddr), 0, 1);
    if (CL_OK != rc)
    {
        goto L5;
    }

    rc = clXdrMarshallClUint32T(&(compId), 0, 1);
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

LL5:  clXdrMarshallClUint32T(&(compId), 0, 1);
LL4:  clXdrMarshallClUint32T(&(localAddr), 0, 1);
LL3:  clXdrMarshallClUint8T(&(handlerFlags), 0, 1);
LL2:  clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);
LL1:  clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
LL0:  clXdrMarshallClNameT(&(pStreamName), 0, 1);

    return rc;

L0:  clXdrMarshallClNameT(&(pStreamName), 0, 1);
L1:  clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
L2:  clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);
L3:  clXdrMarshallClUint8T(&(handlerFlags), 0, 1);
L4:  clXdrMarshallClUint32T(&(localAddr), 0, 1);
L5:  clXdrMarshallClUint32T(&(compId), 0, 1);


    return rc;
}

ClRcT clLogStreamOwnerHandlerRegisterResponseSend_4_0_0(ClIdlHandleT idlHdl,ClRcT retCode)
{
    ClIdlSyncInfoT    *pIdlSyncDeferInfo = NULL;
    ClRcT              rc                = CL_OK;
    ClBufferHandleT outMsgHdl     = 0;
    
    rc = clHandleCheckout(LogidlDatabaseHdl,idlHdl,(void **)&pIdlSyncDeferInfo);
    if( rc != CL_OK)
    {
      goto Label0; 
    }
    outMsgHdl = pIdlSyncDeferInfo->idlRmdDeferMsg;
    
    rc = clIdlSyncResponseSend(pIdlSyncDeferInfo->idlRmdDeferHdl,outMsgHdl,
                                retCode);
    

    

    clHandleCheckin(LogidlDatabaseHdl, idlHdl);
    clHandleDestroy(LogidlDatabaseHdl, idlHdl);
Label0:
    return rc;
}

ClRcT clLogStreamOwnerStreamMcastGetServer_4_0_0(ClEoDataT eoData, ClBufferHandleT inMsgHdl, ClBufferHandleT outMsgHdl)
{
    ClIdlContextInfoT *pIdlCtxInfo = NULL;
    ClRcT rc = CL_OK;
    ClNameT  pStreamName;
    ClUint32T  pStreamScope;
    ClNameT  pStreamScopeNode;
    ClUint64T  mcastAddr;

    memset(&(pStreamName), 0, sizeof(ClNameT));
    memset(&(pStreamScope), 0, sizeof(ClUint32T));
    memset(&(pStreamScopeNode), 0, sizeof(ClNameT));
    memset(&(mcastAddr), 0, sizeof(ClUint64T));


    rc = clXdrUnmarshallClNameT( inMsgHdl,&(pStreamName));
    if (CL_OK != rc)
    {
        goto LL0;
    }

    rc = clXdrUnmarshallClUint32T( inMsgHdl,&(pStreamScope));
    if (CL_OK != rc)
    {
        goto LL1;
    }

    rc = clXdrUnmarshallClNameT( inMsgHdl,&(pStreamScopeNode));
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
    rc = clIdlSyncPrivateInfoSet(LogidlSyncKey, (void *)pIdlCtxInfo);
    if (CL_OK != rc)
    {
        clHeapFree(pIdlCtxInfo);
        goto L0;
    }
    rc = clLogStreamOwnerStreamMcastGet_4_0_0(&(pStreamName), pStreamScope, &(pStreamScopeNode), &(mcastAddr));
    if(pIdlCtxInfo->inProgress == CL_FALSE)
    {
      clHeapFree(pIdlCtxInfo);
      pIdlCtxInfo = NULL;
    }
    if (CL_OK != rc)
    {
       goto L0;
    }
    
    rc = clXdrMarshallClNameT(&(pStreamName), 0, 1);
    if (CL_OK != rc)
    {
        goto L1;
    }

    rc = clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
    if (CL_OK != rc)
    {
        goto L2;
    }

    rc = clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);
    if (CL_OK != rc)
    {
        goto L3;
    }

    if(pIdlCtxInfo != NULL)
    {
      clHeapFree(pIdlCtxInfo);
      return rc;
    }
    
    rc = clXdrMarshallClUint64T(&(mcastAddr), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L4;
    }

L4:    return rc;

LL2:  clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);
LL1:  clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
LL0:  clXdrMarshallClNameT(&(pStreamName), 0, 1);

    return rc;

L0:  clXdrMarshallClNameT(&(pStreamName), 0, 1);
L1:  clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
L2:  clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);

L3:  clXdrMarshallClUint64T(&(mcastAddr), 0, 1);

    return rc;
}

ClRcT clLogStreamOwnerStreamMcastGetResponseSend_4_0_0(ClIdlHandleT idlHdl,ClRcT retCode,CL_OUT  ClUint64T  mcastAddr)
{
    ClIdlSyncInfoT    *pIdlSyncDeferInfo = NULL;
    ClRcT              rc                = CL_OK;
    ClBufferHandleT outMsgHdl     = 0;
    
    rc = clHandleCheckout(LogidlDatabaseHdl,idlHdl,(void **)&pIdlSyncDeferInfo);
    if( rc != CL_OK)
    {
      goto Label0; 
    }
    outMsgHdl = pIdlSyncDeferInfo->idlRmdDeferMsg;
    
    rc = clXdrMarshallClUint64T(&(mcastAddr), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L4;
    }

    rc = clIdlSyncResponseSend(pIdlSyncDeferInfo->idlRmdDeferHdl,outMsgHdl,
                                retCode);
    goto Label1; 
L4:  clXdrMarshallClUint64T(&(mcastAddr), 0, 1);

    clHandleCheckin(LogidlDatabaseHdl, idlHdl);
    clHandleDestroy(LogidlDatabaseHdl, idlHdl);
    return rc;
Label1:
    clHandleCheckin(LogidlDatabaseHdl, idlHdl);
    clHandleDestroy(LogidlDatabaseHdl, idlHdl);
Label0:
    return rc;
}

ClRcT clLogStreamOwnerHandlerDeregisterServer_4_0_0(ClEoDataT eoData, ClBufferHandleT inMsgHdl, ClBufferHandleT outMsgHdl)
{
    ClIdlContextInfoT *pIdlCtxInfo = NULL;
    ClRcT rc = CL_OK;
    ClNameT  pStreamName;
    ClUint32T  pStreamScope;
    ClNameT  pStreamScopeNode;
    ClUint8T  handlerFlags;
    ClUint32T  localAddr;
    ClUint32T  compId;

    memset(&(pStreamName), 0, sizeof(ClNameT));
    memset(&(pStreamScope), 0, sizeof(ClUint32T));
    memset(&(pStreamScopeNode), 0, sizeof(ClNameT));
    memset(&(handlerFlags), 0, sizeof(ClUint8T));
    memset(&(localAddr), 0, sizeof(ClUint32T));
    memset(&(compId), 0, sizeof(ClUint32T));


    rc = clXdrUnmarshallClNameT( inMsgHdl,&(pStreamName));
    if (CL_OK != rc)
    {
        goto LL0;
    }

    rc = clXdrUnmarshallClUint32T( inMsgHdl,&(pStreamScope));
    if (CL_OK != rc)
    {
        goto LL1;
    }

    rc = clXdrUnmarshallClNameT( inMsgHdl,&(pStreamScopeNode));
    if (CL_OK != rc)
    {
        goto LL2;
    }

    rc = clXdrUnmarshallClUint8T( inMsgHdl,&(handlerFlags));
    if (CL_OK != rc)
    {
        goto LL3;
    }

    rc = clXdrUnmarshallClUint32T( inMsgHdl,&(localAddr));
    if (CL_OK != rc)
    {
        goto LL4;
    }

    rc = clXdrUnmarshallClUint32T( inMsgHdl,&(compId));
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
    rc = clIdlSyncPrivateInfoSet(LogidlSyncKey, (void *)pIdlCtxInfo);
    if (CL_OK != rc)
    {
        clHeapFree(pIdlCtxInfo);
        goto L0;
    }
    rc = clLogStreamOwnerHandlerDeregister_4_0_0(&(pStreamName), pStreamScope, &(pStreamScopeNode), handlerFlags, localAddr, compId);
    if(pIdlCtxInfo->inProgress == CL_FALSE)
    {
      clHeapFree(pIdlCtxInfo);
      pIdlCtxInfo = NULL;
    }
    if (CL_OK != rc)
    {
       goto L0;
    }
    
    rc = clXdrMarshallClNameT(&(pStreamName), 0, 1);
    if (CL_OK != rc)
    {
        goto L1;
    }

    rc = clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
    if (CL_OK != rc)
    {
        goto L2;
    }

    rc = clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);
    if (CL_OK != rc)
    {
        goto L3;
    }

    rc = clXdrMarshallClUint8T(&(handlerFlags), 0, 1);
    if (CL_OK != rc)
    {
        goto L4;
    }

    rc = clXdrMarshallClUint32T(&(localAddr), 0, 1);
    if (CL_OK != rc)
    {
        goto L5;
    }

    rc = clXdrMarshallClUint32T(&(compId), 0, 1);
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

LL5:  clXdrMarshallClUint32T(&(compId), 0, 1);
LL4:  clXdrMarshallClUint32T(&(localAddr), 0, 1);
LL3:  clXdrMarshallClUint8T(&(handlerFlags), 0, 1);
LL2:  clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);
LL1:  clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
LL0:  clXdrMarshallClNameT(&(pStreamName), 0, 1);

    return rc;

L0:  clXdrMarshallClNameT(&(pStreamName), 0, 1);
L1:  clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
L2:  clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);
L3:  clXdrMarshallClUint8T(&(handlerFlags), 0, 1);
L4:  clXdrMarshallClUint32T(&(localAddr), 0, 1);
L5:  clXdrMarshallClUint32T(&(compId), 0, 1);


    return rc;
}

ClRcT clLogStreamOwnerHandlerDeregisterResponseSend_4_0_0(ClIdlHandleT idlHdl,ClRcT retCode)
{
    ClIdlSyncInfoT    *pIdlSyncDeferInfo = NULL;
    ClRcT              rc                = CL_OK;
    ClBufferHandleT outMsgHdl     = 0;
    
    rc = clHandleCheckout(LogidlDatabaseHdl,idlHdl,(void **)&pIdlSyncDeferInfo);
    if( rc != CL_OK)
    {
      goto Label0; 
    }
    outMsgHdl = pIdlSyncDeferInfo->idlRmdDeferMsg;
    
    rc = clIdlSyncResponseSend(pIdlSyncDeferInfo->idlRmdDeferHdl,outMsgHdl,
                                retCode);
    

    

    clHandleCheckin(LogidlDatabaseHdl, idlHdl);
    clHandleDestroy(LogidlDatabaseHdl, idlHdl);
Label0:
    return rc;
}

ClRcT clLogStreamOwnerFilterGetServer_4_0_0(ClEoDataT eoData, ClBufferHandleT inMsgHdl, ClBufferHandleT outMsgHdl)
{
    ClIdlContextInfoT *pIdlCtxInfo = NULL;
    ClRcT rc = CL_OK;
    ClNameT  pStreamName;
    ClUint32T  pStreamScope;
    ClNameT  pStreamScopeNode;
    ClLogFilterT_4_0_0  pFilter;

    memset(&(pStreamName), 0, sizeof(ClNameT));
    memset(&(pStreamScope), 0, sizeof(ClUint32T));
    memset(&(pStreamScopeNode), 0, sizeof(ClNameT));
    memset(&(pFilter), 0, sizeof(ClLogFilterT_4_0_0));


    rc = clXdrUnmarshallClNameT( inMsgHdl,&(pStreamName));
    if (CL_OK != rc)
    {
        goto LL0;
    }

    rc = clXdrUnmarshallClUint32T( inMsgHdl,&(pStreamScope));
    if (CL_OK != rc)
    {
        goto LL1;
    }

    rc = clXdrUnmarshallClNameT( inMsgHdl,&(pStreamScopeNode));
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
    rc = clIdlSyncPrivateInfoSet(LogidlSyncKey, (void *)pIdlCtxInfo);
    if (CL_OK != rc)
    {
        clHeapFree(pIdlCtxInfo);
        goto L0;
    }
    rc = clLogStreamOwnerFilterGet_4_0_0(&(pStreamName), pStreamScope, &(pStreamScopeNode), &(pFilter));
    if(pIdlCtxInfo->inProgress == CL_FALSE)
    {
      clHeapFree(pIdlCtxInfo);
      pIdlCtxInfo = NULL;
    }
    if (CL_OK != rc)
    {
       goto L0;
    }
    
    rc = clXdrMarshallClNameT(&(pStreamName), 0, 1);
    if (CL_OK != rc)
    {
        goto L1;
    }

    rc = clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
    if (CL_OK != rc)
    {
        goto L2;
    }

    rc = clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);
    if (CL_OK != rc)
    {
        goto L3;
    }

    if(pIdlCtxInfo != NULL)
    {
      clHeapFree(pIdlCtxInfo);
      return rc;
    }
    
    rc = clXdrMarshallClLogFilterT_4_0_0(&(pFilter), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L4;
    }

L4:    return rc;

LL2:  clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);
LL1:  clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
LL0:  clXdrMarshallClNameT(&(pStreamName), 0, 1);

    return rc;

L0:  clXdrMarshallClNameT(&(pStreamName), 0, 1);
L1:  clXdrMarshallClUint32T(&(pStreamScope), 0, 1);
L2:  clXdrMarshallClNameT(&(pStreamScopeNode), 0, 1);

L3:  clXdrMarshallClLogFilterT_4_0_0(&(pFilter), 0, 1);

    return rc;
}

ClRcT clLogStreamOwnerFilterGetResponseSend_4_0_0(ClIdlHandleT idlHdl,ClRcT retCode,CL_OUT  ClLogFilterT_4_0_0  pFilter)
{
    ClIdlSyncInfoT    *pIdlSyncDeferInfo = NULL;
    ClRcT              rc                = CL_OK;
    ClBufferHandleT outMsgHdl     = 0;
    
    rc = clHandleCheckout(LogidlDatabaseHdl,idlHdl,(void **)&pIdlSyncDeferInfo);
    if( rc != CL_OK)
    {
      goto Label0; 
    }
    outMsgHdl = pIdlSyncDeferInfo->idlRmdDeferMsg;
    
    rc = clXdrMarshallClLogFilterT_4_0_0(&(pFilter), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L4;
    }

    rc = clIdlSyncResponseSend(pIdlSyncDeferInfo->idlRmdDeferHdl,outMsgHdl,
                                retCode);
    goto Label1; 
L4:  clXdrMarshallClLogFilterT_4_0_0(&(pFilter), 0, 1);

    clHandleCheckin(LogidlDatabaseHdl, idlHdl);
    clHandleDestroy(LogidlDatabaseHdl, idlHdl);
    return rc;
Label1:
    clHandleCheckin(LogidlDatabaseHdl, idlHdl);
    clHandleDestroy(LogidlDatabaseHdl, idlHdl);
Label0:
    return rc;
}

