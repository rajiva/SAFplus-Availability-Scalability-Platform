
/*********************************************************************
* ModuleName  : idl
*********************************************************************/
/*********************************************************************
* Description : This file contains the declartions for client stub
*               routines
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/
#ifndef _MSG_IDL_CLIENT_CALLS_FROM_SERVER_CLIENT_H_
#define _MSG_IDL_CLIENT_CALLS_FROM_SERVER_CLIENT_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <clXdrApi.h>
#include <clIdlApi.h>
#include "../clientIDDefinitions.h"
#include "xdrSaMsgQueueGroupNotificationBufferT.h"
#include "xdrClMsgQueueCkptDataT.h"
#include "xdrSaMsgQueueOpenFlagsT.h"
#include "xdrSaMsgQueueGroupPolicyT.h"
#include "xdrClMsgSyncActionT.h"
#include "xdrClIocPhysicalAddressT.h"
#include "xdrSaMsgQueueCreationAttributesT.h"



ClRcT clMsgQDatabaseUpdateClientSync_4_0_0(CL_IN ClIdlHandleT handle, CL_IN ClMsgSyncActionT_4_0_0 syncupType, CL_IN ClMsgQueueCkptDataT_4_0_0* queueData, CL_IN ClUint16T updateCkpt);

typedef void (*MsgIdlClMsgQDatabaseUpdateAsyncCallbackT_4_0_0) (CL_IN ClIdlHandleT handle, CL_IN ClMsgSyncActionT_4_0_0  syncupType, CL_IN ClMsgQueueCkptDataT_4_0_0* queueData, CL_IN ClUint16T  updateCkpt, CL_IN ClRcT rc, CL_IN void* pCookie);

typedef MsgIdlClMsgQDatabaseUpdateAsyncCallbackT_4_0_0 MsgIdlClMsgQDatabaseUpdateAsyncCallbackT;

ClRcT clMsgQDatabaseUpdateClientAsync_4_0_0(CL_IN ClIdlHandleT handle, CL_IN ClMsgSyncActionT_4_0_0  syncupType, CL_IN ClMsgQueueCkptDataT_4_0_0* queueData, CL_IN ClUint16T  updateCkpt,CL_IN MsgIdlClMsgQDatabaseUpdateAsyncCallbackT_4_0_0 fpAsyncCallback, CL_IN void *cookie);

ClRcT clMsgGroupDatabaseUpdateClientSync_4_0_0(CL_IN ClIdlHandleT handle, CL_IN ClMsgSyncActionT_4_0_0 syncupType, CL_IN ClNameT* pGroupName, CL_IN SaMsgQueueGroupPolicyT_4_0_0 policy, CL_IN ClIocPhysicalAddressT_4_0_0 qGroupAddress, CL_IN ClUint16T updateCkpt);

typedef void (*MsgIdlClMsgGroupDatabaseUpdateAsyncCallbackT_4_0_0) (CL_IN ClIdlHandleT handle, CL_IN ClMsgSyncActionT_4_0_0  syncupType, CL_IN ClNameT* pGroupName, CL_IN SaMsgQueueGroupPolicyT_4_0_0  policy, CL_IN ClIocPhysicalAddressT_4_0_0  qGroupAddress, CL_IN ClUint16T  updateCkpt, CL_IN ClRcT rc, CL_IN void* pCookie);

typedef MsgIdlClMsgGroupDatabaseUpdateAsyncCallbackT_4_0_0 MsgIdlClMsgGroupDatabaseUpdateAsyncCallbackT;

ClRcT clMsgGroupDatabaseUpdateClientAsync_4_0_0(CL_IN ClIdlHandleT handle, CL_IN ClMsgSyncActionT_4_0_0  syncupType, CL_IN ClNameT* pGroupName, CL_IN SaMsgQueueGroupPolicyT_4_0_0  policy, CL_IN ClIocPhysicalAddressT_4_0_0  qGroupAddress, CL_IN ClUint16T  updateCkpt,CL_IN MsgIdlClMsgGroupDatabaseUpdateAsyncCallbackT_4_0_0 fpAsyncCallback, CL_IN void *cookie);

typedef void (*MsgIdlClMsgGroupMembershipUpdateAsyncCallbackT_4_0_0) (CL_IN ClIdlHandleT handle, CL_IN ClMsgSyncActionT_4_0_0  syncAct, CL_IN ClNameT* pGroupName, CL_IN ClNameT* pQueueName, CL_IN ClUint16T  updateCkpt, CL_IN ClRcT rc, CL_IN void* pCookie);

typedef MsgIdlClMsgGroupMembershipUpdateAsyncCallbackT_4_0_0 MsgIdlClMsgGroupMembershipUpdateAsyncCallbackT;

ClRcT clMsgGroupMembershipUpdateClientAsync_4_0_0(CL_IN ClIdlHandleT handle, CL_IN ClMsgSyncActionT_4_0_0  syncAct, CL_IN ClNameT* pGroupName, CL_IN ClNameT* pQueueName, CL_IN ClUint16T  updateCkpt,CL_IN MsgIdlClMsgGroupMembershipUpdateAsyncCallbackT_4_0_0 fpAsyncCallback, CL_IN void *cookie);

ClRcT clMsgQueueAllocateClientSync_4_0_0(CL_IN ClIdlHandleT handle, CL_IN ClNameT* pQName, CL_IN SaMsgQueueOpenFlagsT_4_0_0 openFlags, CL_IN SaMsgQueueCreationAttributesT_4_0_0* pCreationAttributes, CL_OUT ClHandleT* pQueueHandle);


#ifdef __cplusplus
}
#endif
#endif /*_MSG_IDL_CLIENT_CALLS_FROM_SERVER_CLIENT_H_*/
