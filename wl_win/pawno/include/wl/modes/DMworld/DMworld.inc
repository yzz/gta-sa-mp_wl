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




#define WL_DMWorld			(false)

#define zone:		zone_
#define gang:		gang_
#define dmw:		dmw_
#define dmwdmin:	dmwadmin_
#define dmwweapon:  dmweapon_
#define dmwscore: 	dmwscore_
#define dmwvehicle: dmwvehicle_

//#define function:%1(%2) forward %1(%2);public %1(%2) debug_public_track("%1(%2)");

//create a gangzone
//INSERT INTO gangzone_state VALUES(NULL,1,'LSPD_YARD',1433.6691,-1727.6340,8.3828,1525.7528,-1596.6997,53.3906,1479.1432,-1687.4896,15.0469);
//create a gang
//INSERT INTO gang_stat VALUES(NULL,'[O.P.E.S]','[O.P.E.S]yzz',3);
#if WL_DMWorld

#define WL_DMW_VERSION			"0.5.1.0"

#define DMWorld_ID				(10)
#define DMW_ICON_ID				(2)


#define COLOR_DMWORLD			(COLOR_LIGHTBLUE)
#define MAX_GANG_NAME			(32)
#define MAX_GANG_ZONE_NAME		(32)
#define MAX_ZONE_NAME			(32)
#define INVALID_GANG_ZONE_ID	(0)
#define INVALID_GANGZONE_ID		(0)
#define INVALID_ZONE_ID			(0)
#define MAX_GANGS				(1000)
#define INVALID_GANG_ID			(0)
//#define ZONE_ATTACK_TIME		(60 * 30)//second(s)

#define DMW_ORG_SPAWNPOINT_X	(1543.8893+random(10))
#define DMW_ORG_SPAWNPOINT_Y	(-1353.5454+random(10))
#define DMW_ORG_SPAWNPOINT_Z	(329.4739+2)

forward dmw:isPlayerSpecDMW(playerid);
public dmw:isPlayerSpecDMW(playerid){ debug_public_track("dmw:isPlayerSpecDMW(playerid){");
	return ((GetPlayerVirtualWorld(playerid) == DMWorld_ID) && !GetPVarInt(playerid,"wl_mode_dmWorld_inworld"));
}

dmw(var){
	return (GetPlayerVirtualWorld(var) == DMWorld_ID);
}



enum {
	gang_relation_neutral,
	gang_relation_hostilit,
	gang_relation_alliance
};

new
	DB:db_dmworld;
//	DB:db_gangzone,
//	DB:db_gang;

new Text:pGangZoneInfo[MAX_PLAYERS];

#define dmw_send(%1,%2,%3) wl_lang_send((%1),COLOR_DMWORLD,%2,%3)
dmw_send(playerid,msg_identify[]){
	wl_lang_send(playerid,COLOR_DMWORLD,msg_identify);
}


#define dmw_sendAll(%1,%2) loopPlayer(var)if(dmw(var))wl_lang_send(var,COLOR_DMWORLD,(%1),%2)
dmw_sendAll(msg_identify[]){
	loopPlayer(var)if(dmw(var))wl_lang_send(COLOR_DMWORLD,msg_identify);
}

#define gang_send(%1,%2,%3) wl_lang_send((%1),COLOR_DMWORLD,%2,%3)
gang_send(playerid,msg_identify[]){
	wl_lang_send(playerid,COLOR_DMWORLD,msg_identify);
}

#define gang_sendgang(%1,%2,%3) loopPlayer(var)if(gang:getPlayerGang(var)==(%1))wl_lang_send(var,COLOR_DMWORLD,%2,%3)
stock gang_sendgang(gangid,msg_identify[]){
	loopPlayer(var)if(gang:getPlayerGang(var)==gangid)wl_lang_send(var,COLOR_DMWORLD,msg_identify);
}



forward OnPlayerGangAttackStart(gangid,zoneid);	
forward OnPlayerGangAttackStop(gangid,zoneid,reasoncode);
forward OnPlayerGangAttackWin(attackgangid,zoneid,defendgangid);	
forward dmw_attackZoneItterCheck(gangid,zoneid);
forward dmw_OnPlayerDisallowedIn(playerid);
forward dmw_OnPlayerAllowedIn(playerid);
forward OnGangdmwScoreChange(gangid,oldscore,newscore);
forward dmw_plrPositionProcess();
forward gang:PlayerPreloginItter(playerid);
forward dmw_OnPlayerEnterGangZone(playerid,gangzoneid);
forward dmw_OnPlayerLeaveGangZone(playerid,gangzoneid);
forward dmw_plrGangZone_ItterCheck();

forward dmw:getPlayer(playerid);

public dmw:getPlayer(playerid){ debug_public_track("dmw:getPlayer(playerid){");
	return GetPVarInt(playerid,"wl_mode_dmWorld_inworld");
}
dmw:setPlayer(playerid,dmw_state){
	SetPVarInt(playerid,"wl_mode_dmWorld_inworld",dmw_state);
	return true;
}

/*
dmw:setPlayerGang(playerid,gangid){
	SetPVarInt(playerid,"wl_dmw_plr_gang",gangid);
	return true;
}
dmw:getPlayerGang(playerid){
	return GetPVarInt(playerid,"wl_dmw_plr_gang");
}
*/

#include <wl\modes\DMworld\dmwSelfdamage>
#include <wl\modes\DMworld\dmwCountAmmoHP>
#include <wl\modes\DMworld\dmwAdmin>
#include <wl\modes\DMworld\dmwBlackList>
#include <wl\modes\DMworld\dmwZone>
#include <wl\modes\DMworld\dmwGang>
#include <wl\modes\DMworld\dmwScore>
#include <wl\modes\DMworld\dmwWeapon>
#include <wl\modes\DMworld\dmwVehicle>
#include <wl\modes\DMworld\dmwAutoOpen>
#include <wl\modes\DMworld\dmwTextdraw>
#include <wl\modes\DMworld\dmw3DText>

dmw:setPlayerToGangSpawn(playerid){
	new
		Float:x,Float:y,Float:z;
	if(gang:getDynamicSpawnPoint(gang:getPlayerGang(playerid),x,y,z)){
		TeleportPlayer(playerid,x,y,z);
	}
	else {
		gang:getGangSpawnPoint(gang:getPlayerGang(playerid),x,y,z);
		if(x == 0 && y == 0 && z == 0){
			TeleportPlayer(playerid,DMW_ORG_SPAWNPOINT_X,DMW_ORG_SPAWNPOINT_Y,DMW_ORG_SPAWNPOINT_Z);
		} 
		else {
			TeleportPlayer(playerid,x,y,z);
		}
	}
	return true;
}
gang:getDynamicSpawnPoint(gangid,&Float:x,&Float:y,&Float:z){
	loopPlayer(playerid){
		if(gang:getPlayerGang(gangid) == gangid && gang:getPlayerInGangLevel(playerid) == 10 && dmw:isPlayerStayEffective(playerid)){
			new
				zoneid = zone:getPlayerZoneByPosition(playerid);
			if(zoneid != INVALID_ZONE_ID && zone:getOwnedGang(zoneid) == gangid){
				zone:getZoneSpawnPoint(zoneid,x,y,z);
				return true;
			}
		}
	}
	return false;
}

dmw:setPlayerIn(playerid){
	ResetPlayerWeapons(playerid);
	SetPlayerVirtualWorld(playerid,DMWorld_ID);
	SetPlayerHealth(playerid,100);
	SetPlayerArmour(playerid,100);
	dmw_setPlayer(playerid,true);
	dmw_setPlayerToGangSpawn(playerid);
}
dmw:setPlayerOut(playerid){
	ResetPlayerWeapons(playerid);
	dmw_setPlayer(playerid,false);
	SetPlayerVirtualWorld(playerid,0);
	OnPlayerSpawn(playerid);
}

#define dmw_isLegalTag(%1) gang:isLegalTag(%1) 
#define dmw_getPlayerGangTag(%1) gang:getPlayerGangTag(%1) 
#define dmw_isPlayerHasGangTag(%1) gang:isPlayerHasGangTag(%1) 
#define dmw_isTagRegistered(%1) gang:isTagRegistered(%1)
#define dmw_getGangByTag(%1) gang:getGangByTag(%1)

