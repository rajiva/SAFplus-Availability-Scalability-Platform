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
*               and unmarshall funtions of clAmsMgmtCCBSetSISIDependencyResponseT 
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/

#ifndef _XDR_CL_AMS_MGMT_CCB_SET_SISI_DEPENDENCY_RESPONSE_T_H_
#define _XDR_CL_AMS_MGMT_CCB_SET_SISI_DEPENDENCY_RESPONSE_T_H_

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

struct _clAmsMgmtCCBSetSISIDependencyResponseT_4_0_0;


ClRcT  clXdrMarshallclAmsMgmtCCBSetSISIDependencyResponseT_4_0_0(void *,ClBufferHandleT , ClUint32T);

ClRcT  clXdrUnmarshallclAmsMgmtCCBSetSISIDependencyResponseT_4_0_0(ClBufferHandleT, void *);

#define clXdrMarshallArrayclAmsMgmtCCBSetSISIDependencyResponseT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallArray((pointer), sizeof(clAmsMgmtCCBSetSISIDependencyResponseT_4_0_0), (multiplicity), clXdrMarshallclAmsMgmtCCBSetSISIDependencyResponseT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallArrayclAmsMgmtCCBSetSISIDependencyResponseT_4_0_0(msg,pointer, multiplicity) \
clXdrUnmarshallArray((msg),(pointer), sizeof(clAmsMgmtCCBSetSISIDependencyResponseT_4_0_0), (multiplicity), clXdrUnmarshallclAmsMgmtCCBSetSISIDependencyResponseT_4_0_0)

#define clXdrMarshallPointerclAmsMgmtCCBSetSISIDependencyResponseT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPointer((pointer), sizeof(clAmsMgmtCCBSetSISIDependencyResponseT_4_0_0), (multiplicity), clXdrMarshallclAmsMgmtCCBSetSISIDependencyResponseT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPointerclAmsMgmtCCBSetSISIDependencyResponseT_4_0_0(msg,pointer) \
clXdrUnmarshallPointer((msg),(pointer), sizeof(clAmsMgmtCCBSetSISIDependencyResponseT_4_0_0), clXdrUnmarshallclAmsMgmtCCBSetSISIDependencyResponseT_4_0_0)

#define clXdrMarshallPtrclAmsMgmtCCBSetSISIDependencyResponseT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPtr((pointer), sizeof(clAmsMgmtCCBSetSISIDependencyResponseT_4_0_0), (multiplicity), clXdrMarshallclAmsMgmtCCBSetSISIDependencyResponseT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPtrclAmsMgmtCCBSetSISIDependencyResponseT_4_0_0(msg,pointer,multiplicity) \
clXdrUnmarshallPtr((msg),(pointer), sizeof(clAmsMgmtCCBSetSISIDependencyResponseT_4_0_0),multiplicity, clXdrUnmarshallclAmsMgmtCCBSetSISIDependencyResponseT_4_0_0)


typedef clAmsMgmtCCBSetSISIDependencyResponseT clAmsMgmtCCBSetSISIDependencyResponseT_4_0_0;



#ifdef __cplusplus
}
#endif

#endif /*_XDR_CL_AMS_MGMT_CCB_SET_SISI_DEPENDENCY_RESPONSE_T_H_*/
