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


//#include <wl\modes\DMworld\gangzone>
zone:createZoneTable(){
	db_processstart("CREATE TABLE IF NOT EXISTS zone (id INTEGER PRIMARY key, name TEXT, minx REAL, miny REAL, minz REAL, maxx REAL, maxy REAL, maxz REAL, spx REAL, spy REAL, spz REAL, attacktime INTEGER)");
	db_processthenfree(db_dmworld);
	
	new
		DBResult:dbr;
	dbr = db_query(db_dmworld,"SELECT id FROM zone LIMIT 2");
	if(db_num_rows(dbr) == 0) db_free_result(db_query(db_dmworld,"INSERT INTO zone VALUES(NULL,'TEST_ARENA',0,0,0,0,0,0,0,0,0,0)"));
	db_free_result(dbr);
	return true;
}
zone:getZoneAmount(){
	new
		zoneAmount[11];
	db_processstart("SELECT count(*) FROM zone");
	db_processthengetresult(db_dmworld);
	if(db_num_rows(dbr)){
		db_get_field(0,zoneAmount,sizeof(zoneAmount));
	}
	db_processend();
	return strval(zoneAmount);
}
zone:getZoneMaxID(){
	new
		zoneid[11];
	db_processstart("SELECT max(id) FROM zone");
	db_processthengetresult(db_dmworld);
	if(db_num_rows(dbr)){
		db_get_field(dbr,0,zoneid,sizeof(zoneid));
	}
	db_processend();
	return strval(zoneid);
}

zone:database_struct(){
	new
		gangid = GangZoneCreate(0,1,0,1);
	if(gangid != 0) GangZoneDestroy(gangid);
	for(new i = 1,j = zone:getZoneMaxID();i <= j;i++){
		db_processstart("SELECT id,name,minx,miny,minz,maxx,maxy,maxz,spx,spy,spz,attacktime FROM zone WHERE id = %d",i);
		db_processthengetresult(db_dmworld);
		if(db_num_rows(dbr)){
			new
				id[11],name[MAX_ZONE_NAME],minx[24],miny[24],minz[24],maxx[24],maxy[24],maxz[24],spx[24],spy[24],spz[24],attacktime[24];
			db_get_field(dbr,0,id,sizeof(id));
			db_get_field(dbr,1,name,sizeof(name));
			db_get_field(dbr,2,minx,sizeof(minx));
			db_get_field(dbr,3,miny,sizeof(miny));
			db_get_field(dbr,4,minz,sizeof(minz));
			db_get_field(dbr,5,maxx,sizeof(maxx));
			db_get_field(dbr,6,maxy,sizeof(maxy));
			db_get_field(dbr,7,maxz,sizeof(maxz));
			db_get_field(dbr,8,spx,sizeof(spx));
			db_get_field(dbr,9,spy,sizeof(spy));
			db_get_field(dbr,10,spz,sizeof(spz));
			db_get_field(dbr,11,attacktime,sizeof(attacktime));
			SetGVarInt("wl_zone_id",strval(id),i);
			SetGVarString("wl_zone_name",name,i);
			SetGVarFloat("wl_zone_minx",floatstr(minx),i);
			SetGVarFloat("wl_zone_miny",floatstr(miny),i);
			SetGVarFloat("wl_zone_minz",floatstr(minz),i);
			SetGVarFloat("wl_zone_maxx",floatstr(maxx),i);
			SetGVarFloat("wl_zone_maxy",floatstr(maxy),i);
			SetGVarFloat("wl_zone_maxz",floatstr(maxz),i);
			SetGVarFloat("wl_zone_spx",floatstr(spx),i);
			SetGVarFloat("wl_zone_spy",floatstr(spy),i);
			SetGVarFloat("wl_zone_spz",floatstr(spz),i);
			SetGVarInt("wl_zone_attacktime",strval(attacktime),i);
			SetGVarInt("wl_zone_ingameid",GangZoneCreate(floatstr(minx),floatstr(miny),floatstr(maxx),floatstr(maxy)),i);
		}
		
		db_processend();
	}
	return true;
}

zone:getZoneIngameID(zoneid){
	return GetGVarInt("wl_zone_ingameid",zoneid);
}

