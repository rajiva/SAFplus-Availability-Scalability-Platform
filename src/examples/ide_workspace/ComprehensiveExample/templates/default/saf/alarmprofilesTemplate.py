from string import Template

mainTemplate = Template("""\
/******************************************************************************
 *
 * cl${compName}alarmMetaStruct.c
 *
 ******************************************************************************
 * This code is auto-generated by OpenClovis IDE @Version 3.1
 *
 *****************************************************************************/
#include <clAlarmDefinitions.h>
#include <clCorMetaData.h>
#include <clCorMetaStruct.h>

${alarmRulesTables}
${alarmProfilesTables}
ClAlarmComponentResAlarmsT appAlarms [] = 
{
${compAlarms}
    {0,0,NULL}
};

""")

compAlarmTemplate = Template("""\
    {${className}, ${pollingInterval}, Cl${profileTableName}},  
""")

alarmProfileTableTemplate = Template("""\
ClAlarmProfileT Cl${profileTableName} [] =
{
${alarmProfiles}
    {CL_ALARM_CATEGORY_INVALID,CL_ALARM_ID_INVALID,CL_ALARM_SEVERITY_INVALID,CL_ALARM_REPORT,0,0,NULL,NULL} 
};
""")

alarmProfileTemplate = Template("""\
    {
        ${category},
        ${probableCauseName},
        ${severity},
        CL_ALARM_REPORT,
        ${assertSoakingTime},
        ${clearSoakingTime},
        ${genRuleTableName},
        ${suppressRuleTableName},
        ${specificProblem}
    },
""")

generationRuleTableTemplate = Template("""\
ClAlarmRuleInfoT Cl${genRuleTableName} [] =
{
${genRules}
    {CL_ALARM_RULE_NO_RELATION, NULL}
};
""")

generationRuleTemplate = Template("""\
    {${genRuleRelationName}, Cl${ruleIDsTableName}},
""")

ruleIDTableTemplate = Template("""\
ClAlarmRuleEntryT Cl${ruleIDsTableName} [] =
{
${ruleIDs}
};
""")

ruleIDTemplate = Template("""\
    {${ruleID}, ${specificProblem}},
""")
