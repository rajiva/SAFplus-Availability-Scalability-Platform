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
*               and unmarshall funtions of ClErrorReportT 
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/

#ifndef _XDR_CL_ERROR_REPORT_T_H_
#define _XDR_CL_ERROR_REPORT_T_H_

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
#include "xdrClAmsRecoveryT.h"

struct _ClErrorReportT_4_0_0;

typedef struct _ClErrorReportT_4_0_0 {
    ClNameT    compName;
    ClInt64T    time;
    ClAmsRecoveryT_4_0_0    recommendedRecovery;
    ClUint32T    handle;
    ClUint64T    instantiateCookie;

}ClErrorReportT_4_0_0;


ClRcT  clXdrMarshallClErrorReportT_4_0_0(void *,ClBufferHandleT , ClUint32T);

ClRcT  clXdrUnmarshallClErrorReportT_4_0_0(ClBufferHandleT, void *);

#define clXdrMarshallArrayClErrorReportT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallArray((pointer), sizeof(ClErrorReportT_4_0_0), (multiplicity), clXdrMarshallClErrorReportT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallArrayClErrorReportT_4_0_0(msg,pointer, multiplicity) \
clXdrUnmarshallArray((msg),(pointer), sizeof(ClErrorReportT_4_0_0), (multiplicity), clXdrUnmarshallClErrorReportT_4_0_0)

#define clXdrMarshallPointerClErrorReportT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPointer((pointer), sizeof(ClErrorReportT_4_0_0), (multiplicity), clXdrMarshallClErrorReportT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPointerClErrorReportT_4_0_0(msg,pointer) \
clXdrUnmarshallPointer((msg),(pointer), sizeof(ClErrorReportT_4_0_0), clXdrUnmarshallClErrorReportT_4_0_0)

#define clXdrMarshallPtrClErrorReportT_4_0_0(pointer, multiplicity, msg, isDelete) \
clXdrMarshallPtr((pointer), sizeof(ClErrorReportT_4_0_0), (multiplicity), clXdrMarshallClErrorReportT_4_0_0, (msg), (isDelete))

#define clXdrUnmarshallPtrClErrorReportT_4_0_0(msg,pointer,multiplicity) \
clXdrUnmarshallPtr((msg),(pointer), sizeof(ClErrorReportT_4_0_0),multiplicity, clXdrUnmarshallClErrorReportT_4_0_0)


typedef ClErrorReportT_4_0_0 ClErrorReportT;



#ifdef __cplusplus
}
#endif

#endif /*_XDR_CL_ERROR_REPORT_T_H_*/
