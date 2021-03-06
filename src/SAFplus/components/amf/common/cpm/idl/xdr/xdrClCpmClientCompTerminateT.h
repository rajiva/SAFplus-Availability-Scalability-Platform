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
*               and unmarshall funtions of ClCpmClientCompTerminateT 
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/

#ifndef _XDR_CL_CPM_CLIENT_COMP_TERMINATE_T_H_
#define _XDR_CL_CPM_CLIENT_COMP_TERMINATE_T_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "clXdrApi.h"

#include "clCpmApi.h"
#include "clCpmIpi.h"
#include "clIocApi.h"
#include "clCpmExtApi.h"
#include "clEoConfigApi.h"
#include "clAmsTypes.h"
#include "xdrClCpmCompRequestTypeT.h"

struct _ClCpmClientCompTerminateT_4_0_0;

typedef struct _ClCpmClientCompTerminateT_4_0_0 {
    ClUint64T    invocation;
    ClNameT    compName;
    ClCpmCompRequestTypeT_4_0_0    requestType;

}ClCpmClientCompTerminateT_4_0_0;


ClRcT  clXdrMarshallClCpmClientCompTerminateT_4_0_0(void *,ClBufferHandleT , ClUint32T);

ClRcT  clXdrUnmarshallClCpmClientCompTerminateT_4_0_0(ClBufferHandleT, void *);

#define clXdrMarshallArrayClCpmClientCompTerminateT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallArray((pointer), sizeof(ClCpmClientCompTerminateT_4_0_0), (multiplicity), clXdrMarshallClCpmClientCompTerminateT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallArrayClCpmClientCompTerminateT_4_0_0(msg,pointer, multiplicity) \
clXdrUnmarshallArray((msg),(pointer), sizeof(ClCpmClientCompTerminateT_4_0_0), (multiplicity), clXdrUnmarshallClCpmClientCompTerminateT_4_0_0)

#define clXdrMarshallPointerClCpmClientCompTerminateT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPointer((pointer), sizeof(ClCpmClientCompTerminateT_4_0_0), (multiplicity), clXdrMarshallClCpmClientCompTerminateT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPointerClCpmClientCompTerminateT_4_0_0(msg,pointer) \
clXdrUnmarshallPointer((msg),(pointer), sizeof(ClCpmClientCompTerminateT_4_0_0), clXdrUnmarshallClCpmClientCompTerminateT_4_0_0)

#define clXdrMarshallPtrClCpmClientCompTerminateT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPtr((pointer), sizeof(ClCpmClientCompTerminateT_4_0_0), (multiplicity), clXdrMarshallClCpmClientCompTerminateT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPtrClCpmClientCompTerminateT_4_0_0(msg,pointer,multiplicity) \
clXdrUnmarshallPtr((msg),(pointer), sizeof(ClCpmClientCompTerminateT_4_0_0),multiplicity, clXdrUnmarshallClCpmClientCompTerminateT_4_0_0)


typedef ClCpmClientCompTerminateT_4_0_0 ClCpmClientCompTerminateT;



#ifdef __cplusplus
}
#endif

#endif /*_XDR_CL_CPM_CLIENT_COMP_TERMINATE_T_H_*/
