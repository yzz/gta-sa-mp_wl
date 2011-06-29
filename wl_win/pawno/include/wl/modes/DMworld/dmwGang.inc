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












//#include <wl\modes\DMworld\gang>





gang:struct(){
	gang:createGangTable();
	gang:database_struct();
	for(new i = 1,j = gang:getGangMaxID();i <= j;i++){
		gang:setGangAttackZone(i,INVALID_GANG_ZONE_ID);
	}
	printf (" [大战城]帮派载入成功,数量:%d",gang:getGangMaxID());
}

gang:createGangTable(){
	sqlquery_processstart("CREATE TABLE IF NOT EXISTS gang_stat (id INTEGER PRIMARY key,name TEXT,owner TEXT,spx REAL,spy REAL, spz REAL,member TEXT DEFAULT '_',relation TEXT DEFAULT '_',ownedzone TEXT DEFAULT '_')");
	sqlquery_processthenfree(db_dmworld);
	
	new
		DBResult:dbr;
	dbr = db_query(db_dmworld,"SELECT id FROM gang_stat LIMIT 2");
	if(db_num_rows(dbr) == 0) db_free_result(db_query(db_dmworld,"INSERT INTO gang_stat VALUES(NULL,'TEST','TEST',0,0,0,'_','_','_')"));
	db_free_result(dbr);	
	return true;
}
gang:createGangInDatabase(gangname[],gangowner[]){
	//printf "create gang:%s %s",gangname,gangowner
	db_processstart("INSERT INTO gang_stat VALUES(NULL,'%s','%s',0.0,0.0,0.0,'_','_','_',0)",gangname,gangowner);
	db_processthenfree(db_dmworld);
	new
		gangid = gang_getGangMaxID();
	SetGVarInt("wl_gang_id",gangid,gangid);
	SetGVarString("wl_gang_name",gangname,gangid);
	SetGVarString("wl_gang_owner",gangowner,gangid);
	return gangid;
}
// //TODO
//gang_removeGangInDatabase(gangid){
//	db_processtart("DELETE FROM gang_stat WHERE id %d")

new
	tmparray[5000];

gang:database_struct(){
	for(new i,j = sizeof(tmparray);i < j;i++){
		tmparray[i] = '\0';	
	}
	for(new i = 1,j = gang:getGangMaxID();i <= j;i++){
		db_processstart("SELECT id,name,owner,member,relation,ownedzone,spx,spy,spz FROM gang_stat WHERE id = %d",i);
		db_processthengetresult(db_dmworld);
		if(db_num_rows(dbr)){	
			new 
				pos,
				id[11],name[MAX_GANG_NAME],owner[MAX_PLAYER_NAME],position[25];	
				
			db_get_field(dbr,0,id,sizeof(id));
			SetGVarInt("wl_gang_id",strval(id),i);
			
			db_get_field(dbr,1,name,sizeof(name));
			SetGVarString("wl_gang_name",name,i);
			
			db_get_field(dbr,2,owner,sizeof(owner));
			SetGVarString("wl_gang_owner",owner,i);
	
			db_get_field(dbr,3,tmparray,sizeof(tmparray));
			new
				userid[11],level[11];
			while((pos = strfind(tmparray,"|",true,pos)) != -1){
				strmid(level,tmparray,pos-2,pos);
				strmid(userid,tmparray,pos-9,pos-3);
				SetGVarInt("wl_user_gangid",i,strval(userid));
				//printf("gang:%d userid:%d",strval(userid),GetGVarInt("wl_user_gangid",strval(userid)));
				SetGVarInt("wl_user_inganglevel",strval(level),strval(userid));
				if(tmparray[++pos] == '_') break;
			}
			db_get_field(dbr,4,tmparray,sizeof(tmparray));
			
			new
				gangid[11],relation[11];
			pos = 0;
			while((pos = strfind(tmparray,"|",true,pos)) != -1){
				//printf "%s",tmparray
				strmid(relation,tmparray,pos-2,pos);
				strmid(gangid,tmparray,pos-9,pos-3);
				SetGVarInt("wl_gang_relation",strval(relation),getDoubleRelationList(i,strval(gangid)));
				//printf "relation:%d|%d|%d",i,strval(gangid),strval(relation)
				if(tmparray[++pos] == '_')break;
			}
			
			db_get_field(dbr,5,tmparray,sizeof(tmparray));
			new
				zoneid[11];
			pos = 0;
			while((pos = strfind(tmparray,"|",true,pos)) != -1){
				strmid(zoneid,tmparray,pos-6,pos);
				SetGVarInt("wl_zone_ownedgang",i,strval(zoneid));
				if(tmparray[++pos] == '_')break;
			}
			
			db_get_field(dbr,6,position,sizeof(position));
			SetGVarFloat("wl_gang_spx",floatstr(position),i);

			db_get_field(dbr,7,position,sizeof(position));
			SetGVarFloat("wl_gang_spy",floatstr(position),i);

			db_get_field(dbr,8,position,sizeof(position));
			SetGVarFloat("wl_gang_spz",floatstr(position),i);			
		}
		db_free_result(dbr);
	}
	
	return true;
}
gang:playerText(playerid,text[]){
	if(text[0] == '!' && text[1]){
        if(gang:getPlayerGang(playerid) != INVALID_GANG_ID){
            new 
				sendstr[MAX_MSG_STR];
            format(sendstr, sizeof(sendstr),"[TC]%s(%d): %s", pName(playerid),playerid, text[1]);
			loopPlayer(i){
				if(gang:getPlayerGang(playerid) == gang:getPlayerGang(i)){
					SendClientMessage(i,COLOR_DMWORLD,sendstr);
				}
			}
			return false;
		}
		else {
			gang:send(playerid,"gang_sendmsg_failed_notmember");
			return true;
		}
	}
    return true;
}
#define MAX_PREGANGLOGIN_TIME		(60)

