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



#define COLOR_VW				(COLOR_LIGHTBLUE)



//vecsystem send
#define VW_send(%1,%2,%3) wl_lang_send((%1),COLOR_VW,%2,%3)
VW_send(playerid,msg_identify[]){
	wl_lang_send(playerid,COLOR_VW,msg_identify);
}

#define VW_sendAll(%1,%2) wl_lang_sendAll(COLOR_VW,(%1),%2)
VW_sendAll(msg_identify[]){
	wl_lang_sendAll(COLOR_VW,msg_identify);
}

#define VW_sendIn(%1,%2,%3) \
	loopPlayer(vwplayer) \
		if(GetPlayerVirtualWorld((%1)) == GetPlayerVirtualWorld(vwplayer)) \
			VW_send(vwplayer,%2,%3)

enum {
	vw_playmode_none,
	vw_playmode_tank,
	vw_playmode_hunter,
	vw_playmode_minigun,
	vw_playmode_quanquan,
	vw_playmode_spaz,
	vw_playmode_amount
};





stock vw_spPlayModeLog(playerid,vw_playmode,index,set){
	return CallLocalFunction("gw_sVWLog","iiii",playerid,vw_playmode,index,set);
}

stock vw_gpPlayModeLog(playerid,vw_playmode,index){
	return CallLocalFunction("gw_gVWLog","iiii",playerid,vw_playmode,index);
}



	
stock vw_gpOrgWorld(playerid){
	return GetPVarInt(playerid,"wl_plr_gvw_pOrgWorld");
}
stock vw_spOrgWorld(playerid,set){
	SetPVarInt(playerid,"wl_plr_gvw_pOrgWorld",set);
	return true;
}




stock vw_spAbleWorld(playerid,targetid,set){
	SetGVarInt("wl_plr_vw_pAbleWorld",set,getDoubleRelationList(playerid,targetid));
	return true;
}
stock vw_gpAbleWorld(playerid,targetid){
	return GetGVarInt("wl_plr_vw_pAbleWorld",getDoubleRelationList(playerid,targetid));
}

stock vw_spAdminWorld(playerid,set){
	SetPVarInt(playerid,"wl_plr_gvw_pAdminWorld",set);
	return true;
}
stock vw_gpAdminWorld(playerid){
	return GetPVarInt(playerid,"wl_plr_gvw_pAdminWorld");
}

stock vw_spPlayMode(playerid,mode){
	SetPVarInt(playerid,"wl_plr_gvw_pPlayMode",mode);
	return true;
}

stock vw_gpPlayMode(playerid){
	return GetPVarInt(playerid,"wl_plr_gvw_pPlayMode");
}


//#include <wl\modes\virtualworld\virtualworld_base>




vw_playerConnect(playerid){
	vw_spOrgWorld(playerid,false);
	vw_spAdminWorld(playerid,true);
	for(new i;i < MAX_PLAYERS;i++){
		vw_spAbleWorld(playerid,i,true);
	}
	vw_spPlayMode(playerid,vw_playmode_none);
}

vw_playerDisconnect(playerid){
	vw_spOrgWorld(playerid,false);
	vw_spAdminWorld(playerid,false);
	for(new i;i < MAX_PLAYERS;i++){
		vw_spAbleWorld(playerid,i,false);
	}
	vw_spPlayMode(playerid,vw_playmode_none);
	
	
	//vw_base_playerDisconnect(playerid);
}

vw_playerSpawn(playerid){
	if(!GetPlayerVirtualWorld(playerid)){
		vw_pTrigergodmode(playerid);
	}else{
		SetPlayerArmour(playerid,100);
	}
	vw_spPlayMode(playerid,vw_playmode_none);
}

