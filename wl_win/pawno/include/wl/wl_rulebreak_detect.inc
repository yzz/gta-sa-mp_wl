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



#define WL_RULEOP_TICK_PREFIX			(100+GetPlayerPing(playerid)*2)
#define WL_RULEOP_CHECK_ITTER			(81)


#define WL_RULEOP_HEALTH_CHECK			(true)
#define WL_RULEOP_ARMOUR_CHECK			(true)
#define WL_RULEOP_TELEPORT_CHECK		(true)
#define WL_RULEOP_DMW_WEAPON_CHECK		(true)
#define WL_RULEOP_DMW_SPEEDHACK_CHECK	(true)

//forward Float:wl_getDisBetweenPoints(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2);
Float:wl_getDisBetweenPoints(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2){ 
	//debug_public_track("Float:wl_getDisBetweenPoints(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2){");
    new 
		Float:x, Float:y, Float:z;
    x = x1-x2;
    y = y1-y2;
    z = z1-z2;
    return Float:floatsqroot(x*x+y*y+z*z);
}

#if WL_RULEOP_HEALTH_CHECK
#define WL_RULEOP_HPSET_TICK			(1000)
stock ruleop_SetPlayerHealth(playerid,Float:health){
	new
		Float:hp;
	GetPlayerHealth(playerid,hp);
	
	SetPVarInt(playerid,"wl_ruleop_pHealth_settick",GetTickCount());
	SetPVarFloat(playerid,"wl_ruleop_pHealth_preset",((hp > health)?hp:health));
	
	return SetPlayerHealth(playerid,health);
}	
#define SetPlayerHealth(%1) ruleop_SetPlayerHealth(%1)
#endif

#if WL_RULEOP_ARMOUR_CHECK
#define WL_RULEOP_ARMOURSET_TICK		(1000)
stock ruleop_SetPlayerArmour(playerid,Float:armour){
	new
		Float:ar;
	GetPlayerArmour(playerid,ar);
	
	SetPVarInt(playerid,"wl_ruleop_pArmour_settick",GetTickCount());
	SetPVarFloat(playerid,"wl_ruleop_pArmour_preset",((ar > armour)?ar:armour));
	
	return SetPlayerArmour(playerid,armour);
}	
#define SetPlayerArmour(%1) ruleop_SetPlayerArmour(%1)
#endif

#if WL_RULEOP_TELEPORT_CHECK
#define WL_RULEOP_TELEPORT_TICK				(1000)
#define WL_RULEOP_TELEPORT_CHECK_RANGE		(400.0)
stock ruleop_SetPlayerPos(playerid,Float:x,Float:y,Float:z){
	//print "checkEx"
	SetPVarInt(playerid,"wl_ruleop_pPos_settick",GetTickCount());
	SetPVarFloat(playerid,"wl_ruleop_pPosx_preset",x);
	SetPVarFloat(playerid,"wl_ruleop_pPosy_preset",y);
	SetPVarFloat(playerid,"wl_ruleop_pPosz_preset",z);
	return SetPlayerPos(playerid,x,y,z);
}
#define SetPlayerPos(%1) ruleop_SetPlayerPos(%1)
//stock ruleop_test(playerid,Float:x,Float:y,Float:z){ return true;}
//#define ruleop_SetPlayerPos(%1) ruleop_test(%1)
stock ruleop_SetVehiclePos(vehicleid,Float:x,Float:y,Float:z){
	for(new playerid;playerid < MAX_PLAYERS;playerid++){
		if(IsPlayerConnected(playerid)){
			if(GetPlayerVehicleID(playerid) == vehicleid){
				SetPVarInt(playerid,"wl_ruleop_pPos_settick",GetTickCount());
				SetPVarFloat(playerid,"wl_ruleop_pPosx_preset",x);
				SetPVarFloat(playerid,"wl_ruleop_pPosy_preset",y);
				SetPVarFloat(playerid,"wl_ruleop_pPosz_preset",z);
			}
		}
	}
	return SetVehiclePos(vehicleid,x,y,z);
}
#define SetVehiclePos(%1) ruleop_SetVehiclePos(%1)

#endif


detect_playerSpawn(playerid){
	SetPVarInt(playerid,"wl_ruleop_pPos_settick",GetTickCount());
}

