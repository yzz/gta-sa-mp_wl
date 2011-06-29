/*
								The MIT License  
								
	Copyright (c) <2010> <yezizhu>  
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:  

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.  
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.  
	==================================
	版权(c) <2010> <yezizhu>  

	使用该许可证的软件被授予以下权限，免费，任何人可以得到这个软件及其相关文档的一个拷贝，
	并且经营该软件不受任何限制，包括无限制的使用、复制、修改、合并、出版、发行、发放从属证书、或者出售该软件的拷贝的权利。
	同时允许获得这些软件的用户享受这些权利，使其服从下面的条件：  
	
	以上的版权通知和权限通知应该包含在所有该软件的拷贝中或者是其他该软件的真实部分中。
	
	该软件按本来的样子提供，没有任何形式的担保，不管是明确地或者暗含的，包含这些但是不受商业性质的担保的限制。
	适合一个特定的用途并且不受侵犯。作者和版权持有人在任何场合对使用该软件涉及的任何要求、损害或者其他责任都不应负责。
	不管它是正在起作用还是只是合同形式、民事侵权或是其他方式，如由它引起，在其作用范围内、与该软件有联系、该软件的使用或者有这个软件引起的其他行为。  
	=====================================   
*/	

#if defined wl_main
	#endinput
#endif
#define wl_main


#include <a_samp>


#include <gvar>
#include <fileExt>






#if defined MAX_STRING
	#undef MAX_STRING
	#define MAX_STRING					(128)
#else
	#define MAX_STRING					(128)
#endif
#if defined MAX_NAME
	#undef MAX_NAME
#endif
#define MAX_NAME						(MAX_PLAYER_NAME)



new const stock bool:FALSE=false;
new const stock bool:TRUE=true;
#define COLOR_GREY				(0xD3D3D3AA)
#define COLOR_LIGHTBLUE			(0x00BFFFAA)
#define COLOR_ULTRARED			(0xFF0606FF)
#define COLOR_PURPLE			(0x9900FFAA)
#define COLOR_GREEN				(0x33AA33AA)
#define COLOR_YELLOW			(0xFFFFE0AA)
#define COLOR_ORANGE			(0xFFA500AA)
#define COLOR_RED				(0xFF0000AA)
#define COLOR_SYSTEM			(0xEFEFF7AA)
#define COLOR_ZONE_DM			(COLOR_LIGHTBLUE)
#define COLOR_WARNING			(COLOR_ULTRARED)
#define COLOR_TIP				(COLOR_LIGHTBLUE)
#define COLOR_STUDY				(COLOR_YELLOW)

//===================System handle==================================
new
	ssstr[MAX_MSG_STR];
#define System_send(%1,%2,%3)	\
do{ \
	format(ssstr,MAX_STRING,(%2),%3); \
	SendClientMessage((%1),COLOR_SYSTEM,ssstr); \
}while(FALSE)
stock System_send(playerid,const sendfstring[]){
	SendClientMessage(playerid,COLOR_SYSTEM,sendfstring);
}

#define System_sendAll(%1,%2)	\
do{ \
	format(ssstr,MAX_STRING,(%1),%2); \
	SendClientMessageToAll(COLOR_SYSTEM,ssstr); \
}while(FALSE)
stock System_sendAll(const sendfstring[]){
	SendClientMessageToAll(COLOR_SYSTEM,sendfstring);
}

//===================================================================================

#include <gcs\gcs_uf>
#include <wl/wl_rulebreak_detect>
#include <gcs/gcs_main>
#include <gcs/gcs_ini_fsload>





//#include <gcs/gcs_ini>
//#include <gcs/ini/gcs_ini_struct>
#include <NPatcher>
#include <zcmd>
#include <streamer>
//#include <Y_Objects>
//#include <F_Streamer>
#include <ecode>
//#include <SII>
//#include <wl/wl_cmd>
//#include <dfile/dini>
//#include <wl/database>


#define playerfile				"wl/player/"
#define acc_pName				"playerName"
#define acc_pPass				"playerPassword"
#define acc_pLevel				"playerTeamLevel"

