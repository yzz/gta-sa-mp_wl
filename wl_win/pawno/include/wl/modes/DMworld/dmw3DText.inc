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