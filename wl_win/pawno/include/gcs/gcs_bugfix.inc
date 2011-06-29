/**====================================================================================
								Bug Fix	
								


Description:
	Fix some PAWN-SAMP bugs.
	
Legal:
	Copyright (C) 2009 ,GCS Team
	
	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
	MA 02110-1301, USA.
	
	
Version:
	0.3.0
Changelog:
	08/10/18:
		Update to prefix for sa-mp 0.3a
		Remove some bugfix (fixed in sa-mp 0.3a).
	08/07/26:
		Update to 0.2.0
		Remove some useless info in source code.
		Bug fix:
			A new bug on GetPlayerMenu 
			A new bug on SpawnPlayer
			GetPlayerAmmo marked as fix, but it haven't been fixed.
			GetPlayerWeapon is a bug fix for GetPlayerWeaponData.
		Add bugfix:
			AttachTrailerToVehicle
			GetVehicleTrailer
			SetPlayerName
			GetWeaponName
	08/06/06:
		First version.
		Fixed:
			Fire death bug - (Fixed)
			GetPlayerMenu - (Error)
			IsPlayerInCheckpoint - (Fixed)
			IsPlayerInRaceCheckpoint - (Fixed)
			SetPlayerRaceCheckpoint - (Fixed)
			SetPlayerCheckpoint - (Fixed)
			GetPlayerColor - (Fixed)
			GetPlayerTeam - (Fixed)
			GivePlayerWeapon - (Fixed)
			GetPlayerAmmo - (Fixed)
			GetPlayerInterior - (Fixed)
			SpawnPlayer - (Fixed)
			floatstr - (Fixed)
			strval - (Fixed)
			strcmp - (Fixed)
			PlayerPlaySound - (Fixed)			

Note:	
	More bug info in http://forum.sa-mp.com/index.php?topic=82288.0
	And you can report sa-mp bug here:http://www.sa-mpbugs.com
	If you find any bug, Send to e-mail:imyezizhu@gmail.com

*/

/**===================================Bug fix list======================================================
Note:
	You can (en/dis)able the bug fix by change false|true.
*/	


/**
	Fire death bug 
		Still "alive" if someone dies in fire.
*/
#define GCS_BF_FIREDEATH				(true)


/**
	IsPlayerInRaceCheckpoint
		Variable isn't initiated until a checkpoint has been set 
		so it returns a undetermined value
*/
#define GCS_BF_ISPLAYERINRACECHECKPOINT	(true)

/**
	IsPlayerInCheckpoint 
		Variable isn't initiated until a checkpoint has been set 
		so it returns a undetermined value
*/
#define GCS_BF_ISPLAYERINCHECKPOINT		(true)

/**
	SetPlayerRaceCheckpoint
		If a checkpoint is already set 
		it will use the size of that checkpoint instead of the new one
		Note:
			Doesn't fix:If the checkpoint is set on a custom object or a non-solid surface it will show floating above the surface
*/
#define GCS_BF_SETPLAYERRACECHEKCPOINT	(true)

/**
	SetPlayerCheckpoint
		If a checkpoint is already set 
		it will use the size of that checkpoint instead of the new one
		Note:
			Doesn't fix:If the checkpoint is set on a custom object or a non-solid surface it will show floating above the surface

*/
#define GCS_BF_SETPLAYERCHEKCPOINT		(true)

/**
	GetPlayerColor
		Returns 0 unless SetPlayerColor has been used
*/
#define GCS_BF_GETPLAYERCOLOR			(true)

/**
	GetPlayerWeaponData
		If ammo bigger than 65534 or smalled than 0 will cause some problems
*/
#define GCS_BF_GETPLAYERWEAPONDATA		(false)

/**
	SetPlayerAmmo
		Doesn't work
		Note:
			Use GetPlayerWeaponData to fix
*/
#define GCS_BF_SETPLAYERAMMO			(false)

/**
	GetPlayerAmmo
		Doesn't work.
		Note:
			Use GetPlayerWeaponData to fix
*/
#define GCS_BF_GETPLAYERAMMO			(false)

/**
	GetWeaponName
		Return null for ids 18, 44 and 45
		Note:
			Named to:
			18 - Molotovs
			44 - Nightvision_Goggles
			45 - Thermal_Goggles
*/
#define GCS_BF_GETWEAPONNAME			(true)


/**
	SpawnPlayer
		Doesn't work if the player is in a vehicle
*/
#define GCS_BF_SPAWNPLAYER				(true)


/**
	strcmp
		If one of the strings is empty but the other isn't, 
		it will return 0 (recognising them as being the same)
*/
#define GCS_BF_STRCMP					(true)

