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




//=======================================Vec============================================
#define WL_VEC_VERSION			("1.0.0.0")
#define DEBUG_VEC				(false)
#define COLOR_VEC				(COLOR_LIGHTBLUE)

enum{
	Vec_lock_none,
	Vec_lock_throw,
	Vec_lock_ban
};
new stock 
	Menu:wl_s_mode_vec_Menu[5];
//=============================================================================================


#define MEM_VEC			(true)
#if MEM_VEC

enum _Vec_Info{
	
};
static
	const stock Vec_ValidToCreate[] = {
		571,437,438,493,433,
		539,568,496,487,476,
		513,560,565,434,494,
		557,470,495,409,490,
		451,411,415,480,429,
		541,506,468,481,522,
		471
	};
#endif





#if MEM_VEC

stock Vec_menuStruction(){
	wl_s_mode_vec_Menu[0] = CreateMenu("~g~Vehicles",2,125,150,275,275);
	wl_s_mode_vec_Menu[1] = CreateMenu("~g~Vehicles",2,125,150,275,275);
	wl_s_mode_vec_Menu[2] = CreateMenu("~g~Vehicles",2,125,150,275,275);
	wl_s_mode_vec_Menu[3] = CreateMenu("~g~Vehicles",1,20,120,150,40);
	wl_s_mode_vec_Menu[4] = CreateMenu("~g~Vehicles",1,20,120,150,40);
	return true;
}
/*
Menu:Vec_getMenu(menupos){
	return wl_s_mode_vec_Menu[menupos];
}
*/
stock Vec_isValidToCreate(modelid){
	for(
		new 
			i,
			amount = sizeof(Vec_ValidToCreate);
		i < amount;i++
	){
		if(modelid == Vec_ValidToCreate[i]){
			return true;
		}
	}
	return false;
}

stock Vec_setPlayerVecID(playerid,vecid){
	#if DEBUG_VEC
		writetolog("[DEBUG_VEC]Vec_setPlayerVecID called");
	#endif
	SetPVarInt(playerid,"wl_plr_Vec_PlayerVecID",vecid);
	return true;
}
forward Vec_getPlayerVecID(playerid);
public Vec_getPlayerVecID(playerid){ debug_public_track("Vec_getPlayerVecID(playerid){");
	#if DEBUG_VEC
		writetolog("[DEBUG_VEC]Vec_getPlayerVecID called");
	#endif
	return GetPVarInt(playerid,"wl_plr_Vec_PlayerVecID");
}


stock Vec_setPlayerVecLockType(playerid,locktype){
	#if DEBUG_VEC
		writetolog("[DEBUG_VEC]Vec_setPlayerVecLockType called");
	#endif
	SetPVarInt(playerid,"wl_plr_Vec_LockType",locktype);
	return true;
}
stock Vec_getPlayerVecLockType(playerid){
	#if DEBUG_VEC
		writetolog("[DEBUG_VEC]Vec_getPlayerVecLockType called");
	#endif
	return GetPVarInt(playerid,"wl_plr_Vec_LockType");
}

#endif
//vecsystem send
#define Vec_send(%1,%2,%3) wl_lang_send((%1),COLOR_VEC,%2,%3)
Vec_send(playerid,msg_identify[]){
	wl_lang_send(playerid,COLOR_VEC,msg_identify);
}

#define Vec_sendAll(%1,%2) wl_lang_sendAll(COLOR_VEC,(%1),%2)
Vec_sendAll(msg_identify[]){
	wl_lang_sendAll(COLOR_VEC,msg_identify);
}

//==================AutoNos=========================
forward Vec_AutoNos();
public Vec_AutoNos(){ debug_public_track("Vec_AutoNos(){");

	loopPlayer(playerid){
		new
			const VecID = GetPlayerVehicleID(playerid);
		if(
			/*sb_gpAutoNos(playerid) &&*/ 
			GetPlayerState(playerid) == PLAYER_STATE_DRIVER && 
			VecID && 
			Vec_isValidNos(VecID) &&
			!CallLocalFunction("dmw_getPlayer","i",playerid)
		){
			AddVehicleComponent(VecID,1010);
		}
	}
	return true;
}
//====================================================
//================AutoRepair===================
forward Vec_AutoRepair();
public Vec_AutoRepair(){ debug_public_track("Vec_AutoRepair(){");
	loopPlayer(playerid){
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
			if(/*sb_gpAutoRepairVec(playerid) && */ !GetPlayerVirtualWorld(playerid)){
				RepairVehicle(GetPlayerVehicleID(playerid));
			}
			if(/*sb_gpAutoHealVec(playerid) && */ !GetPlayerVirtualWorld(playerid)){
				SetVehicleHealth(GetPlayerVehicleID(playerid),1000);
			}
		}
	}
	return true;
}

Vec_OnGameModeInit(){
	SetTimer("Vec_AutoNos",1010*17,true);
	SetTimer("Vec_AutoRepair",1054,true);
	Vec_LoadStaticVehicle();
}
//=========================================

stock Vec_help(playerid){
	Vec_send(playerid,"cmd_vec_help");
	//Vec_send(playerid,"cmd_vec_get_help");
	//Vec_send(playerid,"cmd_vec_clear_help");
	//Vec_send(playerid,"cmd_vec_lock_help");
	//Vec_send(playerid,"cmd_vec_color_help");
	//Vec_send(playerid,"cmd_vec_id_help");
	//Vec_send(playerid,"cmd_vec_fix_help");
	//Vec_send(playerid,"cmd_vec_flip_help");
	//Vec_send(playerid,"cmd_vec_unknown_help");
	return true;
}

