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


stock bool:DM_useHandWeapon(playerid){
	switch(Weapon_getSlotfromID(GetPlayerWeapon(playerid))){
		case 0,1,9,10,11:return true;
		default:return false;
	}
	return false;
}






#include <wl/modes/dm/wl_pdm>
//#include <wl/modes/dm/wl_gdm>
//#include <wl/modes/dm/wl_tdm>





static
	GunDM_Timer;

/*
forward DM_TimerCheck();	



public DM_TimerCheck(){ debug_public_track("DM_TimerCheck(){");
	loopPlayer(playerid){
		if(PDM_getPlayerDM(playerid) != INVALID_PDM_ID){
			
			if(!PDM_isPlayerInPerDMArea(playerid,PDM_getPlayerDM(playerid))){
				PDM_setPlayerToDMArea(playerid,PDM_getPlayerDM(playerid));
				PDM_send(playerid,"[DM]非法离开DM区域，自动传送回 dm");
			}
			
			
			if(!DM_useHandWeapon(playerid) && GetPlayerWeapon(playerid) != WEAPON_TEARGAS && PDM_isPlayeruseInvalidPDMWeapon(playerid,PDM_getPlayerDM(playerid))){
				PDM_outdm_start(playerid)
				GDM_setPlayertoGDM(playerid);
				SetPlayerWorldBounds(playerid,BuyGunArea[2],BuyGunArea[0],BuyGunArea[3],BuyGunArea[1]);
				PDM_send(playerid,"[DM]拥有非法武器,被传送到gdm");
				
			}
			
		}else{
			
			if(GDM_isPlayerInGunDM(playerid)){
				if(GetPlayerVirtualWorld(playerid) != GDM_WORLD){
					//GDM_send(playerid,"[DM]非法离开gun dm区域，自动传送回gun dm");
					//GDM_setPlayertoGDM(playerid);
				}
			}else{
			}			
		}
	}
	return true;
}
*/


wl_mode_DM_Struction(){
	loopPlayerEx(i){
		PDM_setPlayerDM(i,INVALID_PDM_ID);
	}
	for(new i,j = sizeof(wl_n_mode_DMInfo);i<j;i++){
		wl_n_mode_DMInfo[i][E_mode_dm_GangZone] = GangZoneCreate(wl_n_mode_DMInfo[i][E_mode_dm_Area_minx], wl_n_mode_DMInfo[i][E_mode_dm_Area_miny], wl_n_mode_DMInfo[i][E_mode_dm_Area_maxx], wl_n_mode_DMInfo[i][E_mode_dm_Area_maxy]);
	}
}

wl_mode_DM_UnStruction(){
	KillTimer(GunDM_Timer);
}

wl_mode_DM_PlayerSpawn(playerid){
	
	/*
	if(GDM_isPlayerInGunDM(playerid)){
		GDM_setPlayertoGDM(playerid);
		return true;
	}else if
	*/
	if(PDM_getPlayerDM(playerid) != INVALID_PDM_ID){
			PDM_enterdm_start(playerid,PDM_getPlayerDM(playerid));
		return true;
	}
	return false;
}






wl_mode_DM_KeyStateChange(playerid, newkeys, oldkeys){
	#pragma unused playerid,newkeys,oldkeys
	/*
	if((newkeys & KEY_SUBMISSION) && !GDM_allowPlayerSwitchWeapon(playerid)){
		new slotid = Weapon_getSlotfromID(GetPlayerWeapon(playerid));
		if(slotid == 1 && !PDM_isPlayerIn(playerid)){
			GivePlayerWeapon(playerid,GDM_getPlayerSwitchWeapon(playerid,slotid),9999);
			PlayerInfo[playerid][GunDM_PlayerSwitchWeapon][slotid]++;
		}
	}
	if((newkeys & KEY_SUBMISSION) && GDM_allowPlayerSwitchWeapon(playerid)){
		new
			slotid = Weapon_getSlotfromID(GetPlayerWeapon(playerid));
		switch(slotid){
			case 0:{
				new
					Float:tmpfval;
				GetPlayerHealth(playerid,tmpfval);
				GivePlayerWeapon(playerid,WEAPON_PARACHUTE,1);
				if(tmpfval < 99){
					SetPlayerHealth(playerid,100);
				}else
				{
					GetPlayerArmour(playerid,tmpfval);
					if(tmpfval > 99){
						SetPlayerArmour(playerid,0);
					}else
					{
						SetPlayerArmour(playerid,100);
					}
				}
			}
			case 1,2,3,4,5,6,8,9,10,11:{
				GivePlayerWeapon(playerid,GDM_getPlayerSwitchWeapon(playerid,slotid),9999);
				PlayerInfo[playerid][GunDM_PlayerSwitchWeapon][slotid]++;
				//DM_setPlayerSwitchWeapon(playerid,slotid,);
			}
		}
	}
	*/
	return true;
}