/**
	PlayerPlaySound
		Useless of x,y,z
*/
#define GCS_BF_PLAYERPLAYSOUND			(true)

/**
	SetPlayerName
		If you set to the same name but some letters are in a different case it doesn't work (eg "heLLO" to "hello")
*/
#define GCS_BF_SETPLAYERNAME			(true)




//===============================================================================================================



#if GCS_BF_FIREDEATH
stock gcs_bf_FireDeath_PlayerDeath(playerid){
	TogglePlayerControllable(playerid,false);
	TogglePlayerControllable(playerid,true);
}
#endif



#if GCS_BF_ISPLAYERINRACECHECKPOINT
stock gcs_bf_isinRaceCheckpoint_Init(){
	for(new i;i<MAX_PLAYERS;i++)
		SetPlayerRaceCheckpoint(i,0,0,0,0,0,0,0,1);
	for(new i;i<MAX_PLAYERS;i++)
		DisablePlayerRaceCheckpoint(i);
}
#endif



#if GCS_BF_ISPLAYERINCHECKPOINT
stock gcs_bf_isinCheckpoint_Init(){
	for(new i;i<MAX_PLAYERS;i++)
		SetPlayerCheckpoint(i,0,0,0,1);
	for(new i;i<MAX_PLAYERS;i++)
		DisablePlayerCheckpoint(i);
}
#endif



#if GCS_BF_SETPLAYERRACECHEKCPOINT
static stock 
	gcs_s_bf_RaceCheckpoint_type[MAX_PLAYERS],
	Float:gcs_s_bf_RaceCheckpoint_cx[MAX_PLAYERS],
	Float:gcs_s_bf_RaceCheckpoint_cy[MAX_PLAYERS],
	Float:gcs_s_bf_RaceCheckpoint_cz[MAX_PLAYERS],
	Float:gcs_s_bf_RaceCheckpoint_nx[MAX_PLAYERS],
	Float:gcs_s_bf_RaceCheckpoint_ny[MAX_PLAYERS],
	Float:gcs_s_bf_RaceCheckpoint_nz[MAX_PLAYERS],
	Float:gcs_s_bf_RaceCheckpoint_size[MAX_PLAYERS];

forward gcs_bf_setRaceCheckpoint_1(playerid);
public gcs_bf_setRaceCheckpoint_1(playerid){
	SetPlayerRaceCheckpoint(playerid,gcs_s_bf_RaceCheckpoint_type[playerid],gcs_s_bf_RaceCheckpoint_cx[playerid], gcs_s_bf_RaceCheckpoint_cy[playerid], gcs_s_bf_RaceCheckpoint_cz[playerid], gcs_s_bf_RaceCheckpoint_nx[playerid], gcs_s_bf_RaceCheckpoint_ny[playerid],gcs_s_bf_RaceCheckpoint_nz[playerid], gcs_s_bf_RaceCheckpoint_size[playerid]);
}

stock gcs_bf_setPlayerRaceCheckpoint(playerid, type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size){
	DisablePlayerRaceCheckpoint(playerid);
	gcs_s_bf_RaceCheckpoint_type[playerid] = type;
	gcs_s_bf_RaceCheckpoint_cx[playerid] = x;
	gcs_s_bf_RaceCheckpoint_cy[playerid] = y;
	gcs_s_bf_RaceCheckpoint_cz[playerid] = z;
	gcs_s_bf_RaceCheckpoint_nx[playerid] = nextx;
	gcs_s_bf_RaceCheckpoint_ny[playerid] = nexty;
	gcs_s_bf_RaceCheckpoint_nz[playerid] = nextz;
	gcs_s_bf_RaceCheckpoint_size[playerid] = size;
	SetTimerEx("gcs_bf_setRaceCheckpoint_1",GetPlayerPing(playerid)/5+50,false,"i",playerid);
	return true;
}
#define SetPlayerRaceCheckpoint(%1) gcs_bf_setPlayerRaceCheckpoint(%1)
#endif



#if GCS_BF_SETPLAYERCHEKCPOINT
static stock
	Float:gcs_s_bf_Checkpoint_x[MAX_PLAYERS],
	Float:gcs_s_bf_Checkpoint_y[MAX_PLAYERS],
	Float:gcs_s_bf_Checkpoint_z[MAX_PLAYERS],
	Float:gcs_s_bf_Checkpoint_size[MAX_PLAYERS];
