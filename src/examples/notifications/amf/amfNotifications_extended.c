/*
 * Sample AMF notification example. 
 * This is an extension of amfNotifications.c example that tries to get active comps
 * 
 * The notification types are in clAmsClientNotification.h with ClAmsNotificationInfoT
 * for payload
 * The below examples shows the notifications for the important notifications that
 * our customers use to handle notifications. 
 * Some of them use it with their mgmt/confd wrapper
 *
 * clAmsNotificationInitialize sets up the notification.
 * Can be called by the comp. after saAmfInitialize for eg:
 *
 * clAmsNotificationFinalize just finalizes it.
 * Can be called by the comp. in app terminate before saAmfResponse for eg:
 *
 * The getComps routine below tries to obtain the active component 
 * from either SI partial ha state notifications or SU ha state notifications 
 * (any one though eg: below fires it from both on haState active for si/su notification)
 * The partial SI notifications with SU would come when the SI becomes active
 * or moves from fully assigned (redundant) to partially assigned on standby removal
 *
 * Another version: getCompsAsync tries to do the same but by fetching the components
 * through a task pool or job queue without blocking the amf notification callback context.
 *
 */

#include <clCommon.h>
#include <clCommonErrors.h>
#include <clLogApi.h>
#include <clDebugApi.h>
#include <clAmsMgmtClientApi.h>
#include <clAmsClientNotification.h>
#include <clJobQueue.h>
#include <clCpmExtApi.h>

#define CL_AMS_STRING_NTF(S)                                        \
(   ((S) == CL_AMS_NOTIFICATION_SI_PARTIALLY_ASSIGNED)        ? "partially assigned" :          \
    ((S) == CL_AMS_NOTIFICATION_SI_FULLY_ASSIGNED)        ? "fully assigned" : \
    ((S) == CL_AMS_NOTIFICATION_SI_UNASSIGNED)        ? "unassigned" : \
                                                  "Unknown" )

static ClAmsMgmtHandleT mgmtHandle;
static ClJobQueueT notifJobPool;

extern ClRcT getSlotFromSU(const SaNameT *su, ClIocNodeAddressT *slot);

/*
 * New auxiliary function to get active comp from sg name
 */
extern ClRcT getCompsFromSG(ClAmsMgmtHandleT mgmtHandle, const ClNameT *sg);
/*
 * If SI/SU ha state notifications indicate active ha state for si/su,
 * get SU comp list. 
 * Optionally, just fetch comp csi list as an example below
 */
