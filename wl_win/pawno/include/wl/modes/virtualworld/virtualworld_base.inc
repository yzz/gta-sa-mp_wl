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



enum {
	vw_playmode_base_start_none,
	vw_playmode_base_start_making,
	vw_playmode_base_start_started,
	vw_playmode_base_start_amount
}

enum {
	vw_base_end_none,
	vw_base_end_attackwin,
	vw_base_end_defencewin,
	vw_base_end_accident,
	vw_base_end_exit,
	vw_base_end_amount
}


static const stock
	gvw_base_time = 60 * 5;



//disconnect:
vw_base_playerDisconnect(playerid){
	if(GetPVarInt(playerid,"i_wl_vw_base_start")){
		vw_endBase(playerid,vw_base_end_accident);
	}
}


vw_base_playerDeath(playerid,killerid,reason){
	#pragma unused killerid,reason
	if(GetPVarInt(playerid,"i_wl_vw_base_id")){
		//if(!strcmp(GetPVarInt(playerid,"s_wl_vw_base_team"),"attack")){
		//if(GetPVarInt(playerid,"i_wl_vw_base_id") == vw_getFromstr(pName(playerid))){
			DisablePlayerCheckpoint(playerid);
			ResetPlayerWeapons(playerid);
			loopPlayer(j){
				ShowPlayer(playerid,j);
			}
			pVar_delete(playerid,"i_wl_vw_base_id");
			//SetPVarInt(playerid,"i_wl_vw_base_id",0);
			pVar_delete(playerid,"s_wl_vw_base_team");
			//SetPVarString(playerid,"s_wl_vw_base_team","null");
		//}
	}
}

vw_base_playerEnterCheckpoint(playerid){
	if(!strcmp(GetPVarFloat(playerid,"s_wl_vw_base_team"),"attack")){//attacker enter cp
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){//onfoot
			if(!GetPVarInt(vw_getPlayerfromvwid(GetPVarInt(playerid,"i_wl_vw_base_id")),"i_wl_vw_base_cptimeleft")){//countdown hasn't actived
				SetPVarInt(vw_getPlayerfromvwid(GetPVarInt(playerid,"i_wl_vw_base_id")),"i_wl_vw_base_cptimeleft",1);
				SetTimerEx("vw_attackerEnterbasecp",1000*1,false,"ii",GetPlayerVirtualWorld(playerid),playerid);
			}else VW_send(playerid,"[世界-base]你的队友正在夺旗");
		}else VW_send(playerid,"[世界-base]请在红点上夺旗!");
	}
	else if(!strcmp(GetPVarFloat(playerid,"s_wl_vw_base_team"),"attack")){//defencer enter cp
		VW_send(playerid,"[世界-base]你的任务是让敌人远离红点!");
	}
}	
	













forward vw_attackerEnterbasecp(baseid,enterplayerid);
public vw_attackerEnterbasecp(baseid,enterplayerid){ debug_public_track("vw_attackerEnterbasecp(baseid,enterplayerid){");
	if(!IsPlayerInCheckpoint(enterplayerid) || GetPlayerState(enterplayerid) != PLAYER_STATE_ONFOOT){
		vw_attackerLeavebasecp(baseid,enterplayerid);
		return;
	}
	new
		vwhostid = vw_getPlayerfromvwid(baseid),
		timeleft = GetPVarInt(vwhostid,"i_wl_vw_base_cptimeleft");
	if(timeleft > 30){
		vw_endBase(vwhostid,enterplayerid);
	}else{
		new
			tmpstr1[MAX_MSG_STR],
			tmpstr2[MAX_MSG_STR];
		format(tmpstr1,sizeof(tmpstr1),"[世界-base]进攻方正在夺旗,还剩下%d秒!",30-timeleft);
		format(tmpstr2,sizeof(tmpstr2),"[世界-base]我们正在夺旗,还剩下%d秒!",30-timeleft);
		loopPlayer(i){
			if(GetPVarInt(i,"i_wl_vw_base_id") == baseid){
				if(!strcmp(GetPVarFloat(i,"s_wl_vw_base_team"),"defence")){
					VW_send(i,tmpstr1);
				}else if(!strcmp(GetPVarFloat(i,"s_wl_vw_base_team"),"attack")){
					VW_send(i,tmpstr2);
				}
			}
		}
	}
	SetPVarInt(vwhostid,"i_wl_vw_base_cptimeleft",GetPVarInt(vwhostid,"i_wl_vw_base_cptimeleft")+1);
	SetTimerEx("vw_attackerEnterbasecp",1000*1,false,"i",baseid);
}

