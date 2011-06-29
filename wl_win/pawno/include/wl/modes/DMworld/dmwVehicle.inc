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
	//printf(" [��ս��]��ͨ��������ɹ�,����:%d",vecamount);
	
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
			С����  05����  -  ���оӼұر�\n�Ȼ���  20����  -  ������Ѫ��\nװ�׳�  30����  -  �������׳�\n \
			447С��ȸ  476Rustler  487Maverick  423Hunter \
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
				System_send(playerid,"[����]����ʧ��,���ɻ��ֲ���");
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
				System_send(playerid,"[����]����ʧ��,���ɻ��ֲ���");
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
				System_send(playerid,"[����]����ʧ��,���ɻ��ֲ���");
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
		System_send(playerid,"[ϵͳ]�㲻�ڴ�ս����,������Ч");
		return;
	}		
	if(zonegangid == INVALID_GANG_ID){
		System_send(playerid,"[��ս��]�㲻���Լ��ĵ�����,�޷�����ͨ����");
		return;
	}
	if(playergangid == INVALID_GANG_ID){
		System_send(playerid,"[��ս��]�㲻�ǰ��ɷ���,�޷�����ͨ����");
		return;
	}
	if(zonegangid != playergangid){
		System_send(playerid,"[��ս��]�㲻���Լ��ĵ�����,�޷�����ͨ����");
		return;
	}
	ShowPlayerDialog(playerid, g_dmwVehicle_DialogID, DIALOG_STYLE_LIST, "����ͨ����", g_dmwVehicle_purchaseDialogInfo, "ѡ��", "ȡ��");
}