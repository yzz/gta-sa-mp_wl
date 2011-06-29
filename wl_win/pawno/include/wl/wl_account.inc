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

/*
id
usable
name
password

*/
#define acc: acc_
#define account: acc_
#define user: acc_

#define MAX_ACCOUNT_LEN			(MAX_PLAYER_NAME)
#define MAX_PASSWORD_LEN		(32)
#define MAX_PRELOGIN_TIME		(45)//second(s)

static
	DB:db_user;
	
#define user_send(%1,%2,%3) wl_lang_send((%1),COLOR_WHITE,%2,%3)
user_send(playerid,msg_identify[]){
	wl_lang_send(playerid,COLOR_WHITE,msg_identify);
}
#define user_sendAll(%1,%2) loopPlayer(var)wl_lang_send(var,COLOR_WHITE,(%1),%2)
user_sendAll(msg_identify[]){
	loopPlayer(var)wl_lang_send(COLOR_WHITE,msg_identify);
}

forward OnPlayerLogin(playerid);
forward acc_PlayerPreloginItter(playerid);
hook_accountSystem_deleteUser(){}
user:getUserMaxID(){
	new
		id[11];
	
	db_processstart("SELECT max(id) FROM player_account");
	db_processthengetresult(db_user);
	db_processresulted(){
		db_processgetfieldbyindex(0,id);
	}
	db_processend();
	return strval(id);
}
user:database_struct(){
	user:createUserTable();
	for(new i = 1, j = user:getUserMaxID(); i <= j; i++){
		db_processstart("SELECT id,usable,name,password FROM player_account WHERE id = %d",i);
		db_processthengetresult(db_user);
		db_processresulted(){
			new
				id[11],usable[11],name[MAX_ACCOUNT_LEN],password[MAX_PASSWORD_LEN];
			db_processgetfield("id",id);
			db_processgetfield("usable",usable);
			db_processgetfield("name",name);
			db_processgetfield("password",password);
			SetGVarInt("wl_user_id",strval(id),i);
			SetGVarInt("wl_user_usable",strval(usable),i);
			SetGVarString("wl_user_name",name,i);
			SetGVarString("wl_user_password",password,i);
		}
		db_processend();
	}
	return true;
}
user:createUserTable(){
	new
		sqlquery[MAX_SQL_STR];
		
	format(sqlquery,sizeof(sqlquery),"CREATE TABLE IF NOT EXISTS player_account (id INTEGER PRIMARY KEY, usable INTEGER, name TEXT, password TEXT)");
	db_free_result(db_query(db_user,sqlquery));
	
	new
		DBResult:dbr;
	dbr = db_query(db_user,"SELECT id FROM player_account LIMIT 2");
	if(db_num_rows(dbr) == 0) db_free_result(db_query(db_user,"INSERT INTO player_account VALUES(NULL,0,'test','test1')"));
	db_free_result(dbr);
	return true;
	
}
user:deleteUserTable(){
	new
		sqlquery[MAX_SQL_STR];
	format(sqlquery,sizeof(sqlquery),"DROP TABLE player_account");
	db_free_result(db_query(db_user,sqlquery));
	return true;	
}

user:createUser(name[],password[]){
	db_processstart("INSERT INTO player_account VALUES(NULL,1,'%s','%s')",name,password);
	db_processthenfree(db_user);
	new
		userid = user:getUserMaxID();
	SetGVarInt("wl_user_id",userid,userid);
	SetGVarInt("wl_user_usable",true,userid);
	SetGVarString("wl_user_name",name,userid);
	SetGVarString("wl_user_password",password,userid);
	return true;
}
user:deleteUser(userid){
	new
		sqlquery[MAX_SQL_STR];
	format(sqlquery,sizeof(sqlquery),"DELETE FROM player_account WHERE userid = %d",userid);
	db_free_result(db_query(db_user,sqlquery));
	return true;
}

user:setUserUsable(userid,set){
	new
		sqlquery[MAX_SQL_STR];
	format(sqlquery,sizeof(sqlquery),"UPDATE player_account SET usable = %d WHERE id = %d",set,userid);
	db_free_result(db_query(db_user,sqlquery));
	SetGVarInt("wl_user_usable",set,userid);
	return true;
}
user:getUserUsable(userid){
	return GetGVarInt("wl_user_usable",userid);
}

