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



/*=====================Player Variable Table================================================
	wl_ruleop_player_possible_rulebreak					integer	-
	wl_ruleop_player_rulebreak_info						string	-
	wl_ruleop_player_BreakRule							integer	-
	wl_ruleop_player_JailTimer							integer	-
	wl_ruleop_player_BreakTimes							integer	-
  ==========================================================================================*/


#define WORLD_JAIL				(1)
#define RP_CHECK_ITTER			(801)
#define MAX_ALLOR_BREAK_TIMES	(5)

enum {
	erule_none,
	erule_breakjail,
	erule_breakworld,
	erule_driveby,//dbk
	erule_disallowedTele,//teleport unusable vehicle
	erule_navCheck, //cannot use nav(夜视)
	erule_pdmweapon,//use disallowed weapon in pdm
	erule_pdmweaponout,//bring pdm weapon out
	erule_weapon,//invliad weapon
	erule_carjacknpc, //carjack npc
	erule_possiblecheat
}



//static stock
//	g_wl_ruleop_pBreakRule[MAX_PLAYERS],
//	g_wl_ruleop_pJailTimer[MAX_PLAYERS],
//	g_wl_ruleop_pBreakTimes[MAX_PLAYERS];


				
forward wl_ruleop_pBreakRule(playerid);
public wl_ruleop_pBreakRule(playerid){ debug_public_track("wl_ruleop_pBreakRule(playerid){");
	return GetPVarInt(playerid,"wl_ruleop_player_BreakRule");
}

stock wl_ruleop_gpBreakRule(playerid){
	return GetPVarInt(playerid,"wl_ruleop_player_BreakRule");
}

stock wl_ruleop_spBreakRule(playerid,set){
	SetPVarInt(playerid,"wl_ruleop_player_BreakRule",set);
	return true;
}

stock rp_gpBreakTimes(playerid){
	return GetPVarInt(playerid,"wl_ruleop_player_BreakTimes");
}

stock rp_spBreakTimes(playerid,set){
	SetPVarInt(playerid,"wl_ruleop_player_BreakTimes",set);
	return true;
}

wl_ruleop_struction(){
	SetTimer("wl_ruleop_Check",RP_CHECK_ITTER,true);
}

rp_playerDisconnect(playerid){
	rp_spBreakTimes(playerid,0);
	wl_ruleop_spBreakRule(playerid,false);
	KillTimer(GetPVarInt(playerid,"wl_ruleop_player_JailTimer"));
}

rp_playerConnect(playerid){
	rp_spBreakTimes(playerid,0);
	wl_ruleop_spBreakRule(playerid,false);
	KillTimer(GetPVarInt(playerid,"wl_ruleop_player_JailTimer"));
}

rp_playerUpdate(playerid){
#define holdingEx1(%0) ((keys & (%0)) == (%0))
	new
		keys, updown, leftright;
	GetPlayerKeys(playerid,keys,updown,leftright);
	if(GetPlayerWeapon(playerid) == 44 || GetPlayerWeapon(playerid) == 45){
		ResetPlayerWeapons(playerid);
		return false;
	}
	if(!GetPlayerVirtualWorld(playerid)){
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){
			switch(GetPlayerWeapon(playerid)){
				case WEAPON_GRENADE,WEAPON_TEARGAS,WEAPON_MOLTOV,WEAPON_ROCKETLAUNCHER,WEAPON_HEATSEEKER,WEAPON_FLAMETHROWER,WEAPON_MINIGUN,WEAPON_SATCHEL,WEAPON_SPRAYCAN,WEAPON_FIREEXTINGUISHER:{

					if(holdingEx1(KEY_FIRE) || holdingEx1(KEY_ACTION)){
						return false;
					}			
				}
			}
		}
		else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
			switch(GetVehicleModel(GetPlayerVehicleID(playerid))){
				case 520,425,447,407,432,601:{
					if(holdingEx1(KEY_FIRE) || holdingEx1(KEY_ACTION) || holdingEx1(KEY_SECONDARY_ATTACK)){
						return false;
					}
				}
			}
		}
		else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
			switch(GetPlayerWeapon(playerid)){
				case WEAPON_MINIGUN,WEAPON_SHOTGSPA,WEAPON_SAWEDOFF,WEAPON_DEAGLE,WEAPON_SILENCED,WEAPON_COLT45:{
					if(holdingEx1(KEY_FIRE) || holdingEx1(KEY_ACTION) || holdingEx1(KEY_SECONDARY_ATTACK)){
						return false;
					}
				}
			}
		}	
	}
	return true;
}
	

