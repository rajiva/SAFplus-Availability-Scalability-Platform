/*********************************************************************
* ModuleName  : idl
*********************************************************************/
/*********************************************************************
* Description :Client Stub routines
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/
#undef __SERVER__
#define __CLIENT__

#include "msgCltSrvClient.h"
#include "msgCltSrvFuncTable.h"

ClRcT clMsgCltSrvClientTableRegister(ClIocPortT clientPort)
{
    ClRcT rc = CL_OK;

    rc = clEoClientTableRegister(CL_EO_CLIENT_SYM_MOD(gAspFuncTable, MsgCltSrv),
                                 clientPort);
    if (CL_OK != rc)
    {
        return rc;
    }

    return rc;
}

ClRcT clMsgCltSrvClientTableDeregister(void)
{
    return CL_OK;
}