user:getUserIDFromName(name[]){
	new
		sqlquery[MAX_SQL_STR],
		DBResult:dbr,
		id[11];
	format(sqlquery,sizeof(sqlquery),"SELECT id FROM player_account WHERE name = '%s'",name);
	dbr = db_query(db_user,sqlquery);
	if(db_num_rows(dbr)){
		db_get_field(dbr,0,id,sizeof(id));
	}
	db_free_result(dbr);
	return strval(id);
}
user:setUserName(userid,name[]){
	new
		sqlquery[MAX_SQL_STR];
	format(sqlquery,sizeof(sqlquery),"UPDATE player_account SET name = '%s' WHERE id = %d",name,userid);
	db_free_result(db_query(db_user,sqlquery));
	SetGVarString("wl_user_name",name,userid);
	return true;
}
user:getUserName(userid){
	new
		name[MAX_ACCOUNT_LEN];
	GetGVarString("wl_user_name",name,sizeof(name),userid);
	return name;
}

user:setUserPassword(userid,password){
	new
		sqlquery[MAX_SQL_STR];
	format(sqlquery,sizeof(sqlquery),"UPDATE player_account SET password = '%s' WHERE id = %d",password,userid);
	db_free_result(db_query(db_user,sqlquery));
	SetGVarString("wl_user_password",password,userid);
	return true;
}
user:getUserPassword(userid){
	new
		password[MAX_PASSWORD_LEN];
	GetGVarString("wl_user_password",password,sizeof(password),userid);
	return password;
}

