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
* Description : Marshall routine for ClCpmNodeConfigT
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/

#include "xdrClCpmNodeConfigT.h"

ClRcT clXdrMarshallClCpmNodeConfigT_4_0_0(void* pGenVar, ClBufferHandleT msg, ClUint32T isDelete)
{
    ClCpmNodeConfigT_4_0_0* pVar = (ClCpmNodeConfigT_4_0_0*)pGenVar;
    ClRcT rc         = CL_OK;
    ClUint32T length = 0;    

    if ((void*)0 == pVar)
    {
        clXdrMarshallClUint32T(&length, msg, 0);
    }
    else
    {
        length = 1;
        clXdrMarshallClUint32T(&length, msg, 0);

    rc = clXdrMarshallArrayClCharT(pVar->nodeName, 256,msg,isDelete);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrMarshallClNameT(&(pVar->nodeType),msg,isDelete);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrMarshallClNameT(&(pVar->nodeIdentifier),msg,isDelete);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrMarshallClNameT(&(pVar->nodeMoIdStr),msg,isDelete);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrMarshallArrayClCharT(pVar->cpmType, 256,msg,isDelete);
    if (CL_OK != rc)
    {
        return rc;
    }

    }

    return rc;
}


