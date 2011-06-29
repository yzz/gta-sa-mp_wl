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



dmw:attackstart_3DText(gangid,zoneid){
	new
		tmpstr[MAX_MSG_STR],
		hour,minute,second;
	convertSecondToTime(zone:getZoneAttackTime(zoneid),hour,minute,second);
	
	new
		//Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,
		Float:midx,Float:midy,Float:midz;
	//zone:getZoneArea(zoneid,minx,miny,maxx,maxy,minz,maxz);
	zone:getZoneSpawnPoint(zoneid,midx,midy,midz);
	//getZoneMidpoint(midx,midy,midz,minx,miny,maxx,maxy,minz,maxz);
	loopPlayer(playerid){
		if(dmw:getPlayer(playerid)){
			if(gang:getPlayerGang(playerid) == gangid){
				format(tmpstr,sizeof(tmpstr),"Attck time left:%02d:%02d:%02d",hour,minute,second);
				SetPVarInt(playerid,"wl_dmw_pTime3DText",_:CreatePlayer3DTextLabel(playerid,tmpstr,0xa9a9a9FF,midx,midy,midz+2,400,.testLOS = true));
				SetPlayerMapIcon(playerid,DMW_ICON_ID,midx,midy,midz,random(62-58) + 58,COLOR_SYSTEM);
			}
			else if(gang:getPlayerGang(playerid) == zone:getOwnedGang(zoneid)){
				//if(!dmw:isZoneAttackedByMultiGang(zoneid)){
					format(tmpstr,sizeof(tmpstr),"Defence time left:%02d:%02d:%02d",hour,minute,second);
					SetPlayerMapIcon(playerid,DMW_ICON_ID,midx,midy,midz,random(62-58) + 58,COLOR_SYSTEM);
					SetPVarInt(playerid,"wl_dmw_pTime3DText",_:CreatePlayer3DTextLabel(playerid,tmpstr,0xa9a9a9FF,midx,midy,midz+2,400,.testLOS = true));
				//}
			}
		}
	}
}

dmw:attackstop_3DText(gangid,zoneid){
	loopPlayer(playerid){
		if(gang:getPlayerGang(playerid) == gangid){
			DeletePlayer3DTextLabel(playerid,PlayerText3D:GetPVarInt(playerid,"wl_dmw_pTime3DText"));
			SetPVarInt(playerid,"wl_dmw_pTime3DText",INVALID_3DTEXT_ID);
			RemovePlayerMapIcon(playerid,DMW_ICON_ID);
		}
		else if(!zone:getZoneWarState(zoneid)){
			if(gang:getPlayerGang(playerid) == zone:getOwnedGang(zoneid)){
				DeletePlayer3DTextLabel(playerid,PlayerText3D:GetPVarInt(playerid,"wl_dmw_pTime3DText"));
				SetPVarInt(playerid,"wl_dmw_pTime3DText",INVALID_3DTEXT_ID);
				RemovePlayerMapIcon(playerid,DMW_ICON_ID);
			}
		}
	}
}

dmw:attackwin_3DText(gangid,zoneid){
	loopPlayer(playerid){
		if(gang:getPlayerGang(playerid) == gangid){
			DeletePlayer3DTextLabel(playerid,PlayerText3D:GetPVarInt(playerid,"wl_dmw_pTime3DText"));
			SetPVarInt(playerid,"wl_dmw_pTime3DText",INVALID_3DTEXT_ID);
			RemovePlayerMapIcon(playerid,DMW_ICON_ID);
		}
		if(gang:getGangAttackZone(gang:getPlayerGang(playerid)) == zoneid){
			DeletePlayer3DTextLabel(playerid,PlayerText3D:GetPVarInt(playerid,"wl_dmw_pTime3DText"));
			SetPVarInt(playerid,"wl_dmw_pTime3DText",INVALID_3DTEXT_ID);
			RemovePlayerMapIcon(playerid,DMW_ICON_ID);
		}
		if(gang:getPlayerGang(playerid) == zone:getOwnedGang(zoneid)){
			DeletePlayer3DTextLabel(playerid,PlayerText3D:GetPVarInt(playerid,"wl_dmw_pTime3DText"));
			SetPVarInt(playerid,"wl_dmw_pTime3DText",INVALID_3DTEXT_ID);
			RemovePlayerMapIcon(playerid,DMW_ICON_ID);
		}
	}
}

dmw:attackupdate_Text3D(gangid,zoneid){
	new	
		tmpstr[128],
		hour,minute,second;
	convertSecondToTime(zone:getZoneAttackTime(zoneid) - gang_getGangAttackTime(gangid),hour,minute,second);
	new
		//Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,
		Float:midx,Float:midy,Float:midz;
	//zone:getZoneArea(zoneid,minx,miny,maxx,maxy,minz,maxz);
	zone:getZoneSpawnPoint(zoneid,midx,midy,midz);
	loopPlayer(playerid){
		if(dmw:getPlayer(playerid)){
			if(gang:getPlayerGang(playerid) == gangid){
				format(tmpstr,sizeof(tmpstr),"Attck time left:%02d:%02d:%02d",hour,minute,second);
				UpdatePlayer3DTextLabelText(playerid,PlayerText3D:GetPVarInt(playerid,"wl_dmw_pTime3DText"),0xa9a9a9FF,tmpstr);
				SetPlayerMapIcon(playerid,DMW_ICON_ID,midx,midy,midz,random(62-58) + 58,COLOR_SYSTEM);
			}
			else if(gang:getPlayerGang(playerid) == zone:getOwnedGang(zoneid)){
				format(tmpstr,sizeof(tmpstr),"Defence time left:%02d:%02d:%02d",hour,minute,second);
				UpdatePlayer3DTextLabelText(playerid,PlayerText3D:GetPVarInt(playerid,"wl_dmw_pTime3DText"),0xa9a9a9FF,tmpstr);
				SetPlayerMapIcon(playerid,DMW_ICON_ID,midx,midy,midz,random(62-58) + 58,COLOR_SYSTEM);
			}
		}
	}
}