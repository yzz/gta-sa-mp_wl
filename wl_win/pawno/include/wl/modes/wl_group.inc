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


//=======================================Group======================================
#define DEBUG_GROUP				(true)
#define COLOR_GROUP				(0xFF4F3C)
#define MAX_GROUPS				(MAX_PLAYERS)
#define MAX_GROUP_MEMBERS		(MAX_PLAYERS)
#define MAX_GROUP_NAME			(24)
#define INVALID_GROUP_ID		(0)

enum{
	group_tele_none,
	group_tele_goto,
	group_tele_gethere,
	group_request_none,
	group_request_goto,
	group_request_gethere
};
const
	Group_requestTele_Time = 5000;

//===================================================================================


enum _Group_Info{
	Name[MAX_GROUP_NAME],
	//Member[MAX_GROUP_MEMBERS],
	bool:active,
	Members,
	Color
};
static GroupInfo[MAX_GROUPS][_Group_Info];





stock Group_isValid(groupid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_isValid called");
	#endif
	return (groupid > INVALID_GROUP_ID && groupid < MAX_GROUPS)?true:false;
}
stock Group_getPlayerInvited(playerid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_getPlayerInvited called");
	#endif
	return PlayerInfo[playerid][Group_Invited];
}

stock Group_getName(groupid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_getName called");
	#endif
	return GroupInfo[groupid][Name];

}

stock Group_setName(groupid,const group_name[]){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_setName called");
	#endif
	format(GroupInfo[groupid][Name],MAX_GROUP_NAME,"%s",group_name);
	return true;
}


stock Group_getMemberAmount(groupid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_getMemberAmount called");
	#endif
	if(GroupInfo[groupid][active]){
		return GroupInfo[groupid][Members];
	}
	return 0;
}
stock Group_setMemberAmount(groupid,amount){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_setMemberAmount called");
	#endif
	GroupInfo[groupid][Members] = amount;
	return true;
}


stock Group_isPlayerMember(groupid,playerid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_isPlayerMember called");
	#endif
	return (PlayerInfo[playerid][Group_Joined] == groupid)?true:false;
}
stock Group_setMember(groupid,playerid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_setMember called");
	#endif
	GroupInfo[groupid][Members]++;
	PlayerInfo[playerid][Group_Joined] = groupid;
	PlayerInfo[playerid][Group_Invited] = groupid;
	return true;
}
stock Group_removeMember(groupid,playerid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_removeMember called");
	#endif
	PlayerInfo[playerid][Group_Joined] = INVALID_GROUP_ID;
	PlayerInfo[playerid][Group_Invited] = INVALID_GROUP_ID;
	GroupInfo[groupid][Members]--;
	return false;
}


stock Group_setColor(groupid,color){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_setColor called");
	#endif
	GroupInfo[groupid][Color] = color;
	return true;
}
stock Group_getColor(groupid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_getColor called");
	#endif
	
	if(GroupInfo[groupid][active]){
		return GroupInfo[groupid][Color];
	}
	return 0;
}


stock Group_setActive(groupid,bool:Active){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_setActive called");
	#endif
	GroupInfo[groupid][active] = Active;
	return true;
}
stock Group_isActive(groupid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_isActive called");
	#endif
	return (Group_isValid(groupid) && GroupInfo[groupid][active])?true:false;
}


stock Group_setPlayerInvited(groupid,playerid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_setPlayerInvited called");
	#endif
	wl_sPlr_Group_Invited(playerid,groupid);
	return true;
}
stock Group_getPlayer(playerid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_getPlayer called");
	#endif
	return wl_gPlr_Group_Joined(playerid);
}

stock Group_setPlayerTele(playerid,teleportype){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_setPlayerTele called");
	#endif
	
	wl_sPlr_Group_requestTele(playerid,teleportype);
	return true;
}

stock Group_getPlayerTele(playerid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_getPlayerTele called");
	#endif
	return wl_gPlr_Group_requestTele(playerid);
}

