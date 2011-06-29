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


//dmworld admin

dmwdmin:createTable(){
	db_processstart("CREATE TABLE IF NOT EXISTS dmw_admin (id INTEGER PRIMARY KEY,userid INTEGER,level INTEGER)");
	db_processthenfree(db_dmworld);

	new
		DBResult:dbr;
	dbr = db_query(db_dmworld,"SELECT id FROM dmw_admin LIMIT 2");
	if(db_num_rows(dbr) == 0) db_free_result(db_query(db_dmworld,"INSERT INTO dmw_admin VALUES(NULL,0,0)"));
	db_free_result(dbr);
	
}
dmwdmin:isUserInAdminList(userid){
	new
		retval;
	db_processstart("SELECT 1 FROM dmw_admin WHERE userid = %d",userid);
	db_processthengetresult(db_dmworld);
	db_processresulted(){
		retval = true;
	}
	db_processend();
	return retval;
}


dmwdmin:getMaxID(){
	new
		id[11];
	db_processstart("SELECT max(id) FROM dmw_admin");
	db_processthengetresult(db_dmworld);
	db_processresulted(){
		db_get_field(dbr,0,id,sizeof(id));
	}
	db_processend();
	return strval(id);
}

dmwdmin:struct(){
	dmwdmin:createTable();
	
	for(new i = 1, j = dmwdmin:getMaxID(); i <= j; i++){
		db_processstart("SELECT id,userid,level FROM dmw_admin WHERE id = %d",i);
		db_processthengetresult(db_dmworld);
		db_processresulted(){
			new
				id[11],userid[11],level[11];
			db_processgetfield("id",id);
			db_processgetfield("userid",userid);
			db_processgetfield("level",level);
			SetGVarInt("wl_user_dmw_admindid",strval(id),strval(userid));
			SetGVarInt("wl_user_dmw_adminlevel",strval(level),strval(userid));
		}
		db_processend();
	}
	
	return true;
}

dmwdmin:setUserAdminLevel(userid,level){
	if(dmwdmin:isUserInAdminList(userid)){
		db_processstart("UPDATE dmw_admin SET level = %d WHERE userid = %d",level,userid);
		db_processthenfree(db_dmworld);
	}
	else {
		db_processstart("INSERT INTO dmw_admin VALUES(NULL,%d,%d)",userid,level);
		db_processthenfree(db_dmworld);
	}
	SetGVarInt("wl_user_dmw_adminlevel",level,userid);
	return true;
}
dmwdmin:getUserAdminLevel(userid){
	return GetGVarInt("wl_user_dmw_adminlevel",userid);
}
dmwdmin:setPlayerAdminLevel(playerid){
	return dmwdmin:setUserAdminLevel(user:getPlayerUserID(playerid));
}
dmwdmin:getPlayerAdminLevel(playerid){
	return dmwdmin:getUserAdminLevel(user:getPlayerUserID(playerid));
}