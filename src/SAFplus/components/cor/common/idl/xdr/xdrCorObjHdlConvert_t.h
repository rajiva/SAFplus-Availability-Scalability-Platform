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
*               and unmarshall funtions of corObjHdlConvert_t 
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/

#ifndef _XDR_COR_OBJ_HDL_CONVERT_T_H_
#define _XDR_COR_OBJ_HDL_CONVERT_T_H_

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
#include "xdrClCorServiceIdT.h"
#include "xdrClCorObjTypesT.h"
#include "xdrCorObjectOp_e.h"
#include "xdrClCorMOIdT.h"

struct _corObjHdlConvert_t_4_0_0;


ClRcT  clXdrMarshallcorObjHdlConvert_t_4_0_0(void *,ClBufferHandleT , ClUint32T);

ClRcT  clXdrUnmarshallcorObjHdlConvert_t_4_0_0(ClBufferHandleT, void *);

#define clXdrMarshallArraycorObjHdlConvert_t_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallArray((pointer), sizeof(corObjHdlConvert_t_4_0_0), (multiplicity), clXdrMarshallcorObjHdlConvert_t_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallArraycorObjHdlConvert_t_4_0_0(msg,pointer, multiplicity) \
clXdrUnmarshallArray((msg),(pointer), sizeof(corObjHdlConvert_t_4_0_0), (multiplicity), clXdrUnmarshallcorObjHdlConvert_t_4_0_0)

#define clXdrMarshallPointercorObjHdlConvert_t_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPointer((pointer), sizeof(corObjHdlConvert_t_4_0_0), (multiplicity), clXdrMarshallcorObjHdlConvert_t_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPointercorObjHdlConvert_t_4_0_0(msg,pointer) \
clXdrUnmarshallPointer((msg),(pointer), sizeof(corObjHdlConvert_t_4_0_0), clXdrUnmarshallcorObjHdlConvert_t_4_0_0)

#define clXdrMarshallPtrcorObjHdlConvert_t_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPtr((pointer), sizeof(corObjHdlConvert_t_4_0_0), (multiplicity), clXdrMarshallcorObjHdlConvert_t_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPtrcorObjHdlConvert_t_4_0_0(msg,pointer,multiplicity) \
clXdrUnmarshallPtr((msg),(pointer), sizeof(corObjHdlConvert_t_4_0_0),multiplicity, clXdrUnmarshallcorObjHdlConvert_t_4_0_0)


typedef corObjHdlConvert_t corObjHdlConvert_t_4_0_0;



#ifdef __cplusplus
}
#endif

#endif /*_XDR_COR_OBJ_HDL_CONVERT_T_H_*/