stock Group_setTeleRequester(player,playee){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_setTeleRequester called");
	#endif
	wl_sPlr_Group_requester(player,playee);
	return true;
}
stock Group_getTeleRequester(player){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_getTeleRequester called");
	#endif
	return wl_gPlr_Group_requester(player);
}






//=========================Group=========================================
#define Group_send(%1,%2,%3) \
do{\
	new \
		sendfstring[MAX_STRING];\
	format(sendfstring,MAX_STRING,(%2),%3);\
	SendClientMessage((%1),COLOR_GROUP,sendfstring);\
}while(FALSE)

stock Group_send(playerid,const sendfstring[]){
	SendClientMessage(playerid,COLOR_GROUP,sendfstring);
}

#define Group_sendAll(%1,%2) \
do{ \
	new \
	sendfstring[MAX_STRING];\
	format(sendfstring,MAX_STRING,(%1),%2);\
	SendClientMessageToAll(COLOR_GROUP,sendfstring);\
}while(FALSE)
stock Group_sendAll(const sendfstring[]){
	SendClientMessageToAll(COLOR_GROUP,sendfstring);
}


#define Group_sendMember(%1,%2,%3) \ 
do{ \
	new \
		sendfstring[MAX_STRING];\
	new const \
		color = Group_getColor((%1));\
	format(sendfstring,MAX_STRING,(%2),%3);\
	loopPlayer(tmptmptmpval){\
		if(Group_getPlayer(tmptmptmpval) == (%1)){\
			SendClientMessage(tmptmptmpval,color,sendfstring);\
		} \
	} \
}while(FALSE)

stock Group_sendMember(groupid,const group_msg[]){
	loopPlayer(playerid){
		if(Group_getPlayer(playerid) == groupid){
			SendClientMessage(playerid,Group_getColor(groupid),group_msg);
		}
	}
}
//===================================================================//

forward Group_rejectTeleport(player,playee,teleportype);//used for timer




stock Group_Help(playerid){
	#if DEBUG_GROUP
		print("[DEBUG_GROUP]Group_help called");
	#endif
	
	Group_send(playerid,"[团队]团队帮助:");
	Group_send(playerid,"/group create [名称]---创建小团队");
	Group_send(playerid,"/group join ---加入团队");
	Group_send(playerid,"/group invite [玩家ID] ---邀请玩家加入团队");
	Group_send(playerid,"/group refuse  ---拒绝当前团队的邀请");
	Group_send(playerid,"/group leave ---退出当前团队");
	Group_send(playerid,"/group info [号码]---显示团队的信息");
	Group_send(playerid,"------->/group goto 或者 gethere [玩家ID] ---传送到玩家身边<-------");
	Group_send(playerid,"@ ---输入内容可以团队聊天");
	return true;
}





stock Group_PlayerInvitePlayer(inviter,invitee){
	#if DEBUG_GROUP
		print("[DEBUG_GROUP]Group_PlayerInvitePlayer called");
	#endif
	if(IPC(invitee)){
		if(!Group_getPlayerInvited(invitee)){
			if(!Group_getPlayer(invitee) && Group_getPlayer(inviter)){
				new
					group_name[MAX_GROUP_NAME],
					groupid = Group_getPlayer(inviter);
				
				format(group_name,MAX_GROUP_NAME,"%s",Group_getName(groupid));
				Group_setPlayerInvited(groupid,invitee);
				Group_send(invitee,"[团队]您被邀请加入'%s'(id:%d)组织,邀请者 %s(%d)",group_name,groupid,PlayerName(inviter),inviter);
				Group_sendMember( \
					groupid,"[组频]%s(%d)邀请 %s(%d)加入我们的组织", \
					PlayerName(inviter),inviter,PlayerName(invitee),invitee \
				);
			}else
			{
				Group_send(inviter,"[团队]%s(%d)已经有组织了,不能邀请",PlayerName(invitee),invitee);
			}
		}else
		{
			Group_send(inviter,"[团队]%s(%d)已经被邀请了,不能邀请",PlayerName(invitee),invitee);
		}
	}else
	{
		Group_send(inviter,"[团队]对方不在线");
	}
	return true;
}



