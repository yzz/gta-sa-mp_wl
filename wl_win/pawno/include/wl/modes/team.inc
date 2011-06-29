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





#define INVALID_TEAM_ID		(-1)
#define COLOR_TEAM			(COLOR_LIGHTBLUE)


//===================team handle==================================
#define team_send(%1,%2,%3)	\
	format(ssstr,MAX_MSG_STR,(%2),%3); \
	SendClientMessage((%1),COLOR_TEAM,ssstr)
	
stock team_send(playerid,const sendfstring[]){
	SendClientMessage(playerid,COLOR_TEAM,sendfstring);
}

#define team_sendAll(%1,%2)	\
	format(ssstr,MAX_MSG_STR,(%1),%2); \
	SendClientMessageToAll(COLOR_TEAM,ssstr)
	
stock team_sendAll(const sendfstring[]){
	SendClientMessageToAll(COLOR_TEAM,sendfstring);
}
//===================================================================================

/*
stock GetPlayerAdminLevel(playerid){
	return CallRemoteFunction("GetPlayerAdminLevel","i",playerid);
}
*/


static stock
	
	//gTeam_pLevel[MAX_PLAYERS],

	//gTeam_pTeam[MAX_PLAYERS],
	gTeam_index = 10;


stock team_spLevel(playerid,level){
	SetPVarInt(playerid,"wl_team_player_level",level);
	return true;
}

stock team_gpLevel(playerid){
	return GetPVarInt(playerid,"wl_team_player_level");
}

stock team_spTeam(playerid,teamid){
	SetPVarInt(playerid,"wl_team_player_team",teamid);
	return true;
}

stock team_gpTeam(playerid){
	return GetPVarInt(playerid,"wl_team_player_team");
}

stock team_spInNew(playerid){
	++gTeam_index;
	return team_spTeam(playerid,gTeam_index);
}


team_struct(){
	for(new i;i<MAX_PLAYERS;i++){
		team_spTeam(i,INVALID_TEAM_ID);
		team_spLevel(i,0);
	}
}

team_pregister(playerid){
	#pragma unused playerid
	gini_writei(acc_pLevel,0);
}

team_plogin(playerid){
	team_spLevel(playerid,gini_readi(acc_pLevel));
	//team_sp(playerid,gini_readi(acc_pLevel));
}

team_playerConnect(playerid){
	new
		endpos,
		plrTeamslot = INVALID_TEAM_ID;
	if(strfind(pName(playerid),"[") == 0 && (endpos = strfind(pName(playerid),"]")) != -1){
		loopPlayer(i){
			if(playerid == i)continue;
			if(!strcmp(pName(playerid),pName(i),true,endpos)){
				plrTeamslot = team_gpTeam(i);
				break;
			}
		}
		if(plrTeamslot != INVALID_TEAM_ID){
			team_spTeam(playerid,plrTeamslot);
		}
		else {
			team_spInNew(playerid);
		}
	}
	else {
		team_spTeam(playerid,INVALID_TEAM_ID);
	}
}

team_playerDisconnect(playerid){
   team_spTeam(playerid,INVALID_TEAM_ID);
   team_spLevel(playerid,0);
}

team_playerText(playerid,text[]){
	if(text[0] == '!' && text[1]){
        if(team_gpTeam(playerid) != INVALID_TEAM_ID){
            new 
				sendstr[MAX_MSG_STR];
            format(sendstr, sizeof(sendstr),"    [团聊]%s(%d): %s", pName(playerid),playerid, text[1]);
			loopPlayer(i){
				if(team_gpTeam(playerid) == team_gpTeam(i)){
					SendClientMessage(i,COLOR_TEAM,sendstr);
				}
			}
			return false;
		}
	}
    return true;
}