static ClRcT getComps(const SaNameT *si, const SaNameT *su)
{
    ClAmsEntityT targetEntity = {0};
    ClAmsEntityBufferT compBuffer = {0};
    ClUint32T i;
    ClRcT rc = CL_OK;

#if 0
    ClAmsSUConfigT *suConfig = NULL;
    ClAmsSIConfigT *siConfig = NULL;

    targetEntity.type = CL_AMS_ENTITY_TYPE_SU;
    clNameCopy(&targetEntity.name, (ClNameT*)su);

    /*
     * If you want, get su or si config to check parent SG 
     */
    rc = clAmsMgmtEntityGetConfig(mgmtHandle, &targetEntity, (ClAmsEntityConfigT**)&suConfig);
    if(rc != CL_OK)
    {
        clLogError("GET", "COMP", "Get SU [%s] config returned with [%#x]",
                   targetEntity.name.value, rc);
        goto out;
    }
    clLogNotice("GET", "COMP", "SU [%s] parent SG [%s]",
                targetEntity.name.value, suConfig->parentSG.entity.name.value);
    clHeapFree(suConfig);

    /*
     * Or you can fetch SG from si config as well
     */
    targetEntity.type = CL_AMS_ENTITY_TYPE_SI;
    clNameCopy(&targetEntity.name, (ClNameT*)si);

    rc = clAmsMgmtEntityGetConfig(mgmtHandle, &targetEntity, (ClAmsEntityConfigT**)&siConfig);
    if(rc != CL_OK)
    {
        clLogError("GET", "COMP", "GET SI [%s] config returned with [%#x]",
                   targetEntity.name.value, rc);
        goto out;
    }
    clLogNotice("GET", "COMP", "SI [%s] parent SG [%s]", 
                targetEntity.name.value, siConfig->parentSG.entity.name.value);
    /*
     * Can request getting active comp. with sg
     *
     * getCompsFromSG(mgmtHandle, &siConfig->parentSG.entity.name);
     *
     */
    clHeapFree(siConfig);
#endif

    targetEntity.type = CL_AMS_ENTITY_TYPE_SU;
    clNameCopy(&targetEntity.name, (ClNameT*)su);

    /*  
     * Get SU comp list for the active components since we fetch this on 
     * active ha state notifications.
     * Additionally, just fetch the comp csi list as an extended example
     * just in case ...
     */
    rc = clAmsMgmtGetSUCompList(mgmtHandle, &targetEntity, &compBuffer);
    if(rc != CL_OK)
    {
        clLogNotice("GET", "COMP", "SU [%s] comp list returned with [%#x]",
                    targetEntity.name.value, rc);
        goto out;
    }
    ClAmsCompCSIRefBufferT csiBuffer = {0};
    for(i = 0; i < compBuffer.count; ++i)
    {
        ClAmsEntityT *comp = compBuffer.entity + i;
        clLogNotice("GET", "COMP", "SU [%s], comp [%s]",
                    targetEntity.name.value, comp->name.value);
        /*
         * Optional step since the above function would be invoked
         * anyway on active ha state transitions in which case, above comp
         * would be active,
         */
        rc = clAmsMgmtGetCompCSIList(mgmtHandle, comp, &csiBuffer);
        if(rc != CL_OK)
        {
            clLogError("GET", "COMP", "Comp csi list returned with [%#x]", rc);
            goto out;
        }
        for(ClUint32T j = 0; j < csiBuffer.count; ++j )
        {
            ClAmsCompCSIRefT *csiRef = csiBuffer.entityRef + j;
            if(csiRef->haState == CL_AMS_HA_STATE_ACTIVE
               &&
               csiRef->activeComp)
            {
                clLogNotice("GET", "COMP", "CSI [%s], Active comp [%s]",
                            csiRef->entityRef.entity.name.value,
                            csiRef->activeComp->name.value);
                        
            }
        }
        clAmsMgmtFreeCompCSIRefBuffer(&csiBuffer);
        csiBuffer.count = 0;
    }

    out:
    if(csiBuffer.entityRef)
        clAmsMgmtFreeCompCSIRefBuffer(&csiBuffer);
    if(compBuffer.entity)
        clHeapFree(compBuffer.entity);

    return rc;
}

/*
 * Async version through task pool thread to just unblock the amf client notification
 * callback
 */
__attribute__((unused)) static ClRcT getCompsAsyncJobRequest(ClPtrT arg)
{
    SaNameT **arr = arg;
    ClRcT rc = CL_OK;
    CL_ASSERT(arr != NULL);
    CL_ASSERT(arr[0] && arr[1]);
    rc = getComps(arr[0], arr[1]);
    clHeapFree(arr[0]);
    clHeapFree(arr[1]);
    clHeapFree(arr);
    return rc;
}

/*
 * In case you want to unblock the AMF notification callback context,
 * you can force this through a task pool thread
 */
__attribute__((unused)) static ClRcT getCompsAsync(const SaNameT *si, const SaNameT *su)
{
    ClRcT rc = CL_OK;
    SaNameT *cloneSI = clHeapCalloc(1, sizeof(*cloneSI));
    SaNameT *cloneSU = clHeapCalloc(1, sizeof(*cloneSU));
    SaNameT **arr = clHeapCalloc(2, sizeof(*arr));
    CL_ASSERT(cloneSI && cloneSU && arr);

    memcpy(cloneSI, si, sizeof(*cloneSI));
    memcpy(cloneSU, su, sizeof(*cloneSU));
    arr[0] = cloneSI;
    arr[1] = cloneSU;
    if(!notifJobPool.flags)
    {
        rc = clJobQueueInit(&notifJobPool, 0, 1);
        if(rc != CL_OK)
        {
            clLogError("GET", "COMP", "Job queue init returned with [%#x]", rc);
            goto out;
        }
    }
    rc = clJobQueuePush(&notifJobPool, getCompsAsyncJobRequest, (ClPtrT)arr);
    out:
    return rc;
}