wl_ruleop_playerSpawn(playerid){
	if(wl_ruleop_gpBreakRule(playerid)){
		SetPlayerVirtualWorld(playerid,WORLD_JAIL);
		SetPlayerPos(playerid,1271.1410,-1254.5160,14.1928);
		SetPlayerWorldBounds(playerid,1292.6895,1285.0641,-1213.2524,-1252.3297);
		
		ResetPlayerWeapons(playerid);
		SetPlayerArmour(playerid,100);
		SetPlayerHealth(playerid,100);
		GivePlayerWeapon(playerid,WEAPON_KATANA,1);
		GivePlayerWeapon(playerid,WEAPON_DEAGLE,9999);
		GivePlayerWeapon(playerid,WEAPON_SHOTGSPA,9999);
		GivePlayerWeapon(playerid,WEAPON_MP5,9999);
		GivePlayerWeapon(playerid,WEAPON_M4,9999);
		GivePlayerWeapon(playerid,WEAPON_SNIPER,9999);
		GivePlayerWeapon(playerid,WEAPON_GRENADE,9999);
		GivePlayerWeapon(playerid,WEAPON_FIREEXTINGUISHER,9999);
		GivePlayerWeapon(playerid,WEAPON_FLOWER,1);
		GivePlayerWeapon(playerid,WEAPON_PARACHUTE,1);
	}
	return true;

}

//===对付夜视=======
forward wl_ruleop_Check();
public wl_ruleop_Check(){ debug_public_track("wl_ruleop_Check(){");
	loopPlayer(playerid){
		if(wl_ruleop_gpBreakRule(playerid)){
			if(GetPlayerVirtualWorld(playerid) != WORLD_JAIL){
				OnPlayerBreakRule(playerid,erule_breakjail);
			}
			continue;
		}
		if(GetPlayerVirtualWorld(playerid)){
			loopPlayer(i){
				if(!vw_gpAbleWorld(playerid,i)){
					if(vw_isplayerInplayerWorld(playerid,i)){
						OnPlayerBreakRule(playerid,erule_breakworld,i);
						continue;
					}
				}
			}
		}
		/*
		if((GetPlayerWeapon(playerid) == 44 || GetPlayerWeapon(playerid) == 45) && (!GetPlayerVirtualWorld(playerid) || dmw:getPlayer(playerid))){
			OnPlayerBreakRule(playerid,erule_navCheck);
			continue;
		}
		*/
		{
			new
				vecid = Vec_getPlayerVecID(playerid),
				vecmodel = GetVehicleModel(vecid);
				
			
			if(vecmodel){
				if((!GetVehicleVirtualWorld(vecid) && !Vec_usableinNormalWorld(vecmodel))){
					//loopPlayer(i){
					//	if(GetPlayerVehicleID(i) == vecid){
							Vec_DestroyPlayer(playerid);
							OnPlayerBreakRule(playerid,erule_disallowedTele,GetPlayerVehicleID(playerid));
					//		break;
					//	}
					//}
					continue;
				}
				#if WL_DMWorld
				if(GetVehicleVirtualWorld(vecid) == DMWorld_ID){
					Vec_DestroyPlayer(playerid);
					OnPlayerBreakRule(playerid,erule_disallowedTele,GetPlayerVehicleID(playerid));
					continue;
				}
				#endif
			}
		}
		if(PDM_getPlayerDM(playerid) != INVALID_PDM_ID){
			if(PDM_isPlayeruseInvalidPDMWeapon(playerid,PDM_getPlayerDM(playerid))){
				OnPlayerBreakRule(playerid,erule_pdmweapon);
				continue;
			}
			if(GetPlayerWeapon(playerid) && GetPVarInt(playerid,"wl_pdm_dming") && !PDM_isPlayerInPDMAreaEx(playerid,PDM_getPlayerDM(playerid))){
				OnPlayerBreakRule(playerid,erule_pdmweaponout);
				continue;
			}
		}
		/*
		new
			pweapon = GetPlayerWeapon(playerid),
			invalidweapon = ( \
				pweapon == WEAPON_SATCHEL || pweapon == WEAPON_MINIGUN || pweapon == WEAPON_HEATSEEKER || pweapon == WEAPON_BOMB || 
				pweapon == WEAPON_ROCKETLAUNCHER || pweapon == WEAPON_GRENADE || pweapon == WEAPON_TEARGAS || pweapon == WEAPON_MOLTOV  || 
				pweapon == WEAPON_CHAINSAW || pweapon == WEAPON_FLAMETHROWER || pweapon == WEAPON_SPRAYCAN || pweapon == WEAPON_FIREEXTINGUISHER
			);
		if(PDM_getPlayerDM(playerid) == INVALID_PDM_ID && !GetPlayerVirtualWorld(playerid) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && invalidweapon){
			OnPlayerBreakRule(playerid,erule_weapon);
			continue;
		}
		*/
	}
}
//==================
//===对付车杀=======
wl_ruleop_PlayerDeath(playerid, killerid, reason){
	#pragma unused playerid,killerid,reason
	/*
	if(!GetPlayerVirtualWorld(playerid) && GetPlayerState(killerid) == PLAYER_STATE_DRIVER && !IsPlayerInAnyVehicle(playerid) && (reason == WEAPON_UZI || reason == WEAPON_MP5 || reason == WEAPON_TEC9)){
		OnPlayerBreakRule(killerid,erule_driveby);
	}
	*/
}
//=================

