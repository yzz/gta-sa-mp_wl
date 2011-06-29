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
	wl_mode_dmWorld_inworld								integer -
	wl_mode_dmWorld_times_knife							integer	-
	wl_mode_dmWorld_times_chainsaw						integer	-
	wl_mode_dmWorld_times_grenade						integer	-
	wl_mode_dmWorld_times_teargas						integer	-
	wl_mode_dmWorld_times_moltov						integer	-
	wl_mode_dmWorld_times_colt45						integer	-
	wl_mode_dmWorld_times_silenced						integer	-
	wl_mode_dmWorld_times_deagle						integer	-
	wl_mode_dmWorld_times_shotgun						integer	-
	wl_mode_dmWorld_times_sawedoff						integer	-
	wl_mode_dmWorld_times_shotgspa						integer	-
	wl_mode_dmWorld_times_uzi							integer	-
	wl_mode_dmWorld_times_mp5							integer	-
	wl_mode_dmWorld_times_ak47							integer	-
	wl_mode_dmWorld_times_m4							integer	-
	wl_mode_dmWorld_times_tec9							integer	-
	wl_mode_dmWorld_times_rifle							integer	-
	wl_mode_dmWorld_times_flamethrower					integer	-
	wl_mode_dmWorld_times_minigun						integer	-
	wl_mode_dmWorld_times_satchel						integer	-
	wl_mode_dmWorld_times_bomb							integer	-
	wl_mode_dmWorld_times_spraycan						integer	-
	wl_mode_dmWorld_times_fireextinguisher				integer	-
	wl_mode_dmWorld_times_sniper						integer	-
	wl_mode_dmWorld_times_rocketlauncher				integer	-
	wl_mode_dmWorld_times_heatseeker					integer	-
	wl_mode_dmWorld_pOldWeapon_byKeyState				integer	-
	wl_mode_dmWorld_pOldAmmo_byKeyState					integer	-
	wl_mode_dmWorld_pDefencehp							float	-
	wl_mode_dmWorld_times_passengershoot				integer	-
	wl_mode_dmWorld_inAmmoCheck							integer	-
*/

