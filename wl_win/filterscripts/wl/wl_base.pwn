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

#include <a_samp>
#include <gvar>
#define COLOR_SYSTEM					(0xEFEFF7AA)



AntiDeAMX()
{
    new a[][] =
    {
        "Unarmed (Fist)",
        "Brass K"
    };
    #pragma unused a
}

#define MAX_FILE_STR		(256)
//printf("1-%d",(countTimes++%5?0:GetTickCount()));

static stock
	countTimes;

stock wl_ruleop_pBreakRule(playerid){
	return CallRemoteFunction("wl_ruleop_pBreakRule","i",playerid);
}
/*
stock GDM_isPlayerInGunDM(playerid){
	return CallRemoteFunction("GDM_isPlayerInGunDM","i",playerid);
}
*/
stock PDM_isPlayerIn(playerid){
	return CallRemoteFunction("PDM_isPlayerIn","i",playerid);
}

stock GetPlayerAdminLevel(playerid){
	return CallRemoteFunction("GetPlayerAdminLevel","i",playerid);
}

stock Spec_isPlayerSpecing(playerid){
	return CallRemoteFunction("Spec_isPlayerSpecing","i",playerid);
}

/*
static
	ssstr[256];
writelog_init(){
	new
		str[MAX_FILE_STR],
		y,m,d,h,minute,s;
	getdate(y,m,d);
	gettime(h,minute,s);
	SetGVarInt("wl_debug",fopen("wl/wl.log",io_append));
	format("[DEBUG]Struct init(%4d%2d%2d%2d%2d%2d,%d)\r\n",y,m,d,h,minute,s,GetTickCount());
	fwrite(writelog_file(),str);
}

writelog_exit(){
	fclose(writelog_file());
	DeleteGVar("wl_debug");
}

writelog_file(){
	return GetGVarInt("wl_debug");
}


#define writelog(%0,%1) \
	format(ssstr,256,(%0),%1);fwrite(writelog_file(),ssstr);fwrite(writelog_file(),"\r\n")
	
writelog(const str[]){
	fwrite(writelog_file(),str);
	fwrite(writelog_file(),"\r\n");
}
*/
//#define public%1 // detect where use,forward,public

public OnGameModeInit(){
	//printf("1-%d",GetTickCount());
	////printf("[DEBUG]OnGameModeInit-%d",GetTickCount());
	return true;
}

public OnGameModeExit(){
	//printf("2-%d",GetTickCount());
	//printf("[DEBUG]OnGameModeExit-%d",GetTickCount());
	return true;
}
public OnFilterScriptInit(){
	AntiDeAMX();
	SetGVarInt("wl_copyright_preserver",4);
	//writelog_init();
	//printf("3-%d",GetTickCount());
	//printf("[DEBUG]OnFilterScriptInit-%d",GetTickCount());
	return true;
}

public OnFilterScriptExit(){
	//writelog_exit();
	//printf("4-%d",GetTickCount());
	//printf("[DEBUG]OnFilterScriptExit-%d",GetTickCount());
	return true;
}


public OnPlayerConnect(playerid){
	//printf("5(%d)-%d",playerid,GetTickCount());
	////printf("[DEBUG]OnPlayerConnect(%d)--playerid-%d",playerid,GetTickCount());
	return true;
}

public OnPlayerDisconnect(playerid, reason){
	//printf("6(%d,%d)-%d",playerid,reason,GetTickCount());
	////printf("[DEBUG]OnPlayerDisconnect(%d,%d)--playerid,reason-%d",playerid,reason,GetTickCount());
	return true;
}

public OnPlayerSpawn(playerid){
	//printf("7(%d)-%d",playerid,GetTickCount());
	////printf("[DEBUG]OnPlayerSpawn(%d)--playerid-%d",playerid,GetTickCount());
	return true;
}

public OnPlayerDeath(playerid, killerid, reason){
	//printf("8(%d,%d,%d)-%d",playerid,killerid,reason,GetTickCount());
	////printf("[DEBUG]OnPlayerDeath(%d,%d,%d)--playerid,killerid,reason-%d",playerid,killerid,reason,GetTickCount());
	return true;
}