vw_playerDeath(playerid,killerid,reason){
	if(killerid == INVALID_PLAYER_ID){
		if(vw_gpPlayMode(playerid) == vw_playmode_tank){
			VW_sendIn(playerid,"vw_playermode_tank_plrdie",pName(playerid),playerid);
		}
		else if(vw_gpPlayMode(playerid) == vw_playmode_hunter){
			VW_sendIn(playerid,"vw_playermode_hunter_plrdie",pName(playerid),playerid);
		}
	}	
	else if(vw_gpPlayMode(playerid) && vw_gpPlayMode(playerid) == vw_gpPlayMode(killerid)){
		vw_spPlayModeLog(playerid,vw_gpPlayMode(playerid),0,vw_gpPlayModeLog(playerid,vw_gpPlayMode(playerid),0)+1);
		vw_spPlayModeLog(killerid,vw_gpPlayMode(killerid),0,vw_gpPlayModeLog(killerid,vw_gpPlayMode(killerid),0)+1);
		vw_spPlayModeLog(killerid,vw_gpPlayMode(killerid),1,vw_gpPlayModeLog(killerid,vw_gpPlayMode(killerid),1)+1);
		switch(vw_gpPlayMode(playerid)){
			case vw_playmode_minigun:{
				if(!reason || reason == WEAPON_MINIGUN){
					VW_sendIn(playerid,"vw_playermode_minigun_plrdie_killed",pName(playerid),playerid,pName(killerid),killerid);
				}
			}
			case vw_playmode_quanquan:{
				if(!reason || reason == WEAPON_SAWEDOFF || reason == WEAPON_UZI || reason == WEAPON_TEC9){
					VW_sendIn(playerid,"vw_playermode_sawn_plrdie_killed",pName(playerid),playerid,pName(killerid),killerid);
				}
			}
			case vw_playmode_spaz:{
				if(!reason || reason == WEAPON_SHOTGSPA){
					VW_sendIn(playerid,"vw_playermode_spaz_plrdie_killed",pName(playerid),playerid,pName(killerid),killerid);
				}
			}
			case vw_playmode_tank:{
				VW_sendIn(playerid,"vw_playermode_tank_plrdie_killed",pName(playerid),playerid,pName(killerid),killerid);
			}
			case vw_playmode_hunter:{
				VW_sendIn(playerid,"vw_playermode_hunter_plrdie_killed",pName(playerid),playerid,pName(killerid),killerid);
			}
		}
	}
	vw_spPlayMode(playerid,vw_playmode_none);
	
	//vw_base_playerDeath(playerid,killerid,reason);
	
}


vw_playerEnterCheckpoint(playerid){
	#pragma unused playerid
	//vw_base_playerEnterCheckpoint(playerid);
}


stock vw_getFromstr(const str[]){
	new
		vwid;
	for(new i;str[i];i++){
		vwid += str[i]*(i+1)*(i+1)*(i+1);
	}
	return vwid;
}

stock vw_getPlayerfromvwid(vwid){
	loopPlayer(playerid){
		if(vw_getFromstr(pName(playerid)) == vwid)
			return playerid;
	}
	return INVALID_PLAYER_ID;
}

stock vw_isplayerInplayerWorld(playerid,targetworldid){
	if(GetPlayerVirtualWorld(playerid) && GetPlayerVirtualWorld(playerid) == vw_getFromstr(pName(targetworldid)))
		return true;
	return false;
}



stock vw_pTrigergodmode(playerid){
	SetPlayerHealth(playerid,999999999);
	SetPlayerArmour(playerid,100);
}

stock vw_pCanclegodmode(playerid){
	SetPlayerHealth(playerid,100);
	SetPlayerArmour(playerid,100);
}



forward vw_missionTeleport(playerid,targetid,televec,mission);
public vw_missionTeleport(playerid,targetid,televec,mission){ debug_public_track("vw_missionTeleport(playerid,targetid,televec,mission){");
	switch(mission){
		case vw_playmode_none:{
			vw_spPlayMode(playerid,vw_playmode_none);
		}
		case vw_playmode_tank:{
			new
				str[MAX_MSG_STR];
			format(str,MAX_MSG_STR,"/ww vechp %d 9999",targetid);
			vw_spPlayMode(targetid,vw_playmode_tank);
			OnPlayerCommandText(playerid,str);
			TeleportPlayer(targetid,pX(playerid)+5,pY(playerid)+5,pZ(playerid)+3,televec);
		}
		case vw_playmode_hunter:{
			new
				str[MAX_MSG_STR];
			format(str,MAX_MSG_STR,"/ww vechp %d 9999",targetid);
			vw_spPlayMode(targetid,vw_playmode_hunter);
			OnPlayerCommandText(playerid,str);
			TeleportPlayer(targetid,pX(playerid)+10,pY(playerid)+10,pZ(playerid)+20,televec);
		}			
		case vw_playmode_minigun:{
			vw_spPlayMode(targetid,vw_playmode_minigun);
			TeleportPlayer(targetid,pX(playerid)+3,pY(playerid)+3,pZ(playerid)+1,televec);
		}
		case vw_playmode_quanquan:{
			vw_spPlayMode(targetid,vw_playmode_quanquan);
			TeleportPlayer(targetid,pX(playerid)+3,pY(playerid)+3,pZ(playerid)+1,televec);
		}
		case vw_playmode_spaz:{
			vw_spPlayMode(targetid,vw_playmode_spaz);
			TeleportPlayer(targetid,pX(playerid)+3,pY(playerid)+3,pZ(playerid)+1,televec);
		}
	}
	return true;
}

