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


#define RACE_MAP_ICON		(1)



stock Race_isValid(rid){
	return Race_DB_isValid(rid);
}


stock Race_getUnusedrid(){
	return Race_DB_getMaxrid()+1;
}


stock Race_finish(raceid,playerid,time,vecmodel,Float:vechp){
	Race_DB_addRecord(playerid,time,vecmodel,vechp);
	Race_DB_increaseRacedTimes(raceid);
	Race_DB_setRunDate(raceid);
}


stock Race_clearPlrCache(playerid){
	Race_setPlrDialogState(playerid,race_dg_none);
	Race_setPlrDialogPage(playerid,0);
	Race_setPlrDialogItem(playerid,0);
	Race_setPlrState(playerid,race_state_none);
	Race_setPlrRaceState(playerid,race_state_race_none);
	Race_setPlrBuildState(playerid,race_state_build_none);
	Race_setPlrEditState(playerid,race_state_edit_none);
	Race_setPlrSlot(playerid,Race_getSlot());
	Race_setPlrPositionSlot(playerid,Race_getSlot());
	Race_setPlrPosition(playerid,0);
	Race_setPlrrid(playerid,INVALID_RACE_ID);
	Race_setPlrcpid(playerid,0);
	Race_setPlrStarttk(playerid,0);
	Race_setPlrEndtk(playerid,0);
	Race_removePlrRacingCP(playerid);
	return true;
}

stock Race_setPlrInRace(playerid,raceid,position,slot = -1,positionslot = -1){
	Race_setPDFromDB(playerid,raceid,false);
	Race_setPlrState(playerid,race_state_race);
	Race_setPlrRaceState(playerid,race_state_race_ready);
	if(positionslot == -1){
		Race_setPlrPositionSlot(playerid,Race_getSlot());
	}
	else {
		Race_setPlrPositionSlot(playerid,positionslot);
	}
	Race_setPlrPosition(playerid,position);
	Race_setPlrrid(playerid,raceid);
	Race_setPlrcpid(playerid,0);
	if(slot == -1){
		Race_setPlrSlot(playerid,Race_getSlot());
	}
	else {
		Race_setPlrSlot(playerid,slot);
	}
	Race_setPlrRacingCP(playerid,Race_getPlrcpid(playerid));
	TeleportPlayer(playerid,Race_getPlrCPPosx(playerid,0),Race_getPlrCPPosy(playerid,0),Race_getPlrCPPosz(playerid,0));
}

stock Race_setPlrInEdit(playerid,raceid){
	Race_setPDFromDB(playerid,raceid,true);
	Race_setPlrState(playerid,race_state_edit);
	Race_setPlrRaceState(playerid,race_state_edit_none);
	Race_setPlrrid(playerid,raceid);
	Race_setPlrcpid(playerid,0);
	Race_setPlrSlot(playerid,Race_getSlot());
	Race_setPlrPositionSlot(playerid,Race_getSlot());
	Race_setPlrRacingCP(playerid,Race_getPlrcpid(playerid));
	TeleportPlayer(playerid,Race_getPlrCPPosx(playerid,0),Race_getPlrCPPosy(playerid,0),Race_getPlrCPPosz(playerid,0));
}