public OnVehicleSpawn(vehicleid){
	//printf("9(%d)-%d",vehicleid,GetTickCount());
	////printf("[DEBUG]OnVehicleSpawn(%d)--vehicleid-%d",vehicleid,GetTickCount());
	return true;
}
public OnVehicleDeath(vehicleid, killerid){
	//printf("10(%d,%d)-%d",vehicleid,killerid,GetTickCount());
	////printf("[DEBUG]OnVehicleDeath(%d,%d)--vehicleid,killerid-%d",vehicleid,killerid,GetTickCount());
	return true;
}

static g_antiCommandFlood[MAX_PLAYERS][2];

public OnPlayerCommandText(playerid, cmdtext[]){
	//printf("11(%d,%s)-%d",playerid,cmdtext,GetTickCount());
	////printf("[DEBUG]OnPlayerCommandText(%d,%s)--playerid,cmdtext-%d",playerid,cmdtext,GetTickCount());
	if(!g_antiCommandFlood[playerid][0]){
		g_antiCommandFlood[playerid][0] = true;
		g_antiCommandFlood[playerid][1] = GetTickCount();
	}
	else {
		if(GetTickCount() - g_antiCommandFlood[playerid][1] < 1500){
			SendClientMessage(playerid,COLOR_SYSTEM,"[系统]你输入命令的速度太快了");
			return true;
		}
		else {
			g_antiCommandFlood[playerid][0] = false;
		}
	}
	if(GetPVarInt(playerid,"wl_mode_dmWorld_inworld") && GetPlayerAdminLevel(playerid)){
		if(!strcmp(cmdtext,"/tv ",true,3) || !strcmp(cmdtext,"/warn",true,5)) return false;
	}
	if(GetPlayerAdminLevel(playerid) || !strcmp(cmdtext,"/pm ",true,4)) return false;
	if(Spec_isPlayerSpecing(playerid)){
		if(!strcmp(cmdtext[1],"tv",true,2))return false;
		SendClientMessage(playerid,COLOR_SYSTEM,"[系统]在看电视时只能使用'/tv'这个命令");
		return true;
	}
	if(wl_ruleop_pBreakRule(playerid)){
		SendClientMessage(playerid,COLOR_SYSTEM,"[系统]因为你违反了游戏规则,不允许使用任何命令");
		return true;
	}
	if(PDM_isPlayerIn(playerid)){
		if(!strcmp(cmdtext[1],"outdm") || !strcmp(cmdtext[1],"dm likai") || !strcmp(cmdtext[1],"dm exit"))return false;
		SendClientMessage(playerid,COLOR_SYSTEM,"[系统]在PDM中只允许使用'/dm likai','/dm exit','/outdm'这些命令");
		return true;
	}
	if(GetPVarInt(playerid,"wl_mode_dmWorld_inworld")){
		if(!strcmp(cmdtext[1],"dmw",true,3) || !strcmp(cmdtext[1],"gang",true,4) ||!strcmp(cmdtext[1],"dmwdmin",true,7) || !strcmp(cmdtext[1],"ww chat",true,7))return false;
		SendClientMessage(playerid,COLOR_SYSTEM,"[系统]在大战城中只允许使用- /dmw - /gang - 这两个系列的指令");
		return true;
	}
	if(!strcmp(cmdtext[1],"gdm")){
		SendClientMessage(playerid,COLOR_SYSTEM,"[系统]未来世界已取消gdm功能");
		SendClientMessage(playerid,COLOR_SYSTEM,"[系统]输入/ww 和 /getweapon 即可满足你的要求");
		SendClientMessage(playerid,COLOR_SYSTEM,"[系统]更多请查看/ww help  或 /ww help2");
		return true;
	}
	return false;
}