forward gcs_bf_setPlayerCheckpoint_1(playerid);
public gcs_bf_setPlayerCheckpoint_1(playerid){
	SetPlayerCheckpoint(playerid,gcs_s_bf_Checkpoint_x[playerid],gcs_s_bf_Checkpoint_y[playerid],gcs_s_bf_Checkpoint_z[playerid],gcs_s_bf_Checkpoint_size[playerid]);
}
stock gcs_bf_setPlayerCheckpoint(playerid, Float:x, Float:y, Float:z, Float:size){
	DisablePlayerCheckpoint(playerid);
	gcs_s_bf_Checkpoint_x[playerid] = x;
	gcs_s_bf_Checkpoint_y[playerid] = y;
	gcs_s_bf_Checkpoint_z[playerid] = z;
	gcs_s_bf_Checkpoint_size[playerid] = size;
	SetTimerEx("gcs_bf_setPlayerCheckpoint_1",GetPlayerPing(playerid)/5+25,false,"i",playerid);
	return true;
}
#define SetPlayerCheckpoint(%1) gcs_bf_setPlayerCheckpoint(%1)
#endif



#if GCS_BF_GETPLAYERCOLOR
static const stock 
	gcs_bf_pColor[] = {
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF,
0xFF8080FF,0xFFFF80FF,0x80FF80FF,0x00FF80FF,0x80FFFFFF,0xFF0080FF,0xFF80C0FF,0xFF80FFFF,0x80FF00FF,0x00FF40FF
};
stock gcs_bf_getPlayerColor_Connect(playerid){
	SetPlayerColor(playerid,gcs_bf_pColor[playerid]);
}
#endif



#if GCS_BF_GETPLAYERWEAPONDATA || GCS_BF_SETPLAYERAMMO || GCS_BF_GETPLAYERAMMO
stock gcs_bf_getWeaponSlot(weaponid){ 
	switch(weaponid){ 
		case WEAPON_GOLFCLUB,WEAPON_NITESTICK,WEAPON_KNIFE,WEAPON_BAT,WEAPON_SHOVEL,WEAPON_POOLSTICK,WEAPON_KATANA,WEAPON_CHAINSAW: return 1;
		case WEAPON_COLT45,WEAPON_SILENCED,WEAPON_DEAGLE: return 2; 
		case WEAPON_SHOTGUN,WEAPON_SAWEDOFF,WEAPON_SHOTGSPA: return 3; 
		case WEAPON_UZI,WEAPON_MP5,WEAPON_TEC9: return 4; 
		case WEAPON_AK47,WEAPON_M4: return 5; 
		case WEAPON_RIFLE,WEAPON_SNIPER: return 6;
		case WEAPON_ROCKETLAUNCHER,WEAPON_HEATSEEKER,WEAPON_FLAMETHROWER,WEAPON_MINIGUN: return 7;
		case WEAPON_GRENADE,WEAPON_TEARGAS,WEAPON_MOLTOV,WEAPON_SATCHEL: return 8;
		case WEAPON_SPRAYCAN,WEAPON_FIREEXTINGUISHER,WEAPON_CAMERA: return 9;  
		case WEAPON_DILDO,WEAPON_DILDO2,WEAPON_VIBRATOR,WEAPON_VIBRATOR2,WEAPON_FLOWER,WEAPON_CANE: return 10;
		case 44,45,WEAPON_PARACHUTE:return 11;//WEAPON_NIGHTVISION,WEAPON_INFRARED: return 11;
		case WEAPON_BOMB: return 12; 
	}
	return 0; 
}
#endif



#if GCS_BF_GETPLAYERWEAPONDATA
stock gcs_bf_givePlayerWeapon(playerid,weaponid,ammo){
	new 
		ammo2;
	GetPlayerWeaponData(playerid,gcs_bf_getWeaponSlot(weaponid),ammo2,ammo2);
	if(ammo2+ammo > 65532){
		return GivePlayerWeapon(playerid,weaponid,65532-ammo2);
	}else if(ammo2+ammo < 0){
		return GivePlayerWeapon(playerid,weaponid,0-ammo2);
	}
	return GivePlayerWeapon(playerid,weaponid,ammo);
	//return GivePlayerWeapon(playerid,weaponid, ((ammo2+ammo > 65532)?(65532-ammo2):((ammo > 0)?ammo:0)));
}
#define GivePlayerWeapon(%1) gcs_bf_givePlayerWeapon(%1)
#endif



#if GCS_BF_SETPLAYERAMMO
stock gcs_bf_setPlayerAmmo(playerid,ammo){
	return GivePlayerWeapon(playerid,GetPlayerWeapon(playerid),ammo);
}
#define SetPlayerAmmo(%1) gcs_bf_setPlayerAmmo(%1)
#endif