//===========================================================//
dmw:MarkerProcess(playerid,showplayerid){
	if(!(dmw:getPlayer(playerid) && dmw:getPlayer(showplayerid))) return;
	//if(gang:getPlayerGang(playerid) == gang:getPlayerGang(showplayerid)){
		new
			Float:dis = getDisBetweenPlayer(playerid,showplayerid);
		if(dis < 50){
			SetPlayerMarkerForPlayer(playerid,showplayerid,transparencyColor(gang:getPlayerColorByRelation(playerid,showplayerid),255));
			SetPlayerMarkerForPlayer(showplayerid,playerid,transparencyColor(gang:getPlayerColorByRelation(showplayerid,playerid),255));
		}
		else if(dis < 100){
			SetPlayerMarkerForPlayer(playerid,showplayerid,transparencyColor(gang:getPlayerColorByRelation(playerid,showplayerid),220));
			SetPlayerMarkerForPlayer(showplayerid,playerid,transparencyColor(gang:getPlayerColorByRelation(showplayerid,playerid),220));
		}		
		else if(dis < 150){
			SetPlayerMarkerForPlayer(playerid,showplayerid,transparencyColor(gang:getPlayerColorByRelation(playerid,showplayerid),190));
			SetPlayerMarkerForPlayer(showplayerid,playerid,transparencyColor(gang:getPlayerColorByRelation(showplayerid,playerid),190));
		}
		else if(dis < 200){
			SetPlayerMarkerForPlayer(playerid,showplayerid,transparencyColor(gang:getPlayerColorByRelation(playerid,showplayerid),160));
			SetPlayerMarkerForPlayer(showplayerid,playerid,transparencyColor(gang:getPlayerColorByRelation(showplayerid,playerid),160));
		}
		else if(dis < 250){
			SetPlayerMarkerForPlayer(playerid,showplayerid,transparencyColor(gang:getPlayerColorByRelation(playerid,showplayerid),130));
			SetPlayerMarkerForPlayer(showplayerid,playerid,transparencyColor(gang:getPlayerColorByRelation(showplayerid,playerid),130));
		}
		else if(dis < 300){
			SetPlayerMarkerForPlayer(playerid,showplayerid,transparencyColor(gang:getPlayerColorByRelation(playerid,showplayerid),110));
			SetPlayerMarkerForPlayer(showplayerid,playerid,transparencyColor(gang:getPlayerColorByRelation(showplayerid,playerid),110));
		}
		else if(dis < 350){
			SetPlayerMarkerForPlayer(playerid,showplayerid,transparencyColor(gang:getPlayerColorByRelation(playerid,showplayerid),70));
			SetPlayerMarkerForPlayer(showplayerid,playerid,transparencyColor(gang:getPlayerColorByRelation(showplayerid,playerid),70));
		}
		else if(dis < 400){
			SetPlayerMarkerForPlayer(playerid,showplayerid,transparencyColor(gang:getPlayerColorByRelation(playerid,showplayerid),50));
			SetPlayerMarkerForPlayer(showplayerid,playerid,transparencyColor(gang:getPlayerColorByRelation(showplayerid,playerid),50));
		}
		else {
			if(gang:getPlayerGang(playerid) != gang:getPlayerGang(showplayerid)){
				SetPlayerMarkerForPlayer(playerid,showplayerid,transparencyColor(gang:getPlayerColorByRelation(playerid,showplayerid),0));
				SetPlayerMarkerForPlayer(showplayerid,playerid,transparencyColor(gang:getPlayerColorByRelation(showplayerid,playerid),0));
			}
		}
	//}
}
gang:getPlayerColorByRelation(playerid1,playerid2){
	if(gang:getPlayerGang(playerid1) != INVALID_GANG_ID && (gang:getPlayerGang(playerid1) == gang:getPlayerGang(playerid2))){
		return 0x00FF00FF;//GREEN
	}
	new
		relationto = gang:getGangRelation(gang:getPlayerGang(playerid1),gang:getPlayerGang(playerid2)),
		relationfrom = gang:getGangRelation(gang:getPlayerGang(playerid2),gang:getPlayerGang(playerid1));
	switch(relationto){
		case gang_relation_alliance:{
			switch(relationfrom){
				case gang_relation_alliance:{
					return 0x00FFFFFF;//lightblue
				}
				case gang_relation_neutral:{
					return 0xFFFF88FF;//sky-yellow
				}
				case gang_relation_hostilit:{
					return 0x0000FFFF;//deepblue
				}
			}
		}
		case gang_relation_neutral:{
			switch(relationfrom){
				case gang_relation_alliance:{
					return 0x00AAAAFF;//grey-blue
				}
				case gang_relation_neutral:{
					return 0xAAAAAAFF;//grey
				}
				case gang_relation_hostilit:{
					return 0xAA55AAFF;//grey-purple
				}
			}			
		}
		case gang_relation_hostilit:{
			switch(relationfrom){
				case gang_relation_alliance:{
					return 0xFFFF00FF;//yellow
				}
				case gang_relation_neutral:{
					return 0xFF8800FF;//orange
				}
				case gang_relation_hostilit:{
					return 0xFF0000FF;//red
				}
			}			
		}
	}
	return 0xAAAAAABB;//grey
}
forward dmw:getGangZoneColorByPlrGang(playerid,gangid);
public dmw:getGangZoneColorByPlrGang(playerid,gangid){  debug_public_track("dmw:getGangZoneColorByPlrGang(playerid,gangid){ ");

	if(gang:getPlayerGang(playerid) == gangid && gang:getPlayerGang(playerid) != INVALID_GANG_ID){
		return 0x00FF00BB;//GREEN
	}	
	new
		relationto = gang:getGangRelation(gang:getPlayerGang(playerid),gangid),
		relationfrom = gang:getGangRelation(gangid,gang:getPlayerGang(playerid));
	switch(relationto){
		case gang_relation_alliance:{
			switch(relationfrom){
				case gang_relation_alliance:{
					return 0x00FFFFBB;//lightblue
				}
				case gang_relation_neutral:{
					return 0xFFFF88BB;//sky-yellow
				}
				case gang_relation_hostilit:{
					return 0x0000FFBB;//deepblue
				}
			}
		}
		case gang_relation_neutral:{
			switch(relationfrom){
				case gang_relation_alliance:{
					return 0x00AAAABB;//grey-blue
				}
				case gang_relation_neutral:{
					return 0xAAAAAABB;//grey
				}
				case gang_relation_hostilit:{
					return 0xAA55AABB;//grey-purple
				}
			}			
		}
		case gang_relation_hostilit:{
			switch(relationfrom){
				case gang_relation_alliance:{
					return 0xFFFF00BB;//yellow
				}
				case gang_relation_neutral:{
					return 0xFF8800BB;//orange
				}
				case gang_relation_hostilit:{
					return 0xFF0000BB;//red
				}
			}			
		}
	}
	return 0xAAAAAAFF;//grey
	/*
	new
		playergangid = gang:getPlayerGang(playerid),
		relation = gang:getGangRelation(playergangid,gangid);
	if(relation == gang_relation_neutral){
		return transparencyColor(COLOR_GREY,100);//COLOR_GREY
	}
	if(relation == gang_relation_hostilit){
		return transparencyColor(COLOR_ORANGE,150);//COLOR_ORANGE
	}
	if(relation == gang_relation_alliance){
		if(gangid == playergangid){
			return transparencyColor(COLOR_GREEN,150);
		}
		else {
			return transparencyColor(COLOR_LIGHTBLUE,150);
		}
	}
	return transparencyColor(COLOR_GREY,150);
	*/
}

dmw:updateGangZoneInGameForPlr(playerid,gangzoneid){
	if(zone_getZoneWarState(gangzoneid)){
		GangZoneShowForPlayer(playerid,zone:getZoneIngameID(gangzoneid),dmw_getGangZoneColorByPlrGang(playerid,zone:getZoneGang(gangzoneid)));
		GangZoneFlashForPlayer(playerid,zone:getZoneIngameID(gangzoneid),COLOR_RED);
	}
	else {
		GangZoneStopFlashForPlayer(playerid,zone:getZoneIngameID(gangzoneid));
		GangZoneShowForPlayer(playerid,zone:getZoneIngameID(gangzoneid),dmw_getGangZoneColorByPlrGang(playerid,zone:getZoneGang(gangzoneid)));
	}
	return true;
}

dmw:updateGangZoneInGameForAll(gangzoneid){
	loopPlayer(playerid){
		dmw_updateGangZoneInGameForPlr(playerid,gangzoneid);
	}
	return true;
}

dmw:updateZoneForAll(){
	loopPlayer(playerid){
		dmw_showGangZoneInGameForPlayer(playerid);
	}
}

