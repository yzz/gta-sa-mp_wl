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


dmwvehicle:struct(){
	//create vehicle by dmw\vehicles.ini
	/*
	if(!fexist("wl/DMWorld/vehicles.ini")) fcreate("wl/DMWorld/vehicles.ini");
	new 
		File:ofile = fopen("wl/DMWorld/vehicles.ini",io_read),
		rstr[256],
		vecamount;
	while(fread(ofile,rstr)){
		new
			vm,Float:vx,Float:vy,Float:vz,Float:va,color1,color2,
			vecid;
		sscanf(rstr,"p,iffffii",vm,vx,vy,vz,va,color1,color2);
		if(vm != 0){
		//if(!sscanf(rstr,"p,iffffii",vm,vx,vy,vz,va,color1,color2)){
			vecid = AddStaticVehicleEx(vm,vx,vy,vz,va,random(256),random(256),60* 60);
			SetVehicleVirtualWorld(vecid,DMWorld_ID);
			vecamount++;
		}
	}
	//idle(500);
	
	fclose(ofile);
	*/
	
	SetTimer("dmwvehicle_ItterCheck",2046,true);
	//printf(" [大战城]交通工具载入成功,数量:%d",vecamount);
	
	for(new zoneid,zoneamount = zone:getZoneMaxID();zoneid <= zoneamount;zoneid++){
		if(strlen(zone:getZoneName(zoneid))){
			new
				Float:x,Float:y,Float:z;
			zone:getZoneSpawnPoint(zoneid,x,y,z);
			new
				vecid = AddStaticVehicle(478,x,y,z,random(360),random(256),random(256));
			new
				numberplate[56];
			if(zone:getOwnedGang(zoneid) != INVALID_GANG_ID){
				format(numberplate,sizeof(numberplate),gang:getGangName(zone:getOwnedGang(zoneid)));
			}
			else {
				format(numberplate,sizeof(numberplate)," ");
			}
			SetVehicleVirtualWorld(vecid,DMWorld_ID);
			SetVehicleNumberPlate(vecid,numberplate);
		}
	}
}

forward dmwvehicle:ItterCheck();
public dmwvehicle:ItterCheck(){ debug_public_track("dmwvehicle:ItterCheck(){");
	loopPlayer(playerid){
		if(dmw:getPlayer(playerid)){
			if(IsPlayerInAnyVehicle(playerid)){
				new
					vecid = GetPlayerVehicleID(playerid);
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
					new
						Float:vcx,Float:vcy,Float:vcz;
					GetVehicleVelocity(vecid,vcx,vcy,vcz);
					if(vcx+vcy+vcz < 0.01){
						if(GetVehicleModel(vecid) == 416){
							if(pHealth(playerid) < 98){
								SetPlayerHealth(playerid,pHealth(playerid)+1);
							}
						}
						else if(GetVehicleModel(vecid) == 427){
							if(pArmour(playerid) < 98){
								SetPlayerArmour(playerid,pArmour(playerid)+1);
							}				
						}
					}
				}
			}
		}
	}
}

new
	g_dmwVehicle_purchaseDialogInfo[] = 
		" \
			小绵羊  05积分  -  旅行居家必备\n救护车  20积分  -  机动补血车\n装甲车  30积分  -  机动补甲车\n \
			447小麻雀  476Rustler  487Maverick  423Hunter \
		",
	g_dmwVehicle_DialogID = 1336;


dmwvehicle:VehicleDeath(vehicleid){
	if(GetGVarInt("wl_dmw_tempVehicle",vehicleid)){
		DestroyVehicle(vehicleid);
		DeleteGVar("wl_dmw_tempVehicle",vehicleid);
	}
}

dmwvehicle:DialogResponse(playerid,dialogid,response,listitem){
	if(dialogid == g_dmwVehicle_DialogID && response){
		if(listitem == 0){
			if(dmwscore:getPlayerGang(playerid) - 5 < 0){
				System_send(playerid,"[帮派]购买失败,帮派积分不足");
				return;
			}
			new
				vecid = CreateVehicle(448, pX(playerid)+5,pY(playerid)+5,pZ(playerid)+2,0,random(255),random(255),-1);
			SetGVarInt("wl_dmw_tempVehicle",true,vecid);
			SetVehicleNumberPlate(vecid,gang:getGangName(gang:getPlayerGang(playerid)));
			SetVehicleVirtualWorld(vecid,DMWorld_ID);
			
			dmwscore:amountedPlayerGang(playerid, 0 - 5);
			gang:sendgang(gang:getPlayerGang(playerid),"dmw_dialog_buyvec_a",pName(playerid));
		}
		else if(listitem == 1){
			if(dmwscore:getPlayerGang(playerid) - 20 < 0){
				System_send(playerid,"[帮派]购买失败,帮派积分不足");
				return;
			}
			new
				vecid = CreateVehicle(416, pX(playerid)+5,pY(playerid)+5,pZ(playerid)+2,0,random(255),random(255),-1);
			SetGVarInt("wl_dmw_tempVehicle",true,vecid);
			SetVehicleNumberPlate(vecid,gang:getGangName(gang:getPlayerGang(playerid)));
			SetVehicleVirtualWorld(vecid,DMWorld_ID);
			dmwscore:amountedPlayerGang(playerid, 0 - 20);
			gang:sendgang(gang:getPlayerGang(playerid),"dmw_dialog_buyvec_b",pName(playerid));
		}
		else if(listitem == 2){
			if(dmwscore:getPlayerGang(playerid) - 30 < 0){
				System_send(playerid,"[帮派]购买失败,帮派积分不足");
				return;
			}
			new
				vecid = CreateVehicle(427, pX(playerid)+5,pY(playerid)+5,pZ(playerid)+2,0,random(255),random(255),-1);
			SetGVarInt("wl_dmw_tempVehicle",true,vecid);
			SetVehicleNumberPlate(vecid,gang:getGangName(gang:getPlayerGang(playerid)));
			SetVehicleVirtualWorld(vecid,DMWorld_ID);
			dmwscore:amountedPlayerGang(playerid, 0 - 30);
			gang:sendgang(gang:getPlayerGang(playerid),"dmw_dialog_buyvec_c",pName(playerid));
		}
	}
}

dmwvehicle:Command_ShowDialog(playerid){
	new
		zonegangid = zone:getOwnedGang(zone:getPlayerZoneByPosition(playerid)),
		playergangid = gang:getPlayerGang(playerid);
	if(!dmw:getPlayer(playerid)){
		System_send(playerid,"[系统]你不在大战城里,命令无效");
		return;
	}		
	if(zonegangid == INVALID_GANG_ID){
		System_send(playerid,"[大战城]你不在自己的地盘里,无法购买交通工具");
		return;
	}
	if(playergangid == INVALID_GANG_ID){
		System_send(playerid,"[大战城]你不是帮派份子,无法购买交通工具");
		return;
	}
	if(zonegangid != playergangid){
		System_send(playerid,"[大战城]你不在自己的地盘里,无法购买交通工具");
		return;
	}
	ShowPlayerDialog(playerid, g_dmwVehicle_DialogID, DIALOG_STYLE_LIST, "购买交通工具", g_dmwVehicle_purchaseDialogInfo, "选择", "取消");
}