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
#if defined gcs_debug
	#endinput
#endif
#define gcs_debug





new const bool:debug_FALSE=false;
//new const bool:debug_TRUE=true;

new debug_log_dir[] = "/gcs/debug/";
new debug_log[128];
new debug_id;




#define writelog(%1,%2)\ 
do{\
	new \
		sendfstring[128],\
		File:debug_file_ = fopen(debug_log,io_append);\
	format(sendfstring,sizeof(sendfstring),"\r\n[%d]",debug_id);\
	fwrite(debug_file_,sendfstring);\
	format(sendfstring,sizeof(sendfstring),(%1),%2);\
	fwrite(debug_file_,sendfstring);\
	fclose(debug_file_);\
}while(debug_FALSE)


stock writelog(const logstr[]){
	new
		sendfstring[128],
		File:debug_file_ = fopen(debug_log,io_append);
	format(sendfstring,sizeof(sendfstring),"\r\n[%d]%s",debug_id,logstr);
	fwrite(debug_file_,sendfstring);
	fclose(debug_file_);
}


public OnGameModeInit(){
	
	if(!debug_id){
		debug_id = random(1000)+10000;
		printf("====================callback_debug=====================");
		printf("The amx used debug id:%d",debug_id);
		printf("=======================================================");
		
		new tmpval[6];
		gettime(tmpval[0],tmpval[1],tmpval[2]);
		getdate(tmpval[3],tmpval[4],tmpval[5]);
		format(debug_log,sizeof(debug_log),"%s%04d%02d%02d%02d%02d%02d_debug.log",
			debug_log_dir,
			tmpval[3],tmpval[4],tmpval[5],
			tmpval[0],tmpval[1],tmpval[2]
		);
		if(!fexist(debug_log)){
			new File:tmpfile = fopen(debug_log,io_write);
			fclose(tmpfile);
		}
		
	}
	
	/*
	if(!debug_id){
		debug_id = random(1000)+1000;
		printf("====================callback_debug=====================");
		printf("The amx used debug id:%d",debug_id);
		printf("=======================================================");
	}
	printf("[DEBUG_CALLBACK][%d]OnGameModeInit()",debug_id);
	*/
	return gd_OnGameModeInit();
}

public OnGameModeExit(){

	printf("[DEBUG_CALLBACK][%d]OnGameModeExit()",debug_id);
	return gd_OnGameModeExit();
}
public OnFilterScriptInit(){
	
	if(!debug_id){
		debug_id = random(500)+1000;
		printf("====================callback_debug=====================");
		printf("The amx used debug id:%d",debug_id);
		printf("=======================================================");
		
		new tmpval[6];
		gettime(tmpval[0],tmpval[1],tmpval[2]);
		getdate(tmpval[3],tmpval[4],tmpval[5]);
		format(debug_log,sizeof(debug_log),"%s%04d%02d%02d%02d%02d%02d_debug.log",
			debug_log_dir,
			tmpval[4],tmpval[5],
			tmpval[0],tmpval[1],tmpval[2]
		);
		if(!fexist(debug_log)){
			new File:tmpfile = fopen(debug_log,io_write);
			fclose(tmpfile);
		}
	}
	
	/*
	if(!debug_id){
		debug_id = random(1000)+1000;
		printf("====================callback_debug=====================");
		printf("The amx used debug id:%d",debug_id);
		printf("=======================================================");
	}
	printf("[DEBUG_CALLBACK][%d]OnFilterScriptInit()",debug_id);
	*/
	return gd_OnFilterScriptInit();
}


public OnFilterScriptExit(){
	writelog("[DEBUG_CALLBACK][%d]OnFilterScriptExit()",debug_id);
	return gd_OnFilterScriptExit();
}

public OnPlayerConnect(playerid){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerConnect(playerid)(%d)",debug_id,playerid);
	return gd_OnPlayerConnect(playerid);
}
public OnPlayerDisconnect(playerid, reason){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerDisconnect(playerid, reason)(%d,%d)",debug_id,playerid, reason);
	return gd_OnPlayerDisconnect(playerid, reason);
}
public OnPlayerSpawn(playerid){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerSpawn(playerid)(%d)",debug_id,playerid);
	return gd_OnPlayerSpawn(playerid);
}