stock Vec_call(playerid){
	new
		vecid = Vec_getPlayerVecID(playerid);
	if(vecid != INVALID_VEHICLE_ID){
		new
			Float:px,Float:py,Float:pz,Float:pa,Float:vechp;
		//SetVehicleToRespawn(vecid);
		GetVehicleHealth(vecid,vechp);
		if(vechp >= 101){
			SetVehicleVirtualWorld(vecid,GetPlayerVirtualWorld(playerid));
			GetPlayerPos(playerid,px,py,pz);
			GetPlayerFacingAngle(playerid,pa);
			Vec_throwPassenger(playerid);
			SetVehiclePos(vecid,px,py,pz);
			PutPlayerInVehicle(playerid,vecid,0);
			SetVehiclePos(vecid,px,py,pz);
			SetVehicleZAngle(vecid,pa);
			LinkVehicleToInterior(vecid,GetPlayerInterior(playerid));
			Vec_send(playerid,"vec_teleport_succeed");
			return true;
		}
		
	}
	Vec_send(playerid,"vec_teleport_failed");
	return false;
}
stock Vec_throwPassenger(playerid){
	new
		vecid = Vec_getPlayerVecID(playerid);
	if(vecid != INVALID_VEHICLE_ID){
		new
			Float:px,Float:py,Float:pz;
		loopPlayer(i){
			if(GetPlayerVehicleID(i) == vecid && Vec_getPlayerVecID(playerid) != vecid){
				GetPlayerPos(i,px,py,pz);
				SetPlayerPos(i,px,py,pz+3);
				Vec_send(playerid,"vec_clear_succeed");
			}
		}
		return true;
	}
	return false;
}
stock Vec_lock(playerid){
	switch(Vec_getPlayerVecLockType(playerid)){
		case Vec_lock_none:{
			Vec_setPlayerVecLockType(playerid,Vec_lock_throw);
			Vec_send(playerid,"vec_lock_type1_succeed");
		}
		/*
		case Vec_lock_throw:{
			Vec_setPlayerVecLockType(playerid,Vec_lock_ban);
			Vec_send(playerid,"vec_lock_type2_succeed");
			loopPlayer(i){
				if(i != playerid){
					SetVehicleParamsForPlayer(Vec_getPlayerVecID(playerid),i,false,true);
				}
			}
		}
		*/
		case Vec_lock_ban,Vec_lock_throw:{
			Vec_setPlayerVecLockType(playerid,Vec_lock_none);
			Vec_send(playerid,"vec_lock_none_succeed");
			/*
			loopPlayer(i){
				SetVehicleParamsForPlayer(Vec_getPlayerVecID(playerid),i,false,false);
			}
			*/
		}
	}
	return true;
}

static
	gVecOrginalVirturalWorld[MAX_VEHICLES];

stock Vec_getOrginalVW(vecid){
	return gVecOrginalVirturalWorld[vecid];
}

stock Vec_CreatePlayer(playerid,modelid,bool:putinvec = true,bool:pInterior = true,bool:pVirtual = true){
	new
		Float:px,Float:py,Float:pz,Float:pa;
		
	Vec_setPlayerVecID(playerid,CreateVehicle(modelid,3000+random(3000),3000+random(3000),1000+random(3000),0,random(256),random(256),-1));
	GetPlayerPos(playerid,px,py,pz);
	GetPlayerFacingAngle(playerid,pa);
	SetTimerEx("Vec_CreatePlayer_End",1000,false,"iffffiii",playerid,px,py,pz,pa,putinvec,pInterior,pVirtual);
	new
		vecid = Vec_getPlayerVecID(playerid);
	/*if(pInterior) */LinkVehicleToInterior(vecid,GetPlayerInterior(playerid));
	/*if(pVirtual) */SetVehicleVirtualWorld(vecid,GetPlayerVirtualWorld(playerid));
	gVecOrginalVirturalWorld[vecid] = GetPlayerVirtualWorld(playerid);
	Vec_send(playerid,"cmd_vec_color_help");
	return true;
}
forward Vec_CreatePlayer_End(playerid,Float:px,Float:py,Float:pz,Float:pa,bool:putinvec,pInterior,pVirtual);
public Vec_CreatePlayer_End(playerid,Float:px,Float:py,Float:pz,Float:pa,bool:putinvec,pInterior,pVirtual){ debug_public_track("Vec_CreatePlayer_End(playerid,Float:px,Float:py,Float:pz,Float:pa,bool:putinvec,pInterior,pVirtual){");
	new
		vecid = Vec_getPlayerVecID(playerid);
	
	/*if(pInterior) */LinkVehicleToInterior(vecid,GetPlayerInterior(playerid));
	/*if(pVirtual) */SetVehicleVirtualWorld(vecid,GetPlayerVirtualWorld(playerid));
	if(putinvec) PutPlayerInVehicle(playerid,vecid,0);
	SetVehiclePos(vecid,px,py,pz);
	SetVehicleZAngle(vecid,pa);
	return true;
}
stock Vec_DestroyPlayer(playerid){
	new
		vecid = Vec_getPlayerVecID(playerid);
	if(vecid == INVALID_VEHICLE_ID){
		return false;
	}
	
	loopPlayer(i){
		if(GetPlayerVehicleID(playerid) == vecid){
			new
				Float:px,Float:py,Float:pz;
			GetPlayerPos(playerid,px,py,pz);
			SetPlayerPos(playerid,px,py,pz+3);
		}
	}
	SetVehicleToRespawn(vecid);
	SetTimerEx("Vec_DestroyVehicle",2000,false,"i",vecid);
	gVecOrginalVirturalWorld[vecid] = 0;
	Vec_setPlayerVecID(playerid,INVALID_VEHICLE_ID);
	Vec_setPlayerVecLockType(playerid,Vec_lock_none);
	return true;
}

forward Vec_DestroyVehicle(vecid);
public Vec_DestroyVehicle(vecid){ debug_public_track("Vec_DestroyVehicle(vecid){");
	DestroyVehicle(vecid);
	return true;
}
	

zcmd(vec_flip,playerid,params[]){
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
		Vec_flip(GetPlayerVehicleID(playerid));
	}else{
		Vec_send(playerid,"vec_flip_failed_notdriver");
	}
	return true;
}
pzcmd(flip){rzcmd(vec_flip);}
pzcmd(f){rzcmd(vec_flip);}


zcmd(vec_fix,playerid,params[]){
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
		RepairVehicle(GetPlayerVehicleID(playerid));
		Vec_send(playerid,"vec_repair_succeed");
	}else{
		Vec_send(playerid,"vec_repair_failed_notdriver");
	}
	return true;
}
pzcmd(fix){rzcmd(vec_fix);}
pzcmd(fullfix){rzcmd(vec_fix);}
pzcmd(xiuche){rzcmd(vec_fix);}

