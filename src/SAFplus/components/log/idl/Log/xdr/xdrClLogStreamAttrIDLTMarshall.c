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
* Description : Marshall routine for ClLogStreamAttrIDLT
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/

#include "xdrClLogStreamAttrIDLT.h"

ClRcT clXdrMarshallClLogStreamAttrIDLT_4_0_0(void* pGenVar, ClBufferHandleT msg, ClUint32T isDelete)
{
    ClLogStreamAttrIDLT_4_0_0* pVar = (ClLogStreamAttrIDLT_4_0_0*)pGenVar;
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

    rc = clXdrMarshallClStringT(&(pVar->fileName),msg,isDelete);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrMarshallClStringT(&(pVar->fileLocation),msg,isDelete);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrMarshallClUint32T(&(pVar->fileUnitSize),msg,isDelete);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrMarshallClUint32T(&(pVar->recordSize),msg,isDelete);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrMarshallClUint16T(&(pVar->haProperty),msg,isDelete);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrMarshallClLogFileFullActionT_4_0_0(&(pVar->fileFullAction),msg,isDelete);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrMarshallClUint32T(&(pVar->maxFilesRotated),msg,isDelete);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrMarshallClUint32T(&(pVar->flushFreq),msg,isDelete);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrMarshallClInt64T(&(pVar->flushInterval),msg,isDelete);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrMarshallClWaterMarkT_4_0_0(&(pVar->waterMark),msg,isDelete);
    if (CL_OK != rc)
    {
        return rc;
    }

    rc = clXdrMarshallClUint16T(&(pVar->syslog),msg,isDelete);
    if (CL_OK != rc)
    {
        return rc;
    }

    }

    return rc;
}


