
/*
	Amit's Teleports Manager filterscript
	------------------------------
	Programmer: Amit Barami "Amit_B"
	Creation Data: 19/1/2008
	Version: 1.0
	Compatibility: SanAndreas:MultiPlayer 0.2.2
*/

//=[IncludeFiles]===============================================================
#include <a_samp>
#include <gcs/gcs_uf>
//=[Defines]====================================================================
// TP:
#define TELEPORT_MANAGER_FS_STATE true							// TM Filterscript is ON?
#define FILE_NAME "tele.cfg"										// Name of file to write the teleports
// Messages:
#define DRIVER_MESSAGE "[传送]: 连人带车传送成功."	// Message for player driver
#define PASSENGER_MESSAGE "[传送]:只有司机才可以传送."	// Message for player passenger
#define ONFOOT_MESSAGE "[传送]: 传送成功."					// Message for player onfoot
#define ERROR_MESSAGE "TP: ERROR."								// Error message
#define HEALTH_MESSAGE "TP: You need more health to teleport."  // Health message
#define ALREADY_MESSAGE "[传送]:该传送命令已存在."     // Already have teleport message
//==========================
#define MAX_CMDS		(50000)
enum cmd_Info{
	cmd_Name[24],
	Float:cmd_x,
	Float:cmd_y,
	Float:cmd_z,
	Float:cmd_a,
	cmd_interior,
	cmd_virtualworld,
	cmd_lastusedtime
};
new 
	cmdInfo[MAX_CMDS][cmd_Info],
	cmd_Amount;
//=[Variables]==================================================================
new showmsg[MAX_PLAYERS];
//=[Forwards]===================================================================
forward ShowPlayerTMMessage(playerid);
//=[OnFilterScriptInit]=========================================================

loadCmd(){
	if(!fexist(FILE_NAME))fclose(fopen(FILE_NAME,io_write));
	new 
		File:ofile = fopen(FILE_NAME,io_read),
		wstr[256],
		idx,
		name,Float:x,Float:y,Float:z,Float:a,interior,virtualworld,lastusetime;
	while(fread(ofile,wstr)){
		if(!
		sscanf(wstr,"sffffiii",cmdInfo[idx][cmd_Name],cmdInfo[idx][cmd_x],cmdInfo[idx][cmd_y],cmdInfo[idx][cmd_z],cmdInfo[idx][cmd_a],cmdInfo[idx][cmd_interior],cmdInfo[idx][cmd_virtualworld],cmdInfo[idx][cmd_lastusedtime])){
			idx++;
			cmd_Amount++;
			
		}			
	}
	printf(" 玩家自制作传送命令载入成功,数量:%d.",cmd_Amount);
	fclose(ofile);
}

saveCmd(){
	if(!fexist(FILE_NAME))fclose(fopen(FILE_NAME,io_write));
	new 
		File:ofile = fopen(FILE_NAME,io_write),
		rstr[256];
			/*
				new
			deleteamount;
			*/
	for(new idx;idx < cmd_Amount;idx++){
		
		/*
		if(cmdInfo[idx][cmd_lastusedtime] < 20100000){
			printf("deleted:%s %f %f %f %f %i %i %i",deleteamount,cmdInfo[idx][cmd_Name],cmdInfo[idx][cmd_x],cmdInfo[idx][cmd_y],cmdInfo[idx][cmd_z],cmdInfo[idx][cmd_a],cmdInfo[idx][cmd_interior],cmdInfo[idx][cmd_virtualworld],cmdInfo[idx][cmd_lastusedtime]);
			deleteamount++;
			continue;
		}
		*/
		
		format(rstr,sizeof(rstr),"%s %f %f %f %f %i %i %i\r\n",cmdInfo[idx][cmd_Name],cmdInfo[idx][cmd_x],cmdInfo[idx][cmd_y],cmdInfo[idx][cmd_z],cmdInfo[idx][cmd_a],cmdInfo[idx][cmd_interior],cmdInfo[idx][cmd_virtualworld],cmdInfo[idx][cmd_lastusedtime]);
		gini_fwrite(ofile,rstr);
	}
	/*
	printf("Delete %d commands.",deleteamount);
	*/
	fclose(ofile);
}