zone:setZoneName(zoneid,name[]){
	db_processstart("UPDATE zone SET name = '%s' WHERE id = %d",zoneid);
	db_processthenfree(db_dmworld);
	SetGVarString("wl_zone_name",name,MAX_ZONE_NAME,zoneid);
	return true;
}
zone:getZoneName(zoneid){
	new
		name[MAX_ZONE_NAME];
	db_processstart("SELECT name FROM zone WHERE id = %d",zoneid);
	db_processthengetresult(db_dmworld);
	db_processresulted(){
		db_processgetfield("name",name);
	}
	db_processend();
	return name; 
}

zone:setZoneSpawnPoint(zoneid,Float:spx,Float:spy,Float:spz){
	db_processstart("UPDATE zone SET spx = %.4f, spy = %.4f, spz = %.4f WHERE id = %d",spx,spy,spz,zoneid);
	db_processthenfree(db_dmworld);
	SetGVarFloat("wl_zone_spx",spx,zoneid);
	SetGVarFloat("wl_zone_spy",spy,zoneid);
	SetGVarFloat("wl_zone_spz",spz,zoneid);
	return true;
}	
zone:getZoneSpawnPoint(zoneid,&Float:spx,&Float:spy,&Float:spz){
	spx = GetGVarFloat("wl_zone_spx",zoneid);
	spy = GetGVarFloat("wl_zone_spy",zoneid);
	spz = GetGVarFloat("wl_zone_spz",zoneid);
	return true;
}

zone:setZoneAttackTime(zoneid,attacktime){
	db_processstart("UPDATE zone SET attacktime = %d WHERE id = %d",attacktime,zoneid);
	db_processthenfree(db_dmworld);
	SetGVarInt("wl_zone_attacktime",attacktime,zoneid);
}
zone:getZoneAttackTime(zoneid){
	return GetGVarInt("wl_zone_attacktime",zoneid);
}