#define acc_pVWLog_tank_times				"pPM_tank_times"
#define acc_pVWLog_tank_score				"pPM_tank_score"
#define acc_pVWLog_spaz_times				"pPM_spaz_times"
#define acc_pVWLog_spaz_score				"pPM_spaz_score"
#define acc_pVWLog_minigun_times			"pPM_minigun_times"
#define acc_pVWLog_minigun_score			"pPM_minigun_score"
#define acc_pVWLog_quanquan_times			"pPM_quanquan_times"
#define acc_pVWLog_quanquan_score			"pPM_quanquan_score"


#define racefile					"wl/race/"
#define raceNamefile				"race.list"
#define data_race_Name				"raceName"
#define data_race_Description		"raceDescription"
#define data_race_Builder			"raceBuilder"
#define data_race_Password			"racePassword"
#define data_race_RaceTimes			"raceRaceTimes"
#define data_race_LastRunDate		"raceLastRunDate"
#define data_race_Interior			"raceInterior"
#define data_race_Distance			"raceDistance"
#define data_race_cp				"racecp"
#define data_race_cpAmount			"racecpAmount"
#define data_race_cpPosX			"racecpPosX"
#define data_race_cpPosY			"racecpPosY"
#define data_race_cpPosZ			"racecpPosZ"
#define data_race_cpSize			"racecpSize"
#define data_race_cpType			"racecpType"
#define data_race_cpAngel			"racecpAngel"
#define data_race_winnerinfo		"racewinnerinfo"


#define MAX_WEAPON_SLOT	(13)


//====//mode_Gang&Group
stock wl_sPlr_Group_Invited(playerid,set){
	SetPVarInt(playerid,"wl_plr_main_Group_Invited",set);
	return true;
}
stock wl_gPlr_Group_Invited(playerid){
	return GetPVarInt(playerid,"wl_plr_main_Group_Invited");
}

stock wl_sPlr_Group_Joined(playerid,set){
	SetPVarInt(playerid,"wl_plr_main_Group_Joined",set);
	return true;
}
stock wl_gPlr_Group_Joined(playerid){
	return GetPVarInt(playerid,"wl_plr_main_Group_Joined");
}

stock wl_sPlr_Group_requestTele(playerid,set){
	SetPVarInt(playerid,"wl_plr_main_Group_requestTele",set);
	return true;
}
stock wl_gPlr_Group_requestTele(playerid){
	return GetPVarInt(playerid,"wl_plr_main_Group_requestTele");
}

stock wl_sPlr_Group_requester(playerid,set){
	SetPVarInt(playerid,"wl_plr_main_Group_requester",set);
	return true;
}
stock wl_gPlr_Group_requester(playerid){
	return GetPVarInt(playerid,"wl_plr_main_Group_requester");
}
//============================
	/*
	//mode_GunDM
	GunDM_PlayerIn,
	GunDM_PlayerSwitchWeapon[MAX_WEAPON_SLOT],
	//mode_TDM
	TDM_Package,
	TDM_VoteFor,
	TDM_In,
	TDM_Spawn_Time,
	TDM_Score,
	*/
//mode_DM
stock wl_sPlr_DM_PlayerIn(playerid,set){
	SetPVarInt(playerid,"wl_plr_main_DM_PlayerIn",set);
	return true;
}
stock wl_gPlr_DM_PlayerIn(playerid){
	return GetPVarInt(playerid,"wl_plr_main_DM_PlayerIn");
}

stock wl_sPlr_PDM_PlayerKill(playerid,set){
	SetPVarInt(playerid,"wl_plr_main_PDM_PlayerKill",set);
	return true;
}
stock wl_gPlr_PDM_PlayerKill(playerid){
	return GetPVarInt(playerid,"wl_plr_main_PDM_PlayerKill");
}

stock wl_sPlr_PDM_PlayerDeath(playerid,set){
	SetPVarInt(playerid,"wl_plr_main_PDM_PlayerDeath",set);
	return true;
}
stock wl_gPlr_PDM_PlayerDeath(playerid){
	return GetPVarInt(playerid,"wl_plr_main_PDM_PlayerDeath");
}

