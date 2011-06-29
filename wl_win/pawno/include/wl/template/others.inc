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





stock wl_tmp_o_setPlayerSkin(playerid,skinid){
	
	wl_sPlr_Player_Skin(playerid,skinid);
	return true;
}

stock wl_tmp_o_getPlayerSkin(playerid){
	return wl_gPlr_Player_Skin(playerid);
}

zcmd(tmp_skin,playerid,params[]){
	if(Skin_isValid(strval(params))){
		SetPlayerSkin(playerid,strval(params));
		wl_tmp_o_setPlayerSkin(playerid,strval(params));
		System_send(playerid,"[系统]你更换了皮肤,皮肤编号%d",strval(params));
	}else{
		System_send(playerid,"[系统]皮肤ID无效");
	}
	return true;
}
pzcmd(skin) 	rzcmd(tmp_skin);
pzcmd(pifu) 	rzcmd(tmp_skin);
pzcmd(hf)		rzcmd(tmp_skin);
pzcmd(huanfu) 	rzcmd(tmp_skin);

/*
//===================切换场景=====================================

zcmd(tmp_world,playerid,params[]){
	if(isnull(params)){
		if(GetPlayerState(playerid)==PLAYER_STATE_DRIVER){
			SetVehicleVirtualWorld(GetPlayerVehicleID(playerid),0);
		}
		SetPlayerVirtualWorld(playerid,0);	
		System_send(playerid,"[切换世界]你切换回地球~");
		System_send(playerid,"[切换世界]使用方法:/w [世界名称]");
	}else{
		new
			vid;
		if(IsNumeric(params)){
			vid = strval(params);
		}else{
			for(new i;params[i];i++){
				vid += params[i]*(i+1)*(i+1)*(i+1);
			}
		}
		if(vid >= 0 && vid <= 1000000000){
			if(GetPlayerState(playerid)==PLAYER_STATE_DRIVER){
				SetVehicleVirtualWorld(GetPlayerVehicleID(playerid),vid);
			}
			SetPlayerVirtualWorld(playerid,vid);
			System_send(playerid,"[切换世界]你切换到'%s'的世界",params);
		}else{
			System_send(playerid,"[切换世界]你输入的世界不合法");
		}
	}
	return true;
}		
pzcmd(shijie) 	rzcmd(tmp_world);
pzcmd(w) 	rzcmd(tmp_world);
*/
//===================Save&Load pos=============================================================
static stock
	Float:wl_tmp_o_psavex[MAX_PLAYERS],
	Float:wl_tmp_o_psavey[MAX_PLAYERS],
	Float:wl_tmp_o_psavez[MAX_PLAYERS];
	

zcmd(tmp_sp,playerid,params[]){
	GetPlayerPos(playerid,wl_tmp_o_psavex[playerid],wl_tmp_o_psavey[playerid],wl_tmp_o_psavez[playerid]);
	System_send(playerid,"[系统]你的坐标已经保存,输入/lp 可以传送到这里");
	return true;
}
pzcmd(sp) 		rzcmd(tmp_sp);
pzcmd(savepos) 	rzcmd(tmp_sp);

zcmd(tmp_lp,playerid,params[]){
	TeleportPlayer(
		playerid,wl_tmp_o_psavex[playerid],wl_tmp_o_psavey[playerid],wl_tmp_o_psavez[playerid]);
	System_send(playerid,"[系统]你被传送到上次保存的目的地");
	return true;
}
pzcmd(l) 		rzcmd(tmp_lp);
pzcmd(lp) 		rzcmd(tmp_lp);
pzcmd(loadpos) 	rzcmd(tmp_lp);
//==============格斗风格=====================
static
	pFightsytle_dialogid = 41;
zcmd(tmp_fightstyle,playerid,params[]){
	ShowPlayerDialog(playerid,pFightsytle_dialogid,DIALOG_STYLE_LIST,"格斗风格","格斗风格选择 - 感谢fly_luck提供\n \n1.一般风格\n2.拳击风格\n3.功夫风格(荐)\n4.帮战风格1\n5.帮战风格2\n6.帮战风格3\n \n[提示]选择一项,双击或选定后按切换按钮.\n[提示]使用方法:跑动或静止时按住鼠标右键+F或回车.","切换","取消");
	return true;
}
pzcmd(fight) 		rzcmd(tmp_fightstyle);
pzcmd(gedou) 		rzcmd(tmp_fightstyle);
pzcmd(ff) 	rzcmd(tmp_fightstyle);

