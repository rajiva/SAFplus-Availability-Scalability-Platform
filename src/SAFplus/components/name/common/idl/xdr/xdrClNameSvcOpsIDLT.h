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
*               and unmarshall funtions of ClNameSvcOpsIDLT_4_0_0 
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/

#ifndef _XDR_CL_NAME_SVC_OPS_IDLT_H_
#define _XDR_CL_NAME_SVC_OPS_IDLT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "clXdrApi.h"



typedef enum _ClNameSvcOpsIDLT_4_0_0
{
    CL_NS_QUERY_IDL_OBJREF,
    CL_NS_QUERY_IDL_MAPPING,
    CL_NS_QUERY_IDL_ALL_MAPPINGS,
    CL_NS_QUERY_IDL_ATTRIBUTE,
    CL_NS_LIST_IDL_NAMES,
    CL_NS_LIST_IDL_BINDINGS
} ClNameSvcOpsIDLT_4_0_0;


#define      clXdrMarshallClNameSvcOpsIDLT_4_0_0               clXdrMarshallClInt32T

#define      clXdrUnmarshallClNameSvcOpsIDLT_4_0_0             clXdrUnmarshallClInt32T

#define      clXdrMarshallArrayClNameSvcOpsIDLT_4_0_0          clXdrMarshallArrayClInt32T

#define      clXdrUnmarshallArrayClNameSvcOpsIDLT_4_0_0        clXdrUnmarshallArrayClInt32T

#define      clXdrMarshallPointerClNameSvcOpsIDLT_4_0_0        clXdrMarshallPointerClInt32T

#define      clXdrUnmarshallPointerClNameSvcOpsIDLT_4_0_0      clXdrUnmarshallPointerClInt32T

#define      clXdrMarshallPtrClNameSvcOpsIDLT_4_0_0            clXdrMarshallPtrClInt32T

#define      clXdrUnmarshallPtrClNameSvcOpsIDLT_4_0_0          clXdrUnmarshallPtrClInt32T



typedef ClNameSvcOpsIDLT_4_0_0 ClNameSvcOpsIDLT;



#ifdef __cplusplus
}
#endif

#endif /*_XDR_CL_NAME_SVC_OPS_IDLT_H_*/