public gang:PlayerPreloginItter(playerid){ debug_public_track("gang:PlayerPreloginItter(playerid){");
	if(IsPlayerConnected(playerid) && gang:getPlayerGang(playerid) == INVALID_GANG_ID){
		gang:send(playerid,"gang_unregisteredmember_kick",gang:getPlayerGangTag(playerid));
		Kick(playerid);
		DeletePVar(playerid,"wl_plr_preganglogin_timer");
	}
	return true;
}

gang:playerConnect(playerid){
	if(gang:isPlayerHasGangTag(playerid)){
		if(gang:isLegalTag(gang:getPlayerGangTag(playerid))){
			new
				gangid;
			if(!gang:isTagRegistered(gang:getPlayerGangTag(playerid))){

				gangid = gang:createGangInDatabase(gang:getPlayerGangTag(playerid),"none");
				gang:setGangRelation(gangid,gangid,gang_relation_alliance);		
			}
			gangid = gang:getGangByTag(gang:getPlayerGangTag(playerid));
			if(gangid != INVALID_GANG_ID && gang:isTagRegistered(gang:getPlayerGangTag(playerid))){
				if(gang:isGangOwnerNull(gangid)){
					gang:tmpsetPlayerGang(playerid,gangid);
					gang:send(playerid,"gang_unregisteredgang_hint1",gang:getPlayerGangTag(playerid));
					gang:send(playerid,"gang_unregisteredgang_hint2");
				}
				else {
					SetPVarInt(playerid,"wl_plr_preganglogin_timer",SetTimerEx("gang_PlayerPreloginItter",1000*MAX_PREGANGLOGIN_TIME,false,"i",playerid));
					gang:send(playerid,"gang_unregisteredmember_warn1",gang:getPlayerGangTag(playerid));
					gang:send(playerid,"gang_unregisteredmember_warn2",MAX_PREGANGLOGIN_TIME);
				}
			}
		}
		else {
			gang:send(playerid,"gang_unregisteredgang_illeagltag",gang:getPlayerGangTag(playerid));
		}
	}
}

		
		
gang:playerLogin(playerid){ 
	#pragma unused playerid
}
gang:getGangAmount(){
	new
		gang_amount[11];
	db_processstart("SELECT count(*) FROM gang_stat");
	db_processthengetresult(db_dmworld);
	if(db_num_rows(dbr)){
		db_get_field(dbr,0,gang_amount,sizeof(gang_amount));
	}
	db_processend();
	return strval(gang_amount);
}
gang:getGangMaxID(){
	new
		id[11];
	db_processstart("SELECT max(id) FROM gang_stat");
	db_processthengetresult(db_dmworld);
	if(db_num_rows(dbr)){
		db_get_field(dbr,0,id,sizeof(id));
	}
	db_processend();
	return strval(id);
}	

gang:setGangSpawnPoint(gangid,Float:spx,Float:spy,Float:spz){
	db_processstart("UPDATE gang_stat SET spx = %.4f, spy = %.4f, spz = %.4f WHERE id = %d",spx,spy,spz,gangid);
	db_processthenfree(db_dmworld);
	SetGVarFloat("wl_gang_spx",spx,gangid);
	SetGVarFloat("wl_gang_spy",spy,gangid);
	SetGVarFloat("wl_gang_spz",spz,gangid);
	return true;
}	
gang:getGangSpawnPoint(gangid,&Float:spx,&Float:spy,&Float:spz){
	spx = GetGVarFloat("wl_gang_spx",gangid);
	spy = GetGVarFloat("wl_gang_spy",gangid);
	spz = GetGVarFloat("wl_gang_spz",gangid);
	return true;
}

