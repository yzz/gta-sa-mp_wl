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







new
	punishKill_pTick[MAX_PLAYERS];

punishKill_PlayerUpdate(playerid){
	if(GetTickCount() - punishKill_pTick[playerid] > 551){ //prefix check itter
		#define holdingEx2(%0) ((keys & (%0)) == (%0))
		new
			keys, updown, leftright,tmpstr[128],
			vwid = GetPlayerVirtualWorld(playerid);
		static
			Float:XZC[14];
		GetPlayerCameraPos(playerid, XZC[10], XZC[11], XZC[12]);
		GetPlayerCameraFrontVector(playerid, XZC[7], XZC[8], XZC[9]);
		GetPlayerPos(playerid, XZC[0], XZC[1], XZC[2]);

		GetPlayerKeys(playerid,keys,updown,leftright);
		if(holdingEx2(KEY_FIRE)){
			for(new i;i<MAX_PLAYERS;i++){
				if(i != playerid && IsPlayerConnected(i) && GetPlayerVirtualWorld(i) == vwid){
					GetPlayerPos(i, XZC[3], XZC[4], XZC[5]);
					GetDistanceFromPointToLine(XZC[6], XZC[7], XZC[8], XZC[9], XZC[10], XZC[11], XZC[12], XZC[3], XZC[4], XZC[5]);
					if(XZC[6] < 2){
						switch(GetPlayerWeapon(playerid)){
							case WEAPON_KNIFE, WEAPON_CHAINSAW:{
								new
									Float:px,Float:py,Float:pz;
								GetPlayerPos(playerid,px,py,pz);
								if(IsPlayerInRangeOfPoint(i,3,px,py,pz)){
									SetGVarInt("plr_beingattack",true,getTrialRelationList(i,playerid,GetPlayerWeapon(playerid)));
									//format(tmpstr,sizeof(tmpstr),"You are using %d to attack %d",playerid,i);
									//SendClientMessage(playerid,0xFF0000,tmpstr);
									//optional punishment
								}
							}
							case WEAPON_COLT45..WEAPON_MP5, WEAPON_TEC9:{ //can be detected by shootplayer func
								new
									Float:px,Float:py,Float:pz;
								GetPlayerPos(playerid,px,py,pz);
								if(IsPlayerInRangeOfPoint(i,100,px,py,pz)){
									SetGVarInt("plr_beingattack",true,getTrialRelationList(i,playerid,GetPlayerWeapon(playerid)));
									//format(tmpstr,sizeof(tmpstr),"You are using %d to attack %d",playerid,i);
									//SendClientMessage(playerid,0xFF0000,tmpstr);
									//optional punishment
								}
							}
							case WEAPON_M4, WEAPON_AK47:{
								new
									Float:px,Float:py,Float:pz;
								GetPlayerPos(playerid,px,py,pz);
								if(IsPlayerInRangeOfPoint(i,180,px,py,pz)){
									SetGVarInt("plr_beingattack",true,getTrialRelationList(i,playerid,GetPlayerWeapon(playerid)));
									//format(tmpstr,sizeof(tmpstr),"You are using %d to attack %d",playerid,i);
									//SendClientMessage(playerid,0xFF0000,tmpstr);
									//optional punishment
								}			
							}
							case WEAPON_SNIPER:{
								new
									Float:px,Float:py,Float:pz;
								GetPlayerPos(playerid,px,py,pz);
								if(IsPlayerInRangeOfPoint(i,300,px,py,pz)){
									SetGVarInt("plr_beingattack",true,getTrialRelationList(i,playerid,GetPlayerWeapon(playerid)));
									//format(tmpstr,sizeof(tmpstr),"You are using %d to attack %d",playerid,i);
									//SendClientMessage(playerid,0xFF0000,tmpstr);
									//optional punishment
								}
							}
							case WEAPON_SPRAYCAN, WEAPON_FIREEXTINGUISHER:{
								new
									Float:px,Float:py,Float:pz;
								GetPlayerPos(playerid,px,py,pz);
								if(IsPlayerInRangeOfPoint(i,5,px,py,pz)){
									SetGVarInt("plr_beingattack",true,getTrialRelationList(i,playerid,GetPlayerWeapon(playerid)));
									//format(tmpstr,sizeof(tmpstr),"You are using %d to attack %d",playerid,i);
									//SendClientMessage(playerid,0xFF0000,tmpstr);
									//optional punishment
								}
							}
							case WEAPON_FLAMETHROWER:{
								new
									Float:px,Float:py,Float:pz;
								GetPlayerPos(playerid,px,py,pz);
								if(IsPlayerInRangeOfPoint(i,15,px,py,pz)){
									SetGVarInt("plr_beingattack",true,getTrialRelationList(i,playerid,GetPlayerWeapon(playerid)));
									//format(tmpstr,sizeof(tmpstr),"You are using %d to attack %d",playerid,i);
									//SendClientMessage(playerid,0xFF0000,tmpstr);
									//optional punishment
								}
							}
							case WEAPON_GRENADE, WEAPON_MOLTOV:{
								new
									Float:px,Float:py,Float:pz;
								GetPlayerPos(playerid,px,py,pz);
								if(IsPlayerInRangeOfPoint(i,90,px,py,pz)){
									SetGVarInt("plr_beingattack",true,getTrialRelationList(i,playerid,GetPlayerWeapon(playerid)));
									//format(tmpstr,sizeof(tmpstr),"You are using %d to attack %d",playerid,i);
									//SendClientMessage(playerid,0xFF0000,tmpstr);
									//optional punishment
								}				
							}
						}
					}
				}
			}
		}
		punishKill_pTick[playerid] = GetTickCount();
	}
	return true;
}