dmw_showGangZoneInGameForPlayer(playerid){
	for(new i = 1,j = zone_getZoneMaxID();i <= j;i++){
		dmw_updateGangZoneInGameForPlr(playerid,i);
	}
	
//	new
//		gangid = getPlayerGangID(playerid),
//		gangzoneMaxID = dmw_getMaxGangZoneID(),
//		gangzoneAmount = dmw_getGangZoneAmount();
//	for(new i,tmpstr[MAX_MSG_STR],gangzoneid,gangid;i < gangzoneAmount && i < gangzoneMaxID;i++){
//		format(tmpstr,sizeof(tmpstr),"wl_dmw_zone%d_id",i);
//		if(GetGVarType(tmpstr) != GLOBAL_VARTYPE_NONE){
//			gangzoneid = GetGVarInt(tmpstr);
//			dmw_updateGangZoneInGameForPlr(playerid,gangzoneid);
//		}
//	}
//
	return true;
}
//=======================================================//

dmw:checkPlayerAllowedIn(playerid){
	if(!GetPVarInt(playerid,"wl_plr_logged")){
		return 5;// not logged
	}
	
	if(gang_getPlayerGang(playerid) == INVALID_GANG_ID){
		return 6;// not be admitted as gang member
	}
	
	if(dmw_isPlayerHasGangTag(playerid)){
		if(gang:isTagRegistered(dmw_getPlayerGangTag(playerid))){
			if(dmw_isGangTagInBlackList(dmw_getPlayerGangTag(playerid))){
				return 1;//gang tag ban
			}
			else if(dmw_isNameInBlackList(pName(playerid))){
				return 2;//name ban
			}
			else {
				return 0;//allowed in
			}
		}
		else {
			return 4;//not register gang
		}
	}
	else {
		return 3;//no gang tag
	}
}

dmw:isGangZoneBeingAttacked(zoneid){
	for(new i = 1,j = gang_getGangMaxID();i <= j;i++){
		if(gang_getGangAttackZone(i) == zoneid){
			return true;
		}
	}
	return false;
}

dmw:isZoneAttackedByMultiGang(zoneid){
	for(new i = 1,j = gang_getGangMaxID(),k;i <= j;i++){
		if(gang_getGangAttackZone(i) == zoneid){
			if(++k >= 2){
				return true;
			}
		}
	}
	return false;
}

dmw:updateGangZoneWarState(zoneid){
	for(new i = 1,j = gang_getGangMaxID();i <= j;i++){
		if(gang_getGangAttackZone(i) == zoneid){
			zone_setZoneWarState(zoneid,true);
			//System_sendAll("zone%d in war",zoneid);
			return;
		}
	}
	zone_setZoneWarState(zoneid,false);
	//System_sendAll("zone%d out war",zoneid);
}		

dmw:isPlayerStayEffective(playerid){
	if(GetPVarInt(playerid,"wl_plr_online")){
		if(dmw:getPlayer(playerid) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT || GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER){
			return true;
		}		
	}
	return false;
}


dmw:isPlayerAdminable(playerid){
	if(dmwdmin:getPlayerAdminLevel(playerid) >= 5){
		return true;
	}
	return false;
}







public dmw_attackZoneItterCheck(gangid,zoneid){ debug_public_track("dmw_attackZoneItterCheck(gangid,zoneid){");
	new effective;
	loopPlayer(playerid){
		if(gang:getPlayerGang(playerid) == gangid){
			if(zone_getPlayerZone3DByPosition(playerid) == zoneid){	
				if(dmw_isPlayerStayEffective(playerid)){
					effective = true;
					break;
				}
			}
		}
	}
	if(effective){
		
		if(gang_getGangAttackTime(gangid) > zone:getZoneAttackTime(zoneid)){ // attack successfully
			
			new 
				oldownergangid = zone_getZoneOwner(zoneid),
				attackgangid = gangid,
				defendgangid = oldownergangid;
			//Spawnpoint preset		//=============================//
			new
				attackzoneamount,
				defencezoneamount;
			for(new czoneid = 1,j = zone:getZoneMaxID();czoneid < j;czoneid++){
				if(gang:isOwnedZone(attackgangid,czoneid)){
					attackzoneamount++;
				}
				else if(gang:isOwnedZone(defendgangid,czoneid)){
					defencezoneamount++;
				}
			}
			if(attackzoneamount == 0){ //get spawnpoint
				new
					Float:spx,Float:spy,Float:spz;
				zone:getZoneSpawnPoint(zoneid,spx,spy,spz);
				gang:setGangSpawnPoint(attackgangid,spx,spy,spz);
			}
			if(defencezoneamount == 1){ //lose spawnpoint
				gang:setGangSpawnPoint(defendgangid,0,0,0);
			}
			//=============================//
			zone_setZoneOwner(zoneid,gangid);
			
			for(new i = 1,j = gang_getGangMaxID();i <= j;i++){
				if(gang_getGangAttackZone(i) == zoneid){
					gang_setGangAttackTime(i,0);
					gang_deactiveGangAttackTimer(i);
					gang_setGangAttackZone(i,INVALID_ZONE_ID);
				}
			}
			dmw:attackwin_3DText(defendgangid,zoneid);
			dmw_updateGangZoneWarState(zoneid);
			dmw_updateGangZoneInGameForAll(zoneid);
			dmw_AttackWin_baseDeal(attackgangid,zoneid,defendgangid);
			CallRemoteFunction("OnPlayerGangAttackWin","iii",gangid,zoneid,oldownergangid);	
		}
		else {
			//System_sendAll("time left:%d",30 - gang_getGangAttackTime(gangid));
			dmw:attackupdate_Text3D(gangid,zoneid);
			gang_setGangAttackTime(gangid,gang_getGangAttackTime(gangid)+1);
		}
	}
	else { // stop attack
		gang_setGangAttackTime(gangid,0);
		gang_deactiveGangAttackTimer(gangid);
		gang_setGangAttackZone(gangid,INVALID_GANG_ZONE_ID);
		CallLocalFunction("OnPlayerGangAttackStop","iii",gangid,zoneid,1);//1:no attacker left
	}
}