/*
 * Nice to cache the amf db into the cache handle as
 * component su/csi/si info won't change if already cached. 
 * Can delete the cache anytime(process exit) with clAmsMgmtDBFinalize(&cache);
 * Or can be just ok. to leave the cache as it is since its one time anyway
 * and needn't be costly to free as it would be freed by the kernel on process
 * exit and doesn't count as a runtime leak anyway.
 */
static ClAmsMgmtDBHandleT cache;

/*
 * getCompRestartConfig -- gets su name and siname (applicable if csi assigned)
 * given a suName or a compName or both.
 * if suName is provided in the first arg, then get siName for a component in the SU
 * or the component specified for the SU
 * if compName is provided and SUname is null, then get parent SU for the component
 * and si (when assigned csi) in suRet and siRet
 */
ClRcT getCompRestartConfig(const SaNameT *suName, const ClNameT *compName,
                           ClNameT *suRet, ClNameT *siRet)
{
    ClRcT rc = CL_OK;
    ClAmsCompConfigT *compConfig = NULL;
    ClAmsEntityBufferT compBuffer = {0};
    ClAmsEntityT entity = {0};
    ClAmsEntityT *entityComp = &entity;
    ClAmsCompCSIRefBufferT csiRefBuffer = {0};
    ClBoolT restartRecovery = CL_FALSE;
    if(!cache)
    {
        rc = clAmsMgmtDBGet(&cache);
        if(rc != CL_OK) goto out;
    }
    if(suName)
    {
        if(suRet)
        {
            clNameCopy(suRet, (ClNameT*)suName);
        }
        entity.type = CL_AMS_ENTITY_TYPE_SU;
        clNameCopy(&entity.name, (ClNameT*)suName);
        rc = clAmsMgmtDBGetSUCompList(cache, &entity, &compBuffer);
        if(rc != CL_OK) goto out;
        for(ClUint32T i = 0; i < compBuffer.count; ++i)
        {
            ClAmsEntityT *comp = compBuffer.entity + i;
            if(compName && strcmp((const char*)compName->value, comp->name.value)) continue;
            entityComp = comp;
            rc = clAmsMgmtDBGetEntityConfig(cache, comp, (ClAmsEntityConfigT**)&compConfig);
            if(rc != CL_OK)
            {
                goto out_free;
            }
            if(compConfig->recoveryOnTimeout == CL_AMS_RECOVERY_COMP_RESTART
               ||
               compConfig->recoveryOnTimeout == CL_AMS_RECOVERY_NO_RECOMMENDATION)
            {
                restartRecovery = CL_TRUE;
                clHeapFree(compConfig);
                compConfig = NULL;
                break;
            }
        }
    }
    else
    {
        entity.type = CL_AMS_ENTITY_TYPE_COMP;
        clNameCopy(&entity.name, compName);
        rc = clAmsMgmtDBGetEntityConfig(cache, &entity, (ClAmsEntityConfigT**)&compConfig);
        if(rc != CL_OK) goto out;
        if(compConfig->recoveryOnTimeout == CL_AMS_RECOVERY_COMP_RESTART
           ||
           compConfig->recoveryOnTimeout == CL_AMS_RECOVERY_NO_RECOMMENDATION)
        {
            restartRecovery = CL_TRUE;
        }
        if(suRet)
        {
            clNameCopy(suRet, &compConfig->parentSU.entity.name);
        }
        clHeapFree(compConfig);
        compConfig = NULL;
    }

    if(!restartRecovery)
    {
        rc = CL_AMS_RC(CL_ERR_INVALID_STATE);
        goto out_free;
    }

    rc = clAmsMgmtDBGetCompCSIList(cache, entityComp, &csiRefBuffer);
    if(rc != CL_OK)
        goto out_free;
    /*
     * CSI not yet assigned. 
     * Try later or wrong time but would work on a restart recovery...
     */
    if(!csiRefBuffer.count)
    {
        rc = CL_AMS_RC(CL_ERR_NOT_EXIST);
        goto out_free;
    }

    for(ClUint32T i = 0; i < csiRefBuffer.count; ++i)
    {
        ClAmsEntityT *csi = &csiRefBuffer.entityRef[i].entityRef.entity;
        clLogNotice("GET", "COMP", "Comp [%s] has CSI [%s]",
                    entityComp->name.value, csi->name.value);
        ClAmsCSIConfigT *csiConfig = NULL;
        rc = clAmsMgmtDBGetEntityConfig(cache, csi, (ClAmsEntityConfigT**)&csiConfig);
        if(rc != CL_OK)
            goto out_free;
        clLogNotice("GET", "COMP", "Comp [%s] has SI [%s]",
                    entityComp->name.value, csiConfig->parentSI.entity.name.value);
        if(siRet)
            clNameCopy(siRet, &csiConfig->parentSI.entity.name);
        clHeapFree(csiConfig);
        break;
    }

    out_free:
    if(csiRefBuffer.entityRef)
        clAmsMgmtFreeCompCSIRefBuffer(&csiRefBuffer);
    if(compBuffer.entity)
        clHeapFree(compBuffer.entity);
    if(compConfig)
        clHeapFree(compConfig);

    out:
    return rc;
}