TODOList_teaminc(){}
/*
zcmd(team_handle,playerid,params[]){ //todo
	new
		str1[128],str2[128],
		id;
	sscanf(params,"ss",str1,str2);
	id = strval(str2);
	//printf("%d_ %s",id,str2);
	if(!strcmp("makeadmin",str1)){
		if(GetPlayerAdminLevel(playerid) < 3 && team_gpLevel(playerid) < 5){
			team_send(playerid,"[团队]你没有足够的权限使用该命令");
			return true;
		}
		if(isnull(str2)){
			team_send(playerid,"[团队]请输入玩家ID");
			return true;
		}
		if(!IsNumeric(str2)){
			team_send(playerid,"[团队]ID不合法");
			return true;
		}
		if(!IsPlayerConnected(id)){
			team_send(playerid,"[团队]ID为%d的玩家不存在",id);
			return true;
		}
		if(team_gpTeam(id) == INVALID_TEAM_ID){
			team_send(playerid,"[团队]该玩家不属于任何一个团队");
			return true;
		}
		if(!pLogged(id)){
			team_send(playerid,"[团队]该玩家未登陆，不能设置为团队管理员");
			return true;
		}
		if(GetPlayerAdminLevel(playerid) >= 3){
			gini_open(player_getAccount(id));
			gini_writei(acc_pLevel,5);
			gini_save();
			gini_close();
			team_spLevel(id,5);
			team_send(playerid,"[团队]你设置%s(%d)为5级团队管理员",pName(id),id);
			team_send(id,"[团队]你被%s(%d)设置为5级团队管理员,请管理好你的团队成员!",pName(playerid),playerid);
		}
		else if(team_gpLevel(playerid) >= 5 && team_gpTeam(id) == team_gpTeam(playerid)){
			gini_open(player_getAccount(id));
			gini_writei(acc_pLevel,3);
			gini_save();
			gini_close();
			team_spLevel(id,3);
			team_send(playerid,"[团队]你设置%s(%d)为3级团队管理员",pName(id),id);
			team_send(id,"[团队]你被%s(%d)设置为3级团队管理员,请管理好你的团队成员!",pName(playerid),playerid);
		}
		else {
			team_send(playerid,"[团队]设置方和你不属同一团队，设置对方为3级管理员失败");
		}
	}
	else if(!strcmp("unmakeadmin",str1)){
		if(GetPlayerAdminLevel(playerid) < 3 && team_gpLevel(playerid) < 5){
			team_send(playerid,"[团队]你没有足够的权限使用该命令");
			return true;
		}
		if(isnull(str2)){
			team_send(playerid,"[团队]请输入玩家ID");
			return true;
		}
		if(!IsNumeric(str2)){
			team_send(playerid,"[团队]ID不合法");
			return true;
		}
		if(!IsPlayerConnected(id)){
			team_send(playerid,"[团队]ID为%d的玩家不存在",id);
			return true;
		}
		if(team_gpTeam(id) == INVALID_TEAM_ID){
			team_send(playerid,"[团队]该玩家不属于任何一个团队");
			return true;
		}
		if(!pLogged(id)){
			team_send(playerid,"[团队]该玩家未登陆，不能设置为团队管理员");
			return true;
		}
		if(GetPlayerAdminLevel(playerid) >= 3){
			gini_open(player_getAccount(id));
			gini_writei(acc_pLevel,0);
			gini_save();
			gini_close();
			team_spLevel(id,0);
			team_send(playerid,"[团队]你取消了%s(%d)团队管理员权限",pName(id),id);
			team_send(id,"[团队]你被%s(%d)取消了团队管理员权限!",pName(playerid),playerid);
		}
		else if(team_gpLevel(playerid) >= 5 && team_gpTeam(id) == team_gpTeam(playerid)){
			gini_open(player_getAccount(id));
			gini_writei(acc_pLevel,0);
			gini_save();
			gini_close();
			team_spLevel(id,0);
			team_send(playerid,"[团队]你取消了%s(%d)团队管理员权限",pName(id),id);
			team_send(id,"[团队]你被%s(%d)取消了团队管理员权限!",pName(playerid),playerid);
		}
		else {
			team_send(playerid,"[团队]设置方和你不属同一团队，取消对方团队管理员失败");
		}
	}
	else if(!strcmp("kill",str1)){
		if(!team_gpLevel(playerid)){
			team_send(playerid,"[团队]你无权使用该命令");
			return true;
		}
		if(isnull(str2) || !IsPlayerConnected(id)){
			team_send(playerid,"[团队]你输入的玩家ID不存在/在线");
			return true;
		}
		if(team_gpTeam(id) != team_gpTeam(playerid)){
			team_send(playerid,"[团队]对方不是同队成员");
			return true;
		}
		SetPlayerHealth(id,0);
		team_send(id,"[团队]你被团队管理员%s(%d)赐死",pName(playerid),playerid);
		team_send(playerid,"[团队]你使用管理命令将团队成员%s(%d)的血量设置为0",pName(id),id);
	}
	else if(!strcmp("kick",str1)){
		if(!team_gpLevel(playerid)){
			team_send(playerid,"[团队]你无权使用该命令");
			return true;
		}
		if(isnull(str2) || !IsPlayerConnected(id)){
			team_send(playerid,"[团队]你输入的玩家ID不存在/在线");
			return true;
		}
		if(team_gpTeam(id) != team_gpTeam(playerid)){
			team_send(playerid,"[团队]对方不是同队成员");
			return true;
		}
		Kick(id);
		team_send(id,"[团队]你被团队管理员%s(%d)踢出服务器",pName(playerid),playerid);
		team_send(playerid,"[团队]你使用管理命令将团队成员%s(%d)踢出服务器",pName(id),id);
	}
	else if(!strcmp("goto",str1)){
		if(!team_gpLevel(playerid)){
			team_send(playerid,"[团队]你无权使用该命令");
			return true;
		}
		if(isnull(str2) || !IsPlayerConnected(id)){
			team_send(playerid,"[团队]你输入的玩家ID不存在/在线");
			return true;
		}if(team_gpTeam(id) != team_gpTeam(playerid)){
			team_send(playerid,"[团队]对方不是同队成员");
			return true;
		}
		TeleportPlayer(playerid,pX(id),pY(id),pZ(id),pAngle(id),pInterior(id),false,pVirtualWorld(id));
		team_send(id,"[团队]团队管理员%s(%d)传送到你身边",pName(playerid),playerid);
		team_send(playerid,"[团队]你传送到团队成员%s(%d)身边",pName(id),id);
	}
	else if(!strcmp("gethere",str1)){
		if(!team_gpLevel(playerid)){
			team_send(playerid,"[团队]你无权使用该命令");
			return true;
		}
		if(isnull(str2) || !IsPlayerConnected(id)){
			team_send(playerid,"[团队]你输入的玩家ID不存在/在线");
			return true;
		}if(team_gpTeam(id) != team_gpTeam(playerid)){
			team_send(playerid,"[团队]对方不是同队成员");
			return true;
		}
		TeleportPlayer(id,pX(playerid),pY(playerid),pZ(playerid),pAngle(playerid),pInterior(playerid),false,pVirtualWorld(playerid));
		team_send(id,"[团队]你被传送到团队管理员%s(%d)身边",pName(playerid),playerid);
		team_send(playerid,"[团队]团队成员%s(%d)被你传送到你身边",pName(id),id);
	}
	else if(!strcmp("help",str1)){
		#define DG_TEAM_HELP_CAPTION	"团队系统帮助:"
		#define DG_TEAM_HELP_INFO	"介绍:拥有相同队标的玩家将自动组成团队\n \n玩家可用命令:/t help\n普通成员可用命令: !聊天信息 - 队内聊天\n\
									3级团队管理员命令:\n    /t goto/gethere [玩家id] - 进行传送操作\n    \
									/t kill - 杀死指定团队成员\n    /t kick - 把指定成员踢出服务器\n\
									5级/服务器管理员命令:\n    /t makeadmin [玩家id] - 将指定玩家设置为团队管理员\n    /t unmakeadmin [玩家id] - 取消玩家管理员权限\n"
		#define DG_TEAM_HELP_BUTTON1	"确定"
		#define DG_TEAM_HELP_BUTTON2	"取消"
		ShowPlayerDialog(playerid,1,DIALOG_STYLE_LIST,DG_TEAM_HELP_CAPTION,DG_TEAM_HELP_INFO,DG_TEAM_HELP_BUTTON1,DG_TEAM_HELP_BUTTON2);
	}
	else if(!strcmp("info",str1)){
		loopPlayer(i){
			//if(!pLogged(i) || team_gpTeam(i) == INVALID_TEAM_ID) continue;
			team_send(playerid,"debug:%d(%s) team:%d level:%d logged:%d",i,pName(i),team_gpTeam(i),team_gpLevel(i),pLogged(i));
		}
	}
	else {
		team_send(playerid,"[团队]你输入的子命令'%s'不存在",params);
	}
	return true;
}
pzcmd(t){rzcmd(team_handle);}
pzcmd(team){rzcmd(team_handle);}
*/