forward vw_attackerLeavebasecp(baseid,enterplayerid);
public vw_attackerLeavebasecp(baseid,enterplayerid){ debug_public_track("vw_attackerLeavebasecp(baseid,enterplayerid){");
	#pragma unused enterplayerid
	new
		vwhostid = vw_getPlayerfromvwid(baseid);
	SetPVarInt(vwhostid,"i_wl_vw_base_cptimeleft",0);
	loopPlayer(i){
		if(GetPVarInt(i,"i_wl_vw_base_id") == baseid){
			VW_send(i,"[世界-base]进攻方的抢旗行动被打退了");
		}
	}
}


forward vw_loopBase(playerid);
public vw_loopBase(playerid){ debug_public_track("vw_loopBase(playerid){");
	SetPVarInt(playerid,"i_wl_vw_base_timeCrack",GetPVarInt(playerid,"i_wl_vw_base_timeCrack")+1);
	if(gvw_base_time-GetPVarInt(playerid,"i_wl_vw_base_timeCrack") <= 0) vw_endBase(playerid,vw_base_end_defencewin);
	//VW_sendAll("[time]crack:%d left:%d a:",GetPVarInt(playerid,"i_wl_vw_base_timeCrack"),gvw_base_time-GetPVarInt(playerid,"i_wl_vw_base_timeCrack"),gvw_base_time);
}

forward vw_startBase(playerid);
public vw_startBase(playerid){ debug_public_track("vw_startBase(playerid){");
	SetPVarInt(playerid,"i_wl_vw_base_looptimer",SetTimerEx("vw_loopBase",1000,gvw_base_time,"ii",playerid,vw_base_end_defencewin));
	SetPVarInt(playerid,"i_wl_vw_base_timeCrack",0);
	loopPlayer(i){
		if(GetPVarInt(playerid,"i_wl_vw_base_id") == vw_getFromstr(pName(playerid))){
		//if(vw_isplayerInplayerWorld(i,playerid)){
			if(!strcmp(GetPVarFloat(i,"s_wl_vw_base_team"),"defence")){
				SetPlayerCheckpoint(i,GetPVarFloat(playerid,"f_wl_vw_base_cpx"),GetPVarFloat(playerid,"f_wl_vw_base_cpy"),GetPVarFloat(playerid,"f_wl_vw_base_cpz"),2);
				TeleportPlayer(i,GetPVarFloat(playerid,"f_wl_vw_base_defencex")+random(5),GetPVarFloat(playerid,"f_wl_vw_base_defencey")+random(5),GetPVarFloat(playerid,"f_wl_vw_base_defencez")+2,random(65535),.ignoreVec = true);
				OnPlayerCommandText(i,"/ww getweapon");
				SetPlayerHealth(i,100);
				SetPlayerArmour(i,100);
				loopPlayer(j){
					if(!strcmp(GetPVarFloat(j,"s_wl_vw_base_team"),"defence")){
						ShowPlayer(i,j);
					}
					else if(!strcmp(GetPVarFloat(j,"s_wl_vw_base_team"),"attack")){
						HidePlayer(i,j);
					}
					else{
						HidePlayer(i,j);
					}
					//if(strcmp(GetPVarFloat(i,"s_wl_vw_base_team"),"defence")) HidePlayer(i,j);
					//else ShowPlayer(i,j);
				}
				VW_send(i,"[世界-base]全力守护红点5分钟！");
				VW_send(i,"[世界-base]进攻方站在红点超过30s,我们就失败了!");
			}else if(!strcmp(GetPVarFloat(i,"s_wl_vw_base_team"),"attack")){
				SetPlayerCheckpoint(i,GetPVarFloat(playerid,"f_wl_vw_base_cpx"),GetPVarFloat(playerid,"f_wl_vw_base_cpy"),GetPVarFloat(playerid,"f_wl_vw_base_cpz"),2);
				TeleportPlayer(i,GetPVarFloat(playerid,"f_wl_vw_base_attackx")+random(5),GetPVarFloat(playerid,"f_wl_vw_base_attacky")+random(5),GetPVarFloat(playerid,"f_wl_vw_base_attackz")+2,random(65535),.ignoreVec = true);
				OnPlayerCommandText(i,"/ww getweapon");
				SetPlayerHealth(i,100);
				SetPlayerArmour(i,100);
				loopPlayer(j){
					if(!strcmp(GetPVarFloat(j,"s_wl_vw_base_team"),"attack")){
						ShowPlayer(i,j);
					}
					else if(!strcmp(GetPVarFloat(j,"s_wl_vw_base_team"),"defence")){
						HidePlayer(i,j);
					}
					else{
						HidePlayer(i,j);
					}
				}
				VW_send(i,"[世界-base]全力进攻红点!");
				VW_send(i,"[世界-base]我们站在红点超过30s就胜利了!");
			}
		}
	}
}

