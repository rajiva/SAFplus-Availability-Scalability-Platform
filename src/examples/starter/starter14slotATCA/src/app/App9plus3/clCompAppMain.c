/******************************************************************************
 *
 * clCompAppMain.c
 *
 ***************************** Legal Notice ***********************************
 *
 * This file is autogenerated by OpenClovis IDE, Copyright (C) 2002-2008 by 
 * OpenClovis. All rights reserved.
 *
 ***************************** Description ************************************
 *
 * This file provides a skeleton for writing a SAF aware component.
 *
 * Template Version: 1.0
 *
 *****************************************************************************/

/******************************************************************************
 * Include files needed to compile this file
 *****************************************************************************/

/*
 * POSIX Includes.
 */
#include <assert.h>
#include <errno.h>

/*
 * Basic ASP Includes.
 */
#include <clCommon.h>

/*
 * ASP Client Includes.
 */
#include <clLogApi.h>

#include <clEoApi.h>
#include <clCpmApi.h>
#include <saAmf.h>
 
#include "clCompAppMain.h"
#include "../common/netwrapper.h"

/******************************************************************************
 * Optional Features
 *****************************************************************************/

/*
 * This template has a few default clprintfs. These can be disabled by
 * changing clprintf to a null function
 */

#define clprintf(severity, ...)   clAppLog(CL_LOG_HANDLE_APP, severity, 10, \
                                  CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,\
                                  __VA_ARGS__)

/******************************************************************************
 * Global Variables.
 *****************************************************************************/

pid_t mypid;
SaAmfHandleT amfHandle;

ClBoolT unblockNow = CL_FALSE;

/*
 * Declare other global variables here.
 */
VirtualIpAddress gVirtualIp;

/******************************************************************************
 * Application Life Cycle Management Functions
 *****************************************************************************/

/*
 * main
 * -------------------
 * This function is invoked when the application is to be initialized.
 */

int main(int argc, char *argv[])
{
    SaNameT             appName = {0};
    SaAmfCallbacksT     callbacks;
    SaVersionT          version;
    ClIocPortT          iocPort;
    SaAisErrorT         rc = SA_AIS_OK;

    SaSelectionObjectT dispatch_fd;
    fd_set read_fds;
    
    /*
     * Declare other local variables here.
     */

    /*
     * Get the pid for the process and store it in global variable.
     */

    mypid = getpid();

    /*
     * Initialize and register with CPM. 'version' specifies the
     * version of AMF with which this application would like to
     * interface. 'callbacks' is used to register the callbacks this
     * component expects to receive.
     */

    version.releaseCode  = 'B';
    version.majorVersion = 01;
    version.minorVersion = 01;
    
    callbacks.saAmfHealthcheckCallback          = NULL;
    callbacks.saAmfComponentTerminateCallback   = clCompAppTerminate;
    callbacks.saAmfCSISetCallback               = clCompAppAMFCSISet;
    callbacks.saAmfCSIRemoveCallback            = clCompAppAMFCSIRemove;
    callbacks.saAmfProtectionGroupTrackCallback = NULL;
        
    /*
     * Initialize AMF client library.
     */

    if ( (rc = saAmfInitialize(&amfHandle, &callbacks, &version)) != SA_AIS_OK) 
        goto errorexit;

    FD_ZERO(&read_fds);

    /*
     * Get the AMF dispatch FD for the callbacks
     */
    if ( (rc = saAmfSelectionObjectGet(amfHandle, &dispatch_fd)) != SA_AIS_OK)
        goto errorexit;
    
    FD_SET(dispatch_fd, &read_fds);


    /*
     * Do the application specific initialization here.
     */


    /*
     * Now register the component with AMF. At this point it is
     * ready to provide service, i.e. take work assignments.
     */

    if ( (rc = saAmfComponentNameGet(amfHandle, &appName)) != SA_AIS_OK) 
        goto errorexit;
    if ( (rc = saAmfComponentRegister(amfHandle, &appName, NULL)) != SA_AIS_OK) 
        goto errorexit;

    /*
     * Print out standard information for this component.
     */

    clEoMyEoIocPortGet(&iocPort);
    
    clprintf (CL_LOG_SEV_INFO, "Component [%.*s] : PID [%d]. Initializing\n", appName.length, appName.value, mypid);
    clprintf (CL_LOG_SEV_INFO, "   IOC Address             : 0x%x\n", clIocLocalAddressGet());
    clprintf (CL_LOG_SEV_INFO, "   IOC Port                : 0x%x\n", iocPort);


    /*
     * Block on AMF dispatch file descriptor for callbacks
     */
    do
    {
        if( select(dispatch_fd + 1, &read_fds, NULL, NULL, NULL) < 0)
        {
            if (EINTR == errno)
            {
                continue;
            }
		    clprintf (CL_LOG_SEV_ERROR, "Error in select()");
			perror("");
            break;
        }
        saAmfDispatch(amfHandle, SA_DISPATCH_ALL);
    }while(!unblockNow);      

    /*
     * Do the application specific finalization here.
     */


    if((rc = saAmfFinalize(amfHandle)) != SA_AIS_OK)
	{
        clprintf (CL_LOG_SEV_ERROR, "AMF finalization error[0x%X]", rc);
	}

    clprintf (CL_LOG_SEV_INFO, "AMF Finalized");
    
    return 0;

errorexit:

    clprintf (CL_LOG_SEV_ERROR, "Component [%.*s] : PID [%d]. Initialization error [0x%x]\n",
              appName.length, appName.value, mypid, rc);

    return -1;
}


