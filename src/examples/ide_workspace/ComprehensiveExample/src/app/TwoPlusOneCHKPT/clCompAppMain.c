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
 * This file provides a skeleton for writing a SAF aware component. Application
 * specific code should be added between the ---BEGIN_APPLICATION_CODE--- and
 * ---END_APPLICATION_CODE--- separators.
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

/*
 * Basic ASP Includes.
 */
#include <clCommon.h>

/*
 * ASP Client Includes.
 */
#include <clLogApi.h>

#include <clCpmApi.h>
#include <saAmf.h>

/*
 * ---BEGIN_APPLICATION_CODE---
 */
 
#include "clCompAppMain.h"
#include "../ev/ev.h"
#include <arpa/inet.h>

#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include <clOsalApi.h>
#include <clIocServices.h>

#include <clRmdApi.h>
#include <clDebugApi.h>
#include <clOmApi.h>
#include <clOampRtApi.h>
#include <clProvApi.h>
#include <clAlarmApi.h>
#include <clEoApi.h>
#include <clIdlApi.h>
#include <clCkptApi.h>

/*
 * ---END_APPLICATION_CODE---
 */

/******************************************************************************
 * Optional Features
 *****************************************************************************/

/*
 * This is necessary if the component wishes to provide a service that
 * will be used by other components.
 */

#if HAS_EO_SERVICES

extern ClRcT TwoPlusOneCHKPT_EOClientInstall(void);

#endif

/*
 * This template has a few default clprintfs. These can be disabled by
 * changing clprintf to a null function
 */

#define clprintf(severity, ...)   clAppLog(CL_LOG_HANDLE_APP, severity, 10, \
                                  CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,\
                                  __VA_ARGS__)

/*
 * ---BEGIN_APPLICATION_CODE---
 */

static void* testCkpMainLoop(void *thdParam);

/*
 * ---END_APPLICATION_CODE---
 */

/******************************************************************************
 * Global Variables.
 *****************************************************************************/

pid_t mypid;
SaAmfHandleT amfHandle;

ClBoolT unblockNow = CL_FALSE;

/*
 * ---BEGIN_APPLICATION_CODE---
 */

/*
 * Declare other global variables here.
 */
static int running = 1;
static int exiting = 0;
static char           appname[CL_MAX_NAME_LENGTH];  /* Component instance name               */
static ClUint32T      seq      = 0; /* Sequence number for print lines       */
static ClAmsHAStateT  ha_state = CL_AMS_HA_STATE_NONE; /* HA state           */

#define CKPT_NAME     "TwoPlusOneCHKPT"  /* Checkpoint name for this application  */

static SaCkptHandleT  ckpt_svc_handle; /* Checkpointing service handle       */
static SaCkptHandleT  ckpt_handle;  /* Checkpoint handle                     */
#define CKPT_SID_NAME "1"           /* Checkpoint section id                 */

static SaCkptSectionIdT ckpt_sid = { /* Section id for checkpoints           */
        (SaUint16T)sizeof(CKPT_SID_NAME)-1,
        (SaUint8T*)CKPT_SID_NAME
};

/*
 * ---END_APPLICATION_CODE---
 */

/*
 * Description of this EO
 */

ClEoConfigT clEoConfig =
{
    COMP_EO_NAME,               /* EO Name                                  */
    COMP_EO_THREAD_PRIORITY,    /* EO Thread Priority                       */
    COMP_EO_NUM_THREAD,         /* No of EO thread needed                   */
    COMP_IOC_PORT,              /* Required Ioc Port                        */
    COMP_EO_USER_CLIENT_ID, 
    COMP_EO_USE_THREAD_MODEL,   /* Thread Model                             */
    NULL,                       /* Application Initialize Callback          */
    NULL,                       /* Application Terminate Callback           */
    clCompAppStateChange,       /* Application State Change Callback        */
    clCompAppHealthCheck,       /* Application Health Check Callback        */
};

/*
 * Basic libraries used by this EO. The first 6 libraries are
 * mandatory, the others can be enabled or disabled by setting to
 * CL_TRUE or CL_FALSE.
 */