detect_PlayerUpdate(playerid){
	
	//===============avearge check times========================
	{
		static
			wl_ruleop_oldtick[MAX_PLAYERS];
		if(wl_ruleop_oldtick[playerid]){
			if(GetTickCount() - wl_ruleop_oldtick[playerid] > WL_RULEOP_CHECK_ITTER){
				wl_ruleop_oldtick[playerid] = 0;
				//can start process
			}
			else if(GetTickCount() - wl_ruleop_oldtick[playerid] > 10000){ //player disconnect,pasued,lagged
				wl_ruleop_oldtick[playerid] = GetTickCount();
			}
			else {
				return true;
			}
		}
		else {
			wl_ruleop_oldtick[playerid] = GetTickCount();
			return true;
		}
	}
	//==========================================================//
	#if WL_RULEOP_HEALTH_CHECK
	{
		new
			healthtick = GetPVarInt(playerid,"wl_ruleop_pHealth_settick"),
			Float:health,
			Float:healthEx = GetPVarFloat(playerid,"wl_ruleop_pHealth_preset");
		GetPlayerHealth(playerid,health);
		if(!healthtick){
			if(health > healthEx+1 && health >= 1){
				/*
				static
					ruleop_healthLocation[][4]	=	{ //x y z range
						{ 0,0,0,0}
					};
				new
					Float:px,Float:py,Float:pz;
				GetPlayerPos(playerid,px,py,pz);
				*/
				//todo if()
				CallLocalFunction("wl_ruleop_PossibleCheat","is",playerid,"Health Hack");
				SetPVarFloat(playerid,"wl_ruleop_pHealth_preset",health);
				return true;
			}
			SetPVarFloat(playerid,"wl_ruleop_pHealth_preset",health);
		}
		if(healthtick){
			if(GetTickCount()-healthtick > WL_RULEOP_HPSET_TICK+WL_RULEOP_TICK_PREFIX){
				SetPVarInt(playerid,"wl_ruleop_pHealth_settick",0);
				SetPVarFloat(playerid,"wl_ruleop_pHealth_preset",health);
			}
		}
	}
	#endif
	//===========================================================
	#if WL_RULEOP_ARMOUR_CHECK
	{
		new
			armourtick = GetPVarInt(playerid,"wl_ruleop_pArmour_settick"),
			Float:armour,
			Float:armourEx = GetPVarFloat(playerid,"wl_ruleop_pArmour_preset");
		GetPlayerArmour(playerid,armour);
		if(!armourtick){
			if(armour > armourEx+1 && armour >= 1){
				/*
				static
					ruleop_armourLocation[][4]	=	{ //x y z range
						{ 0,0,0,0}
					};
				new
					Float:px,Float:py,Float:pz;
				GetPlayerPos(playerid,px,py,pz);
				*/
				//todo if()
				CallLocalFunction("wl_ruleop_PossibleCheat","is",playerid,"Armour Hack");
				SetPVarFloat(playerid,"wl_ruleop_pArmour_preset",armour);
				return true;
			}
			SetPVarFloat(playerid,"wl_ruleop_pArmour_preset",armour);
		}
		if(armourtick){
			if(GetTickCount()-armourtick > WL_RULEOP_ARMOURSET_TICK+WL_RULEOP_TICK_PREFIX){
				SetPVarInt(playerid,"wl_ruleop_pArmour_settick",0);
				SetPVarFloat(playerid,"wl_ruleop_pArmour_preset",armour);
			}
		}
	}
	#endif
	#if WL_RULEOP_TELEPORT_CHECK
	{
		new
			teleporttick = GetPVarInt(playerid,"wl_ruleop_pPos_settick"),
			Float:px,Float:py,Float:pz;
		GetPlayerPos(playerid,px,py,pz);
		if(!teleporttick){
			new
				Float:distance = wl_getDisBetweenPoints(px,py,pz,GetPVarFloat(playerid,"wl_ruleop_pPosx_preset"),GetPVarFloat(playerid,"wl_ruleop_pPosy_preset"),GetPVarFloat(playerid,"wl_ruleop_pPosz_preset"));
			//printf("distance %.2f overdis:%.2f",distance,WL_RULEOP_TELEPORT_CHECK_RANGE);
			//System_sendAll("distance %.2f limit:%.2f",distance,WL_RULEOP_TELEPORT_CHECK_RANGE);
			if(distance > WL_RULEOP_TELEPORT_CHECK_RANGE){
				static
					Float:ruleop_teleportLocation[][6]	=	{ //x y z range
						{ 1574.5638,-1332.7548,16.4844,1545.7561,-1366.6320,326.5773},
						{ 1545.7561,-1366.6320,326.5773,1574.5638,-1332.7548,16.4844}
					};
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT || GetPlayerState(playerid) == PLAYER_STATE_DRIVER ){
					
					new
						confirmed = true;
					for(new i, j = sizeof(ruleop_teleportLocation),Float:cp[9]; i < j; i++){
						for(new k;k < 6;k++){
							cp[k] = ruleop_teleportLocation[i][k];
						}
						cp[6] = GetPVarFloat(playerid,"wl_ruleop_pPosx_preset");
						cp[7] = GetPVarFloat(playerid,"wl_ruleop_pPosy_preset");
						cp[8] = GetPVarFloat(playerid,"wl_ruleop_pPosz_preset");
						if(PointToPoint(px,py,pz,cp[0],cp[1],cp[2],20.0) && PointToPoint(cp[6],cp[7],cp[8],cp[3],cp[4],cp[5],20.0)){
							confirmed = false;
							break;
						}
					}
					if(confirmed){
						CallLocalFunction("wl_ruleop_PossibleCheat","is",playerid,"Teleport Hack");
					}
					
					SetPVarFloat(playerid,"wl_ruleop_pPosx_preset",px);
					SetPVarFloat(playerid,"wl_ruleop_pPosy_preset",py);
					SetPVarFloat(playerid,"wl_ruleop_pPosz_preset",pz);
					return true;
				}
			}
			SetPVarFloat(playerid,"wl_ruleop_pPosx_preset",px);
			SetPVarFloat(playerid,"wl_ruleop_pPosy_preset",py);
			SetPVarFloat(playerid,"wl_ruleop_pPosz_preset",pz);
		}
		if(teleporttick){
			//print "check"
			if(GetTickCount()-teleporttick > WL_RULEOP_TELEPORT_TICK+WL_RULEOP_TICK_PREFIX){
				SetPVarInt(playerid,"wl_ruleop_pPos_settick",0);
				SetPVarFloat(playerid,"wl_ruleop_pPosx_preset",px);
				SetPVarFloat(playerid,"wl_ruleop_pPosy_preset",py);
				SetPVarFloat(playerid,"wl_ruleop_pPosz_preset",pz);
			}
		}
	}
	#endif
	//=======================================================================
	#if WL_RULEOP_DMW_WEAPON_CHECK
	{
		if(CallLocalFunction("dmw_getPlayer","i",playerid)){
			new
				slotid = Weapon_getSlotfromID(GetPlayerWeapon(playerid)),
				weaponid,ammo;
			
			GetPlayerWeaponData(playerid,slotid,weaponid,ammo);
			
			//System_sendAll("%d %d %d %d |%d %d",playerid,slotid,weaponid,ammo,GetGVarInt("wl_dmw_pweapon_weaponid",getDoubleRelationList(playerid,slotid)),GetGVarInt("wl_dmw_pweapon_ammo",getDoubleRelationList(playerid,slotid)));
			if(weaponid){
				if(weaponid != GetGVarInt("wl_dmw_pweapon_weaponid",getDoubleRelationList(playerid,slotid))){
					if(weaponid != WEAPON_PARACHUTE && weaponid != WEAPON_BOMB){ //apart from parachute,bomb
						SetGVarInt("wl_dmw_pweapon_weaponid",weaponid,getDoubleRelationList(playerid,slotid));
						CallLocalFunction("wl_ruleop_PossibleCheat","is",playerid,"Weapon Hack in DMworld");
					}
				}
				else if(ammo >= 1){
					if(ammo > GetGVarInt("wl_dmw_pweapon_ammo",getDoubleRelationList(playerid,slotid))){
						CallLocalFunction("wl_ruleop_PossibleCheat","is",playerid,"Weapon Hack in DMworld");
					}
				}
				else if(ammo < 0){
					CallLocalFunction("wl_ruleop_PossibleCheat","is",playerid,"Possible Weapon Hack in DMworld");
				}
			}
			SetGVarInt("wl_dmw_pweapon_ammo",ammo,getDoubleRelationList(playerid,slotid));
		}
	}
	#endif
	
	#if WL_RULEOP_DMW_SPEEDHACK_CHECK
	{
		if(CallLocalFunction("dmw_getPlayer","i",playerid)){
			if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
				new
					Float:speed,
					Float:x2,Float:y2,Float:z2;
				GetVehicleVelocity(GetPlayerVehicleID(playerid),x2,y2,z2);	
				if(z2 < -0.4)z2 = -0.4;
				speed = (x2*100*x2*100+y2*100*y2*100+z2*100*z2*100);
				if(speed > 25000){ //hydra speed://22500
					CallLocalFunction("wl_ruleop_PossibleCheat","is",playerid,"Possible Speed Hack in DMworld");
				}
				
			}
		}
	}
	#endif
	return true;
}
			








