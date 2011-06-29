/**====================================================================================
								ecode
								
								
								
Description:
	Easy Code System
	
	You can use easier and more simple code to save time.

Legal:

	Copyright (c) 2009 Shindo(ssh)

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

Version:
	0.1
	
Changelog:
	2009/08/02:
		First version

Functions:
	there are three ways to use easy code system, you can set wehther to use thme.
	eg. if you don't want to use mode_2, you can change the value of CODE_MODE_2 to (false)
	
	CODE_MODE_1 has the following stocks:
	    PlayerAngle(playerid); - the same as GetPlayerFacingAngle, but more easy, it returns the player's facing angle.
		PlayerHealth(playerid); - the same as GetPlayerHealth, but more easy, it returns the player's health.
		PlayerIP(playerid); - the same as GetPlayerIp, but more easy, it returns the player's IP.
		PlayerArmour(playerid); - the same as GetPlayerArmour, but more easy, it returns the player's armour.
		PlayerName(playerid); - the same as GetPlayerName, but more easy, it returns the player's name.
		VehicleHealth(vehicleid); - the same as GetVehicleHealth, but more easy, it returns vehicle's health.
		VehicleAngle(vehicleid); - the same sa GetVehicleZAngle, but more easy, it returns vehicle's z-rot angle.
		WeaponName(weaponid); - the same as GetWeaponName, but more easy, it returns weapon's name.
		eg.
			PlayerX(playerid); - you can use it to only get the player's x pos(it returns the player's x pos).
			PlayerY(playerid); - you can use it to only get the player's y pos(it returns the player's y pos).
			PlayerZ(playerid); - you can use it to only get the player's z pos(it returns the player's z pos).
		so others that is similar to above have the same mean as above.
		
	CODE_MODE_2 has the following stocks:
		playerAngle(playerid); - the same as GetPlayerFacingAngle, but more easy, it returns the player's facing angle.
		playerHealth(playerid); - the same as GetPlayerHealth, but more easy, it returns the player's health.
		playerIP(playerid); - the same as GetPlayerIp, but more easy, it returns the player's IP.
		playerArmour(playerid); - the same as GetPlayerArmour, but more easy, it returns the player's armour.
		playerName(playerid); - the same as GetPlayerName, but more easy, it returns the player's name.
		vehicleHealth(vehicleid); - the same as GetVehicleHealth, but more easy, it returns vehicle's health.
		vehicleAngle(vehicleid); - the same sa GetVehicleZAngle, but more easy, it returns vehicle's z-rot angle.
		weaponName(weaponid); - the same as GetWeaponName, but more easy, it returns weapon's name.
		eg.
			playerX(playerid); - you can use it to only get the player's x pos(it returns the player's x pos).
			playerY(playerid); - you can use it to only get the player's y pos(it returns the player's y pos).
			playerZ(playerid); - you can use it to only get the player's z pos(it returns the player's z pos).
		so others that is similar to above have the same mean as above.
		
	CODE_MODE_3 has the following stocks:
		pAngle(playerid); - the same as GetPlayerFacingAngle, but more easy, it returns the player's facing angle.
		pHealth(playerid); - the same as GetPlayerHealth, but more easy, it returns the player's health.
		pIP(playerid); - the same as GetPlayerIp, but more easy, it returns the player's IP.
		pArmour(playerid); - the same as GetPlayerArmour, but more easy, it returns the player's armour.
		pName(playerid); - the same as GetPlayerName, but more easy, it returns the player's name.
		vHealth(vehicleid); - the same as GetVehicleHealth, but more easy, it returns vehicle's health.
		vAngle(vehicleid); - the same sa GetVehicleZAngle, but more easy, it returns vehicle's z-rot angle.
		wName(weaponid); - the same as GetWeaponName, but more easy, it returns weapon's name.
		eg.
			pX(playerid); - you can use it to only get the player's x pos(it returns the player's x pos).
			pY(playerid); - you can use it to only get the player's y pos(it returns the player's y pos).
			pZ(playerid); - you can use it to only get the player's z pos(it returns the player's z pos).
		so others that is similar to above have the same mean as above.
	
	You can use three ways at the same time.
	
Definitions:
	eg. CODE_MODE_1:ObjectPos, it's the same as GetObjectPos, but the code is more simple.
	 	CODE_MODE_2:objectPos, it's the same as GetObjectPos, but the code is more simple.
	 	CODE_MODE_3:oPos, it's the same as GetObjectPos, but the code is more simple.

=======================================================================================*/