//====================
//template_forcespam
stock wl_sPlr_forceSpaming(playerid,set){
	SetPVarInt(playerid,"wl_plr_main_forceSpaming",set);
	return true;
}
stock wl_gPlr_forceSpaming(playerid){
	return GetPVarInt(playerid,"wl_plr_main_forceSpaming");
}
//=============
/*
	//template_lang_system
	lang_Player,
*/
//template_other
stock wl_sPlr_Player_Skin(playerid,set){
	SetPVarInt(playerid,"wl_plr_main_Player_Skin",set);
	return true;
}
stock wl_gPlr_Player_Skin(playerid){
	return GetPVarInt(playerid,"wl_plr_main_Player_Skin");
}
//===================
//other
stock wl_sPlr_ppos_x(playerid,Float:set){
	SetPVarFloat(playerid,"wl_plr_main_ppos_x",set);
	return true;
}
stock Float:wl_gPlr_ppos_x(playerid){
	return GetPVarFloat(playerid,"wl_plr_main_ppos_x");
}

stock wl_sPlr_ppos_y(playerid,Float:set){
	SetPVarFloat(playerid,"wl_plr_main_ppos_y",set);
	return true;
}
stock Float:wl_gPlr_ppos_y(playerid){
	return GetPVarFloat(playerid,"wl_plr_main_ppos_y");
}

stock wl_sPlr_ppos_z(playerid,Float:set){
	SetPVarFloat(playerid,"wl_plr_main_ppos_z",set);
	return true;
}
stock Float:wl_gPlr_ppos_z(playerid){
	return GetPVarFloat(playerid,"wl_plr_main_ppos_z");
}

stock wl_sPlr_ppos_angle(playerid,Float:set){
	SetPVarFloat(playerid,"wl_plr_main_ppos_angle",set);
	return true;
}
stock Float:wl_gPlr_ppos_angle(playerid){
	return GetPVarFloat(playerid,"wl_plr_main_ppos_angle");
}




//=========================


	

//DEBUG
new
	const logname[] = "wl/debug_log";
#define writetolog(%0,%1) \
do{ \
	new \ 
		logstring[128]; \
	format(logstring,sizeof(logstring),(%0),%1); \
	new \
		File:append_Log = fopen(logname,io_append); \
	fwrite(append_Log,logstring); \
	fwrite(append_Log,"\r\n"); \
	fclose(append_Log); \
}while(FALSE)
stock writetolog(const logstring[]){
	new
		File:append_Log = fopen(logname,io_append);
	fwrite(append_Log,logstring);
	fwrite(append_Log,"\r\n");
	fclose(append_Log);
}
//=====================================================================================================
stock GetPlayerAdminLevel(playerid){
	return CallRemoteFunction("GetPlayerAdminLevel","i",playerid);
}










#include <wl\wl_lang>

//#include <wl\wl_subaccount>
#include <wl\wl_account>
#include <wl\wl_objective>
#include <wl\wl_template>
#include <wl\wl_mode>
#include <wl\wl_ruleop>






wl_GameModeInit(){
	AntiDeAMX();
//	mode_protection();
//	Srm_OnGameModeInit();
	//mode_introduction();
	gcs_GameModeInit();
	wl_lang_OnGameModeInit();
	acc_OnGameModeInit();
	wl_objective_GameModeInit();
	wl_tmp_GameModeInit();
	wl_mode_Struction();
	wl_ruleop_struction();
	return true;
}

wl_GameModeExit(){
	wl_mode_UnStruction();
	return true;
}

wl_PlayerRequestClass(playerid,classid){
	wl_objective_RequestClass(playerid, classid);
	return true;
}

wl_PlayerConnect(playerid){
//	Srm_OnPlayerConnect(playerid);
	gcs_PlayerConnect(playerid);
	wl_lang_OnPlayerConnect(playerid);
	acc_OnPlayerConnect(playerid);
	//sb_playerConnect(playerid);
	wl_tmp_PlayerConnect(playerid);
	wl_mode_PlayerConnect(playerid);
	//account_playerConnect(playerid);
	rp_playerConnect(playerid);
	return true;
}

wl_PlayerDisconnect(playerid,reason){
//	Srm_OnPlayerDisconnect(playerid,reason);
	gcs_PlayerDisconnect(playerid,reason);
	acc_OnPlayerDisconnect(playerid);
	//Object_OnPlayerDisconnect(playerid,reason);
	//sb_playerDisconnect(playerid);
	wl_tmp_PlayerDisconnect(playerid);
	wl_mode_PlayerDisconnect(playerid,reason);
	//account_playerDisconnect(playerid);
	rp_playerDisconnect(playerid);
	return true;
}

wl_PlayerRequestSpawn(playerid){
	wl_tmp_PlayerRequestSpawn(playerid);
	return true;
}