stock Race_setPDFromDB(playerid,rid,bool:password){

	new
		DBResult:dbr,
		DBResult:dbr2,
		sqlstr[MAX_SQL_STR];
		
		
	format(sqlstr,sizeof(sqlstr),"SELECT name,password,builder,description,raced_times,lastrundate,interior,cpAmount,lenth FROM race_stat WHERE id = %d",rid);
	dbr = db_query(db_race_main,sqlstr);
	
	
	new
		name[MAX_RACE_NAME],
		password2[MAX_RACE_PASSWORD],
		builder2[MAX_PLAYER_NAME],
		description[MAX_RACE_DESCRIPTION],
		raced_times[11],
		lastrundate[36],
		interior[11],
		cpAmount[11],
		lenth[11];
	db_get_field(dbr,0,name,sizeof(name));
	if(password)db_get_field(dbr,1,password2,sizeof(password2));
	db_get_field(dbr,2,builder2,sizeof(builder2));
	db_get_field(dbr,3,description,sizeof(description));
	db_get_field(dbr,4,raced_times,sizeof(raced_times));
	db_get_field(dbr,5,lastrundate,sizeof(lastrundate));
	db_get_field(dbr,6,interior,sizeof(interior));
	db_get_field(dbr,7,cpAmount,sizeof(cpAmount));
	db_get_field(dbr,8,lenth,sizeof(lenth));
	Race_setPlrrid(playerid,rid);
	Race_setPlrName(playerid,name);
	if(password)Race_setPlrPassword(playerid,password2);
	Race_setPlrBuilder(playerid,builder2);
	Race_setPlrDescription(playerid,description);
	Race_setPlrRacedTimes(playerid,strval(raced_times));
	Race_setPlrLastrundate(playerid,lastrundate);
	Race_setPlrInterior(playerid,strval(interior));
	Race_setPlrCPAmount(playerid,strval(cpAmount));
	db_free_result(dbr);
	
	new
		type[11],
		size[24],
		posx[24],
		posy[24],
		posz[24],
		angel[24];
	format(sqlstr,sizeof(sqlstr),"SELECT cp_type,cp_size,cp_posx,cp_posy,cp_posz,cp_angel FROM race_%d_checkpoint WHERE cp_id BETWEEN 0 AND %d",rid,Race_getPlrCPAmount(playerid));
	dbr2 = db_query(db_race_main,sqlstr);
	for(new i,j = Race_getPlrCPAmount(playerid);i < j;i++){
		db_get_field(dbr2,0,type,sizeof(type));
		db_get_field(dbr2,1,size,sizeof(size));
		db_get_field(dbr2,2,posx,sizeof(posx));
		db_get_field(dbr2,3,posy,sizeof(posy));
		db_get_field(dbr2,4,posz,sizeof(posz));
		db_get_field(dbr2,5,angel,sizeof(angel));
		db_next_row(dbr2);
		Race_setPlrCPType(playerid,i,strval(type));
		Race_setPlrCPSize(playerid,i,floatstr(size));
		Race_setPlrCPPosx(playerid,i,floatstr(posx));
		Race_setPlrCPPosy(playerid,i,floatstr(posy));
		Race_setPlrCPPosz(playerid,i,floatstr(posz));
		Race_setPlrCPAngel(playerid,i,floatstr(angel));
	}
	db_free_result(dbr2);
}


stock Race_setPlrTocpid(playerid,cpid){
	//Race_setPlrrid(playerid,raceid);
	Race_setPlrcpid(playerid,cpid);
	Race_setPlrRacingCP(playerid,cpid);
	TeleportPlayer(playerid,Race_getPlrCPPosx(playerid,cpid),Race_getPlrCPPosy(playerid,cpid),Race_getPlrCPPosz(playerid,cpid));
}

stock Race_getDialogPages(){
	new
		raceamount = Race_DB_getAmount();
	//((raceamount%Race_Dialog_item_perpage)?0:1)	
	return (raceamount/Race_Dialog_item_perpage+((raceamount%Race_Dialog_item_perpage)?1:0));
}


stock Race_setPlrRacingCP(playerid,cpid){
	DisablePlayerRaceCheckpoint(playerid);
	SetPlayerRaceCheckpoint(playerid,Race_getPlrCPType(playerid,cpid),Race_getPlrCPPosx(playerid,cpid),Race_getPlrCPPosy(playerid,cpid),Race_getPlrCPPosz(playerid,cpid),Race_getPlrCPPosx(playerid,cpid+1),Race_getPlrCPPosy(playerid,cpid+1),Race_getPlrCPPosz(playerid,cpid+1),Race_getPlrCPSize(playerid,cpid));
	RemovePlayerMapIcon(playerid,GetPVarInt(playerid,"wl_race_cp_mapicon"));
	SetPlayerMapIcon(playerid,GetPVarInt(playerid,"wl_race_cp_mapicon"),Race_getPlrCPPosx(playerid,cpid+1),Race_getPlrCPPosy(playerid,cpid+1),Race_getPlrCPPosz(playerid,cpid+1),34,COLOR_RACE);
}

