/*********************************************************************
* File: 
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

#ifndef _MSG_CLT_SRV_CLIENT_H_
#define _MSG_CLT_SRV_CLIENT_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <clCommon.h>
#include <clIocApi.h>

ClRcT clMsgCltSrvClientTableRegister(ClIocPortT clientPort);

ClRcT clMsgCltSrvClientTableDeregister(void);

#ifdef __cplusplus
}
#endif
#endif /*_MSG_CLT_SRV_CLIENT_H_*/
