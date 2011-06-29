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




static stock
	bool:gcs_s_gcmd_pTeleporting[MAX_PLAYERS];

enum E_gtele_Info{
	Float:E_gtele_x,
	Float:E_gtele_y,
	Float:E_gtele_z,
	Float:E_gtele_a,
	E_gtele_interior,
	E_gtele_type
};
static stock
	gtele_gTeleInfo[MAX_PLAYERS][E_gtele_Info];
	

stock gtele_teleportPlayer(playerid,Float:px,Float:py,Float:pz,Float:pa,Float:vx,Float:vy,Float:vz,Float:va,interior){
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
		gtele_gTeleInfo[playerid][E_gtele_x] = vx;
		gtele_gTeleInfo[playerid][E_gtele_y] = vy;
		gtele_gTeleInfo[playerid][E_gtele_z] = vz;
		gtele_gTeleInfo[playerid][E_gtele_a] = va;
		gtele_gTeleInfo[playerid][E_gtele_type] = GetPlayerVehicleID(playerid); 
		SetPlayerInterior(playerid,interior);
		SetPlayerPos(playerid,vx,vy,vz);
		SetVehiclePos(gtele_gTeleInfo[playerid][E_gtele_type],vx,vy,vz);
	}else{
		gtele_gTeleInfo[playerid][E_gtele_x] = px;
		gtele_gTeleInfo[playerid][E_gtele_y] = py;
		gtele_gTeleInfo[playerid][E_gtele_z] = pz;
		gtele_gTeleInfo[playerid][E_gtele_a] = pa;	
		gtele_gTeleInfo[playerid][E_gtele_type] = 0;
		SetPlayerPos(playerid,px,py,pz);
	}
	gtele_gTeleInfo[playerid][E_gtele_interior] = interior;
	SetTimerEx("gtele_teleportPlayer_1",GetPlayerPing(playerid)*2+400,false,"i",playerid);
	gcs_s_gcmd_pTeleporting[playerid] = true;
	//printf("call:%d,%f,%f,%f,%f,%f,%f,%f,%f,%d",playerid,px,py,pz,pa,vx,vy,vz,va,interior);
	return true;
}
	
forward	gtele_teleportPlayer_1(playerid);
public gtele_teleportPlayer_1(playerid){
	if(gtele_gTeleInfo[playerid][E_gtele_type]){
		SetVehiclePos(
			gtele_gTeleInfo[playerid][E_gtele_type],
			gtele_gTeleInfo[playerid][E_gtele_x],
			gtele_gTeleInfo[playerid][E_gtele_y],
			gtele_gTeleInfo[playerid][E_gtele_z]
		);
		SetVehicleZAngle(
			gtele_gTeleInfo[playerid][E_gtele_type],
			gtele_gTeleInfo[playerid][E_gtele_a]
		);
		PutPlayerInVehicle(playerid,gtele_gTeleInfo[playerid][E_gtele_type],0);
	}else{
		SetPlayerPos(
			playerid,
			gtele_gTeleInfo[playerid][E_gtele_x],
			gtele_gTeleInfo[playerid][E_gtele_y],
			gtele_gTeleInfo[playerid][E_gtele_z]
		);
		SetPlayerFacingAngle(playerid,gtele_gTeleInfo[playerid][E_gtele_a]);
	}
	SetPlayerInterior(playerid,gtele_gTeleInfo[playerid][E_gtele_interior]);
	gcs_s_gcmd_pTeleporting[playerid] = false;
	//printf("called");
}





//===========================================================//



/**===============================================================
*Date:2009/3/14
*Author:GCS Team
*Name:gcmd_telep(playerid,Float:x,Float:y,Float:z);
*Describe:To teleport player with object load,automatic teleport vehicle too,etc.
*Feel like to avoid falling when loading objects
*Future:Help facing to anti-hack teleport.
=================================================================*/

	
	
stock bool:gcmd_gcmd_PlayerTeleporting(playerid){
	if(IsPlayerConnected(playerid) && gcs_s_gcmd_pTeleporting[playerid])return true;
	return false;
}
forward gcmd_telep_End(playerid,Float:x,Float:y,Float:z,Float:angle,pinterior,bool:ignoreVec,virtualworld);
stock gcmd_telep(playerid,Float:x,Float:y,Float:z,Float:angle = -65535.0,pinterior = -20,bool:ignoreVec=false,virtualworld = -20){
	/*
	if(gcmd_gcmd_PlayerTeleporting(playerid)){
		SendClientMessage(playerid,0x0000FFAA,"[传送]传送失败,一项传送进行中");
		return false;
	}
	*/
	if(!ignoreVec && GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
		SetVehiclePos(GetPlayerVehicleID(playerid),x,y,z);
		if(angle == -65535.0) GetVehicleZAngle(GetPlayerVehicleID(playerid),angle);
	}
	else{
		SetPlayerPos(playerid,x,y,z);
		if(angle == -65535.0) GetPlayerFacingAngle(playerid,angle);
	}
	if(pinterior == -20) pinterior = GetPlayerInterior(playerid);
	if(virtualworld == -20) virtualworld = GetPlayerVirtualWorld(playerid);
	gcs_s_gcmd_pTeleporting[playerid] = true;
	SetTimerEx("gcmd_telep_End",GetPlayerPing(playerid)*2+800,false,"iffffiii",playerid,x,y,z,angle,pinterior,ignoreVec,virtualworld);
	return true;
}
public gcmd_telep_End(playerid,Float:x,Float:y,Float:z,Float:angle,pinterior,bool:ignoreVec,virtualworld){
	if(!ignoreVec && GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
		SetVehicleVirtualWorld(GetPlayerVehicleID(playerid),virtualworld);
		SetVehicleZAngle(GetPlayerVehicleID(playerid),angle);
		SetVehiclePos(GetPlayerVehicleID(playerid),x,y,z);
		LinkVehicleToInterior(GetPlayerVehicleID(playerid),pinterior);
	}else
	{
		SetPlayerVirtualWorld(playerid,virtualworld);
		SetPlayerPos(playerid,x,y,z);
		SetPlayerFacingAngle(playerid,angle);
	}
	if(pinterior != -20)
	SetPlayerInterior(playerid,pinterior);
	PlayerPlaySound(playerid, 1057,0,0,0);
	gcs_s_gcmd_pTeleporting[playerid] = false;
	return true;
}
//=========================================================================//


/**======================================================
*Date:2009/3/21
*Name:remindPlayerText
*Author:Gcs Team
*Describe:remind a player with some text while using sound
=======================================================*/
//======================================================
stock gcmd_rpText(playerid,const remind_text[]){
	new
		sendformatstring[MAX_STRING];
	format(sendformatstring,sizeof(sendformatstring),"~n~~n~~n~~n~~n~~n~~n~~n~~n~%s",remind_text);
	GameTextForPlayer(playerid,sendformatstring,3000,3);
	PlayerPlaySound(playerid,1056,0,0,0);
	return true;
}
//===========================================================


#define gtele_multitele(%1,%2,%3) \
	if(!strcmp((%1),cmdtext[1],true)) \
		return gcmd_rpText(playerid,(%2)),gtele_teleportPlayer(playerid,%3)

#define gtele_singeltele(%1,%2,%3,%4,%5,%6,%7,%8) \
	if(!strcmp((%1),cmdtext[1],true)) \
	return gcmd_rpText(playerid,(%8)),gcmd_telep(playerid,(%2),(%3),(%4),(%5),(%6),(%7))