zcmd(vw_vw,playerid,params[]){
	new
		vwid;
	if(isnull(params)){
		if(GetPlayerState(playerid)==PLAYER_STATE_DRIVER){
			SetVehicleVirtualWorld(GetPlayerVehicleID(playerid),0);
		}
		SetPlayerVirtualWorld(playerid,0);	
		ResetPlayerWeapons(playerid);
		vw_pTrigergodmode(playerid);
		VW_send(playerid,"cmd_vw_w_succeed");
	}
	else {
		if(IsNumeric(params)){
			new targetid = strval(params);
			if(IsPlayerConnected(targetid)){
				if(vw_gpAbleWorld(playerid,targetid)){
					vw_pCanclegodmode(playerid);
					vwid = vw_getFromstr(pName(targetid));
					if(GetPlayerState(playerid)==PLAYER_STATE_DRIVER){
						SetVehicleVirtualWorld(GetPlayerVehicleID(playerid),vwid);
					}
					SetPlayerVirtualWorld(playerid,vwid);
					VW_send(playerid,"cmd_vw_w_toplayer_succeed_tome",pName(targetid),targetid);
					VW_send(targetid,"cmd_vw_w_toplayer_succeed_toit",pName(playerid),playerid);
				}
				else {
					VW_send(playerid,"cmd_vw_w_toplayer_failed_notallow",pName(targetid),targetid);
				}
			}
			else {
				VW_send(playerid,"cmd_vw_w_toplayer_failed_notconnected");
			}
		}
		else {
			vwid = vw_getFromstr(params);
			vw_pCanclegodmode(playerid);
			VW_send(playerid,"cmd_vw_w_toother_succeed",params);
		}
		if(vwid >= 0 && vwid <= 1000000000){
			if(GetPlayerState(playerid)==PLAYER_STATE_DRIVER){
				SetVehicleVirtualWorld(GetPlayerVehicleID(playerid),vwid);
			}
			SetPlayerVirtualWorld(playerid,vwid);
		}
		else {
			VW_send(playerid,"cmd_vw_w_toother_failed_invalidworld");
		}
	}
	return true;
}		
pzcmd(w) 	rzcmd(vw_vw);

