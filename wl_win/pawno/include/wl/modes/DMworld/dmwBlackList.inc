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


//#include <wl/modes/DMworld/blacklistset>
dmw:createBlacklistTable(){
	new
		sqlquery[MAX_SQL_STR];
	format(sqlquery,sizeof(sqlquery),"CREATE TABLE IF NOT EXISTS dmw_blacklist (banid INTEGER PRIMARY KEY,bantype TEXT,banstr TEXT)");
	db_free_result(db_query(db_dmworld,sqlquery));
	
	new
		DBResult:dbr;
	dbr = db_query(db_dmworld,"SELECT banid FROM dmw_blacklist LIMIT 2");
	if(db_num_rows(dbr) == 0) db_free_result(db_query(db_dmworld,"INSERT INTO dmw_blacklist VALUES(NULL,'0','0')"));
	db_free_result(dbr);
	return true;
}
dmw:setGangTagInBlackList(const gang[]){
	new
		sqlquery[MAX_MSG_STR*2],
		DBResult:dbr;
	format(sqlquery,sizeof(sqlquery),"SELECT banid WHERE bantype = 'gang' AND banstr = '%s' FROM dmw_blacklist",gang);
	dbr = db_query(db_dmworld,sqlquery);
	if(db_num_rows(dbr) == 0){
		format(sqlquery,sizeof(sqlquery),"INSERT INTO dmw_blacklist VALUES (NULL,'gang','%s')",gang);
		db_query(db_dmworld,sqlquery);
	}
	db_free_result(dbr);
	return true;
}
dmw:removeGangTagInBlackList(const gang[]){
	new
		sqlquery[MAX_MSG_STR*2];
	format(sqlquery,sizeof(sqlquery),"DELETE FROM dmw_blacklist WHERE bantype = 'gang' AND banstr = '%s'",gang);
	db_free_result(db_query(db_dmworld,sqlquery));
	return true;
}
dmw:isGangTagInBlackList(const gang[]){
	new
		sqlquery[MAX_MSG_STR*2],
		DBResult:dbr,
		retval;
	format(sqlquery,sizeof(sqlquery),"SELECT banid FROM dmw_blacklist WHERE bantype = 'gang' AND banstr = '%s'",gang);
	dbr = db_query(db_dmworld,sqlquery);
	retval = (db_num_rows(dbr) != 0);
	db_free_result(dbr);
	return retval;
}

dmw:setNameInBlackList(const name[]){
	new
		sqlquery[MAX_MSG_STR*2],
		DBResult:dbr;
	format(sqlquery,sizeof(sqlquery),"SELECT banid FROM dmw_blacklist WHERE bantype = 'name' AND banstr = '%s'",name);
	dbr = db_query(db_dmworld,sqlquery);
	if(db_num_rows(dbr) == 0){
		format(sqlquery,sizeof(sqlquery),"INSERT INTO dmw_blacklist VALUES (NULL,'name','%s')",name);
		db_query(db_dmworld,sqlquery);
	}
	db_free_result(dbr);
	return true;
}
dmw:removeNameInBlackList(const name[]){
	new
		sqlquery[MAX_MSG_STR*2];
	format(sqlquery,sizeof(sqlquery),"DELETE FROM dmw_blacklist WHERE bantype = 'name' AND banstr = '%s'",name);
	db_free_result(db_query(db_dmworld,sqlquery));
	return true;
}
dmw:isNameInBlackList(const name[]){
	new
		sqlquery[MAX_MSG_STR*2],
		DBResult:dbr,
		retval;
	format(sqlquery,sizeof(sqlquery),"SELECT banid FROM dmw_blacklist WHERE bantype = 'name' AND banstr = '%s'",name);
	dbr = db_query(db_dmworld,sqlquery);
	retval = (db_num_rows(dbr) != 0);
	db_free_result(dbr);
	return retval;
}
 
dmw:allowGang(gangid){
	new
		sqlquery[MAX_MSG_STR*2],
		DBResult:dbr;
	format(sqlquery,sizeof(sqlquery),"SELECT gang_name WHERE gangid = %d FROM gang_state",gangid);
	dbr = db_query(db_dmworld,sqlquery);
	if(db_num_rows(dbr) != 0){
		new
			gangtag[MAX_MSG_STR];
		db_get_field(dbr,0,gangtag,sizeof(gangtag));
		if(dmw_isGangTagInBlackList(gangtag)){
			dmw_removeGangTagInBlackList(gangtag);
			loopPlayer(playerid){
				if(!strcmp(gang:getPlayerGangTag(playerid),gangtag,true)){
					//dmw_setPlayerAllowedIn(playerid);
					CallLocalFunction("dmw_OnPlayerAllowedIn","i",playerid);
				}
			}
		}
	}
	db_free_result(dbr);	
	return true;
}
dmw:disallowGang(gangid){
	new
		sqlquery[MAX_MSG_STR*2],
		DBResult:dbr;
	format(sqlquery,sizeof(sqlquery),"SELECT gang_name FROM gang_state WHERE gangid = %d",gangid);
	dbr = db_query(db_dmworld,sqlquery);
	if(db_num_rows(dbr) != 0){
		new
			gangtag[MAX_MSG_STR];
		db_get_field(dbr,0,gangtag,sizeof(gangtag));
		if(!dmw_isGangTagInBlackList(gangtag)){
			dmw_setGangTagInBlackList(gangtag);
			loopPlayer(playerid){
				if(!strcmp(gang:getPlayerGangTag(playerid),gangtag,true)){
					//dmw_setPlayerDisallowedIn(playerid);
					CallLocalFunction("dmw_OnPlayerDisallowedIn","i",playerid);
				}
			}
		}
	}
	db_free_result(dbr);	
	return true;
}	
dmw:disallowPlayer(playerid){
	if(!dmw_isNameInBlackList(pName(playerid))){
		dmw_setNameInBlackList(pName(playerid));
		//dmw_setPlayerDisallowedIn(playerid);
	}		CallLocalFunction("dmw_OnPlayerDisallowedIn","i",playerid);

	return true;
}	
dmw:allowPlayer(playerid){
	if(dmw_isNameInBlackList(pName(playerid))){
		dmw_removeNameInBlackList(pName(playerid));
		//dmw_setPlayerAllowedIn(playerid);
		CallLocalFunction("dmw_OnPlayerAllowedIn","i",playerid);
	}
	return true;
}
	
dmw:blacklist_Player_connect(playerid){
	if(dmw_isNameInBlackList(pName(playerid)) || (gang:isPlayerHasGangTag(playerid) && dmw_isGangTagInBlackList(gang:getPlayerGangTag(playerid)))){
		//dmw_setPlayerDisallowedIn(playerid);
	}
	else {
		//dmw_setPlayerAllowedIn(playerid);
	}
}
dmw:blacklist_struct(){
	dmw_createBlacklistTable();
}