public OnFilterScriptInit()
{
	print("\n\n====== [ Teleports Manager filterscript v0.2 ]  ======\n");
	print("  Programmer: Amit Barami \"Amit_B\"");
	print("  Creation Date: 19/1/2008");
	print("  Version: 1.0");
	print("  Compatibility: SanAndreas:MultiPlayer 0.2.2");
	if(!fexist(FILE_NAME))
	{
		new File:tm;
		tm = fopen(FILE_NAME,io_write);
		fclose(tm);
	}
	loadCmd();
	print("  Teleports Manager filterscript *Loaded*!");
	print("\n======================================================\n");
	/*
	SendClientMessageToAll(0x993300AA,"Teleports Manager help:");
	SendClientMessageToAll(0x00EEADDF,"Programmer: Amit Barami \"Amit_B\"");
	SendClientMessageToAll(0x00EEADDF,"Creation Date: 19/1/2008");
	SendClientMessageToAll(0x00EEADDF,"Version: 1.0");
	SendClientMessageToAll(0x00EEADDF,"Compatibility: SanAndreas:MultiPlayer 0.2.2");
	SendClientMessageToAll(0x00EEADDF,"Commands: /tm /setteleport /rteleports");
	*/
	return 1;
}
//=[OnFilterScriptExit]=========================================================
public OnFilterScriptExit()
{
	print("\n\n====== [ Teleports Manager filterscript v0.2 ]  ======\n");
	print("  Programmer: Amit Barami \"Amit_B\"");
	print("  Creation Date: 19/1/2008");
	print("  Version: 1.0");
	print("  Compatibility: SanAndreas:MultiPlayer 0.2.2");

	print("  Teleports Manager filterscript *UnLoaded*!");
	print("\n======================================================\n");
	saveCmd();
	return 1;
}
//=[OnPlayerConnect]============================================================
/*public OnPlayerConnect(playerid)
{
	showmsg[playerid] = SetTimerEx("ShowPlayerTMMessage",2000,1,"i",playerid);
	return 1;
}*/
//=[OnPlayerCommandText]========================================================
public OnPlayerCommandText(playerid, cmdtext[])
{
	//print("hi")
	new cmdtexts[128], idx;
	cmdtexts = strtok(cmdtext,idx);

	if(!strcmp(cmdtext,"/help tele",true))
	{
		SendClientMessage(playerid,0xFFFF00FF,"[自制命令]帮助:输入/vmake 自制传送命令");
		return true;
	}
	if(!strcmp(cmdtexts,"/vmake",true) || !strcmp(cmdtexts,"/maketele",true) || !strcmp(cmdtexts,"/chuansongtianjia",true) || !strcmp(cmdtexts,"/cstj",true))
	{
		new telecmd[256], File:tmfile, wstring[256], tmp[256], already[256];
		//if(!IsPlayerAdmin(playerid)) {return 1;} 不允许非GM创建命令
		if(!fexist(FILE_NAME))
		{
			tmfile = fopen(FILE_NAME,io_write);
			fclose(tmfile);
		}
		telecmd = strtok(cmdtext,idx);
		if(!strlen(telecmd))
		{
			SendClientMessage(playerid,0xFFFFFFAA,"[自制传送]使用方法: /vmake [传送名称(不用带'/')]");
			return 1;
		}
		tmfile = fopen(FILE_NAME,io_read);
		while(fread(tmfile,tmp))
		{
		    idx = 0;
			already = strtok(tmp,idx);
			if(!strcmp(already,telecmd,true))
			{
	    		SendClientMessage(playerid,0xAA3333AA,ALREADY_MESSAGE);
			    return 1;
			}
		}
		fclose(tmfile);
		new
			cmd = cmd_Amount,
			tmpdate[4];
		cmd_Amount++;
		format(cmdInfo[cmd][cmd_Name],128,"%s",telecmd);
		cmdInfo[cmd][cmd_interior] = GetPlayerInterior(playerid);
		cmdInfo[cmd][cmd_virtualworld] = GetPlayerVirtualWorld(playerid);
		GetPlayerPos(playerid,cmdInfo[cmd][cmd_x],cmdInfo[cmd][cmd_y],cmdInfo[cmd][cmd_z]);
		GetPlayerFacingAngle(playerid,cmdInfo[cmd][cmd_a]);
		tmfile = fopen(FILE_NAME,io_append);
		getdate(tmpdate[0],tmpdate[1],tmpdate[2]);
		tmpdate[3] = tmpdate[0]*10000+tmpdate[1]*100+tmpdate[2];
		format(wstring,sizeof(wstring),"%s %f %f %f %f %d %d %d\r\n",cmdInfo[cmd][cmd_Name],cmdInfo[cmd][cmd_x],cmdInfo[cmd][cmd_y],cmdInfo[cmd][cmd_z],cmdInfo[cmd][cmd_a],cmdInfo[cmd][cmd_interior],cmdInfo[cmd][cmd_virtualworld],tmpdate[3]);
		gini_fwrite(tmfile,wstring);
		fclose(tmfile);
		format(wstring,sizeof(wstring),"[传送] '//%s' 传送命令创建成功.坐标: %f %f %f.",cmdInfo[cmd][cmd_Name],cmdInfo[cmd][cmd_x],cmdInfo[cmd][cmd_y],cmdInfo[cmd][cmd_z]);
		SendClientMessage(playerid,0xFF0000FF,wstring);
		return 1;
	}

	if(!strcmp(cmdtext,"/vvgtele",true))
	{
		if(!IsPlayerAdmin(playerid))return true;
	    new File:rf;
	    fremove(FILE_NAME);
	    rf = fopen(FILE_NAME,io_write);
	    fclose(rf);
		SendClientMessage(playerid,0x33AA33AA,"TM: Teleports has been reseted.");
		return 1;
	}
	
	if(cmdtext[0] == '/' && cmdtext[1] == '/' && cmdtext[2]){
		for(new i;i< cmd_Amount;i++){
			if(!strcmp(cmdtext[2],cmdInfo[i][cmd_Name],true)){
				new
					tmpdate[3],
					gt[128];
				getdate(tmpdate[0],tmpdate[1],tmpdate[2]);
				cmdInfo[i][cmd_lastusedtime] = tmpdate[0]*10000+tmpdate[1]*100+tmpdate[2];			
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
					SetVehicleVirtualWorld(GetPlayerVehicleID(playerid),cmdInfo[i][cmd_virtualworld]);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid),cmdInfo[i][cmd_interior]);
					SetVehiclePos(GetPlayerVehicleID(playerid),cmdInfo[i][cmd_x],cmdInfo[i][cmd_y],cmdInfo[i][cmd_z]);
					SetVehicleZAngle(GetPlayerVehicleID(playerid),cmdInfo[i][cmd_a]);
					//format(gt,sizeof(gt),"~>~~y~%s~<~",cmdtext[1]);
					//GameTextForPlayer(playerid,gt,3000,4);
					format(gt,sizeof(gt),"[传送]你传送到'%s'",cmdtext);
					SendClientMessage(playerid,0xFFFF00FF,gt);
				}
				else if(GetPlayerState(playerid) == PLAYER_STATE_PASSENGER)
				{
					SendClientMessage(playerid,0xFFFF00FF,PASSENGER_MESSAGE);
				}
				else if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				{
					SetPlayerPos(playerid,cmdInfo[i][cmd_x],cmdInfo[i][cmd_y],cmdInfo[i][cmd_z]);
					SetPlayerFacingAngle(playerid,cmdInfo[i][cmd_a]);
					SetPlayerInterior(playerid,cmdInfo[i][cmd_interior]);
					//SetPlayerVirtualWorld(playerid,cmdInfo[i][cmd_virtualworld]);
					//format(gt,sizeof(gt),"~>~~y~%s~<~",cmdtext[1]);
					//GameTextForPlayer(playerid,gt,3000,4);
					format(gt,sizeof(gt),"[传送]你传送到'%s'",cmdtext);
					SendClientMessage(playerid,0xFFFF00FF,gt);
				}
				else
				{
					SendClientMessage(playerid,0xFFFF00FF,ERROR_MESSAGE);

				}
				return 1;
			}
		}
		SendClientMessage(playerid,0xFFFF00FF,"[传送]你输入的存送命令不存在");
		return true;
	}
	return 0;
}
//=[ShowPlayerTMMessage]========================================================
public ShowPlayerTMMessage(playerid)
{
	SendClientMessage(playerid,0xFFFF00FF,"查看所有传送命令输入 /teles.");
	KillTimer(showmsg[playerid]);
	return 1;
}



