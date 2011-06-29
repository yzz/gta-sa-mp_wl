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


#include <wl\wl_objective_h>

#include <wl\objective\wl_objective_class>
#include <wl\objective\wl_objective_object>
#include <wl\objective\wl_objective_borcast>
#include <wl\objective\wl_objective_spawn>
#include <wl\objective\wl_objective_tele>


wl_objective_GameModeInit(){
	wl_objective_object_struction();
	wl_objective_class_struction();
	wl_objective_borcast_struction();
	//wl_objective_tele_struction();
}

wl_objective_RequestClass(playerid,classid){
	wl_objective_class_RequestClass(playerid,classid);
}

wl_objective_SpawnPlayer(playerid){
	if(wl_obj_spawn_SpawnPlayer(playerid))return true;
	return false;
}

/*
wl_objective_CommandText(playerid,cmdtext[]){
	//#pragma unsed playerid,cmdtext
	//return wl_objective_tele_CommandText(playerid,cmdtext);
}
*/





/*
#if defined _wl_objective_included
  #endinput
#endif
#define _wl_objective_included
*/
/*
new const stock
	objectFile[]		=		"wl/object.ini",
	vehicleFile[]		=		"wl/vehicle.ini",
	pickupFile[]		=		"wl/pickup.ini",
	borcastFile[]		=		"wl/borcast.ini",
	spawnFile[]			=		"wl/spawn.ini",
	cmdFile[] 			=		"wl/cmd.ini",
	teleFile[] 			=		"wl/tele.ini",
	pClassFile[]		=		"wl/class.ini";
	
	
#define MAX_SPAWN_POS		(100)
#define MAX_BORCAST			(100)
#define MAX_TELE			(1000)	
#define MAX_PLAYER_CLASS	(1000)	
enum e_pClass{
	e_pClass_classid,
	Float:e_pClass_x,
	Float:e_pClass_y,
	Float:e_pClass_z,
	Float:e_pClass_a
};

enum e_pSpawn{
	Float:e_pSpawn_x,
	Float:e_pSpawn_y,
	Float:e_pSpawn_z,
	Float:e_pSpawn_a,
	e_pSpawn_interior,
	e_pSpawn_str[MAX_STRING]
};
enum{
	e_borcast_warning,
	e_borcast_tip,
	e_borcast_study,
	e_borcast_amount
};
	
enum e_tele{
	Float:e_tele_x,
	Float:e_tele_y,
	Float:e_tele_z,
	Float:e_tele_a,
	bool:e_tele_ignoreVec,
	e_tele_interior,
	e_tele_text[MAX_NAME],
	e_tele_cmd1[MAX_NAME],
	e_tele_cmd2[MAX_NAME],
	e_tele_cmd3[MAX_NAME],
	e_tele_cmd4[MAX_NAME],
	e_tele_cmd5[MAX_NAME],
	e_tele_cmd6[MAX_NAME],
	e_tele_cmd7[MAX_NAME],
	e_tele_cmd8[MAX_NAME],
	e_tele_cmd9[MAX_NAME],
	e_tele_cmd10[MAX_NAME],
	e_tele_cmdAmount
};

new stock
	e_pSpawnInfo[MAX_SPAWN_POS][e_pSpawn],
	g_pSpawnposAmount,
	e_borcastInfo[e_borcast_amount][MAX_BORCAST][MAX_STRING],
	g_borcastAmount[e_borcast_amount],
	g_borcastColor[e_borcast_amount] = {COLOR_WARNING,COLOR_TIP,COLOR_STUDY},
	e_wl_gTeleInfo[MAX_TELE][e_tele],
	wl_gteleAmount,
	e_pClassInfo[MAX_PLAYER_CLASS][e_pClass],
	g_pClassAmount;

objective_OnGamemodeInit(){
	Object_Object();
	objective_loadpClass();
	objective_loadtele();
	objective_loadObject();
	objective_loadSpawn();
	objective_loadBorcast();
	SetTimer("randBorcast",1000*120,true);
}


stock objective_loadBorcast(){
	if(!fexist(borcastFile)){
		printf "File \"%s\" not found",spawnFile
		abort();
	}
	new
		borcastName[MAX_NAME],
		borcastMainName[3][] = {"warn","tip","study"},
		tmpstr[MAX_STRING];
	INI_Open(borcastFile);
	for(new i;i<e_borcast_amount;i++){
		for(new j;j<MAX_BORCAST;j++){
			format(borcastName,sizeof(borcastName),"%s%03d",borcastMainName[i],j+1);
			if(!INI_ReadString(tmpstr,borcastName)){
				printf "[Borcast]Borcast %s loaded,amount:%d",borcastMainName[i],g_borcastAmount[i]
				break;
			}
			format(e_borcastInfo[i][j],MAX_STRING,tmpstr);
			//printf "[Borcast]%s",e_borcastInfo[i][j]
			g_borcastAmount[i]++;
		}
	}
	INI_Save();
	INI_Close();
	return true;
}
stock objective_loadSpawn(){
	if(!fexist(spawnFile)){
		printf "File \"%s\" not found",spawnFile
		abort();
	}
	new
		spawnName[MAX_NAME],
		tmpstr[MAX_STRING],
		tmpval;
	for(new i;i<MAX_SPAWN_POS;i++){
		format(spawnName,sizeof(spawnName),"spawn%03d",i+1);
		if(!readini(spawnFile,spawnName,tmpstr)){
			printf "[Spawn]Spawn pos loaded,amount:%d",g_pSpawnposAmount;
			return true;
		}
		sscanf(
			tmpstr,"p,ffffisd",
			e_pSpawnInfo[i][e_pSpawn_x],
			e_pSpawnInfo[i][e_pSpawn_y],
			e_pSpawnInfo[i][e_pSpawn_z],
			e_pSpawnInfo[i][e_pSpawn_a],
			e_pSpawnInfo[i][e_pSpawn_interior],
			e_pSpawnInfo[i][e_pSpawn_str],tmpval
		);
		g_pSpawnposAmount++;
	}
	return true;
}

stock objective_loadpClass(){
	if(!fexist(pClassFile)){
		printf "File \"%s\" not found",objectFile
		abort();
	}
	new
		File:tmpfile = fopen(pClassFile,io_read),
		tmpstr[256],
		classid,
		Float:ox,Float:oy,Float:oz,Float:oa,
		line;
	while(fread(tmpfile,tmpstr)){
		line++;
		if(tmpstr[0] == ';' || tmpstr[0] == '[')continue;
		if(!sscanf(tmpstr,"p,dffff",classid,ox,oy,oz,oa)){
			wl_create_class(classid,ox,oy,oz,oa);
		}else{
			tmpstr[strlen(tmpstr)-2] = '\0';
			printf "File(line:%d) load failed,file string:\r\n\"%s\"",line,tmpstr
		}
	}
	fclose(tmpfile);
	printf "[Class]Class(es) loaded,Amount:%d",g_pClassAmount
	return true;
}
stock objective_loadObject(){
	if(!fexist(objectFile)){
		printf "File \"%s\" not found",objectFile
		abort();
	}
	new
		File:tmpfile = fopen(objectFile,io_read),
		tmpstr[256],
		modelid,
		Float:ox,Float:oy,Float:oz,
		Float:orx,Float:ory,Float:orz,
		objamount,line;
	while(fread(tmpfile,tmpstr)){
		line++;
		if(tmpstr[0] == ';' || tmpstr[0] == '[')continue;
		if(!sscanf(tmpstr,"p,dffffff",modelid,ox,oy,oz,orx,ory,orz)){
			CreateDynamicObject(modelid,ox,oy,oz,orx,ory,orz);
			objamount++;
		}else{
			tmpstr[strlen(tmpstr)-2] = '\0';
			printf "File(line:%d) load failed,file string:\r\n\"%s\"",line,tmpstr
		}
	}
	fclose(tmpfile);
	printf "[Object]Object(s) loaded,Amount:%d",objamount
	return true;
}

stock objective_loadtele(){
	for(new i;i<MAX_TELE;i++){
		new
			teleName[MAX_NAME],
			teleCmd[256];
		format(teleName,sizeof(teleName),"tele%04d",i+1);
		if(!readini(teleFile,teleName,teleCmd)){
			printf "[Tele]Tele loaded,amount:%d",i
			return;
		}
		objective_tele_create(teleCmd);
	}
}




stock wl_cmd_create(const cmdname[]){
	new
		cmdText[MAX_STRING],
		cmdStr[10][MAX_STRING];
	if(!readini(cmdFile,cmdname,cmdText))return false;
	for(new k,l,m;(cmdStr[l][m++]=cmdText[k]);k++){
		if(cmdStr[l][m-1] == ','){
			cmdStr[l][m-1] = '\0';
			l++;
			m=0;
		}
	}
	gcmd_create(cmdname,cmdStr[0],cmdStr[1],cmdStr[2],cmdStr[3],cmdStr[4],cmdStr[5],cmdStr[6],cmdStr[7],cmdStr[8],cmdStr[9]);
	return true;
}	
stock objective_tele_create(tele_cmds[]){
	//printf "|%s|",tele_cmds
	new const
		telePos = wl_gteleAmount,
		tmpval;
	sscanf(
		tele_cmds,"p,ffffiisssssssssssi",
		e_wl_gTeleInfo[telePos][e_tele_x],
		e_wl_gTeleInfo[telePos][e_tele_y],
		e_wl_gTeleInfo[telePos][e_tele_z],
		e_wl_gTeleInfo[telePos][e_tele_a],
		e_wl_gTeleInfo[telePos][e_tele_interior],
		e_wl_gTeleInfo[telePos][e_tele_ignoreVec],
		e_wl_gTeleInfo[telePos][e_tele_text],
		e_wl_gTeleInfo[telePos][e_tele_cmd1],
		e_wl_gTeleInfo[telePos][e_tele_cmd2],
		e_wl_gTeleInfo[telePos][e_tele_cmd3],
		e_wl_gTeleInfo[telePos][e_tele_cmd4],
		e_wl_gTeleInfo[telePos][e_tele_cmd5],
		e_wl_gTeleInfo[telePos][e_tele_cmd6],
		e_wl_gTeleInfo[telePos][e_tele_cmd7],
		e_wl_gTeleInfo[telePos][e_tele_cmd8],
		e_wl_gTeleInfo[telePos][e_tele_cmd9],
		e_wl_gTeleInfo[telePos][e_tele_cmd10],
		tmpval
		
	);
	//printf "%f|%f",px,py
	if(!e_wl_gTeleInfo[telePos][e_tele_cmd1][0]){
		e_wl_gTeleInfo[telePos][e_tele_cmdAmount] = 0;
		return false;
	}
	else if(!e_wl_gTeleInfo[telePos][e_tele_cmd2][0])e_wl_gTeleInfo[telePos][e_tele_cmdAmount] = 1;
	else if(!e_wl_gTeleInfo[telePos][e_tele_cmd3][0])e_wl_gTeleInfo[telePos][e_tele_cmdAmount] = 2;
	else if(!e_wl_gTeleInfo[telePos][e_tele_cmd4][0])e_wl_gTeleInfo[telePos][e_tele_cmdAmount] = 3;
	else if(!e_wl_gTeleInfo[telePos][e_tele_cmd5][0])e_wl_gTeleInfo[telePos][e_tele_cmdAmount] = 4;
	else if(!e_wl_gTeleInfo[telePos][e_tele_cmd6][0])e_wl_gTeleInfo[telePos][e_tele_cmdAmount] = 5;
	else if(!e_wl_gTeleInfo[telePos][e_tele_cmd7][0])e_wl_gTeleInfo[telePos][e_tele_cmdAmount] = 6;
	else if(!e_wl_gTeleInfo[telePos][e_tele_cmd8][0])e_wl_gTeleInfo[telePos][e_tele_cmdAmount] = 7;
	else if(!e_wl_gTeleInfo[telePos][e_tele_cmd9][0])e_wl_gTeleInfo[telePos][e_tele_cmdAmount] = 8;
	else if(!e_wl_gTeleInfo[telePos][e_tele_cmd10][0])e_wl_gTeleInfo[telePos][e_tele_cmdAmount] = 9;
	else e_wl_gTeleInfo[telePos][e_tele_cmdAmount] = 10;
	wl_gteleAmount++;
	
	printf("[tele]%d,pos:%.2f,%.2f,%.2f,%.2f,%d,%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
		e_wl_gTeleInfo[telePos][e_tele_cmdAmount],
		e_wl_gTeleInfo[telePos][e_tele_x],e_wl_gTeleInfo[telePos][e_tele_y],e_wl_gTeleInfo[telePos][e_tele_z],
		e_wl_gTeleInfo[telePos][e_tele_a],e_wl_gTeleInfo[telePos][e_tele_interior],
		e_wl_gTeleInfo[telePos][e_tele_ignoreVec],
		e_wl_gTeleInfo[telePos][e_tele_cmd1],e_wl_gTeleInfo[telePos][e_tele_cmd2],
		e_wl_gTeleInfo[telePos][e_tele_cmd3],e_wl_gTeleInfo[telePos][e_tele_cmd4],
		e_wl_gTeleInfo[telePos][e_tele_cmd5],e_wl_gTeleInfo[telePos][e_tele_cmd6],
		e_wl_gTeleInfo[telePos][e_tele_cmd7],e_wl_gTeleInfo[telePos][e_tele_cmd8],
		e_wl_gTeleInfo[telePos][e_tele_cmd9],e_wl_gTeleInfo[telePos][e_tele_cmd10]
	);
	
	return true;
}

stock looptele_progress(const val1,const val2,retstr[],lenth = sizeof(retstr)){
	switch(val1){ 
		case 0:format(retstr,lenth,"%s",e_wl_gTeleInfo[val2][e_tele_cmd1]); 
		case 1:format(retstr,lenth,"%s",e_wl_gTeleInfo[val2][e_tele_cmd2]); 
		case 2:format(retstr,lenth,"%s",e_wl_gTeleInfo[val2][e_tele_cmd3]); 
		case 3:format(retstr,lenth,"%s",e_wl_gTeleInfo[val2][e_tele_cmd4]); 
		case 4:format(retstr,lenth,"%s",e_wl_gTeleInfo[val2][e_tele_cmd5]); 
		case 5:format(retstr,lenth,"%s",e_wl_gTeleInfo[val2][e_tele_cmd6]); 
		case 6:format(retstr,lenth,"%s",e_wl_gTeleInfo[val2][e_tele_cmd7]); 
		case 7:format(retstr,lenth,"%s",e_wl_gTeleInfo[val2][e_tele_cmd8]); 
		case 8:format(retstr,lenth,"%s",e_wl_gTeleInfo[val2][e_tele_cmd9]); 
		case 9:format(retstr,lenth,"%s",e_wl_gTeleInfo[val2][e_tele_cmd10]); 
	}
}
#define looptele() \
do{ \
	for(new i,j = wl_gteleAmount,k,l[MAX_NAME];i < j;i++){ \
		for(k = 0;k < e_wl_gTeleInfo[i][e_tele_cmdAmount];k++){ \
			looptele_progress(k,i,l); \
			if(!strcmp(cmdtext[1],l)){ \
				TeleportPlayer(playerid,e_wl_gTeleInfo[i][e_tele_x],e_wl_gTeleInfo[i][e_tele_y],e_wl_gTeleInfo[i][e_tele_z],e_wl_gTeleInfo[i][e_tele_a],e_wl_gTeleInfo[i][e_tele_interior],e_wl_gTeleInfo[i][e_tele_ignoreVec]); \
				remindPlayerText(playerid,e_wl_gTeleInfo[i][e_tele_text]); \
				return true; \
			} \ 
		} \
	} \
}while(FALSE)
stock wl_create_class(classid,Float:cx,Float:cy,Float:cz,Float:ca){
	if(g_pClassAmount >= MAX_PLAYER_CLASS)return false;
	new id = g_pClassAmount;
	e_pClassInfo[id][e_pClass_classid] = classid;
	e_pClassInfo[id][e_pClass_x] = cx;
	e_pClassInfo[id][e_pClass_y] = cy;
	e_pClassInfo[id][e_pClass_z] = cz;
	e_pClassInfo[id][e_pClass_a] = ca;
	AddPlayerClass(classid,0,0,0,0,0,0,0,0,0,0);
	g_pClassAmount++;
	return true;
}

objective_RequestClass(playerid,classid){
	new
		Float:tmpx = e_pClassInfo[classid][e_pClass_x],
		Float:tmpy = e_pClassInfo[classid][e_pClass_y],
		Float:tmpz = e_pClassInfo[classid][e_pClass_z],
		Float:tmpa = e_pClassInfo[classid][e_pClass_a];
	SetPlayerPos(playerid,tmpx,tmpy,tmpz);
	SetPlayerFacingAngle(playerid,180-tmpa);
	SetPlayerCameraLookAt(playerid,tmpx,tmpy,tmpz);
	getBackfrontXY(tmpx,tmpy,tmpa,4.0);
	SetPlayerCameraPos(playerid,tmpx,tmpy,tmpz);
}
forward randBorcast();
public randBorcast(){ debug_public_track("randBorcast(){");
	new
		borcast_type = random(e_borcast_amount),
		borcast_pos = random(g_borcastAmount[borcast_type]);
	SendClientMessageToAll(g_borcastColor[borcast_type],e_borcastInfo[borcast_type][borcast_pos]);
	return true;
}
	
randSpawnPlayer(playerid){
	new
		r = random(g_pSpawnposAmount);
	TeleportPlayer(playerid,e_pSpawnInfo[r][e_pSpawn_x],e_pSpawnInfo[r][e_pSpawn_y],e_pSpawnInfo[r][e_pSpawn_z],e_pSpawnInfo[r][e_pSpawn_a],e_pSpawnInfo[r][e_pSpawn_interior],true);
	System_send(playerid,e_pSpawnInfo[r][e_pSpawn_str]);
}
objective_OnPlayerSpawn(playerid){
	randSpawnPlayer(playerid);
}
*/