ClUint8T clEoBasicLibs[] =
{
    COMP_EO_BASICLIB_OSAL,      /* Lib: Operating System Adaptation Layer   */
    COMP_EO_BASICLIB_TIMER,     /* Lib: Timer                               */
    COMP_EO_BASICLIB_BUFFER,    /* Lib: Buffer Management                   */
    COMP_EO_BASICLIB_IOC,       /* Lib: Intelligent Object Communication    */
    COMP_EO_BASICLIB_RMD,       /* Lib: Remote Method Dispatch              */
    COMP_EO_BASICLIB_EO,        /* Lib: Execution Object                    */
    COMP_EO_BASICLIB_OM,        /* Lib: Object Management                   */
    COMP_EO_BASICLIB_HAL,       /* Lib: Hardware Adaptation Layer           */
    COMP_EO_BASICLIB_DBAL,      /* Lib: Database Adaptation Layer           */
};

/*
 * Client libraries used by this EO. All are optional and can be
 * enabled or disabled by setting to CL_TRUE or CL_FALSE.
 */

ClUint8T clEoClientLibs[] =
{
    COMP_EO_CLIENTLIB_COR,      /* Lib: Common Object Repository            */
    COMP_EO_CLIENTLIB_CM,       /* Lib: Chassis Management                  */
    COMP_EO_CLIENTLIB_NAME,     /* Lib: Name Service                        */
    COMP_EO_CLIENTLIB_LOG,      /* Lib: Log Service                         */
    COMP_EO_CLIENTLIB_TRACE,    /* Lib: Trace Service                       */
    COMP_EO_CLIENTLIB_DIAG,     /* Lib: Diagnostics                         */
    COMP_EO_CLIENTLIB_TXN,      /* Lib: Transaction Management              */
    CL_FALSE,                   /* NA */
    COMP_EO_CLIENTLIB_PROV,     /* Lib: Provisioning Management             */
    COMP_EO_CLIENTLIB_ALARM,    /* Lib: Alarm Management                    */
    COMP_EO_CLIENTLIB_DEBUG,    /* Lib: Debug Service                       */
    COMP_EO_CLIENTLIB_GMS,       /* Lib: Cluster/Group Membership Service    */
    COMP_EO_CLIENTLIB_PM        /* Lib: Performance Management              */
};

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
    ClRcT               rc = SA_AIS_OK;

    SaSelectionObjectT dispatch_fd;
    fd_set read_fds;
    
    /*
     * ---BEGIN_APPLICATION_CODE---
     */

    /*
     * Declare other local variables here.
     */
    SaAisErrorT		saRc = SA_AIS_OK;

    /*
     * ---END_APPLICATION_CODE---
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

    
#if HAS_EO_SERVICES


    rc = TwoPlusOneCHKPT_EOClientInstall();

#endif

    /*
     * Do the application specific initialization here.
     */

    /*
     * ---BEGIN_APPLICATION_CODE---
     */

    printf("TwoPlusOneCHKPT: Initializing and registering with CPM...\n");

    /*
     * ---END_APPLICATION_CODE---
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
     * ---BEGIN_APPLICATION_CODE---
     */

    strncpy(appname, (ClCharT*)appName.value, sizeof(appname)-1);

    /* Set up console redirection for demo purposes */
    (void)ev_init(argc, argv, (ClCharT*)appName.value);

    printf("%s: Instantiated as component instance %s.\n", appname, appName.value);

    printf("%s: Waiting for CSI assignment...\n", appName.value);

    /* Main loop: Keep printing something unless we are suspended */
    if (ha_state != CL_AMS_HA_STATE_ACTIVE)
    {
        printf("%s: Waiting for CSI assignment...\n", appname);
    }
    if ((saRc = checkpoint_initialize()) != SA_AIS_OK)
    {
        clOsalPrintf("%s: Failed [0x%x] to initialize checkpoint\n",
                    appname, saRc);
        return saRc;
    }
    if ((saRc = checkpoint_read_seq(&seq)) != SA_AIS_OK)
    {
        clOsalPrintf("%s: Failed [0x%x] to read checkpoint\n",
                    appname, saRc);
        checkpoint_finalize();
        return saRc;
    }
#ifdef CL_INST
    if ((rc = clDataTapInit(DATA_TAP_DEFAULT_FLAGS, 203)) != CL_OK)
    {
        clOsalPrintf("%s: Failed [0x%x] to initialize data tap\n",
                    appname, rc);
    }
