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
*               and unmarshall funtions of ClLogStreamMapT 
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/

#ifndef _XDR_CL_LOG_STREAM_MAP_T_H_
#define _XDR_CL_LOG_STREAM_MAP_T_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "clXdrApi.h"

#include "clIocApi.h"
#include "clLogApi.h"

struct _ClLogStreamMapT_4_0_0;


ClRcT  clXdrMarshallClLogStreamMapT_4_0_0(void *,ClBufferHandleT , ClUint32T);

ClRcT  clXdrUnmarshallClLogStreamMapT_4_0_0(ClBufferHandleT, void *);

#define clXdrMarshallArrayClLogStreamMapT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallArray((pointer), sizeof(ClLogStreamMapT_4_0_0), (multiplicity), clXdrMarshallClLogStreamMapT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallArrayClLogStreamMapT_4_0_0(msg,pointer, multiplicity) \
clXdrUnmarshallArray((msg),(pointer), sizeof(ClLogStreamMapT_4_0_0), (multiplicity), clXdrUnmarshallClLogStreamMapT_4_0_0)

#define clXdrMarshallPointerClLogStreamMapT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPointer((pointer), sizeof(ClLogStreamMapT_4_0_0), (multiplicity), clXdrMarshallClLogStreamMapT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPointerClLogStreamMapT_4_0_0(msg,pointer) \
clXdrUnmarshallPointer((msg),(pointer), sizeof(ClLogStreamMapT_4_0_0), clXdrUnmarshallClLogStreamMapT_4_0_0)

#define clXdrMarshallPtrClLogStreamMapT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPtr((pointer), sizeof(ClLogStreamMapT_4_0_0), (multiplicity), clXdrMarshallClLogStreamMapT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPtrClLogStreamMapT_4_0_0(msg,pointer,multiplicity) \
clXdrUnmarshallPtr((msg),(pointer), sizeof(ClLogStreamMapT_4_0_0),multiplicity, clXdrUnmarshallClLogStreamMapT_4_0_0)


typedef ClLogStreamMapT ClLogStreamMapT_4_0_0;



#ifdef __cplusplus
}
#endif

#endif /*_XDR_CL_LOG_STREAM_MAP_T_H_*/