/*
 * clCompAppTerminate
 * ------------------
 * This function is invoked when the application is to be terminated.
 */

void clCompAppTerminate(SaInvocationT invocation, const SaNameT *compName)
{
    SaAisErrorT rc = SA_AIS_OK;

    clprintf (CL_LOG_SEV_INFO, "Component [%.*s] : PID [%d]. Terminating\n",
              compName->length, compName->value, mypid);

    
    /*
     * Unregister with AMF and respond to AMF saying whether the
     * termination was successful or not.
     */

    if ( (rc = saAmfComponentUnregister(amfHandle, compName, NULL)) != SA_AIS_OK)
        goto errorexit;

    saAmfResponse(amfHandle, invocation, SA_AIS_OK);

    clprintf (CL_LOG_SEV_INFO, "Component [%.*s] : PID [%d]. Terminated\n",
              compName->length, compName->value, mypid);

    unblockNow = CL_TRUE;
    
    return;

errorexit:

    clprintf (CL_LOG_SEV_ERROR, "Component [%.*s] : PID [%d]. Termination error [0x%x]\n",
              compName->length, compName->value, mypid, rc);

    return;
}

/*
 * clCompAppStateChange
 * ---------------------
 * This function is invoked to change the state of an EO.
 *
 * WARNING: This function is deprecated, and may not be supported in the future.
 * Usage of this feature is discouraged.
 */

ClRcT clCompAppStateChange(ClEoStateT eoState)
{
    switch (eoState)
    {
        case CL_EO_STATE_SUSPEND:
        {
            break;
        }

        case CL_EO_STATE_RESUME:
        {
            break;
        }
        
        default:
        {
            break;
        }
    }
 
    return CL_OK;
}

/*
 * clCompAppHealthCheck
 * --------------------
 * This function is invoked to perform a healthcheck on the application. The
 * health check logic is application specific.
 */

ClRcT clCompAppHealthCheck(ClEoSchedFeedBackT* schFeedback)
{
    /*
     * Add code for application specific health check below. The
     * defaults indicate EO is healthy and polling interval is
     * unaltered.
     */

    
    schFeedback->freq   = CL_EO_DEFAULT_POLL; 
    schFeedback->status = CL_CPM_EO_ALIVE;


    return CL_OK;
}

/******************************************************************************
 * Application Work Assignment Functions
 *****************************************************************************/

/*
 * clCompAppAMFCSISet
 * ------------------
 * This function is invoked when a CSI assignment is made or the state
 * of a CSI is changed.
 */