//==============================
//  1second = 36times
//==============================
forward DMWorld_countHP();
public DMWorld_countHP(){ debug_public_track("DMWorld_countHP(){");
	loopPlayer(playerid){
		if(dmw_getPlayer(playerid)){
			new
				Float:decreasehp,
				times_knife = GetPVarInt(playerid,"wl_mode_dmWorld_times_knife"),
				times_chainsaw = GetPVarInt(playerid,"wl_mode_dmWorld_times_chainsaw"),
				times_grenade = GetPVarInt(playerid,"wl_mode_dmWorld_times_grenade"),
				times_teargas = GetPVarInt(playerid,"wl_mode_dmWorld_times_teargas"),
				times_moltov = GetPVarInt(playerid,"wl_mode_dmWorld_times_moltov"),
				times_colt45 = GetPVarInt(playerid,"wl_mode_dmWorld_times_colt45"),
				times_silenced = GetPVarInt(playerid,"wl_mode_dmWorld_times_silenced"),
				times_deagle = GetPVarInt(playerid,"wl_mode_dmWorld_times_deagle"),
				times_shotgun = GetPVarInt(playerid,"wl_mode_dmWorld_times_shotgun"),
				times_sawedoff = GetPVarInt(playerid,"wl_mode_dmWorld_times_sawedoff"),
				times_shotgspa = GetPVarInt(playerid,"wl_mode_dmWorld_times_shotgspa"),
				times_uzi = GetPVarInt(playerid,"wl_mode_dmWorld_times_uzi"),
				times_mp5 = GetPVarInt(playerid,"wl_mode_dmWorld_times_mp5"),
				times_ak47 = GetPVarInt(playerid,"wl_mode_dmWorld_times_ak47"),
				times_m4 = GetPVarInt(playerid,"wl_mode_dmWorld_times_m4"),
				times_tec9 = GetPVarInt(playerid,"wl_mode_dmWorld_times_tec9"),
				times_rifle = GetPVarInt(playerid,"wl_mode_dmWorld_times_rifle"),
				times_flamethrower = GetPVarInt(playerid,"wl_mode_dmWorld_times_flamethrower"),
				times_minigun = GetPVarInt(playerid,"wl_mode_dmWorld_times_minigun"),
				times_satchel = GetPVarInt(playerid,"wl_mode_dmWorld_times_satchel"),
				times_bomb = GetPVarInt(playerid,"wl_mode_dmWorld_times_bomb"),
				times_spraycan = GetPVarInt(playerid,"wl_mode_dmWorld_times_spraycan"),
				times_fireextinguisher = GetPVarInt(playerid,"wl_mode_dmWorld_times_fireextinguisher"),
				times_sniper = GetPVarInt(playerid,"wl_mode_dmWorld_times_sniper"),
				times_rocketlauncher = GetPVarInt(playerid,"wl_mode_dmWorld_times_rocketlauncher"),
				times_heatseeker = GetPVarInt(playerid,"wl_mode_dmWorld_times_heatseeker");

			if(times_knife){
				decreasehp += sd_knife;
			}
			if(times_chainsaw){
				decreasehp += (times_chainsaw)*sd_chainsaw/18;
			}
			if(times_grenade){
				decreasehp += (times_grenade > 6)?(2*sd_grenade):(1*sd_grenade);
				//decreasehp += (1+times_grenade/18)*sd_grenade;
			}
			if(times_teargas){
				decreasehp += (times_teargas > 6)?(2*sd_teargas):(1*sd_teargas);
				//decreasehp += (1+times_teargas/18)*sd_teargas;
			}
			if(times_moltov){
				decreasehp += (times_moltov > 6)?(2*sd_moltov):(1*sd_moltov);
				//decreasehp += (1+times_moltov/18)*sd_moltov;
			}
			if(times_colt45){
				decreasehp += (times_colt45)*sd_colt45/18;
			}
			if(times_silenced){
				decreasehp += (times_silenced)*sd_silenced/18;
			}
			if(times_deagle){
				decreasehp += (times_deagle)*sd_deagle/18;
			}
			if(times_shotgun){
				decreasehp += (times_shotgun > 6)?(2*sd_shotgun):(1*sd_shotgun);
				//decreasehp += (1+times_shotgun/5)*sd_shotgun;
			}
			if(times_sawedoff){
				decreasehp += (times_sawedoff)*sd_sawedoff/18;
			}
			if(times_shotgspa){
				decreasehp += (times_shotgspa)*sd_shotgspa/18;
			}
			if(times_uzi){
				decreasehp += (times_uzi)*sd_uzi/18;
			}
			if(times_mp5){
				decreasehp += (times_mp5)*(sd_mp5/18);
			}
			if(times_ak47){
				decreasehp += (times_ak47)*(sd_ak47/18);
			}
			if(times_m4){
				decreasehp += (times_m4)*sd_m4/18;
			}
			if(times_tec9){
				decreasehp += (times_tec9)*sd_tec9/18;
			}
			if(times_rifle){
				decreasehp += (times_rifle > 6)?(2*sd_rifle):(1*sd_rifle);
				//decreasehp += (1+times_rifle/5)*sd_rifle;
			}
			if(times_flamethrower){
				decreasehp += (times_flamethrower)*sd_flamethrower/18;
			}
			if(times_minigun){
				decreasehp += (times_minigun)*sd_minigun/18;
			}
			if(times_satchel){
				decreasehp += (times_satchel > 6)?(2*sd_satchel):(1*sd_satchel);
				//decreasehp += (times_satchel)*sd_satchel;
			}
			if(times_bomb){
				decreasehp += (times_bomb)*sd_bomb/18;
			}
			if(times_spraycan){
				decreasehp += (times_spraycan)*sd_spraycan/18;
			}
			if(times_fireextinguisher){
				decreasehp += (times_fireextinguisher)*sd_fireextinguisher/18;
			}
			if(times_sniper){
				decreasehp += (times_sniper > 6)?(2*sd_sniper):(1*sd_sniper);
				//decreasehp += (times_sniper*18)*sd_sniper;
			}
			if(times_rocketlauncher){
				decreasehp += (times_rocketlauncher > 6)?(2*sd_rocketlauncher):(1*sd_rocketlauncher);
				//decreasehp += (1+times_rocketlauncher/8)*sd_rocketlauncher;
			}
			if(times_heatseeker){
				decreasehp += (times_heatseeker > 6)?(2*sd_heatseeker):(1*sd_heatseeker);
				//decreasehp += (1+times_heatseeker/8)*sd_heatseeker;
			}
			if(decreasehp != 0 && decreasehp < 0.5) decreasehp = 0.5;
			//if(decreasehp != 0)System_send(playerid,"你扣了 %.5f hp",decreasehp);
			SetPlayerHealth(playerid,pHealth(playerid)-decreasehp);
		
			SetPVarInt(playerid,"wl_mode_dmWorld_times_knife",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_chainsaw",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_grenade",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_teargas",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_moltov",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_colt45",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_silenced",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_deagle",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_shotgun",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_sawedoff",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_shotgspa",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_uzi",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_mp5",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_ak47",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_m4",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_tec9",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_rifle",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_flamethrower",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_minigun",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_satchel",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_bomb",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_spraycan",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_fireextinguisher",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_sniper",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_rocketlauncher",0);
			SetPVarInt(playerid,"wl_mode_dmWorld_times_heatseeker",0);
		}
	}
	return true;
}
			
				
				

