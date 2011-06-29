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


#define DEBUG_PDM				(true)
#define COLOR_PDM				(COLOR_LIGHTBLUE)


#define PDM_send(%1,%2,%3) \
do{\
	new \
		sendfstring[MAX_STRING];\
	format(sendfstring,MAX_STRING,(%2),%3);\
	SendClientMessage((%1),COLOR_PDM,sendfstring);\
}while(FALSE)

stock PDM_send(playerid,const sendfstring[]){
	SendClientMessage(playerid,COLOR_PDM,sendfstring);
}

#define PDM_sendAll(%1,%2) \
do{ \
	new \
	sendfstring[MAX_STRING];\
	format(sendfstring,MAX_STRING,(%1),%2);\
	SendClientMessageToAll(COLOR_PDM,sendfstring);\
}while(FALSE)

stock PDM_sendAll(const sendfstring[]){
	SendClientMessageToAll(COLOR_PDM,sendfstring);
}


#define MAX_PDM						(50)
#define MAX_PDM_COMMAND_IDENTIFY	(MAX_CMD_IDENTIFY_LENGTH)
#define MAX_PDM_COMMAND_NAME		(MAX_CMD_COMMAND_LENGTH)
#define MAX_PDM_SPAWN_POSITION		(5)
#define MAX_PDM_WEAPON				(10)
#define INVALID_PDM_ID				(-1)


forward PDM_isPlayerIn(playerid);

public PDM_isPlayerIn(playerid){ debug_public_track("PDM_isPlayerIn(playerid){");
	if((wl_gPlr_DM_PlayerIn(playerid) != INVALID_PDM_ID)){
		return true;
	}
	return false;
}

/*
stock PDM_setDMtoCommand(dmid){
	new
		cmdName[128];
	format(cmdName,128,"pdm%03d",dmid);
	return true;
}
*/

stock PDM_setPlayerToDMArea(playerid,dmid){
	new
		Float:x,Float:y,Float:z,
		i = wl_n_mode_DMInfo[dmid][E_mode_dm_Interior];
	switch(random(10)){
		case 0:{
			x = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_x1];
			y = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_y1];
			z = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_z1];
		}
		case 1:{
			x = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_x2];
			y = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_y2];
			z = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_z2];
		}
		case 2:{
			x = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_x3];
			y = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_y3];
			z = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_z3];
		}
		case 3:{
			x = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_x4];
			y = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_y4];
			z = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_z4];
		}
		case 4:{
			x = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_x5];
			y = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_y5];
			z = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_z5];
		}
		case 5:{
			x = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_x6];
			y = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_y6];
			z = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_z6];
		}
		case 6:{
			x = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_x7];
			y = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_y7];
			z = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_z7];
		}
		case 7:{
			x = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_x8];
			y = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_y8];
			z = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_z8];
		}
		case 8:{
			x = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_x9];
			y = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_y9];
			z = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_z9];
		}
		case 9:{
			x = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_x10];
			y = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_y10];
			z = wl_n_mode_DMInfo[dmid][E_mode_dm_Spawn_z10];
		}
	}
	TeleportPlayer(playerid,x,y,z,90,i,true);
	PDM_send(playerid,wl_n_mode_DMInfo[dmid][E_mode_dm_Description]);
	return true;
}
stock PDM_givePlayerDMWeapon(playerid,dmid){
	GivePlayerWeapon(playerid,wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID1],wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_Ammo1]);
	GivePlayerWeapon(playerid,wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID2],wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_Ammo2]);
	GivePlayerWeapon(playerid,wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID3],wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_Ammo3]);
	GivePlayerWeapon(playerid,wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID4],wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_Ammo4]);
	GivePlayerWeapon(playerid,wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID5],wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_Ammo5]);
	GivePlayerWeapon(playerid,wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID6],wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_Ammo6]);
	GivePlayerWeapon(playerid,wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID7],wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_Ammo7]);
	GivePlayerWeapon(playerid,wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID8],wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_Ammo8]);
	GivePlayerWeapon(playerid,wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID9],wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_Ammo9]);
	GivePlayerWeapon(playerid,wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID10],wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_Ammo10]);
	return true;
}

stock PDM_getPlayerDM(playerid){
	return wl_gPlr_DM_PlayerIn(playerid);
}

stock PDM_setPlayerDM(playerid,dmid){
	wl_sPlr_DM_PlayerIn(playerid,dmid);
	return true;
}

stock PDM_isPlayerInPDMAreaEx(playerid,dmid){//prefix nearby
	if(PlayerInArea(playerid,wl_n_mode_DMInfo[dmid][E_mode_dm_Area_minx]-50,wl_n_mode_DMInfo[dmid][E_mode_dm_Area_miny]-50,wl_n_mode_DMInfo[dmid][E_mode_dm_Area_maxx]+50,wl_n_mode_DMInfo[dmid][E_mode_dm_Area_maxy]+50)){
		return true;
	}
	return false;
}