static ClRcT amsNotificationCallback(ClAmsNotificationInfoT *notification)
{
    switch(notification->type)
    {
        /*
         * Partially assigned when SI is assigned active with no standby 
         * or standby removed to transition from fully assigned
         */
    case CL_AMS_NOTIFICATION_SI_PARTIALLY_ASSIGNED:
        {
            clLogNotice("EVT", "NTF", "Received SI [%s] event", CL_AMS_STRING_NTF(notification->type));
            clLogNotice("EVT", "NTF", "SI name : [%.*s]",
                      notification->amsStateNotification.siName.length,
                      notification->amsStateNotification.siName.value);
            clLogNotice("EVT", "NTF", "SU name : [%.*s]",
                      notification->amsStateNotification.suName.length,
                      notification->amsStateNotification.suName.value);
            clLogNotice("EVT", "NTF", "Last HA State : [%s]",
                      CL_AMS_STRING_H_STATE(notification->amsStateNotification.lastHAState));
            clLogNotice("EVT", "NTF", "New HA State : [%s]",
                      CL_AMS_STRING_H_STATE(notification->amsStateNotification.newHAState));
            
            /*
             * Get comps for the ha state
             */
            if(notification->amsStateNotification.newHAState == SA_AMF_HA_ACTIVE)
            {
                getComps(&notification->amsStateNotification.siName,
                         &notification->amsStateNotification.suName);
            }
            break;
        }
        /*
         * Fully assigned SI notification when SI is fully assigned
         * or when standby is assigned to SI with active assignments
         * making it redundant or available.
         */
    case CL_AMS_NOTIFICATION_SI_FULLY_ASSIGNED:
        {
            clLogNotice("EVT", "NTF", "Received SI [%s] event", CL_AMS_STRING_NTF(notification->type));
            clLogNotice("EVT", "NTF", "SI name : [%.*s]",
                      notification->amsStateNotification.siName.length,
                      notification->amsStateNotification.siName.value);
            clLogNotice("EVT", "NTF", "SU name : [%.*s]",
                      notification->amsStateNotification.suName.length,
                      notification->amsStateNotification.suName.value);
            clLogNotice("EVT", "NTF", "Last HA State : [%s]",
                      CL_AMS_STRING_H_STATE(notification->amsStateNotification.lastHAState));
            clLogNotice("EVT", "NTF", "New HA State : [%s]",
                      CL_AMS_STRING_H_STATE(notification->amsStateNotification.newHAState));

            break;
        }
        /*
         * Removal of SI assignment
         */
    case CL_AMS_NOTIFICATION_SI_UNASSIGNED:
        {
            clLogNotice("EVT", "NTF", "Received SI [%s] event", CL_AMS_STRING_NTF(notification->type));
            clLogNotice("EVT", "NTF", "SI name : [%.*s]",
                      notification->amsStateNotification.siName.length,
                      notification->amsStateNotification.siName.value);
            clLogNotice("EVT", "NTF", "SU name : [%.*s]",
                      notification->amsStateNotification.suName.length,
                      notification->amsStateNotification.suName.value);
            clLogNotice("EVT", "NTF", "Last HA State : [%s]",
                      CL_AMS_STRING_H_STATE(notification->amsStateNotification.lastHAState));
            clLogNotice("EVT", "NTF", "New HA State : [%s]",
                      CL_AMS_STRING_H_STATE(notification->amsStateNotification.newHAState));

            break;
        }
        /*
         * SU ha state change notifications with SI
         */
    case CL_AMS_NOTIFICATION_SU_HA_STATE_CHANGE:
        {
            clLogNotice("EVT", "NTF", "Received SU HA state change event");
            clLogNotice("EVT", "NTF", "SU name : [%.*s]",
                      notification->amsStateNotification.suName.length,
                      notification->amsStateNotification.suName.value);
            clLogNotice("EVT", "NTF", "SI name : [%.*s]",
                      notification->amsStateNotification.siName.length,
                      notification->amsStateNotification.siName.value);
            clLogNotice("EVT", "NTF", "Last HA State : [%s]",
                      CL_AMS_STRING_H_STATE(notification->amsStateNotification.lastHAState));
            clLogNotice("EVT", "NTF", "New HA State : [%s]",
                      CL_AMS_STRING_H_STATE(notification->amsStateNotification.newHAState));
            if(notification->amsStateNotification.newHAState == SA_AMF_HA_ACTIVE)
            {
                getComps(&notification->amsStateNotification.siName,
                         &notification->amsStateNotification.suName);
                getSlotFromSU(&notification->amsStateNotification.suName, NULL);
            }
            break;
        }

    case CL_AMS_NOTIFICATION_OPER_STATE_CHANGE:
        {
            clLogNotice("EVT", "NTF", "Received operational state [%s - %s] notification for type [%s] "
                      "entity [%.*s]", CL_AMS_STRING_O_STATE(notification->amsStateNotification.lastOperState),
                      CL_AMS_STRING_O_STATE(notification->amsStateNotification.newOperState),
                      CL_AMS_STRING_ENTITY_TYPE(notification->amsStateNotification.entityType),
                      notification->amsStateNotification.entityName.length,
                      notification->amsStateNotification.entityName.value);
        }
        break;

    case CL_AMS_NOTIFICATION_ADMIN_STATE_CHANGE:
        {
            clLogNotice("EVT", "NTF", "Received admin state [%s - %s] notification for type [%s] "
                      "entity [%.*s]", 
                      CL_AMS_STRING_A_STATE(notification->amsStateNotification.lastAdminState),
                      CL_AMS_STRING_A_STATE(notification->amsStateNotification.newAdminState),
                      CL_AMS_STRING_ENTITY_TYPE(notification->amsStateNotification.entityType),
                      notification->amsStateNotification.entityName.length,
                      notification->amsStateNotification.entityName.value);
        }
        break;

    case CL_AMS_NOTIFICATION_COMP_ARRIVAL:
        {
            clLogNotice ("EVT", "NTF", "Component arrival for [%.*s]",
                       notification->amsCompNotification.compName.length,
                       notification->amsCompNotification.compName.value);
            clLogNotice("EVT", "NTF", "Comp node [%.*s]", 
                      notification->amsCompNotification.nodeName.length,
                      notification->amsCompNotification.nodeName.value);

        }
        break;

    case CL_AMS_NOTIFICATION_COMP_DEPARTURE:
        {
            clLogNotice ("EVT", "NTF", "Component [%s] for [%.*s]",
                       notification->amsCompNotification.operation == CL_CPM_COMP_DEATH ?
                       "death" : "departure",
                       notification->amsCompNotification.compName.length,
                       notification->amsCompNotification.compName.value);
            clLogNotice("EVT", "NTF", "Comp node [%.*s]", 
                      notification->amsCompNotification.nodeName.length,
                      notification->amsCompNotification.nodeName.value);

        }
        break;
        
    case CL_AMS_NOTIFICATION_NODE_DEPARTURE:
        {
            if(notification->amsNodeNotification.operation == CL_CPM_NODE_DEPARTURE
               ||
               notification->amsNodeNotification.operation == CL_CPM_NODE_DEATH)
            {
                clLogNotice("EVT", "NTF", "Node [%s] for [%.*s], address [%d]",
                          notification->amsNodeNotification.operation == CL_CPM_NODE_DEPARTURE ?
                          "departure" : "death",
                          notification->amsNodeNotification.nodeName.length,
                          notification->amsNodeNotification.nodeName.value,
                          notification->amsNodeNotification.nodeIocAddress);
            }
        }
        break;

    default:
        {
            break;
        }
    }
    
    return CL_OK;
}