wl_PlayerSpawn(playerid){
	detect_playerSpawn(playerid);
	//sb_playerSpawn(playerid);
	wl_tmp_PlayerSpawn(playerid);
	wl_ruleop_playerSpawn(playerid);
	if(PDM_getPlayerDM(playerid) != INVALID_PDM_ID){
		wl_mode_PlayerSpawn(playerid);
	}
	dmw:playerSpawn(playerid);
	if(PDM_getPlayerDM(playerid) == INVALID_PDM_ID && GetPlayerVirtualWorld(playerid) == 0){
		GivePlayerWeapon(playerid,23,17 * 100);
		GivePlayerWeapon(playerid,43,9999);
		GivePlayerWeapon(playerid,WEAPON_KATANA,1);
		SetPlayerHealth(playerid,99999);
		wl_objective_SpawnPlayer(playerid);
	}
}

wl_PlayerDeath(playerid,killerid,reason){
	gcs_PlayerDeath(playerid,killerid,reason);
	wl_ruleop_PlayerDeath(playerid, killerid, reason);
	wl_tmp_PlayerDeath(playerid,killerid);
	wl_mode_PlayerDeath(playerid,killerid,reason);
	return true;
}

wl_PlayerPrivmsg(playerid,recieverid,text[]){
	if(wl_tmp_PlayerPrivmsg(playerid,recieverid,text))return true;
	return false;
}

wl_PlayerText(playerid,text[]){
	wl_tmp_playerText(playerid);
	if(!wl_mode_PlayerText(playerid,text)) return true;
	if(wl_tmp_PlayerText(playerid,text))return true;
	return false;
}

wl_CommandText(playerid,cmdtext[]){
	
	//gcs_CommandText(playerid,cmdtext);
	wl_tmp_playerCommandText(playerid);
	if(/*wl_objective_CommandText(playerid,cmdtext) || */wl_mode_CommandText(playerid,cmdtext)) return true;
	return false;
}

wl_PlayerSelectedMenuRow(playerid,row){
	gcs_PlayerSelectedMenu(playerid);
	if(wl_mode_PlayerSelectedMenuRow(playerid,row))return true;
	return false;
}

wl_PlayerExitedMenu(playerid){
	gcs_PlayerExitedMenu(playerid);
	wl_mode_PlayerExitedMenu(playerid);
	return true;
}

wl_PlayerStateChange(playerid,newstate,oldstate){
	wl_tmp_playerStateChange(playerid);
	wl_mode_PlayerStateChange(playerid,newstate,oldstate);
	return true;
}

wl_KeyStateChange(playerid,newkeys,oldkeys){
	wl_tmp_playerKeyStateChange(playerid);
	wl_mode_KeyStateChange(playerid,newkeys,oldkeys);
	wl_mode_PlayerKeyStateChange(playerid,newkeys,oldkeys);
	return true;
}

wl_DialogResponse(playerid, dialogid, response, listitem, inputtext[]){
	wl_mode_DialogResponse(playerid, dialogid, response, listitem, inputtext);
	wl_tmp_DialogResponse(playerid, dialogid, response, listitem, inputtext);
}

wl_EnterCheckpoint(playerid){
	wl_mode_EnterCheckpoint(playerid);
}

wl_EnterRaceCheckpoint(playerid){
	wl_mode_EnterRaceCheckpoint(playerid);
	return true;
}

wl_PlayerUpdate(playerid){
	
	detect_PlayerUpdate(playerid);
	wl_tmp_PlayerUpdate(playerid);
	return true;
}
	
wl_PlayerClickPlayer(playerid, clickedplayerid, source){
	#pragma unused playerid,clickedplayerid,source
	//account_PlayerClickPlayer(playerid, clickedplayerid, source);
	return true;
}






//=========================================================================================



























		




