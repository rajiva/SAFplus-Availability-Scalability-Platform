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
*               and unmarshall funtions of ClNameSvcBindingIDLT 
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/

#ifndef _XDR_CL_NAME_SVC_BINDING_IDLT_H_
#define _XDR_CL_NAME_SVC_BINDING_IDLT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "clXdrApi.h"



struct _ClNameSvcBindingIDLT_4_0_0;

typedef struct _ClNameSvcBindingIDLT_4_0_0 {
    ClUint32T    cksum;
    ClNameT    name;
    ClUint32T    refCount;
    ClUint32T    dsId;
    ClInt32T    hashId;
    ClUint32T    priority;
    ClInt32T    nodeHdl;

}ClNameSvcBindingIDLT_4_0_0;


ClRcT  clXdrMarshallClNameSvcBindingIDLT_4_0_0(void *,ClBufferHandleT , ClUint32T);

ClRcT  clXdrUnmarshallClNameSvcBindingIDLT_4_0_0(ClBufferHandleT, void *);

#define clXdrMarshallArrayClNameSvcBindingIDLT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallArray((pointer), sizeof(ClNameSvcBindingIDLT_4_0_0), (multiplicity), clXdrMarshallClNameSvcBindingIDLT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallArrayClNameSvcBindingIDLT_4_0_0(msg,pointer, multiplicity) \
clXdrUnmarshallArray((msg),(pointer), sizeof(ClNameSvcBindingIDLT_4_0_0), (multiplicity), clXdrUnmarshallClNameSvcBindingIDLT_4_0_0)

#define clXdrMarshallPointerClNameSvcBindingIDLT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPointer((pointer), sizeof(ClNameSvcBindingIDLT_4_0_0), (multiplicity), clXdrMarshallClNameSvcBindingIDLT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPointerClNameSvcBindingIDLT_4_0_0(msg,pointer) \
clXdrUnmarshallPointer((msg),(pointer), sizeof(ClNameSvcBindingIDLT_4_0_0), clXdrUnmarshallClNameSvcBindingIDLT_4_0_0)

#define clXdrMarshallPtrClNameSvcBindingIDLT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPtr((pointer), sizeof(ClNameSvcBindingIDLT_4_0_0), (multiplicity), clXdrMarshallClNameSvcBindingIDLT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPtrClNameSvcBindingIDLT_4_0_0(msg,pointer,multiplicity) \
clXdrUnmarshallPtr((msg),(pointer), sizeof(ClNameSvcBindingIDLT_4_0_0),multiplicity, clXdrUnmarshallClNameSvcBindingIDLT_4_0_0)


typedef ClNameSvcBindingIDLT_4_0_0 ClNameSvcBindingIDLT;



#ifdef __cplusplus
}
#endif

#endif /*_XDR_CL_NAME_SVC_BINDING_IDLT_H_*/