#endif
    rc = clOsalTaskCreateDetached("testCkpMainLoop",
                             CL_OSAL_SCHED_OTHER,
                             CL_OSAL_THREAD_PRI_NOT_APPLICABLE,
                             65536,
                             testCkpMainLoop,
                             (void*)appname);

    if(CL_OK != rc)
    {
        clprintf (CL_LOG_SEV_CRITICAL, "Task creation error[0x%X]", rc);
    }
    
    /*
     * ---END_APPLICATION_CODE---
     */

    /*
     * Block on AMF dispatch file descriptor for callbacks
     */
    do
    {
        if( select(dispatch_fd + 1, &read_fds, NULL, NULL, NULL) < 0)
        {
		    clprintf (CL_LOG_SEV_ERROR, "Error in select()");
			perror("");
            break;
        }
        saAmfDispatch(amfHandle, SA_DISPATCH_ALL);
    }while(!unblockNow);      

    /*
     * Do the application specific finalization here.
     */

    /*
     * ---BEGIN_APPLICATION_CODE---
     */

    /*
     * ---END_APPLICATION_CODE---
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
     * ---BEGIN_APPLICATION_CODE--- 
     */

    exiting = 1;
    printf("Component is terminating...\n");
    checkpoint_finalize();

    /*
     * ---END_APPLICATION_CODE---
     */
    
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
            /*
             * ---BEGIN_APPLICATION_CODE---
             */

            running = 0;

            /*
             * ---END_APPLICATION_CODE---
             */

            break;
        }

        case CL_EO_STATE_RESUME:
        {
            /*
             * ---BEGIN_APPLICATION_CODE---
             */

            running = 1;

            /*
             * ---END_APPLICATION_CODE---
             */

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

    /*
     * ---BEGIN_APPLICATION_CODE---
     */
    
    schFeedback->freq   = CL_EO_DEFAULT_POLL; 
    schFeedback->status = CL_CPM_EO_ALIVE;

    /*
     * ---END_APPLICATION_CODE---
     */

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
     * ---BEGIN_APPLICATION_CODE--- 
     */

    ClRcT rc = CL_OK;

    /*
     * ---END_APPLICATION_CODE---
     */

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

            /*
             * ---BEGIN_APPLICATION_CODE---
             */

            printf("%s: Active state requested from state %d\n",
                        appname, ha_state);

            checkpoint_replica_activate();

            if (ha_state == CL_AMS_HA_STATE_STANDBY)
            {
                /* Read checkpoint, make our replica the active replica */
                printf("%s reading checkpoint\n", appname);
                rc = checkpoint_read_seq(&seq);
                printf("%s read checkpoint: seq = %u\n", appname, seq);
            }
            
            ha_state = CL_AMS_HA_STATE_ACTIVE;

            /*
             * ---END_APPLICATION_CODE---
             */

            saAmfResponse(amfHandle, invocation, SA_AIS_OK);
            break;
        }

        case SA_AMF_HA_STANDBY:
        {
            /*
             * AMF has requested application to take the standby HA state 
             * for this CSI.
             */

            /*
             * ---BEGIN_APPLICATION_CODE---
             */

            printf("%s: Standby state requested\n", appname);
            
            ha_state = CL_AMS_HA_STATE_STANDBY;

            /*
             * ---END_APPLICATION_CODE---
             */

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

            /*
             * ---BEGIN_APPLICATION_CODE---
             */

            printf("%s: QUIESCED\n", appname);
            ha_state = haState;

            /*
             * ---END_APPLICATION_CODE---
             */

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

            /*
             * ---BEGIN_APPLICATION_CODE---
             */

            printf("%s: QUIESCING\n", appname);
            ha_state = haState;

            /*
             * ---END_APPLICATION_CODE---
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

    /*
     * ---BEGIN_APPLICATION_CODE---
     */

    // ...

    /*
     * ---END_APPLICATION_CODE---
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
 * ---BEGIN_APPLICATION_CODE---
 */

/*
 * Insert any other utility functions here.
 */
static ClRcT
checkpoint_initialize()
{
	SaAisErrorT rc = SA_AIS_OK;
	SaVersionT  ckpt_version = {'B', 1, 1};
	SaNameT     ckpt_name = { strlen(CKPT_NAME), CKPT_NAME };
	SaUint32T   seq_no;
	SaCkptCheckpointCreationAttributesT create_atts = {
		.creationFlags     = SA_CKPT_WR_ACTIVE_REPLICA_WEAK |
			SA_CKPT_CHECKPOINT_COLLOCATED,
		.checkpointSize    = sizeof(SaUint32T),
		.retentionDuration = (SaTimeT)0, 
		.maxSections       = 2, // default section, plus section we create
		.maxSectionSize    = sizeof(SaSizeT),
		.maxSectionIdSize  = (SaSizeT)64
	};

	SaCkptSectionCreationAttributesT section_atts = {
		.sectionId = &ckpt_sid,
		.expirationTime = SA_TIME_END
	};

	clOsalPrintf("%s: checkpoint_initialize\n", appname);
	/* Initialize checkpointing service instance */
	rc = saCkptInitialize(&ckpt_svc_handle, /* Checkpoint service handle */
			NULL,		    /* Optional callbacks table */
			&ckpt_version);   /* Required verison number */
	if (rc != SA_AIS_OK)
	{
		clOsalPrintf("%s: ERROR: Failed to initialize checkpoint service\n",
				appname);
		return rc;
	}
	clOsalPrintf("%s: Checkpoint service initialized (handle=0x%x)\n",
			appname, ckpt_svc_handle);

	//
	// Create the checkpoint for read and write.  If we fail to open it
	// then open it without CREATE.  The retry loop is to deal with the
	// possibility that multiple processes might all come along here
	// and fail to open the checkpoint because it hasn't been created
	// yet and then they all try to create the checkpoint.  All but
	// the first would fail.  This retry allows all the rest of the
	// processes to come through and open without CREATE
	// TODO: change it to a straight retry loop where we start off with
	// mode = (CL_CKPT_CHECKPOINT_READ | CL_CKPT_CHECKPOINT_WRITE)
	// and on each iteration of the loop we xor in
	// CL_CKPT_CHECKPOINT_CREATE.  That should let us do the same thing
	// but without the duplication of the clCkptCheckpointOpen call
	rc = saCkptCheckpointOpen(ckpt_svc_handle,      // Service handle
			&ckpt_name,         // Checkpoint name
			&create_atts,       // Optional creation attr.
			(SA_CKPT_CHECKPOINT_READ |
			 SA_CKPT_CHECKPOINT_WRITE |
			 SA_CKPT_CHECKPOINT_CREATE),
			(SaTimeT)-1,        // No timeout
			&ckpt_handle);      // Checkpoint handle
	if (rc != SA_AIS_OK)
	{
		clOsalPrintf("%s: ERROR: Failed [0x%x] to open checkpoint\n",
				appname, rc);
		(void)clCkptFinalize(ckpt_svc_handle);
		return rc;
	}
	clOsalPrintf("%s: Checkpoint opened (handle=0x%x)\n", appname, ckpt_handle);

	/*
	 * Try to create a section so that updates can operate by overwriting
	 * the section over and over again.
	 * If subsequent processes come through here, they will fail to create
	 * the section.  That is OK, even though it will cause an error message
	 * If the section create fails because the section is already there, then
	 * read the sequence number
	 */
	// Put data in network byte order
	seq_no = htonl(seq);

	// Creating the section
	checkpoint_replica_activate();
	rc = saCkptSectionCreate(ckpt_handle,           // Checkpoint handle
			&section_atts,         // Section attributes
			(SaUint8T*)&seq_no,    // Initial data
			(SaSizeT)sizeof(seq_no)); // Size of data
	if (rc != SA_AIS_OK && rc != SA_AIS_ERR_EXIST)
	{
		printf("%s: ERROR: Failed [0x %x] to create checkpoint section\n", appname, rc);
		(void)clCkptCheckpointClose(ckpt_handle);
		(void)clCkptFinalize(ckpt_svc_handle);
		return rc;
	}
	else if (rc != SA_AIS_OK && rc == SA_AIS_ERR_EXIST)
	{
		rc = checkpoint_read_seq(&seq);
		if (rc != SA_AIS_OK)
		{
			printf("%s: ERROR: Failed [0x%x] to read checkpoint section\n",
					appname, rc);
			(void)saCkptCheckpointClose(ckpt_handle);
			(void)saCkptFinalize(ckpt_svc_handle);
			return rc;
		}
	}
	else
	{
		clOsalPrintf("%s: Section created\n", appname);
	}
	/* Open checkpoint for read to write depending on input argument */

	return rc;
}

static SaAisErrorT
checkpoint_finalize(void)
{
    SaAisErrorT rc;

    rc = saCkptCheckpointClose(ckpt_handle);
    if (rc != SA_AIS_OK)
    {
        clOsalPrintf("%s: failed: [0x%x] to close checkpoint handle %d\n",
                    appname, rc, ckpt_handle);
    }
    rc = saCkptFinalize(ckpt_svc_handle);
    if (rc != SA_AIS_OK)
    {
        clOsalPrintf("%s: failed: [0x%x] to finalize checkpoint\n",
                    appname, rc);
    }
    return SA_AIS_OK;
}

static SaAisErrorT
checkpoint_write_seq(ClUint32T seq)
{
    SaAisErrorT rc = SA_AIS_OK;
    SaUint32T seq_no;
    
    /* Putting data in network byte order */
    seq_no = htonl(seq);
//    clOsalPrintf("checkpoint_write_seq: seq_no = %lu, seq = %lu\n", seq_no, seq); fflush(stdout);
    
    /* Write checkpoint */
    rc = saCkptSectionOverwrite(ckpt_handle,
                                &ckpt_sid,
                                &seq_no,
                                sizeof(SaUint32T));
    if (rc != SA_AIS_OK)
    {
        clOsalPrintf("Failed [0x%x] to write to section\n", rc);
    }
    else
    {
        rc = saCkptCheckpointSynchronize(ckpt_handle, SA_TIME_END );
        if (rc != SA_AIS_OK)
        {
            clOsalPrintf("Failed [0x%x] to synchronize the checkpoint\n", rc);
        }
    }

    return rc;
}

static SaAisErrorT
checkpoint_read_seq(ClUint32T *seq)
{
    SaAisErrorT rc = SA_AIS_OK;
    SaUint32T err_idx; /* Error index in ioVector */
    SaUint32T seq_no = 0xffffffff;
    SaCkptIOVectorElementT iov = {
        .sectionId  = ckpt_sid,
        .dataBuffer = (void *)&seq_no,
        .dataSize   = sizeof(SaUint32T),
        .dataOffset = (SaSizeT)0,
        .readSize   = sizeof(SaUint32T)
    };
        
    rc = saCkptCheckpointRead(ckpt_handle, &iov, 1, &err_idx);
    if (rc != SA_AIS_OK )
    {
        clOsalPrintf("Error: [0x%x] from checkpoint read, err_idx = %u\n",
                    rc, err_idx);
    }

    /* FIXME: How to process this err_idx? */
    *seq = ntohl(seq_no);
//    clOsalPrintf("checkpoint_read_seq: seq_no = %lu, seq = %lu\n", seq_no, *seq); fflush(stdout);
    
    return rc;
}

static SaAisErrorT
checkpoint_replica_activate(void)
{
    SaAisErrorT     rc = SA_AIS_OK;

    if ((rc = saCkptActiveReplicaSet(ckpt_handle)) != SA_AIS_OK)
    {
        clOsalPrintf(
                "checkpoint_replica_activate failed [0x%x] in ActiveReplicaSet",
                rc);
    }

    return rc;
}

static void*
testCkpMainLoop(void *thdParam)
{
    SaAisErrorT saRc = SA_AIS_OK;
    char *appname = (char*)thdParam;

    while (!exiting)
    {
        if (running && ha_state == CL_AMS_HA_STATE_ACTIVE)
        {
            printf("%s: Hello World! (seq=%d)\n", appname, seq++);

#ifdef CL_INST
            if ((rc = clDataTapSend(seq)) != CL_OK && (rc != CL_ERR_INVALID_PARAMETER))
            {
                clOsalPrintf("%s: Failed [0x%x] to send data tap data\n",
                            appname, rc);
            }
#endif
            
            /* Checkpoint new sequence number */
            saRc = checkpoint_write_seq(seq);
            if (saRc != SA_AIS_OK)
            {
                printf("%s: ERROR: Checkpoint write failed. Exiting.\n", appname);
                break;
            }
        }
        sleep(1);
    }

    return NULL;
}

/*
 * ---END_APPLICATION_CODE---
 */