stock Group_PlayerCreate(playerid,const group_name[]){
	#if DEBUG_GROUP
		print("[DEBUG_GROUP]Group_PlayerCreate called");
	#endif
	if(!Group_getPlayer(playerid)){
		new
			groupid;
		for(new i=1;i<MAX_GROUPS;i++){
			if(!Group_isActive(i)){
				groupid = i;
				break;
			}			
		}
		if(
			Group_setName(groupid,group_name) &&
			Group_setMember(groupid,playerid) &&
			Group_setColor(groupid,GetPlayerColor(playerid)) &&
			Group_setActive(groupid,true)
		){
			Group_send(playerid,"[团队]你创建了组织'%s'(id:%d)",Group_getName(groupid),groupid);
		}
	}else
	{
		Group_send(playerid,"[团队]你已经在一个组织了,不能创建新组织");
	}
	return true;
}



stock Group_PlayerCheckInfo(playerid,groupid){
	#if DEBUG_GROUP
		print("[DEBUG_GROUP]Group_PlayerCheckInfo called");
	#endif
	if(Group_isActive(groupid)){
		Group_send(playerid,"[团队]=============================================================");
		Group_send(playerid,"[团队]'%s'(id:%d) 成员",Group_getName(groupid),groupid);
		for(new i,j = Group_getMemberAmount(groupid);i < j;i++){
			loopPlayer(k){
				if(Group_isPlayerMember(groupid,k)){
					Group_send(playerid,"[团队]%s(%d)",PlayerName(k),k);
				}
			}
		}
		Group_send(playerid,"[团队]============================================================");
	}else
	{
		Group_send(playerid,"[团队]你没有加入任何组织.");
	}
	return true;
}



stock Group_PlayerJoin(playerid){
	#if DEBUG_GROUP
		print("[DEBUG_GROUP]Group_PlayerJoin called");
	#endif
	if(Group_getPlayerInvited(playerid)){
		new
			groupid = Group_getPlayerInvited(playerid);
		Group_setPlayerInvited(INVALID_GROUP_ID,playerid);
		Group_setMember(groupid,playerid);
		SetPlayerColor(playerid,Group_getColor(groupid));
		Group_Help(playerid);
		Group_sendMember(groupid,"[团队]欢迎 %s(%d)加入该组织^^",PlayerName(playerid),playerid);
	}else
	{
		Group_send(playerid,"[团队]加入失败,请确认你能否加入组织");
	}
	return true;
}


stock Group_PlayerRefuse(playerid){
	#if DEBUG_GROUP
		print("[DEBUG_GROUP]Group_PlayerRefuse called");
	#endif
	if(Group_getPlayerInvited(playerid)){
		new 
			groupid = Group_getPlayerInvited(playerid);
			//group_name[MAX_GROUP_NAME];
		
		//Group_getName(groupid,group_name);
		Group_sendMember(groupid,"[组频]%s(%d)拒绝加入我帮",PlayerName(playerid),playerid);
		Group_send(playerid,"[团队]你拒绝加入组织%s(%d)",Group_getName(groupid),groupid);
		Group_setPlayerInvited(INVALID_GROUP_ID,playerid);
	}else
	{
		Group_send(playerid,"[团队]拒绝无效");
	}
	return true;
}