public OnPlayerDeath(playerid, killerid, reason){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerDeath(playerid, killerid, reason)(%d,%d,%d)",debug_id,playerid, killerid, reason);
	return gd_OnPlayerDeath(playerid, killerid, reason);
}
public OnVehicleSpawn(vehicleid){
	writelog("[DEBUG_CALLBACK][%d]OnVehicleSpawn(vehicleid)(%d)",debug_id,vehicleid);
	return gd_OnVehicleSpawn(vehicleid);
}
public OnVehicleDeath(vehicleid, killerid){
	writelog("[DEBUG_CALLBACK][%d]OnVehicleDeath(vehicleid, killerid)(%d,%d)",debug_id,vehicleid, killerid);
	return gd_OnVehicleDeath(vehicleid, killerid);
}
public OnPlayerText(playerid, text[]){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerText(playerid)(%d)",debug_id,playerid);
	return gd_OnPlayerText(playerid, text);
}

public OnPlayerCommandText(playerid, cmdtext[]){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerCommandText(playerid, cmdtext[])(%d,%s)",debug_id,playerid, cmdtext);
	return gd_OnPlayerCommandText(playerid, cmdtext);
}


public OnPlayerInfoChange(playerid){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerInfoChange(playerid)(%d)",debug_id,playerid);
	return gd_OnPlayerInfoChange(playerid);
}
public OnPlayerRequestClass(playerid, classid){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerRequestClass(playerid, classid)(%d,%d)",debug_id,playerid, classid);
	return gd_OnPlayerRequestClass(playerid, classid);
}
public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)(%d,%d,%d)",debug_id,playerid, vehicleid, ispassenger);
	return gd_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
}
	
public OnPlayerExitVehicle(playerid, vehicleid){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerExitVehicle(playerid, vehicleid)(%d,%d)",debug_id,playerid, vehicleid);
	return gd_OnPlayerExitVehicle(playerid, vehicleid);
}
public OnPlayerStateChange(playerid, newstate, oldstate){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerStateChange(playerid, newstate, oldstate)(%d,%d,%d)",debug_id,playerid, newstate, oldstate);
	return gd_OnPlayerStateChange(playerid, newstate, oldstate);
}
public OnPlayerEnterCheckpoint(playerid){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerEnterCheckpoint(playerid)(%d)",debug_id,playerid);
	return gd_OnPlayerEnterCheckpoint(playerid);
}
public OnPlayerLeaveCheckpoint(playerid){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerLeaveCheckpoint(playerid)(%d)",debug_id,playerid);
	return gd_OnPlayerLeaveCheckpoint(playerid);
}
public OnPlayerEnterRaceCheckpoint(playerid){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerEnterRaceCheckpoint(playerid)(%d)",debug_id,playerid);
	return gd_OnPlayerEnterRaceCheckpoint(playerid);
}
public OnPlayerLeaveRaceCheckpoint(playerid){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerLeaveRaceCheckpoint(playerid)(%d)",debug_id,playerid);
	return gd_OnPlayerLeaveRaceCheckpoint(playerid);
}
public OnRconCommand(cmd[]){
	writelog("[DEBUG_CALLBACK][%d]OnRconCommand(cmd[])(%s)",debug_id,cmd);
	return gd_OnRconCommand(cmd);
}
public OnPlayerPrivmsg(playerid, recieverid, text[]){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerPrivmsg(playerid, recieverid,)(%d,%d)",debug_id,playerid, recieverid);
	return gd_OnPlayerPrivmsg(playerid, recieverid, text);
}
public OnPlayerRequestSpawn(playerid){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerRequestSpawn(playerid)(%d)",debug_id,playerid);
	return gd_OnPlayerRequestSpawn(playerid);
}

public OnObjectMoved(objectid){
	writelog("[DEBUG_CALLBACK][%d]OnObjectMoved(objectid)(%d)",debug_id,objectid);
	return gd_OnObjectMoved(objectid);
}
public OnPlayerObjectMoved(playerid, objectid){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerObjectMoved(playerid, objectid)(%d,%d)",debug_id,playerid, objectid);
	return gd_OnPlayerObjectMoved(playerid, objectid);
}

