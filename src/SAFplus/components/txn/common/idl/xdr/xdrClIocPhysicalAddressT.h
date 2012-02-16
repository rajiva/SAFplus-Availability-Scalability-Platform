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
*               and unmarshall funtions of ClIocPhysicalAddressT 
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/

#ifndef _XDR_CL_IOC_PHYSICAL_ADDRESS_T_H_
#define _XDR_CL_IOC_PHYSICAL_ADDRESS_T_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "clXdrApi.h"

#include "clTxnCommonDefn.h"
#include "clIocApi.h"

struct _ClIocPhysicalAddressT_4_0_0;


ClRcT  clXdrMarshallClIocPhysicalAddressT_4_0_0(void *,ClBufferHandleT , ClUint32T);

ClRcT  clXdrUnmarshallClIocPhysicalAddressT_4_0_0(ClBufferHandleT, void *);

#define clXdrMarshallArrayClIocPhysicalAddressT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallArray((pointer), sizeof(ClIocPhysicalAddressT_4_0_0), (multiplicity), clXdrMarshallClIocPhysicalAddressT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallArrayClIocPhysicalAddressT_4_0_0(msg,pointer, multiplicity) \
clXdrUnmarshallArray((msg),(pointer), sizeof(ClIocPhysicalAddressT_4_0_0), (multiplicity), clXdrUnmarshallClIocPhysicalAddressT_4_0_0)

#define clXdrMarshallPointerClIocPhysicalAddressT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPointer((pointer), sizeof(ClIocPhysicalAddressT_4_0_0), (multiplicity), clXdrMarshallClIocPhysicalAddressT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPointerClIocPhysicalAddressT_4_0_0(msg,pointer) \
clXdrUnmarshallPointer((msg),(pointer), sizeof(ClIocPhysicalAddressT_4_0_0), clXdrUnmarshallClIocPhysicalAddressT_4_0_0)

#define clXdrMarshallPtrClIocPhysicalAddressT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPtr((pointer), sizeof(ClIocPhysicalAddressT_4_0_0), (multiplicity), clXdrMarshallClIocPhysicalAddressT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPtrClIocPhysicalAddressT_4_0_0(msg,pointer,multiplicity) \
clXdrUnmarshallPtr((msg),(pointer), sizeof(ClIocPhysicalAddressT_4_0_0),multiplicity, clXdrUnmarshallClIocPhysicalAddressT_4_0_0)


typedef ClIocPhysicalAddressT ClIocPhysicalAddressT_4_0_0;



#ifdef __cplusplus
}
#endif

#endif /*_XDR_CL_IOC_PHYSICAL_ADDRESS_T_H_*/