zcmd(cmd_dmwdmin,playerid,params[]){
	zcmd_advused();
	if(compare("setnamedmwdminlevel",1)){
		if(IsPlayerAdmin(playerid) || dmwdmin:getPlayerAdminLevel(playerid) >= 10){
			if(!isnull(cmd_(2)) && !isnull(cmd_(3)) && !isnull(cmd_(4))){
				new
					userid,
					level = strval(cmd_(4));
				if((IsPlayerAdmin(playerid) && level <= 10) || (dmwdmin:getPlayerAdminLevel(playerid) >= 10 && level <= 9)){
					if(user:isNameRegistered(cmd_(2))){
						userid = user:getUserIDFromName(cmd_(2));
					}
					else {
						user:createUser(cmd_(2),cmd_(3));
						userid = user:getUserMaxID();
					}
					dmwdmin:setUserAdminLevel(userid,level);
					System_send(playerid,"dmwdmin account created, name(%s),password(%s),level(%d)",cmd_(2),cmd_(3),strval(cmd_(4)));
					//writelog("[dmwdmin]account created, name(%s),password(%s),level(%d), operator:%s",cmd_(2),cmd_(3),strval(cmd_(4)),pName(playerid));
				}
				else {
					System_send(playerid,"[dmwdmin]process failed, possible invalid level (should between 1-10)");
				}
			}
			else {
				System_send(playerid,"Command usage: /dmwdmin setnamedmwdminlevel [accountname/playername] [password] [level]");
			}
		}
		else {
			System_send(playerid,"command refused, not RCON admin");
		}
		return true;
	}
	else if(compare("deletegangzone",1)){
		if(dmwdmin:getPlayerAdminLevel(playerid) >= 9){
			new
				zoneid = zone:getPlayerZoneByPosition(playerid);
			if(zoneid != INVALID_ZONE_ID){
				//writelog("[zone]Zone '%s'(%d) deleted, operator:%s",zone:getZoneName(zoneid),zoneid,pName(playerid));
				zone:removeZoneInGame(zoneid);
				dmw:updateZoneForAll();
				System_send(playerid,"zone removed");
			}
			else {
				System_send(playerid,"command failed, not in zone.");
			}
		}
		else {
			System_send(playerid,"command refused, not dmw(>=lv9) admin %d",dmwdmin:getPlayerAdminLevel(playerid) );
		}
		return true;
	}				
	else if(compare("creategangzone",1)){
		if(dmwdmin:getPlayerAdminLevel(playerid) >= 8){
			if(GetGVarInt("wl_zone_creategangzone_times",playerid) == 0){
				new
					Float:px,Float:py,Float:pz;
				GetPlayerPos(playerid,px,py,pz);
				SetGVarFloat("wl_zone_creategangzone_x1",px,playerid);
				SetGVarFloat("wl_zone_creategangzone_y1",py,playerid);
				SetGVarFloat("wl_zone_creategangzone_z1",pz,playerid);
				SetGVarInt("wl_zone_creategangzone_times",1,playerid);
				System_send(playerid,"[ZoneCreate]Step1:logged bound index1, now to take another diagnolpoint.");
			}
			else if(GetGVarInt("wl_zone_creategangzone_times",playerid) == 1){
				new
					Float:px,Float:py,Float:pz;
				GetPlayerPos(playerid,px,py,pz);
				SetGVarFloat("wl_zone_creategangzone_x2",px,playerid);
				SetGVarFloat("wl_zone_creategangzone_y2",py,playerid);
				SetGVarFloat("wl_zone_creategangzone_z2",pz,playerid);
				SetGVarInt("wl_zone_creategangzone_times",2,playerid);
				System_send(playerid,"[ZoneCreate]Step2:logged bound index2, now to take spawnpoint");
			}
			else if(GetGVarInt("wl_zone_creategangzone_times",playerid) == 2){
				if(isnull(cmd_(2))){
					System_send(playerid,"Please input zone name * /creategangzone [gangzone_name] - create a gangzone");
					return true;
				}
				new
					Float:px,Float:py,Float:pz;
				GetPlayerPos(playerid,px,py,pz);
				SetGVarFloat("wl_zone_creategangzone_x3",px,playerid);
				SetGVarFloat("wl_zone_creategangzone_y3",py,playerid);
				SetGVarFloat("wl_zone_creategangzone_z3",pz,playerid);
				SetGVarInt("wl_zone_creategangzone_times",3,playerid);
				SetGVarString("wl_zone_creategangzone_name",cmd_(2),playerid);
				zone:createZoneInGame(playerid);
				
				System_send(playerid,"[ZoneCreate]Step finished.");
			}
		}
		else {
			System_send(playerid,"command refused, not dmw(>=lv8) admin");
		}
	}
	else if(compare("selfdamage",1)){
		if(dmwdmin:getPlayerAdminLevel(playerid) >= 10){
			DMWrold_SelfDamage_Struct();
			System_send(playerid,"selfdamage reloaded");
			
		}
		else {
			System_send(playerid,"command refused, not dmw(lv10) admin");
			return true;
		}
	}
	else if(compare("creategang",1)){
		if(!(dmwdmin:getPlayerAdminLevel(playerid) >= 8)){
			System_send(playerid, "[GANG]Command process cancled, not dmw(>=lv8) admin * /dmwdmin creategang [playerid] - create a gang by specfic player's info");
			return true;
		}
		if(isnull(cmd_(2))){
			System_send(playerid, "[GANG]Please input playerid * /dmwdmin creategang [playerid] - create a gang by specfic player's info");
			return true;
		}
		if(!IsNumeric(cmd_(2))){
			System_send(playerid,"[GANG]Please input a number * /dmwdmin creategang [playerid] - create a gang by specfic player's info");
			return true;
		}
		new
			setplayerid = strval(cmd_(2));
		if(!IsPlayerConnected(setplayerid)){
			System_send(playerid,"[GANG]Please input a connected playerid * /dmwdmin creategang [playerid] - create a gang by specfic player's info");
			return true;
		}
		if(!user:logged(setplayerid)){
			System_send(playerid,"[GANG]The player doesn't login on, it can only set registered player * /dmwdmin creategang [playerid] - create a gang by specfic player's info");
			return true;
		}
		if(!gang:isPlayerHasGangTag(setplayerid)){
			System_send(playerid,"[GANG]The player doesn't tag as a gang member * /dmwdmin creategang [playerid] - create a gang by specfic player's info");
			return true;
		}
		new
			gangtag[MAX_GANG_NAME];
		format(gangtag,sizeof(gangtag),"%s",gang:getPlayerGangTag(setplayerid));
		if(!gang:isLegalTag(gangtag)){
			System_send(playerid,"[GANG]Gangtag invalid, make sure that gangtag can only be grouped by 'a'-'z', 'A'-'Z', '0'-'9', '-' and '.' * /dmwdmin creategang [playerid] - create a gang by specfic player's info");
			return true;
		}
		new
			gangid = gang:getGangByTag(gangtag);
		/*
		if(gangid != INVALID_GANG_ID && !gang:isGangOwnerNull(gangid)){
			System_send(playerid,"[GANG]The gangtag has already registered * /dmwdmin creategang [playerid] - create a gang by specfic player's info");
			return true;
		}
		*/
		/*
		gang:createGangInDatabase(gangtag,pName(setplayerid));
		new
			gangid = gang:getGangMaxID();
		gang:setGangRelation(gangid,gangid,gang_relation_alliance);		
		*/
		gang:setPlayerGang(setplayerid,gangid);
		gang:setPlayerInGangLevel(setplayerid,10);
		gang:setGangOwner(gangid,pName(setplayerid));
		//writelog("[gang]Gang '%s'(%d) created, owner:%s  |  operator:%s",gangtag,gangid,pName(setplayerid),pName(playerid));
		System_send(playerid,"[GANG]Gang '%s' created, owner:%s",gangtag,pName(setplayerid));
		System_send(setplayerid,"[GANG]You are now the owner of gang '%s'(operator:%s), please type '/gang help' to display a list of commands you may use.",gangtag,pName(playerid));
		return true;
	}
	else if(compare("setzoneattacktime",1)){
		if(!(dmwdmin:getPlayerAdminLevel(playerid) >= 8)){
			System_send(playerid, "[ZONE]Command process cancled, not dmw(>=lv8) admin * /dmwdmin setzoneattacktime [time] - set current zone attack time");
			return true;
		}
		if(zone:getPlayerZoneByPosition(playerid) == INVALID_ZONE_ID){
			System_send(playerid,"[ZONE]Please stand in a zone area.");
			return true;
		}
		new
			time = strval(cmd_(2));
		if(time <= 0){
			System_send(playerid,"[ZONE]Zone attack time set failed, invalid input");
			System_send(playerid,"[ZONE]/dmwdmin setzoneattacktime [attacktime] - set current zone attack time");
			return true;
		}
		zone:setZoneAttackTime(zone:getPlayerZoneByPosition(playerid),time);
		System_send(playerid,"[ZONE]Zone attack time set to %d seconds",time);
	}
	else if(compare("help",1)){
		System_send(playerid,"====dmwdmin command help====");
		System_send(playerid,"(RCON/LV10)/dmwdmin setnamedmwdminlevel [accountname/playername] [password] [level]- create/set a dmwdmin account");
		System_send(playerid,"(LV8)/dmwdmin creategangzone [gangzone_name] - create a gangzone(take diagnolpoints, spawnpoint)");
		System_send(playerid,"(LV9)/dmwdmin deletegangzone - delete the gangzone on which you are standing.");
		System_send(playerid,"(LV8)/dmwdmin setzoneattacktime [attacktime] - set current zone attack time.");
		System_send(playerid,"(LV8)/dmwdmin creategang [playerid] - create a gang by specfic player's info");
		System_send(playerid,"(LV10)/dmwdmin selfdamage - reload selfdamage.cfg, debug command.");
		System_send(playerid,"(LV5)/dmwdmin open - allow to enter dmworld");
		System_send(playerid,"(LV5)/dmwdmin close - disallow to enter dmworld");
		System_send(playerid,"(LV5)/dmwdmin bantag - disallow specfic [tag] into dmworld");
		System_send(playerid,"(LV5)/dmwdmin banplayergang - disallow specfic gang into dmworld");
		System_send(playerid,"(LV5)/dmwdmin banplayer - disallow specfic player into dmworld");
		System_send(playerid,"============================");
		return true;
	}
		
	/*
	else if(compare("setgangadminlevel",1)){
		if(dmwdmin:getPlayerAdminLevel(playerid) >= 10){
			if(!isnull(cmd_(2))){
				if(IsNumeric(cmd_(2))){
					new
						setid = strval(cmd_(2));
					if(IsPlayerConnected(setid)){
						if(user:logged(setid)){
							if(gang:getPlayerGang(setid) != INVALID_GANG_ID){
								if(!isnull(cmd_(3))){
									if(IsNumeric(cmd_(3))){
										new
											level = strval(cmd_(3));
										if(level >= 0 && level <= 10){
											gang:setPlayerInGangLevel(setid,level);
											gang:send(playerid,"cmd_dmwdmin_setgangadminlevel_pass_1",pName(setid),level);
											gang:send(setid,"cmd_dmwdmin_setgangadminlevel_pass_2",pName(playerid),level);
										}
										else {
											gang:send(playerid,"cmd_dmwdmin_setgangadminlevel_denied_limit_level");
										}
									}
									else {
										gang:send(playerid,"cmd_dmwdmin_setgangadminlevel_denied_invalid_level");
									}
								}
								else {
									gang:send(playerid,"cmd_dmwdmin_setgangadminlevel_denied_notinput_level");
									gang:send(playerid,"cmd_dmwdmin_setgangadminlevel_help");
								}
							}
							else {
								gang:send(playerid,"cmd_dmwdmin_setgangadminlevel_denied_notregisteredgangmember");
							}
						}
						else {
							gang:send(playerid,"cmd_dmwdmin_setgangadminlevel_denied_notlogged");
						}
					}
					else {
						gang:send(playerid,"cmd_dmwdmin_setgangadminlevel_denied_notconnected");		
					}
				}
				else {
					gang:send(playerid,"cmd_dmwdmin_setgangadminlevel_denied_id_invalidinput");
				}
			}
			else {
				gang:send(playerid,"cmd_dmwdmin_setgangadminlevel_denied_id_notinput");
				gang:send(playerid,"cmd_dmwdmin_setgangadminlevel_help");
			}
		}
		else {
			gang:send(playerid,"cmd_dmwdmin_setgangadminlevel_nopower");
		}
	}
	*/
	else if(dmw_isPlayerAdminable(playerid)){
		if(compare("bantag",1)){
			if(isnull(cmd_(2))){
				dmw_send(playerid,WL_LANG_DMW_ADMIN_CMD_BANTAG_USAGE);
			}
			else if(dmw_isLegalTag(cmd_(2))){
				if(dmw_isGangTagInBlackList(cmd_(2))){
					dmw_send(playerid,WL_LANG_DMW_ADMIN_CMD_BANTAG_FAILED_ALREADYBANNED,cmd_(2));
				}
				else {
					dmw_setGangTagInBlackList(cmd_(2));
					dmw_send(playerid,WL_LANG_DMW_ADMIN_CMD_BANTAG_SUCCEED,cmd_(2));
				}
			}
			else {
				dmw_send(playerid,WL_LANG_DMW_ADMIN_CMD_BANTAG_FAILED_ILLEAGLTAG,cmd_(2));
			}
		}
		else if(compare("banplayergang",1)){
			if(isnull(cmd_(2))){
				dmw_send(playerid,WL_LANG_DMW_ADMIN_CMD_BANPLAYERGANG_USAGE);
			}
			else if(IsNumeric(cmd_(2))){
				new
					banplayerid = strval(cmd_(2));
				if(IsPlayerConnected(banplayerid)){
					if(gang:getPlayerGang(banplayerid) != INVALID_GANG_ID){
						dmw_disallowGang(gang:getPlayerGang(banplayerid));
						dmw_send(playerid,WL_LANG_DMW_ADMIN_CMD_BANPLAYERGANG_SUCCEED,pName(banplayerid),banplayerid,gang:getGangName(gang:getPlayerGang(banplayerid)));
					}
					else {
						dmw_send(playerid,WL_LANG_DMW_ADMIN_CMD_BANPLAYERGANG_FAILED_NOTGANGMEMBER);
					}
				}
				else {
					dmw_send(playerid,WL_LANG_DMW_ADMIN_CMD_BANPLAYERGANG_FAILED_NOTCONNECTED);
				}
			}
			else {
				dmw_send(playerid,WL_LANG_DMW_ADMIN_CMD_BANPLAYERGANG_USAGE);
			}
		}
		else if(compare("banplayer",1)){
			if(isnull(cmd_(2))){
				dmw_send(playerid,WL_LANG_DMW_ADMIN_CMD_BANPLAYER_USAGE);
			}
			else if(IsNumeric(cmd_(2))){
				new
					banplayerid = strval(cmd_(2));
				if(IsPlayerConnected(banplayerid)){
					dmw_disallowPlayer(banplayerid);
					dmw_send(playerid,WL_LANG_DMW_ADMIN_CMD_BANPLAYER_SUCCEED,pName(banplayerid),banplayerid);
				}
				else {
					dmw_send(playerid,WL_LANG_DMW_ADMIN_CMD_BANPLAYER_FAILED);
				}
			}
			else {
				dmw_send(playerid,WL_LANG_DMW_ADMIN_CMD_BANPLAYER_USAGE);
			}
		}
		/*
		else if(compare("open",1)){
			SetGVarInt("wl_dmw_admission",true);
			dmw_send(playerid,WL_LANG_DMW_DMW_ADMISSION_OPEN);
		}
		else if(compare("close",1)){
			SetGVarInt("wl_dmw_admission",false);
			loopPlayer(pid){
				if(dmw:getPlayer(pid)){
					dmw:setPlayerOut(pid);
					System_send(playerid,"[大战城]大战城被强制关闭了");
				}
			}
			dmw_send(playerid,WL_LANG_DMW_DMW_ADMISSION_CLOSE);
		}
		*/
		else {
			dmw_send(playerid,WL_LANG_DMW_UNKNOWNCMD,params);
		}
	}	
	return true;
}
pzcmd(dmwdmin){ rzcmd(cmd_dmwdmin);}			
						
	
zcmd(cmd_gang,playerid,params[]){
	zcmd_advused();
	if(isnull(cmd_(1))){
		gang:send(playerid,"cmd_gang_help");
		return true;
	}
	if(gang:getPlayerGang(playerid) == INVALID_GANG_ID){
		gang:send(playerid,"cmd_gang_notin");
		return true;
	}
	if(compare("addmember",1)){
		if(gang:getPlayerInGangLevel(playerid) >= 5){
			if(isnull(cmd_(2))){
				gang:send(playerid,"cmd_gang_addmember_noinput");
				gang:send(playerid,"cmd_gang_addmember_help");
			}
			else if(IsNumeric(cmd_(2))){
				new
					member = strval(cmd_(2));
				if(IsPlayerConnected(member)){
					if(user:logged(member)){
						/*
						if(gang:getPlayerGang(member) == INVALID_GANG_ID){
						*/
							if(!strcmp(gang:getPlayerGangTag(member),gang:getPlayerGangTag(playerid))){
								gang:setPlayerGang(member,gang:getPlayerGang(playerid));
								gang:sendgang(gang:getPlayerGang(playerid),"cmd_gang_addmember_pass_1",pName(member));
								gang:send(playerid,"cmd_gang_addmember_pass_2",gang:getGangName(gang:getPlayerGang(playerid)));
							}
							else {
								gang:send(playerid,"cmd_gang_addmember_denied_notsamegangtag",pName(member));
							}
						/*	
						}
						
						else {
							gang:send(playerid,"cmd_gang_addmember_denied_notsameggang",pName(member));
						}
						*/
					}
					else {
						gang:send(playerid,"cmd_gang_addmember_denied_notlogged",pName(member));
					}
				}
				else {
					gang:send(playerid,"cmd_gang_addmember_denied_notconnected");
				}
			}
			else {
				gang:send(playerid,"cmd_gang_addmember_denied_invalidid");
			}
		}
		else {
			gang:send(playerid,"cmd_gang_addmember_denied_nopower");
		}
	}
	else if(compare("setlevel",1)){
		if(gang:getPlayerInGangLevel(playerid) >= 10){
			if(isnull(cmd_(2))){
				gang:send(playerid,"cmd_gang_setlevel_denied_noinput");
				gang:send(playerid,"cmd_gang_setlevel_help");
			}
			else if(IsNumeric(cmd_(2))){
				new
					member = strval(cmd_(2));
				if(IsPlayerConnected(member)){
					if(user:logged(member)){
						if(gang:getPlayerGang(member) == gang:getPlayerGang(playerid)){
							if(!isnull(cmd_(3))){
								new
									level = strval(cmd_(3));
								if(level >= 0 && level <=10){
									gang:setPlayerInGangLevel(member,level);
									gang:send(playerid,"cmd_gang_setlevel_pass_ermsg",pName(member),level);
									gang:send(member,"cmd_gang_setlevel_pass_eemsg",pName(playerid),level);
									gang:sendgang(gang:getPlayerGang(playerid),"cmd_gang_setlevel_pass_elsemsg",pName(playerid),pName(member),level);
								}
								else {
									gang:send(playerid,"cmd_gang_setlevel_denied_level_limit");
								}
							}
							else {
								gang:send(playerid,"cmd_gang_setlevel_denied_notinput_level");
								gang:send(playerid,"cmd_gang_setlevel_help");
							}
						}
						else {
							gang:send(playerid,"cmd_gang_setlevel_denied_notsamegang");
						}
					}
					else {
						gang:send(playerid,"cmd_gang_setlevel_denied_notlogged");
					}
				}
				else {
					gang:send(playerid,"cmd_gang_setlevel_denied_notconnected");
				}
			}
			else {
				gang:send(playerid,"cmd_gang_setlevel_denied_notinput_id");
				gang:send(playerid,"cmd_gang_setlevel_help");
			}
		}
		else {
			gang:send(playerid,"cmd_gang_setlevel_denied_nopower");
		}
	}
	else if(compare("setrelation",1)){
		if(gang:getPlayerInGangLevel(playerid) >= 5){
			new
				gangid = zone:getZoneOwner(zone:getPlayerZoneByPosition(playerid));
			if(gangid != INVALID_GANG_ID){
				if(gangid != gang:getPlayerGang(playerid)){
					if(!isnull(cmd_(2))){
						if(IsNumeric(cmd_(2))){
							new
								relation = strval(cmd_(2))-1;
							if(relation >= 0 && relation <= 2){
								gang:setGangRelation(gang:getPlayerGang(playerid),gangid,relation);
								dmw:updateZoneForAll();
								switch(relation){
									case gang_relation_neutral: {
										gang:send(playerid,"cmd_gang_setrelation_pass_neutral_self",gang:getGangName(gangid));
										gang:sendgang(gang:getPlayerGang(playerid),"cmd_gang_setrelation_pass_neutral_selfgang",pName(playerid),gang:getGangName(gangid));
										gang:sendgang(gangid,"cmd_gang_setrelation_pass_neutral_setgang",gang:getGangName(gang:getPlayerGang(playerid)));
									}
									case gang_relation_hostilit: {
										gang:send(playerid,"cmd_gang_setrelation_pass_hostilit",gang:getGangName(gangid));
										gang:sendgang(gang:getPlayerGang(playerid),"cmd_gang_setrelation_pass_hostilit_selfgang",pName(playerid),gang:getGangName(gangid));
										gang:sendgang(gangid,"cmd_gang_setrelation_pass_hostilit_setgang",gang:getGangName(gang:getPlayerGang(playerid)));
									}
									case gang_relation_alliance: {
										gang:send(playerid,"cmd_gang_setrelation_pass_alliance",gang:getGangName(gangid));
										gang:sendgang(gang:getPlayerGang(playerid),"cmd_gang_setrelation_pass_alliance_selfgang",pName(playerid),gang:getGangName(gangid));
										gang:sendgang(gangid,"cmd_gang_setrelation_pass_alliance_setgang",gang:getGangName(gang:getPlayerGang(playerid)));
									}
								}
							}
							else {
								gang:send(playerid,"cmd_gang_setrelation_denied_relation_limit");
								gang:send(playerid,"cmd_gang_setrelation_help");
							}
						}
						else { 
							gang:send(playerid,"cmd_gang_setrelation_denied_relation_invalid");
							gang:send(playerid,"cmd_gang_setrelation_help");
						}
					}
					else {
						gang:send(playerid,"cmd_gang_setrelation_denied_relation_notinput");
						gang:send(playerid,"cmd_gang_setrelation_help");
					}
				}
				else {
					gang:send(playerid,"cmd_gang_setrelation_denied_zone_samegang");
				}
			}
			else {
				gang:send(playerid,"cmd_gang_setrelation_denied_zone_nogang");				
			}
		}
		else {
			gang:send(playerid,"cmd_gang_setrelation_denied");
		}
	}
	else if(compare("help",1)){
		gang:send(playerid,"cmd_gang_help_1");
		gang:send(playerid,"cmd_gang_addmember_help");
		gang:send(playerid,"cmd_gang_setlevel_help");
		gang:send(playerid,"cmd_gang_setrelation_help");
		gang:send(playerid,"cmd_dmw_attack_help");
		gang:send(playerid,"cmd_dmw_retreat_help");
		gang:send(playerid,"cmd_gang_help_2");
	}
	else {
		gang:send(playerid,"cmd_gang_nosuchcmd",params);
	}
	return true;
}
pzcmd(gang){ rzcmd(cmd_gang);}
//todo
forward dmw:enterDMWDelay(playerid);
public dmw:enterDMWDelay(playerid){ debug_public_track("dmw:enterDMWDelay(playerid){");
	dmw_setPlayer(playerid,true);	
	dmw:playerSpawn(playerid);
	
}