/*
 * clAmsNotificationInitialize sets up the notification.
 * Can be called by the comp. after saAmfInitialize for eg:
 */
ClRcT clAmsNotificationInitialize(void)
{
    ClRcT rc = CL_OK;
    static ClVersionT version = { 'B', 1, 1 };
    rc = clAmsMgmtInitialize(&mgmtHandle, NULL, &version);
    if(rc != CL_OK)
    {
        clLogError("NOTIF", "INIT", "Mgmt initialize returned with [%#x]", rc);
        return rc;
    }
    if((rc = clAmsClientNotificationInitialize(amsNotificationCallback) ) != CL_OK)
    {
        clLogWarning("EVT", "NTF", "AMF notification initialize returned with [%#x]", rc);
    }
    return rc;
}

/*
 * clAmsNotificationFinalize just finalizes it.
 * Can be called by the comp. in app terminate before saAmfResponse for eg:
 */
void clAmsNotificationFinalize(void)
{
    clAmsClientNotificationFinalize();
    if(mgmtHandle)
    {
        clAmsMgmtFinalize(mgmtHandle);
        mgmtHandle = 0;
    }
    if(notifJobPool.flags)
        clJobQueueDelete(&notifJobPool);
}

/*
 * Auxiliary function: get active comp given an SG
 */