//forward OnPlayerBreakRule(playerid,ruleid,other);
stock OnPlayerBreakRule(playerid,ruleid,other = -1){
	switch(ruleid){
		case erule_breakjail:{
			if(rp_gpBreakTimes(playerid) < MAX_ALLOR_BREAK_TIMES){
				rp_spBreakTimes(playerid,rp_gpBreakTimes(playerid)+1);
				wl_ruleop_setPlayerJail(playerid,true,30);
				System_send(playerid,"[系统]请不要尝试越狱,累计5次将会被踢出服务器!(次数:%d)",rp_gpBreakTimes(playerid));
			}else{
				System_sendAll("[系统]%s(%d)因尝试越狱被踢出服务器",pName(playerid),playerid);
				Kick(playerid);
			}
		}
		case erule_breakworld:{
			SetPlayerVirtualWorld(playerid,0);
			System_send(playerid,"[系统]你不允许进入'%s'(%d)的世界",pName(other),other);
		}
		case erule_navCheck:{
			ResetPlayerWeapons(playerid);
			wl_ruleop_setPlayerJail(playerid,true,30);
			System_sendAll("[系统]%s(%d)在大世界拥有非法武器(夜视镜),被抓去蹲班房",pName(playerid),playerid);
		}
		case erule_disallowedTele:{
			System_send(playerid,"[系统]不允许把非常规交通工具传送到大世界");
			//if(Vec_getOrginalVW(other)) SetVehicleVirtualWorld(other,Vec_getOrginalVW(other));
			//else SetVehicleVirtualWorld(other,random(500)+1000);
			//wl_ruleop_setPlayerJail(playerid,true,30);
			//System_sendAll("[系统]%s(%d)把非常规交通工具传送到大世界,被抓去蹲班房",pName(playerid),playerid);
		}
		case erule_driveby:{
			SetPlayerHealth(playerid,0);
			wl_ruleop_setPlayerJail(playerid,true,30);
			System_sendAll("[系统]%s(%d)因车杀,被抓去蹲班房",pName(playerid),playerid);
		}
		case erule_pdmweapon:{
			PDM_outdm_start(playerid);
			wl_ruleop_setPlayerJail(playerid,true,30);
			System_sendAll("[系统]%s(%d)拥有非dm武器,被抓去蹲班房",pName(playerid),playerid);
		}
		case erule_pdmweaponout:{
			//PDM_outdm_start(playerid);
			//wl_ruleop_setPlayerJail(playerid,true,30);
			PDM_setPlayerToDMArea(playerid,PDM_getPlayerDM(playerid));
			System_send(playerid,"[系统]请不要尝试把dm武器带出去!");
		}
		case erule_weapon:{
			wl_ruleop_setPlayerJail(playerid,true,30);
			System_send(playerid,"[系统]在大世界不允许有超级暴力武器.");
			System_sendAll("[系统]%s(%d)在大世界拥有非法武器,被抓去蹲班房",pName(playerid),playerid);
		}
		case erule_possiblecheat:{
			loopPlayer(i){
				if(GetPlayerAdminLevel(playerid) >= 1){
					System_send(i,"[系统]%s(%d)有在竞技玩法中作弊的嫌疑(beta).",pName(playerid),playerid);
				}
			}
			//wl_ruleop_setPlayerJail(playerid,true,30);
		}
	}
	return true;
}