zcmd(cmd_dmworld,playerid,params[]){
	zcmd_advused();
	if(isnull(cmd_(1))){
		dmw:send(playerid,"cmd_dmw_help_1");
		dmw:send(playerid,"cmd_dmw_enter_help");
		dmw:send(playerid,"cmd_dmw_exit_help");
		dmw:send(playerid,"cmd_dmw_attack_help");
		dmw:send(playerid,"cmd_dmw_retreat_help");	
		dmw:send(playerid,"cmd_dmw_buyweapon_help");
		dmw:send(playerid,"cmd_dmw_help_2");
		//DMWorld_showPlayerMainHelp(playerid);
	}
	else if(compare("jinru",1) || compare("enter",1) || compare("in",1)){
		dmw:activeAutoOpen();
		/*
		if(!GetGVarInt("wl_dmw_admission")){
			dmw_send(playerid,WL_LANG_DMW_DMW_HASBENN_CLOSED);
			return true;
		}
		*/
		if(dmw_getPlayer(playerid)){
			dmw_send(playerid,WL_LANG_DMW_ENTER_DNIED_ALREADYIN);
		}
		else {
			switch(dmw:checkPlayerAllowedIn(playerid)){
				case 0,3,4,5,6:{ //allowed
					ResetPlayerWeapons(playerid);
					dmw_setPlayerToGangSpawn(playerid);
					SetTimerEx("dmw_enterDMWDelay",1000+GetPlayerPing(playerid)*2,false,"i",playerid);
					dmw_send(playerid,WL_LANG_DMW_ENTER_1);
					dmw_send(playerid,WL_LANG_DMW_ENTER_2);
				//	dmw_send(playerid,WL_LANG_DMW_ENTER_SPAWNGANG,dmw_getPlrGangOrginalZoneName(playerid));
				}
				case 1:{ //gang tag ban
					dmw_send(playerid,WL_LANG_DMW_ENTER_DENIED_GANGTAGBAN_1);
					dmw_send(playerid,WL_LANG_DMW_ENTER_DENIED_GANGTAGBAN_2);
				}
				case 2:{ //name ban
					dmw_send(playerid,WL_LANG_DMW_ENTER_DENIED_NAMEBAN_1);
					dmw_send(playerid,WL_LANG_DMW_ENTER_DENIED_NAMEBAN_2);
				}
				/*
				case 3:{ //not gang tag
					dmw_send(playerid,WL_LANG_DMW_ENTER_DENIED_NOTEAM);
				}
				case 4:{ //not register gang
					dmw_send(playerid,WL_LANG_DMW_GANGREGISTER_HINT,dmw_getPlayerGangTag(playerid));
				}
				case 5:{ //plr not logged
					dmw_send(playerid,WL_LANG_DMW_ENTER_DENIED_NOT_LOGGED);
				}
				
				case 6:{ //not be adminted as current gang member
					dmw_send(playerid,WL_LANG_DMW_ENTER_DENIED_NOT_REGISTERED_GANG_MEMBER);
				}
				*/
				
			}
		}
	}
	else if(compare("buyweapon",1) || compare("gun",1)){
		dmwweapon:Command_ShowDialog(playerid);
	}
	else if(compare("buyvehicle",1) || compare("car",1)){
		dmwvehicle:Command_ShowDialog(playerid);
	}
	else if(compare("likai",1) || compare("leave",1) || compare("exit",1) || compare("out",1)){
		if(dmw_getPlayer(playerid)){
			dmw_setPlayerOut(playerid);
			dmw_send(playerid,WL_LANG_DMW_EXIT_1);
		}
		else {
			dmw_send(playerid,WL_LANG_DMW_EXIT_DENIED_NOTINT);
		}
	}
	else if(compare("attack",1) || compare("jingong",1)){
		dmw:activeAutoOpen();
		if(!GetGVarInt("wl_dmw_admission")){
			dmw_send(playerid,WL_LANG_DMW_DMW_HASBENN_CLOSED);
			return true;
		}
		if(!dmw_getPlayer(playerid)){
			dmw_send(playerid,"cmd_dmw_attack_denied_notindmw");
			return true;
		}
		if(gang:isGangOwnerNull(gang:getPlayerGang(playerid))){
			new
				zoneid = zone_getPlayerZoneByPosition(playerid);
			if(zoneid == INVALID_GANG_ZONE_ID){
				dmw_send(playerid,WL_LANG_DMW_UNABLEATTACK_NOTINZONE);
			}
			else if(zone_getZoneOwner(zoneid) == gang_getPlayerGang(playerid)){
				dmw_send(playerid,WL_LANG_DMW_UNABLEATTACK_SELFZONE);
			}
			else if(dmw:isGangZoneBeingAttacked(zoneid)){
				dmw:send(playerid,"dmw_attack_start_denied_zoneinwar");
			}
			else {
				gang:setGangAttackZone(gang:getPlayerGang(playerid),zoneid);
				gang:activeGangAttckTimer(gang:getPlayerGang(playerid));
				zone:setZoneWarState(zoneid,true);
				CallLocalFunction("OnPlayerGangAttackStart","ii",gang_getPlayerGang(playerid),zoneid);
			}
		}
		else if(gang_getPlayerInGangLevel(playerid) >= 5){ 
			if(gang_isPlayerGangAttacking(playerid)){
				dmw_send(playerid,WL_LANG_DMW_UNABLEATTACK_ATTACKINGANOTHERZONE);
			}
			else {
				new
					zoneid = zone_getPlayerZoneByPosition(playerid);
				if(zoneid == INVALID_GANG_ZONE_ID){
					dmw_send(playerid,WL_LANG_DMW_UNABLEATTACK_NOTINZONE);
				}
				else if(zone_getZoneOwner(zoneid) == gang_getPlayerGang(playerid)){
					dmw_send(playerid,WL_LANG_DMW_UNABLEATTACK_SELFZONE);
				}
				else if(dmw:isGangZoneBeingAttacked(zoneid)){
					dmw:send(playerid,"dmw_attack_start_denied_zoneinwar");
				}
				else {
					gang:setGangAttackZone(gang:getPlayerGang(playerid),zoneid);
					gang:activeGangAttckTimer(gang:getPlayerGang(playerid));
					zone:setZoneWarState(zoneid,true);
					CallLocalFunction("OnPlayerGangAttackStart","ii",gang_getPlayerGang(playerid),zoneid);
				}
			}
		}
		else {
			dmw_send(playerid,WL_LANG_DMW_UNABLEATTACK_NOTOWNER);
		}
	}
	else if(compare("stopattack",1) || compare("chetui",1) || compare("retreat",1)){
		if(!dmw_getPlayer(playerid)){
			dmw_send(playerid,"cmd_dmw_retreat_denied_notindmw");
			return true;
		}
		if(gang_getPlayerInGangLevel(playerid) >= 5){
			if(gang_isPlayerGangAttacking(playerid)){
				new
					gangid = gang_getPlayerGang(playerid),
					attackzoneid = gang_getGangAttackZone(gangid);
				zone:setZoneWarState(attackzoneid,false);
				gang_setGangAttackTime(gangid,0);
				gang_deactiveGangAttackTimer(gangid);
				gang_setGangAttackZone(gangid,INVALID_GANG_ZONE_ID);
				CallLocalFunction("OnPlayerGangAttackStop","iii",gangid,attackzoneid,2);
			}
			else {
				dmw_send(playerid,WL_LANG_DMW_ATTACKSTOP_RETREAT_NOTATTACKING_1);
				dmw_send(playerid,WL_LANG_DMW_ATTACKSTOP_RETREAT_NOTATTACKING_2);
			}
		}
		else {
			dmw_send(playerid,WL_LANG_DMW_ATTACKSTOP_NOTOWNER);
		}		
	}
	else if(compare("help",1)){
		dmw:send(playerid,"cmd_dmw_help_1");
		dmw:send(playerid,"cmd_dmw_enter_help");
		dmw:send(playerid,"cmd_dmw_exit_help");
		dmw:send(playerid,"cmd_dmw_attack_help");
		dmw:send(playerid,"cmd_dmw_retreat_help");		
		dmw:send(playerid,"cmd_dmw_help_2");
	}
	else {
		dmw_send(playerid,WL_LANG_DMW_UNKNOWNCMD,params);
	}
	return true;
}
pzcmd(dmw){ rzcmd(cmd_dmworld);}

