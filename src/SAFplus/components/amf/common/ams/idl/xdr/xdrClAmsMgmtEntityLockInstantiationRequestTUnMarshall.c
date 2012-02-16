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
* Description : Unmarshall routine for clAmsMgmtEntityLockInstantiationRequestT
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/
#include "xdrClAmsMgmtEntityLockInstantiationRequestT.h"

ClRcT clXdrUnmarshallclAmsMgmtEntityLockInstantiationRequestT_4_0_0(ClBufferHandleT msg , void* pGenVar)
{
    clAmsMgmtEntityLockInstantiationRequestT_4_0_0* pVar = (clAmsMgmtEntityLockInstantiationRequestT_4_0_0*)pGenVar;
    ClRcT     rc     = CL_OK;
    ClUint32T length = 0;

    if ((void*)0 == pVar)
    {
        return CL_XDR_RC(CL_ERR_NULL_POINTER);
    }

    clXdrUnmarshallClUint32T(msg, &length);
    if( 0 == length)
    {
        pGenVar = NULL;
    }
    else
    {

    rc = clXdrUnmarshallClHandleT(msg,&(pVar->handle));
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrUnmarshallClAmsEntityConfigT_4_0_0(msg,&(pVar->entity));
    if (CL_OK != rc)
    {
        return rc;
    }

    }

    return rc;
}