stock Vec_usableinNormalWorld(vecmodelid){
	static
		gVecunusableinNormalWorld[] = { 592,435,441,464,465,501,564,569,570,584,590,591,594,606,607,608,610,611,577};
	//520,425,407,432,601,476
	for(new i,j = sizeof(gVecunusableinNormalWorld);i < j;i++){
		if(gVecunusableinNormalWorld[i] == vecmodelid)return false;
	}
	return true;
}

zcmd(vec_main,playerid,params[]){
	zcmd_advused();
	if(isnull(cmd_(1))){
		Vec_send(playerid,"cmd_vec_id_help");
		Vec_send(playerid,"cmd_vec_menu_help");
	}
	else if(IsNumeric(cmd_(1))){
		new 
			vecmodelid = strval(cmd_(1));
		if(vecmodelid < 400 || vecmodelid > 611){
			Vec_send(playerid,"vec_create_failed_invalidvecid",vecmodelid);
		}
		else if(GetPlayerVirtualWorld(playerid)){
			Vec_DestroyPlayer(playerid);
			Vec_CreatePlayer(playerid,vecmodelid);
			Vec_send(playerid,"vec_create_succeed",vecmodelid);
		}
		else{
			if(Vec_usableinNormalWorld(vecmodelid)){
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,vecmodelid);
				Vec_send(playerid,"vec_create_succeed",vecmodelid);
			}
			else{
				Vec_send(playerid,"vec_create_failed_invalidinworld0",vecmodelid);
			}
		}
	}
	else if(compare("wode",1) || compare("tele",1) || compare("teleport",1) || compare("get",1)){
		Vec_call(playerid);
	}
	else if(compare("ti",1) || compare("clear",1)){
		Vec_throwPassenger(playerid);
	}
	else if(compare("suo",1) || compare("lock",1)){
		Vec_lock(playerid);
		//yezizhu
	}
	else if(compare("fix",1)){
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
			RepairVehicle(GetPlayerVehicleID(playerid));
			Vec_send(playerid,"vec_repair_succeed");
		}
		else{
			Vec_send(playerid,"vec_repair_failed_notdriver");
		}
	}
	else if(compare("flip",1)){
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
			Vec_flip(GetPlayerVehicleID(playerid));
		}else{
			Vec_send(playerid,"vec_flip_failed_notdriver");
		}
	}
	else if(compare("color",1)){
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
				ChangeVehicleColor(GetPlayerVehicleID(playerid),strval(cmd_(2)),strval(cmd_(3)));
				Vec_send(playerid,"vec_color_succeed");
		}else{
			Vec_send(playerid,"vec_color_failed_notdriver");
		}
	}
	else if(compare("help",1)){
		Vec_send(playerid,"cmd_vec_get_help");
		Vec_send(playerid,"cmd_vec_clear_help");
		Vec_send(playerid,"cmd_vec_lock_help");
		Vec_send(playerid,"cmd_vec_color_help");
		Vec_send(playerid,"cmd_vec_id_help");
		Vec_send(playerid,"cmd_vec_fix_help");
		Vec_send(playerid,"cmd_vec_flip_help");		
	}
	else if(compare("menu",1)){
		TogglePlayerControllable(playerid, false);
		ShowMenuForPlayer(wl_s_mode_vec_Menu[0],playerid);		
	}
	else if(compare("tune",1)){
		if(GetPlayerVehicleID(playerid) && GetVehicleModel(GetPlayerVehicleID(playerid)) != 493){
			TogglePlayerControllable(playerid, false);
			ShowMenuForPlayer(wl_s_mode_vec_Menu[3],playerid);
			Vec_send(playerid,"vec_tune_tie");
		}else{
			Vec_send(playerid,"vec_tune_failed_vecnomod");
		}
	}
	else{
		Vec_send(playerid,"cmd_vec_unknowncmd",params);
	}
	return true;
}



zcmd(c,playerid,params[]){rzcmd(vec_main);}
zcmd(v,playerid,params[]){rzcmd(vec_main);}
zcmd(car,playerid,params[]){rzcmd(vec_main);}
zcmd(vec,playerid,params[]){rzcmd(vec_main);}

zcmd(vec_zr350,playerid,params[]){
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,477);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_zr350");
	return true;
}
zcmd(zr350,playerid,params[]){rzcmd(vec_zr350);}

zcmd(vec_stretch,playerid,params[]){
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,409);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_stretch");
	return true;
}
pzcmd(club){rzcmd(vec_stretch);}
pzcmd(stretch){rzcmd(vec_stretch);}


zcmd(vec_bandito,playerid,params[]){
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,568);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_bandito");
	return true;
}
pzcmd(bandito){rzcmd(vec_bandito);}
pzcmd(band){rzcmd(vec_bandito);}

zcmd(vec_quadbike,playerid,params[]){
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,471);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_quadbike");
	return true;
}
pzcmd(quad){rzcmd(vec_quadbike);}
pzcmd(quadbike){rzcmd(vec_quadbike);}

zcmd(vec_packer,playerid,params[]){
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,443);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_packer");
	return true;
}
pzcmd(packer){rzcmd(vec_packer);}


zcmd(vec_sandking,playerid,params[]){
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,495);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_sandking");
	return true;
}
pzcmd(sand){rzcmd(vec_sandking);}
pzcmd(sandking){rzcmd(vec_sandking);}

zcmd(vec_sanchez,playerid,params[]){
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,468);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_sanchez");
	return true;
}
pzcmd(sanchez){rzcmd(vec_sanchez);}
pzcmd(sanc){rzcmd(vec_sanchez);}

zcmd(vec_maverick,playerid,params[]){
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,487);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_maverick");
	return true;
}
pzcmd(zhishengji){rzcmd(vec_maverick);}
pzcmd(helecopter){rzcmd(vec_maverick);}
pzcmd(maverick){rzcmd(vec_maverick);}