zcmd(vw_vww,playerid,params[]){
	zcmd_advused();
	if(isnull(params)){
		new
			str[MAX_MSG_STR];
		format(str,MAX_MSG_STR,"/w %d",playerid);
		OnPlayerCommandText(playerid,str);
		VW_send(playerid,"cmd_vw_ww_succeed",params);
	}		
	else if(compare("goto",1)){
		if(isnull(cmd_(2))){
			VW_send(playerid,"cmd_vw_ww_goto_help");
		}
		else if(IsNumeric(cmd_(2))){
			new
				targetid = strval(cmd_(2));
			if(IsPlayerConnected(targetid)){
				if(!vw_isplayerInplayerWorld(targetid,playerid)){
					VW_send(playerid,"cmd_vw_ww_goto_failed_notin");
				}else{
					TeleportPlayer(playerid,pX(targetid)+3,pY(targetid)+3,pZ(targetid)+1);
					VW_send(playerid,"cmd_vw_ww_goto_succeed_tome",pName(targetid),targetid);
					VW_send(targetid,"cmd_vw_ww_goto_succeed_toit",pName(playerid),playerid);
				}
			}else{
				VW_send(playerid,"cmd_vw_ww_goto_failed_notconnected");
			}
		}else{
			VW_send(playerid,"cmd_vw_ww_goto_failed_invalidid");
		}
	}
	else if(compare("gethere",1)){
		if(isnull(cmd_(2))){
			VW_send(playerid,"cmd_vw_ww_gethere_help");
		}
		else if(IsNumeric(cmd_(2))){
			new
				targetid = strval(cmd_(2));
			if(IsPlayerConnected(targetid)){
				if(!vw_isplayerInplayerWorld(targetid,playerid)){
					VW_send(playerid,"cmd_vw_ww_gethere_failed_notin");
				}else{
					TeleportPlayer(targetid,pX(playerid)+3,pY(playerid)+3,pZ(playerid)+1);
					VW_send(playerid,"cmd_vw_ww_gethere_succeed_tome",pName(targetid),targetid);
					VW_send(targetid,"cmd_vw_ww_gethere_succeed_toit",pName(playerid),playerid);
				}
			}else{
				VW_send(playerid,"cmd_vw_ww_gethere_failed_notconnected");
			}
		}else{
			VW_send(playerid,"cmd_vw_ww_gethere_failed_invalidid");
		}
	}
	else if(compare("spaz",1)){
		if(isnull(cmd_(2))){
			VW_send(playerid,"cmd_vw_ww_spaz_help");
		}		
		else if(IsNumeric(cmd_(2))){
			new
				targetid = strval(cmd_(2));
			if(IsPlayerConnected(targetid)){
				if(vw_isplayerInplayerWorld(targetid,playerid)){
					if(isnull(cmd_(3))){
						SetPlayerHealth(targetid,100);
					}else{
						SetPlayerHealth(targetid,floatstr(cmd_(3)));
					}
					SetPlayerArmour(targetid,100);
					ResetPlayerWeapons(targetid);
					GivePlayerWeapon(targetid,27,99999);
					SetTimerEx("vw_missionTeleport",GetPlayerPing(playerid)*2+800,false,"iiii",playerid,targetid,false,vw_playmode_spaz);
					VW_send(targetid,"cmd_vw_ww_spaz_succeed_toit",pName(playerid),playerid);
					VW_send(playerid,"cmd_vw_ww_spaz_succeed_tome",pName(targetid),targetid);
				}else{
					VW_send(playerid,"cmd_vw_ww_spaz_failed_notin");
					VW_send(playerid,"cmd_vw_ww_spaz_help");
				}
			}else{
				VW_send(playerid,"cmd_vw_ww_spaz_failed_notconnected");
				VW_send(playerid,"cmd_vw_ww_spaz_help");
			}
		}else{
			VW_send(playerid,"cmd_vw_ww_spaz_failed_invalidid");
			VW_send(playerid,"cmd_vw_ww_spaz_help");
		}
	}
	else if(compare("quanquan",1) || compare("sawnoff",1)){
		if(isnull(cmd_(2))){
			VW_send(playerid,"cmd_vw_ww_sawn_help");
		}		
		else if(IsNumeric(cmd_(2))){
			new
				targetid = strval(cmd_(2));
			if(IsPlayerConnected(targetid)){
				if(vw_isplayerInplayerWorld(targetid,playerid)){
					if(isnull(cmd_(3))){
						SetPlayerHealth(targetid,100);
					}else{
						SetPlayerHealth(targetid,floatstr(cmd_(3)));
					}
					SetPlayerArmour(targetid,100);
					ResetPlayerWeapons(targetid);
					GivePlayerWeapon(targetid,26,99999);
					GivePlayerWeapon(targetid,28,99999);
					SetTimerEx("vw_missionTeleport",GetPlayerPing(playerid)*2+800,false,"iiii",playerid,targetid,false,vw_playmode_quanquan);
					VW_send(targetid,"cmd_vw_ww_sawn_succeed_toit",pName(playerid),playerid);
					VW_send(playerid,"cmd_vw_ww_sawn_succeed_tome",pName(targetid),targetid);
				}else{
					VW_send(playerid,"cmd_vw_ww_sawn_failed_notin");
					VW_send(playerid,"cmd_vw_ww_sawn_help");
				}
			}else{
				VW_send(playerid,"cmd_vw_ww_sawn_failed_notconnected");
				VW_send(playerid,"cmd_vw_ww_sawn_help");
			}
		}else{
			VW_send(playerid,"cmd_vw_ww_sawn_failed_invalidid");
			VW_send(playerid,"cmd_vw_ww_sawn_help");
		}
	}
	else if(compare("hunter",1)){
		if(isnull(cmd_(2))){
			VW_send(playerid,"cmd_vw_ww_hunter_help");
		}	
		else if(IsNumeric(cmd_(2))){
			new
				targetid = strval(cmd_(2));
			if(IsPlayerConnected(targetid)){
				if(vw_isplayerInplayerWorld(targetid,playerid)){
					SetPlayerArmour(targetid,100);
					SetPlayerHealth(targetid,100);
					ResetPlayerWeapons(targetid);
					OnPlayerCommandText(targetid,"/c 425");
					SetTimerEx("vw_missionTeleport",GetPlayerPing(playerid)*2+800,false,"iiii",playerid,targetid,true,vw_playmode_hunter);
					VW_send(targetid,"cmd_vw_ww_hunter_succeed_toit",pName(playerid),playerid);
					VW_send(playerid,"cmd_vw_ww_hunter_succeed_tome",pName(targetid),targetid);
				}else{
					VW_send(playerid,"cmd_vw_ww_hunter_failed_notin");
					VW_send(playerid,"cmd_vw_ww_hunter_help");
				}
			}else{
				VW_send(playerid,"cmd_vw_ww_hunter_failed_notconnected");
				VW_send(playerid,"cmd_vw_ww_hunter_help");
			}
		}else{
			VW_send(playerid,"cmd_vw_ww_hunter_failed_invalidid");
			VW_send(playerid,"cmd_vw_ww_hunter_help");
		}
	}		
	else if(compare("tank",1)){
		if(isnull(cmd_(2))){
			VW_send(playerid,"cmd_vw_ww_tank_help");
		}	
		else if(IsNumeric(cmd_(2))){
			new
				targetid = strval(cmd_(2));
			if(IsPlayerConnected(targetid)){
				if(vw_isplayerInplayerWorld(targetid,playerid)){
					SetPlayerArmour(targetid,100);
					SetPlayerHealth(targetid,100);
					ResetPlayerWeapons(targetid);
					OnPlayerCommandText(targetid,"/c 432");
					SetTimerEx("vw_missionTeleport",GetPlayerPing(playerid)*2+800,false,"iiii",playerid,targetid,true,vw_playmode_tank);
					VW_send(targetid,"cmd_vw_ww_tank_succeed_toit",pName(playerid),playerid);
					VW_send(playerid,"cmd_vw_ww_tank_succeed_tome",pName(targetid),targetid);
				}else{
					VW_send(playerid,"cmd_vw_ww_tank_failed_notin");
					VW_send(playerid,"cmd_vw_ww_tank_help");
				}
			}else{
				VW_send(playerid,"cmd_vw_ww_tank_failed_notconnected");
				VW_send(playerid,"cmd_vw_ww_tank_help");
			}
		}else{
			VW_send(playerid,"cmd_vw_ww_tank_failed_invalidid");
			VW_send(playerid,"cmd_vw_ww_tank_help");
		}
	}	
	else if(compare("minigun",1)){
		if(isnull(cmd_(2))){
			VW_send(playerid,"cmd_vw_ww_minigun_help");
		}		
		else if(IsNumeric(cmd_(2))){
			new
				targetid = strval(cmd_(2));
			if(IsPlayerConnected(targetid)){
				if(vw_isplayerInplayerWorld(targetid,playerid)){
					if(isnull(cmd_(3))){
						SetPlayerHealth(targetid,5000);
					}else{
						SetPlayerHealth(targetid,floatstr(cmd_(3)));
					}
					ResetPlayerWeapons(targetid);
					GivePlayerWeapon(targetid,38,99999);
					GivePlayerWeapon(targetid,41,99999);
					SetPlayerArmour(targetid,100);
					SetTimerEx("vw_missionTeleport",GetPlayerPing(playerid)*2+800,false,"iiii",playerid,targetid,false,vw_playmode_minigun);
					VW_send(targetid,"cmd_vw_ww_minigun_succeed_toit",pName(playerid),playerid);
					VW_send(playerid,"cmd_vw_ww_minigun_succeed_tome",pName(targetid),targetid);
				}else{
					VW_send(playerid,"cmd_vw_ww_minigun_failed_notin");
					VW_send(playerid,"cmd_vw_ww_minigun_help");
				}
			}else{
				VW_send(playerid,"cmd_vw_ww_minigun_failed_notconnected");
				VW_send(playerid,"cmd_vw_ww_minigun_help");
			}
		}else{
			VW_send(playerid,"cmd_vw_ww_minigun_failed_invalidid");
			VW_send(playerid,"cmd_vw_ww_minigun_help");
		}
	}
	else if(compare("allow",1) || compare("ban",1)){
		if(isnull(cmd_(2))){
			VW_send(playerid,"cmd_vw_ww_allow_help");
		}
		else if(IsNumeric(cmd_(2))){
			new
				targetid = strval(cmd_(2));
			if(IsPlayerConnected(targetid)){
				if(vw_gpAbleWorld(targetid,playerid)){
					vw_spAbleWorld(targetid,playerid,false);
					if(vw_isplayerInplayerWorld(targetid,playerid)){
						SetPlayerVirtualWorld(targetid,0);
						VW_send(targetid,"cmd_vw_ww_allow_succeed_ban_toit",pName(playerid));
					}
					VW_send(playerid,"cmd_vw_ww_allow_succeed_ban_tome'",pName(targetid),targetid);
				}else{
					vw_spAbleWorld(targetid,playerid,true);
					VW_send(playerid,"cmd_vw_ww_allow_succeed_unban'",pName(targetid),targetid);
				}
			}else{
				VW_send(playerid,"cmd_vw_ww_allow_failed_notconnected");
			}
		}else{
			VW_send(playerid,"cmd_vw_ww_allow_failed_invalidid");
		}
	}
	else if(compare("hp",1)){
		if(isnull(cmd_(2))){
			VW_send(playerid,"cmd_vw_ww_hp_help");
		}
		else if(isnull(cmd_(3))){
			VW_send(playerid,"cmd_vw_ww_hp_help");
		}		
		else if(IsNumeric(cmd_(2))){
			new
				targetid = strval(cmd_(2)),
				Float:hp = floatstr(cmd_(3));
			if(IsPlayerConnected(targetid)){
				if(vw_isplayerInplayerWorld(targetid,playerid)){
					SetPlayerHealth(targetid,hp);
					VW_send(playerid,"cmd_vw_ww_hp_succeed_tome",pName(targetid),targetid,hp);
					VW_send(targetid,"cmd_vw_ww_hp_succeed_toit",pName(playerid),playerid,hp);
				}else{
					VW_send(playerid,"cmd_vw_ww_hp_failed_notin");
				}
			}else{
				VW_send(playerid,"cmd_vw_ww_hp_failed_notconnected");
			}
		}else{
			VW_send(playerid,"cmd_vw_ww_hp_failed_invalidid");
		}
	}
	else if(compare("armour",1)){
		if(isnull(cmd_(2))){
			VW_send(playerid,"cmd_vw_ww_armour_help");
		}
		else if(isnull(cmd_(3))){
			VW_send(playerid,"cmd_vw_ww_armour_help");
		}		
		else if(IsNumeric(cmd_(2))){
			new
				targetid = strval(cmd_(2)),
				Float:armour = floatstr(cmd_(3));
			if(IsPlayerConnected(targetid)){
				if(vw_isplayerInplayerWorld(targetid,playerid)){
					SetPlayerArmour(targetid,armour);
					VW_send(playerid,"cmd_vw_ww_armour_succeed_tome",pName(targetid),targetid,armour);
					VW_send(targetid,"cmd_vw_ww_armour_succeed_toit",pName(playerid),playerid,armour);
				}else{
					VW_send(playerid,"cmd_vw_ww_armour_failed_notin");
				}
			}else{
				VW_send(playerid,"cmd_vw_ww_armour_failed_notconnected");
			}
		}else{
			VW_send(playerid,"cmd_vw_ww_armour_failed_invalidid");
		}
	}
	else if(compare("giveweapon",1)){
		if(isnull(cmd_(2))){
			VW_send(playerid,"cmd_vw_ww_giveweapon_help");
		}
		else if(IsNumeric(cmd_(2))){
			new
				id = strval(cmd_(2));
			if(IsPlayerConnected(id)){
				if(vw_isplayerInplayerWorld(id,playerid)){
					new
						wid = strval(cmd_(3)),
						ammo = strval(cmd_(4));
					if(wid >= 0 && wid <= 46){
						GivePlayerWeapon(id,wid,ammo);
						VW_send(id,"cmd_vw_ww_giveweapon_succeed_toit",pName(playerid),playerid,wName(wid),wid,ammo);
						VW_send(playerid,"cmd_vw_ww_giveweapon_succeed_tome",pName(id),id,wName(wid),wid,ammo);
					}else{
						VW_send(playerid,"cmd_vw_ww_giveweapon_failed_invalidweaponid");
					}
				}else{
					VW_send(playerid,"cmd_vw_ww_giveweapon_failed_notin");
				}
			}else{
				VW_send(playerid,"cmd_vw_ww_giveweapon_failed_notconnected");
			}
		}else{
			VW_send(playerid,"cmd_vw_ww_giveweapon_failed_invalidid");
		}
	}
	else if(compare("vechp",1)){
		if(isnull(cmd_(2))){
			VW_send(playerid,"cmd_vw_ww_vechp_help");
		}
		else if(isnull(cmd_(3))){
			VW_send(playerid,"cmd_vw_ww_vechp_help");
		}
		else if(IsNumeric(cmd_(2))){
			new
				targetid = strval(cmd_(2));
			if(IsPlayerConnected(targetid)){
				if(vw_isplayerInplayerWorld(targetid,playerid)){
					new
						Float:hp = floatstr(cmd_(3)),
						vecid = CallLocalFunction("Vec_getPlayerVecID","i",targetid);
					if(vecid != INVALID_VEHICLE_ID){
						SetVehicleHealth(vecid,hp);
						VW_send(playerid,"cmd_vw_ww_vechp_succeed_tome",pName(targetid),targetid,hp);
						VW_send(targetid,"cmd_vw_ww_vechp_succeed_toit",pName(playerid),playerid,hp);
					}else{
						VW_send(playerid,"cmd_vw_ww_vechp_failed_novec");
					}
				}else{
					VW_send(playerid,"cmd_vw_ww_vechp_failed_notin");
				}
			}else{
				VW_send(playerid,"cmd_vw_ww_vechp_failed_notconnected");
			}
		}else{
			VW_send(playerid,"cmd_vw_ww_vechp_failed_invalidid");
		}
	}
	else if(compare("resetweapon",1)){
		if(isnull(cmd_(2))){
			VW_send(playerid,"cmd_vw_ww_resetweapon_help");
		}
		else if(IsNumeric(cmd_(2))){
			new
				id = strval(cmd_(2));
			if(IsPlayerConnected(id)){
				if(vw_isplayerInplayerWorld(id,playerid)){
					ResetPlayerWeapons(playerid);
					VW_send(playerid,"cmd_vw_ww_resetweapon_succeed_toit",pName(playerid),playerid);
					VW_send(playerid,"cmd_vw_ww_resetweapon_succeed_tome",pName(id),id);
				}else{
					VW_send(playerid,"cmd_vw_ww_resetweapon_failed_notin");
				}
			}else{
				VW_send(playerid,"cmd_vw_ww_resetweapon_failed_notconnected");
			}
		}else{
			VW_send(playerid,"cmd_vw_ww_resetweapon_failed_invalidid");
		}
	}
	else if(compare("getweapon",1)){
		if(GetPlayerVirtualWorld(playerid)){
			ResetPlayerWeapons(playerid);
			GivePlayerWeapon(playerid,WEAPON_KATANA,1);
			GivePlayerWeapon(playerid,WEAPON_DEAGLE,9999);
			GivePlayerWeapon(playerid,WEAPON_SHOTGSPA,9999);
			GivePlayerWeapon(playerid,WEAPON_MP5,9999);
			GivePlayerWeapon(playerid,WEAPON_M4,9999);
			GivePlayerWeapon(playerid,WEAPON_SNIPER,9999);
			GivePlayerWeapon(playerid,WEAPON_TEARGAS,9999);
			GivePlayerWeapon(playerid,WEAPON_FIREEXTINGUISHER,9999);
			GivePlayerWeapon(playerid,WEAPON_FLOWER,1);
			GivePlayerWeapon(playerid,WEAPON_PARACHUTE,1);
			VW_send(playerid,"cmd_vw_ww_getweapon_succeed");
		}
		else {
			VW_send(playerid,"cmd_vw_ww_getweapon_failed_innormalworld");
		}
	}
	else if(compare("chat",1)){
		if(isnull(cmd_(2))){
			VW_send(playerid,"cmd_vw_ww_chat_failed_inputtext");
		}else if(GetPVarInt(playerid,"i_sadmin_mute")){
			VW_send(playerid,"cmd_vw_ww_chat_failed_mute");
		}else{
			wl_tmp_fm_PlayerText(playerid,params[4],true);
		}
	}
	else if(compare("help",1)){
		
		static 
			gvw_help_dialog_info[] = "\
			/ww chat [聊天内容] - 全世界聊天\n\
			\n \n \n以下命令专属世界主人可用\n\
			/ww allow [玩家ID] - (不)允许指定玩家进入你的专属世界\n\
			/ww hp [玩家ID] - 设置指定玩家hp\n\
			/ww armour [玩家ID] - 设置指定玩家armour\n\
			/ww vechp [玩家ID] - 设置指定玩家专属车辆hp\n\
			/ww giveweapon [玩家ID] [武器ID] [子弹数量] - 设置指定玩家武器";
		ShowPlayerDialog(playerid,1,DIALOG_STYLE_LIST,"世界帮助",gvw_help_dialog_info,"确定","取消");
		
		VW_send(playerid,"cmd_vw_ww_help11");
		VW_send(playerid,"cmd_vw_w_help");
		VW_send(playerid,"cmd_vw_w_toid_help");
		VW_send(playerid,"cmd_vw_ww_help");
		VW_send(playerid,"cmd_vw_ww_allow_help");
		VW_send(playerid,"cmd_vw_ww_hp_help");
		VW_send(playerid,"cmd_vw_ww_armour_help");
		VW_send(playerid,"cmd_vw_ww_vechp_help");
		VW_send(playerid,"cmd_vw_ww_giveweapon_help");
		VW_send(playerid,"cmd_vw_ww_help12");
		VW_send(playerid,"cmd_vw_ww_help13");
	}
	else if(compare("help2",1)){
		
		static
			gvw_help2_dialog_info[] = "\
			/ww base set - 开设一个base\n\
			/ww spaz [玩家ID] - spaz对决\n\
			/ww quanquan [玩家ID] - 圈圈对决\n\
			/ww minigun [玩家ID] [玩家 hp(可不设置,默认为5000)] - minigun对决\n\
			/ww hunter [玩家ID] [hunter hp(可不设置,默认为9999)]\n\
			/ww tank [玩家ID] [tank hp(可不设置,默认为9999)]- 让玩家快速加入tank大战!";
		ShowPlayerDialog(playerid,1,DIALOG_STYLE_LIST,"世界帮助",gvw_help2_dialog_info,"确定","取消");
		
		VW_send(playerid,"cmd_vw_ww_help21");
		VW_send(playerid,"cmd_vw_ww_goto_help");
		VW_send(playerid,"cmd_vw_ww_gethere_help");
		VW_send(playerid,"cmd_vw_ww_spaz_help");
		VW_send(playerid,"cmd_vw_ww_sawn_help");
		VW_send(playerid,"cmd_vw_ww_hunter_help");
		VW_send(playerid,"cmd_vw_ww_tank_help");
		VW_send(playerid,"cmd_vw_ww_help22");
		VW_send(playerid,"cmd_vw_ww_help23");
	}else{
		VW_send(playerid,"cmd_vw_ww_unknowncmd",params);
	}
	return true;
}
pzcmd(ww) 	rzcmd(vw_vww);