ClRcT getCompsFromSG(ClAmsMgmtHandleT mgmtHandle, const ClNameT *sg)
{
    ClAmsEntityBufferT suBuffer = {0};
    ClAmsEntityBufferT compBuffer = {0};
    ClAmsCompCSIRefBufferT csiRefBuffer = {0};
    ClAmsEntityT targetEntity = {0};
    ClUint32T i;
    ClRcT rc = CL_OK;
    
    targetEntity.type = CL_AMS_ENTITY_TYPE_SG;
    clNameCopy(&targetEntity.name, sg);
    rc = clAmsMgmtGetSGAssignedSUList(mgmtHandle, &targetEntity, &suBuffer);
    if(rc != CL_OK)
    {
        clLogError("GET", "COMP", "SG [%s] assigned su list returned [%#x]",
                   targetEntity.name.value, rc);
        goto out;
    }

    for(i = 0; i < suBuffer.count; ++i)
    {
        ClUint32T j;
        ClAmsEntityT *su = suBuffer.entity + i;
        rc = clAmsMgmtGetSUCompList(mgmtHandle, su, &compBuffer);
        if(rc != CL_OK)
        {
            clLogError("GET", "COMP", "SU [%s] comp list returned [%#x]",
                       su->name.value, rc);
            goto out;
        }
        for(j = 0; j < compBuffer.count; ++j)
        {
            ClAmsEntityT *comp = compBuffer.entity + j;
            ClUint32T k;
            rc = clAmsMgmtGetCompCSIList(mgmtHandle, comp, &csiRefBuffer);
            if(rc != CL_OK)
            {
                clLogError("GET", "COMP", "Comp [%s] csi list returned [%#x]",
                           comp->name.value, rc);
                goto out;
            }
            for(k = 0; k < csiRefBuffer.count; ++k)
            {
                ClAmsCompCSIRefT *csiRef = csiRefBuffer.entityRef + k;
                if(csiRef->haState == CL_AMS_HA_STATE_ACTIVE
                   &&
                   csiRef->activeComp)
                {
                    clLogNotice("GET", "COMP", "CSI [%s] has active comp [%s]",
                                csiRef->entityRef.entity.name.value,
                                csiRef->activeComp->name.value);
                }
            }
            clAmsMgmtFreeCompCSIRefBuffer(&csiRefBuffer); /*frees csiRef->activeComp references,etc.*/
            csiRefBuffer.count = 0;
        }
        if(compBuffer.entity)
        {
            clHeapFree(compBuffer.entity);
            compBuffer.entity = NULL;
        }
        compBuffer.count = 0;
    }

    out:
    if(suBuffer.entity)
    {
        clHeapFree(suBuffer.entity);
    }
    if(compBuffer.entity)
    {
        clHeapFree(compBuffer.entity);
    }
    if(csiRefBuffer.entityRef)
    {
        clAmsMgmtFreeCompCSIRefBuffer(&csiRefBuffer);
    }
    return rc;
}

