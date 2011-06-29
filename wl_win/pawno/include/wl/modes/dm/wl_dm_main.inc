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
	��Ȩ(c) <2010> <yezizhu>  

	ʹ�ø�����֤����������������Ȩ�ޣ���ѣ��κ��˿��Եõ����������������ĵ���һ��������
	���Ҿ�Ӫ�����������κ����ƣ����������Ƶ�ʹ�á����ơ��޸ġ��ϲ������桢���С����Ŵ���֤�顢���߳��۸������Ŀ�����Ȩ����
	ͬʱ���������Щ�������û�������ЩȨ����ʹ����������������  
	
	���ϵİ�Ȩ֪ͨ��Ȩ��֪ͨӦ�ð��������и������Ŀ����л�������������������ʵ�����С�
	
	�������������������ṩ��û���κ���ʽ�ĵ�������������ȷ�ػ��߰����ģ�������Щ���ǲ�����ҵ���ʵĵ��������ơ�
	�ʺ�һ���ض�����;���Ҳ����ַ������ߺͰ�Ȩ���������κγ��϶�ʹ�ø������漰���κ�Ҫ���𺦻����������ζ���Ӧ����
	�����������������û���ֻ�Ǻ�ͬ��ʽ��������Ȩ����������ʽ�������������������÷�Χ�ڡ������������ϵ����������ʹ�û�����������������������Ϊ��  
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
				PDM_send(playerid,"[DM]�Ƿ��뿪DM�����Զ����ͻ� dm");
			}
			
			
			if(!DM_useHandWeapon(playerid) && GetPlayerWeapon(playerid) != WEAPON_TEARGAS && PDM_isPlayeruseInvalidPDMWeapon(playerid,PDM_getPlayerDM(playerid))){
				PDM_outdm_start(playerid)
				GDM_setPlayertoGDM(playerid);
				SetPlayerWorldBounds(playerid,BuyGunArea[2],BuyGunArea[0],BuyGunArea[3],BuyGunArea[1]);
				PDM_send(playerid,"[DM]ӵ�зǷ�����,�����͵�gdm");
				
			}
			
		}else{
			
			if(GDM_isPlayerInGunDM(playerid)){
				if(GetPlayerVirtualWorld(playerid) != GDM_WORLD){
					//GDM_send(playerid,"[DM]�Ƿ��뿪gun dm�����Զ����ͻ�gun dm");
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
			format(tmpstr,sizeof(tmpstr),"[PDM]%s(%dɱ%d��)��'%s'��ɱ����",pName(playerid),wl_gPlr_PDM_PlayerKill(playerid),wl_gPlr_PDM_PlayerDeath(playerid),wl_n_mode_DMInfo[PDM_getPlayerDM(playerid)][E_mode_dm_Command_Name]);
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
		format(tmpstr,sizeof(tmpstr),"[pdm]%s(%dɱ%d��)��'%s'ɱ��%s(%dɱ%d��)",pName(killerid),wl_gPlr_PDM_PlayerKill(killerid),wl_gPlr_PDM_PlayerDeath(killerid),wl_n_mode_DMInfo[PDM_getPlayerDM(playerid)][E_mode_dm_Command_Name],pName(playerid),wl_gPlr_PDM_PlayerKill(playerid),wl_gPlr_PDM_PlayerDeath(playerid));
		looper(i,0,MAX_PLAYERS,(IsPlayerConnected(i) && (PDM_getPlayerDM(i) != INVALID_PDM_ID))){
			PDM_send(i,tmpstr);
			//print(tmpstr);
		}
	}
	
	return true;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	