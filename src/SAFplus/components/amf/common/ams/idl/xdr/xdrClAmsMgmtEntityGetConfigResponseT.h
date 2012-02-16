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
*               and unmarshall funtions of clAmsMgmtEntityGetConfigResponseT 
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/

#ifndef _XDR_CL_AMS_MGMT_ENTITY_GET_CONFIG_RESPONSE_T_H_
#define _XDR_CL_AMS_MGMT_ENTITY_GET_CONFIG_RESPONSE_T_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "clXdrApi.h"

#include "clAmsEntities.h"
#include "clAmsMgmtCommon.h"
#include "clMetricApi.h"
#include "clIocApi.h"
#include "clAmsNotifications.h"
#include "clAmsMgmtServerApi.h"
#include "xdrClAmsEntityConfigT.h"

struct _clAmsMgmtEntityGetConfigResponseT_4_0_0;


ClRcT  clXdrMarshallclAmsMgmtEntityGetConfigResponseT_4_0_0(void *,ClBufferHandleT , ClUint32T);

ClRcT  clXdrUnmarshallclAmsMgmtEntityGetConfigResponseT_4_0_0(ClBufferHandleT, void *);

#define clXdrMarshallArrayclAmsMgmtEntityGetConfigResponseT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallArray((pointer), sizeof(clAmsMgmtEntityGetConfigResponseT_4_0_0), (multiplicity), clXdrMarshallclAmsMgmtEntityGetConfigResponseT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallArrayclAmsMgmtEntityGetConfigResponseT_4_0_0(msg,pointer, multiplicity) \
clXdrUnmarshallArray((msg),(pointer), sizeof(clAmsMgmtEntityGetConfigResponseT_4_0_0), (multiplicity), clXdrUnmarshallclAmsMgmtEntityGetConfigResponseT_4_0_0)

#define clXdrMarshallPointerclAmsMgmtEntityGetConfigResponseT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPointer((pointer), sizeof(clAmsMgmtEntityGetConfigResponseT_4_0_0), (multiplicity), clXdrMarshallclAmsMgmtEntityGetConfigResponseT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPointerclAmsMgmtEntityGetConfigResponseT_4_0_0(msg,pointer) \
clXdrUnmarshallPointer((msg),(pointer), sizeof(clAmsMgmtEntityGetConfigResponseT_4_0_0), clXdrUnmarshallclAmsMgmtEntityGetConfigResponseT_4_0_0)

#define clXdrMarshallPtrclAmsMgmtEntityGetConfigResponseT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPtr((pointer), sizeof(clAmsMgmtEntityGetConfigResponseT_4_0_0), (multiplicity), clXdrMarshallclAmsMgmtEntityGetConfigResponseT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPtrclAmsMgmtEntityGetConfigResponseT_4_0_0(msg,pointer,multiplicity) \
clXdrUnmarshallPtr((msg),(pointer), sizeof(clAmsMgmtEntityGetConfigResponseT_4_0_0),multiplicity, clXdrUnmarshallclAmsMgmtEntityGetConfigResponseT_4_0_0)


typedef clAmsMgmtEntityGetConfigResponseT clAmsMgmtEntityGetConfigResponseT_4_0_0;



#ifdef __cplusplus
}
#endif

#endif /*_XDR_CL_AMS_MGMT_ENTITY_GET_CONFIG_RESPONSE_T_H_*/