forward vw_endBase(playerid,endmode);
public vw_endBase(playerid,endmode){ debug_public_track("vw_endBase(playerid,endmode){");
	//SendClientMessageToAll(COLOR_WHITE,"test");
	if(endmode == vw_base_end_defencewin) VW_sendAll("[世界-base]由%s(%d)举行的base,防守方获得胜利!",pName(playerid),playerid);
	else if(endmode == vw_base_end_attackwin) VW_sendAll("[世界-base]由%s(%d)举行的base,进攻方获得胜利!",pName(playerid),playerid);
	else if(endmode == vw_base_end_accident){
		loopPlayer(i){
			if(GetPVarInt(playerid,"i_wl_vw_base_id") == vw_getFromstr(pName(playerid))){
				VW_send(i,"[世界-base]因举办人掉线，base被迫取消了...");
			}
		}
	}
	else if(endmode == vw_base_end_exit){
		loopPlayer(i){
			if(GetPVarInt(playerid,"i_wl_vw_base_id") == vw_getFromstr(pName(playerid))){
				VW_send(i,"[世界-base]举办人强制结束了base...");
			}
		}
	}
	loopPlayer(i){
		if(GetPVarInt(i,"i_wl_vw_base_id") == vw_getFromstr(pName(playerid))){
			ResetPlayerWeapons(i);
			DisablePlayerCheckpoint(i);
			loopPlayer(j){
				ShowPlayer(i,j);
				//SetPlayerMarkerForPlayer(i,j,GetPlayerColor(j));
				//ShowPlayerNameTagForPlayer(i, j, true);
			}
			//SetPVarInt(playerid,"i_wl_vw_base_id",false);
			pVar_delete(playerid,"i_wl_vw_base_id");
			pVar_delete(playerid,"s_wl_vw_base_team")
			//SetPVarString(playerid,"s_wl_vw_base_team","null");
			//if(!strcmp(GetPVarFloat(i,"s_wl_vw_base_team"),"defence"){
		}
	}
	KillTimer(GetPVarInt(playerid,"i_wl_vw_base_looptimer"));
	KillTimer(GetPVarInt(playerid,"i_wl_vw_base_endtimer"));
	/*
	SetPVarInt(playerid,"i_wl_vw_base_timeCrack",0);
	SetPVarInt(playerid,"i_wl_vw_base_endtimer",false);
	SetPVarInt(playerid,"i_wl_vw_base_start",false);
	//pVar_delete(playerid,"s_wl_vw_base_startmode")
	SetPVarString(playerid,"s_wl_vw_base_startmode","null");
	SetPVarFloat(playerid,"f_wl_vw_base_cpx",0);
	SetPVarFloat(playerid,"f_wl_vw_base_cpy",0);
	SetPVarFloat(playerid,"f_wl_vw_base_cpz",0);
	SetPVarFloat(playerid,"f_wl_vw_base_defencex",0);
	SetPVarFloat(playerid,"f_wl_vw_base_defencey",0);
	SetPVarFloat(playerid,"f_wl_vw_base_defencez",0);
	SetPVarFloat(playerid,"f_wl_vw_base_attackx",0);
	SetPVarFloat(playerid,"f_wl_vw_base_attacky",0);
	SetPVarFloat(playerid,"f_wl_vw_base_attackz",0);
	SetPVarInt(playerid,"i_wl_vw_base_cptimeleft",0);	
	*/
	
	pVar_delete(playerid,"i_wl_vw_base_timeCrack");
	pVar_delete(playerid,"i_wl_vw_base_endtimer");
	pVar_delete(playerid,"i_wl_vw_base_start");
	pVar_delete(playerid,"s_wl_vw_base_startmode");
	pVar_delete(playerid,"f_wl_vw_base_cpx");
	pVar_delete(playerid,"f_wl_vw_base_cpy");
	pVar_delete(playerid,"f_wl_vw_base_cpz");
	pVar_delete(playerid,"f_wl_vw_base_defencex");
	pVar_delete(playerid,"f_wl_vw_base_defencey");
	pVar_delete(playerid,"f_wl_vw_base_defencez");
	pVar_delete(playerid,"f_wl_vw_base_attackx");
	pVar_delete(playerid,"f_wl_vw_base_attacky");
	pVar_delete(playerid,"f_wl_vw_base_attackz");
	pVar_delete(playerid,"i_wl_vw_base_cptimeleft");
	//SendClientMessageToAll(COLOR_WHITE,"test");
	return true;
}



