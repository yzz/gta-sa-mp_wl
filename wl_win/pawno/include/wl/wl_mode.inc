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


#if defined _wl_mode_include
	#endinput
#endif
#define _wl_mode_include


//#include <wl/modes/wl_modes>
#include <wl/modes/dm/wl_dm_main>
//#include <wl/modes/team>
//#include <wl/modes/wl_group>
//#include <wl/modes/wl_gang>
#include <wl/modes/wl_vec>
#include <wl/modes/virtualworld>
#include <wl/modes/drunkbyhp>
#include <wl/modes/race/race_main>
#include <wl/modes/DMworld/DMworld>



wl_mode_db_Struction(){
	/*
	for(new i;i<MAX_PLAYERS;i++){
		PlayerInfo[i][Group_Invited] = INVALID_GROUP_ID;
		PlayerInfo[i][Group_Joined] = INVALID_GROUP_ID;
		PlayerInfo[i][Group_requester] = INVALID_PLAYER_ID;
		PlayerInfo[i][Group_requestTele] = group_tele_none;
	}
	*/
	//loopPlayerEx(i){
		//PlayerInfo[i][TDM_In] = INVALID_TDM_ID;
		//PlayerInfo[i][TDM_VoteFor] = INVALID_TDM_ID;
	//}
	#if MEM_VEC
	/*
	loopPlayerEx(i){
		PlayerInfo[i][Vec_PlayerVecID] = INVALID_VEHICLE_ID;
		PlayerInfo[i][Vec_LockType] = Vec_lock_none;
	}
	*/
	#endif
	return true;
	
}
wl_mode_db_OnPlayerDisconnect(playerid,reason){
	#pragma unused playerid,reason
	/*
	PlayerInfo[playerid][Group_Invited] = INVALID_GROUP_ID;
	PlayerInfo[playerid][Group_Joined] = INVALID_GROUP_ID;
	PlayerInfo[playerid][Group_requester] = INVALID_PLAYER_ID;
	PlayerInfo[playerid][Group_requestTele] = group_tele_none;

	PlayerInfo[playerid][GunDM_PlayerIn] = false;
	*/
	#if MEM_VEC
	/*
	PlayerInfo[playerid][Vec_PlayerVecID] = INVALID_VEHICLE_ID;
	*/
	#endif
	
	return true;
}
wl_mode_Struction(){
	//team_struct();
	wl_mode_DM_Struction();
	//#if WL_MODE_RACE
	Race_struct();
	//#endif
	Vec_Struction();
	
	wl_mode_db_Struction();
	mode_drunkbyhp_struction();
	dmw_struct();
	return true;
}
wl_mode_UnStruction(){
	wl_mode_DM_UnStruction();
	Vec_Unstruction();
	return true;
}
wl_mode_PlayerConnect(playerid){
	//wl_mode_DM_Connect(playerid);
	//team_playerConnect(playerid);
	wl_mode_DM_PlayerConnect(playerid);
	Race_playerConnect(playerid);
	vw_playerConnect(playerid);
	dmw_playerConnect(playerid);
	return true;
}
wl_mode_PlayerDisconnect(playerid,reason){
	//team_playerDisconnect(playerid);
	wl_mode_DM_Disconnect(playerid,reason);
	Vec_OnPlayerDisconnect(playerid,reason);
	Race_playerDisconnect(playerid);
	vw_playerDisconnect(playerid);
	//gg_OnPlayerDisconnect(playerid,reason);
	wl_mode_db_OnPlayerDisconnect(playerid,reason);
	dmw_playerDisconnect(playerid);
	return true;
}
wl_mode_PlayerSpawn(playerid){
	vw_playerSpawn(playerid);
	if(wl_mode_DM_PlayerSpawn(playerid))return true;
	return false;
}
wl_mode_PlayerDeath(playerid,killerid,reason){
	vw_playerDeath(playerid,killerid,reason);
	wl_mode_DM_PlayerDeath(playerid,killerid,reason);
	dmw:playerDeath(playerid,killerid,reason);
	Race_playerDeath(playerid);
	return true;
}
wl_mode_PlayerSelectedMenuRow(playerid,row){
	if(Vec_OnPlayerSelectedMenuRow(playerid,row))return true;
	return false;
}
wl_mode_PlayerExitedMenu(playerid){
	#pragma unused playerid
	return true;
}

wl_mode_PlayerExitVehicle(playerid){
	Vec_PlayerExitVehicle(playerid);
}

wl_mode_PlayerStateChange(playerid,newstate,oldstate){
	Vec_OnPlayerStateChange(playerid,newstate,oldstate);
	return true;
}
wl_mode_PlayerText(playerid,text[]){
	//return team_playerText(playerid,text);
	return gang:playerText(playerid,text);
}

wl_mode_CommandText(playerid,cmdtext[]){
	return wl_mode_DM_CommandText(playerid,cmdtext);
}

wl_mode_PlayerKeyStateChange(playerid,newkeys,oldkeys){
	wl_mode_DM_KeyStateChange(playerid,newkeys,oldkeys);
	return true;
}

wl_mode_DialogResponse(playerid, dialogid, response, listitem, inputtext[]){
	Race_DialogResponse(playerid, dialogid, response, listitem, inputtext);
	dmw:DialogResponse(playerid,dialogid,response,listitem);
	//Vec_DialogResponse(playerid, dialogid, response, listitem);
	return false;
}

wl_mode_EnterCheckpoint(playerid){
	vw_playerEnterCheckpoint(playerid);
}

wl_mode_EnterRaceCheckpoint(playerid){
	//#if WL_MODE_RACE
	Race_EnterRaceCheckpoint(playerid);
	//#endif
	
	return true;
}

wl_mode_KeyStateChange(playerid,newkeys,oldkeys){
	#pragma unused playerid,newkeys,oldkeys
	//DMWorld_KeyStateChange(playerid,newkeys,oldkeys);
	return true;
}

wl_mode_VehicleDeath(vehicleid){
	dmw:VehicleDeath(vehicleid);
}