public OnPlayerPickUpPickup(playerid, pickupid){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerPickUpPickup(playerid, pickupid)(%d,%d)",debug_id,playerid, pickupid);
	return gd_OnPlayerPickUpPickup(playerid, pickupid);
}
	
public OnVehicleMod(playerid, vehicleid, componentid){
	writelog("[DEBUG_CALLBACK][%d]OnVehicleMod(playerid, vehicleid, componentid)(%d,%d,%d)",debug_id,playerid, vehicleid, componentid);
	return gd_OnVehicleMod(playerid, vehicleid, componentid);
}
	
public OnVehiclePaintjob(playerid, vehicleid, paintjobid){
	writelog("[DEBUG_CALLBACK][%d]OnVehiclePaintjob(playerid, vehicleid, paintjobid)(%d,%d,%d)",debug_id,playerid, vehicleid, paintjobid);
	return gd_OnVehiclePaintjob(playerid, vehicleid, paintjobid);
}
public OnVehicleRespray(playerid, vehicleid, color1, color2){
	writelog("[DEBUG_CALLBACK][%d]OnVehicleRespray(playerid, vehicleid, color1, color2)(%d,%d,%d,%d)",debug_id,playerid, vehicleid, color1, color2);
	return gd_OnVehicleRespray(playerid, vehicleid, color1, color2);
}


public OnPlayerSelectedMenuRow(playerid, row){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerSelectedMenuRow(playerid, row)(%d,%d)",debug_id,playerid, row);
	return gd_OnPlayerSelectedMenuRow(playerid, row);
}
public OnPlayerExitedMenu(playerid){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerExitedMenu(playerid)(%d)",debug_id,playerid);
	return gd_OnPlayerExitedMenu(playerid);
}
public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid){
	writelog("[DEBUG_CALLBACK][%d]OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)(%d,%d,%d)",debug_id,playerid, newinteriorid, oldinteriorid);
	return gd_OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
	//writelog("[DEBUG_CALLBACK][%d]OnPlayerKeyStateChange(playerid, newkeys, oldkeys)(%d,%d,%d)",debug_id,playerid, newkeys, oldkeys);
	//return gd_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	return true;
}


public OnPlayerUpdate(playerid){
	//writelog("[DEBUG_CALLBACK][%d]OnPlayerUpdate(playerid)(%d)",debug_id,playerid);
	//return gd_OnPlayerUpdate(playerid);	
	return true;
}



#define OnGameModeInit gd_OnGameModeInit
#define OnGameModeExit gd_OnGameModeExit
#define OnFilterScriptInit gd_OnFilterScriptInit
#define OnFilterScriptExit gd_OnFilterScriptExit
#define OnPlayerConnect gd_OnPlayerConnect 
#define OnPlayerDisconnect gd_OnPlayerDisconnect 
#define OnPlayerSpawn gd_OnPlayerSpawn 
#define OnPlayerDeath gd_OnPlayerDeath 
#define OnVehicleSpawn gd_OnVehicleSpawn 
#define OnVehicleDeath gd_OnVehicleDeath 
#define OnPlayerText gd_OnPlayerText 
#define OnPlayerCommandText gd_OnPlayerCommandText 
#define OnPlayerInfoChange gd_OnPlayerInfoChange 
#define OnPlayerRequestClass gd_OnPlayerRequestClass 
#define OnPlayerEnterVehicle gd_OnPlayerEnterVehicle 
#define OnPlayerExitVehicle gd_OnPlayerExitVehicle 
#define OnPlayerStateChange gd_OnPlayerStateChange 
#define OnPlayerEnterCheckpoint gd_OnPlayerEnterCheckpoint 
#define OnPlayerLeaveCheckpoint gd_OnPlayerLeaveCheckpoint 
#define OnPlayerEnterRaceCheckpoint gd_OnPlayerEnterRaceCheckpoint 
#define OnPlayerLeaveRaceCheckpoint gd_OnPlayerLeaveRaceCheckpoint 
#define OnRconCommand gd_OnRconCommand 
#define OnPlayerPrivmsg gd_OnPlayerPrivmsg 
#define OnPlayerRequestSpawn gd_OnPlayerRequestSpawn 
#define OnObjectMoved gd_OnObjectMoved 
#define OnPlayerObjectMoved gd_OnPlayerObjectMoved 
#define OnPlayerPickUpPickup gd_OnPlayerPickUpPickup 
#define OnVehicleMod gd_OnVehicleMod 
#define OnVehiclePaintjob gd_OnVehiclePaintjob 
#define OnVehicleRespray gd_OnVehicleRespray 
#define OnPlayerSelectedMenuRow gd_OnPlayerSelectedMenuRow 
#define OnPlayerExitedMenu gd_OnPlayerExitedMenu 
#define OnPlayerInteriorChange gd_OnPlayerInteriorChange 
#define OnPlayerKeyStateChange gd_OnPlayerKeyStateChange 
#define OnPlayerUpdate gd_OnPlayerUpdate 