stock Group_PlayerLeave(playerid){
	#if DEBUG_GROUP
		print("[DEBUG_GROUP]Group_PlayerLeave called");
	#endif
	if(Group_getPlayer(playerid)){
		new
			groupid = Group_getPlayer(playerid),
			group_name[MAX_GROUP_NAME];
		
		format(group_name,MAX_GROUP_NAME,"%s",Group_getName(groupid));
		Group_removeMember(groupid,playerid);
		SetPlayerColor(playerid,COLOR_WHITE);
		if(!Group_getMemberAmount(groupid)){
			loopPlayer(i){
				if(Group_getPlayerInvited(i) == groupid){
					Group_setPlayerInvited(INVALID_GROUP_ID,i);
				}
			}
			Group_setActive(groupid,false);
			Group_send(playerid,"[团队]你离开了原来的组织,原组织解散");
		}else
		{
			if(!IPC(playerid)){
				Group_sendMember(groupid,"[组频](%d)离开了组织(原因:下线)",playerid);
			}else
			{
				Group_send(playerid,"[团队]你离开了原来的组织%s(%d)",group_name,groupid);
				Group_sendMember(groupid,"[组频]%s(%d)离开了组织",PlayerName(playerid),playerid);
			}
		}
	}
	return true;
}


public Group_rejectTeleport(player,playee,teleportype){ debug_public_track("Group_rejectTeleport(player,playee,teleportype){");
	#pragma unused teleportype
	if(Group_getPlayerTele(playee) && Group_getPlayerTele(player)){
		Group_setPlayerTele(playee,group_tele_none);
		Group_setPlayerTele(player,group_tele_none);
		Group_setTeleRequester(player,INVALID_PLAYER_ID);
		Group_send(playee,"[团队][传送]%s拒绝了你的传送请求(超时或拒绝)",PlayerName(player));
		Group_send(player,"[团队][传送]你拒绝了%s的传送请求(超时或拒绝)",PlayerName(playee));
		remindPlayerText(playee,"%s has rejected ur request",PlayerName(player));
		remindPlayerText(player,"You have rejected %s's request",PlayerName(playee));
	}
	return true;
}

stock Group_acceptTeleport(player,playee,teleportype){
	if(Group_getPlayerTele(playee) && Group_getPlayerTele(player)){
		new
			Float:pposx,
			Float:pposy,
			Float:pposz;
		switch(teleportype){
			case group_tele_goto:{
				GetPlayerPos(player,pposx,pposy,pposz);
				TeleportPlayer(playee,pposx,pposy,pposz);
			}
			case group_tele_gethere:{
				GetPlayerPos(playee,pposx,pposy,pposz);
				TeleportPlayer(player,pposx,pposy,pposz);
			}
		}
		
		Group_setPlayerTele(playee,group_tele_none);
		Group_setPlayerTele(player,group_tele_none);
		Group_setTeleRequester(player,INVALID_PLAYER_ID);	
		Group_send(playee,"[团队][传送]%s接受了你的传送请求",PlayerName(player));
		Group_send(player,"[团队][传送]你接受了%s的传送请求",PlayerName(playee));
		remindPlayerText(playee,"%s has accepted ur request",PlayerName(player));
		remindPlayerText(player,"You have accepted %s's request",PlayerName(playee));	
	}
	return true;
}

stock Group_requestTeleport(player,playee,teleportype){
	if(Group_getPlayer(player) && Group_getPlayer(player) == Group_getPlayer(playee)){
		if(!Group_getPlayerTele(playee) && !Group_getPlayerTele(player)){
			Group_setPlayerTele(playee,teleportype);
			Group_setPlayerTele(player,teleportype+3);
			SetTimerEx("Group_rejectTeleport",Group_requestTele_Time,false,"iii",player,playee,teleportype);
			Group_setTeleRequester(playee,player);
			switch(teleportype){
				case group_tele_goto:{
					Group_send(playee,"[团队][传送]%s请求传送到你身旁,请在%d秒内输入yes或者no回应",PlayerName(player),Group_requestTele_Time/1000);
					Group_send(player,"[团队][传送]你请求传送到%s身旁,请在%ds内等待回应",PlayerName(playee),Group_requestTele_Time/1000);
					remindPlayerText(playee,"%s is requesting for teleporting",PlayerName(player));
				}
				case group_tele_gethere:{
					Group_send(playee,"[团队][传送]%s邀请你到他旁边,请在%d秒内输入yes或者no回应",PlayerName(player),Group_requestTele_Time);
					Group_send(player,"[团队][传送]你邀请%s到你旁边,请在%d秒内等待回应",PlayerName(playee),Group_requestTele_Time);
					remindPlayerText(playee,"%s is requesting for teleporting",PlayerName(player));
				}
			}
		}else
		{
			Group_send(player,"[团队][传送]有人处于传送状态,邀请失败,请稍后再试");
		}
	}else
	{
		Group_send(player,"[团队][传送]双方不属于同一组织,邀请失败");
	}
	return true;
}