#define CODE_MODE_1 (true) // if you don't want to use this way, you can change it to (false)
#define CODE_MODE_2 (false) // if you don't want to use this way, you can change it to (false)
#define CODE_MODE_3 (true) // if you don't want to use this way, you can change it to (false)

#if CODE_MODE_1
	#define ObjectPos(%1) GetObjectPos(%1)
	#define ObjectRot(%1) GetObjectRot(%1)
	#define PlayerAmmo(%1) GetPlayerAmmo(%1)
	#define PlayerColor(%1) GetPlayerColor(%1)
	#define PlayerInterior(%1) GetPlayerInterior(%1)
	#define PlayerKeys(%1) GetPlayerKeys(%1) //pity
	#define PlayerMenu(%1) GetPlayerMenu(%1)
	#define PlayerMoney(%1) GetPlayerMoney(%1)
	#define PlayerObjectPos(%1) GetPlayerObjectPos(%1)
	#define PlayerObjectRot(%1) GetPlayerObjectRot(%1)
	#define PlayerPing(%1) GetPlayerPing(%1)
	#define PlayerPos(%1) GetPlayerPos(%1)
	#define PlayerScore(%1) GetPlayerScore(%1)
	#define PlayerSkin(%1) GetPlayerSkin(%1)
	#define PlayerSpecialAction(%1) GetPlayerSpecialAction(%1)
	#define PlayerState(%1) GetPlayerState(%1)
	#define PlayerTeam(%1) GetPlayerTeam(%1)
	#define PlayerTime(%1) GetPlayerTime(%1)
	#define PlayerVehicleID(%1) GetPlayerVehicleID(%1)
	#define PlayerVirtualWorld(%1) GetPlayerVirtualWorld(%1)
	#define PlayerWantedLevel(%1) GetPlayerWantedLevel(%1)
	#define PlayerWeapon(%1) GetPlayerWeapon(%1)
	#define PlayerWeaponData(%1) GetPlayerWeaponData(%1)
	#define TickCount GetTickCount
	#define VehicleModel(%1) GetVehicleModel(%1)
	#define VehiclePos(%1) GetVehiclePos(%1)
	#define VehicleTrailer(%1) GetVehicleTrailer(%1)
	#define VehicleVirtualWorld(%1) GetVehicleVirtualWorld(%1)

	/*forward Float:PlayerAngle(playerid);
	forward Float:PlayerHealth(playerid);
	forward Float:PlayerArmour(playerid);
	forward PlayerIP(playerid);
	forward PlayerName(playerid);
	forward Float:VehicleHealth(vehicleid);
	forward Float:VehicleAngle(vehicleid);
	forward WeaponName(weaponid);
	forward Float:PlayerX(playerid);
	forward Float:PlayerY(playerid);
	forward Float:PlayerZ(playerid);
	forward Float:ObjectX(objectid);
	forward Float:ObjectY(objectid);
	forward Float:ObjectZ(objectid);
	forward Float:ObjectRotX(objectid);
	forward Float:ObjectRotY(objectid);
	forward Float:ObjectRotZ(objectid);
	forward Float:VehicleX(vehicleid);
	forward Float:VehicleY(vehicleid);
	forward Float:VehicleZ(vehicleid);
	forward Float:PlayerObjectPosX(playerid,objectid);
	forward Float:PlayerObjectPosY(playerid,objectid);
	forward Float:PlayerObjectPosZ(playerid,objectid);
	forward Float:PlayerObjectRotX(playerid,objectid);
	forward Float:PlayerObjectRotY(playerid,objectid);
	forward Float:PlayerObjectRotZ(playerid,objectid);*/

	stock Float:PlayerAngle(playerid)
	{
		new Float:Angle;
		GetPlayerFacingAngle(playerid, Angle);
		return Angle;
	}

	stock Float:PlayerHealth(playerid)
	{
	    new Float:Health;
	    GetPlayerHealth(playerid, Health);
	    return Health;
	}

	stock Float:PlayerArmour(playerid)
	{
	    new Float:Armour;
	    GetPlayerArmour(playerid, Armour);
	    return Armour;
	}

	stock PlayerIP(playerid)
	{
		new PIP[16];
		GetPlayerIp(playerid,PIP, sizeof(PIP));
		return PIP;
	}

	stock PlayerName(playerid)
	{
		new PN[MAX_PLAYER_NAME];
		GetPlayerName(playerid, PN, sizeof(PN));
		return PN;
	}
	

	stock Float:VehicleHealth(vehicleid)
	{
	    new Float:health;
	    GetVehicleHealth(vehicleid, health);
	    return health;
	}

	stock Float:VehicleAngle(vehicleid)
	{
		new Float:angle;
	    GetVehicleZAngle(vehicleid, angle);
		return angle;
	}

	stock WeaponName(weaponid)
	{
	    new weaName[65];
	    GetWeaponName(weaponid, weaName, sizeof(weaName));
	    return weaName;
	}

	stock Float:PlayerX(playerid)
	{
		new Float:p_pos[3];
		GetPlayerPos(playerid,p_pos[0],p_pos[1],p_pos[2]);
		return p_pos[0];
	}

	stock Float:PlayerY(playerid)
	{
		new Float:p_pos[3];
		GetPlayerPos(playerid,p_pos[0],p_pos[1],p_pos[2]);
		return p_pos[1];
	}

	stock Float:PlayerZ(playerid)
	{
		new Float:p_pos[3];
		GetPlayerPos(playerid,p_pos[0],p_pos[1],p_pos[2]);
		return p_pos[2];
	}

	stock Float:ObjectX(objectid)
	{
		new Float:o_pos[3];
		GetObjectPos(objectid,o_pos[0],o_pos[1],o_pos[2]);
		return o_pos[0];
	}

	stock Float:ObjectY(objectid)
	{
		new Float:o_pos[3];
		GetObjectPos(objectid,o_pos[0],o_pos[1],o_pos[2]);
		return o_pos[1];
	}

	stock Float:ObjectZ(objectid)
	{
		new Float:o_pos[3];
		GetObjectPos(objectid,o_pos[0],o_pos[1],o_pos[2]);
		return o_pos[2];
	}

	stock Float:ObjectRotX(objectid)
	{
		new Float:r_pos[3];
		GetObjectRot(objectid,r_pos[0],r_pos[1],r_pos[2]);
		return r_pos[0];
	}

	stock Float:ObjectRotY(objectid)
	{
		new Float:r_pos[3];
		GetObjectRot(objectid,r_pos[0],r_pos[1],r_pos[2]);
		return r_pos[1];
	}

	stock Float:ObjectRotZ(objectid)
	{
		new Float:r_pos[3];
		GetObjectRot(objectid,r_pos[0],r_pos[1],r_pos[2]);
		return r_pos[2];
	}

	stock Float:VehicleX(vehicleid)
	{
		new Float:v_pos[3];
		GetVehiclePos(vehicleid,v_pos[0],v_pos[1],v_pos[2]);
		return v_pos[0];
	}

	stock Float:VehicleY(vehicleid)
	{
		new Float:v_pos[3];
		GetVehiclePos(vehicleid,v_pos[0],v_pos[1],v_pos[2]);
		return v_pos[1];
	}

	stock Float:VehicleZ(vehicleid)
	{
		new Float:v_pos[3];
		GetVehiclePos(vehicleid,v_pos[0],v_pos[1],v_pos[2]);
		return v_pos[2];
	}

	stock Float:PlayerObjectPosX(playerid,objectid)
	{
		new Float:o_pos[3];
		GetPlayerObjectPos(playerid,objectid,o_pos[0],o_pos[1],o_pos[2]);
		return o_pos[0];
	}

	stock Float:PlayerObjectPosY(playerid,objectid)
	{
		new Float:o_pos[3];
		GetPlayerObjectPos(playerid,objectid,o_pos[0],o_pos[1],o_pos[2]);
		return o_pos[1];
	}

	stock Float:PlayerObjectPosZ(playerid,objectid)
	{
		new Float:o_pos[3];
		GetPlayerObjectPos(playerid,objectid,o_pos[0],o_pos[1],o_pos[2]);
		return o_pos[2];
	}

	stock Float:PlayerObjectRotX(playerid,objectid)
	{
		new Float:r_pos[3];
		GetPlayerObjectRot(playerid,objectid,r_pos[0],r_pos[1],r_pos[2]);
		return r_pos[0];
	}

	stock Float:PlayerObjectRotY(playerid,objectid)
	{
		new Float:r_pos[3];
		GetPlayerObjectRot(playerid,objectid,r_pos[0],r_pos[1],r_pos[2]);
		return r_pos[1];
	}

	stock Float:PlayerObjectRotZ(playerid,objectid)
	{
		new Float:r_pos[3];
		GetPlayerObjectRot(playerid,objectid,r_pos[0],r_pos[1],r_pos[2]);
		return r_pos[2];
	}
