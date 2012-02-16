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
* Description : Unmarshall routine for ClNameVersionT
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/
#include "xdrClNameVersionT.h"

ClRcT clXdrUnmarshallClNameVersionT_4_0_0(ClBufferHandleT msg , void* pGenVar)
{
    ClNameVersionT_4_0_0* pVar = (ClNameVersionT_4_0_0*)pGenVar;
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

    rc = clXdrUnmarshallClUint8T(msg,&(pVar->releaseCode));
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrUnmarshallClUint8T(msg,&(pVar->majorVersion));
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrUnmarshallClUint8T(msg,&(pVar->minorVersion));
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrUnmarshallClUint8T(msg,&(pVar->reserved));
    if (CL_OK != rc)
    {
        return rc;
    }

    }

    return rc;
}