dmw:AttackStart_baseDeal(gangid,zoneid){
	dmw:sendAll("dmw_attack_start_announe",gang:getGangName(gangid),gang:getGangName(zone:getZoneOwner(zoneid)),zone:getZoneName(zoneid));
}

dmw:AttackWin_baseDeal(attackgangid,zoneid,defendgangid){
		new
			zonename[MAX_GANG_ZONE_NAME],
			attackgangname[MAX_GANG_NAME],
			defendgangname[MAX_GANG_NAME];
		format(zonename,sizeof(zonename),"%s",zone:getZoneName(zoneid));
		format(attackgangname,sizeof(attackgangname),"%s",gang:getGangName(attackgangid));
		format(defendgangname,sizeof(defendgangname),"%s",gang:getGangName(defendgangid));
	if(defendgangid != INVALID_GANG_ID){
		loopPlayer(playerid){
			new
				playergangid = gang:getPlayerGang(playerid);
			if(playergangid == defendgangid){
				dmw_send(playerid,WL_LANG_DMW_GANGDEFNCE_FAILED,zonename,attackgangname);
			}
			else if(playergangid == attackgangid){
				dmw_send(playerid,WL_LANG_DMW_GANGATTACK_SUCCEED,defendgangname,zonename);
			}
			else if(playergangid != INVALID_GANG_ID){
				dmw_send(playerid,WL_LANG_DMW_ZONECAPTURED_ANNOUNEMENT,defendgangname,zonename,attackgangname);
			}
		}
	}
	dmw_sendAll("dmw_attackwin_noowner_zone_announce",attackgangname,zonename);
}

