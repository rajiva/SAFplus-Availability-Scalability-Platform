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
/*******************************************************************************
 * ModuleName  : cor
 * File        : clCorDmData.h
 *******************************************************************************/

/*******************************************************************************
 * Description :
 * Defines structures used to stream the DM data.
 *****************************************************************************/

#ifndef _CL_COR_DM_DATA_H_
#define _CL_COR_DM_DATA_H_

#include <clCommon.h>
#include <clCorMetaData.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct 
{
    ClUint32T numEntries;
    ClCorAttrDefT* pAttrDef;
    ClUint32T flags;
} VDECL_VER(ClCorAttrDefIDLT, 4, 1, 0);
 
#ifdef __cplusplus
}
#endif
#endif