forward punishKill_cancleSuspect(killerid,playerid);
public punishKill_cancleSuspect(killerid,playerid){ debug_public_track("punishKill_cancleSuspect(killerid,playerid){");
	SetGVarInt("plr_suspect",0,playerid);
}

zcmd(yesss,playerid,parmas[]){
	new
		killerid = GetGVarInt("plr_suspect",playerid);
	if(killerid){
		if(IsPlayerConnected(killerid)){
			killerid = killerid - 1;
			CallRemoteFunction("wl_ruleop_setPlayerJail","iii",killerid,true,45);
			SetGVarInt("plr_suspect",0,playerid);
			System_send(playerid,"[系统]你把%s投进监狱%d秒",pName(killerid),45);
			System_send(killerid,"[系统]%s把你投进监狱%d秒",pName(playerid),45);
			System_sendAll("[系统]%s因为杀害%s而被他投进监狱%d秒",pName(killerid),pName(playerid),45);
		}
		else {
			System_send(playerid,"[系统]该玩家已经下线了，投放监狱失败");
		}
	}
	return true;
}

punishKill_playerDisconnect(playerid){
	for(new i;i < MAX_PLAYERS;i++){
		DeleteGVar("plr_suspect",playerid);
		for(new j;j < 55;i++){
			new 
				index = getTrialRelationList(playerid,i,j));
			if(GetGVarType("plr_beingattack",index) == GLOBAL_VARTYPE_INT){
				DeleteGVar("plr_beingattack",index);
			}
		}
	}
	return true;
}