wl_mode_DM_CommandText(playerid,cmdtext[]){
	return PDM_playerCommandText(playerid,cmdtext);
}

wl_mode_DM_PlayerConnect(playerid){
	PDM_setPlayerDM(playerid,INVALID_PDM_ID);
	//GDM_setPlayerInGunDM(playerid,false);
}


wl_mode_DM_Disconnect(playerid,reason){
	#pragma unused reason
	//for(new i;i<MAX_WEAPON_SLOT;i++)PlayerInfo[playerid][GunDM_PlayerSwitchWeapon][i] = 0;
	PDM_setPlayerDM(playerid,INVALID_PDM_ID);
	//GDM_setPlayerInGunDM(playerid,false);
	
	wl_sPlr_PDM_PlayerKill(playerid,0);
	wl_sPlr_PDM_PlayerDeath(playerid,0);
}


wl_mode_DM_PlayerDeath(playerid,killerid,reason){
	#pragma unused reason
	
	if(killerid == INVALID_PLAYER_ID){
		if(PDM_getPlayerDM(playerid) != INVALID_PDM_ID){
			wl_sPlr_PDM_PlayerDeath(playerid,wl_gPlr_PDM_PlayerDeath(playerid)+1);
			new
				tmpstr[MAX_STRING];
			format(tmpstr,sizeof(tmpstr),"[PDM]%s(%d杀%d亡)在'%s'自杀身亡",pName(playerid),wl_gPlr_PDM_PlayerKill(playerid),wl_gPlr_PDM_PlayerDeath(playerid),wl_n_mode_DMInfo[PDM_getPlayerDM(playerid)][E_mode_dm_Command_Name]);
			SetPVarInt(playerid,"wl_pdm_dming",false);
			looper(i,0,MAX_PLAYERS,(IsPlayerConnected(i) && (PDM_getPlayerDM(i) != INVALID_PDM_ID))){
				PDM_send(i,tmpstr);
			}
		}
		return true;
	}
	
	
	if((PDM_getPlayerDM(playerid) != INVALID_PDM_ID) && (PDM_getPlayerDM(killerid) != INVALID_PDM_ID)){
		wl_sPlr_PDM_PlayerDeath(playerid,wl_gPlr_PDM_PlayerDeath(playerid)+1);
		wl_sPlr_PDM_PlayerKill(playerid,wl_gPlr_PDM_PlayerKill(playerid)+1);
		SetPlayerHealth(killerid,(pHealth(killerid) > 90)?100.0:(pHealth(killerid)+10));
		new
			tmpstr[MAX_STRING];
		format(tmpstr,sizeof(tmpstr),"[pdm]%s(%d杀%d亡)在'%s'杀了%s(%d杀%d亡)",pName(killerid),wl_gPlr_PDM_PlayerKill(killerid),wl_gPlr_PDM_PlayerDeath(killerid),wl_n_mode_DMInfo[PDM_getPlayerDM(playerid)][E_mode_dm_Command_Name],pName(playerid),wl_gPlr_PDM_PlayerKill(playerid),wl_gPlr_PDM_PlayerDeath(playerid));
		looper(i,0,MAX_PLAYERS,(IsPlayerConnected(i) && (PDM_getPlayerDM(i) != INVALID_PDM_ID))){
			PDM_send(i,tmpstr);
			//print(tmpstr);
		}
	}
	
	return true;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	