forward DMWorld_countByKeyState();
public DMWorld_countByKeyState(){ debug_public_track("DMWorld_countByKeyState(){");
	#define holdingEx(%0) ((keys & (%0)) == (%0))
	loopPlayer(playerid){
		if(dmw_getPlayer(playerid)){	
			new
				keys,updown,leftright,
				weaponid 	= GetPlayerWeapon(playerid),
				//ammo 		= GetPlayerAmmo(playerid),
				//oldweaponid = GetPVarInt(playerid,"wl_mode_dmWorld_pOldWeapon_byKeyState"),
				//oldammo 	= GetPVarInt(playerid,"wl_mode_dmWorld_pOldAmmo_byKeyState"),
				Float:hp;//Float:decreasehp;
			GetPlayerHealth(playerid,hp);
			GetPlayerKeys(playerid,keys,updown,leftright);
			/*
			if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT){
				if((keys == (KEY_JUMP | KEY_HANDBRAKE))){
					if(IsFeleeWeapon(weaponid)){
						new
							Float:defencehp = GetPVarFloat(playerid,"wl_mode_dmWorld_pDefencehp");
						if(defencehp >= 1){
							SetPlayerHealth(playerid,defencehp - 0.3);
							SetPVarFloat(playerid,"wl_mode_dmWorld_pDefencehp",defencehp - 0.1);
						}
						else {
							SetPVarFloat(playerid,"wl_mode_dmWorld_pDefencehp",hp);
						}
					}
				}
				else {
					SetPVarFloat(playerid,"wl_mode_dmWorld_pDefencehp",0.0);
				}
			}
			*/
			if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT || GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK){
				if(holdingEx(KEY_FIRE)){	
					switch(weaponid){
						case WEAPON_CHAINSAW:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_chainsaw",GetPVarInt(playerid,"wl_mode_dmWorld_times_chainsaw")+1);
						case WEAPON_GRENADE:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_grenade",GetPVarInt(playerid,"wl_mode_dmWorld_times_grenade")+1);
						case WEAPON_TEARGAS:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_teargas",GetPVarInt(playerid,"wl_mode_dmWorld_times_teargas")+1);
						case WEAPON_MOLTOV:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_moltov",GetPVarInt(playerid,"wl_mode_dmWorld_times_moltov")+1);
						case WEAPON_COLT45:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_colt45",GetPVarInt(playerid,"wl_mode_dmWorld_times_colt45")+1);
						case WEAPON_SILENCED:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_silenced",GetPVarInt(playerid,"wl_mode_dmWorld_times_silenced")+1);
						case WEAPON_DEAGLE:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_deagle",GetPVarInt(playerid,"wl_mode_dmWorld_times_deagle")+1);
						case WEAPON_SHOTGUN:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_shotgun",GetPVarInt(playerid,"wl_mode_dmWorld_times_shotgun")+1);
						case WEAPON_SAWEDOFF:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_sawedoff",GetPVarInt(playerid,"wl_mode_dmWorld_times_sawedoff")+1);
						case WEAPON_SHOTGSPA:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_shotgspa",GetPVarInt(playerid,"wl_mode_dmWorld_times_shotgspa")+1);
						case WEAPON_UZI:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_uzi",GetPVarInt(playerid,"wl_mode_dmWorld_times_uzi")+1);
						case WEAPON_MP5:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_mp5",GetPVarInt(playerid,"wl_mode_dmWorld_times_mp5")+1);
						case WEAPON_AK47:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_ak47",GetPVarInt(playerid,"wl_mode_dmWorld_times_ak47")+1);
						case WEAPON_M4:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_m4",GetPVarInt(playerid,"wl_mode_dmWorld_times_m4")+1);
						case WEAPON_TEC9:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_tec9",GetPVarInt(playerid,"wl_mode_dmWorld_times_tec9")+1);
						case WEAPON_RIFLE:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_rifle",GetPVarInt(playerid,"wl_mode_dmWorld_times_rifle")+1);
						case WEAPON_FLAMETHROWER:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_flamethrower",GetPVarInt(playerid,"wl_mode_dmWorld_times_flamethrower")+1);
						case WEAPON_MINIGUN:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_minigun",GetPVarInt(playerid,"wl_mode_dmWorld_times_minigun")+1);
						case WEAPON_SATCHEL:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_satchel",GetPVarInt(playerid,"wl_mode_dmWorld_times_satchel")+1);
						case WEAPON_BOMB:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_bomb",GetPVarInt(playerid,"wl_mode_dmWorld_times_bomb")+1);
						case WEAPON_SPRAYCAN:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_spraycan",GetPVarInt(playerid,"wl_mode_dmWorld_times_spraycan")+1);
						case WEAPON_FIREEXTINGUISHER:
							SetPVarInt(playerid,"wl_mode_dmWorld_times_fireextinguisher",GetPVarInt(playerid,"wl_mode_dmWorld_times_fireextinguisher")+1);
					}
					if((holdingEx(KEY_FIRE | KEY_HANDBRAKE))){
						switch(weaponid){
							case WEAPON_KNIFE:
								SetPVarInt(playerid,"wl_mode_dmWorld_times_knife",GetPVarInt(playerid,"wl_mode_dmWorld_times_knife")+1);	
							case WEAPON_SNIPER:
								SetPVarInt(playerid,"wl_mode_dmWorld_times_sniper",GetPVarInt(playerid,"wl_mode_dmWorld_times_sniper")+1);			
							case WEAPON_ROCKETLAUNCHER:
								SetPVarInt(playerid,"wl_mode_dmWorld_times_rocketlauncher",GetPVarInt(playerid,"wl_mode_dmWorld_times_rocketlauncher")+1);
							case WEAPON_HEATSEEKER:
								SetPVarInt(playerid,"wl_mode_dmWorld_times_heatseeker",GetPVarInt(playerid,"wl_mode_dmWorld_times_heatseeker")+1);
						}
					}				
				}	
			}
			else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
				if(IsMotorBike(GetPlayerVehicleID(playerid)) || IsBike(GetPlayerVehicleID(playerid))){
					if(holdingEx(KEY_FIRE) || holdingEx(KEY_ACTION)){
						switch(weaponid){
							case WEAPON_UZI:
								SetPVarInt(playerid,"wl_mode_dmWorld_times_uzi",GetPVarInt(playerid,"wl_mode_dmWorld_times_uzi")+4);
							case WEAPON_MP5:
								SetPVarInt(playerid,"wl_mode_dmWorld_times_mp5",GetPVarInt(playerid,"wl_mode_dmWorld_times_mp5")+4);
							case WEAPON_TEC9:
								SetPVarInt(playerid,"wl_mode_dmWorld_times_tec9",GetPVarInt(playerid,"wl_mode_dmWorld_times_tec9")+4);
						}
					}
				}
				else if(IsShootableByDriverHandVehicle(GetPlayerVehicleID(playerid))){
					if(holdingEx(KEY_FIRE | KEY_LOOK_RIGHT) || holdingEx(KEY_FIRE | KEY_LOOK_LEFT) || holdingEx(KEY_ACTION | KEY_LOOK_RIGHT) || holdingEx(KEY_ACTION | KEY_LOOK_LEFT)){
						switch(weaponid){
							case WEAPON_UZI:
								SetPVarInt(playerid,"wl_mode_dmWorld_times_uzi",GetPVarInt(playerid,"wl_mode_dmWorld_times_uzi")+4);
							case WEAPON_MP5:
								SetPVarInt(playerid,"wl_mode_dmWorld_times_mp5",GetPVarInt(playerid,"wl_mode_dmWorld_times_mp5")+4);
							case WEAPON_TEC9:
								SetPVarInt(playerid,"wl_mode_dmWorld_times_tec9",GetPVarInt(playerid,"wl_mode_dmWorld_times_tec9")+4);
						}
					}
				}
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 447){
					if(holdingEx(KEY_FIRE) || holdingEx(KEY_ACTION)){
						SetPVarInt(playerid,"wl_mode_dmWorld_times_mp5",GetPVarInt(playerid,"wl_mode_dmWorld_times_mp5")+4);
					}
				}
			}
			else if(GetPlayerState(playerid) == PLAYER_STATE_PASSENGER){
				if(IsShootableByPassengerVehicle(GetPlayerVehicleID(playerid))){
					if(holdingEx(KEY_FIRE) || holdingEx(KEY_ACTION)){
						#define DMWORLD_PREFIX_PASSENGER_SHOOT			(5)
						SetPVarInt(playerid,"wl_mode_dmWorld_times_passengershoot",GetPVarInt(playerid,"wl_mode_dmWorld_times_passengershoot")+1);
						switch(weaponid){
							case WEAPON_UZI:
								SetPVarInt(playerid,"wl_mode_dmWorld_times_uzi",GetPVarInt(playerid,"wl_mode_dmWorld_times_uzi")+GetPVarInt(playerid,"wl_mode_dmWorld_times_passengershoot")/DMWORLD_PREFIX_PASSENGER_SHOOT);
							case WEAPON_MP5:
								SetPVarInt(playerid,"wl_mode_dmWorld_times_mp5",GetPVarInt(playerid,"wl_mode_dmWorld_times_mp5")+GetPVarInt(playerid,"wl_mode_dmWorld_times_passengershoot")/DMWORLD_PREFIX_PASSENGER_SHOOT);
							case WEAPON_TEC9:
								SetPVarInt(playerid,"wl_mode_dmWorld_times_tec9",GetPVarInt(playerid,"wl_mode_dmWorld_times_tec9")+GetPVarInt(playerid,"wl_mode_dmWorld_times_passengershoot")/DMWORLD_PREFIX_PASSENGER_SHOOT);
						}
						if(GetPVarInt(playerid,"wl_mode_dmWorld_times_passengershoot") && !(GetPVarInt(playerid,"wl_mode_dmWorld_times_passengershoot")%DMWORLD_PREFIX_PASSENGER_SHOOT)){
							SetPVarInt(playerid,"wl_mode_dmWorld_times_passengershoot",0);
						}
					}
				}
			}
		}	

	}
}

