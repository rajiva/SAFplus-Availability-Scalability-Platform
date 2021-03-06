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
#include <clDispatchApi.h>
#include <clOsalApi.h>
#include <clQueueApi.h>

#ifndef _CL_DISPATCH_H_
#define _CL_DISPATCH_H_
                                                                                                                             
#ifdef __cplusplus
extern "C"
{
#endif /* endif for __cplusplus */

/* Static function declarations */
/* Function declarations */
static void clDispatchHandleDestructor(void* cbArgs);
static void clDispatchQueueDestroyCallback(
              const ClQueueDataT queueData);
static void clDispatchQueueDequeueCallback(
              const ClQueueDataT queueData);


/* 
 * Structure to hold the data required by this specific instance
 * of dispatch handle.
 */
typedef struct ClDispatchDbEntry {
    ClQueueT                        cbQueue;
    ClFdT                           readFd;
    ClFdT                           writeFd;
    ClOsalMutexIdT                  dispatchMutex;
    ClDispatchCallbackT             svcCallback;
    ClDispatchQueueDestroyCallbackT queueDestroyCallback;
    ClHandleT                       svcInstanceHandle;
    ClBoolT                         shouldDelete;
} ClDispatchDbEntryT;

#define CHECK_LIB_INIT do {                         \
    if (databaseHandle == CL_HANDLE_INVALID_VALUE)  \
    {                                               \
        return CL_ERR_NOT_INITIALIZED;              \
    }                                               \
} while(0)

#ifdef __cplusplus
}
#endif /* endif for __cplusplus */
                                                                                                                             
#endif /* endif for ifndef _CL_DISPATCH_H_ */