public OnPlayerRequestClass(playerid, classid){
	//printf("12(%d,%d)-%d",playerid,classid,GetTickCount());
	////printf("[DEBUG]OnPlayerRequestClass(%d,%d)--playerid,classid-%d",playerid,classid,GetTickCount());
	return true;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger){
	//printf("13(%d,%d,%d)-%d",playerid,vehicleid,ispassenger,GetTickCount());
	////printf("[DEBUG]OnPlayerEnterVehicle(%d,%d,%d)--playerid,vehicleid,ispassenger-%d",playerid,vehicleid,ispassenger,GetTickCount());
	return true;
}
public OnPlayerExitVehicle(playerid, vehicleid){
	//printf("14(%d,%d)-%d",playerid,vehicleid,GetTickCount());
	////printf("[DEBUG]OnPlayerExitVehicle(%d,%d)--playerid,vehicleid-%d",playerid,vehicleid,GetTickCount());
	return true;
}

public OnPlayerStateChange(playerid, newstate, oldstate){
	//printf("15(%d,%d,%d)-%d",playerid,newstate,oldstate,GetTickCount());
	////printf("[DEBUG]OnPlayerStateChange(%d,%d,%d)--playerid,newstate,oldstate-%d",playerid,newstate,oldstate,GetTickCount());
	return true;
}

public OnPlayerEnterCheckpoint(playerid){
	//printf("16(%d)-%d",playerid,GetTickCount());
	////printf("[DEBUG]OnPlayerEnterCheckpoint(%d)--playerid-%d",playerid,GetTickCount());
	return true;
}
public OnPlayerLeaveCheckpoint(playerid){
	//printf("17(%d)-%d",playerid,GetTickCount());
	////printf("[DEBUG]OnPlayerLeaveCheckpoint(%d)--playerid-%d",playerid,GetTickCount());
	return true;
}
public OnPlayerEnterRaceCheckpoint(playerid){
	//printf("18(%d)-%d",playerid,GetTickCount());
	////printf("[DEBUG]OnPlayerEnterRaceCheckpoint(%d)--playerid-%d",playerid,GetTickCount());
	return true;
}
public OnPlayerLeaveRaceCheckpoint(playerid){
	//printf("19(%d)-%d",playerid,GetTickCount());
	////printf("[DEBUG]OnPlayerLeaveRaceCheckpoint(%d)--playerid-%d",playerid,GetTickCount());
	return true;
}
public OnRconCommand(cmd[]){
	//printf("20(%s)-%d",cmd,GetTickCount());
	////printf("[DEBUG]OnRconCommand(%s)--cmd-%d",cmd,GetTickCount());
	return true;
}
public OnPlayerRequestSpawn(playerid){
	//printf("21(%d)-%d",playerid,GetTickCount());
	////printf("[DEBUG]OnPlayerRequestSpawn(%d)--playerid-%d",playerid,GetTickCount());
	return true;
}
public OnObjectMoved(objectid){
	//printf("22(%d)-%d",objectid,GetTickCount());
	////printf("[DEBUG]OnObjectMoved(%d)--objectid-%d",objectid,GetTickCount());
	return true;
}
public OnPlayerObjectMoved(playerid, objectid){
	//printf("23(%d,%d)-%d",playerid,objectid,GetTickCount());
	////printf("[DEBUG]OnPlayerObjectMoved(%d,%d)--playerid,objectid-%d",playerid,objectid,GetTickCount());
	return true;
}
public OnPlayerPickUpPickup(playerid, pickupid){
	//printf("24(%d,%d)-%d",playerid,pickupid,GetTickCount());
	////printf("[DEBUG]OnPlayerPickUpPickup(%d,%d)--playerid,pickupid-%d",playerid,pickupid,GetTickCount());
	return true;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid){
	//printf("25(%d,%d,%d)-%d",playerid,vehicleid,paintjobid,GetTickCount());
	////printf("[DEBUG]OnVehiclePaintjob(%d,%d,%d)--playerid,vehicleid,paintjobid-%d",playerid,vehicleid,paintjobid,GetTickCount());
	return true;
}
public OnVehicleRespray(playerid, vehicleid, color1, color2){
	//printf("26(%d,%d,%d,%d)-%d",playerid,vehicleid,color1,color2,GetTickCount());
	////printf("[DEBUG]OnVehicleRespray(%d,%d,%d,%d)--playerid,vehicleid,color1,color2-%d",playerid,vehicleid,color1,color2,GetTickCount());
	return true;
}