stock IsShootableByPassengerVehicle(vecid){
	new vecidEx[] = {
						403,406,417,425,426,430,431,432,435,436,
						437,441,442,446,447,448,449,450,452,453,
						454,456,460,464,465,469,472,473,476,481,
						484,485,486,487,488,493,497,501,509,510,
						511,512,513,519,520,530,531,532,537,538,
						539,548,553,563,564,568,569,570,571,572,
						574,577,583,584,590,591,592,593,594,595,
						606,607,608,610,611
					};
	for(new i,j = sizeof(vecidEx),k = GetVehicleModel(vecid);i < j;i++){
		if(k == vecidEx[i]){
			return false;
		}
	}
	return true;
}
stock IsFeleeWeapon(weaponid){
	if((weaponid >= 0 && weaponid <= 15) || weaponid == WEAPON_PARACHUTE) return true;
	return false;
}
stock IsShootableByDriverHandVehicle(vecid){
	new vecidEx[] = {
						417,425,432,441,447,460,464,465,469,476,
						487,488,497,501,511,512,513,519,520,537,
						538,548,553,563,564,569,570,577,592,593,
						594,601
					};
	for(new i,j = sizeof(vecidEx),k = GetVehicleModel(vecid);i < j;i++){
		if(k == vecidEx[i]){
			return false;
		}
	}
	return true;
}
stock IsCountableAndDamagedWeapon(weaponid){
	if((weaponid >= 16 && weaponid <= 39) || weaponid == 41 || weaponid == 42) return true;
	return false;
}