forward wl_ruleop_PossibleCheat(playerid,info[]);
public wl_ruleop_PossibleCheat(playerid,info[]){ debug_public_track("wl_ruleop_PossibleCheat(playerid,info[]){");
	if(CallLocalFunction("dmw_getPlayer","i",playerid)){
		if(!strcmp(info,"Weapon Hack in DMworld")){
			System_send(playerid,"[系统]服务器怀疑你违反了游戏规则(原因:%s),如有误判,请到wl.gtabbs.com发帖叙述清楚情况投诉",info);
			ResetPlayerWeapons(playerid);
			SetPlayerHealth(playerid,0);
			SetPlayerPos(playerid,pX(playerid),pY(playerid),pZ(playerid)+5);
			CallLocalFunction("dmw_getPlayer","i",playerid);
			Kick(playerid);
		}
		else if(!strcmp(info,"Possible Speed Hack in DMworld")){
			SetPlayerHealth(playerid,0);
			SetPlayerPos(playerid,pX(playerid),pY(playerid),pZ(playerid)+5);
			System_send(playerid,"[系统]服务器怀疑你违反了游戏规则(原因:%s),如有误判,请到wl.gtabbs.com发帖叙述清楚情况投诉",info);
		}
		else if(!strcmp(info,"Armour Hack")){
			SetPlayerHealth(playerid,0);
			SetPlayerPos(playerid,pX(playerid),pY(playerid),pZ(playerid)+5);
			System_send(playerid,"[系统]服务器怀疑你违反了游戏规则(原因:%s),如有误判,请到wl.gtabbs.com发帖叙述清楚情况投诉",info);
		}
		else if(!strcmp(info,"Health Hack")){
			SetPlayerHealth(playerid,0);
			SetPlayerPos(playerid,pX(playerid),pY(playerid),pZ(playerid)+5);
			System_send(playerid,"[系统]服务器怀疑你违反了游戏规则(原因:%s),如有误判,请到wl.gtabbs.com发帖叙述清楚情况投诉",info);
		}
		else if(!strcmp(info,"Teleport Hack")){
			if(!CallLocalFunction("Spec_isPlayerSpecing","i",playerid)){
				SetPlayerHealth(playerid,0);
				SetPlayerPos(playerid,pX(playerid),pY(playerid),pZ(playerid)+5);
				System_send(playerid,"[系统]服务器怀疑你违反了游戏规则(原因:%s),如有误判,请到wl.gtabbs.com发帖叙述清楚情况投诉",info);
			}
		}
	}
	/*
	else {
		System_sendAll("%s(%d) cheat (%s)",pName(playerid),playerid,info);
	}
	*/
	/*
	if(dmw:getPlayer(playerid)){
		System_send(playerid,"[系统]服务器怀疑你作弊,被抓去蹲班房(原因:%s),如有误抓,请到wl.gtabbs.com发帖叙述清楚情况投诉",info);
		if(GetPlayerAdminLevel(playerid) <= 0){
			OnPlayerBreakRule(playerid,erule_possiblecheat);
		}
		else {
			System_send(playerid,"[系统]号外,GM逃脱术!");
		}
		//todo
		SetPVarInt(playerid,"wl_ruleop_player_possible_rulebreak",true);
		SetPVarString(playerid,"wl_ruleop_player_rulebreak_info",info);
	}
	*/
	return true;
}