stock Race_removePlrRacingCP(playerid){
	DisablePlayerRaceCheckpoint(playerid);
	RemovePlayerMapIcon(playerid,GetPVarInt(playerid,"wl_race_cp_mapicon"));
}

stock Race_DialogDymCreateByDB(page){
	page--;//prefix for pawn
	new
		tmpstr[MAX_MSG_STR],
		DBResult:dbr,
		sqlstr[MAX_SQL_STR];
	format(sqlstr,sizeof(sqlstr),"SELECT id,name,builder,raced_times,lenth FROM race_stat \
		WHERE id BETWEEN %d AND %d",page*Race_Dialog_item_perpage,page*Race_Dialog_item_perpage+Race_Dialog_item_perpage);
	dbr = db_query(db_race_main,sqlstr);
	

	Race_Dialog_rs_info[0] = '\0';
	if(page == 0)
	strcat(Race_Dialog_rs_info,"请选择赛道\n");
	strcat(Race_Dialog_rs_info,"上一页\n");
	
	for(new i,id[11],name[MAX_RACE_NAME],builder2[MAX_PLAYER_NAME],raced_times[11],lenth[24],j = db_num_rows(dbr);i < Race_Dialog_item_perpage && i < j;i++){
		db_get_field(dbr,0,id,sizeof(id));
		db_get_field(dbr,1,name,sizeof(name));
		db_get_field(dbr,2,builder2,sizeof(builder2));
		db_get_field(dbr,3,raced_times,sizeof(raced_times));
		db_get_field(dbr,4,lenth,sizeof(lenth));
		db_next_row(dbr);
		if(!isnull(name)){
			format(tmpstr,sizeof(tmpstr),"(%d)%s %s 比赛次数:%d 赛道长度:%.f\n",strval(id),name,builder2,strval(raced_times),floatstr(lenth));
			strcat(Race_Dialog_rs_info,tmpstr);
		}
	}
	db_free_result(dbr);
	
	strcat(Race_Dialog_rs_info,"下一页\n");
	format(Race_Dialog_rs_caption,sizeof(Race_Dialog_rs_caption),"请选择赛道    -  第%d/%d页",page+1, Race_getDialogPages());
}


public Race_countdown(playerid){ debug_public_track("Race_countdown(playerid){");
	
	new
		slotid = Race_getPlrSlot(playerid);
	SetPVarInt(playerid,"wl_race_countdown",GetPVarInt(playerid,"wl_race_countdown")-1);
	switch(GetPVarInt(playerid,"wl_race_countdown")+1){
		case 0:{
			//start race
			
			for(new i;i<MAX_PLAYERS;i++){
				if(IsPlayerConnected(i) && slotid == Race_getPlrSlot(i)){
					Race_setPlrState(i,race_state_race);
					Race_setPlrRaceState(i,race_state_race_start);
					Race_setPlrStarttk(i,GetTickCount());
					if(IsPlayerInRaceCheckpoint(i))Race_EnterRaceCheckpoint(i);
					KillTimer(GetPVarInt(playerid,"wl_race_countdowntimer"));
					Race_send(i,"race_countdown_finish_start");
					PlayerPlaySound(i,1057);
					GameTextForPlayer(i,"~w~GO ~y~GO ~r~GO!",2500,3);
					
				}
			}
		}
		case 1:{
			for(new i;i<MAX_PLAYERS;i++){
				if(slotid == Race_getPlrSlot(i)){
					PlayerPlaySound(i,1056);
					GameTextForPlayer(i,"~r~1",2500,3);
				}
			}
		}
		case 2:{
			for(new i;i<MAX_PLAYERS;i++){
				if(slotid == Race_getPlrSlot(i)){
					PlayerPlaySound(i,1056);
					GameTextForPlayer(i,"~y~2",2500,3);
				}
			}
		}
		case 3:{
			for(new i;i<MAX_PLAYERS;i++){
				if(slotid == Race_getPlrSlot(i)){
					PlayerPlaySound(i,1056);
					GameTextForPlayer(i,"~b~3",2500,3);
				}
			}
		}
		case 4:{
			for(new i;i<MAX_PLAYERS;i++){
				if(slotid == Race_getPlrSlot(i)){
					PlayerPlaySound(i,1056);
					GameTextForPlayer(i,"~g~4",2500,3);
				}
			}
		}
		case 5:{
			Race_loopSlot(slotid,i){
				Race_send(i,"race_countdown_comingstart");
				PlayerPlaySound(i,1056);
				GameTextForPlayer(i,"~p~5",2500,3);
			}
			/*
			for(new i;i<MAX_PLAYERS;i++){
				if(slotid == Race_getPlrSlot(i)){
					Race_send(i,"[赛车]注意,比赛即将开始.");
					PlayerPlaySound(i,1056);
					GameTextForPlayer(i,"~p~5",2500,3);
				}
			}
			*/
		}
	}
}


