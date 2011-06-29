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









new
	DB:db_race_main,
	DB:db_race_record;


Race_DB_struct(){	
	db_race_main = db_open("wl/race/race_std.db");
	db_race_record = db_open("wl/race/race_record.db");
	new
		sqlstr[MAX_SQL_STR];
	
	
	format(sqlstr,sizeof(sqlstr),"CREATE TABLE IF NOT EXISTS race_stat  ( \
		id INTEGER PRIMARY KEY, name TEXT, password TEXT,builder TEXT,description TEXT,raced_times INTEGER, \
		lastrundate	TEXT,interior INTEGER,cpAmount INTEGER,lenth REAL )");	
	db_free_result(db_query(db_race_main,sqlstr));
	

	format(sqlstr,sizeof(sqlstr),"CREATE TABLE IF NOT EXISTS `race_records`  (  \
		id INTEGER PRIMARY KEY,name TEXT ,builder TEXT , \
		winner TEXT ,usetime INTEGER,vecid INTEGER,vechp REAL,finishdate TEXT )");
	db_free_result(db_query(db_race_record,sqlstr)); 
}


stock Race_DB_isValid(rid){
	new
		DBResult:dbr,
		sqlstr[MAX_MSG_STR*2],
		retval;
	format(sqlstr,sizeof(sqlstr),"SELECT id FROM race_stat WHERE id = %d",rid);
	dbr = db_query(db_race_main,sqlstr);
	if(db_num_rows(dbr))retval = true;
	db_free_result(dbr);
	return retval;
}	

stock Race_DB_getridFromName(const race_name[]){
	new
		DBResult:dbr,
		id[11],
		sqlstr[MAX_MSG_STR*2],
		retval_raceid;
	format(sqlstr,sizeof(sqlstr),"SELECT id FROM race_stat WHERE name = '%s'",race_name);
	dbr = db_query(db_race_main,sqlstr);
	db_get_field(dbr,0,id,sizeof(id));
	if(db_num_rows(dbr)) retval_raceid = strval(id);
	else retval_raceid = INVALID_RACE_ID;
	db_free_result(dbr);
	return retval_raceid;
}

stock Race_DB_getNameFromrid(const rid){
	new
		DBResult:dbr,
		retval_race_name[MAX_RACE_NAME],
		sqlstr[MAX_MSG_STR*2];
	format(sqlstr,sizeof(sqlstr),"SELECT name FROM race_stat WHERE id = %d",rid);
	dbr = db_query(db_race_main,sqlstr);
	if(db_num_rows(dbr)){	
		db_get_field(dbr,0,retval_race_name,sizeof(retval_race_name));
	}
	db_free_result(dbr);
	return retval_race_name;
}
	


stock Race_DB_getMaxrid(){
	new
		DBResult:dbr,
		rid[11],
		retval_raceid;
	dbr = db_query(db_race_main,"SELECT max(id) FROM race_stat");
	db_get_field(dbr,0,rid,sizeof(rid));
	if(db_num_rows(dbr)) retval_raceid = strval(rid);
	else retval_raceid = 0;
	db_free_result(dbr);
	return retval_raceid;
}

stock Race_DB_getAmount(){
	new
		DBResult:dbr,
		raceAmount[11],
		retval_raceamount;
	dbr = db_query(db_race_main,"SELECT count(*) FROM race_stat");
	db_get_field(dbr,0,raceAmount,sizeof(raceAmount));
	if(db_num_rows(dbr)) retval_raceamount = strval(raceAmount);
	else retval_raceamount = 0;
	db_free_result(dbr);
	return retval_raceamount;
}


