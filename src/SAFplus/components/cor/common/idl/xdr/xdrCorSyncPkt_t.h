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


/*********************************************************************
* ModuleName  : idl
*********************************************************************/
/*********************************************************************
* Description : This file contains the declarations for marshall 
*               and unmarshall funtions of corSyncPkt_t 
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/

#ifndef _XDR_COR_SYNC_PKT_T_H_
#define _XDR_COR_SYNC_PKT_T_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "clXdrApi.h"

#include "clCorTxnJobStream.h"
#include "clTimerApi.h"
#include "clCorNotifyApi.h"
#include "clCorClient.h"
#include "clIocApi.h"
#include "clCorDmData.h"
#include "clCorMetaData.h"
#include "clCorSync.h"
#include "xdrCorSyncEvts_e.h"

struct _corSyncPkt_t_4_0_0;


ClRcT  clXdrMarshallcorSyncPkt_t_4_0_0(void *,ClBufferHandleT , ClUint32T);

ClRcT  clXdrUnmarshallcorSyncPkt_t_4_0_0(ClBufferHandleT, void *);

#define clXdrMarshallArraycorSyncPkt_t_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallArray((pointer), sizeof(corSyncPkt_t_4_0_0), (multiplicity), clXdrMarshallcorSyncPkt_t_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallArraycorSyncPkt_t_4_0_0(msg,pointer, multiplicity) \
clXdrUnmarshallArray((msg),(pointer), sizeof(corSyncPkt_t_4_0_0), (multiplicity), clXdrUnmarshallcorSyncPkt_t_4_0_0)

#define clXdrMarshallPointercorSyncPkt_t_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPointer((pointer), sizeof(corSyncPkt_t_4_0_0), (multiplicity), clXdrMarshallcorSyncPkt_t_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPointercorSyncPkt_t_4_0_0(msg,pointer) \
clXdrUnmarshallPointer((msg),(pointer), sizeof(corSyncPkt_t_4_0_0), clXdrUnmarshallcorSyncPkt_t_4_0_0)

#define clXdrMarshallPtrcorSyncPkt_t_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPtr((pointer), sizeof(corSyncPkt_t_4_0_0), (multiplicity), clXdrMarshallcorSyncPkt_t_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPtrcorSyncPkt_t_4_0_0(msg,pointer,multiplicity) \
clXdrUnmarshallPtr((msg),(pointer), sizeof(corSyncPkt_t_4_0_0),multiplicity, clXdrUnmarshallcorSyncPkt_t_4_0_0)


typedef corSyncPkt_t corSyncPkt_t_4_0_0;



#ifdef __cplusplus
}
#endif

#endif /*_XDR_COR_SYNC_PKT_T_H_*/