forward wl_ruleop_setPlayerJail(playerid,set,second);
public wl_ruleop_setPlayerJail(playerid,set,second){ debug_public_track("wl_ruleop_setPlayerJail(playerid,set,second){");
	if(set){
		KillTimer(GetPVarInt(playerid,"wl_ruleop_player_JailTimer"));
		SetPVarInt(playerid,"wl_ruleop_player_JailTimer",SetTimerEx("wl_ruleop_setPlayerJail",second*1000,false,"iii",playerid,false,false));
		wl_ruleop_spBreakRule(playerid,true);
		SetPlayerVirtualWorld(playerid,WORLD_JAIL);
		SetPlayerPos(playerid,1271.1410,-1254.5160,14.1928);
		SetPlayerWorldBounds(playerid,1292.6895,1285.0641,-1213.2524,-1252.3297);
		
		ResetPlayerWeapons(playerid);
		SetPlayerArmour(playerid,100);
		SetPlayerHealth(playerid,100);
		GivePlayerWeapon(playerid,WEAPON_KATANA,1);
		GivePlayerWeapon(playerid,WEAPON_DEAGLE,9999);
		GivePlayerWeapon(playerid,WEAPON_SHOTGSPA,9999);
		GivePlayerWeapon(playerid,WEAPON_MP5,9999);
		GivePlayerWeapon(playerid,WEAPON_M4,9999);
		GivePlayerWeapon(playerid,WEAPON_SNIPER,9999);
		GivePlayerWeapon(playerid,WEAPON_GRENADE,9999);
		GivePlayerWeapon(playerid,WEAPON_FIREEXTINGUISHER,9999);
		GivePlayerWeapon(playerid,WEAPON_FLOWER,1);
		GivePlayerWeapon(playerid,WEAPON_PARACHUTE,1);
		
		System_send(playerid,"[系统]你被抓到监狱,%d秒后自动放出",second);
	}else{
		KillTimer(GetPVarInt(playerid,"wl_ruleop_player_JailTimer"));
		wl_ruleop_spBreakRule(playerid,false);
		SetPlayerHealth(playerid,0);
		SetPlayerVirtualWorld(playerid,0);
		SetPlayerWorldBounds(playerid,9999,-9999,9999,-9999);
		System_send(playerid,"[系统]你出狱了!请做个合格的玩家",second);
	}
}

/*
new stock
	g_splitcmd[5][MAX_MSG_STR];
#define cmd_(%1) g_splitcmd[(%1)-1]
#define compare(%1,%2) !strcmp(%1,g_splitcmd[(%2)-1],true)
#define zcmd_advused() sscanf(params,"sssss",g_splitcmd[0],g_splitcmd[1],g_splitcmd[2],g_splitcmd[3],g_splitcmd[4]);
*/
zcmd(jail,playerid,params[]){
	if(GetPlayerAdminLevel(playerid) < 2){
		System_send(playerid,"[系统]你无权使用该命令!");
		return true;
	}
	zcmd_advused();
	new
		jailee = IsNumeric(cmd_(1))?strval(cmd_(1)):INVALID_PLAYER_ID,
		second = strval(cmd_(2));
	if(!IsPlayerConnected(jailee) || IsPlayerNPC(jailee)){
		System_send(playerid,"[系统]你输入的玩家不合法!");
		return true;
	}
	if(!second){
		System_send(playerid,"[系统]你输入的时间不合法!");
		return true;
	}
	if(isnull(cmd_(3))){
		System_send(playerid,"[系统]使用方法:/jail [玩家id] [时间:秒] [原因]!");
		return true;
	}
	if(wl_ruleop_gpBreakRule(jailee)){
		System_send(playerid,"[系统]该玩家已经在监狱了");
		return true;
	}
	wl_ruleop_setPlayerJail(jailee,true,second);
	System_send(playerid,"[系统]你抓%s(%d)到监狱,%d秒后自动放出",pName(jailee),jailee,second);
	System_send(jailee,"[系统]你被%s(%d)抓到监狱,%d秒后自动放出",pName(playerid),playerid,second);
	
	return true;
}


