dmw:AttackStop_baseDeal(gangid,zoneid,reasoncode){
	switch(reasoncode){
		case 1:{ //no attacker left
			dmw_sendAll(WL_LANG_DMW_ATTACKSTOP_NOATTACKLEFT,gang:getGangName(gangid),zone:getZoneName(zoneid));
		}
		case 2:{ //retreat
			dmw_sendAll(WL_LANG_DMW_ATTACKSTOP_RETREAT,gang:getGangName(gangid),zone:getZoneName(zoneid));
		}
	}
}

public OnPlayerGangAttackStart(gangid,zoneid){ debug_public_track("OnPlayerGangAttackStart(gangid,zoneid){");
	dmw_updateGangZoneWarState(zoneid);
	//dmw:updateZoneForAll();
	dmw_updateGangZoneInGameForAll(zoneid);
	dmw:attackstart_3DText(gangid,zoneid);

	dmw_AttackStart_baseDeal(gangid,zoneid);
	return true;
}


				
public OnPlayerGangAttackStop(gangid,zoneid,reasoncode){ debug_public_track("OnPlayerGangAttackStop(gangid,zoneid,reasoncode){");
	dmw_updateGangZoneWarState(zoneid);
	//dmw:updateZoneForAll()
	dmw_updateGangZoneInGameForAll(zoneid);
	dmw:attackstop_3DText(gangid,zoneid);
	dmw_AttackStop_baseDeal(gangid,zoneid,reasoncode);
	return true;
}
/*
public OnPlayerGangAttackWin(attackgangid,zoneid,defendgangid){ debug_public_track("OnPlayerGangAttackWin(attackgangid,zoneid,defendgangid){");
	new
		attackzoneamount,
		defencezoneamount;
	
	//if(zone:getOwnedGang(zoneid) != INVALID_GANG_ID){
		for(new czoneid = 1,j = zone:getZoneMaxID();czoneid < j;czoneid++){
			if(gang:isOwnedZone(attackgangid,czoneid)){
				attackzoneamount++;
			}
			else if(gang:isOwnedZone(defendgangid,czoneid)){
				defencezoneamount++;
			}
		}
	//}
	
		
	if(attackzoneamount == 0){ //get spawnpoint
		new
			Float:spx,Float:spy,Float:spz;
		zone:getZoneSpawnPoint(zoneid,spx,spy,spz);
		gang:setGangSpawnPoint(attackgangid,spx,spy,spz);
	}
	if(defencezoneamount == 1){ //lose spawnpoint
		gang:setGangSpawnPoint(defendgangid,0,0,0);
	}
	dmw:attackwin_3DText(defendgangid,zoneid);
	dmw_updateGangZoneWarState(zoneid);
	dmw_updateGangZoneInGameForAll(zoneid);
	dmw_AttackWin_baseDeal(attackgangid,zoneid,defendgangid);
	return true;
}
*/