stock Race_DB_get(rid,name[] = "",password[] = "",builder[] = "",description[] = "",raced_times[] = "",lastrundate[] = "",interior[] = "", cpAmount[] = "",lenth[] = "",name_ = false,password_ = false,builder_ = false,description_ = false,raced_times_ = false,lastrundate_ = false,interior_ = false, cpAmount_ = false,lenth_ = false){
	new
		DBResult:dbr,
		sqlstr[MAX_MSG_STR*2];
	format(sqlstr,sizeof(sqlstr),"SELECT name,password,builder,description,raced_times,lastrundate,interior,cpAmount,lenth FROM race_stat WHERE id = %d",rid);
	dbr = db_query(db_race_main,sqlstr);
	
	if(name_)
		db_get_field(dbr,0,name,MAX_RACE_NAME);
	if(password_)
		db_get_field(dbr,1,password,MAX_RACE_PASSWORD);
	if(builder_)
		db_get_field(dbr,2,builder,MAX_PLAYER_NAME);
	if(description_)
		db_get_field(dbr,3,description,MAX_RACE_DESCRIPTION);
	if(raced_times_)
		db_get_field(dbr,4,raced_times,11);
	if(lastrundate_)
		db_get_field(dbr,5,lastrundate,34);
	if(interior_)
		db_get_field(dbr,6,interior,11);
	if(cpAmount_)
		db_get_field(dbr,7,cpAmount,11);
	if(lenth_)
		db_get_field(dbr,8,lenth,24);
	
	db_free_result(dbr);
	return true;
}

stock Race_DB_getcp(rid,cpid,x[] = "",y[] = "",z[] = "",a[] = "",s[] = "",t[] = "", x_ = false, y_ = false, z_ = false, a_ = false, s_ = false, t_ = false){
	new
		DBResult:dbr,
		sqlstr[MAX_MSG_STR*2];
		
	format(sqlstr,sizeof(sqlstr),"SELECT * FROM race_%d_checkpoint WHERE cp_id = %d",rid,cpid);
	dbr = db_query(db_race_main,sqlstr);
		
	if(t_))
		db_get_field(dbr,0,t);
	if(s_))
		db_get_field(dbr,1,s);
	if(x_))
		db_get_field(dbr,2,x);
	if(y_))
		db_get_field(dbr,3,y);
	if(z_))
		db_get_field(dbr,4,z);
	if(a_))
		db_get_field(dbr,5,a);
	
	db_free_result(dbr);
	return true;
}



stock Race_DB_edit(rid,name[] = "",password[] = "",builder[] = "",description[] = "",raced_times = -65535,lastrundate[] = "",interior = -65535, cpAmount = -65535,Float:lenth = -65535.0){
	new
		sqlstr[MAX_SQL_STR],
		tmpstr[MAX_MSG_STR];
	format(sqlstr,sizeof(sqlstr),"UPDATE race_stat SET ");
	if(!isnull(name)){
		format(tmpstr,sizeof(tmpstr),"name = '%s',",name);
		strcat(sqlstr,tmpstr);
	}
	if(!isnull(password)){
		format(tmpstr,sizeof(tmpstr),"password = '%s',",password);
		strcat(sqlstr,tmpstr);
	}
	if(!isnull(builder)){
		format(tmpstr,sizeof(tmpstr),"builder = '%s',",builder);
		strcat(sqlstr,tmpstr);
	}
	if(!isnull(description)){
		format(tmpstr,sizeof(tmpstr),"description = '%s',",description);
		strcat(sqlstr,tmpstr);
	}
	if(raced_times != -65535){
		format(tmpstr,sizeof(tmpstr),"raced_times = %d,",raced_times);
		strcat(sqlstr,tmpstr);
	}
	if(!isnull(lastrundate)){
		format(tmpstr,sizeof(tmpstr),"lastrundate = '%s',",lastrundate);
		strcat(sqlstr,tmpstr);
	}
	if(interior != -65535){
		format(tmpstr,sizeof(tmpstr),"interior = %d,",interior);
		strcat(sqlstr,tmpstr);
	}
	if(cpAmount != -65535){
		format(tmpstr,sizeof(tmpstr),"cpAmount = %d,",cpAmount);
		strcat(sqlstr,tmpstr);
	}
	if(lenth != -65535.0){
		format(tmpstr,sizeof(tmpstr),"lenth = %.3f,",lenth);
		strcat(sqlstr,tmpstr);
	}
	format(tmpstr,sizeof(tmpstr),"id = %d WHERE id = %d",rid,rid);
	strcat(sqlstr,tmpstr);
	db_free_result(db_query(db_race_main,sqlstr));
	return true;
}


