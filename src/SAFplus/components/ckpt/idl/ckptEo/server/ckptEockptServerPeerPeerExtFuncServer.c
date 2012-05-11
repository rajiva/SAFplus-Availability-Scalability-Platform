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
#include "ckptEockptServerPeerPeerExtFuncServer.h"
#include "ckptEoServer.h"

extern ClUint32T  ckptEoidlSyncKey;
extern ClHandleDatabaseHandleT  ckptEoidlDatabaseHdl;



ClRcT clCkptRemSvrWelcomeServer_5_1_0(ClEoDataT eoData, ClBufferHandleT inMsgHdl, ClBufferHandleT outMsgHdl)
{
    ClIdlContextInfoT *pIdlCtxInfo = NULL;
    ClRcT rc = CL_OK;
    ClVersionT  pVersion;
    ClUint32T  peerAddr;
    ClUint8T  credential;

    memset(&(pVersion), 0, sizeof(ClVersionT));
    memset(&(peerAddr), 0, sizeof(ClUint32T));
    memset(&(credential), 0, sizeof(ClUint8T));


    rc = clXdrUnmarshallClUint32T( inMsgHdl,&(peerAddr));
    if (CL_OK != rc)
    {
        goto LL0;
    }

    rc = clXdrUnmarshallClUint8T( inMsgHdl,&(credential));
    if (CL_OK != rc)
    {
        goto LL1;
    }

    rc = clXdrUnmarshallClVersionT( inMsgHdl,&(pVersion));
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
    rc = clIdlSyncPrivateInfoSet(ckptEoidlSyncKey, (void *)pIdlCtxInfo);
    if (CL_OK != rc)
    {
        clHeapFree(pIdlCtxInfo);
        goto L0;
    }
    rc = clCkptRemSvrWelcome_5_1_0(&(pVersion), peerAddr, credential);
    if(pIdlCtxInfo->inProgress == CL_FALSE)
    {
      clHeapFree(pIdlCtxInfo);
      pIdlCtxInfo = NULL;
    }
    if (CL_OK != rc)
    {
       goto L0;
    }
    
    rc = clXdrMarshallClUint32T(&(peerAddr), 0, 1);
    if (CL_OK != rc)
    {
        goto L1;
    }

    rc = clXdrMarshallClUint8T(&(credential), 0, 1);
    if (CL_OK != rc)
    {
        goto L2;
    }

    if(pIdlCtxInfo != NULL)
    {
      clHeapFree(pIdlCtxInfo);
      return rc;
    }
    
    rc = clXdrMarshallClVersionT(&(pVersion), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L3;
    }

L3:    return rc;

LL2:  clXdrMarshallClVersionT(&(pVersion), 0, 1);
LL1:  clXdrMarshallClUint8T(&(credential), 0, 1);
LL0:  clXdrMarshallClUint32T(&(peerAddr), 0, 1);

    return rc;

L0:  clXdrMarshallClUint32T(&(peerAddr), 0, 1);
L1:  clXdrMarshallClUint8T(&(credential), 0, 1);

L2:  clXdrMarshallClVersionT(&(pVersion), 0, 1);

    return rc;
}

ClRcT clCkptRemSvrWelcomeResponseSend_5_1_0(ClIdlHandleT idlHdl,ClRcT retCode,CL_INOUT  ClVersionT  pVersion)
{
    ClIdlSyncInfoT    *pIdlSyncDeferInfo = NULL;
    ClRcT              rc                = CL_OK;
    ClBufferHandleT outMsgHdl     = 0;
    
    rc = clHandleCheckout(ckptEoidlDatabaseHdl,idlHdl,(void **)&pIdlSyncDeferInfo);
    if( rc != CL_OK)
    {
      goto Label0; 
    }
    outMsgHdl = pIdlSyncDeferInfo->idlRmdDeferMsg;
    
    rc = clXdrMarshallClVersionT(&(pVersion), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L3;
    }

    rc = clIdlSyncResponseSend(pIdlSyncDeferInfo->idlRmdDeferHdl,outMsgHdl,
                                retCode);
    
L3:  clXdrMarshallClVersionT(&(pVersion), 0, 1);

    

    clHandleCheckin(ckptEoidlDatabaseHdl, idlHdl);
    clHandleDestroy(ckptEoidlDatabaseHdl, idlHdl);
Label0:
    return rc;
}