#if GCS_BF_GETPLAYERAMMO
stock gcs_bf_getPlayerAmmo(playerid){
	new
		slot = gcs_bf_getWeaponSlot(GetPlayerWeapon(playerid));
	if(slot == 0 || slot == 1 || slot == 9 || slot == 10 || slot == 11) return 0;
	new ammo;
	GetPlayerWeaponData(playerid,slot,ammo,ammo);
	return ammo;
}
#define GetPlayerAmmo(%1) gcs_bf_getPlayerAmmo(%1)
#endif



#if GCS_BF_GETWEAPONNAME
stock gcs_bf_getWeaponName(weaponid,weapon[], len){
	switch(weaponid){
		case 18:{
			format(weapon,len,"Molotovs");
			return true;
		}
		case 44:{
			format(weapon,len,"Nightvision_Goggles");
			return true;
		}
		case 45:{
			format(weapon,len,"Thermal_Goggles");
			return true;
		}
	}
	return GetWeaponName(weaponid,weapon,len);
}
#define GetWeaponName(%1) gcs_bf_getWeaponName(%1)
#endif





#if GCS_BF_SPAWNPLAYER
forward gcs_bf_spawnPlayer_1(playerid);
public gcs_bf_spawnPlayer_1(playerid){
	SpawnPlayer(playerid);
}
stock gcs_bf_spawnPlayer(playerid){
	if(IsPlayerInAnyVehicle(playerid)){
		new
			Float:ppos[3];
		GetPlayerPos(playerid,ppos[0],ppos[1],ppos[2]);
		SetPlayerPos(playerid,ppos[0],ppos[1],ppos[2]+1);
		SetTimerEx("gcs_bf_spawnPlayer_1",GetPlayerPing(playerid)/5+25,false,"i",playerid);
		return true;
	}
	return SpawnPlayer(playerid);
}
#define SpawnPlayer(%1) gcs_bf_spawnPlayer(%1)
#endif



#if GCS_BF_SETPLAYERNAME
stock gcs_bf_setPlayerName(playerid,name[]){
	new
		oname[MAX_PLAYER_NAME];
	GetPlayerName(playerid,oname,MAX_PLAYER_NAME);
	if(!strcmp(oname,name,true))
		SetPlayerName(playerid,"UMKMOW_MANE");
	return SetPlayerName(playerid,name);
}
#define SetPlayerName(%1) gcs_bf_setPlayerName(%1)
#endif





#if GCS_BF_STRCMP
stock gcs_bf_strcmp(const str1[],const str2[],bool:ignorecase = false,length = cellmax){
	if(!str1[0] && !str2[0])return 0;
	if(!str1[0])return 0-strlen(str2);
	if(!str2[0])return strlen(str1);
	return strcmp(str1,str2,ignorecase,length);
}
#define strcmp(%1) gcs_bf_strcmp(%1)
#endif



#if GCS_BF_PLAYERPLAYSOUND
stock gcs_bf_PlayerplaySound(playerid,soundid,const Float:playeridx=0.0,const Float:playeridy=0.0,const Float:playeridz=0.0){
	#pragma unused playeridx,playeridy,playeridz
	new
		Float:tmppos[3];
	GetPlayerPos(playerid,tmppos[0],tmppos[1],tmppos[2]);
	return PlayerPlaySound(playerid,soundid,tmppos[0],tmppos[1],tmppos[2]);
}
#define PlayerPlaySound(%1) gcs_bf_PlayerplaySound(%1)
#endif





#if (GCS_BF_FIREDEATH)
gcs_bf_OnPlayerDeath(playerid){
	#if GCS_BF_FIREDEATH
		gcs_bf_FireDeath_PlayerDeath(playerid);
	#endif
}
#endif


#if (GCS_BF_GETPLAYERCOLOR)

gcs_bf_OnPlayerConnect(playerid){

	#if GCS_BF_GETPLAYERCOLOR
		gcs_bf_getPlayerColor_Connect(playerid);
	#endif	
	
}

#endif



#if (GCS_BF_ISPLAYERINRACECHECKPOINT || GCS_BF_ISPLAYERINCHECKPOINT)

gcs_bf_OnGameModeInit(){

	#if GCS_BF_ISPLAYERINRACECHECKPOINT
		gcs_bf_isinRaceCheckpoint_Init();
	#endif
	
	#if GCS_BF_ISPLAYERINCHECKPOINT
		gcs_bf_isinCheckpoint_Init();
	#endif
}

#endif