stock Race_DB_editcp(rid,cpid,t = -65535,Float:s =  -65535.0,Float:x =  -65535.0,Float:y = -65535.0,Float:z = -65535.0,Float:a =  -65535.0){
	new
		sqlstr[MAX_MSG_STR*2],
		tmpstr[MAX_MSG_STR];
	format(sqlstr,sizeof(sqlstr),"UPDATE race_%d_checkpoint SET ",rid);
	if(t != -65535){
		format(tmpstr,sizeof(tmpstr),"cp_type = %d,",t);
		strcat(sqlstr,tmpstr);
	}
	if(s != -65535.0){
		format(tmpstr,sizeof(tmpstr),"cp_size = %.3f,",s);
		strcat(sqlstr,tmpstr);
	}
	if(x != -65535.0){
		format(tmpstr,sizeof(tmpstr),"cp_posx = %.3f,",x);
		strcat(sqlstr,tmpstr);
	}
	if(y != -65535.0){
		format(tmpstr,sizeof(tmpstr),"cp_posy = %.3f,",y);
		strcat(sqlstr,tmpstr);
	}
	if(z != -65535.0){
		format(tmpstr,sizeof(tmpstr),"cp_posz = %.3f,",z);
		strcat(sqlstr,tmpstr);
	}
	if(a != -65535.0){
		format(tmpstr,sizeof(tmpstr),"cp_angel = %.3f,",a);
		strcat(sqlstr,tmpstr);
	}
	format(tmpstr,sizeof(tmpstr),"cp_id = %d WHERE cp_id = %d",cpid,cpid);
	strcat(sqlstr,tmpstr);
	db_free_result(db_query(db_race_main,sqlstr));
	return true;
}



stock Race_DB_createCheckpointTable(raceid){
	new
		sqlstr[MAX_MSG_STR*2];
	format(sqlstr,sizeof(sqlstr),"CREATE TABLE IF NOT EXISTS race_%d_checkpoint (cp_id INTEGER PRIMARY KEY,cp_type INTEGER,cp_size REAL ,\
		cp_posx	REAL ,cp_posy REAL ,cp_posz	REAL ,cp_angel REAL)",raceid);
	db_free_result(db_query(db_race_main,sqlstr));	
	return true;
}

stock Race_DB_createcp(rid,type,Float:size,Float:x,Float:y,Float:z,Float:a = 0.0){
	Race_DB_createCheckpointTable(rid);
	new
		sqlstr[MAX_SQL_STR];
	format(sqlstr,sizeof(sqlstr),"INSERT INTO race_%d_checkpoint VALUES (NULL,%d,%.3f,%.3f,%.3f,%.3f,%.3f); \
		UPDATE race_stat SET cpAmount = cpAmount+1 WHERE id = %d;",rid,type,size,x,y,z,a,rid); 
	db_free_result(db_query(db_race_main,sqlstr));	
}

stock Race_DB_create(const name[] = "",const password[] = ""){
	new
		sqlstr[MAX_MSG_STR*2];
	format(sqlstr,sizeof(sqlstr),"INSERT INTO race_stat VALUES(NULL,'%s','%s','none','none',0,'%s',0,0,0.0);",name,password,Race_getDate());
	db_free_result(db_query(db_race_main,sqlstr));
	return Race_DB_getMaxrid();
}

stock Race_DB_increaseRacedTimes(raceid){
	new
		sqlstr[MAX_MSG_STR*2];
	format(sqlstr,sizeof(sqlstr),"UPDATE race_stat SET raced_times = raced_times+1 WHERE id = %d",raceid);
	db_free_result(db_query(db_race_main,sqlstr));
}

