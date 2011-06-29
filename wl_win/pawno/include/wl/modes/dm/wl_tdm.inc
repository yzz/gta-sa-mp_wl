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


/*
#define DEBUG_TDM				(true)
#define COLOR_TDM				(COLOR_LIGHTBLUE)


#define TDM_send(%1,%2,%3) \
do{\
	new \
		sendfstring[MAX_STRING];\
	format(sendfstring,MAX_STRING,(%2),%3);\
	SendClientMessage((%1),COLOR_TDM,sendfstring);\
}while(FALSE)

stock TDM_send(playerid,const sendfstring[]){
	SendClientMessage(playerid,COLOR_TDM,sendfstring);
}

#define TDM_sendAll(%1,%2) \
do{ \
	new \
	sendfstring[MAX_STRING];\
	format(sendfstring,MAX_STRING,(%1),%2);\
	SendClientMessageToAll(COLOR_TDM,sendfstring);\
}while(FALSE)
stock TDM_sendAll(const sendfstring[]){
	SendClientMessageToAll(COLOR_TDM,sendfstring);
}


forward TDM_getPlayerIn(playerid);


//======================================TDM=========================================//


#define MAX_TDM_NAME					(24)

#define MAX_TDM_WEAPON_PACKAGE_NAME		(MAX_TDM_NAME)
#define INVALID_TDM_WEAPON_PACKAGE_ID	(-1)
#define MAX_TDM_WEAPON_PACKAGE			(10)//do not change it
#define MAX_TDM							(100)//max is 100
#define MAX_TDM_SPAWN_POS				(100)
#define INVALID_TDM_ID					(-1)

#define WORLD_TDM						(20)
enum{
	TDM_pausing,
	TDM_voting,
	TDM_starting,
}
//================================================================================================

enum _TDM_Info{
	Name[MAX_STRING],
	Float:Spawn_Area[4],
	Float:Spawn_Pos_x[MAX_TDM_SPAWN_POS],
	Float:Spawn_Pos_y[MAX_TDM_SPAWN_POS],
	Float:Spawn_Pos_z[MAX_TDM_SPAWN_POS],
	Spawn_Pos_Amount,
	Float:Spawn_Health,
	Float:Spawn_Armour,
	Spawn_SafeTime,
	Spawn_Interior,
	//package
	Package_Weapon[(MAX_TDM_WEAPON_PACKAGE)*MAX_WEAPON_SLOT],
	Package_Ammo[(MAX_TDM_WEAPON_PACKAGE)*MAX_WEAPON_SLOT],
	Package_Name[(MAX_TDM_WEAPON_PACKAGE)*MAX_TDM_NAME],
	Package_Amount,
	//
	Player_Spawn_Times,
	Vote_Times,
	
	End_Time,

	bool:active,
	bool:used
};		
static TDMInfo[MAX_TDM][_TDM_Info];
static
	TDM_Time_Type = TDM_pausing,
	TDM_CurID,
	TDM_Vote_Time,
	TDM_Start_Time,
	TDM_End_Time,
	TDM_Next_Time;



stock TDM_setCur(tdmid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setCur called");
	#endif	
	TDM_CurID = tdmid;
	return true;
}
stock TDM_getCur(){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getCur called");
	#endif	
	return TDM_CurID;
}
stock TDM_setType(type){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setType called");
	#endif	
	TDM_Time_Type = type;
	return true;
}
stock TDM_getType(){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getType called");
	#endif	
	return TDM_Time_Type
}
stock TDM_setVoteTime(votetime){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setVoteTime called");
	#endif	
	TDM_Vote_Time = votetime;
	return true;
}
stock TDM_getVoteTime(){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getVoteTime called");
	#endif	
	return TDM_Vote_Time;
}
stock TDM_setStartTime(starttime){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setStartTime called");
	#endif	
	TDM_Start_Time = starttime;
	return true;
}
stock TDM_getStartTime(){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getStartTime called");
	#endif	
	return TDM_Start_Time;
}
stock TDM_setEndTime(endtime){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setEndTime called");
	#endif	
	TDM_End_Time = endtime;
	return true;
}
stock TDM_getEndTime(){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getEndTime called");
	#endif	
	return TDM_End_Time;
}
stock TDM_setNextTime(nexttime){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setNextTime called");
	#endif	
	TDM_Next_Time = nexttime;
	return true;
}
stock TDM_getNextTime(){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getNextTime called");
	#endif	
	return TDM_Next_Time;
}
stock TDM_setPackageWeaponAmmo(tdmid,pkgid,Weaponid[],Ammo[]){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setPackageWeaponAmmo called");
	#endif	
	//if(!TDM_isValidID(tdmid))return false;
	for(
		new
			pos = pkgid*MAX_WEAPON_SLOT,
			lenth = pos+MAX_WEAPON_SLOT,
			i;
		pos < lenth;
		pos++,i++
	){
		TDMInfo[tdmid][Package_Weapon][pos] = Weaponid[i];
		TDMInfo[tdmid][Package_Ammo][pos] = Ammo[i];
		TDMInfo[tdmid][Package_Amount]++;
	}
	return true;
}
stock TDM_getPackageWeapon(tdmid,pkgid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getPackageWeapon called");
	#endif	
	//if(!TDM_isValidID(tdmid))return false;
	for(new i;i < TDMInfo[tdmid][Package_Amount];i++){
		package_weapon[i] = TDMInfo[tdmid][Package_Weapon][pkgid*MAX_WEAPON_SLOT+i];
	}
	//CallRemoteFunction("passString_send","s",TDMInfo[tdmid][Package_Weapon]);
	return TDMInfo[tdmid][Package_Weapon];
}
stock TDM_getPackageAmmo(tdmid,pkgid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getPackageAmmo called");
	#endif	
	//if(!TDM_isValidID(tdmid))return false;
	for(new i;i < TDMInfo[tdmid][Package_Amount];i++){
		package_ammo[i] = TDMInfo[tdmid][Package_Ammo][pkgid*MAX_WEAPON_SLOT+i];
	}
	//CallRemoteFunction("passString_send","s",TDMInfo[tdmid][Package_Ammo]);
	return TDMInfo[tdmid][Package_Ammo];
}
stock TDM_getPackageName(tdmid,pkgid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getPackageName called");
	#endif	
	//if(!TDM_isValidID(tdmid))return false;
	for(
		new
			pos = pkgid*MAX_TDM_NAME,
			length = pos+MAX_TDM_NAME,
			i;
		pos < length;
		pos++,i++
	){
		pkg_name[i] = TDMInfo[tdmid][Package_Name][pos];
	}
	//CallRemoteFunction("passString_send","s",TDMInfo[tdmid][Package_Name]);
	return TDMInfo[tdmid][Package_Name];
}
stock TDM_setPackageName(tdmid,pkgid,const pkg_name[]){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setPackageName called");
	#endif	
	//if(!TDM_isValidID(tdmid))return false;
	for(
		new
			pos = pkgid*MAX_TDM_NAME,
			lenth = pos+MAX_TDM_NAME,
			i;
		pos < lenth;
		pos++,i++
	){
		TDMInfo[tdmid][Package_Name][pos] = pkg_name[i];
	}
	return true;
}
stock TDM_getPackageAmount(tdmid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getPackageAmount called");
	#endif	
	return TDMInfo[tdmid][Package_Amount];
}
stock TDM_setPackageAmount(tdmid,amount){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setPackageAmount called");
	#endif	
	TDMInfo[tdmid][Package_Amount] = amount;
	return true;
}
stock TDM_setName(tdmid,const tdm_name[]){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setName called");
	#endif	
	format(TDMInfo[tdmid][Name],MAX_TDM_NAME,"%s",tdm_name);
	return true;
}
stock TDM_getName(tdmid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getName called");
	#endif	
	//CallRemoteFunction("passString_send","s",TDMInfo[tdmid][Name]);
	return TDMInfo[tdmid][Name];
}
stock TDM_setArea(tdmid,Float:minx,Float:miny,Float:maxx,Float:maxy){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setArea called");
	#endif	
	TDMInfo[tdmid][Spawn_Area][0] = minx;
	TDMInfo[tdmid][Spawn_Area][1] = miny;
	TDMInfo[tdmid][Spawn_Area][2] = maxx;
	TDMInfo[tdmid][Spawn_Area][3] = maxy;
	return true;
}
stock TDM_isPlayerInTDMArea(playerid,tdmid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_isPlayerInTDMArea called");
	#endif	
	return PlayerInArea(playerid,TDMInfo[tdmid][Spawn_Area][0],TDMInfo[tdmid][Spawn_Area][1],TDMInfo[tdmid][Spawn_Area][2],TDMInfo[tdmid][Spawn_Area][3]);
}
stock TDM_setPlayerSpawnPos(tdmid,Float:px,Float:py,Float:pz){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setPlayerSpawnPos called");
	#endif	
	if(TDMInfo[tdmid][Spawn_Pos_Amount] >= MAX_TDM_SPAWN_POS)return false;
	TDMInfo[tdmid][Spawn_Pos_x][TDMInfo[tdmid][Spawn_Pos_Amount]] = px;
	TDMInfo[tdmid][Spawn_Pos_y][TDMInfo[tdmid][Spawn_Pos_Amount]] = py;
	TDMInfo[tdmid][Spawn_Pos_z][TDMInfo[tdmid][Spawn_Pos_Amount]] = pz;
	TDMInfo[tdmid][Spawn_Pos_Amount]++;
	return true;
}
stock TDM_getPlayerSpawnPos(tdmid,spawn_pos,&Float:px,&Float:py,&Float:pz){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getPlayerSpawnPos called");
	#endif	
	px = TDMInfo[tdmid][Spawn_Pos_x][spawn_pos];
	px = TDMInfo[tdmid][Spawn_Pos_y][spawn_pos];
	px = TDMInfo[tdmid][Spawn_Pos_z][spawn_pos];
	return true;
}

//public TDM_setPlayerToTDMSpawn(playerid,tdmid,spawn_pos){ debug_public_track("TDM_setPlayerToTDMSpawn(playerid,tdmid,spawn_pos){");
//	TeleportPlayer( \
//		playerid, \
//		TDMInfo[tdmid][Spawn_Pos_x][spawn_pos], \
//		TDMInfo[tdmid][Spawn_Pos_y][spawn_pos], \
//		TDMInfo[tdmid][Spawn_Pos_z][spawn_pos], \
//		0,true
//	);
//	return true;
//}

stock TDM_setPlayerSpawnPosAmount(tdmid,amount){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setPlayerSpawnPosAmount called");
	#endif	
	TDMInfo[tdmid][Spawn_Pos_Amount] = amount;
	return true;
}
stock TDM_getPlayerSpawnPosAmount(tdmid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getPlayerSpawnPosAmount called");
	#endif	
	return TDMInfo[tdmid][Spawn_Pos_Amount];
}
stock TDM_setPlayerSpawnHealth(tdmid,Float:spawn_health){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setPlayerSpawnHealth called");
	#endif	
	TDMInfo[tdmid][Spawn_Health] = spawn_health;
	return true;
}
stock TDM_getPlayerSpawnHealth(tdmid,&Float:spawn_health){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getPlayerSpawnHealth called");
	#endif	
	spawn_health = TDMInfo[tdmid][Spawn_Health];
	return true;
}
stock TDM_setPlayerSpawnArmour(tdmid,Float:spawn_armour){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setPlayerSpawnArmour called");
	#endif	
	TDMInfo[tdmid][Spawn_Armour] = spawn_armour;
	return true;
}
stock TDM_getPlayerSpawnArmour(tdmid,&Float:spawn_armour){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getPlayerSpawnArmour called");
	#endif	
	spawn_armour = TDMInfo[tdmid][Spawn_Armour];
	return true;
}
stock TDM_setSafeTime(tdmid,safetime){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setSafeTime called");
	#endif	
	TDMInfo[tdmid][Spawn_SafeTime] = safetime;
	return true;
}
stock TDM_getSafeTime(tdmid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getSafeTime called");
	#endif	
	return TDMInfo[tdmid][Spawn_SafeTime];
}
stock TDM_setInterior(tdmid,interiorid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setInterior called");
	#endif	
	TDMInfo[tdmid][Spawn_Interior] = interiorid;
	return true;
}
stock TDM_getInterior(tdmid){
	return TDMInfo[tdmid][Spawn_Interior];
}
stock TDM_setSpawnTimes(tdmid,times){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setSpawnTimes called");
	#endif	
	TDMInfo[tdmid][Player_Spawn_Times] = times;
	return true;
}

stock TDM_getSpawnTimes(tdmid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getSpawnTimes called");
	#endif	
	return TDMInfo[tdmid][Player_Spawn_Times];
}
stock TDM_setVoteAmount(tdmid,amount){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setVoteAmount called");
	#endif	
	TDMInfo[tdmid][Vote_Times] = amount;
	return true;
}
stock TDM_getVoteAmount(tdmid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getVoteAmount called");
	#endif	
	return TDMInfo[tdmid][Vote_Times];
}
stock TDM_setTDMEndTime(tdmid,endtime){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setTDMEndTime called");
	#endif	
	TDMInfo[tdmid][End_Time] = endtime;
	return true;
}
stock TDM_getTDMEndTime(tdmid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getTDMEndTime called");
	#endif	
	return TDMInfo[tdmid][End_Time]
}
stock TDM_setUsed(tdmid,bool:set){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setUsed called");
	#endif	
	TDMInfo[tdmid][used] = set;
	return true;
}
stock TDM_isUsed(tdmid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_isUsed called");
	#endif	
	return TDMInfo[tdmid][used];
}
stock TDM_setActive(tdmid,bool:set){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setActive called");
	#endif	
	TDMInfo[tdmid][active] = set;
	return true;
}
stock TDM_isActive(tdmid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_isActive called");
	#endif	
	return TDMInfo[tdmid][active];
}
stock TDM_setPlayerSpawnTime(playerid,times){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setPlayerSpawnTime called");
	#endif	
	PlayerInfo[playerid][TDM_Spawn_Time] = times;
	return true;
}
stock TDM_getPlayerSpawnTime(playerid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getPlayerSpawnTime called");
	#endif	
	return PlayerInfo[playerid][TDM_Spawn_Time];
}
stock TDM_setPlayerScore(playerid,score){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setPlayerScore called");
	#endif	
	PlayerInfo[playerid][TDM_Score] = score;
	return true;
}
stock TDM_getPlayerWeaponPackage(playerid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getPlayerWeaponPackage called");
	#endif	
	return PlayerInfo[playerid][TDM_Package];
}
stock TDM_setPlayerPackage(playerid,pkgid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setPlayerPackage called");
	#endif	
	PlayerInfo[playerid][TDM_Package] = pkgid;
	return true;
}

stock TDM_getPlayerScore(playerid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getPlayerScore called");
	#endif	
	return PlayerInfo[playerid][TDM_Score];
}
stock TDM_getPlayerVote(playerid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getPlayerVote called");
	#endif	
	return PlayerInfo[playerid][TDM_VoteFor];
}
stock TDM_setPlayerVote(playerid,tdmid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setPlayerVote called");
	#endif	
	PlayerInfo[playerid][TDM_VoteFor] = tdmid;
}
public TDM_getPlayerIn(playerid){ debug_public_track("TDM_getPlayerIn(playerid){");
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_getPlayerIn called");
	#endif	
	return PlayerInfo[playerid][TDM_In];
}
stock TDM_setPlayerIn(playerid,tdmid){
	#if DEBUG_DM
		writetolog("[DEBUG_TDM]TDM_setPlayerIn called");
	#endif	
	PlayerInfo[playerid][TDM_In] = tdmid;
	printf "%d,%d",playerid,tdmid
}
*/
gcmd(dm_teamDM){
//	GDM_send(player(),"[TDM]开发中");
}