punishKill_playerDeath(playerid,killerid,reason){ //todo ?
	if(killerid != INVALID_PLAYER_ID && PDM_getPlayerDM(killerid) == INVALID_PDM_ID){
		if(!GetPlayerVirtualWorld(playerid) && !GetPlayerVirtualWorld(killerid)){
			if(GetPlayerState(killerid) == PLAYER_STATE_ONFOOT){
				if((reason == WEAPON_KNIFE || reason == WEAPON_CHAINSAW || (reason >= WEAPON_GRENADE && reason <= WEAPON_FIREEXTINGUISHER)) && GetPlayerWeapon(playerid) == reason){
					switch (reason) {
						case WEAPON_KNIFE, WEAPON_CHAINSAW:{
							new
								Float:px,Float:py,Float:pz;
							GetPlayerPos(playerid,px,py,pz);
							if(IsPlayerInRangeOfPoint(killerid,10,px,py,pz){
								if(GetGVarInt("plr_beingattack",getTrialRelationList(playerid,killerid,reason))){
									SetGVarInt("plr_suspect",killerid+1,playerid);
									SetTimerEx("punishKill_cancleSuspect",1000 * 10,false,"ii",killerid,playerid);
									System_send(playerid,"[系统]你被%s杀死,你现在可以选择是否将他报仇,输入 /yes 即可将他送入监狱, 10秒后自动撤消控诉",pName(killerid));
								}
							}
						}
						case WEAPON_COLT45 ... WEAPON_MP5, WEAPON_TEC9:{ //can be detected by shootplayer func
							new
								Float:px,Float:py,Float:pz;
							GetPlayerPos(playerid,px,py,pz);
							if(IsPlayerInRangeOfPoint(killerid,150,px,py,pz){
								if(GetGVarInt("plr_beingattack",getTrialRelationList(playerid,killerid,reason))){
									SetGVarInt("plr_suspect",killerid+1,playerid);
									SetTimerEx("punishKill_cancleSuspect",1000 * 10,false,"ii",killerid,playerid);
									System_send(playerid,"[系统]你被%s杀死,你现在可以选择是否将他报仇,输入 /yes 即可将他送入监狱, 10秒后自动撤消控诉",pName(killerid));
								}
							}
						}
						case WEAPON_M4, WEAPON_AK47:{
							new
								Float:px,Float:py,Float:pz;
							GetPlayerPos(playerid,px,py,pz);
							if(IsPlayerInRangeOfPoint(killerid,200,px,py,pz){
								if(GetGVarInt("plr_beingattack",getTrialRelationList(playerid,killerid,reason))){
									SetGVarInt("plr_suspect",killerid+1,playerid);
									SetTimerEx("punishKill_cancleSuspect",1000 * 10,false,"ii",killerid,playerid);
									System_send(playerid,"[系统]你被%s杀死,你现在可以选择是否将他报仇,输入 /yes 即可将他送入监狱, 10秒后自动撤消控诉",pName(killerid));
								}
							}			
						}
						case WEAPON_SNIPER:{
							new
								Float:px,Float:py,Float:pz;
							GetPlayerPos(playerid,px,py,pz);
							if(IsPlayerInRangeOfPoint(killerid,300,px,py,pz){
								if(GetGVarInt("plr_beingattack",getTrialRelationList(playerid,killerid,reason))){
									SetGVarInt("plr_suspect",killerid+1,playerid);
									SetTimerEx("punishKill_cancleSuspect",1000 * 10,false,"ii",killerid,playerid);
									System_send(playerid,"[系统]你被%s杀死,你现在可以选择是否将他报仇,输入 /yes 即可将他送入监狱, 10秒后自动撤消控诉",pName(killerid));
								}
							}
						}
						case WEAPON_SPRAYCAN, WEAPON_FIREEXTINGUISHER:{
							new
								Float:px,Float:py,Float:pz;
							GetPlayerPos(playerid,px,py,pz);
							if(IsPlayerInRangeOfPoint(killerid,15,px,py,pz){
								if(GetGVarInt("plr_beingattack",getTrialRelationList(playerid,killerid,reason))){
									SetGVarInt("plr_suspect",killerid+1,playerid);
									SetTimerEx("punishKill_cancleSuspect",1000 * 10,false,"ii",killerid,playerid);
									System_send(playerid,"[系统]你被%s杀死,你现在可以选择是否将他报仇,输入 /yes 即可将他送入监狱, 10秒后自动撤消控诉",pName(killerid));
								}
							}
						}
						case WEAPON_FLAMETHROWER:{
							new
								Float:px,Float:py,Float:pz;
							GetPlayerPos(playerid,px,py,pz);
							if(IsPlayerInRangeOfPoint(killerid,50,px,py,pz){
								if(GetGVarInt("plr_beingattack",getTrialRelationList(playerid,killerid,reason))){
									SetGVarInt("plr_suspect",killerid+1,playerid);
									SetTimerEx("punishKill_cancleSuspect",1000 * 10,false,"ii",killerid,playerid);
									System_send(playerid,"[系统]你被%s杀死,你现在可以选择是否将他报仇,输入 /yes 即可将他送入监狱, 10秒后自动撤消控诉",pName(killerid));
								}
							}
						}
						case WEAPON_GRENADE, WEAPON_MOLTOV:{
							new
								Float:px,Float:py,Float:pz;
							GetPlayerPos(playerid,px,py,pz);
							if(IsPlayerInRangeOfPoint(killerid,90,px,py,pz){
								if(GetGVarInt("plr_beingattack",getTrialRelationList(playerid,killerid,reason))){
									SetGVarInt("plr_suspect",killerid+1,playerid);
									SetTimerEx("punishKill_cancleSuspect",1000 * 10,false,"ii",killerid,playerid);
									System_send(playerid,"[系统]你被%s杀死,你现在可以选择是否将他报仇,输入 /yes 即可将他送入监狱, 10秒后自动撤消控诉",pName(killerid));
								}
							}				
						}
					}
				}
			}
			else if(GetPlayerState(killerid) == PLAYER_STATE_PASSENGER){
				switch(reason){
					case WEAPON_SHOTGUN,WEAPON_UZI,WEAPON_MP5,WEAPON_AK47,WEAPON_M4,WEAPON_TEC9,WEAPON_RIFLE,WEAPON_SNIPER:{
						//todo (passenger attack detect needed)
						/* 
						if(GetGVarInt("plr_beingattack",getTrialRelationList(playerid,killerid,reason))){
							SetGVarInt("plr_suspect",killerid+1,playerid);
							SetTimerEx("punishKill_cancleSuspect",1000 * 10,false,"ii",killerid,playerid);
							System_send(playerid,"[系统]你被%s杀死,你现在可以选择是否将他报仇,输入 /yes 即可将他送入监狱, 10秒后自动撤消控诉",pName(killerid));
						}
						*/
					}
				}
			}
			/*
			else if(GetPlayerState(killerid) == PLAYER_STATE_ONFOOT){
				if(reason == WEAPON_VEHICLE || reason == WEAPON_COLLISION){
					new
						Float:px,Float:py,Float:pz;
					GetPlayerPos(playerid,px,py,pz);
			*/
		}
	}
	for(new i; i < 55; i++){
		new 
			index = getTrialRelationList(playerid,killerid,j));
		if(GetGVarType("plr_beingattack",index) == GLOBAL_VARTYPE_INT){
			SetGVarInt("plr_beingattack",false,index);
		}
	}		
	return true;
}

















stock crossp(Float:v1x, Float:v1y, Float:v1z, Float:v2x, Float:v2y, Float:v2z, &Float:output)
{
	new
		Float:c1 = (v1y * v2z) - (v1z * v2y),
		Float:c2 = (v1z * v2x) - (v1x * v2z),
        Float:c3 = (v1x * v2y) - (v1y * v2x);
    output = floatsqroot ((c1 * c1) + (c2 * c2) + (c3 * c3));
    return 0;
}

stock GetDistanceFromPointToLine(&Float:distance, Float:line_vector_x, Float:line_vector_y, Float:line_vector_z, Float:line_x, Float:line_y, Float:line_z, Float:point_x, Float:point_y, Float:point_z)
{
	//A line is defined by a point (which is on the line (line_x/y/z)) and a vector which defines the direction (line_vector_x/y/z).
	static Float:output;
    crossp(line_vector_x, line_vector_y, line_vector_z, point_x - line_x, point_y - line_y, point_z - line_z, output);//Cross product of 2 vectors.
    distance = output / floatsqroot ((line_vector_x * line_vector_x) + (line_vector_y * line_vector_y) + (line_vector_z * line_vector_z));
	return 0;
}






