zcmd(vec_stuntplane,playerid,params[]){
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,513);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_stuntplane");
	return true;
}
pzcmd(stuntplane){rzcmd(vec_stuntplane);}
pzcmd(plane){rzcmd(vec_stuntplane);}
pzcmd(feiji){rzcmd(vec_stuntplane);}

zcmd(vec_rustler,playerid,params[]){
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,476);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_rustler");
	return true;
}
pzcmd(rustler){rzcmd(vec_rustler);}
pzcmd(zdj){rzcmd(vec_rustler);}

zcmd(vec_turismo,playerid,params[]){
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,451);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_turismo");
	return true;
}
pzcmd(tur){rzcmd(vec_turismo);}
pzcmd(turismo){rzcmd(vec_turismo);}

zcmd(vec_infernus,playerid,params[]){
	#pragma unused params
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,411);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_infernus");
	return true;
}
pzcmd(inf){rzcmd(vec_infernus);}
pzcmd(infernus){rzcmd(vec_infernus);}

zcmd(vec_cheetah,playerid,params[]){
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,415);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_cheetah");
	return true;
}
pzcmd(cheetah){rzcmd(vec_cheetah);}

zcmd(vec_supergt,playerid,params[]){
	#pragma unused params
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,506);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_supergt");
	return true;
}
pzcmd(supergt){rzcmd(vec_supergt);}

zcmd(vec_bmx,playerid,params[]){
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,481);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_bmx");
	return true;
}
pzcmd(bmx){rzcmd(vec_bmx);}
pzcmd(zixingche){rzcmd(vec_bmx);}
pzcmd(danche){rzcmd(vec_bmx);}

zcmd(vec_nrg500,playerid,params[]){
	#pragma unused params
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,522);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_nrg");
	return true;
}
pzcmd(nrg){rzcmd(vec_nrg500);}
pzcmd(nrg500){rzcmd(vec_nrg500);}

zcmd(vec_kart,playerid,params[]){
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,571);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_kart");
	return true;
}
pzcmd(kart){rzcmd(vec_kart);}

zcmd(vec_bus,playerid,params[]){
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,437);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_bus");
	return true;
}
pzcmd(bus){rzcmd(vec_bus);}

zcmd(vec_taxi,playerid,params[]){
	#pragma unused params
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,438);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_taxi");
	return true;
}
pzcmd(taxi){rzcmd(vec_taxi);}
pzcmd(cab){rzcmd(vec_taxi);}

zcmd(vec_jetmax,playerid,params[]){
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,493);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_jetmax");
	return true;
}
pzcmd(boat){rzcmd(vec_jetmax);}
pzcmd(jetmax){rzcmd(vec_jetmax);}

zcmd(vec_sultan,playerid,params[]){
	#pragma unused params
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,560);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_sultan");
	return true;
}
pzcmd(sultan){rzcmd(vec_sultan);}
pzcmd(sul){rzcmd(vec_sultan);}

zcmd(vec_flash,playerid,params[]){
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,565);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_flash");
	return true;
}
pzcmd(flash){rzcmd(vec_flash);}

zcmd(vec_copcar,playerid,params[]){	
	Vec_DestroyPlayer(playerid);
	Vec_CreatePlayer(playerid,599);
	//Vec_lock(playerid);
	Vec_send(playerid,"vec_create_copcar");
	return true;
}
pzcmd(copcar){rzcmd(vec_copcar);}

Vec_Struction(){
	Vec_MenuCreate();
	Vec_OnGameModeInit();
	return true;
}
Vec_Unstruction(){
	Vec_MenuDestroy();
	return true;
}

Vec_OnPlayerDisconnect(playerid,reason){
	#pragma unused reason
	Vec_DestroyPlayer(playerid);
	return true;
}

static
	pExitVehicle[MAX_PLAYERS];

Vec_PlayerExitVehicle(playerid){
	pExitVehicle[playerid] = true;
}