static gRaceDialog_edithelp[] = 	"/r edit start [赛道名称] [赛道维护密码] - 进入赛道维护模式\n/r edit leave - 强制退出赛道维护模式\n\
			/r edit miaoshu [新描述] - 修改赛道描述\n/r edit password [新密码] - 修改赛道密码\n\
			/r edit cp [检查点ID] - 修改指定检查点信息\n\
			/r edit setcppose - 设置当前检查点位置\n/r edit setcpszie [检查点大小] - 设置当前检查点大小\n/r edit setcptype [检查点类型ID] - 设置当前检查点类型\
			/r edit savecp - 保存当前检查点\n/r edit saverace - 保存赛道\n";

stock Race_Dialogprocess(playerid,dialogstate = race_dg_none,listitem = -1,page = -1){
	if(dialogstate != race_dg_none){
		Race_setPlrDialogState(playerid,dialogstate);
	}
	if(page != -1){
		Race_setPlrDialogPage(playerid,page);
	}
	if(listitem != -1){
		Race_setPlrDialogItem(playerid,listitem);
	}
	switch(Race_getPlrDialogState(playerid)){
		case race_dg_choose_start: { //choose race for joining
			Race_DialogDymCreateByDB(page);
			ShowPlayerDialog(playerid,Race_dialog_id,RaceDialog_type,Race_Dialog_rs_caption,Race_Dialog_rs_info,"确定","取消");
		}
		case race_dg_choose_info: { //choouse race for viewing info
			Race_DialogDymCreateByDB(page);
			ShowPlayerDialog(playerid,Race_dialog_id,RaceDialog_type,Race_Dialog_rs_caption,Race_Dialog_rs_info,"确定","取消");
		}
		case race_dg_view_info: { //view current race info
			new
				raceid;
			if(listitem != -1){
				raceid = listitem;
			}
			else {
				if(Race_getPlrrid(playerid) == INVALID_RACE_ID){
					raceid = Race_getPlrDialogPage(playerid)*Race_Dialog_item_perpage+Race_getPlrDialogItem(playerid)-1;
				}
				else {
					raceid = Race_getPlrrid(playerid);
				}
			}
			new
				sqlstr[MAX_MSG_STR*2],
				DBResult:dbr,
				name[MAX_RACE_NAME],
				builder[MAX_PLAYER_NAME],
				description[MAX_RACE_DESCRIPTION],
				lenth[24],
				raced_times[11];
			format(sqlstr,sizeof(sqlstr),"SELECT name,builder,description,lenth,raced_times FROM race_stat WHERE id = %d",raceid);
			dbr = db_query(db_race_main,sqlstr);
			if(db_num_rows(dbr)){
					//info[MAX_DIALOG_STR];
				db_get_field(dbr,0,name,sizeof(name));	
				db_get_field(dbr,1,builder,sizeof(builder));
				db_get_field(dbr,2,description,sizeof(description));
				db_get_field(dbr,3,lenth,sizeof(lenth));
				db_get_field(dbr,4,raced_times,sizeof(raced_times));
				format(Race_Dialog_rs_info,sizeof(Race_Dialog_rs_info), \
					"赛道ID%d\n赛道名称:%s\n赛道制作人:%s\n赛道描述:%s\n赛道长度:%f gta unit(s)\n\
					赛道完成次数:%d\n \n最近的比赛成绩:\n",\
					raceid,name,builder,description,floatstr(lenth),strval(raced_times)
				);
				db_free_result(dbr);
			}
			new
				DBResult:dbr2,
				winner[MAX_PLAYER_NAME],
				usetime[11],
				vecid[11],
				vechp[24],
				tmpstr[MAX_MSG_STR];
			format(sqlstr,sizeof(sqlstr),"SELECT winner,usetime,vecid,vechp FROM race_records WHERE `name` = '%s' ORDER BY id DESC",name);
			dbr2 = db_query(db_race_record,sqlstr);
			
			for(new i,j = db_num_rows(dbr2); i < MAX_RACE_WINNER && i < j;i++) {
				db_get_field(dbr2,0,winner,sizeof(winner));
				db_get_field(dbr2,1,usetime,sizeof(usetime));
				db_get_field(dbr2,2,vecid,sizeof(vecid));
				db_get_field(dbr2,3,vechp,sizeof(vechp));
				db_next_row(dbr2);
				strins(usetime,".",strlen(usetime)-3);
				format(tmpstr,sizeof(tmpstr),"车手:%s   交通工具:%s(hp:%.2f)   用时:%s秒\n",winner,vecid,floatstr(vechp),usetime);
				strcat(Race_Dialog_rs_info,tmpstr);
			}
			db_free_result(dbr2);
			ShowPlayerDialog(playerid,Race_dialog_id_deresponse,DIALOG_STYLE_LIST,"赛道信息",Race_Dialog_rs_info,"确定","取消");
		}
		case race_dg_help:{ //generally help
			static
				Race_dialog_info_mainhelp[] = "\
					/r s -  发起/开始比赛\n/r info  -  查看赛道信息\n/r page [页码] - 通过页码快速查看赛道\n\
					/r join [玩家ID]  -  加入指定玩家的比赛\n/r likai1  -  强制退出比赛\n\
					/r fastjoin [赛道名称]  -  快速加入指定赛道\n\
					/r fastview [赛道名称]  -  快速查看指定赛信息\n\
					/r search [赛道名称] [赛道制作人]  -  快速查找赛道\n\
					/r name [赛道名称]  -  快速查找赛道\n\
					/r builder [赛道制作人]  -  快速查找赛道\n\
					/r edit help = 查看赛道维护帮助\n/r help  -  查看赛车系统帮助";
			ShowPlayerDialog(playerid,Race_dialog_id_deresponse,DIALOG_STYLE_LIST,"[赛车系统帮助]",Race_dialog_info_mainhelp,"确定","取消");
		}
		case race_dg_help_build:{ //build help
			static
				Race_dialog_info_buildhelp[] = "\
					/r build start  -  进入赛道制作模式\n/r build leave  -  强制退出赛道制作模式\n\
					/r build setcp  -  设置当前检查点位置\n/r build setcpsize  -  设置当前检查点大小\n\
					/r build setcptype  -  设置当前检查点类型\n/r build savecp  -  保存当前检查点设置\n\
					/r build saverace  -  保存当前赛道\n";
			ShowPlayerDialog(playerid,Race_dialog_id_deresponse,DIALOG_STYLE_LIST,"[赛道制作帮助]",Race_dialog_info_buildhelp,"确定","取消");
		}
		case race_dg_help_setcp:{ //setcp help
			ShowPlayerDialog(playerid,Race_dialog_id_deresponse,DIALOG_STYLE_LIST,"[赛道制作帮助-设置红点]","帮助","确定","取消");
		}
		case race_dg_sr_setname:{ //save race - setname
			ShowPlayerDialog(playerid,Race_dialog_id,DIALOG_STYLE_INPUT,"[赛道制作]-设置赛道名称","请输入赛道名称(不能使用中文!)\n请遵循方便玩家记忆、输入的原则","下一步","上一步");
		}
		case race_dg_sr_setdes:{ //save race - setdescripetion
			ShowPlayerDialog(playerid,Race_dialog_id,DIALOG_STYLE_INPUT,"[赛道制作]-设置赛道简单描述(不能使用中文!)","对该赛道进行简单的描述","下一步","上一步");
		}
		case race_dg_sr_setpass:{ //save race - setpassword
			ShowPlayerDialog(playerid,Race_dialog_id,DIALOG_STYLE_INPUT,"[赛道制作]-设置赛道密码(不能使用中文!)","请输入赛道密码\n密码用于以后维护赛道，请务必记住!","下一步","上一步");
		}
		case race_dg_sr_setsave:{ //save race - sure to save
			ShowPlayerDialog(playerid,Race_dialog_id,DIALOG_STYLE_LIST,"[赛道制作]-确认保存赛道","确认保存赛道?","下一步","上一步");
		}
		case race_dg_sh_byname:{
			ShowPlayerDialog(playerid,Race_dialog_id_deresponse,DIALOG_STYLE_LIST,"/r fastjoin [赛道ID]加入赛道  /r fastview [赛道ID]查看赛道信息",Race_Dialog_rs_info,"确定","取消");
		}
		case race_dg_sh_bybuilder:{
			ShowPlayerDialog(playerid,Race_dialog_id_deresponse,DIALOG_STYLE_LIST,"/r fastjoin [赛道ID]加入赛道  /r fastview [赛道ID]查看赛道信息",Race_Dialog_rs_info,"确定","取消");
		}	
		case race_dg_sh_bynameandbuilder:{
			ShowPlayerDialog(playerid,Race_dialog_id_deresponse,DIALOG_STYLE_LIST,"/r fastjoin [赛道ID]加入赛道  /r fastview [赛道ID]查看赛道信息",Race_Dialog_rs_info,"确定","取消");
		}
		case race_dg_help_edit:{
			ShowPlayerDialog(playerid,Race_dialog_id_deresponse,DIALOG_STYLE_LIST,"赛道维护帮助",gRaceDialog_edithelp,"确定","取消");
		}
	}
	return true;
}




