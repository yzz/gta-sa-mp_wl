/***********************************
*                                 *
*   - Coded by:    ZeeX           *
*   - Version:     0.2.3          *
*   - Last update: 18/09/2009     *
*                                 *
***********************************/
 
#define ZCMD_NO_CALLBACK true 
 
#if defined _zcmd_included
        #endinput
#endif
#define _zcmd_included
 
#define MAX_COMM_FUNC_NAME (32)
 
#define zcmd(%1,%2,%3)               \
                        forward zcmd_%1(%2, %3); \
                        public zcmd_%1(%2, %3)

//add by GCS Team


#define rzcmd(%1) \
    return zcmd_%1(playerid,params)
#define pzcmd(%1) \
    zcmd(%1,playerid,params[])

#if !defined MAX_MSG_STR
    #define MAX_MSG_STR 128
#endif
   
new
	g_splitcmd[5][MAX_MSG_STR];
#define cmd_(%1) g_splitcmd[(%1)-1]
#define compare(%1,%2) !strcmp(%1,g_splitcmd[(%2)-1],true)
#define zcmd_advused() sscanf(params,"sssss",g_splitcmd[0],g_splitcmd[1],g_splitcmd[2],g_splitcmd[3],g_splitcmd[4])    
    
//
/*
#if !defined isnull
forward isnull(const params[]);
public isnull(const params[]){
    return  (params[0] == '\0' || params[0] == '\1');
}
#endif
*/

#if !defined isnull
        #define isnull(%1) \
                ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

 
 
#if !defined ZCMD_NO_CALLBACK
 
static
    gHasOPCT = false;
 
 
#if defined FILTERSCRIPT
 
public OnFilterScriptInit()
{
    if (funcidx("ZCMD_OnPlayerCommandText") != -1)
    {
        gHasOPCT = true;
    }
    return CallLocalFunction("ZCMD_OnFilterScriptInit", "");
}
 
#define OnFilterScriptInit ZCMD_OnFilterScriptInit
forward ZCMD_OnFilterScriptInit();
 
#else
 
public OnGameModeInit()
{
    if (funcidx("ZCMD_OnPlayerCommandText") != -1)
    {
        gHasOPCT = true;
    }
    return CallLocalFunction("ZCMD_OnGameModeInit", "");
}
 
#define OnGameModeInit ZCMD_OnGameModeInit
forward ZCMD_OnGameModeInit();
 
#endif
 
public OnPlayerCommandText(playerid, cmdtext[])
{
    if (gHasOPCT && CallLocalFunction("ZCMD_OnPlayerCommandText", "is", playerid, cmdtext))
    {
        g_splitcmd[0][0] = '\0';
        g_splitcmd[1][0] = '\0';
        g_splitcmd[2][0] = '\0';
        g_splitcmd[3][0] = '\0';
        g_splitcmd[4][0] = '\0';
        return 1;
    }
 
#else
 
ZCMD_ProcessCommand(playerid, cmdtext[])
{
 
#endif
 
    new
        pos,
        funcname[MAX_COMM_FUNC_NAME];
    //yezizhu:A bug here
    while (cmdtext[pos] && cmdtext[pos] != ' ') cmdtext[pos++] |= 0x20;
    //
    //while (cmdtext[pos] && cmdtext[pos] != ' ' && (cmdtext[pos] >= 'A' || cmdtext[pos] <= 'Z')) cmdtext[pos++] |= 0x20;
    if (!cmdtext[pos])
    {
        format(funcname, sizeof (funcname), "zcmd_%s", cmdtext[1]);
    }
    else
    {
        format(funcname, sizeof (funcname), "zcmd_%.*s", pos-1, cmdtext[1]);
        while (cmdtext[++pos] == ' ') {}
        if (cmdtext[pos])
        {
            g_splitcmd[0][0] = '\0';
            g_splitcmd[1][0] = '\0';
            g_splitcmd[2][0] = '\0';
            g_splitcmd[3][0] = '\0';
            g_splitcmd[4][0] = '\0';
            return CallLocalFunction(funcname, "is", playerid, cmdtext[pos]);
        }
    }
    g_splitcmd[0][0] = '\0';
    g_splitcmd[1][0] = '\0';
    g_splitcmd[2][0] = '\0';
    g_splitcmd[3][0] = '\0';
    g_splitcmd[4][0] = '\0';
    return CallLocalFunction(funcname, "is", playerid, "\1");
}
 
#if !defined ZCMD_NO_CALLBACK
 
#define OnPlayerCommandText ZCMD_OnPlayerCommandText
forward ZCMD_OnPlayerCommandText(playerid, cmdtext[]);
 
#endif