Fightsytle_DialogResponse(playerid, dialogid, response, listitem){
	if(dialogid == pFightsytle_dialogid){
		if(response){
			if(listitem == 2) 
				SetPlayerFightingStyle(playerid,FIGHT_STYLE_NORMAL),SendClientMessage(playerid,COLOR_LIGHTBLUE,"[格斗]你成功将格斗风格切换为正常.");
			if(listitem == 3) 
				SetPlayerFightingStyle(playerid,FIGHT_STYLE_BOXING),SendClientMessage(playerid,COLOR_LIGHTBLUE,"[格斗]你成功将格斗风格切换为拳击.");
			if(listitem == 4) 
				SetPlayerFightingStyle(playerid,FIGHT_STYLE_KUNGFU),SendClientMessage(playerid,COLOR_LIGHTBLUE,"[格斗]你成功将格斗风格切换为功夫.");
			if(listitem == 5) 
				SetPlayerFightingStyle(playerid,FIGHT_STYLE_KNEEHEAD),SendClientMessage(playerid,COLOR_LIGHTBLUE,"[格斗]你成功将格斗风格切换为帮战1.");
			if(listitem == 6) 
				SetPlayerFightingStyle(playerid,FIGHT_STYLE_GRABKICK),SendClientMessage(playerid,COLOR_LIGHTBLUE,"[格斗]你成功将格斗风格切换为帮战2.");
			if(listitem == 7) 
				SetPlayerFightingStyle(playerid,FIGHT_STYLE_ELBOW),SendClientMessage(playerid,COLOR_LIGHTBLUE,"[格斗]你成功将格斗风格切换为帮战3.");
		}
	}
}
//=============================================
//=================================================

wl_tmp_o_PlayerRequestSpawn(playerid){
	wl_tmp_o_setPlayerSkin(playerid,GetPlayerSkin(playerid));
	return true;
}

wl_tmp_o_PlayerSpawn(playerid){
	SetPlayerSkin(playerid,wl_tmp_o_getPlayerSkin(playerid));
	return true;
}

wl_tmp_o_PlayerDisconnect(playerid){
	wl_tmp_o_setPlayerSkin(playerid,0);
	return true;
}



//========================================================