Marker_struct(){
	SetTimer("Marker_itter",2046,true);
	
}
forward Marker_itter();
public Marker_itter(){  debug_public_track("Marker_itter(){ ");//todo: high bandwidth use
	new
		tranprancy[32];
	loopPlayer(playerid){
		loopPlayer(showplayerid){
			if(showplayerid < playerid){	
				continue;
			}
			#if WL_DMWorld
			if(dmw:getPlayer(playerid) && dmw:getPlayer(showplayerid)){
				dmw:MarkerProcess(playerid,showplayerid); 
			}
			#endif
			else { 
				//if(getDisBetweenPlayer(playerid,showplayerid) < 350){
					format(tranprancy,sizeof(tranprancy),"%.f",255-getDisBetweenPlayer(playerid,showplayerid) * 0.35);
					p_setMarkerTransparency(showplayerid,playerid,strval(tranprancy));
					p_setMarkerTransparency(playerid,showplayerid,strval(tranprancy));
				//}
			}
		}
	}
}


public OnGameModeInit(){ debug_public_track("OnGameModeInit(){");

	
	{
		//temp set
		if(!fexist("wl/do_not_delete.wl")){ //clean database
			fcreate("wl/do_not_delete.wl");
			fremove("wl/DMWorld/dmworld.db");
			fremove("wl/user.db");
			/*
			{
				db_processstart("DELETE TABLE gang_stat;DELETE TABLE zone;DELETE TABLE dmw_blacklist;DELETE TABLE dmw_admin");
				db_processthenfree(db_dmworld);
			}
			{
				db_processstart("DELETE TABLE player_account");
				db_processthenfree(db_user);			
			}
			*/
		}
	}

	//SendRconCommand("loadfs gcs_ini");
	
	wl_GameModeInit();
	SetGameModeText("0.3赛车/旅游/特技/DM");
	UsePlayerPedAnims();
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_GLOBAL);
	Marker_struct();
	//LimitPlayerMarkerRadius(440);
	SetNameTagDrawDistance(40);
	
	
	SendRconCommand("loadfs tele");
	SendRconCommand("loadfs spectate");
	SendRconCommand("loadfs Seifanims");
	SendRconCommand("loadfs drift");
	SendRconCommand("loadfs tunecar");
	
	SetTimer("autoRestart",1111*45,true);
	return true;
}
public OnGameModeExit(){ debug_public_track("OnGameModeExit(){");
	
	SendRconCommand("unloadfs gcs_ini");
	SendRconCommand("unloadfs tele");
	SendRconCommand("unloadfs spectate");
	SendRconCommand("unloadfs Seifanims");
	SendRconCommand("unloadfs drift");
	SendRconCommand("unloadfs tunecar");
	wl_GameModeExit();
	
	return true;
}
public OnFilterScriptInit(){ debug_public_track("OnFilterScriptInit(){");
//	Srm_OnFilterScriptInit();
	return true;
}
public OnFilterScriptExit(){ debug_public_track("OnFilterScriptExit(){");
	return true;
}
public OnPlayerConnect(playerid){ debug_public_track("OnPlayerConnect(playerid){");
	System_sendAll("[系统]欢迎玩家%s(%d)进入服务器^^ ",pName(playerid),playerid);

	GivePlayerMoney(playerid,999999);
	wl_PlayerConnect(playerid);
	System_send(playerid,"[系统]欢迎来到未来世界，在本服务器可以输入 - /c - 刷车, - /tunecar - 改车， - /r s - 赛车");
	System_send(playerid,"[系统]欢迎来到未来世界，在本服务器可以输入 - /wuqi - 购买武器, /dm [id] - 加入DM。");
	//System_send(playerid,"[系统]大战城 输入/dmw enter进入大战城,/dmw attack抢夺地盘 - 开放时间:19:00 - 22:00");
	System_send(playerid,"[系统]更多帮助请见/help或登陆help.gtaip.com 查看(版权信息 - /wl)");	
	return true;
}



public OnPlayerDisconnect(playerid, reason){ debug_public_track("OnPlayerDisconnect(playerid, reason){");
	switch(reason){
		case 0:System_sendAll("[系统]玩家%s(%d)掉线了",pName(playerid),playerid);
		case 1:System_sendAll("[系统]玩家%s(%d)下线了",pName(playerid),playerid);
		case 2:System_sendAll("[系统]玩家%s(%d)被赶出了服务器",pName(playerid),playerid);
	}
	wl_PlayerDisconnect(playerid,reason);

	return true;
}

public OnPlayerSpawn(playerid){ debug_public_track("OnPlayerSpawn(playerid){");
	
	//GivePlayerWeapon(playerid,WEAPON_PARACHUTE,1);
	//sb_useGodmode(playerid);
	wl_PlayerSpawn(playerid);

	return true;
}