zone:setZoneArea(zoneid,Float:minx,Float:maxx,Float:miny,Float:maxy,Float:minz,Float:maxz){
	db_processstart("UPDATE zone SET minx = %.4f,miny = %.4f,minz = %.4f,maxx = %.4f,maxy = %.4f,maxz = %.4f WHERE id = %d",minx,miny,minz,maxx,maxy,maxz,zoneid);
	db_processthenfree(db_dmworld);
	SetGVarFloat("wl_zone_minx",minx,zoneid);
	SetGVarFloat("wl_zone_miny",miny,zoneid);
	SetGVarFloat("wl_zone_minz",minz,zoneid);
	SetGVarFloat("wl_zone_maxx",maxx,zoneid);
	SetGVarFloat("wl_zone_maxy",maxy,zoneid);
	SetGVarFloat("wl_zone_maxz",maxz,zoneid);
	return true;
}
zone:getZoneArea(zoneid,&Float:minx,&Float:maxx,&Float:miny,&Float:maxy,&Float:minz,&Float:maxz){
	minx = GetGVarFloat("wl_zone_minx",zoneid);
	miny = GetGVarFloat("wl_zone_miny",zoneid);
	minz = GetGVarFloat("wl_zone_minz",zoneid);
	maxx = GetGVarFloat("wl_zone_maxx",zoneid);
	maxy = GetGVarFloat("wl_zone_maxy",zoneid);
	maxz = GetGVarFloat("wl_zone_maxz",zoneid);	
	return true;
}
zone:removeZoneInGame(zoneid){
	db_processstart("DELETE FROM zone WHERE id = %d",zoneid);
	db_processthenfree(db_dmworld);
	GangZoneHideForAll(GetGVarInt("wl_zone_ingameid"));
	GangZoneDestroy(GetGVarInt("wl_zone_ingameid"));
	DeleteGVar("wl_zone_id",zoneid);
	DeleteGVar("wl_zone_name",zoneid);
	DeleteGVar("wl_zone_minx",zoneid);
	DeleteGVar("wl_zone_miny",zoneid);
	DeleteGVar("wl_zone_minz",zoneid);
	DeleteGVar("wl_zone_maxx",zoneid);
	DeleteGVar("wl_zone_maxy",zoneid);
	DeleteGVar("wl_zone_maxz",zoneid);
	DeleteGVar("wl_zone_spx",zoneid);
	DeleteGVar("wl_zone_spy",zoneid);
	DeleteGVar("wl_zone_spz",zoneid);
	DeleteGVar("wl_zone_attacktime",zoneid);
	DeleteGVar("wl_zone_ingameid",zoneid);	
}
zone:createZoneInGame(playerid){
	new
		Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,
		Float:spx,Float:spy,Float:spz,
		zoneid,ingameid,name[MAX_ZONE_NAME];
	if(GetGVarFloat("wl_zone_creategangzone_x1",playerid) > GetGVarFloat("wl_zone_creategangzone_x2",playerid)){
		maxx = GetGVarFloat("wl_zone_creategangzone_x1",playerid);
		minx = GetGVarFloat("wl_zone_creategangzone_x2",playerid);
	}
	else {
		maxx = GetGVarFloat("wl_zone_creategangzone_x2",playerid);
		minx = GetGVarFloat("wl_zone_creategangzone_x1",playerid);
	}
	if(GetGVarFloat("wl_zone_creategangzone_y1",playerid) > GetGVarFloat("wl_zone_creategangzone_y2",playerid)){
		maxy = GetGVarFloat("wl_zone_creategangzone_y1",playerid);
		miny = GetGVarFloat("wl_zone_creategangzone_y2",playerid);
	}
	else {
		maxy = GetGVarFloat("wl_zone_creategangzone_y2",playerid);
		miny = GetGVarFloat("wl_zone_creategangzone_y1",playerid);
	}
	if(GetGVarFloat("wl_zone_creategangzone_z1",playerid) > GetGVarFloat("wl_zone_creategangzone_z2",playerid)){
		maxz = GetGVarFloat("wl_zone_creategangzone_z1",playerid);
		minz = GetGVarFloat("wl_zone_creategangzone_z2",playerid);
	}
	else {
		maxz = GetGVarFloat("wl_zone_creategangzone_z2",playerid);
		minz = GetGVarFloat("wl_zone_creategangzone_z1",playerid);
	}
	spx = GetGVarFloat("wl_zone_creategangzone_x3",playerid);
	spy = GetGVarFloat("wl_zone_creategangzone_y3",playerid);
	spz = GetGVarFloat("wl_zone_creategangzone_z3",playerid);
	GetGVarString("wl_zone_creategangzone_name",name,sizeof(name),playerid);
	db_processstart("INSERT INTO zone VALUES (NULL,'%s',%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%d)",name,minx,miny,minz-100,maxx,maxy,maxz+100,spx,spy,spz,60*10);
	db_processthenfree(db_dmworld);
	//db_processend();
	
	zoneid = zone:getZoneMaxID();
	ingameid = GangZoneCreate(minx,miny,maxx,maxy);
	SetGVarInt("wl_zone_id",zoneid,zoneid);
	SetGVarString("wl_zone_name",name,zoneid);
	SetGVarFloat("wl_zone_minx",minx,zoneid);
	SetGVarFloat("wl_zone_miny",miny,zoneid);
	SetGVarFloat("wl_zone_minz",minz,zoneid);
	SetGVarFloat("wl_zone_maxx",maxx,zoneid);
	SetGVarFloat("wl_zone_maxy",maxy,zoneid);
	SetGVarFloat("wl_zone_maxz",maxz,zoneid);
	SetGVarFloat("wl_zone_spx",spx,zoneid);
	SetGVarFloat("wl_zone_spy",spy,zoneid);
	SetGVarFloat("wl_zone_spz",spz,zoneid);
	SetGVarInt("wl_zone_attacktime",60 * 10,zoneid);
	SetGVarInt("wl_zone_ingameid",ingameid,zoneid);

	DeleteGVar("wl_zone_creategangzone_x1",playerid);
	DeleteGVar("wl_zone_creategangzone_y1",playerid);
	DeleteGVar("wl_zone_creategangzone_z1",playerid);
	DeleteGVar("wl_zone_creategangzone_x2",playerid);
	DeleteGVar("wl_zone_creategangzone_y2",playerid);
	DeleteGVar("wl_zone_creategangzone_z2",playerid);
	DeleteGVar("wl_zone_creategangzone_x3",playerid);
	DeleteGVar("wl_zone_creategangzone_y3",playerid);
	DeleteGVar("wl_zone_creategangzone_z3",playerid);
	DeleteGVar("wl_zone_creategangzone_name",playerid);
	DeleteGVar("wl_zone_creategangzone_times",playerid);
	dmw_updateGangZoneInGameForAll(zoneid);
	System_send(playerid,"zone create|%d|%d|%s|%.3f|%.3f|%.3f|%.3f|%.3f|%.3f|%.3f|%.3f|%.3f||id,ingameid,name,minx,miny,minz,maxx,maxy,maxz,spx,spy,spz",zoneid,ingameid,name,minx,miny,minz,maxx,maxy,maxz,spx,spy,spz);
	//printf("zone create|%d|%d|%s|%.3f|%.3f|%.3f|%.3f|%.3f|%.3f|%.3f|%.3f|%.3f||id,ingameid,name,minx,miny,minz,maxx,maxy,maxz,spx,spy,spz",zoneid,ingameid,name,minx,miny,minz,maxx,maxy,maxz,spx,spy,spz);
	//writelog("[zone]Zone '%s'(%d) created, operator:%s, info(%.f,%.f,%.f,%.f,%.f,%.f,%.f,%.f,%.f)",name,zoneid,pName(playerid),minx,miny,minz,maxx,maxy,maxz,spx,spy,spz);

}
	
