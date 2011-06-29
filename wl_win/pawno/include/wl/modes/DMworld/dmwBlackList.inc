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