public OnPlayerDeath(playerid, killerid, reason){ debug_public_track("OnPlayerDeath(playerid, killerid, reason){");
	SendDeathMessage(killerid,playerid,reason);
	wl_PlayerDeath(playerid,killerid,reason);
	return true;
}
public OnVehicleSpawn(vehicleid){ debug_public_track("OnVehicleSpawn(vehicleid){");
	return true;
}
public OnVehicleDeath(vehicleid, killerid){ debug_public_track("OnVehicleDeath(vehicleid, killerid){");
	wl_mode_VehicleDeath(vehicleid);
	return true;
}

public OnPlayerText(playerid, text[]){ debug_public_track("OnPlayerText(playerid, text[]){");
	if(wl_PlayerText(playerid,text)){
		return false;
	}
	return true;
}


public OnPlayerRequestClass(playerid, classid){ debug_public_track("OnPlayerRequestClass(playerid, classid){");
	wl_PlayerRequestClass(playerid,classid);
	//objective_RequestClass(playerid,classid);
	return true;
}
public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger){ debug_public_track("OnPlayerEnterVehicle(playerid, vehicleid, ispassenger){");
	return true;
}
public OnPlayerExitVehicle(playerid, vehicleid){ debug_public_track("OnPlayerExitVehicle(playerid, vehicleid){");
	wl_mode_PlayerExitVehicle(playerid);
	return true;
}
public OnPlayerStateChange(playerid, newstate, oldstate){ debug_public_track("OnPlayerStateChange(playerid, newstate, oldstate){");
	wl_PlayerStateChange(playerid,newstate,oldstate);
	return true;
}
public OnPlayerEnterCheckpoint(playerid){ debug_public_track("OnPlayerEnterCheckpoint(playerid){");
	wl_EnterCheckpoint(playerid);
	return true;
}
public OnPlayerLeaveCheckpoint(playerid){ debug_public_track("OnPlayerLeaveCheckpoint(playerid){");
	return true;
}
public OnPlayerEnterRaceCheckpoint(playerid){ debug_public_track("OnPlayerEnterRaceCheckpoint(playerid){");
	wl_EnterRaceCheckpoint(playerid);
	return true;
}
public OnPlayerLeaveRaceCheckpoint(playerid){ debug_public_track("OnPlayerLeaveRaceCheckpoint(playerid){");
	return true;
}
public OnRconCommand(cmd[]){ debug_public_track("OnRconCommand(cmd[]){");
	return true;
}


public OnPlayerRequestSpawn(playerid){ debug_public_track("OnPlayerRequestSpawn(playerid){");
	wl_PlayerRequestSpawn(playerid);
	return true;
}
public OnObjectMoved(objectid){ debug_public_track("OnObjectMoved(objectid){");
	return true;
}
public OnPlayerObjectMoved(playerid, objectid){ debug_public_track("OnPlayerObjectMoved(playerid, objectid){");
	return true;
}
public OnPlayerPickUpPickup(playerid, pickupid){ debug_public_track("OnPlayerPickUpPickup(playerid, pickupid){");
	return true;
}
public OnVehicleMod(playerid, vehicleid, componentid){ debug_public_track("OnVehicleMod(playerid, vehicleid, componentid){");
	return true;
}
public OnVehiclePaintjob(playerid, vehicleid, paintjobid){ debug_public_track("OnVehiclePaintjob(playerid, vehicleid, paintjobid){");
	return true;
}
public OnVehicleRespray(playerid, vehicleid, color1, color2){ debug_public_track("OnVehicleRespray(playerid, vehicleid, color1, color2){");
	return true;
}
public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid){ debug_public_track("OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid){");
	return true;
}
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys){ debug_public_track("OnPlayerKeyStateChange(playerid, newkeys, oldkeys){");
	wl_KeyStateChange(playerid,newkeys,oldkeys);
	debug_public_track("keystatechange:exit");
	return true;
}
public OnPlayerSelectedMenuRow(playerid,row){ debug_public_track("OnPlayerSelectedMenuRow(playerid,row){");
	TogglePlayerControllable(playerid, true);
	if(wl_PlayerSelectedMenuRow(playerid,row))return true;
	return true;
}
public OnPlayerExitedMenu(playerid){ debug_public_track("OnPlayerExitedMenu(playerid){");
	TogglePlayerControllable(playerid, true);
	wl_PlayerExitedMenu(playerid);
	return true;
}

