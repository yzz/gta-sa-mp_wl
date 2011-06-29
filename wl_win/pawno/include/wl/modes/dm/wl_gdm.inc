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


#define DEBUG_GDM				(false)
#define COLOR_GDM				(COLOR_LIGHTBLUE)
#define GDM_WORLD				(2)

forward GDM_setPlayeroutGDM(playerid);
forward GDM_setPlayertoGDM(playerid);

#define GDM_send(%1,%2,%3) \
do{\
	new \
		sendfstring[MAX_STRING];\
	format(sendfstring,MAX_STRING,(%2),%3);\
	SendClientMessage((%1),COLOR_GDM,sendfstring);\
}while(FALSE)

stock GDM_send(playerid,const sendfstring[]){
	SendClientMessage(playerid,COLOR_GDM,sendfstring);
}

#define GDM_sendAll(%1,%2) \
do{ \
	new \
	sendfstring[MAX_STRING];\
	format(sendfstring,MAX_STRING,(%1),%2);\
	SendClientMessageToAll(COLOR_GDM,sendfstring);\
}while(FALSE)

stock GDM_sendAll(const sendfstring[]){
	SendClientMessageToAll(COLOR_GDM,sendfstring);
}




forward GDM_isPlayerInGunDM(playerid);






/*
new 
	stock Menu:DM_BuyGunMenu[2];
*/

new stock
	Float:GunDMArea[4] = {1041.1852,-1449.3239,1612.2349,-1133.2903},
	Float:BuyGunArea[4] = {1285.0641,-1252.3297,1292.6895,-1213.2524};


//============================================================================================//
static const
	GDM_SwitchWeapon[MAX_WEAPON_SLOT][10] = {
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,0},
		{WEAPON_GOLFCLUB,WEAPON_NITESTICK,WEAPON_BAT,WEAPON_SHOVEL,WEAPON_POOLSTICK,WEAPON_KATANA,/*WEAPON_CHAINSAW*/-1,-1,-1,6},
		{WEAPON_COLT45,WEAPON_SILENCED,WEAPON_DEAGLE,-1,-1,-1,-1,-1,-1,3},
		{WEAPON_SHOTGUN,WEAPON_SAWEDOFF,WEAPON_SHOTGSPA,-1,-1,-1,-1,-1,-1,3},
		{WEAPON_UZI,WEAPON_MP5,WEAPON_TEC9,-1,-1,-1,-1,-1,-1,3},
		{WEAPON_AK47,WEAPON_M4,-1,-1,-1,-1,-1,-1,-1,2},
		{WEAPON_RIFLE,WEAPON_SNIPER,-1,-1,-1,-1,-1,-1,-1,2},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,0},
		{WEAPON_GRENADE,WEAPON_TEARGAS,WEAPON_MOLTOV,-1,-1,-1,-1,-1,-1,3},
		{WEAPON_SPRAYCAN,WEAPON_FIREEXTINGUISHER,WEAPON_CAMERA,-1,-1,-1,-1,-1,-1,3},
		{WEAPON_DILDO,WEAPON_DILDO2,WEAPON_VIBRATOR,WEAPON_VIBRATOR2,WEAPON_FLOWER,WEAPON_CANE,-1,-1,-1,6},
		//{44,45,WEAPON_PARACHUTE,-1,-1,-1,-1,-1,-1,3},
		{WEAPON_PARACHUTE,-1,-1,-1,-1,-1,-1,-1,-1,1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,0}
	};	
	
	
	
stock GDM_setPlayerSwitchWeapon(playerid,slotid,num){
	
	#if DEBUG_GDM
		writelog("[DEBUG_GDM]GDM_setPlayerSwitchWeapon called");
	#endif
	
	PlayerInfo[playerid][GunDM_PlayerSwitchWeapon][slotid] = num;
	return true;
}


stock GDM_getPlayerSwitchWeapon(playerid,slotid){
	
	#if DEBUG_GDM
		writetolog("[DEBUG_GDM]GDM_getPlayerSwitchWeapon called");
	#endif
	
	new 
		weaponloop = GDM_SwitchWeapon[slotid][9],
		switchid = (PlayerInfo[playerid][GunDM_PlayerSwitchWeapon][slotid]>weaponloop)?PlayerInfo[playerid][GunDM_PlayerSwitchWeapon][slotid]%weaponloop:PlayerInfo[playerid][GunDM_PlayerSwitchWeapon][slotid];
	return GDM_SwitchWeapon[slotid][switchid];
}




