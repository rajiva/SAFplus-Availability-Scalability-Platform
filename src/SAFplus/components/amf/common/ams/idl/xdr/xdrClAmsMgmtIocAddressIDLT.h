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
*               and unmarshall funtions of ClAmsMgmtIocAddressIDLT 
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/

#ifndef _XDR_CL_AMS_MGMT_IOC_ADDRESS_IDLT_H_
#define _XDR_CL_AMS_MGMT_IOC_ADDRESS_IDLT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "clXdrApi.h"

#include "xdrClIocPhysicalAddressT.h"

struct _ClAmsMgmtIocAddressIDLT_4_0_0;

typedef enum _ClAmsMgmtIocAddressIDLTEnumT_4_0_0
{
    CLAMSMGMTIOCADDRESSIDLTIOCPHYADDRESS = 1,
    CLAMSMGMTIOCADDRESSIDLTIOCLOGICALADDRESS,
    CLAMSMGMTIOCADDRESSIDLTIOCMULTICASTADDRESS,

} ClAmsMgmtIocAddressIDLTEnumT_4_0_0;

typedef struct _ClAmsMgmtIocAddressIDLT_4_0_0
{
    ClAmsMgmtIocAddressIDLTEnumT_4_0_0 discriminant;
    union
    {
        ClIocPhysicalAddressT_4_0_0    iocPhyAddress;
        ClUint64T    iocLogicalAddress;
        ClUint64T    iocMulticastAddress;

    }clAmsMgmtIocAddressIDLT;
}ClAmsMgmtIocAddressIDLT_4_0_0;


ClRcT  clXdrMarshallClAmsMgmtIocAddressIDLT_4_0_0(void *,ClBufferHandleT , ClUint32T);

ClRcT  clXdrUnmarshallClAmsMgmtIocAddressIDLT_4_0_0(ClBufferHandleT, void *);

#define clXdrMarshallArrayClAmsMgmtIocAddressIDLT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallArray((pointer), sizeof(ClAmsMgmtIocAddressIDLT_4_0_0), (multiplicity), clXdrMarshallClAmsMgmtIocAddressIDLT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallArrayClAmsMgmtIocAddressIDLT_4_0_0(msg,pointer, multiplicity) \
clXdrUnmarshallArray((msg),(pointer), sizeof(ClAmsMgmtIocAddressIDLT_4_0_0), (multiplicity), clXdrUnmarshallClAmsMgmtIocAddressIDLT_4_0_0)

#define clXdrMarshallPointerClAmsMgmtIocAddressIDLT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPointer((pointer), sizeof(ClAmsMgmtIocAddressIDLT_4_0_0), (multiplicity), clXdrMarshallClAmsMgmtIocAddressIDLT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPointerClAmsMgmtIocAddressIDLT_4_0_0(msg,pointer) \
clXdrUnmarshallPointer((msg),(pointer), sizeof(ClAmsMgmtIocAddressIDLT_4_0_0), clXdrUnmarshallClAmsMgmtIocAddressIDLT_4_0_0)

#define clXdrMarshallPtrClAmsMgmtIocAddressIDLT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPtr((pointer), sizeof(ClAmsMgmtIocAddressIDLT_4_0_0), (multiplicity), clXdrMarshallClAmsMgmtIocAddressIDLT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPtrClAmsMgmtIocAddressIDLT_4_0_0(msg,pointer,multiplicity) \
clXdrUnmarshallPtr((msg),(pointer), sizeof(ClAmsMgmtIocAddressIDLT_4_0_0),multiplicity, clXdrUnmarshallClAmsMgmtIocAddressIDLT_4_0_0)


typedef ClAmsMgmtIocAddressIDLT_4_0_0 ClAmsMgmtIocAddressIDLT;



#ifdef __cplusplus
}
#endif

#endif /*_XDR_CL_AMS_MGMT_IOC_ADDRESS_IDLT_H_*/