zcmd(wl_vw_base,playerid,params[]){
	zcmd_advused();
	if(isnull(cmd_(1))){
		VW_send(playerid,"[世界-base]输入/b set 开设base");
		VW_send(playerid,"[世界-base]输入/b join 参加base");
		VW_send(playerid,"[世界-base]输入/b time 查看base剩余时间");
		VW_send(playerid,"[世界-base]输入/b end 强制结束base");
	}
	else if(compare("end",1)){
		if(GetPVarInt(playerid,"i_wl_vw_base_start")){
			if(GetPVarInt(playerid,"i_wl_vw_base_id") == vw_getFromstr(pName(playerid))){
				VW_send(playerid,"[世界-base]你强制结束了base");
				vw_endBase(playerid,vw_base_end_exit);
			}else{
				VW_send(playerid,"[世界-base]你只能结束专属世界的base");
			}
		}else{
			VW_send(playerid,"[世界-base]你并没有举行base");
		}
	}
	else if(compare("time",1)){
		if(GetPVarInt(playerid,"i_wl_vw_base_id")){
			new
				hostid = vw_getPlayerfromvwid(GetPVarInt(playerid,"i_wl_vw_base_id"));
			VW_send(playerid,"[世界-base]base剩余时间:%d秒",gvw_base_time-GetPVarInt(hostid,"i_wl_vw_base_timeCrack"));
		}else{
			VW_send(playerid,"[世界-base]你不在base里");
		}
	}
	else if(compare("set",1)){
		if(!vw_isplayerInplayerWorld(playerid,playerid)){
			VW_send(playerid,"[世界-base]请到专属世界开设base(输入/ww即可到达专属世界)");
			return true;
		}
		if(GetPVarInt(playerid,"i_wl_vw_base_start")){
			VW_send(playerid,"[世界-base]你已经开设base了");
			return true;
		}
		if(!pVar_exist(playerid,"s_wl_vw_base_startmode")){
			SetPVarString(playerid,"s_wl_vw_base_startmode","vw_playmode_base_start_setcp");
			VW_send(playerid,"[世界-base]你开始创建一个临时base");
			VW_send(playerid,"[世界-base]请设置守护点(走到守护点位置,输入/b set 即设定该位置为守护点)");
			new
				tmpstr[MAX_MSG_STR];
			format(tmpstr,MAX_MSG_STR,"[当前世界]%s(%d)开始创建一个临时base",pName(playerid),playerid);
			loopPlayer(i){
				if(GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i)){
					VW_send(i,tmpstr);
				}
			}
			//VW_sendIn(playerid,"[当前世界]%s(%d)开始创建一个临时base",pName(playerid),playerid);
		}
		else if(!strcmp(GetPVarFloat(playerid,"s_wl_vw_base_startmode"),"vw_playmode_base_start_setcp")){
			SetPVarString(playerid,"s_wl_vw_base_startmode","vw_playmode_base_start_setdefence");
			SetPVarFloat(playerid,"f_wl_vw_base_cpx",pX(playerid));
			SetPVarFloat(playerid,"f_wl_vw_base_cpy",pY(playerid));
			SetPVarFloat(playerid,"f_wl_vw_base_cpz",pZ(playerid));
			VW_send(playerid,"[世界-base]你设置了守护点");
			VW_send(playerid,"[世界-base]请设置防守方出生点(走到防守方出生点位置，输入/b set 即可)");
			VW_send(playerid,"[世界-base]注意出生点周围要比较空旷");
		}
		else if(!strcmp(GetPVarFloat(playerid,"s_wl_vw_base_startmode"),"vw_playmode_base_start_setdefence")){
			SetPVarString(playerid,"s_wl_vw_base_startmode","vw_playmode_base_start_setattack");
			SetPVarFloat(playerid,"f_wl_vw_base_defencex",pX(playerid));
			SetPVarFloat(playerid,"f_wl_vw_base_defencey",pY(playerid));
			SetPVarFloat(playerid,"f_wl_vw_base_defencez",pZ(playerid));
			VW_send(playerid,"[世界-base]你设置了防守方出生点");
			VW_send(playerid,"[世界-base]请设置进攻方出生点(走到进攻方出生点位置，输入/b set 即可)");
			VW_send(playerid,"[世界-base]注意出生点周围要比较空旷");
		}
		else if(!strcmp(GetPVarFloat(playerid,"s_wl_vw_base_startmode"),"vw_playmode_base_start_setattack")){
			SetPVarInt(playerid,"i_wl_vw_base_start",true);
			pVar_delete(playerid,"s_wl_vw_base_startmode");
			//SetPVarString(playerid,"s_wl_vw_base_startmode","null");
			SetPVarFloat(playerid,"f_wl_vw_base_attackx",pX(playerid));
			SetPVarFloat(playerid,"f_wl_vw_base_attacky",pY(playerid));
			SetPVarFloat(playerid,"f_wl_vw_base_attackz",pZ(playerid));
			SetTimerEx("vw_startBase",1000*30,false,"i",playerid);
			VW_send(playerid,"[世界-base]你设置了进攻方出生点");
			new
				tmpstr[MAX_MSG_STR];
			format(tmpstr,MAX_MSG_STR,"[当前世界]%s(%d)创建临时base完毕,请选择队伍,30秒后自动开始!",pName(playerid),playerid);
			loopPlayer(i){
				if(GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i)){
					VW_send(i,tmpstr);
					VW_send(i,"[世界-base]输入/b join attack 加入攻击方");
					VW_send(i,"[世界-base]输入/b join defence 加入防守方");
				}
			}
			//VW_sendIn(playerid,"[当前世界]%s(%d)创建临时base完毕,30秒后自动开始!",pName(playerid),playerid);
		}
	}
	else if(compare("help",1)){
		VW_send(playerid,"[世界-base]输入/b set 开设base");
		VW_send(playerid,"[世界-base]输入/b join 参加base");
		VW_send(playerid,"[世界-base]输入/b time 查看base剩余时间");
		VW_send(playerid,"[世界-base]输入/b end 强制结束base");
	}
	else if(compare("join",1)){
		new
			starterid = vw_getPlayerfromvwid(GetPlayerVirtualWorld(playerid));
		if(IsPlayerConnected(starterid) && GetPVarInt(starterid,"i_wl_vw_base_start")){
			if(compare("attack",2)){
				SetPVarInt(playerid,"i_wl_vw_base_id",GetPlayerVirtualWorld(playerid));
				SetPVarString(playerid,"s_wl_vw_base_team","attack");
				VW_send(playerid,"[世界-base]你加入了攻击方");
				new
					tmpstr[MAX_MSG_STR];
				format(tmpstr,MAX_MSG_STR,"[世界-base]%s(%d)加入了攻击方,!",pName(playerid),playerid);
				loopPlayer(i){
					if(GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i)){
						VW_send(i,tmpstr);
					}
				}
			}
			else if(compare("defence",2)){
				SetPVarInt(playerid,"i_wl_vw_base_id",GetPlayerVirtualWorld(playerid));
				SetPVarString(playerid,"s_wl_vw_base_team","defence");
				VW_send(playerid,"[世界-base]你加入了防守方");
				new
					tmpstr[MAX_MSG_STR];
				format(tmpstr,MAX_MSG_STR,"[世界-base]%s(%d)加入了防守方,!",pName(playerid),playerid);
				loopPlayer(i){
					if(GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i)){
						VW_send(i,tmpstr);
					}
				}
			}
			else{
				VW_send(playerid,"[世界-base]你输入的队伍不存在");
				VW_send(playerid,"[世界-base]输入/b join attack 加入攻击方");
				VW_send(playerid,"[世界-base]输入/b join defence 加入防守方");
				
			}
		}
		else{
			VW_send(playerid,"[世界-base]该世界没有临时base");
		}
	}
	else{
		VW_send(playerid,"[世界-base]你输入的命令不存在");
		VW_send(playerid,"[世界-base]输入/b set 开设base");
		VW_send(playerid,"[世界-base]输入/b join 参加base");
		VW_send(playerid,"[世界-base]输入/b time 查看base剩余时间");
		VW_send(playerid,"[世界-base]输入/b end 强制结束base");
	}
	return true;
}

zcmd(base,playerid,params[]){return zcmd_wl_vw_base(playerid,params);}
zcmd(b,playerid,params[]){return zcmd_wl_vw_base(playerid,params);}