user:isNameRegistered(name[]){
	new
		sqlquery[MAX_SQL_STR],
		DBResult:dbr,
		retval;
	format(sqlquery,sizeof(sqlquery),"SELECT id FROM player_account WHERE name = '%s'",name);
	dbr = db_query(db_user,sqlquery);
	if(db_num_rows(dbr)){
		retval = true;
	}
	db_free_result(dbr);
	return retval;
}
user:isPlayerRegistered(playerid){
	new
		sqlquery[MAX_SQL_STR],
		DBResult:dbr,
		retval;
	format(sqlquery,sizeof(sqlquery),"SELECT id FROM player_account WHERE name = '%s'",pName(playerid));
	dbr = db_query(db_user,sqlquery);
	if(db_num_rows(dbr)){
		retval = true;
	}
	db_free_result(dbr);
	return retval;
}
user:validPassword(password[]){
	for(new i;password[i];i++){
		if((password[i] >= '0' && password[i] <= '9') || (password[i] >= 'a' && password[i] <= 'z') || (password[i] >= 'A' && password[i] <= 'Z')){
			continue;
		}
		return false;
	}
	return true;
}
user:validAccount(name[]){
	for(new i;name[i];i++){
		if((name[i] >= '0' && name[i] <= '9') || (name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || name[i] == '_' || name[i] == '.' || name[i] == '[' || name[i] == ']'){
			continue;
		}
		return false;
	}
	return true;
}	
user:PlayerLogged(playerid){
	return GetPVarInt(playerid,"wl_plr_logged");
}
user:logged(playerid){
	return GetPVarInt(playerid,"wl_plr_logged");
}
user:playerLogged(playerid){
	return GetPVarInt(playerid,"wl_plr_logged");
}
user:getPlayerUserID(playerid){
	return GetPVarInt(playerid,"wl_plr_userid");
}
user:setPlayerUserID(playerid,userid){
	SetPVarInt(playerid,"wl_plr_userid",userid);
	return true;
}

public user:PlayerPreloginItter(playerid){ debug_public_track("user:PlayerPreloginItter(playerid){");
	if(IsPlayerConnected(playerid) && !GetPVarInt(playerid,"wl_plr_logged")){
		user_send(playerid,WL_LANG_ACC_NOT_PRELOGIN);
		Kick(playerid);
	}
	return true;
}

acc_OnGameModeInit(){
	db_user = db_open("wl/user.db");
	user:database_struct();
}
acc_OnPlayerConnect(playerid){
	if(user:isPlayerRegistered(playerid)){
		SetPVarInt(playerid,"wl_plr_prelogin_timer",SetTimerEx("acc_PlayerPreloginItter",1000*MAX_PRELOGIN_TIME,false,"i",playerid));
		user_send(playerid,WL_LANG_ACC_CONNECT_ALREADY_REGISTERD,MAX_PRELOGIN_TIME);
	}
	return true;
}
acc_OnPlayerDisconnect(playerid){
	KillTimer(GetPVarInt(playerid,"wl_plr_prelogin_timer"));
	return true;
}

zcmd(acc_register,playerid,params[]){
	if(user:PlayerLogged(playerid)){
		user_send(playerid,WL_LANG_ACC_CMD_REGISTER_FAILED_ALREADY_LOGIN);
		return true;
	}
	if(user:isPlayerRegistered(playerid)){
		user_send(playerid,WL_LANG_ACC_CMD_REGISTER_FAILED_ALREADY_REGISTERED);
		return true;
	}
	if(isnull(params)){
		user_send(playerid,WL_LANG_ACC_CMD_REGISTER_FAILED_NOT_ENTER_PASSWORD);
		return true;
	}
	if(strlen(params) > MAX_PASSWORD_LEN){
		user_send(playerid,WL_LANG_ACC_CMD_REGISTER_FAILED_INPUT_TOO_LONG,MAX_PASSWORD_LEN-1);
		return true;
	}
	if(!user:validPassword(params)){
		user_send(playerid,WL_LANG_ACC_CMD_REGISTER_FAILED_INPUT_INVALID);
		return true;
	}
	user:createUser(pName(playerid),params);
	SetPVarInt(playerid,"wl_plr_logged",true);
	SetPVarInt(playerid,"wl_plr_userid",user:getUserIDFromName(pName(playerid)));
	user_send(playerid,WL_LANG_ACC_CMD_REGISTER_PASS,pName(playerid),params);
	user_send(playerid,WL_LANG_ACC_CMD_LOGIN_PASS);
	return true;
}
pzcmd(register){rzcmd(acc_register);} 

zcmd(acc_login,playerid,params[]){
	if(user:PlayerLogged(playerid)){
		user_send(playerid,WL_LANG_ACC_CMD_LOGIN_FAILED_ALREADY_LOGIN);
	}
	else if(!user:isPlayerRegistered(playerid)){
		user_send(playerid,WL_LANG_ACC_CMD_LOGIN_FAILED_UNREGISTERED);
	}
	else if(isnull(params)){
		user_send(playerid,WL_LANG_ACC_CMD_LOGIN_FAILED_NOT_ENTER_PASSWORD);
	}
	else if(!user:validPassword(params)){
		user_send(playerid,WL_LANG_ACC_CMD_LOGIN_FAILED_INVALID_PASSWORD);
	}
	else if(!strcmp(params,user:getUserPassword(user:getUserIDFromName(pName(playerid))))){
		SetPVarInt(playerid,"wl_plr_logged",true);
		SetPVarInt(playerid,"wl_plr_userid",user:getUserIDFromName(pName(playerid)));
		user_send(playerid,WL_LANG_ACC_CMD_LOGIN_PASS,pName(playerid),params);
		CallLocalFunction("OnPlayerLogin","i",playerid);
	}
	else {
		user_send(playerid,WL_LANG_ACC_CMD_LOGIN_FAILED_INCORRECT_PASSWORD);
	}
	return true;
}
pzcmd(login){rzcmd(acc_login);}

zcmd(acc_account,playerid,params[]){
	System_send(playerid,"[帐号]该命令暂时不可用");
	return true;
	/*
	if(!pLogged(playerid)){
		user_send(playerid,"[帐号]未登陆，不能使用帐号管理系列命令");
		return true;
	}
	if(isnull(params)){
		user_send(playerid,"[帐号]输入/a help 查看帮助");
		return true;
	}
	new
		str1[128],str2[128];
	sscanf(params,"ss",str1,str2);
	if(!strcmp("changepass",str1)){
		if(isnull(str2)){
			user_send(playerid,"[帐号]请输入新密码");
			return true;
		}
		if(strlen(str2) > MAX_PASSWORD_LEN){
			user_send(playerid,"[帐号]密码修改失败，输入密码太长(不能超过%d个字符).",MAX_PASSWORD_LEN-1);
			return true;
		}
		for(new i;str2[i];i++){
			if((str2[i] >= '0' && str2[i] <= '9') || (str2[i] >= 'a' && str2[i] <= 'z') || (str2[i] >= 'A' && str2[i] <= 'Z')){
				continue;
			}else{
				user_send(playerid,"[帐号]密码修改失败，密码只能由数字、字母组成。");
				return true;
			}
		}
		gini_open(player_getAccount(playerid));
		gini_writes(user:pPass,str2);
		gini_save();
		gini_close();
		user_send(playerid,"[帐号]密码修改成功，请记住新密码为'%s'!",str2);
		
	}else if(!strcmp("help",str1)){
		user_send(playerid,"[帐号]帐号命令帮助:");
		user_send(playerid,"[帐号]/a changepass - 修改帐号密码");
	}else{
		user_send(playerid,"[帐号]你输入的子命令'%s'无效,请输入/a help 查看帐号帮助",params);
	}
	return true;
	*/
}
pzcmd(account){rzcmd(acc_account);}
pzcmd(a){rzcmd(acc_account);}		
		
		
		
		
	
	
	