#endif

#if CODE_MODE_2
	#define objectPos(%1) GetObjectPos(%1)
	#define objectRot(%1) GetObjectRot(%1)
	#define playerAmmo(%1) GetPlayerAmmo(%1)
	#define playerColor(%1) GetPlayerColor(%1)
	#define playerInterior(%1) GetPlayerInterior(%1)
	#define playerKeys(%1) GetPlayerKeys(%1) //pity
	#define playerMenu(%1) GetPlayerMenu(%1)
	#define playerMoney(%1) GetPlayerMoney(%1)
	#define playerObjectPos(%1) GetPlayerObjectPos(%1)
	#define playerObjectRot(%1) GetPlayerObjectRot(%1)
	#define playerPing(%1) GetPlayerPing(%1)
	#define playerPos(%1) GetPlayerPos(%1)
	#define playerScore(%1) GetPlayerScore(%1)
	#define playerSkin(%1) GetPlayerSkin(%1)
	#define playerSpecialAction(%1) GetPlayerSpecialAction(%1)
	#define playerState(%1) GetPlayerState(%1)
	#define playerTeam(%1) GetPlayerTeam(%1)
	#define playerTime(%1) GetPlayerTime(%1)
	#define playerVehicleID(%1) GetPlayerVehicleID(%1)
	#define playerVirtualWorld(%1) GetPlayerVirtualWorld(%1)
	#define playerWantedLevel(%1) GetPlayerWantedLevel(%1)
	#define playerWeapon(%1) GetPlayerWeapon(%1)
	#define playerWeaponData(%1) GetPlayerWeaponData(%1)
	#define tickCount(%1) GetTickCount(%1)
	#define vehicleModel(%1) GetVehicleModel(%1)
	#define vehiclePos(%1) GetVehiclePos(%1)
	#define vehicleTrailer(%1) GetVehicleTrailer(%1)
	#define vehicleVirtualWorld(%1) GetVehicleVirtualWorld(%1)

	/*forward Float:playerAngle(playerid);
	forward Float:playerHealth(playerid);
	forward Float:playerArmour(playerid);
	forward playerIP(playerid);
	forward playerName(playerid);
	forward Float:vehicleHealth(vehicleid);
	forward Float:vehicleAngle(vehicleid);
	forward weaponName(weaponid);
	forward Float:playerX(playerid);
	forward Float:playerY(playerid);
	forward Float:playerZ(playerid);
	forward Float:objectX(objectid);
	forward Float:objectY(objectid);
	forward Float:objectZ(objectid);
	forward Float:objectRotX(objectid);
	forward Float:objectRotY(objectid);
	forward Float:objectRotZ(objectid);
	forward Float:vehicleX(vehicleid);
	forward Float:vehicleY(vehicleid);
	forward Float:vehicleZ(vehicleid);
	forward Float:playerObjectPosX(playerid,objectid);
	forward Float:playerObjectPosY(playerid,objectid);
	forward Float:playerObjectPosZ(playerid,objectid);
	forward Float:playerObjectRotX(playerid,objectid);
	forward Float:playerObjectRotY(playerid,objectid);
	forward Float:playerObjectRotZ(playerid,objectid);*/

	stock Float:playerAngle(playerid)
	{
		new Float:Angle;
		GetPlayerFacingAngle(playerid, Angle);
		return Angle;
	}

	stock Float:playerHealth(playerid)
	{
	    new Float:Health;
	    GetPlayerHealth(playerid, Health);
	    return Health;
	}

	stock Float:playerArmour(playerid)
	{
	    new Float:Armour;
	    GetPlayerArmour(playerid, Armour);
	    return Armour;
	}

	stock playerIP(playerid)
	{
		new PIP[16];
		GetPlayerIp(playerid,PIP, sizeof(PIP));
		return PIP;
	}

	stock playerName(playerid)
	{
		new PN[MAX_PLAYER_NAME];
		GetPlayerName(playerid, PN, sizeof(PN));
		return PN;
	}

	stock Float:vehicleHealth(vehicleid)
	{
	    new Float:health;
	    GetVehicleHealth(vehicleid, health);
	    return health;
	}

	stock Float:vehicleAngle(vehicleid)
	{
		new Float:angle;
	    GetVehicleZAngle(vehicleid, angle);
		return angle;
	}

	stock weaponName(weaponid)
	{
	    new weaName[65];
	    GetWeaponName(weaponid, weaName, sizeof(weaName));
	    return weaName;
	}

	stock Float:playerX(playerid)
	{
		new Float:p_pos[3];
		GetPlayerPos(playerid,p_pos[0],p_pos[1],p_pos[2]);
		return p_pos[0];
	}

	stock Float:playerY(playerid)
	{
		new Float:p_pos[3];
		GetPlayerPos(playerid,p_pos[0],p_pos[1],p_pos[2]);
		return p_pos[1];
	}

	stock Float:playerZ(playerid)
	{
		new Float:p_pos[3];
		GetPlayerPos(playerid,p_pos[0],p_pos[1],p_pos[2]);
		return p_pos[2];
	}

	stock Float:objectX(objectid)
	{
		new Float:o_pos[3];
		GetObjectPos(objectid,o_pos[0],o_pos[1],o_pos[2]);
		return o_pos[0];
	}

	stock Float:objectY(objectid)
	{
		new Float:o_pos[3];
		GetObjectPos(objectid,o_pos[0],o_pos[1],o_pos[2]);
		return o_pos[1];
	}

	stock Float:objectZ(objectid)
	{
		new Float:o_pos[3];
		GetObjectPos(objectid,o_pos[0],o_pos[1],o_pos[2]);
		return o_pos[2];
	}

	stock Float:objectRotX(objectid)
	{
		new Float:r_pos[3];
		GetObjectRot(objectid,r_pos[0],r_pos[1],r_pos[2]);
		return r_pos[0];
	}

	stock Float:objectRotY(objectid)
	{
		new Float:r_pos[3];
		GetObjectRot(objectid,r_pos[0],r_pos[1],r_pos[2]);
		return r_pos[1];
	}

	stock Float:objectRotZ(objectid)
	{
		new Float:r_pos[3];
		GetObjectRot(objectid,r_pos[0],r_pos[1],r_pos[2]);
		return r_pos[2];
	}

	stock Float:vehicleX(vehicleid)
	{
		new Float:v_pos[3];
		GetVehiclePos(vehicleid,v_pos[0],v_pos[1],v_pos[2]);
		return v_pos[0];
	}

	stock Float:vehicleY(vehicleid)
	{
		new Float:v_pos[3];
		GetVehiclePos(vehicleid,v_pos[0],v_pos[1],v_pos[2]);
		return v_pos[1];
	}

	stock Float:vehicleZ(vehicleid)
	{
		new Float:v_pos[3];
		GetVehiclePos(vehicleid,v_pos[0],v_pos[1],v_pos[2]);
		return v_pos[2];
	}

	stock Float:playerObjectPosX(playerid,objectid)
	{
		new Float:o_pos[3];
		GetPlayerObjectPos(playerid,objectid,o_pos[0],o_pos[1],o_pos[2]);
		return o_pos[0];
	}

	stock Float:playerObjectPosY(playerid,objectid)
	{
		new Float:o_pos[3];
		GetPlayerObjectPos(playerid,objectid,o_pos[0],o_pos[1],o_pos[2]);
		return o_pos[1];
	}

	stock Float:playerObjectPosZ(playerid,objectid)
	{
		new Float:o_pos[3];
		GetPlayerObjectPos(playerid,objectid,o_pos[0],o_pos[1],o_pos[2]);
		return o_pos[2];
	}

	stock Float:playerObjectRotX(playerid,objectid)
	{
		new Float:r_pos[3];
		GetPlayerObjectRot(playerid,objectid,r_pos[0],r_pos[1],r_pos[2]);
		return r_pos[0];
	}

	stock Float:playerObjectRotY(playerid,objectid)
	{
		new Float:r_pos[3];
		GetPlayerObjectRot(playerid,objectid,r_pos[0],r_pos[1],r_pos[2]);
		return r_pos[1];
	}

	stock Float:playerObjectRotZ(playerid,objectid)
	{
		new Float:r_pos[3];
		GetPlayerObjectRot(playerid,objectid,r_pos[0],r_pos[1],r_pos[2]);
		return r_pos[2];
	}