stock Race_getridFromName(const name[]){
	return Race_DB_getridFromName(name);
}

stock Race_getNameFromrid(const rid){
	return Race_DB_getNameFromrid(rid);
}




stock Race_setPositionSlotValue(const slotid,const value){
	loopPlayer(playerid){
		if(Race_getPlrPositionSlot(playerid) == slotid){
			Race_setPlrPositionSlotValue(playerid,value);
		}
	}
	return true;
}
stock Race_getPositionSlotValue(const slotid){
	loopPlayer(playerid){
		if(Race_getPlrPositionSlot(playerid) == slotid){
			return Race_getPlrPositionSlotValue(playerid);
		}
	}
	return false;
}



stock Float:Race_prefixPlrDistance(playerid){
	new
		Float:distance;
	for(new i,j = Race_getPlrCPAmount(playerid)-1;i < j;i++){
		new
			Float:x1,Float:y1,Float:z1,
			Float:x2,Float:y2,Float:z2;
		x1 = Race_getPlrCPPosx(playerid,i);
		y1 = Race_getPlrCPPosy(playerid,i);
		z1 = Race_getPlrCPPosz(playerid,i);
		x2 = Race_getPlrCPPosx(playerid,i+1);
		y2 = Race_getPlrCPPosy(playerid,i+1);
		z2 = Race_getPlrCPPosz(playerid,i+1);
		distance += getDisBetweenPoints(x1,y1,z1,x2,y2,z2);
	}

	return distance;
}