forward OnPlayerPrivmsg(playerid, recieverid, text[]);
public OnPlayerPrivmsg(playerid, recieverid, text[]){ debug_public_track("OnPlayerPrivmsg(playerid, recieverid, text[]){");
	if(wl_PlayerPrivmsg(playerid,recieverid,text))return false;
	return true;
}

public OnPlayerCommandText(playerid,cmdtext[]){ debug_public_track("OnPlayerCommandText(playerid,cmdtext[]){");
	if(ZCMD_ProcessCommand(playerid, cmdtext)) return true;
	if(wl_CommandText(playerid,cmdtext)) return true;
	System_send(playerid,"[系统]你输入的命令'%s'有误，请输入 /help 或登陆help.gtaip.com 查看帮助",cmdtext);
	return true;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source){ debug_public_track("OnPlayerClickPlayer(playerid, clickedplayerid, source){");
	wl_PlayerClickPlayer(playerid, clickedplayerid, source);
	return true;
}

public OnPlayerUpdate(playerid){ //debug_public_track("OnPlayerUpdate(playerid){");
	if(!rp_playerUpdate(playerid))return false;
	wl_PlayerUpdate(playerid);
	return true;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]){ debug_public_track("OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]){");
	wl_DialogResponse(playerid, dialogid, response, listitem, inputtext);
	return false;
}



zcmd(banpm,playerid,params[]){
	new
		recevierid;
	if(!sscanf(params,"i",recevierid)){
		if(IsPlayerConnected(recevierid)){
			if(GetGVarInt("wl_plr_banpm",getDoubleRelationList(playerid,recevierid))){
				SetGVarInt("wl_plr_banpm",false,getDoubleRelationList(playerid,recevierid));
				System_send(playerid,"[PM]你关闭了屏蔽%s(%d)的PM信息的功能，开启该功能请再次输入 - /banpm %d",pName(recevierid),recevierid,recevierid);
			}
			else {
				SetGVarInt("wl_plr_banpm",true,getDoubleRelationList(playerid,recevierid));
				System_send(playerid,"[PM]你开启了屏蔽%s(%d)的PM信息的功能，关闭该功能请再次输入 - /banpm %d",pName(recevierid),recevierid,recevierid);
			}
		}
		else {
			System_send(playerid,"ID为%d的玩家不在线",recevierid);
		}
	}
	else {
		System_send(playerid,"使用方法 - /banpm [玩家ID] - 开启/关闭屏蔽玩家PM信息的功能");
	}
	return true;
}

	
zcmd(pm,playerid,params[]){
	// PM Command
	#define ADMINFS_MESSAGE_COLOR 0xFF444499
	#define PM_INCOMING_COLOR     0xFFFF22AA
	#define PM_OUTGOING_COLOR     0xFFCC2299
	new
		pmee,
		Msg[128];
	if(!sscanf(params,"is",pmee,Msg)){
		//printf("%d,%d,%s",playerid,pmee,Msg);
		if(IsPlayerConnected(pmee)){
			if(playerid != pmee){
				if(!GetGVarInt("wl_plr_banpm",getDoubleRelationList(pmee,playerid))){
					OnPlayerPrivmsg(playerid,pmee,Msg);
					printf("PM: %d to %d:%s",playerid,pmee,Msg);
				}
				else {
					System_send(playerid,"[PM]玩家%s(%d)屏蔽了你的PM信息，发送失败",pName(pmee),pmee);
				}
			} 
			else {
				SendClientMessage(playerid,ADMINFS_MESSAGE_COLOR,"You cannot PM yourself");
			}
		}
		else {
			SendClientMessage(playerid,ADMINFS_MESSAGE_COLOR,"/pm : Bad player ID");
		}
	}
	else {
		SendClientMessage(playerid,ADMINFS_MESSAGE_COLOR,"Usage: /pm (id) (message)");
	}
	return 1;
	#undef ADMINFS_MESSAGE_COLOR
	#undef PM_INCOMING_COLOR
	#undef PM_OUTGOING_COLOR
}