public OnPlayerSelectedMenuRow(playerid, row){
	//printf("27(%d,%d)-%d",playerid,row,GetTickCount());
	////printf("[DEBUG]OnPlayerSelectedMenuRow(%d,%d)--playerid,row-%d",playerid,row,GetTickCount());
	return true;
}
public OnPlayerExitedMenu(playerid){
	//printf("28(%d)-%d",playerid,GetTickCount());
	////printf("[DEBUG]OnPlayerExitedMenu(%d)--playerid-%d",playerid,GetTickCount());
	return true;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid){
	//printf("29(%d,%d,%d)-%d",playerid, newinteriorid, oldinteriorid,GetTickCount());
	////printf("[DEBUG]OnPlayerInteriorChange(%d,%d,%d)--playerid, newinteriorid, oldinteriorid-%d",playerid, newinteriorid, oldinteriorid,GetTickCount());
	return true;
}


public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]){
	//printf("30(%d,%d,%d,%d,%s)-%d",playerid, dialogid, response, listitem, inputtext,GetTickCount());
	////printf("[DEBUG]OnDialogResponse(%d,%d,%d,%d,%s)--playerid, dialogid, response, listitem, inputtext-%d",playerid, dialogid, response, listitem, inputtext,GetTickCount());
	return false;
}


public OnPlayerClickPlayer(playerid, clickedplayerid, source){
	//printf("31(%d,%d,%d)-%d",playerid, clickedplayerid, source, GetTickCount());
	////printf("[DEBUG]OnPlayerClickPlayer(%d,%d,%d)--playerid, clickedplayerid, source-%d",playerid, clickedplayerid, source, GetTickCount());
	return false;
}

public OnRconLoginAttempt(ip[], password[], success){
	//printf("32(%s,%s,%d)-%d",ip, password, success,GetTickCount());
	////printf("[DEBUG]OnRconLoginAttempt(%s,%s,%d)--ip, password, success-%d",ip, password, success,GetTickCount());
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	//printf("33(%d,%d,%d)-%d",playerid,vehicleid,componentid,GetTickCount());
	////printf("[DEBUG]OnVehicleMod(%d,%d,%d)--playerid,vehicleid,componentid-%d",playerid,vehicleid,componentid,GetTickCount());
	return true;
}



///=========================================================

/*
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
	//writetolog("[DEBUG]OnPlayerKeyStateChange(%d,%d,%d)--playerid, newkeys, oldkeys-%d%d%d",playerid, newkeys, oldkeys);
	return true;
}


public OnPlayerStreamIn(playerid, forplayerid){
	////printf("[DEBUG]OnPlayerStreamIn(%d,%d)--playerid, forplayerid-%d",playerid, forplayerid,GetTickCount());
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid){
	////printf("[DEBUG]OnPlayerStreamOut(%d,%d)--playerid, forplayerid-%d",playerid, forplayerid,GetTickCount());
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid){
	////printf("[DEBUG]OnVehicleStreamIn(%d,%d)--vehicleid, forplayerid-%d",vehicleid, forplayerid,GetTickCount());
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid){
	////printf("[DEBUG]OnVehicleStreamOut(%d,%d)--vehicleid, forplayerid-%d",vehicleid, forplayerid,GetTickCount());
	return 1;
}


public OnPlayerText(playerid, text[]){
	//printf("[DEBUG]OnPlayerText(%d,%s)--playerid,text-%d",playerid,text,GetTickCount());
	return true;
}

public OnPlayerUpdate(playerid){
	//printf("[DEBUG]OnPlayerUpdate(%d)--playerid",playerid);
	return true;
}
*/