Vec_OnPlayerStateChange(playerid,newstate,oldstate){
	//#pragma unused oldstate
	//System_sendAll("%d n:%d o:%d",playerid,newstate,oldstate);
	static
		gVecOldVec[MAX_PLAYERS];	
	if(newstate == PLAYER_STATE_DRIVER){
		pExitVehicle[playerid] = false;
		gVecOldVec[playerid] = GetPlayerVehicleID(playerid);
		Vec_help(playerid);
		if(!CallLocalFunction("dmw_getPlayer","i",playerid) && Vec_isValidNos(GetPlayerVehicleID(playerid))){
			AddVehicleComponent(GetPlayerVehicleID(playerid),1010);
		}
	}
	if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER && !pExitVehicle[playerid]){
		if(gVecOldVec[playerid] == Vec_getPlayerVecID(playerid) && Vec_getPlayerVecLockType(playerid) != Vec_lock_none){
			PutPlayerInVehicle(playerid,gVecOldVec[playerid],0);
		}
	}
	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER){
		new
			pvecid = GetPlayerVehicleID(playerid);
		Vec_send(playerid,"vec_mdoel_id",GetVehicleModel(pvecid));
		if(Vec_getPlayerVecID(playerid) == pvecid){
			switch(Vec_getPlayerVecLockType(playerid)){
				case Vec_lock_none:{
					Vec_send(playerid,"vec_lock_type_none");
				}
			}
		}else{
			loopPlayer(i){
				if(Vec_getPlayerVecID(i) == pvecid){
					switch(Vec_getPlayerVecLockType(i)){
						case Vec_lock_throw,Vec_lock_ban:{
							new
								Float:px,Float:py,Float:pz;
							GetPlayerPos(playerid,px,py,pz);
							SetPlayerPos(playerid,px,py,pz);
							Vec_send(playerid,"vec_lock_type_lock",PlayerName(i));							
						}
						case Vec_lock_none:{
							Vec_send(playerid,"vec_lock_type_lock",PlayerName(i));
							Vec_send(i,"vec_selfvec_hint",PlayerName(playerid));
						}
					}
					break;
				}
			}
		}
	}
	return true;
}
/*
zcmd(neon,playerid,params[]){
	ShowPlayerDialog(playerid, 8899, DIALOG_STYLE_LIST, "Pick Neon Color", "Blue\nRed\nGreen\nWhite\nPink\nYellow\nPolice Strobe\nInterior Lights\nBack Neon\nFront neon\nUndercover Roof Light\nRemove All Neon", "Select", "Cancel");
	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 10.0);
	return true;
}

Vec_DialogResponse(playerid, dialogid, response, listitem)
{

 if(dialogid == 8899)
	{
		if(response)
		{
			if(listitem == 0){
				//blue
				DestroyDynamicObject(GetPVarInt(playerid, "neon_left"));
				DestroyDynamicObject(GetPVarInt(playerid, "neon_right"));
				SetPVarInt(playerid, "neon_left", CreateDynamicObject(18648,0,0,0,0,0,0, .distance = 10000.0));
				SetPVarInt(playerid, "neon_right", CreateDynamicObject(18648,0,0,0,0,0,0, .distance = 10000.0));
				AttachObjectToVehicle(GetPVarInt(playerid, "neon_left"), GetPlayerVehicleID(playerid), -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
				AttachObjectToVehicle(GetPVarInt(playerid, "neon_right"), GetPlayerVehicleID(playerid), 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
   			}
			if(listitem == 1){
				//red
				DestroyDynamicObject(GetPVarInt(playerid, "neon_left"));
				DestroyDynamicObject(GetPVarInt(playerid, "neon_right"));
	            SetPVarInt(playerid, "neon_left", CreateDynamicObject(18647,0,0,0,0,0,0, .distance = 10000.0));
	            SetPVarInt(playerid, "neon_right", CreateDynamicObject(18647,0,0,0,0,0,0, .distance = 10000.0));
	            AttachObjectToVehicle(GetPVarInt(playerid, "neon_left"), GetPlayerVehicleID(playerid), -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	            AttachObjectToVehicle(GetPVarInt(playerid, "neon_right"), GetPlayerVehicleID(playerid), 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	            SendClientMessage(playerid, 0xFFFFFFAA, "neon installed");

}
			if(listitem == 2){
			//green
				DestroyDynamicObject(GetPVarInt(playerid, "neon_left"));
				DestroyDynamicObject(GetPVarInt(playerid, "neon_right"));
	            SetPVarInt(playerid, "neon_left", CreateDynamicObject(18649,0,0,0,0,0,0, .distance = 10000.0));
	            SetPVarInt(playerid, "neon_right", CreateDynamicObject(18649,0,0,0,0,0,0, .distance = 10000.0));
	            AttachObjectToVehicle(GetPVarInt(playerid, "neon_left"), GetPlayerVehicleID(playerid), -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	            AttachObjectToVehicle(GetPVarInt(playerid, "neon_right"), GetPlayerVehicleID(playerid), 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	            SendClientMessage(playerid, 0xFFFFFFAA, "neon installed");

	            }
			if(listitem == 3){
				DestroyDynamicObject(GetPVarInt(playerid, "neon_left"));
				DestroyDynamicObject(GetPVarInt(playerid, "neon_right"));
	            SetPVarInt(playerid, "neon_left", CreateDynamicObject(18652,0,0,0,0,0,0, .distance = 10000.0));
	            SetPVarInt(playerid, "neon_right", CreateDynamicObject(18652,0,0,0,0,0,0, .distance = 10000.0));
	            AttachObjectToVehicle(GetPVarInt(playerid, "neon_left"), GetPlayerVehicleID(playerid), -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	            AttachObjectToVehicle(GetPVarInt(playerid, "neon_right"), GetPlayerVehicleID(playerid), 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	            SendClientMessage(playerid, 0xFFFFFFAA, "neon installed");
			}
			if(listitem == 4){
			//pink
				DestroyDynamicObject(GetPVarInt(playerid, "neon_left"));
				DestroyDynamicObject(GetPVarInt(playerid, "neon_right"));
	            SetPVarInt(playerid, "neon_left", CreateDynamicObject(18651,0,0,0,0,0,0, .distance = 10000.0));
	            SetPVarInt(playerid, "neon_right", CreateDynamicObject(18651,0,0,0,0,0,0, .distance = 10000.0));
	            AttachObjectToVehicle(GetPVarInt(playerid, "neon_left"), GetPlayerVehicleID(playerid), -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	            AttachObjectToVehicle(GetPVarInt(playerid, "neon_right"), GetPlayerVehicleID(playerid), 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	            SendClientMessage(playerid, 0xFFFFFFAA, "neon installed");

			}
			if(listitem == 5){
			//yellow
				DestroyDynamicObject(GetPVarInt(playerid, "neon_left"));
				DestroyDynamicObject(GetPVarInt(playerid, "neon_right"));
	            SetPVarInt(playerid, "neon_left", CreateDynamicObject(18650,0,0,0,0,0,0, .distance = 10000.0));
	            SetPVarInt(playerid, "neon_right", CreateDynamicObject(18650,0,0,0,0,0,0, .distance = 10000.0));
	            AttachObjectToVehicle(GetPVarInt(playerid, "neon_left"), GetPlayerVehicleID(playerid), -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	            AttachObjectToVehicle(GetPVarInt(playerid, "neon_right"), GetPlayerVehicleID(playerid), 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	            SendClientMessage(playerid, 0xFFFFFFAA, "neon installed");

			}
			if(listitem == 6){
			//police
				DestroyDynamicObject(GetPVarInt(playerid, "neon_left"));
				DestroyDynamicObject(GetPVarInt(playerid, "neon_right"));
	            SetPVarInt(playerid, "neon_left", CreateDynamicObject(18646,0,0,0,0,0,0, .distance = 10000.0));
	            SetPVarInt(playerid, "neon_right", CreateDynamicObject(18646,0,0,0,0,0,0, .distance = 10000.0));
	            AttachObjectToVehicle(GetPVarInt(playerid, "neon_left"), GetPlayerVehicleID(playerid), -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	            AttachObjectToVehicle(GetPVarInt(playerid, "neon_right"), GetPlayerVehicleID(playerid), 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
	            SendClientMessage(playerid, 0xFFFFFFAA, "neon installed");

	        }
	        if(listitem == 7){
				//interior
				DestroyDynamicObject(GetPVarInt(playerid, "interior_left"));
				DestroyDynamicObject(GetPVarInt(playerid, "interior_right"));
	            SetPVarInt(playerid, "interior_left", CreateDynamicObject(18646,0,0,0,0,0,0, .distance = 10000.0));
	            SetPVarInt(playerid, "interior_right", CreateDynamicObject(18646,0,0,0,0,0,0, .distance = 10000.0));
	            AttachObjectToVehicle(GetPVarInt(playerid, "interior_left"), GetPlayerVehicleID(playerid), 0, -0.0, 0, 2.0, 2.0, 3.0);
	            AttachObjectToVehicle(GetPVarInt(playerid, "interior_right"), GetPlayerVehicleID(playerid), 0, -0.0, 0, 2.0, 2.0, 3.0);
	            SendClientMessage(playerid, 0xFFFFFFAA, "Interior lights installed");

	        }
          	if(listitem == 8){
				//back
				DestroyDynamicObject(GetPVarInt(playerid, "back_left"));
				DestroyDynamicObject(GetPVarInt(playerid, "back_right"));
	            SetPVarInt(playerid, "back_left", CreateDynamicObject(18646,0,0,0,0,0,0, .distance = 10000.0));
	            SetPVarInt(playerid, "back_right", CreateDynamicObject(18646,0,0,0,0,0,0, .distance = 10000.0));
	            AttachObjectToVehicle(GetPVarInt(playerid, "back_left"), GetPlayerVehicleID(playerid), -0.0, -1.5, -1, 2.0, 2.0, 3.0);
	            AttachObjectToVehicle(GetPVarInt(playerid, "back_right"), GetPlayerVehicleID(playerid), -0.0, -1.5, -1, 2.0, 2.0, 3.0);
	            SendClientMessage(playerid, 0xFFFFFFAA, "Back neon installed");
	        }
            if(listitem == 9){
				//front
				DestroyDynamicObject(GetPVarInt(playerid, "front_left"));
				DestroyDynamicObject(GetPVarInt(playerid, "front_right"));
	            SetPVarInt(playerid, "front_left", CreateDynamicObject(18646,0,0,0,0,0,0, .distance = 10000.0));
	            SetPVarInt(playerid, "front_right", CreateDynamicObject(18646,0,0,0,0,0,0, .distance = 10000.0));
	            AttachObjectToVehicle(GetPVarInt(playerid, "front_left"), GetPlayerVehicleID(playerid), -0.0, 1.5, -0.6, 2.0, 2.0, 3.0);
	            AttachObjectToVehicle(GetPVarInt(playerid, "front_right"), GetPlayerVehicleID(playerid), -0.0, 1.5, -0.6, 2.0, 2.0, 3.0);
	            SendClientMessage(playerid, 0xFFFFFFAA, "Front neon installed");
	        }
	        if(listitem == 10){
	            //undercover				
				DestroyDynamicObject(GetPVarInt(playerid, "undercover_left"));
				DestroyDynamicObject(GetPVarInt(playerid, "undercover_right"));
	            SetPVarInt(playerid, "undercover_left", CreateDynamicObject(18646,0,0,0,0,0,0, .distance = 10000.0));
	            SetPVarInt(playerid, "undercover_right", CreateDynamicObject(18646,0,0,0,0,0,0, .distance = 10000.0));
	            AttachObjectToVehicle(GetPVarInt(playerid, "undercover_left"), GetPlayerVehicleID(playerid), -0.5, -0.2, 0.8, 2.0, 2.0, 3.0);
	            AttachObjectToVehicle(GetPVarInt(playerid, "undercover_right"), GetPlayerVehicleID(playerid), -0.5, -0.2, 0.8, 2.0, 2.0, 3.0);
	            SendClientMessage(playerid, 0xFFFFFFAA, "Undercover lights installed");
	        }
			if(listitem == 11){
				//remove neon
				DestroyDynamicObject(GetPVarInt(playerid, "neon_left"));
				DestroyDynamicObject(GetPVarInt(playerid, "neon_right"));
				DestroyDynamicObject(GetPVarInt(playerid, "interior_left"));
				DestroyDynamicObject(GetPVarInt(playerid, "interior_right"));
				DestroyDynamicObject(GetPVarInt(playerid, "back_left"));
				DestroyDynamicObject(GetPVarInt(playerid, "back_right"));
				DestroyDynamicObject(GetPVarInt(playerid, "front_left"));
				DestroyDynamicObject(GetPVarInt(playerid, "front_right"));
				DestroyDynamicObject(GetPVarInt(playerid, "undercover_left"));
				DestroyDynamicObject(GetPVarInt(playerid, "undercover_right"));
			}
		}
	}
	return false;
}
*/