public dmw_OnPlayerDisallowedIn(playerid){ debug_public_track("dmw_OnPlayerDisallowedIn(playerid){");
	dmw_send(playerid,WL_LANG_DMW_NOT_ALLOWED_IN);
	dmw_setPlayerOut(playerid);
	return true;
}

public dmw_OnPlayerAllowedIn(playerid){ debug_public_track("dmw_OnPlayerAllowedIn(playerid){");
	dmw_send(playerid,WL_LANG_DMW_ALLOWED_IN);
	return true;
}



public dmw_OnPlayerEnterGangZone(playerid,gangzoneid){ debug_public_track("dmw_OnPlayerEnterGangZone(playerid,gangzoneid){");
	dmw:textdraw_enterZone(playerid,gangzoneid);
	//new
	//	gangid = zone:getZoneOwner(gangzoneid);
	//System_send(playerid,"plr(%d) enter gangzone'%s(%d,%d)' ownergang:%s(%d) owner(%s)",playerid,zone:getZoneName(gangzoneid),gangzoneid,zone:getZoneIngameID(gangzoneid),gang:getGangName(gangid),gangid,gang:getGangOwner(gangid));
	return true;
}

public dmw_OnPlayerLeaveGangZone(playerid,gangzoneid){ debug_public_track("dmw_OnPlayerLeaveGangZone(playerid,gangzoneid){");
	dmw:textdraw_leaveZone(playerid);
	//new
	//	gangid = zone:getZoneOwner(gangzoneid);
	//System_send(playerid,"plr(%d) leave gangzone'%s(%d,%d)' ownergang:%s(%d) owner(%s)",playerid,zone:getZoneName(gangzoneid),gangzoneid,zone:getZoneIngameID(gangzoneid),gang:getGangName(gangid),gangid,gang:getGangOwner(gangid));
	return true;
}


public dmw_plrGangZone_ItterCheck(){ debug_public_track("dmw_plrGangZone_ItterCheck(){");
	loopPlayer(playerid){
		new
			newzoneid = zone:getPlayerZoneByPosition(playerid),
			oldzoneid = GetPVarInt(playerid,"dmw_plr_oldzone");
		if(oldzoneid != newzoneid){ // to different zone 
			if(oldzoneid != INVALID_GANG_ZONE_ID && newzoneid != INVALID_GANG_ZONE_ID){
				CallLocalFunction("dmw_OnPlayerLeaveGangZone","ii",playerid,oldzoneid);
			}
			if(newzoneid == INVALID_GANG_ZONE_ID){ //outzone
				CallLocalFunction("dmw_OnPlayerLeaveGangZone","ii",playerid,oldzoneid);
			}			
			else { //enterzone
				CallLocalFunction("dmw_OnPlayerEnterGangZone","ii",playerid,newzoneid);
			}
		}
		SetPVarInt(playerid,"dmw_plr_oldzone",newzoneid);
	}
}


public dmw_plrPositionProcess(){ debug_public_track("dmw_plrPositionProcess(){");
	loopPlayer(playerid){
		if(dmw:getPlayer(playerid)){
			if(dmw_isPlayerStayEffective(playerid)){
				new
					zoneid = zone:getPlayerZoneByPosition(playerid),
					gangid = gang:getPlayerGang(playerid);
				if(zoneid != INVALID_ZONE_ID && gangid != INVALID_GANG_ID){
					new
						zonegangid = zone:getOwnedGang(zoneid);
					//System_send(playerid,"hp++?pgang:%d,zonegang:%d (relation:%d,%d)",gangid,zonegangid,gang:getGangRelation(zonegangid,gangid),gang:getGangRelation(gangid,zonegangid));
					if(gang:getGangRelation(zonegangid,gangid) == gang_relation_alliance && gang:getGangRelation(gangid,zonegangid) == gang_relation_alliance){
						if(pHealth(playerid) <= 97){
							SetPlayerHealth(playerid,pHealth(playerid) + 3);
						}
						//System_send(playerid,"hp++");
					}
				}
			}
		}
	}
}

public OnGangdmwScoreChange(gangid,oldscore,newscore){ debug_public_track("OnGangdmwScoreChange(gangid,oldscore,newscore){");
	dmwscore:OnGangdmwScoreChange(gangid,oldscore,newscore);
	return true;
}



dmw:struct(){
	db_dmworld = db_open("wl/DMWorld/dmworld.db");
	SetTimer("DMWorld_countHP",2001,true);//
	SetTimer("DMWorld_countByKeyState",53,true);//
	SetTimer("dmw_plrGangZone_ItterCheck",1010,true);//
	SetTimer("dmw_plrPositionProcess",5002,true);//
	
	DMWrold_SelfDamage_Struct();
	dmwdmin:struct();
	dmw_blacklist_struct();
	dmw:autoOpen_struct();
	gang:struct();
	zone:struct();
	
	dmwscore:struct();
	dmwweapon:struct();
	dmwvehicle:struct();
}



dmw:playerConnect(playerid){
	dmw:setPlayer(playerid,false);
	dmw:blacklist_Player_connect(playerid);
	gang:playerConnect(playerid);
	zone:Playerconnect(playerid);
	dmwweapon:cache_playerConnect(playerid);
	dmw:textdraw_playerConnect(playerid);
}

dmw:playerDisconnect(playerid){
	dmw:setPlayer(playerid,false);
	dmwweapon:cache_playerDisconnect(playerid);
	dmw:textdraw_playerDisconnect(playerid);

}

dmw:playerLogin(playerid){
	gang:playerLogin(playerid);
	zone:playerLogin(playerid);
	dmwscore:playerLogin(playerid);
}

dmw:playerSpawn(playerid){
	if(dmw:getPlayer(playerid)){
		dmw_setPlayerIn(playerid);
		dmwweapon:cache_playerSpawn(playerid);
		dmwweapon:cache_set(playerid,WEAPON_DEAGLE,7 * 14);
		dmwweapon:cache_set(playerid,WEAPON_SHOTGUN,30);
		dmwweapon:cache_set(playerid,WEAPON_AK47,60 * 8);
		dmwweapon:cache_set(playerid,WEAPON_PARACHUTE,1);
		dmwweapon:cache_set(playerid,WEAPON_MP5,30 * 8);
		ResetPlayerWeapons(playerid);
		GivePlayerWeapon(playerid,WEAPON_DEAGLE,7 * 14);
		GivePlayerWeapon(playerid,WEAPON_SHOTGUN,30);
		GivePlayerWeapon(playerid,WEAPON_AK47,60 * 8);
		GivePlayerWeapon(playerid,WEAPON_PARACHUTE,1);
		GivePlayerWeapon(playerid,WEAPON_MP5,30 * 8);
		
		return true;
	}
	return false;
}

dmw:playerDeath(playerid,killerid,reason){
	#pragma unused reason
	dmwweapon:cache_playerDeath(playerid);
	dmwscore:playerDeath(playerid,killerid);
}

dmw:DialogResponse(playerid,dialogid,response,listitem){
	dmwweapon:DialogResponse(playerid,dialogid,response,listitem);
	dmwvehicle:DialogResponse(playerid,dialogid,response,listitem);
}

dmw:VehicleDeath(vehicleid){
	dmwvehicle:VehicleDeath(vehicleid);
}












#else

dmw_struct({Float,_}:...){}
dmw_playerConnect({Float,_}:...){}
dmw_playerDisconnect({Float,_}:...){}
dmw_playerDeath({Float,_}:...){}
gang_playerText({Float,_}:...){return true;}
dmw_DialogResponse({Float,_}:...){}
dmw_getPlayer({Float,_}:...){}
dmw_VehicleDeath({Float,_}:...){}
dmw_playerSpawn({Float,_}:...){}
dmw_playerLogin({Float,_}:...){}


#endif