/*
 * Auxiliary function: Start a given SG. 
 * Tries to transition the sg admin state from locked_i to unlocked
 */
ClRcT amfSGStart(const ClCharT *name)
{
    ClRcT rc = CL_OK;
    ClAmsEntityT entity = {0};
    ClAmsSGConfigT *config = NULL;

    entity.type = CL_AMS_ENTITY_TYPE_SG;
    clNameSet(&entity.name, name);
    rc = clAmsMgmtEntityGetConfig(mgmtHandle, &entity, (ClAmsEntityConfigT**)&config);
    if(rc != CL_OK)
    {
        clLogError("ENTITY", "START", "SG [%s] get config returned with [%#x]", 
                   name, rc);
        goto out;
    }
    if(config->adminState == CL_AMS_ADMIN_STATE_UNLOCKED)
        goto out_free;

    switch(config->adminState)
    {
    case CL_AMS_ADMIN_STATE_LOCKED_I:
        rc = clAmsMgmtEntityLockAssignment(mgmtHandle, &entity);
        if(rc != CL_OK)
        {
            clLogNotice("ENTITY", "START", "[%s] locka returned with [%#x]",
                        name, rc);
            goto out_free;
        }
        /*
         * fall through
         */
    case CL_AMS_ADMIN_STATE_LOCKED_A:
        rc = clAmsMgmtEntityUnlock(mgmtHandle, &entity);
        if(rc != CL_OK)
        {
            clLogNotice("ENTITY", "START", "[%s] unlock returned with [%#x]",
                        name, rc);
            goto out_free;
        }
        break;
    default:
        break;
    }

    out_free:
    if(config)
        clHeapFree(config);

    out:
    return rc;
}

/*
 * Async version of amfSGStart.
 * Tries to transition the admin states of the SG from locked_i to unlocked
 * through a jobqueue/taskpool since the mgmtentitylock/unlock functions are 
 * synchronous
 */
static ClRcT sgStartAsync(ClPtrT arg);

ClRcT amfSGStartAsync(const ClCharT *name)
{
    ClRcT rc = CL_OK;
    static ClJobQueueT job;
    ClCharT *cloneSG = NULL;
    if(!job.flags)
    {
        rc = clJobQueueInit(&job, 0, 1);
        if(rc != CL_OK)
            return rc;
    }
    cloneSG = clStrdup(name);
    return clJobQueuePush(&job, sgStartAsync, (ClPtrT)cloneSG);
}
    
static ClRcT sgStartAsync(ClPtrT arg)
{
    ClCharT *sg = arg;
    ClRcT rc = amfSGStart(sg);
    clHeapFree(sg);
    return rc;
}

ClRcT getSlotFromSU(const SaNameT *su, ClIocNodeAddressT *slot)
{
    ClRcT rc = CL_OK;
    ClAmsSUConfigT *suConfig = NULL;
    ClAmsEntityT entity = {0};
    ClCpmSlotInfoT slotInfo = {0};

    if(slot)
        *slot = 0;
    entity.type = CL_AMS_ENTITY_TYPE_SU;
    clNameCopy(&entity.name, (const ClNameT*)su);
    rc = clAmsMgmtEntityGetConfig(mgmtHandle, &entity, (ClAmsEntityConfigT**)&suConfig);
    if(rc != CL_OK)
    {
        clLogError("SUS", "CONFIG", "SU [%.*s] get config returned [%#x]", su->length, su->value, rc);
        return rc;
    }
    clNameSet(&slotInfo.nodeName, suConfig->parentNode.entity.name.value);
    rc = clCpmSlotGet(CL_CPM_NODENAME, &slotInfo);
    if(rc != CL_OK)
    {
        clLogError("SUS", "SLOT", "Slot get for node [%s] returned [%#x]",
                   slotInfo.nodeName.value, rc);
    }
    else
    {
        if(slot)
        {
            *slot = slotInfo.nodeIocAddress;
        }
        else
        {
            clLogNotice("SUS", "SLOT", "Node [%s] on slot [%d]", 
                        slotInfo.nodeName.value, 
                        slotInfo.nodeIocAddress);
        }
    }
    clHeapFree(suConfig);
    return rc;
}