//======================检测玩家是否切换/死机======================================
/*
Pause_OnPlayerSpawn(playerid){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
Pause_OnPlayerDeath(playerid, killerid, reason){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	SetPVarInt(killerid,"wl_plr_online",true);
	SetPVarInt(killerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
*/
Pause_OnPlayerText(playerid){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return false;
}
Pause_OnPlayerCommandText(playerid){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return false;
}
/*
Pause_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
Pause_OnPlayerExitVehicle(playerid, vehicleid){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
*/
Pause_OnPlayerStateChange(playerid){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
/*
Pause_OnPlayerSelectedMenuRow(playerid, row){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
Pause_OnPlayerExitedMenu(playerid){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
*/
Pause_OnPlayerKeyStateChange(playerid){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
Pause_OnPlayerUpdate(playerid){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
/*
Pause_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
Pause_OnPlayerClickPlayer(playerid, clickedplayerid, source){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
*/
Pause_struction(){
	SetTimer("Pause_Check",999*3,true);
}

forward Pause_Check();
public Pause_Check(){ debug_public_track("Pause_Check(){");
	new
		gPause_gTick = GetTickCount();
	for(new playerid;playerid < MAX_PLAYERS;playerid++){
		if(IsPlayerConnected(playerid)){
			if(GetPVarInt(playerid,"wl_plr_online")){
				if(gPause_gTick - GetPVarInt(playerid,"wl_plr_online_tick") > 5000){
					SetPVarInt(playerid,"wl_plr_online",false);
				}
			}
		}
	}
}

//=============================================================
zcmd(tmp_kill,playerid,params[]){
	SetPlayerHealth(playerid,0);
	System_send(playerid,"[系统]自杀成功...");
	return true;
}
pzcmd(k) 		rzcmd(tmp_kill);
pzcmd(kill) 	rzcmd(tmp_kill);
pzcmd(zisha) 	rzcmd(tmp_kill);


zcmd(tmp_search,playerid,params[]){
	if(isnull(params)){
		System_send(playerid,"[系统]请输入玩家的关键字");
	}
	else {
		searchPlayer(playerid,params);
	}
	return true;
}
pzcmd(id) 	rzcmd(tmp_search);
pzcmd(search) 	rzcmd(tmp_search);
pzcmd(chazhao) 	rzcmd(tmp_search);


zcmd(tmp_parachute,playerid,params[]){
	GivePlayerWeapon(playerid,WEAPON_PARACHUTE,1);
	return true;
}

pzcmd(jls) 			rzcmd(tmp_parachute);
pzcmd(jiangluosan) 	rzcmd(tmp_parachute);
pzcmd(parachute) 	rzcmd(tmp_parachute);

zcmd(tmp_dive,playerid,params[]){
	new
		Float:ppx,
		Float:ppy,
		Float:ppz;
	GetPlayerPos(playerid,ppx,ppy,ppz);
	SetPlayerPos(playerid,ppx,ppy,ppz+500);
	GivePlayerWeapon(playerid,WEAPON_PARACHUTE,1);
	System_send(playerid,"[系统]一飞冲天!!!");
	return true;
}
pzcmd(tiaosan) 	rzcmd(tmp_dive);
pzcmd(dive) 	rzcmd(tmp_dive);
pzcmd(ts) 		rzcmd(tmp_dive);


zcmd(tmp_afk_sta,playerid,params[]){
	TogglePlayerControllable(playerid, false);
	if(isnull(params)) System_send(playerid,"[系统]%s(%d)暂时离开(原因:未知)",PlayerName(playerid),playerid);
	else System_send(playerid,"[系统]%s(%d)暂时离开(原因:%s)",PlayerName(playerid),playerid,params);
	new
		bubble[MAX_MSG_STR];
	format(bubble,sizeof(bubble),"%s(%d)在挂机(原因:%s)",pName(playerid),playerid,((isnull(params))?("未知"):(params)));
	SetPlayerChatBubble(playerid,bubble, GetPlayerColor(playerid), 50, 1000*60*60*60);
	//if(paramn(1)) System_sendAll("[系统]%s(%d)暂时离开(原因:未知)",PlayerName(playerid),playerid);
	//else System_sendAll("[系统]%s(%d)暂时离开(原因:%s)",PlayerName(playerid),playerid,params(1));
	return true;
}
pzcmd(afk) 		rzcmd(tmp_afk_sta);
pzcmd(likai) 	rzcmd(tmp_afk_sta);

zcmd(tmp_afk_end,playerid,params[]){
	TogglePlayerControllable(playerid,true);
	System_send(playerid,"[系统]%s(%d)归来!",PlayerName(playerid),playerid);
	SetPlayerChatBubble(playerid,"我归来了!", GetPlayerColor(playerid), 50, 1000*5);
	//System_sendAll("[系统]%s(%d)归来!",PlayerName(playerid),playerid);
	return true;
}
pzcmd(huilai) 	rzcmd(tmp_afk_end);
pzcmd(back) 	rzcmd(tmp_afk_end);


zcmd(tmp_jetpack,playerid,params[]){
	System_send(playerid,"[系统]召唤JetPack成功");
	SetPlayerSpecialAction(playerid, 2);
	return true;
}
pzcmd(feixingqi) 	rzcmd(tmp_jetpack);
pzcmd(fxq) 			rzcmd(tmp_jetpack);
pzcmd(jetpack) 		rzcmd(tmp_jetpack);
//==========Count down=====================
forward wl_tmp_CountDown();

static
	wl_tmp_gCount = 5,
	wl_tmp_gCountText[5][5]=
{
   "~r~1",
   "~y~2",
   "~b~3",
   "~g~4",
   "~p~5"
},
	Float:wl_tmp_gCountrange[3];

public wl_tmp_CountDown(){ debug_public_track("wl_tmp_CountDown(){");
	if(wl_tmp_gCount > 0){
		wl_tmp_gCount--;
		loopPlayer(i){
			if(IsPlayerInRangeOfPoint(i,100,wl_tmp_gCountrange[0],wl_tmp_gCountrange[1],wl_tmp_gCountrange[2])){
				PlayerPlaySound(i,1056);
				GameTextForPlayer(i,wl_tmp_gCountText[wl_tmp_gCount],2500,3);
			}
		}
		SetTimer("wl_tmp_CountDown",998,false);
	}else{
		loopPlayer(i){
			if(IsPlayerInRangeOfPoint(i,100,wl_tmp_gCountrange[0],wl_tmp_gCountrange[1],wl_tmp_gCountrange[2])){
				PlayerPlaySound(i,1057);
				GameTextForPlayer(i,"~g~GO~r~!!~n~~g~GO~r~!!~n~~g~GO~r~!!", 2500, 3);
			}
		}
		wl_tmp_gCount = 5;
	}
	return true;
}

zcmd(tmp_countdown,playerid,params[]){
	if(wl_tmp_gCount >= 5){
		GetPlayerPos(playerid,wl_tmp_gCountrange[0],wl_tmp_gCountrange[1],wl_tmp_gCountrange[2]);
		System_send(playerid, "[成功] 倒计时开始");
		wl_tmp_CountDown();
	}else{
		System_send(playerid, "[错误] 抱歉, 倒计时已经开启....");
	}
	return true;
}
pzcmd(count) 	rzcmd(tmp_countdown);
pzcmd(djs) 		rzcmd(tmp_countdown);
pzcmd(daoshu) 	rzcmd(tmp_countdown);
//=============================//

	zcmd(shang,playerid,params[]){
		new
			Float:px,Float:py,Float:pz;
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
			GetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz);
			SetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz+2);
		}else{
			GetPlayerPos(playerid,px,py,pz);
			SetPlayerPos(playerid,px,py,pz+2);
		}
		return true;
	}
	zcmd(xia,playerid,params[]){
		new
			Float:px,Float:py,Float:pz;
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
			GetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz);
			SetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz-2);
		}else{
			GetPlayerPos(playerid,px,py,pz);
			SetPlayerPos(playerid,px,py,pz-2);
		}
		return true;
	}
	zcmd(zuo,playerid,params[]){
		new
			Float:px,Float:py,Float:pz;
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
			GetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz);
			SetVehiclePos(GetPlayerVehicleID(playerid),px+2,py,pz);
		}else{
			GetPlayerPos(playerid,px,py,pz);
			SetPlayerPos(playerid,px+2,py,pz);
		}
		return true;
	}
	zcmd(you,playerid,params[]){
		new
			Float:px,Float:py,Float:pz;
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
			GetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz);
			SetVehiclePos(GetPlayerVehicleID(playerid),px-2,py,pz);
		}else{
			GetPlayerPos(playerid,px,py,pz);
			SetPlayerPos(playerid,px-2,py,pz);
		}
		return true;
	}
	zcmd(qian,playerid,params[]){
		new
			Float:px,Float:py,Float:pz;
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
			GetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz);
			SetVehiclePos(GetPlayerVehicleID(playerid),px,py+2,pz);
		}else{
			GetPlayerPos(playerid,px,py,pz);
			SetPlayerPos(playerid,px,py+2,pz);
		}
		return true;
	}
	zcmd(hou,playerid,params[]){
		new
			Float:px,Float:py,Float:pz;
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
			GetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz);
			SetVehiclePos(GetPlayerVehicleID(playerid),px,py-2,pz);
		}else{
			GetPlayerPos(playerid,px,py,pz);
			SetPlayerPos(playerid,px,py-2,pz);
		}
		return true;
	}
	//
	zcmd(zican,playerid,params[]){
		new
			Float:ph;
		GetPlayerHealth(playerid,ph);
		SetPlayerHealth(playerid,ph-5);
		System_send(playerid,"[系统]你在自残ing(剩余血量:%f) -0-",ph-5);
		return true;
	}