/*
gcmd(gg_group){
	
	if(paramn(1)){
		Group_Help(player());
	}else if(paramsame(1,"goto")){
		if(!paramn(2) && IsNumeric(params(2)) && IsPlayerConnected(parami(2))) 
			Group_requestTeleport(player(),parami(2),group_tele_goto);
		else Group_send(player(),"[团队]输入的玩家ID无效");
	}else if(paramsame(1,"gethere")){
		if(!paramn(2) && IsNumeric(params(2)) && IsPlayerConnected(parami(2))) 
			Group_requestTeleport(player(),parami(2),group_tele_gethere);
		else Group_send(player(),"[团队]输入的玩家ID无效");
	}else if(paramsame(1,"invite")){
		if(!paramn(2) && IsNumeric(params(2)) && IsPlayerConnected(parami(2))) 
			Group_PlayerInvitePlayer(player(),parami(2));
		else Group_send(player(),"[团队]输入的玩家ID无效");
	}else if(paramsame(1,"info")){
		if(paramn(2)) Group_PlayerCheckInfo(playerid,Group_getPlayer(player()));
		else Group_PlayerCheckInfo(player(),parami(2));
	}else if(paramsame(1,"create")){
		if(paramn(2)) Group_send(playerid,"[团队]请输入你要创建的团队的名称");
		else Group_PlayerCreate(playerid,params(2));
	}else if(paramsame(1,"join")){
		Group_PlayerJoin(player());	
	}else if(paramsame(1,"refuse")){
		Group_PlayerRefuse(player());	
	}else if(paramsame(1,"leave")){
		if(Group_getPlayer(player())) Group_PlayerLeave(player());
		else Group_send(player(),"[团队]你没有加入任何组织,怎么离开?");
	}else if(paramsame(1,"help")){
		Group_Help(player());
	}else{
		Group_send(player(),"[团队]你输入的子命令\"%s\"无效,请输入/group help 查看帮助",params);
	}
}
*/
/*
gg_OnPlayerText(playerid,text[]){
	if(text[0] == '@' && text[1]){
		if(Group_getPlayer(playerid)){
			Group_sendMember( \
				Group_getPlayer(playerid),"[组频]%s(%d):%s", \
				PlayerName(playerid),playerid,text[1]\
			);
		}else{
			Group_send(playerid,"[团队]你没有加入任何组织,不能使用组频");
		}
		return false;
	}else
	if(
		text[0] == 'y' && text[1] == 'e' && text[2] == 's' &&
		Group_getPlayerTele(playerid) == group_tele_goto ||
		Group_getPlayerTele(playerid) == group_tele_gethere
	){
		Group_acceptTeleport(playerid,Group_getTeleRequester(playerid),Group_getPlayerTele(playerid));
		return false;
	}else
	if(text[0] == 'n' && text[1] == 'o' && 
		Group_getPlayerTele(playerid) == group_tele_goto ||
		Group_getPlayerTele(playerid) == group_tele_gethere
	){
		Group_rejectTeleport(playerid,Group_getTeleRequester(playerid),Group_getPlayerTele(playerid));
		return false;
	}
	return true;
}


gg_OnPlayerDisconnect(playerid,reason){
	#pragma unused reason
	Group_PlayerLeave(playerid);
	return true;
}
*/