stock PDM_isPlayerInPerDMArea(playerid,dmid){
	if(PlayerInArea(playerid,wl_n_mode_DMInfo[dmid][E_mode_dm_Area_minx],wl_n_mode_DMInfo[dmid][E_mode_dm_Area_miny],wl_n_mode_DMInfo[dmid][E_mode_dm_Area_maxx],wl_n_mode_DMInfo[dmid][E_mode_dm_Area_maxy])){
		return true;
	}
	return false;
}

stock PDM_isPlayeruseInvalidPDMWeapon(playerid,dmid){
	new 
		weaponid = GetPlayerWeapon(playerid);
		if(
			weaponid == wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID1] || weaponid == wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID2] ||
			weaponid == wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID3] || weaponid == wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID4] ||
			weaponid == wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID5] || weaponid == wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID6] ||
			weaponid == wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID7] || weaponid == wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID8] ||
			weaponid == wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID9] || weaponid == wl_n_mode_DMInfo[dmid][E_mode_dm_Weapon_ID10]
		){
			return false;
		}
	return true;
}
	






zcmd(pdm_outdm,playerid,params[]){
	PDM_outdm_start(playerid);
	return true;
}
pzcmd(outdm) rzcmd(pdm_outdm);

stock PDM_outdm_start(playerid){
	SetPlayerArmedWeapon(playerid,0);
	ResetPlayerWeapons(playerid);
	GangZoneHideForPlayer(playerid,wl_n_mode_DMInfo[PDM_getPlayerDM(playerid)][E_mode_dm_GangZone]);
	SetPlayerWorldBounds(playerid,9999,-9999,9999,-9999);
	SetTimerEx("PDM_outdm_end",3000,false,"i",playerid);
}

forward PDM_outdm_end(playerid);
public PDM_outdm_end(playerid){ debug_public_track("PDM_outdm_end(playerid){");
	SetPVarInt(playerid,"wl_pdm_dming",false);
	PDM_setPlayerDM(playerid,INVALID_PDM_ID);
	PDM_send(playerid,"[PDM]你离开了DM");
	OnPlayerSpawn(playerid);
}	
	
stock PDM_enterdm_start(playerid,dmid){
	ResetPlayerWeapons(playerid);
	PDM_setPlayerDM(playerid,dmid);
	PDM_setPlayerToDMArea(playerid,dmid);
	
	SetPlayerWorldBounds(playerid,wl_n_mode_DMInfo[dmid][E_mode_dm_Area_maxx],wl_n_mode_DMInfo[dmid][E_mode_dm_Area_minx],wl_n_mode_DMInfo[dmid][E_mode_dm_Area_maxy],wl_n_mode_DMInfo[dmid][E_mode_dm_Area_miny]);
	GangZoneShowForPlayer(playerid,wl_n_mode_DMInfo[dmid][E_mode_dm_GangZone],0xAA333355);
	GangZoneFlashForPlayer(playerid,wl_n_mode_DMInfo[dmid][E_mode_dm_GangZone], GetPlayerColor(playerid));
	SetTimerEx("PDM_enterdm_end",6000+GetPlayerPing(playerid)*2,false,"ii",playerid,dmid);
}


forward PDM_enterdm_end(playerid,dmid);
public PDM_enterdm_end(playerid,dmid){ debug_public_track("PDM_enterdm_end(playerid,dmid){");
	SetPVarInt(playerid,"wl_pdm_dming",true);
	SetPlayerHealth(playerid,100);
	SetPlayerArmour(playerid,100);
	PDM_givePlayerDMWeapon(playerid,dmid);
}

stock PDM_commandDM(playerid,const dm_identify[]){
	new
		dmid = strval(dm_identify[3]);
	if(dmid >= sizeof(wl_n_mode_DMInfo)){
		PDM_send(playerid,"[PDM]你输入的DM不存在!");
		return true;
	}
	PDM_enterdm_start(playerid,dmid);	
	PDM_sendAll("[PDM]%s(%d)进入了'%s' (/dm %d)",pName(playerid),playerid,wl_n_mode_DMInfo[dmid][E_mode_dm_Command_Name],dmid);
	return true;
}

PDM_playerCommandText(playerid,cmdtext[]){

	if(!strcmp(cmdtext[1],"dm likai") || !strcmp(cmdtext[1],"dm exit")){
		OnPlayerCommandText(playerid,"/outdm");
		return true;
	}
	for(new i,j = sizeof(wl_n_mode_DMInfo);i<j;i++){
		if(
			!strcmp(cmdtext[1],wl_n_mode_DMInfo[i][E_mode_dm_Command_Type1]) ||
			!strcmp(cmdtext[1],wl_n_mode_DMInfo[i][E_mode_dm_Command_Type2]) ||
			!strcmp(cmdtext[1],wl_n_mode_DMInfo[i][E_mode_dm_Command_Type3])
		){
			new
				tmpstr[32];
			format(tmpstr,32,"dm %d",i);
			PDM_commandDM(playerid,tmpstr);
			return true;
		}
	}
	new
		tmpstr[32];
	for(new i;i < 59;i++){
		format(tmpstr,32,"dm %d",i);
		if(!strcmp(cmdtext[1],tmpstr,true)){
			PDM_commandDM(playerid,tmpstr);
			return true;
		}
	}
	return false;
}