/*
#define gd_OnGameModeInit(); OnGameModeInit(); 
#define gd_OnGameModeExit(); OnGameModeExit(); 
#define gd_OnFilterScriptInit(); OnFilterScriptInit(); 
#define gd_OnFilterScriptExit(); OnFilterScriptExit(); 
#define gd_OnPlayerConnect(%1); OnPlayerConnect(%1); 
#define gd_OnPlayerDisconnect(%1); OnPlayerDisconnect(%1); 
#define gd_OnPlayerSpawn(%1); OnPlayerSpawn(%1); 
#define gd_OnPlayerDeath(%1); OnPlayerDeath(%1); 
#define gd_OnVehicleSpawn(%1); OnVehicleSpawn(%1); 
#define gd_OnVehicleDeath(%1); OnVehicleDeath(%1); 
#define gd_OnPlayerText(%1); OnPlayerText(%1); 
#define gd_OnPlayerCommandText(%1); OnPlayerCommandText(%1); 
#define gd_OnPlayerInfoChange(%1); OnPlayerInfoChange(%1); 
#define gd_OnPlayerRequestClass(%1); OnPlayerRequestClass(%1); 
#define gd_OnPlayerEnterVehicle(%1); OnPlayerEnterVehicle(%1); 
#define gd_OnPlayerExitVehicle(%1); OnPlayerExitVehicle(%1); 
#define gd_OnPlayerStateChange(%1); OnPlayerStateChange(%1); 
#define gd_OnPlayerEnterCheckpoint(%1); OnPlayerEnterCheckpoint(%1); 
#define gd_OnPlayerLeaveCheckpoint(%1); OnPlayerLeaveCheckpoint(%1); 
#define gd_OnPlayerEnterRaceCheckpoint(%1); OnPlayerEnterRaceCheckpoint(%1); 
#define gd_OnPlayerLeaveRaceCheckpoint(%1);OnPlayerLeaveRaceCheckpoint(%1); 
#define gd_OnRconCommand(%1); OnRconCommand(%1); 
#define gd_OnPlayerPrivmsg(%1); OnPlayerPrivmsg(%1); 
#define gd_OnPlayerRequestSpawn(%1); OnPlayerRequestSpawn(%1); 
#define gd_OnObjectMoved(%1); OnObjectMoved(%1); 
#define gd_OnPlayerObjectMoved(%1); OnPlayerObjectMoved(%1); 
#define gd_OnPlayerPickUpPickup(%1); OnPlayerPickUpPickup(%1); 
#define gd_OnVehicleMod(%1); OnVehicleMod(%1); 
#define gd_OnVehiclePaintjob(%1); OnVehiclePaintjob(%1); 
#define gd_OnVehicleRespray(%1); OnVehicleRespray(%1); 
#define gd_OnPlayerSelectedMenuRow(%1); OnPlayerSelectedMenuRow(%1); 
#define gd_OnPlayerExitedMenu(%1); OnPlayerExitedMenu(%1); 
#define gd_OnPlayerInteriorChange(%1); OnPlayerInteriorChange(%1); 
#define gd_OnPlayerKeyStateChange(%1); OnPlayerKeyStateChange(%1); 
#define gd_OnPlayerUpdate(%1); OnPlayerUpdate(%1); 
*/
/*

#define OnGameModeInit(); gd_OnGameModeInit();
#define OnGameModeExit(); gd_OnGameModeExit();
#define OnFilterScriptInit(); gd_OnFilterScriptInit();
#define OnFilterScriptExit(); gd_OnFilterScriptExit();
#define OnPlayerConnect(%1); gd_OnPlayerConnect(%1);
#define OnPlayerDisconnect(%1); gd_OnPlayerDisconnect(%1);
#define OnPlayerSpawn(%1); gd_OnPlayerSpawn(%1);
#define OnPlayerDeath(%1); gd_OnPlayerDeath(%1);
#define OnVehicleSpawn(%1); gd_OnVehicleSpawn(%1);
#define OnVehicleDeath(%1); gd_OnVehicleDeath(%1);
#define OnPlayerText(%1); gd_OnPlayerText(%1);
#define OnPlayerCommandText(%1); gd_OnPlayerCommandText(%1);
#define OnPlayerInfoChange(%1); gd_OnPlayerInfoChange(%1);
#define OnPlayerRequestClass(%1); gd_OnPlayerRequestClass(%1);
#define OnPlayerEnterVehicle(%1); gd_OnPlayerEnterVehicle(%1);
#define OnPlayerExitVehicle(%1); gd_OnPlayerExitVehicle(%1);
#define OnPlayerStateChange(%1); gd_OnPlayerStateChange(%1);
#define OnPlayerEnterCheckpoint(%1); gd_OnPlayerEnterCheckpoint(%1);
#define OnPlayerLeaveCheckpoint(%1); gd_OnPlayerLeaveCheckpoint(%1);
#define OnPlayerEnterRaceCheckpoint(%1); gd_OnPlayerEnterRaceCheckpoint(%1);
#define OnPlayerLeaveRaceCheckpoint(%1); gd_OnPlayerLeaveRaceCheckpoint(%1);
#define OnRconCommand(%1); gd_OnRconCommand(%1);
#define OnPlayerPrivmsg(%1); gd_OnPlayerPrivmsg(%1);
#define OnPlayerRequestSpawn(%1); gd_OnPlayerRequestSpawn(%1);
#define OnObjectMoved(%1); gd_OnObjectMoved(%1);
#define OnPlayerObjectMoved(%1); gd_OnPlayerObjectMoved(%1);
#define OnPlayerPickUpPickup(%1); gd_OnPlayerPickUpPickup(%1);
#define OnVehicleMod(%1); gd_OnVehicleMod(%1);
#define OnVehiclePaintjob(%1); gd_OnVehiclePaintjob(%1);
#define OnVehicleRespray(%1); gd_OnVehicleRespray(%1);
#define OnPlayerSelectedMenuRow(%1); gd_OnPlayerSelectedMenuRow(%1);
#define OnPlayerExitedMenu(%1); gd_OnPlayerExitedMenu(%1);
#define OnPlayerInteriorChange(%1); gd_OnPlayerInteriorChange(%1);
#define OnPlayerKeyStateChange(%1); gd_OnPlayerKeyStateChange(%1);
#define OnPlayerUpdate(%1); gd_OnPlayerUpdate(%1);
*/
/*
#define OnGameModeInit() gd_OnGameModeInit()
#define OnGameModeExit() gd_OnGameModeExit()
#define OnFilterScriptInit() gd_OnFilterScriptInit()
#define OnFilterScriptExit() gd_OnFilterScriptExit()
#define OnPlayerConnect(%1) gd_OnPlayerConnect(%1)
#define OnPlayerDisconnect(%1) gd_OnPlayerDisconnect(%1)
#define OnPlayerSpawn(%1) gd_OnPlayerSpawn(%1)
#define OnPlayerDeath(%1) gd_OnPlayerDeath(%1)
#define OnVehicleSpawn(%1) gd_OnVehicleSpawn(%1)
#define OnVehicleDeath(%1) gd_OnVehicleDeath(%1)
#define OnPlayerText(%1) gd_OnPlayerText(%1)
//#define OnPlayerCommandText(%1) gd_OnPlayerCommandText(%1)
#define OnPlayerInfoChange(%1) gd_OnPlayerInfoChange(%1)
#define OnPlayerRequestClass(%1) gd_OnPlayerRequestClass(%1)
#define OnPlayerEnterVehicle(%1) gd_OnPlayerEnterVehicle(%1)
#define OnPlayerExitVehicle(%1) gd_OnPlayerExitVehicle(%1)
#define OnPlayerStateChange(%1) gd_OnPlayerStateChange(%1)
#define OnPlayerEnterCheckpoint(%1) gd_OnPlayerEnterCheckpoint(%1)
#define OnPlayerLeaveCheckpoint(%1) gd_OnPlayerLeaveCheckpoint(%1)
#define OnPlayerEnterRaceCheckpoint(%1) gd_OnPlayerEnterRaceCheckpoint(%1)
#define OnPlayerLeaveRaceCheckpoint(%1) gd_OnPlayerLeaveRaceCheckpoint(%1)
#define OnRconCommand(%1) gd_OnRconCommand(%1)
#define OnPlayerPrivmsg(%1) gd_OnPlayerPrivmsg(%1)
#define OnPlayerRequestSpawn(%1) gd_OnPlayerRequestSpawn(%1)
#define OnObjectMoved(%1) gd_OnObjectMoved(%1)
#define OnPlayerObjectMoved(%1) gd_OnPlayerObjectMoved(%1)
#define OnPlayerPickUpPickup(%1) gd_OnPlayerPickUpPickup(%1)
#define OnVehicleMod(%1) gd_OnVehicleMod(%1)
#define OnVehiclePaintjob(%1) gd_OnVehiclePaintjob(%1)
#define OnVehicleRespray(%1) gd_OnVehicleRespray(%1)
#define OnPlayerSelectedMenuRow(%1) gd_OnPlayerSelectedMenuRow(%1)
#define OnPlayerExitedMenu(%1) gd_OnPlayerExitedMenu(%1)
#define OnPlayerInteriorChange(%1) gd_OnPlayerInteriorChange(%1)
//#define OnPlayerKeyStateChange(%1) gd_OnPlayerKeyStateChange(%1)
//#define OnPlayerUpdate(%1) gd_OnPlayerUpdate(%1)
*/