#endif

#if CODE_MODE_3
	#define oPos(%1) GetObjectPos(%1)
	#define oRot(%1) GetObjectRot(%1)
	#define pAmmo(%1) GetPlayerAmmo(%1)
	#define pColor(%1) GetPlayerColor(%1)
	#define pInterior(%1) GetPlayerInterior(%1)
	#define pKeys(%1) GetPlayerKeys(%1) //pity
	#define pMenu(%1) GetPlayerMenu(%1)
	#define pMoney(%1) GetPlayerMoney(%1)
	#define pObjectPos(%1) GetPlayerObjectPos(%1)
	#define pObjectRot(%1) GetPlayerObjectRot(%1)
	#define pPing(%1) GetPlayerPing(%1)
	#define pPos(%1) GetPlayerPos(%1)
	#define pScore(%1) GetPlayerScore(%1)
	#define pSkin(%1) GetPlayerSkin(%1)
	#define pSpecialAction(%1) GetPlayerSpecialAction(%1)
	#define pState(%1) GetPlayerState(%1)
	#define pTeam(%1) GetPlayerTeam(%1)
	#define pTime(%1) GetPlayerTime(%1)
	#define pVehicleID(%1) GetPlayerVehicleID(%1)
	#define pVirtualWorld(%1) GetPlayerVirtualWorld(%1)
	#define pWantedLevel(%1) GetPlayerWantedLevel(%1)
	#define pWeapon(%1) GetPlayerWeapon(%1)
	#define pWeaponData(%1) GetPlayerWeaponData(%1)
	#define tCount(%1) GetTickCount(%1)
	#define vModel(%1) GetVehicleModel(%1)
	#define vPos(%1) GetVehiclePos(%1)
	#define vTrailer(%1) GetVehicleTrailer(%1)
	#define vVirtualWorld(%1) GetVehicleVirtualWorld(%1)

	/*forward Float:pAngle(playerid);
	forward Float:pHealth(playerid);
	forward Float:pArmour(playerid);
	forward pIP(playerid);
	forward pName(playerid);
	forward Float:vHealth(vehicleid);
	forward Float:vAngle(vehicleid);
	forward wName(weaponid);
	forward Float:pX(playerid);
	forward Float:pY(playerid);
	forward Float:pZ(playerid);
	forward Float:oX(objectid);
	forward Float:oY(objectid);
	forward Float:oZ(objectid);
	forward Float:oRotX(objectid);
	forward Float:oRotY(objectid);
	forward Float:oRotZ(objectid);
	forward Float:vX(vehicleid);
	forward Float:vY(vehicleid);
	forward Float:vZ(vehicleid);
	forward Float:pObjectPosX(playerid,objectid);
	forward Float:pObjectPosY(playerid,objectid);
	forward Float:pObjectPosZ(playerid,objectid);
	forward Float:pObjectRotX(playerid,objectid);
	forward Float:pObjectRotY(playerid,objectid);
	forward Float:pObjectRotZ(playerid,objectid);*/

	stock Float:pAngle(playerid)
	{
		new Float:Angle;
		GetPlayerFacingAngle(playerid, Angle);
		return Angle;
	}

	stock Float:pHealth(playerid)
	{
	    new Float:Health;
	    GetPlayerHealth(playerid, Health);
	    return Health;
	}

	stock Float:pArmour(playerid)
	{
	    new Float:Armour;
	    GetPlayerArmour(playerid, Armour);
	    return Armour;
	}

	stock pIP(playerid)
	{
		new PIP[16];
		GetPlayerIp(playerid,PIP, sizeof(PIP));
		return PIP;
	}

	stock pName(playerid)
	{
		new PN[MAX_PLAYER_NAME];
		GetPlayerName(playerid, PN, sizeof(PN));
		return PN;
	}

	stock Float:vHealth(vehicleid)
	{
	    new Float:health;
	    GetVehicleHealth(vehicleid, health);
	    return health;
	}

	stock Float:vAngle(vehicleid)
	{
		new Float:angle;
	    GetVehicleZAngle(vehicleid, angle);
		return angle;
	}

	stock wName(weaponid)
	{
	    new weaName[65];
	    GetWeaponName(weaponid, weaName, sizeof(weaName));
	    return weaName;
	}

	stock Float:pX(playerid)
	{
		new Float:p_pos[3];
		GetPlayerPos(playerid,p_pos[0],p_pos[1],p_pos[2]);
		return p_pos[0];
	}

	stock Float:pY(playerid)
	{
		new Float:p_pos[3];
		GetPlayerPos(playerid,p_pos[0],p_pos[1],p_pos[2]);
		return p_pos[1];
	}

	stock Float:pZ(playerid)
	{
		new Float:p_pos[3];
		GetPlayerPos(playerid,p_pos[0],p_pos[1],p_pos[2]);
		return p_pos[2];
	}

	stock Float:oX(objectid)
	{
		new Float:o_pos[3];
		GetObjectPos(objectid,o_pos[0],o_pos[1],o_pos[2]);
		return o_pos[0];
	}

	stock Float:oY(objectid)
	{
		new Float:o_pos[3];
		GetObjectPos(objectid,o_pos[0],o_pos[1],o_pos[2]);
		return o_pos[1];
	}

	stock Float:oZ(objectid)
	{
		new Float:o_pos[3];
		GetObjectPos(objectid,o_pos[0],o_pos[1],o_pos[2]);
		return o_pos[2];
	}

	stock Float:oRotX(objectid)
	{
		new Float:r_pos[3];
		GetObjectRot(objectid,r_pos[0],r_pos[1],r_pos[2]);
		return r_pos[0];
	}

	stock Float:oRotY(objectid)
	{
		new Float:r_pos[3];
		GetObjectRot(objectid,r_pos[0],r_pos[1],r_pos[2]);
		return r_pos[1];
	}

	stock Float:oRotZ(objectid)
	{
		new Float:r_pos[3];
		GetObjectRot(objectid,r_pos[0],r_pos[1],r_pos[2]);
		return r_pos[2];
	}

	stock Float:vX(vehicleid)
	{
		new Float:v_pos[3];
		GetVehiclePos(vehicleid,v_pos[0],v_pos[1],v_pos[2]);
		return v_pos[0];
	}

	stock Float:vY(vehicleid)
	{
		new Float:v_pos[3];
		GetVehiclePos(vehicleid,v_pos[0],v_pos[1],v_pos[2]);
		return v_pos[1];
	}

	stock Float:vZ(vehicleid)
	{
		new Float:v_pos[3];
		GetVehiclePos(vehicleid,v_pos[0],v_pos[1],v_pos[2]);
		return v_pos[2];
	}

	stock Float:pObjectPosX(playerid,objectid)
	{
		new Float:o_pos[3];
		GetPlayerObjectPos(playerid,objectid,o_pos[0],o_pos[1],o_pos[2]);
		return o_pos[0];
	}

	stock Float:pObjectPosY(playerid,objectid)
	{
		new Float:o_pos[3];
		GetPlayerObjectPos(playerid,objectid,o_pos[0],o_pos[1],o_pos[2]);
		return o_pos[1];
	}

	stock Float:pObjectPosZ(playerid,objectid)
	{
		new Float:o_pos[3];
		GetPlayerObjectPos(playerid,objectid,o_pos[0],o_pos[1],o_pos[2]);
		return o_pos[2];
	}

	stock Float:pObjectRotX(playerid,objectid)
	{
		new Float:r_pos[3];
		GetPlayerObjectRot(playerid,objectid,r_pos[0],r_pos[1],r_pos[2]);
		return r_pos[0];
	}

	stock Float:pObjectRotY(playerid,objectid)
	{
		new Float:r_pos[3];
		GetPlayerObjectRot(playerid,objectid,r_pos[0],r_pos[1],r_pos[2]);
		return r_pos[1];
	}

	stock Float:pObjectRotZ(playerid,objectid)
	{
		new Float:r_pos[3];
		GetPlayerObjectRot(playerid,objectid,r_pos[0],r_pos[1],r_pos[2]);
		return r_pos[2];
	}
#endif

//EOF