gang:setGangName(gangid,name[]){
	db_processstart("UPDATE gang_stat SET name = '%s' WHERE id %d",name,gangid);
	db_processthenfree(db_dmworld);
	SetGVarString("wl_gang_name",name,gangid);
	return true;
}
gang:getGangName(gangid){
	new
		gangname[MAX_GANG_NAME];
	GetGVarString("wl_gang_name",gangname,sizeof(gangname),gangid);
	return gangname;
}

gang:setGangOwner(gangid,owner[]){
	db_processstart("UPDATE gang_stat SET owner = '%s' WHERE id %d",owner,gangid);
	db_processthenfree(db_dmworld);
	SetGVarString("wl_gang_owner",owner,gangid);
	return true;
}
gang:getGangOwner(gangid){
	new
		owner[MAX_PLAYER_NAME];
	GetGVarString("wl_gang_owner",owner,sizeof(owner),gangid);
	return owner;
}
/*
gang:setGangOwnerNull(gangid){
	gang:setGangOwner(gangid,"none");
	return true;
}
*/
gang:isGangOwnerNull(gangid){
	return (!strcmp(gang:getGangOwner(gangid),"none",false,4));
}

gang:getGangRelation(gangid1,gangid2){
	return GetGVarInt("wl_gang_relation",getDoubleRelationList(gangid1,gangid2));
}
gang:setGangRelation(gangid1,gangid2,relation){
	gang:removeGangRelation(gangid1,gangid2);
	db_processstart("UPDATE gang_stat SET relation = replace(relation,'_','%06d:%02d|_') WHERE id = %d",gangid2,relation,gangid1);
	db_processthenfree(db_dmworld);
	SetGVarInt("wl_gang_relation",relation,getDoubleRelationList(gangid1,gangid2));
	return true;
}
gang:removeGangRelation(gangid1,gangid2){
	new
		oldrelation = gang_getGangRelation(gangid1,gangid2);
	db_processstart("UPDATE gang_stat SET relation = replace(relation,'%06d:%02d|','') WHERE id = %d",gangid2,oldrelation,gangid1);
	db_processthenfree(db_dmworld);
	SetGVarInt("wl_gang_relation",gang_relation_neutral,getDoubleRelationList(gangid1,gangid2));
	return true;
}	

gang:removeOwnedZone(zoneid){
	db_processstart("UPDATE gang_stat SET ownedzone = replace(ownedzone,'%06d|','')",zoneid);
	db_processthenfree(db_dmworld);
	SetGVarInt("wl_zone_ownedgang",INVALID_GANG_ID,zoneid);
	return true;
}
gang:setOwnedZone(gangid,zoneid){
	zone_removeOwnedGone(zoneid);
	db_processstart("UPDATE gang_stat SET ownedzone = replace(ownedzone,'_','%06d|_') WHERE id = %d",zoneid,gangid);
	db_processthenfree(db_dmworld);
	SetGVarInt("wl_zone_ownedgang",gangid,zoneid);
	return true;
}

gang:isOwnedZone(gangid,zoneid){
	return (GetGVarInt("wl_zone_ownedgang",zoneid) == gangid);
}

gang:removeUserFromGang(userid){
	new
		level = gang_getUserInGangLevel(userid);
	if(level){
		db_processstart("UPDATE gang_stat SET member = replace(member,'%06d:%02d|','')",userid,level);
		db_processthenfree(db_dmworld);
		return true;
	}
	SetGVarInt("wl_user_gangid",INVALID_GANG_ID,userid);
	return false;
}
gang:setUserGang(userid,gangid){
	if(gang_getUserGang(userid) != INVALID_GANG_ID){
		gang_removeUserFromGang(userid);
	}
	db_processstart("UPDATE gang_stat SET member = replace(member,'_','%06d:00|_') WHERE id = %d",userid,gangid);
	db_processthenfree(db_dmworld);
	SetGVarInt("wl_user_gangid",gangid,userid);
	return true;
}
gang:getUserGang(userid){
	//printf("userid:%d gangid:%d",userid,GetGVarInt("wl_user_gangid",userid));
	return GetGVarInt("wl_user_gangid",userid);
}
gang:setUserInGangLevel(userid,level){
	new
		oldlevel = gang_getUserInGangLevel(userid),
		gangid = gang_getUserGang(userid);
	if(gang_getUserGang(userid) != INVALID_GANG_ID){
		db_processstart("UPDATE gang_stat SET member = replace(member,'%06d:%02d|','%06d:%02d|') WHERE id = %d",userid,oldlevel,userid,level,gangid);
		db_processthenfree(db_dmworld);
		//printf "%06d,%02d,%06d,%02d,%d",userid,oldlevel,userid,level,gangid
	}
	else {
		return false;
	}
	SetGVarInt("wl_user_inganglevel",level,userid);
	return true;
}
gang:getUserInGangLevel(userid){
	return GetGVarInt("wl_user_inganglevel",userid);
}
gang:getUserGangName(userid){
	return gang_getGangName(gang_getUserGang(userid));
}
gang:setPlayerGang(playerid,gangid){
	return gang_setUserGang(user:getPlayerUserID(playerid),gangid);
}
gang:getPlayerGang(playerid){
	if(gang:tmpgetPlayerGang(playerid) != INVALID_GANG_ID){
		//System_sendAll("tmpgang %d",gang:tmpgetPlayerGang(playerid));
		return gang:tmpgetPlayerGang(playerid);
	}
	//System_sendAll("orggang %d",gang_getUserGang(user:getPlayerUserID(playerid)));
	return gang_getUserGang(user:getPlayerUserID(playerid));
}
gang:tmpsetPlayerGang(playerid,gangid){
	SetPVarInt(playerid,"wl_plr_tmpgang",gangid);
	return true;
}
gang:tmpgetPlayerGang(playerid){
	return GetPVarInt(playerid,"wl_plr_tmpgang");
}
gang:setPlayerInGangLevel(playerid,level){
	return gang_setUserInGangLevel(user:getPlayerUserID(playerid),level);
}
gang:getPlayerInGangLevel(playerid){
	return gang_getUserInGangLevel(user:getPlayerUserID(playerid));
}
gang:getPlayerGangName(playerid){
	return gang_getUserGangName(userid);
}