zcmd(help,playerid,params[]){
	#define DIALOG_CMD_HELP_CAPTION	"帮助(help.gtaip.com)"
	#define DIALOG_CMD_HELP_INFO	"\
	个性化设置系统:/s help    帐号帮助:/a help\
	车辆系统:/c help    换胎:/c tune     漂移计分系统:/d help\n\
	赛车系统: 提示输入/join时,输入/join 即可参加    学习制作赛道找lxd\n\
	群组系统:/g help\n团队系统:/t help\n进入大型DM区域:/gdm   进入普通DM:/dm [id]\n\
	电视系统:/tv\n动作系统:/animlist\n21点系统:/bj help\n自制传送点/vmake\n \n其它命令:/cmds"
	#define DIALOG_CMD_HELP_BUTTON1	"确定"
	#define DIALOG_CMD_HELP_BUTTON2	"取消"
	ShowPlayerDialog(playerid,1,DIALOG_STYLE_LIST,DIALOG_CMD_HELP_CAPTION,DIALOG_CMD_HELP_INFO,DIALOG_CMD_HELP_BUTTON1,DIALOG_CMD_HELP_BUTTON2);
	return 1;
}
zcmd(cmds,playerid,params[]){
	#define DIALOG_CMD_CMDS_CAPTION	"命令帮助(help.gtaip.com)"
		#define DIALOG_CMD_CMDS_INFO   "\
		/sp 保存你当前坐标    /lp 传送到最近保存的坐标处\n/w [id]或者 /world [id]随意切换世界，输入 /w 即可回到地球\
		/afk [原因] 挂机    /back 归来\n/ff 切换格斗风格\n\
		/skin [皮肤id] 永久切换皮肤\n/kill 自杀 /zican 自残\n/id [玩家部分名字] 找玩家\n\
		/jetpack 叫个飞行器玩玩    /jls 叫个降落伞     /dive 原地高空跳伞\n/count 倒计时\n \
		/shang /xia /zuo /you /qian /hou 微调你的位置\n其它帮助:/help\n"
	#define DIALOG_CMD_CMDS_BUTTON1 "确定"
	#define DIALOG_CMD_CMDS_BUTTON2 "取消"
ShowPlayerDialog(playerid,1,DIALOG_STYLE_LIST,DIALOG_CMD_CMDS_CAPTION,DIALOG_CMD_CMDS_INFO,DIALOG_CMD_CMDS_BUTTON1,DIALOG_CMD_CMDS_BUTTON2);
	return 1;
}
zcmd(thanks,playerid,params[]){
	#define DIALOG_CMD_THX_CAPTION	"特别鸣谢(help.gtaip.com)"
	#define DIALOG_CMD_THX_INFO	"如有疏漏请报告给管理员(排名不分先后) \n\n制作群\n   vvg,yezizhu,Cn_Shindo,Sean.X,MK124,fangye\n \
								GM\n   LXD,JL3517,TaiZi,KTS,CHY,luck,Devil_ggggg\n \
								玩家\nowen,Leon,TaiZi,Heise,TY,Ak47,hand,TCWTQS...\n \
								网站\n   gtabbs.com sa-mp.com.cn gtaip.com gta.qq.topzj.com\n"
	#define DIALOG_CMD_THX_BUTTON1	"确定"
	#define DIALOG_CMD_THX_BUTTON2	"取消"
	ShowPlayerDialog(playerid,1,DIALOG_STYLE_LIST,DIALOG_CMD_THX_CAPTION,DIALOG_CMD_THX_INFO,DIALOG_CMD_THX_BUTTON1,DIALOG_CMD_THX_BUTTON2);
	return 1;
}




zcmd(subaccount,playerid,params[]){
	System_send(playerid,"[帐号]服务器暂时取消个性化设置功能");
	return true;
}
pzcmd(s) 			rzcmd(subaccount);		

	/*
zcmd(acc_register,playerid,params[]){
	System_send(playerid,"[帐号]服务器暂时取消注册功能");
	return true;
}
//pzcmd(register)		rzcmd(acc_register); 

zcmd(acc_login,playerid,params[]){
	System_send(playerid,"[帐号]服务器暂时取消登陆功能");
	return true;
}
pzcmd(register)		rzcmd(acc_register);

zcmd(acc_account,playerid,params[]){
	System_send(playerid,"[帐号]服务器暂时注册系统功能");
	return true;
}
pzcmd(account)		rzcmd(acc_account);
pzcmd(a)			rzcmd(acc_account);
	*/
	