forward gd_OnGameModeInit();
forward gd_OnGameModeExit();
forward gd_OnFilterScriptInit();
forward gd_OnFilterScriptExit();
forward gd_OnPlayerConnect(playerid);
forward gd_OnPlayerDisconnect(playerid, reason);
forward gd_OnPlayerSpawn(playerid);
forward gd_OnPlayerDeath(playerid, killerid, reason);
forward gd_OnVehicleSpawn(vehicleid);
forward gd_OnVehicleDeath(vehicleid, killerid);
forward gd_OnPlayerText(playerid, text[]);
forward gd_OnPlayerCommandText(playerid, cmdtext[]);
forward gd_OnPlayerInfoChange(playerid);
forward gd_OnPlayerRequestClass(playerid, classid);
forward gd_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
forward gd_OnPlayerExitVehicle(playerid, vehicleid);
forward gd_OnPlayerStateChange(playerid, newstate, oldstate);
forward gd_OnPlayerEnterCheckpoint(playerid);
forward gd_OnPlayerLeaveCheckpoint(playerid);
forward gd_OnPlayerEnterRaceCheckpoint(playerid);
forward gd_OnPlayerLeaveRaceCheckpoint(playerid);
forward gd_OnRconCommand(cmd[]);
forward gd_OnPlayerPrivmsg(playerid, recieverid, text[]);
forward gd_OnPlayerRequestSpawn(playerid);
forward gd_OnObjectMoved(objectid);
forward gd_OnPlayerObjectMoved(playerid, objectid);
forward gd_OnPlayerPickUpPickup(playerid, pickupid);
forward gd_OnVehicleMod(playerid, vehicleid, componentid);
forward gd_OnVehiclePaintjob(playerid, vehicleid, paintjobid);
forward gd_OnVehicleRespray(playerid, vehicleid, color1, color2);
forward gd_OnPlayerSelectedMenuRow(playerid, row);
forward gd_OnPlayerExitedMenu(playerid);
forward gd_OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
forward gd_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
forward gd_OnPlayerUpdate(playerid);