Vec_OnPlayerSelectedMenuRow(playerid,row){
	new
		Menu:curMenu = GetPlayerMenu(playerid);
	if(curMenu == wl_s_mode_vec_Menu[0]){
		//TogglePlayerControllable(playerid, true);
		switch(row){
			case 0:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,451);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 1:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,411);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 2:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,506);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 3:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,415);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 4:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,480);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 5:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,429);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 6:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,541);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 7:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,481);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 8:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,522);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 9:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,471);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 10:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,468);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 11:{
				//TogglePlayerControllable(playerid, false);
				ShowMenuForPlayer(wl_s_mode_vec_Menu[1],playerid);
			}
		}
	}else
	if(curMenu == wl_s_mode_vec_Menu[1]){
		//TogglePlayerControllable(playerid, true);
		switch(row){
			case 0:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,571);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 1:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,437);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 2:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,438);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 3:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,493);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 4:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,433);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 5:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,539);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 6:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,568);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 7:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,496);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 8:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,497);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 9:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,476);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 10:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,513);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 11:{
				//TogglePlayerControllable(playerid, false);
				ShowMenuForPlayer(wl_s_mode_vec_Menu[2],playerid);
			}
		}
	}else
	if(curMenu == wl_s_mode_vec_Menu[2]){
		//TogglePlayerControllable(playerid, true);
		switch(row){
			case 0:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,560);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 1:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,565);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 2:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,490);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 3:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,599);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 4:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,434);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 5:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,494);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 6:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,557);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 7:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,470);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 8:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,495);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 9:{
				Vec_DestroyPlayer(playerid);
				Vec_CreatePlayer(playerid,409);
				HideMenuForPlayer(curMenu,playerid);
				
			}
			case 10:{
				//TogglePlayerControllable(playerid, false);
				ShowMenuForPlayer(wl_s_mode_vec_Menu[0],playerid);
			}
		}
	}else
	if(curMenu == wl_s_mode_vec_Menu[3]){
		TogglePlayerControllable(playerid, true);
		switch(row){
			case 0:{
				AddVehicleComponent(GetPlayerVehicleID(playerid),1025);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 1:{
				AddVehicleComponent(GetPlayerVehicleID(playerid),1074);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 2:{
				AddVehicleComponent(GetPlayerVehicleID(playerid),1076);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 3:{
				AddVehicleComponent(GetPlayerVehicleID(playerid),1078);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 4:{
				AddVehicleComponent(GetPlayerVehicleID(playerid),1081);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 5:{
				AddVehicleComponent(GetPlayerVehicleID(playerid),1082);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 6:{
				AddVehicleComponent(GetPlayerVehicleID(playerid),1085);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 7:{
				AddVehicleComponent(GetPlayerVehicleID(playerid),1096);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 8:{
				AddVehicleComponent(GetPlayerVehicleID(playerid),1097);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 9:{
				AddVehicleComponent(GetPlayerVehicleID(playerid),1098);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 10:{
				TogglePlayerControllable(playerid, false);
				ShowMenuForPlayer(wl_s_mode_vec_Menu[4],playerid);
			}
		}
	}else
	if(curMenu == wl_s_mode_vec_Menu[4]){
		//TogglePlayerControllable(playerid, true);
		switch(row){
			
			case 0:{
				AddVehicleComponent(GetPlayerVehicleID(playerid),1084);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 1:{
				AddVehicleComponent(GetPlayerVehicleID(playerid),1073);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 2:{
				AddVehicleComponent(GetPlayerVehicleID(playerid),1075);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 3:{
				AddVehicleComponent(GetPlayerVehicleID(playerid),1077);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 4:{
				AddVehicleComponent(GetPlayerVehicleID(playerid),1079);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 5:{
				AddVehicleComponent(GetPlayerVehicleID(playerid),1080);
				HideMenuForPlayer(curMenu,playerid);
			}
			case 6:{
				AddVehicleComponent(GetPlayerVehicleID(playerid),1083);
				HideMenuForPlayer(curMenu,playerid);	
			}
			case 7:{
				//TogglePlayerControllable(playerid, false);
				ShowMenuForPlayer(wl_s_mode_vec_Menu[3],playerid);
			}
		}
	}else return false;
	return true;
}

Vec_MenuCreate(){
	Vec_menuStruction();
	SetMenuColumnHeader(wl_s_mode_vec_Menu[0],0,"Fast cars and bikes:");
	AddMenuItem(wl_s_mode_vec_Menu[0],0,"Turismo");
	AddMenuItem(wl_s_mode_vec_Menu[0],0,"Infernus");
	AddMenuItem(wl_s_mode_vec_Menu[0],0,"Super-GT" );
	AddMenuItem(wl_s_mode_vec_Menu[0],0,"Cheetah" );
	AddMenuItem(wl_s_mode_vec_Menu[0],0,"Comet" );
	AddMenuItem(wl_s_mode_vec_Menu[0],0,"Banshee" );
	AddMenuItem(wl_s_mode_vec_Menu[0],0,"Bullet" );
	AddMenuItem(wl_s_mode_vec_Menu[0],0,"BMX" );
	AddMenuItem(wl_s_mode_vec_Menu[0],0,"NRG-500" );
	AddMenuItem(wl_s_mode_vec_Menu[0],0,"Quad" );
	AddMenuItem(wl_s_mode_vec_Menu[0],0,"Sanchez" );
	AddMenuItem(wl_s_mode_vec_Menu[0],0,"Exchange");
	AddMenuItem(wl_s_mode_vec_Menu[0],1,"/tur" );
	AddMenuItem(wl_s_mode_vec_Menu[0],1,"/inf" );
	AddMenuItem(wl_s_mode_vec_Menu[0],1,"/supergt" );
	AddMenuItem(wl_s_mode_vec_Menu[0],1,"/cheetah" );
	AddMenuItem(wl_s_mode_vec_Menu[0],1,"/car 480" );
	AddMenuItem(wl_s_mode_vec_Menu[0],1,"/car 429" );
	AddMenuItem(wl_s_mode_vec_Menu[0],1,"/car 541" );
	AddMenuItem(wl_s_mode_vec_Menu[0],1,"/bmx" );
	AddMenuItem(wl_s_mode_vec_Menu[0],1,"/nrg" );
	AddMenuItem(wl_s_mode_vec_Menu[0],1,"/car 471" );
	AddMenuItem(wl_s_mode_vec_Menu[0],1,"/car 468" );
	
	
	SetMenuColumnHeader(wl_s_mode_vec_Menu[1],0,"Special vehicles(boat,air,etc)");
	AddMenuItem(wl_s_mode_vec_Menu[1],0,"Kart");
	AddMenuItem(wl_s_mode_vec_Menu[1],0,"Coach");
	AddMenuItem(wl_s_mode_vec_Menu[1],0,"Cabbie");
	AddMenuItem(wl_s_mode_vec_Menu[1],0,"Jetmax");
	AddMenuItem(wl_s_mode_vec_Menu[1],0,"Barracks");
	AddMenuItem(wl_s_mode_vec_Menu[1],0,"Vortex");
	AddMenuItem(wl_s_mode_vec_Menu[1],0,"Bandito");
	AddMenuItem(wl_s_mode_vec_Menu[1],0,"Blistac");
	AddMenuItem(wl_s_mode_vec_Menu[1],0,"Helecopter");
	AddMenuItem(wl_s_mode_vec_Menu[1],0,"Rustler");
	AddMenuItem(wl_s_mode_vec_Menu[1],0,"Stunt");
	AddMenuItem(wl_s_mode_vec_Menu[1],0,"Exchange");
	AddMenuItem(wl_s_mode_vec_Menu[1],1,"/kart");
	AddMenuItem(wl_s_mode_vec_Menu[1],1,"/bus");
	AddMenuItem(wl_s_mode_vec_Menu[1],1,"/taxi");
	AddMenuItem(wl_s_mode_vec_Menu[1],1,"/boat");
	AddMenuItem(wl_s_mode_vec_Menu[1],1,"/car 433");
	AddMenuItem(wl_s_mode_vec_Menu[1],1,"/car 539");
	AddMenuItem(wl_s_mode_vec_Menu[1],1,"/car 496");
	AddMenuItem(wl_s_mode_vec_Menu[1],1,"/car 497");
	AddMenuItem(wl_s_mode_vec_Menu[1],1,"/car 476");
	AddMenuItem(wl_s_mode_vec_Menu[1],1,"/car 513");
	
	
	SetMenuColumnHeader(wl_s_mode_vec_Menu[2],0,"Normal vehicles");
	AddMenuItem(wl_s_mode_vec_Menu[2],0,"Sultan");
	AddMenuItem(wl_s_mode_vec_Menu[2],0,"Flash");
	AddMenuItem(wl_s_mode_vec_Menu[2],0,"Fbiranch");
	AddMenuItem(wl_s_mode_vec_Menu[2],0,"Copcar");
	AddMenuItem(wl_s_mode_vec_Menu[2],0,"Hotknife");
	AddMenuItem(wl_s_mode_vec_Menu[2],0,"Hotring");
	AddMenuItem(wl_s_mode_vec_Menu[2],0,"Monster");
	AddMenuItem(wl_s_mode_vec_Menu[2],0,"Patriot");
	AddMenuItem(wl_s_mode_vec_Menu[2],0,"Sandking");
	AddMenuItem(wl_s_mode_vec_Menu[2],0,"Stretch");
	AddMenuItem(wl_s_mode_vec_Menu[2],0,"Exchange");
	AddMenuItem(wl_s_mode_vec_Menu[2],1,"/sultan");
	AddMenuItem(wl_s_mode_vec_Menu[2],1,"/flash");
	AddMenuItem(wl_s_mode_vec_Menu[2],1,"/fbicar");
	AddMenuItem(wl_s_mode_vec_Menu[2],1,"/copcar");
	AddMenuItem(wl_s_mode_vec_Menu[2],1,"/car 434");
	AddMenuItem(wl_s_mode_vec_Menu[2],1,"/car 494");
	AddMenuItem(wl_s_mode_vec_Menu[2],1,"/car 557");
	AddMenuItem(wl_s_mode_vec_Menu[2],1,"/car 470");
	AddMenuItem(wl_s_mode_vec_Menu[2],1,"/car 495");
	AddMenuItem(wl_s_mode_vec_Menu[2],1,"/car 409");
	
	
	SetMenuColumnHeader(wl_s_mode_vec_Menu[3],0,"Wheels");
	AddMenuItem(wl_s_mode_vec_Menu[3],0,"Offroad");
	AddMenuItem(wl_s_mode_vec_Menu[3],0,"Mega");
	AddMenuItem(wl_s_mode_vec_Menu[3],0,"Wires");
	AddMenuItem(wl_s_mode_vec_Menu[3],0,"Twist");
	AddMenuItem(wl_s_mode_vec_Menu[3],0,"Grove");
	AddMenuItem(wl_s_mode_vec_Menu[3],0,"Import");
	AddMenuItem(wl_s_mode_vec_Menu[3],0,"Atomic");
	AddMenuItem(wl_s_mode_vec_Menu[3],0,"Ahab");
	AddMenuItem(wl_s_mode_vec_Menu[3],0,"Virtual");
	AddMenuItem(wl_s_mode_vec_Menu[3],0,"Access");
	AddMenuItem(wl_s_mode_vec_Menu[3],0,"Exchange");
	
	
	SetMenuColumnHeader(wl_s_mode_vec_Menu[4],0,"Wheels");
	AddMenuItem(wl_s_mode_vec_Menu[4],0,"Trance");
	AddMenuItem(wl_s_mode_vec_Menu[4],0,"Shadow");
	AddMenuItem(wl_s_mode_vec_Menu[4],0,"Rimshine");
	AddMenuItem(wl_s_mode_vec_Menu[4],0,"Classic");
	AddMenuItem(wl_s_mode_vec_Menu[4],0,"Cutter");
	AddMenuItem(wl_s_mode_vec_Menu[4],0,"Switch");
	AddMenuItem(wl_s_mode_vec_Menu[4],0,"Dollar");
	AddMenuItem(wl_s_mode_vec_Menu[4],0,"Exchange");	
	
}
Vec_MenuDestroy(){
	DestroyMenu(wl_s_mode_vec_Menu[0]);
	DestroyMenu(wl_s_mode_vec_Menu[1]);
	DestroyMenu(wl_s_mode_vec_Menu[2]);
	DestroyMenu(wl_s_mode_vec_Menu[3]);
	DestroyMenu(wl_s_mode_vec_Menu[4]);
}



Vec_LoadStaticVehicle(){
	if(!fexist("wl/vehicles.ini")){
		printf(" 载入交通工具错误,wl/vehicles.ini 不存在");
		return;
	}
	new 
		File:ofile = fopen("wl/vehicles.ini",io_read),
		rstr[256],
		vecamount,line;
	while(fread(ofile,rstr)){
		new
			vm,Float:vx,Float:vy,Float:vz,Float:va;
		line++;
		if(!sscanf(rstr,"p,iffff",vm,vx,vy,vz,va)){
			AddStaticVehicleEx(vm,vx,vy,vz,va,random(100),random(100),240);
			vecamount++;
		}else{
			//printf("  交通工具部分载入失败，问题行:%d",line);
			//printf("  问题行字符串:%s",rstr);
		}
	}
	fclose(ofile);
	printf(" 交通工具载入成功,数量:%d",vecamount);
}