public GDM_isPlayerInGunDM(playerid){ debug_public_track("GDM_isPlayerInGunDM(playerid){");
	#if DEBUG_GDM
		writetolog("[DEBUG_GDM]GDM_isPlayerInGunDM called");
	#endif	
	return PlayerInfo[playerid][GunDM_PlayerIn]?true:false;
}
stock GDM_setPlayerInGunDM(playerid,bool:set){
	#if DEBUG_GDM
		writetolog("[DEBUG_GDM]GDM_setPlayerInGunDM called");
	#endif	
	PlayerInfo[playerid][GunDM_PlayerIn] = set;
	return true;
}
/*
stock GDM_isPlayerInGunDMArea(playerid){
	#if DEBUG_GDM
		writetolog("[DEBUG_GDM]GDM_isPlayerInGunDM called");
	#endif	
	return PlayerInArea(playerid,GunDMArea[0],GunDMArea[1],GunDMArea[2],GunDMArea[3]);
}
*/
/*
stock GDM_isPlayerInBuyGunArea(playerid){
	#if DEBUG_GDM
		writetolog("[DEBUG_GDM]GDM_isPlayerInGunDM called");
	#endif	
	return PlayerInArea(playerid,BuyGunArea[0],BuyGunArea[1],BuyGunArea[2],BuyGunArea[3]);
}
*/
stock GDM_allowPlayerSwitchWeapon(playerid){
	#if DEBUG_GDM
		writetolog("[DEBUG_GDM]GDM_allowPlayerSwitchWeapon called");
	#endif
	return (!GetPlayerVehicleID(playerid) && GDM_isPlayerInGunDM(playerid) /*&& GDM_isPlayerInBuyGunArea(playerid)*/);
}

public GDM_setPlayeroutGDM(playerid){ debug_public_track("GDM_setPlayeroutGDM(playerid){");
	ResetPlayerWeapons(playerid);
	SetPlayerVirtualWorld(playerid,0);
	GDM_setPlayerInGunDM(playerid,false);
	OnPlayerSpawn(playerid);
	//SetPlayerWorldBounds(playerid,9999,-9999,9999,-9999);
	GDM_send(playerid,"[DM]你离开了战场");
	return true;	
}


public GDM_setPlayertoGDM(playerid){ debug_public_track("GDM_setPlayertoGDM(playerid){");
	GDM_setPlayerInGunDM(playerid,true);
	ResetPlayerWeapons(playerid);
	SetPlayerArmour(playerid,100);
	SetPlayerHealth(playerid,100);
	SetPlayerVirtualWorld(playerid,GDM_WORLD);
	GivePlayerWeapon(playerid,WEAPON_KATANA,1);
	GivePlayerWeapon(playerid,WEAPON_DEAGLE,9999);
	GivePlayerWeapon(playerid,WEAPON_SHOTGSPA,9999);
	GivePlayerWeapon(playerid,WEAPON_MP5,9999);
	GivePlayerWeapon(playerid,WEAPON_M4,9999);
	GivePlayerWeapon(playerid,WEAPON_SNIPER,9999);
	GivePlayerWeapon(playerid,WEAPON_TEARGAS,9999);
	GivePlayerWeapon(playerid,WEAPON_FIREEXTINGUISHER,9999);
	GivePlayerWeapon(playerid,WEAPON_FLOWER,1);
	GivePlayerWeapon(playerid,WEAPON_PARACHUTE,1);
	//1236.0431,-1259.0552,17.1903
	TeleportPlayer(playerid,1271.1410,-1254.5160,14.1928,90,0,true);
	GDM_send(playerid,"[DM]再次输入/gdm可离开战场");
	GDM_send(playerid,"[DM]在废弃战场按\"num1\"可以切换武器");
	return true;
}


zcmd(gdm_gunDM,playerid,params[]){
	if(GDM_isPlayerInGunDM(playerid)){
		GDM_setPlayeroutGDM(playerid);
	}else
	{
		GDM_setPlayertoGDM(playerid);
	}
	return true;
}
pzcmd(gdm) rzcmd(gdm_gunDM);