stock Race_DB_setRunDate(raceid){
	new
		sqlstr[MAX_MSG_STR*2];
	format(sqlstr,sizeof(sqlstr),"UPDATE race_stat SET lastrundate = '%s' WHERE id = %d",Race_getDate(),raceid);
	db_free_result(db_query(db_race_main,sqlstr));
}

stock Race_DB_addRecord(const finisher, const usedtime, const vecid, const Float:vechp){
	new
		sqlstr[MAX_MSG_STR*2];
	format(
		sqlstr,sizeof(sqlstr),"INSERT INTO race_records VALUES (NULL,'%s','%s','%s',%d,%d,'%.2f','%s');",
		Race_getPlrName(finisher),Race_getPlrBuilder(finisher),pName(finisher),usedtime,vecid,vechp,Race_getDate()
	);
	db_free_result(db_query(db_race_record,sqlstr));
}

stock Race_DB_remove(raceid){
	new
		sqlstr[MAX_MSG_STR*2];
	format(sqlstr,sizeof(sqlstr),"DELETE FROM race_stat WHERE id = %d; DROP TABLE race_%d_checkpoint;",raceid,raceid);
	db_free_result(db_query(db_race_main,sqlstr));
	return true;
}



#define Race_DB_searchSearch_1() \
	new DBResult:dbr,sqlstr[MAX_SQL_STR],name[MAX_RACE_NAME],builder[MAX_PLAYER_NAME];\
	format(sqlstr,sizeof(sqlstr),"SELECT id,name,builder FROM race_stat WHERE builder LIKE '%%%s%%' AND name LIKE '%%%s%%'",cmd3,cmd2);\
	dbr = db_query(db_race_main,sqlstr)
	
#define Race_DB_searchSearch_2() \
	for(new i,j = db_num_rows(dbr);i < j && i < 100;i++){\
		db_get_field(dbr,1,name,sizeof(name));\
		db_get_field(dbr,2,builder,sizeof(builder));\
		db_next_row(dbr);\
		format(tmpstr,sizeof(tmpstr),"%04d %s %s\n",Race_getridFromName(name),name,builder);\
		strcat(Race_Dialog_rs_info,tmpstr);\
	}\
	db_free_result(dbr)
	
	
#define Race_DB_searchBuilder_1() \
	new DBResult:dbr,sqlstr[MAX_SQL_STR],name[MAX_RACE_NAME],builder[MAX_PLAYER_NAME];\
	format(sqlstr,sizeof(sqlstr),"SELECT id,name,builder FROM race_stat WHERE builder LIKE '%%%s%%'",cmd2);\
	dbr = db_query(db_race_main,sqlstr)
			
#define Race_DB_searchBuilder_2() \
	for(new i,j = db_num_rows(dbr);i < j && i < 50;i++){\
		db_get_field(dbr,1,name,sizeof(name));\
		db_get_field(dbr,2,builder,sizeof(builder));\
		db_next_row(dbr);\
		format(tmpstr,sizeof(tmpstr),"ID:%04d %s %s\n",Race_getridFromName(name),name,builder);\
		strcat(Race_Dialog_rs_info,tmpstr);\
	}\
	db_free_result(dbr)

#define Race_DB_searchName_1() \
	new DBResult:dbr,sqlstr[MAX_SQL_STR],name[MAX_RACE_NAME],builder[MAX_PLAYER_NAME];\
	format(sqlstr,sizeof(sqlstr),"SELECT id,name,builder FROM race_stat WHERE name LIKE '%%%s%%'",cmd2);\
	dbr = db_query(db_race_main,sqlstr)
			

#define Race_DB_searchName_2() \
	for(new i,j = db_num_rows(dbr);i < j && i < 50;i++){\
		db_get_field(dbr,1,name,sizeof(name));\
		db_get_field(dbr,2,builder,sizeof(builder));\
		db_next_row(dbr);\
		format(tmpstr,sizeof(tmpstr),"%04d %s %s\n",Race_getridFromName(name),name,builder);\
		strcat(Race_Dialog_rs_info,tmpstr);\
	}\
	db_free_result(dbr)