zone:setZoneWarState(gangzoneid,set){
	SetGVarInt("wl_zone_warstate",set,gangzoneid);
	return true;
}
zone:getZoneWarState(gangzoneid){
	return GetGVarInt("wl_zone_warstate",gangzoneid);
}

zone:setPlayerToZoneSpawn(playerid,zoneid){
	new
		Float:x,Float:y,Float:z;
	zone_getZoneSpawnPoint(zoneid,x,y,z);
	TeleportPlayer(playerid,x,y,z);
	return true;
}
zone:getPlayerZoneByPosition(playerid){
	new
		zoneid[11],
		Float:x,Float:y,Float:z;
	GetPlayerPos(playerid,x,y,z);
	db_processstart("SELECT id FROM zone WHERE minx < %.f AND maxx > %.f AND miny < %.f AND maxy > %.f",x,x,y,y);
	db_processthengetresult(db_dmworld);
	db_processresulted(){
		db_processgetfield("id",zoneid);
	}
	db_processend();
	return strval(zoneid);
}
zone:getPlayerZone3DByPosition(playerid){
	new
		zoneid[11],
		Float:x,Float:y,Float:z;
	GetPlayerPos(playerid,x,y,z);
	db_processstart("SELECT id FROM zone WHERE minx < %.f AND maxx > %.f AND miny < %.f AND maxy > %.f AND minz < %.f AND maxz > %.f",x,x,y,y,z,z);
	db_processthengetresult(db_dmworld);
	db_processresulted(){
		db_processgetfield("id",zoneid);
	}
	db_processend();
	return strval(zoneid);
}

zone:struct(){
	zone_createZoneTable();
	zone_database_struct();
	printf (" [大战城]地盘载入成功,数量:%d",zone:getZoneMaxID());
}
zone:Playerconnect(playerid){
	dmw_showGangZoneInGameForPlayer(playerid);
}
zone:playerLogin(playerid){
	dmw_showGangZoneInGameForPlayer(playerid);
}
zone:getOwnedGang(zoneid){
	return GetGVarInt("wl_zone_ownedgang",zoneid);
}
#define zone_removeOwnedGone(%1) gang_removeOwnedZone(%1)
#define zone_setOwnedGang(%1,%2) gang_setOwnedZone(%2,%1)
#define zone_setZoneGang(%1,%2) gang_setOwnedZone(%2,%1)
#define zone_setZoneOwner(%1,%2) gang_setOwnedZone(%2,%1)
#define zone_getZoneOwner(%1) zone_getOwnedGang(%1)
#define zone_getZoneGang(%1) zone_getOwnedGang(%1)
//=========================================================================
//=========================================================================
//=========================================================================