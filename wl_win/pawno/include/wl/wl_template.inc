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



#include <wl\template\weathertime>
#include <wl\template\score>
//#include <wl\template\punishKill>
#include <wl\template\forcespam>
#include <wl\template\armedbody>
#include <wl\template\weaponset>
#include <wl\template\others>



wl_tmp_GameModeInit(){
	wl_tmp_wt_Struction();
	wl_tmp_fm_Struct();
	Pause_struction();
	score_Sturction();
	return true;
}

wl_tmp_PlayerConnect(playerid){
	wl_tmp_wt_PlayerConnect(playerid);
	score_PlayerConnect(playerid);
	return true;
}

wl_tmp_PlayerDisconnect(playerid){
	wl_tmp_o_PlayerDisconnect(playerid);
	return true;
}

wl_tmp_PlayerSpawn(playerid){
	wl_tmp_wt_PlayerSpawn(playerid);
	wl_tmp_o_PlayerSpawn(playerid);
	weaponset_playerSpawn(playerid);
	return true;
}

wl_tmp_PlayerDeath(playerid,killerid){
	score_PlayerDeath(playerid,killerid);
	return true;
}

wl_tmp_PlayerText(playerid,text[]){
	if(wl_tmp_fm_PlayerText(playerid,text))return true;
	return false;
}

wl_tmp_PlayerPrivmsg(playerid,recieverid,text[]){
	if(wl_tmp_fm_PlayerPrivmsg(playerid,recieverid,text))return true;
	return false;
}

wl_tmp_PlayerRequestSpawn(playerid){
	wl_tmp_o_PlayerRequestSpawn(playerid);
	return true;
}



wl_tmp_DialogResponse(playerid, dialogid, response, listitem, inputtext[]){
	#pragma unused inputtext
	Fightsytle_DialogResponse(playerid, dialogid, response, listitem);
	weaponset_DialogResponse(playerid, dialogid, response, listitem);
}

wl_tmp_PlayerUpdate(playerid){
	Pause_OnPlayerUpdate(playerid);
	armedbody_playerUpdate(playerid);
}

wl_tmp_playerText(playerid){
	Pause_OnPlayerText(playerid);
}

wl_tmp_playerCommandText(playerid){
	Pause_OnPlayerCommandText(playerid);
}

wl_tmp_playerStateChange(playerid){
	Pause_OnPlayerStateChange(playerid);
}
wl_tmp_playerKeyStateChange(playerid){
	Pause_OnPlayerKeyStateChange(playerid);
}






