gang:isTagRegistered(tag[]){
	new
		retval;
	db_processstart("SELECT id FROM gang_stat WHERE name = '%s'",tag);
	db_processthengetresult(db_dmworld);
	retval = db_num_rows(dbr);
	db_processend();
	return retval;
}
gang:getGangByTag(tag[]){
	new
		id[12];
	db_processstart("SELECT id FROM gang_stat WHERE name = '%s'",tag);
	db_processthengetresult(db_dmworld);
	if(db_num_rows(dbr)){
		db_get_field(dbr,0,id,sizeof(id));
	}
	db_processend();
	return strval(id);
}

gang:setGangWarState(gangid,bool:set){
	SetGVarInt("wl_gang_warstate",set,gangid);
	return true;
}
gang:getGangWarState(gangid){
	return GetGVarInt("wl_gang_warstate",gangid);
}
gang:setGangAttackZone(gangid,gangzoneid){
	SetGVarInt("wl_gang_attackzone",gangzoneid,gangid);
	return true;
}	
gang:getGangAttackZone(gangid){
	return GetGVarInt("wl_gang_attackzone",gangid);
}
gang:setGangAttackTimer(gangid,timer){
	SetGVarInt("wl_gang_attacktimer",timer,gangid);
	return true;
}	
gang:getGangAttackTimer(gangid){
	return GetGVarInt("wl_gang_attacktimer",gangid);
}
gang:setGangAttackTime(gangid,time){
	SetGVarInt("wl_gang_attacktime",time,gangid);
	return true;
}	
gang:getGangAttackTime(gangid){
	return GetGVarInt("wl_gang_attacktime",gangid);
}
gang:activeGangAttckTimer(gangid){
	gang:setGangAttackTimer(gangid,SetTimerEx("dmw_attackZoneItterCheck",1001,true,"ii",gangid,gang:getGangAttackZone(gangid)));
	return true;
}
gang:deactiveGangAttackTimer(gangid){
	KillTimer(gang:getGangAttackTimer(gangid));
	return true;
}

gang:isPlayerGangAttacking(playerid){
	if(gang:getGangAttackZone(gang:getPlayerGang(playerid)) == INVALID_GANG_ZONE_ID){
		return false;
	}
	return true;
}

gang:isLegalTag(tag[]){
	new
		len = strlen(tag);
	if(len && tag[0] == '[' && tag[len-1] == ']'){
		for(new i = 1;i < len-1;i++){
			if((tag[i] >= 'a' && tag[i] <= 'z') || (tag[i] >= 'A' && tag[i] <= 'Z') || (tag[i] >= '0' && tag[i] <= '9') || tag[i] == '.' || tag[i] == '_'){
				continue;
			}
			else {
				return false;
			}
		}
	}
	else return false;
	return true;
}

gang:getPlayerGangTag(playerid){
	new
		retval[MAX_PLAYER_NAME];
	if(gang:isPlayerHasGangTag(playerid)){
		format(retval,strfind(pName(playerid),"]")+2,"%s",pName(playerid));
	}
	return retval;
}
gang:isPlayerHasGangTag(playerid){
	new
		pname[MAX_PLAYER_NAME];
	GetPlayerName(playerid,pname,sizeof(pname));
	return (pname[0] == '[' && strfind(pname,"]") != -1);
}

//=========================================================================
//=========================================================================
//=========================================================================