void clCompAppAMFCSISet(SaInvocationT       invocation,
                        const SaNameT       *compName,
                        SaAmfHAStateT       haState,
                        SaAmfCSIDescriptorT csiDescriptor)
{
    /*
     * Print information about the CSI Set
     */

    clprintf (CL_LOG_SEV_INFO, "Component [%.*s] : PID [%d]. CSI Set Received\n", 
              compName->length, compName->value, mypid);

    clCompAppAMFPrintCSI(csiDescriptor, haState);

    /*
     * Take appropriate action based on state
     */

    switch ( haState )
    {
        case SA_AMF_HA_ACTIVE:
        {
            /*
             * AMF has requested application to take the active HA state 
             * for the CSI.
             */

            if (csiDescriptor.csiFlags == CL_AMS_CSI_FLAG_TARGET_ALL)
              {
                ClRcT rc;
                ClCpmCompCSIRefT csiRef = { 0 };
                ClInt32T i;
                rc = clCpmCompCSIList((ClNameT*)compName, &csiRef);
                if(rc != CL_OK)
                  {
                    clLogError("APP", "CSISET", "Comp CSI get returned [%#x]", rc);
                  }
                else
                  {
                    for(i = 0; i < csiRef.numCSIs; ++i)
                      {
                        VirtualIpAddress temp;
                        ClCpmCompCSIT *pCSI = &csiRef.pCSIList[i];
                        clprintf(CL_LOG_SEV_INFO,"Comp [%.*s], CSI [%.*s], HA state [%s]",
                                 compName->length,
                                 compName->value, 
                                 pCSI->csiDescriptor.csiName.length,
                                 pCSI->csiDescriptor.csiName.value,
                                 STRING_HA_STATE((ClUint32T)pCSI->haState));

                        GetVirtualAddressInfoAsp(&pCSI->csiDescriptor, &temp);
                        AddRemVirtualAddress("up",&temp);

                      }
                    if(csiRef.pCSIList)
                      clHeapFree(csiRef.pCSIList);
                  }
              }
            else /* CL_AMS_CSI_FLAG_ADD_ONE */
              {
            	GetVirtualAddressInfo(&csiDescriptor, &gVirtualIp);
                AddRemVirtualAddress("up",&gVirtualIp);
              }

            saAmfResponse(amfHandle, invocation, SA_AIS_OK);
            break;
        }

        case SA_AMF_HA_STANDBY:
        {
            /*
             * AMF has requested application to take the standby HA state 
             * for this CSI.
             */

        	GetVirtualAddressInfo(&csiDescriptor, &gVirtualIp);
            AddRemVirtualAddress("down",&gVirtualIp);  /* Bring it down just in case it is up from a prior run */

            saAmfResponse(amfHandle, invocation, SA_AIS_OK);
            break;
        }

        case SA_AMF_HA_QUIESCED:
        {
            /*
             * AMF has requested application to quiesce the CSI currently
             * assigned the active or quiescing HA state. The application 
             * must stop work associated with the CSI immediately.
             */

              if (csiDescriptor.csiFlags == CL_AMS_CSI_FLAG_TARGET_ONE)
                {
                  AddRemVirtualAddress("down",&gVirtualIp);
                }           
              else if (csiDescriptor.csiFlags == CL_AMS_CSI_FLAG_TARGET_ALL)
              {                
                ClRcT rc;
                ClCpmCompCSIRefT csiRef = { 0 };
                ClInt32T i;
                rc = clCpmCompCSIList((ClNameT*)compName, &csiRef);
                if(rc != CL_OK)
                  {
                    clLogError("APP", "CSISET", "Comp CSI get returned [%#x]", rc);
                  }
                else
                  {
                    for(i = 0; i < csiRef.numCSIs; ++i)
                      {
                        VirtualIpAddress temp;
                        ClCpmCompCSIT *pCSI = &csiRef.pCSIList[i];

                        clprintf(CL_LOG_SEV_INFO,"Comp [%.*s], CSI [%.*s], HA state [%s]",
                                    compName->length,
                                    compName->value, 
                                    pCSI->csiDescriptor.csiName.length,
                                    pCSI->csiDescriptor.csiName.value,
                                    STRING_HA_STATE((ClUint32T)pCSI->haState));

                        GetVirtualAddressInfoAsp(&pCSI->csiDescriptor, &temp);
                        AddRemVirtualAddress("down",&temp);

                      }
                    if(csiRef.pCSIList)
                      clHeapFree(csiRef.pCSIList);
                  }
              }
              else /* CL_AMS_CSI_FLAG_ADD_ONE */
                {
                  VirtualIpAddress temp;
                  GetVirtualAddressInfo(&csiDescriptor, &temp);
                  AddRemVirtualAddress("down",&temp);
                }

            saAmfResponse(amfHandle, invocation, SA_AIS_OK);
            break;
        }

        case SA_AMF_HA_QUIESCING:
        {
            /*
             * AMF has requested application to quiesce the CSI currently
             * assigned the active HA state. The application must stop work
             * associated with the CSI gracefully and not accept any new
             * workloads while the work is being terminated.
             */

            saAmfCSIQuiescingComplete(amfHandle, invocation, SA_AIS_OK);
            break;
        }

        default:
        {
            assert(0);
            break;
        }
    }

    return;
}

