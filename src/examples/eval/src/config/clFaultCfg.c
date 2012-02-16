/******************************************************************************
 *
 * clFaultLocalCfg.c
 *
 ******************************************************************************
 * This code is auto-generated by OpenClovis IDE Version 2.3.0
 *
 ***************************** Description ************************************
 *
 * This file contains application specific FML
 * configuration data and callouts.
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <clEoApi.h>
#include <clFaultDefinitions.h>
#include <clFaultApi.h>
#include <clFaultErrorId.h>
#include <clDebugApi.h>
#define SIMULATION_VERSION
/**@#-*/
#ifndef COMP_DEBUG_VAR
#define COMP_DEBUG_VAR CL_DEBUG_TRACE
#endif



extern ClRcT ClFaultCompRestartRequest(ClFaultRecordPtr hRec);
extern ClRcT clFaultEscalate(ClFaultRecordPtr hRec);


ClUint32T clFaultLocalProbationPeriod = 10;
 /*************************/ 
extern ClRcT foo1(ClFaultRecordPtr hRec);
 /*************************/ 
ClFaultSeqTblT	comCR_SeqTbl[] = { foo1, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	comMJ_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	comMN_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	comWR_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	comIN_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	comCL_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	qosCR_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	qosMJ_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	qosMN_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	qosWR_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	qosIN_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	qosCL_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	procCR_SeqTbl[] = { ClFaultCompRestartRequest, ClFaultCompRestartRequest, ClFaultCompRestartRequest, ClFaultCompRestartRequest, clFaultEscalate};

ClFaultSeqTblT	procMJ_SeqTbl[] = { ClFaultCompRestartRequest, ClFaultCompRestartRequest, ClFaultCompRestartRequest, ClFaultCompRestartRequest, clFaultEscalate};

ClFaultSeqTblT	procMN_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	procWR_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	procIN_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	procCL_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	equipCR_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	equipMJ_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	equipMN_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	equipWR_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	equipIN_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	equipCL_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	envCR_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	envMJ_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	envMN_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	envWR_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	envIN_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};

ClFaultSeqTblT	envCL_SeqTbl[] = { NULL, NULL, NULL, NULL, NULL};
 /*************************/ 
ClFaultSeqTblT	*com_2DSeqTbls[] =
{
	comCR_SeqTbl,
	comMJ_SeqTbl,
	comMN_SeqTbl,
	comWR_SeqTbl,
	comIN_SeqTbl,
	comCL_SeqTbl
};

ClFaultSeqTblT	*qos_2DSeqTbls[] =
{
	qosCR_SeqTbl,
	qosMJ_SeqTbl,
	qosMN_SeqTbl,
	qosWR_SeqTbl,
	qosIN_SeqTbl,
	qosCL_SeqTbl
};

ClFaultSeqTblT	*proc_2DSeqTbls[] =
{
	procCR_SeqTbl,
	procMJ_SeqTbl,
	procMN_SeqTbl,
	procWR_SeqTbl,
	procIN_SeqTbl,
	procCL_SeqTbl
};

ClFaultSeqTblT	*equip_2DSeqTbls[] =
{
	equipCR_SeqTbl,
	equipMJ_SeqTbl,
	equipMN_SeqTbl,
	equipWR_SeqTbl,
	equipIN_SeqTbl,
	equipCL_SeqTbl
};

ClFaultSeqTblT	*env_2DSeqTbls[] =
{
	envCR_SeqTbl,
	envMJ_SeqTbl,
	envMN_SeqTbl,
	envWR_SeqTbl,
	envIN_SeqTbl,
	envCL_SeqTbl
};
 /*************************/ 
ClFaultSeqTblT  **fmSeqTbls[] =
{
    com_2DSeqTbls,
    qos_2DSeqTbls,
    proc_2DSeqTbls,
    equip_2DSeqTbls,
    env_2DSeqTbls
};