public OnGameModeInit(){
	return true;
}
public OnGameModeExit(){
	return true;
}

public OnPlayerConnect(playerid){
	return true;
}
public OnPlayerDisconnect(playerid, reason){
	return true;
}
public OnPlayerSpawn(playerid){
	return true;
}
public OnPlayerDeath(playerid, killerid, reason){
	return true;
}
public OnVehicleSpawn(vehicleid){
	return true;
}
public OnVehicleDeath(vehicleid, killerid){
	return true;
}
public OnPlayerText(playerid, text[]){
	return true;
}


public OnPlayerRequestClass(playerid, classid){
	return true;
}
public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger){
	return true;
}
public OnPlayerExitVehicle(playerid, vehicleid){
	return true;
}
public OnPlayerStateChange(playerid, newstate, oldstate){
	return true;
}
public OnPlayerEnterCheckpoint(playerid){
	return true;
}
public OnPlayerLeaveCheckpoint(playerid){
	return true;
}
public OnPlayerEnterRaceCheckpoint(playerid){
	return true;
}
public OnPlayerLeaveRaceCheckpoint(playerid){
	return true;
}
public OnRconCommand(cmd[]){
	return true;
}
public OnPlayerRequestSpawn(playerid){
	return true;
}
public OnObjectMoved(objectid){
	return true;
}
public OnPlayerObjectMoved(playerid, objectid){
	return true;
}
public OnPlayerPickUpPickup(playerid, pickupid){
	return true;
}
public OnVehicleMod(playerid, vehicleid, componentid){
	return true;
}
public OnVehiclePaintjob(playerid, vehicleid, paintjobid){
	return true;
}
public OnVehicleRespray(playerid, vehicleid, color1, color2){
	return true;
}
public OnPlayerSelectedMenuRow(playerid, row){
	return true;
}
public OnPlayerExitedMenu(playerid){
	return true;
}
public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid){
	return true;
}
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
	return true;
}
public OnPlayerUpdate(playerid){
	return true;
}