/*
 * clCompAppAMFCSIRemove
 * ---------------------
 * This function is invoked when a CSI assignment is to be removed.
 */

void clCompAppAMFCSIRemove(SaInvocationT  invocation,
                           const SaNameT  *compName,
                           const SaNameT  *csiName,
                           SaAmfCSIFlagsT csiFlags)
{
    clprintf (CL_LOG_SEV_INFO, "Component [%.*s] : PID [%d]. CSI Remove Received\n", 
              compName->length, compName->value, mypid);

    clprintf (CL_LOG_SEV_INFO, "   CSI                     : %.*s\n", csiName->length, csiName->value);
    clprintf (CL_LOG_SEV_INFO, "   CSI Flags               : 0x%d\n", csiFlags);

    /*
     * Add application specific logic for removing the work for this CSI.
     */

    saAmfResponse(amfHandle, invocation, SA_AIS_OK);

    return;
}

/******************************************************************************
 * Utility functions 
 *****************************************************************************/

/*
 * clCompAppAMFPrintCSI
 * --------------------
 * Print information received in a CSI set request.
 */

void clCompAppAMFPrintCSI(SaAmfCSIDescriptorT csiDescriptor,
                          SaAmfHAStateT haState)
{
    clprintf (CL_LOG_SEV_INFO,
              "CSI Flags : [%s]",
              STRING_CSI_FLAGS(csiDescriptor.csiFlags));

    if (SA_AMF_CSI_TARGET_ALL != csiDescriptor.csiFlags)
    {
        clprintf (CL_LOG_SEV_INFO, "CSI Name : [%s]", 
                  csiDescriptor.csiName.value);
    }

    if (SA_AMF_CSI_ADD_ONE == csiDescriptor.csiFlags)
    {
        ClUint32T i = 0;
        
        clprintf (CL_LOG_SEV_INFO, "Name value pairs :");
        for (i = 0; i < csiDescriptor.csiAttr.number; i++)
        {
            clprintf (CL_LOG_SEV_INFO, "Name : [%s]",
                      csiDescriptor.csiAttr.
                      attr[i].attrName);
            clprintf (CL_LOG_SEV_INFO, "Value : [%s]",
                      csiDescriptor.csiAttr.
                      attr[i].attrValue);
        }
    }
    
    clprintf (CL_LOG_SEV_INFO, "HA state : [%s]",
              STRING_HA_STATE(haState));

    if (SA_AMF_HA_ACTIVE == haState)
    {
        clprintf (CL_LOG_SEV_INFO, "Active Descriptor :");
        clprintf (CL_LOG_SEV_INFO,
                  "Transition Descriptor : [%d]",
                  csiDescriptor.csiStateDescriptor.
                  activeDescriptor.transitionDescriptor);
        clprintf (CL_LOG_SEV_INFO,
                  "Active Component : [%s]",
                  csiDescriptor.csiStateDescriptor.
                  activeDescriptor.activeCompName.value);
    }
    else if (SA_AMF_HA_STANDBY == haState)
    {
        clprintf (CL_LOG_SEV_INFO, "Standby Descriptor :");
        clprintf (CL_LOG_SEV_INFO,
                  "Standby Rank : [%d]",
                  csiDescriptor.csiStateDescriptor.
                  standbyDescriptor.standbyRank);
        clprintf (CL_LOG_SEV_INFO, "Active Component : [%s]",
                  csiDescriptor.csiStateDescriptor.
                  standbyDescriptor.activeCompName.value);
    }
}

/*
 * Insert any other utility functions here.
 */

