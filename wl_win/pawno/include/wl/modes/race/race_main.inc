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







#define WL_MODE_RACE			(true)


#if WL_MODE_RACE
#define WL_RACE_VERSION			"0.9.8.1"
#define MAX_RACE_WINNER			(20)
#define INVALID_RACE_ID			(-1)
#define MAX_RACE_NAME			(24)
#define MAX_RACE_PASSWORD		(36)
#define MAX_RACE_DESCRIPTION	(MAX_MSG_STR-20)
#define MAX_RACE_BUILDER		(MAX_PLAYER_NAME)

#define COLOR_RACE				COLOR_VEC


#define Race_send(%1,%2,%3) wl_lang_send((%1),COLOR_RACE,%2,%3)
Race_send(playerid,msg_identify[]){
	wl_lang_send(playerid,COLOR_RACE,msg_identify);
}
#define Race_sendAll(%1,%2) wl_lang_sendAll(COLOR_RACE,(%1),%2)
Race_sendAll(msg_identify[]){
	wl_lang_sendAll(COLOR_RACE,msg_identify);
}

forward Race_countdown(playerid);

enum {
	race_state_none,
	race_state_build,
	race_state_race,
	race_state_edit,
	
	race_state_build_setcppos, // set cp pos
	race_state_build_setcpinfo, // set cp size
	race_state_build_info, // set cp info
	race_state_build_none, // not in build state	
	
	race_state_race_none,
	race_state_race_start,
	race_state_race_ready,
	race_state_race_race,
	

	race_state_edit_none,
	//race_state_edit_setcppos,
	race_state_edit_setcpinfo//pos type size
	//race_state_edit_setcpname,
	//race_state_edit_setcpdescription,
	//race_state_edit_setcppassword,
	//race_state_edit_deleterace,
};

enum {
	race_dg_none,//none state
	race_dg_choose_start,//choose race for joining
	race_dg_choose_info,//choouse race for viewing info
	race_dg_view_info,//view current race info
	race_dg_help,//generally help
	race_dg_help_build,//build help
	race_dg_help_setcp,//setcp help
	race_dg_sr_setname,//save race - setname
	race_dg_sr_setdes,//save race - setdescripetion
	race_dg_sr_setpass,//save race - setpassword
	race_dg_sr_setsave,//save race - sure to save
	race_dg_sh_byname,//searh by name
	race_dg_sh_bybuilder,//search by builder
	race_dg_sh_bynameandbuilder,//by name and builder
	race_dg_help_edit
};



new
	gRaceSlot;
#define Race_loopSlot(%1,%2) \
	loopPlayer(%2) \
		if(%1 == Race_getPlrSlot(%2))
		
#define Race_sendSlot(%1,%2,%3,%4) \
	Race_loopSlot(%1,%2) \
		Race_send(%2,%3,%4)
		

stock Race_sendSlot(slotid,msg[]){
	Race_loopSlot(slotid,i){
		Race_send(i,msg);
	}
}


stock Race_getSlot(){
	return ((gRaceSlot <= 0)?(gRaceSlot = 1):++gRaceSlot);
}


new
	Race_dialog_id = 100,
	Race_dialog_id_deresponse = 101,
	
	Race_Dialog_rs_info[MAX_DIALOG_STR],
	Race_Dialog_rs_caption[MAX_MSG_STR],
	Race_Dialog_item_perpage = 10,
	RaceDialog_type = DIALOG_STYLE_LIST;

stock Race_getDate(){
	new
		y,m,d,
		date[36];
	getdate(y,m,d);
	format(date,sizeof(date),"%04d-%02d-%02d",y,m,d);
	return date;
}

#include <wl/modes/race/race_function>
#include <wl/modes/race/race_db>
#include <wl/modes/race/race>


Race_struct(){
	Race_DB_struct();
	printf (" [赛车]赛道载入成功,数量:%d",Race_DB_getAmount());
	return true;
}




Race_EnterRaceCheckpoint(playerid){
	if(Race_getPlrState(playerid) == race_state_race){
		if(Race_getPlrRaceState(playerid) == race_state_race_start){
			new
				raceid = Race_getPlrrid(playerid),
				cpid = Race_getPlrcpid(playerid),
				cpAmount = Race_getPlrCPAmount(playerid);
			if(cpAmount - cpid <= 1){ //last checkpoint
				new
					position = Race_getPositionSlotValue(Race_getPlrPositionSlot(playerid));
				Race_setPositionSlotValue(Race_getPlrPositionSlot(playerid),position+10);
				position++;
				Race_setPlrEndtk(playerid,GetTickCount());
				new
					time = (Race_getPlrEndtk(playerid)-Race_getPlrStarttk(playerid)),
					timestr[36];
				valstr(timestr,time);
				strins(timestr,".",strlen(timestr)-3);
				Race_sendAll("race_entercp_finish_announce",pName(playerid),playerid,Race_getPlrName(playerid),Race_getPlrrid(playerid),timestr,position);
				new
					vecmodel = GetVehicleModel(GetPlayerVehicleID(playerid)),
					Float:vechp;
				GetVehicleHealth(GetPlayerVehicleID(playerid),vechp);
				
				Race_finish(raceid,playerid,time,vecmodel,vechp);
				
				Race_Dialogprocess(playerid,race_dg_view_info);
				Race_clearPlrCache(playerid);
			}
			else { //normal checkpoint
				new
					tmpstr[MAX_MSG_STR];
				format(tmpstr,sizeof(tmpstr),"%d/%d",cpid+1,Race_getPlrCPAmount(playerid));
				GameTextForPlayer(playerid,tmpstr,800,1);
				PlayerPlaySound(playerid,1056);
				Race_setPlrcpid(playerid,cpid+1);
				cpid = Race_getPlrcpid(playerid);
				Race_setPlrRacingCP(playerid,cpid);
			}
		}
		else {
			
			if(Race_getPlrPosition(playerid) == 1){
				Race_send(playerid,"race_entercp_ready_hint_host_1");
				Race_send(playerid,"race_entercp_ready_hint_host_2",playerid);
			}
			else {
				Race_send(playerid,"race_entercp_ready_hint_joiner_2");
			}
		}
	}
}
	


	
Race_DialogResponse(playerid, dialogid, response, listitem, inputtext[]){
	if(dialogid == Race_dialog_id){
		new
			RaceDialog_size = Race_getDialogPages();
		switch(Race_getPlrDialogState(playerid)){
			case race_dg_choose_start:{
				if(response){
					if(listitem >= Race_Dialog_item_perpage+1){
						if(Race_getPlrDialogPage(playerid) >= RaceDialog_size){
							Race_send(playerid,"race_dialog_closedialog");
						}
						else {
							Race_Dialogprocess(playerid, .page = Race_getPlrDialogPage(playerid)+1);
						}
					}
					else if(listitem == 0){
						if(Race_getPlrDialogPage(playerid) == 1){
							Race_send(playerid,"race_dialog_closedialog");
						}
						else {
							Race_Dialogprocess(playerid, .page = Race_getPlrDialogPage(playerid)-1);
						}
					}
					else {
						new
							race = (Race_getPlrDialogPage(playerid)-1)*Race_Dialog_item_perpage+listitem-1,
							tmpstr[128];
						format(tmpstr,sizeof(tmpstr),"/race fastjoin %d",race);
						OnPlayerCommandText(playerid,tmpstr);
					}
				}
				else if(!response){
					Race_send(playerid,"race_dialog_closedialog");
				}
			}
			case race_dg_choose_info:{
				if(response){
					if(listitem >= Race_Dialog_item_perpage+1){
						if(Race_getPlrDialogPage(playerid) == RaceDialog_size){
							Race_send(playerid,"race_dialog_closedialog");
						}
						else {
							Race_Dialogprocess(playerid, .page = Race_getPlrDialogPage(playerid)+1);
						}
					}
					else if(listitem == 0){
						if(Race_getPlrDialogPage(playerid) == 1){
							Race_send(playerid,"race_dialog_closedialog");
						}
						else {
							Race_Dialogprocess(playerid, .page = Race_getPlrDialogPage(playerid)-1);
						}
					}
					else {
						//Race_Dialogprocess(playerid,race_dg_view_info, .listitem = listitem+Race_getPlrDialogPage(playerid)*Race_Dialog_item_perpage);
						new
							race = (Race_getPlrDialogPage(playerid)-1)*Race_Dialog_item_perpage+listitem-1,
							tmpstr[128];
						format(tmpstr,sizeof(tmpstr),"/race fastview %d",race);
						OnPlayerCommandText(playerid,tmpstr);
					}
				}
				else if(!response){
					Race_send(playerid,"race_dialog_closedialog");
				}
			}
			case race_dg_sr_setname:{
				if(response){
					if(strlen(inputtext) > 2 && strlen(inputtext) < MAX_RACE_NAME){
						if(IsSTDStr(inputtext)){
							if(Race_getridFromName(inputtext) == INVALID_RACE_ID){
								Race_setPlrBuildState(playerid,race_state_build_info);
								Race_Dialogprocess(playerid,race_dg_sr_setdes);
								Race_setPlrName(playerid,inputtext);
								Race_send(playerid,"race_dialog_setname_succeed",inputtext);
							}
							else {
								Race_Dialogprocess(playerid);
								Race_send(playerid,"race_dialog_setname_failed_nameexisted",inputtext);
							}
						}
						else {
							Race_Dialogprocess(playerid);
							Race_send(playerid,"race_dialog_setname_failed_nameinvalid");
						}
					}
					else {
						Race_Dialogprocess(playerid);
						Race_send(playerid,"race_dialog_setname_failed_nameoutofindex",MAX_RACE_NAME-1);
					}
				} else {
					Race_setPlrBuildState(playerid,race_state_build_setcppos);
					Race_setPlrRacingCP(playerid,Race_getPlrcpid(playerid));
					//Race_Dialogprocess(playerid);
					Race_send(playerid,"race_dialog_setname_previous_operation_1");
					Race_send(playerid,"race_dialog_setname_previous_operation_2");
					Race_send(playerid,"race_dialog_setname_previous_operation_3");
					
				}
			}
			case race_dg_sr_setdes:{
				if(response){
					if(strlen(inputtext) > 2 && strlen(inputtext) < MAX_RACE_DESCRIPTION){
						Race_setPlrBuildState(playerid,race_state_build_info);
						Race_Dialogprocess(playerid,race_dg_sr_setpass);
						Race_setPlrDescription(playerid,inputtext);
						Race_DB_edit(Race_getPlrrid(playerid), .builder = pName(playerid), .description = inputtext);
						Race_send(playerid,"race_dialog_setdescription_succeed_1");
						Race_send(playerid,inputtext);
						Race_send(playerid,"race_dialog_setdescription_succeed_2");
					} else {
						Race_Dialogprocess(playerid);
						Race_send(playerid,"race_dialog_setdescription_failed_outofindex",MAX_RACE_DESCRIPTION-1);
						
					}
				} else {
					Race_setPlrBuildState(playerid,race_state_build_info);
					Race_Dialogprocess(playerid,race_dg_sr_setname);
					Race_send(playerid,"race_dialog_setdescription_previous_operation");
				}
			}
			case race_dg_sr_setpass:{
				if(response){
					if(strlen(inputtext) > 2 && strlen(inputtext) < MAX_RACE_PASSWORD){
						if(IsSTDStr(inputtext)){
							Race_setPlrBuildState(playerid,race_state_build_info);
							Race_Dialogprocess(playerid,race_dg_sr_setsave);
							Race_setPlrPassword(playerid,inputtext);
							Race_send(playerid,"race_dialog_setpassword_succeed",inputtext);
						}
						else {
							Race_Dialogprocess(playerid);
							Race_send(playerid,"race_dialog_setpassword_failed_nameinvalid");
						}
					}
					else {
						Race_Dialogprocess(playerid);
						Race_send(playerid,"race_dialog_setpassword_failed_outofindex",MAX_RACE_PASSWORD-1);
					}
				} else {
					Race_setPlrBuildState(playerid,race_state_build_info);
					Race_Dialogprocess(playerid,race_dg_sr_setdes);
					Race_send(playerid,"race_dialog_setpassword_previous_operation");
				}
			}
			case race_dg_sr_setsave:{
				if(response){
					//new
					//	rid = Race_getUnusedrid();
					Race_setPlrBuilder(playerid,pName(playerid));
					//Race_setDBFromPD(playerid,rid,true);
					Race_send(playerid,"race_dialog_Setsave_succeed_1",Race_getPlrName(playerid),Race_getPlrrid(playerid));
					Race_send(playerid,"race_dialog_setsave_succeed_2",Race_getPlrrid(playerid));
					new
						tmpstr[MAX_MSG_STR];
					format(tmpstr,sizeof(tmpstr),"/race fastview %d",Race_getPlrrid(playerid));
					OnPlayerCommandText(playerid,tmpstr);
					Race_clearPlrCache(playerid);
				} else {
					Race_setPlrBuildState(playerid,race_state_build_info);
					Race_Dialogprocess(playerid,race_dg_sr_setpass);
					Race_send(playerid,"race_dialog_setsave_previous_operation");
				}
			}
		}
	}
}

Race_playerConnect(playerid){
	Race_clearPlrCache(playerid);
}

Race_playerDisconnect(playerid){
	if(Race_getPlrPosition(playerid) == 1 && Race_getPlrRaceState(playerid) == race_state_race_ready){
		new
			slot = Race_getPlrSlot(playerid);
		loopPlayer(i){
			if(slot == Race_getPlrSlot(i)){
				Race_clearPlrCache(i);
				Race_send(i,"race_cancle_reason_hostdisconnect");
			}
		}
	}
	Race_clearPlrCache(playerid);
}

Race_playerDeath(playerid){
	if(Race_getPlrPosition(playerid) == 1 && Race_getPlrRaceState(playerid) == race_state_race_ready){
		new
			slot = Race_getPlrSlot(playerid);
		loopPlayer(i){
			if(slot == Race_getPlrSlot(i)){
				Race_clearPlrCache(i);
				Race_send(i,"race_cancle_reason_hostdeath");
			}
		}
	}
	Race_clearPlrCache(playerid);
}


zcmd(cmd_race,playerid,params[]){
	static
		bool:Race_debugConclose = true;
	if(!strcmp("admin",params,true) && GetPlayerAdminLevel(playerid) >= 3){
		if(Race_debugConclose){
			Race_debugConclose = false;
			System_send(playerid,"[Race]Race system:closed");
		}else{
			Race_debugConclose = true;
			System_send(playerid,"[Race]Race system:open");
		}
		return true;
	}
	if(!Race_debugConclose){
		System_send(playerid,"[Race]Race system has been colsed");
		return true;
	}
	new
		cmd1[MAX_MSG_STR],cmd2[MAX_MSG_STR],cmd3[MAX_MSG_STR],cmd4[MAX_MSG_STR],cmd5[MAX_MSG_STR];
	sscanf(params,"sssss",cmd1,cmd2,cmd3,cmd4,cmd5);
	if(!strcmp("start",cmd1,true) || !strcmp("s",cmd1,true)){
		if(!cmd2[0]){
			if(Race_getPlrState(playerid) == race_state_none){
				Race_Dialogprocess(playerid,race_dg_choose_start, .page = 1);
				Race_send(playerid,"race_cmd_race_start_select_1");
				Race_send(playerid,"race_cmd_race_start_select_2");
			}
			else if(Race_getPlrState(playerid) == race_state_race){
				if(Race_getPlrRaceState(playerid) == race_state_race_ready){
					if(Race_getPlrPosition(playerid) == 1){
						if(GetPVarInt(playerid,"wl_race_countdown") > 0){
							Race_send(playerid,"race_cmd_race_start_countdown");
						}
						else {
							SetPVarInt(playerid,"wl_race_countdown",5);
							SetPVarInt(playerid,"wl_race_countdowntimer",SetTimerEx("Race_countdown",998,GetPVarInt(playerid,"wl_race_countdown"),"d",playerid));
							Race_sendSlot(Race_getPlrSlot(playerid),"race_cmd_race_start_countdown");
							Race_setPositionSlotValue(Race_getPlrPositionSlot(playerid),0);
						}
					}
					else {
						Race_send(playerid,"race_cmd_race_start_wait");
					}
				}
				else {
					Race_send(playerid,"race_cmd_race_Start_failed_racing");
				}
			}
			else if(Race_getPlrState(playerid) == race_state_build){
				Race_send(playerid,"race_cmd_race_Start_failed_building");
			}
		}
		else if(Race_getridFromName(cmd2) != INVALID_RACE_ID){
			new
				tmpstr[128];
			format(tmpstr,sizeof(tmpstr),"/race fastjoin %d",Race_getridFromName(cmd2));
			OnPlayerCommandText(playerid,tmpstr);
		}
		else {
			Race_send(playerid,"race_cmd_race_start_failed_unexistrace",cmd2);
		}
	}
	else if(!strcmp("page",cmd1,true)){
		if(Race_getPlrState(playerid) == race_state_none){
			new
				page = strval(cmd2),
				pageAmount = Race_getDialogPages();
			if(page >= 1 && page <= pageAmount){
				//Race_setPlrDialogPage(playerid,page-1);	
				Race_Dialogprocess(playerid,race_dg_choose_start, .page = page);
				Race_send(playerid,"race_cmd_race_page_select");
			}
			else {
				Race_send(playerid,"race_cmd_race_page_failed_outofindex");
				Race_send(playerid,"race_cmd_race_page_help");
			}
		}
		else {
			Race_send(playerid,"race_cmd_race_page_failed_cannoutuse");
			Race_send(playerid,"race_cmd_race_page_help");
		}
	}	
	else if(!strcmp("info",cmd1,true)){
		if(Race_getPlrState(playerid) == race_state_none){
			//output a dialog for choosing
			Race_Dialogprocess(playerid,race_dg_choose_info,.page = 1);
			Race_send(playerid,"race_cmd_race_info_select");
		}
		else if(Race_getPlrState(playerid) == race_state_race){
				//output a dialog
				Race_Dialogprocess(playerid,race_dg_view_info);
				Race_send(playerid,"race_cmd_race_info_current");
		}
		else {
			Race_send(playerid,"race_cmd_race_info_failed_building");
		}
	}
	else if(!strcmp("fastjoin",cmd1,true)){
		if(Race_getPlrState(playerid) == race_state_none){
			if(isnull(cmd2)){
				Race_send(playerid,"race_cmd_race_fastjoin_failed_emptyinput");
				return true;
			}
			new
				raceid = strval(cmd2);
				
			if(Race_isValid(raceid)){
				Race_setPlrInRace(playerid,raceid,1);
				Race_sendAll("race_cmd_race_fastjoin_succeed_announce",pName(playerid),Race_getPlrName(playerid),playerid);
				Race_send(playerid,"race_cmd_race_fastjoin_succeed_hint_1",Race_getPlrName(playerid),raceid,playerid);
				Race_send(playerid,"race_cmd_race_fastjoin_succeed_hint_2");
			}
			else {
				Race_send(playerid,"race_cmd_race_fastjoin_failed_unoperatable");
			}
		}
		else if(Race_getPlrState(playerid) == race_state_race){
			Race_send(playerid,"race_cmd_race_fastjoin_failed_racing");
		}
		else if(Race_getPlrState(playerid) == race_state_build){
			Race_send(playerid,"race_cmd_race_fastjoin_failed_building");
		}
	}
	else if(!strcmp("fastview",cmd1,true)){
		if(!isnull(cmd2)){
			if(IsNumeric(cmd2)){
				Race_Dialogprocess(playerid,race_dg_view_info,strval(cmd2));
			}
			else {
				Race_send(playerid,"race_cmd_race_fastview_failed_errorinput");
				Race_send(playerid,"race_cmd_race_fastview_help");
			}
		}
		else {
			Race_send(playerid,"race_cmd_race_Fastview_failed_emptyinput");
			Race_send(playerid,"race_cmd_race_fastview_help");
		}
	}
	else if(!strcmp("join",cmd1,true)){
		if(Race_getPlrState(playerid) != race_state_none){
			Race_send(playerid,"race_cmd_race_join_failed_errorstate");
		}
		else if(!cmd2[0]){
			Race_send(playerid,"race_cmd_race_join_failed_emptyinput");
		}
		else if(IsNumeric(cmd2)){
			new
				starter = strval(cmd2);
			if(IsPlayerConnected(starter)){
				if(Race_getPlrState(starter) == race_state_race && Race_getPlrRaceState(starter) == race_state_race_ready){
					Race_setPlrInRace(playerid,Race_getPlrrid(starter),2,Race_getPlrSlot(starter),Race_getPlrPositionSlot(starter));
					Race_Dialogprocess(playerid,race_dg_view_info,Race_getPlrrid(playerid));
					Race_send(playerid,"race_cmd_race_join_succeed_tome",pName(starter));
					Race_send(starter,"race_cmd_race_join_succeed_toit",pName(playerid));
				}
				else {
					Race_send(playerid,"race_cmd_race_join_failed_notready",pName(starter));
				}
			}
			else {
				Race_send(playerid,"race_cmd_race_join_failed_notconnected");
			}
		}
		else {
			Race_send(playerid,"race_cmd_race_join_help");
		} 
	}
	else if(!strcmp("leave",cmd1,true) || !strcmp("likai",cmd1,true) || !strcmp("exit",cmd1,true)){
		if(Race_getPlrState(playerid) == race_state_race){
			if(Race_getPlrPosition(playerid) == 1 && Race_getPlrRaceState(playerid) == race_state_race_ready){
				new
					slot = Race_getPlrSlot(playerid);
				loopPlayer(i){
					if(slot == Race_getPlrSlot(i)){
						Race_clearPlrCache(i);
						Race_send(i,"race_cmd_race_leave_succeed_announce");
					}
				}
			}
			Race_clearPlrCache(playerid);
			Race_send(playerid,"race_cmd_race_leave_succeed_tome");
		}
		else {
			Race_send(playerid,"race_cmd_race_leave_failed_notracing");
		}
	}
	else if(!strcmp("help",cmd1,true)){
		Race_Dialogprocess(playerid,race_dg_help);
		
	}
	else if(!strcmp("name",cmd1,true)){ //search race by name	
		if(!isnull(cmd2)){
			new	
				tmpstr[MAX_MSG_STR];
			Race_Dialog_rs_info[0] = '\0';
			Race_DB_searchName_1();
			Race_DB_searchName_2();
			if(Race_Dialog_rs_info[0]){
				strcat(Race_Dialog_rs_info," \n");
				Race_Dialogprocess(playerid,race_dg_sh_byname);
				Race_send(playerid,"race_cmd_race_name_succeed_hint_1");
				Race_send(playerid,"race_cmd_race_name_succeed_hint_2");
			}
			else {
				Race_send(playerid,"race_cmd_race_name_failed_hint_1");
				Race_send(playerid,"race_cmd_race_name_failed_hint_2");
			}
		}
		else {
			Race_send(playerid,"race_cmd_race_name_failed_emptyinput");
			Race_send(playerid,"race_cmd_race_name_help");
		}			
	}
	else if(!strcmp("builder",cmd1,true)){ //search race by builder	
		if(!isnull(cmd2)){
			new	
				tmpstr[MAX_MSG_STR];
			Race_Dialog_rs_info[0] = '\0';
			Race_DB_searchBuilder_1();
			Race_DB_searchBuilder_2();
			if(Race_Dialog_rs_info[0]){
				strcat(Race_Dialog_rs_info," \n");
				Race_Dialogprocess(playerid,race_dg_sh_bybuilder);
				Race_send(playerid,"race_cmd_race_builder_succeed_hint_1");
				Race_send(playerid,"race_cmd_race_builder_succeed_hint_2");
			}
			else {
				Race_send(playerid,"race_cmd_race_builder_failed_hint_1");
				Race_send(playerid,"race_cmd_race_builder_failed_hint_2");
			}
		}
		else {
			Race_send(playerid,"race_cmd_race_builder_failed_emptyinput");
			Race_send(playerid,"race_cmd_race_name_help");
		}	
	}
	else if(!strcmp("search",cmd1,true)){ //search race by name&builder	
		if(!isnull(cmd2)){
			if(!isnull(cmd3)){
			
			
				new	
					tmpstr[MAX_MSG_STR];
				Race_Dialog_rs_info[0] = '\0';
				Race_DB_searchSearch_1();
				Race_DB_searchSearch_2();
				if(Race_Dialog_rs_info[0]){
					strcat(Race_Dialog_rs_info," \n");
					Race_Dialogprocess(playerid,race_dg_sh_bynameandbuilder);
					Race_send(playerid,"race_cmd_race_search_succeed_hint_1");
					Race_send(playerid,"race_cmd_race_search_succeed_hint_2");
				}
				else {
					Race_send(playerid,"race_cmd_race_search_failed_hint_1");
					Race_send(playerid,"race_cmd_race_search_failed_hint_2");	
				}
			}
			else {
				Race_send(playerid,"race_cmd_race_builder_failed_emptybuilder");
				Race_send(playerid,"race_cmd_race_search_help");
			}
		}
		else {
			Race_send(playerid,"race_cmd_race_builder_failed_emptyname");
			Race_send(playerid,"race_cmd_race_search_help");
		}
	}				
	else if(!strcmp("edit",cmd1,true)){ 
		if(!strcmp("help",cmd2,true)){
			Race_Dialogprocess(playerid,race_dg_help_edit);
		}
		else if(!strcmp("start",cmd2,true) || !strcmp("s",cmd2,true)){
			switch(Race_getPlrState(playerid)){
				case race_state_race:{
					Race_send(playerid,"race_cmd_race_edit_failed_raceing");
				}
				case race_state_build:{
					Race_send(playerid,"race_cmd_race_edit_failed_editing");
				}
				case race_state_edit:{
					Race_send(playerid,"race_cmd_race_edit_failed_building");
				}
				case race_state_none:{
					if(!isnull(cmd3)){
						if(!isnull(cmd4)){
							new
								rid = Race_getridFromName(cmd3);
							if(rid != INVALID_RACE_ID){
								new	
									password[MAX_RACE_PASSWORD];
								Race_DB_get(rid, .password = password, .password_ = true);
								if(!strcmp(password,cmd4)){
									Race_setPlrInEdit(playerid,rid);
									Race_Dialogprocess(playerid,race_dg_help_edit);
									Race_send(playerid,"race_cmd_race_edit_succeed");
									Race_send(playerid,"race_cmd_race_edit_cp_help");
									Race_send(playerid,"race_cmd_race_edit_setcppos_help");
									Race_send(playerid,"race_cmd_race_edit_setcpsize_help");
									Race_send(playerid,"race_cmd_race_edit_setcptype_help");
									Race_send(playerid,"race_cmd_race_edit_savecp_help");
									Race_send(playerid,"race_cmd_race_edit_cp_help");
									Race_send(playerid,"race_cmd_race_edit_saverace_help");
								}
								else {
									Race_send(playerid,"race_cme_race_edit_failed_errorpassword");
								}
							}
							else {
								Race_send(playerid,"race_cmd_race_edit_failed_unexistname");
							}
						}
						else {
							Race_send(playerid,"race_cmd_race_edit_failed_emptypassword");
							Race_send(playerid,"race_cmd_race_edit_start_help");
						}
					}
					else {
						Race_send(playerid,"race_cmd_race_edit_failed_emptyname");
						Race_send(playerid,"race_cmd_race_edit_start_help");
					}
				}
			}
		}
		else if(!strcmp("leave",cmd2,true)){
			if(Race_getPlrState(playerid) == race_state_edit){
				Race_clearPlrCache(playerid);
				Race_send(playerid,"race_cmd_race_edit_leave_succeed");
			}
			else {
				Race_send(playerid,"race_cmd_race_edit_leave_failed_notediting");
			}
		}
		else if(!strcmp("delete",cmd2,true)){
			if(GetPlayerAdminLevel(playerid) < 3){
				Race_send(playerid,"race_cmd_race_edit_delete_failed_nopower");
				return true;
			}
			if(!isnull(cmd3)){
				if(!isnull(cmd4)){
					new
						rid = Race_getridFromName(cmd3);
					if(rid != INVALID_RACE_ID){
						new	
							password[MAX_RACE_PASSWORD];
						Race_DB_get(rid, .password = password, .password_ = true);
						if(!strcmp(password,cmd4)){
							new
								name[MAX_RACE_NAME];
							Race_DB_get(rid, .name = name, .name_ = true);
							Race_send(playerid,"race_cmd_race_edit_delete_succeed",name);
							Race_DB_remove(rid);
						}
						else {
							Race_send(playerid,"race_cmd_race_edit_delete_failed_incorrectpassword");
						}
					}
					else {
						Race_send(playerid,"race_cmd_race_edit_delete_failed_unexistname");
					}
				}
				else {
					Race_send(playerid,"race_cmd_race_edit_delete_failed_emptypassword");
					Race_send(playerid,"race_cmd_race_edit_delete_help");
				}
			}
			else {
				Race_send(playerid,"race_cmd_race_edit_delete_failed_emptyname");
				Race_send(playerid,"race_cmd_race_edit_delete_help");
			}
		}		
		else if(!strcmp("name",cmd2,true)){
			if(Race_getPlrState(playerid) == race_state_edit){
				if(!isnull(cmd3)){
					if(strlen(cmd3) > 2 && strlen(cmd3) < MAX_RACE_NAME){
						if(IsSTDStr(cmd3)){
							if(Race_getridFromName(cmd3) == INVALID_RACE_ID){
								Race_setPlrName(playerid,cmd3);
								Race_DB_edit(Race_getPlrrid(playerid), .name = cmd3);
								Race_send(playerid,"race_cmd_race_edit_name_succeed",cmd3);
							}
							else {
								Race_send(playerid,"race_cmd_race_edit_failed_name_alreadyexist");
							}
						}
						else {
							Race_send(playerid,"race_cmd_race_edit_failed_name_invalid");
						}
					}
					else {
						Race_send(playerid,"race_cmd_race_edit_failed_name_outofindex",MAX_RACE_PASSWORD-1);
					}
				}
				else {
					Race_send(playerid,"race_cmd_race_edit_failed_empty");
					Race_send(playerid,"race_cmd_race_edit_name_help");		
				}					
			}
			else {
				Race_send(playerid,"race_cmd_race_edit_name_failed_notediting");
			}
		}
		else if(!strcmp("miaoshu",cmd2,true) || !strcmp("description",cmd2,true)){
			if(Race_getPlrState(playerid) == race_state_edit){
				if(strlen(cmd3) > 2 && strlen(cmd3) < MAX_RACE_DESCRIPTION){
					Race_setPlrDescription(playerid,cmd3);
					Race_DB_edit(Race_getPlrrid(playerid), .description = cmd3);
					Race_send(playerid,"race_cmd_race_edit_description_succeed_1");	
					Race_send(playerid,cmd3);
					Race_send(playerid,"race_cmd_race_edit_description_succeed_2");
				}
				else {
					Race_send(playerid,"race_cmd_race_edit_description_failed_outofindex",MAX_RACE_DESCRIPTION-1);
					Race_send(playerid,"race_cmd_race_edit_description_help");
				}
			}
			else {
				Race_send(playerid,"race_cmd_race_edit_failed_notediting");
			}
		}
		else if(!strcmp("password",cmd2,true) || !strcmp("mima",cmd2,true)){
			if(Race_getPlrState(playerid) == race_state_edit){
				if(strlen(cmd3) > 2 && strlen(cmd3) < MAX_RACE_PASSWORD){
					if(IsSTDStr(cmd3)){
						Race_setPlrPassword(playerid,cmd3);
						Race_DB_edit(Race_getPlrrid(playerid), .password = cmd3);
						Race_send(playerid,"race_cmd_race_edit_password_succeed",cmd3);
					}
					else {
						Race_send(playerid,"race_cmd_race_edit_password_failed_invalid");
					}
				}
				else {
					Race_send(playerid,"race_cmd_race_edit_password_failed_outofindex",MAX_RACE_PASSWORD-1);
					Race_send(playerid,"race_cmd_race_edit_password_help");
				}
			}
			else {
				Race_send(playerid,"race_cmd_race_edit_password_failed_notediting");
			}
		}
		else if(!strcmp("cp",cmd2,true)){
			if(Race_getPlrState(playerid) == race_state_edit){
				if(Race_getPlrEditState(playerid) == race_state_edit_none){
					if(!isnull(cmd3)){
						if(IsNumeric(cmd3)){
							new
								cpid = strval(cmd3);
							if(cpid >= 1 && cpid <= Race_getPlrCPAmount(playerid)){
								Race_setPlrEditState(playerid,race_state_edit_setcpinfo);
								if(cpid < Race_getPlrCPAmount(playerid)){
									Race_setPlrTocpid(playerid,cpid);
									Race_send(playerid,"race_cmd_race_edit_cp_succeed_setoldcp",cpid+1);
									Race_send(playerid,"race_cmd_race_edit_cp_succeed_hint1");
									Race_send(playerid,"race_cmd_race_edit_cp_succeed_hint2");
									Race_send(playerid,"race_cmd_race_edit_cp_succeed_hint3");
								}
								else {
									Race_send(playerid,"race_cmd_race_edit_cp_succeed_setnewcp");
									Race_send(playerid,"race_cmd_race_edit_cp_succeed_hint1");
									Race_send(playerid,"race_cmd_race_edit_cp_succeed_hint2");
									Race_send(playerid,"race_cmd_race_edit_cp_succeed_hint3");
								}
							}
							else {
								Race_send(playerid,"race_cmd_race_edit_cp_failed_notexist");
								Race_send(playerid,"race_cmd_race_edit_cp_help");
							}
						}
						else {
							Race_send(playerid,"race_cmd_race_edit_cp_failed_invalid");
							Race_send(playerid,"race_cmd_race_edit_cp_help");
						}
					}
					else {
						Race_send(playerid,"race_cmd_race_edit_cp_failed_emptyinput");
						Race_send(playerid,"race_cmd_race_edit_cp_help");
					}
				}
				else if(Race_getPlrEditState(playerid) == race_state_edit_setcpinfo){
					Race_send(playerid,"race_cmd_race_edit_cp_failed_setting");
					Race_send(playerid,"race_cmd_race_edit_cp_failed_setting_hint1");
					Race_send(playerid,"race_cmd_race_edit_cp_failed_setting_hint2");
				}
			}
			else {
				Race_send(playerid,"race_cmd_race_edit_cp_failed_notediting");
			}
		}
		else if(!strcmp("setcppos",cmd2,true) || !strcmp("setcp",cmd2,true)){
			if(Race_getPlrState(playerid) == race_state_edit){
				if(Race_getPlrEditState(playerid) == race_state_edit_setcpinfo){
					Race_setPlrCPPosx(playerid,Race_getPlrcpid(playerid),pX(playerid));
					Race_setPlrCPPosy(playerid,Race_getPlrcpid(playerid),pY(playerid));
					Race_setPlrCPPosz(playerid,Race_getPlrcpid(playerid),pZ(playerid));
					//Race_setPlrCPPos(playerid,Race_getPlrcpid(playerid),pX(playerid),pY(playerid),pZ(playerid));
					//Race_editcpInDB(Race_getPlrrid(playerid),Race_getPlrcpid(playerid), .x = pX(playerid), .y = pY(playerid), .z = pZ(playerid));
					Race_setPlrRacingCP(playerid,Race_getPlrcpid(playerid));
					Race_send(playerid,"race_cmd_race_edit_setcppos_succeed");
					Race_send(playerid,"race_cmd_race_edit_setcppos_succeed_hint1");
					Race_send(playerid,"race_cmd_race_edit_setcppos_succeed_hint2");
					Race_send(playerid,"race_cmd_race_edit_setcppos_succeed_hint3");
				}
				else if(Race_getPlrEditState(playerid) == race_state_edit_none){
					Race_send(playerid,"race_cmd_race_edit_setcppos_failed_notinset");
					Race_send(playerid,"race_cmd_race_edit_setcppos_failed_notinset_hint1");
					Race_send(playerid,"race_cmd_race_edit_setcppos_help");
				}
			}
			else {
				Race_send(playerid,"[赛道维护]你不在赛道维护模式,请输入 - /r help - 查看帮助");
			}
		}
		else if(!strcmp("setcpsize",cmd2,true)){
			if(Race_getPlrState(playerid) == race_state_edit){
				if(Race_getPlrEditState(playerid) == race_state_edit_setcpinfo){
					if(!isnull(cmd3)){
						if(IsFloatric(cmd3)){
							new
								Float:size = floatstr(cmd3);
							Race_setPlrCPSize(playerid,Race_getPlrcpid(playerid),size);
							//Race_editcpInDB(Race_getPlrrid(playerid),Race_getPlrcpid(playerid), .s = size);
							Race_setPlrRacingCP(playerid,Race_getPlrcpid(playerid));
							Race_send(playerid,"race_cmd_race_edit_setcppsize_succeed");
							Race_send(playerid,"race_cmd_race_edit_setcppsize_succeed_hint1");
							Race_send(playerid,"race_cmd_race_edit_setcppsize_succeed_hint2");
							Race_send(playerid,"race_cmd_race_edit_setcppsize_succeed_hint3");							
						}
						else {
							Race_send(playerid,"race_cmd_race_edit_setcppsize_failed_errorinput");
							Race_send(playerid,"race_cmd_race_edit_setcppsize_help");
						}
					}
					else {
						Race_send(playerid,"race_cmd_race_edit_setcppsize_failed_errorinput");
						Race_send(playerid,"race_cmd_race_edit_setcppsize_help");
					}
				}
				else if(Race_getPlrEditState(playerid) == race_state_edit_none){
					Race_send(playerid,"race_cmd_race_edit_setcppsize_failed_notinset");
					Race_send(playerid,"race_cmd_race_edit_setcppsize_failed_notinset_hint1");
					Race_send(playerid,"race_cmd_race_edit_setcppsize_help");
				}
			}
			else {
				Race_send(playerid,"race_cmd_race_edit_setcppsize_failed_notediting");
			}
		}		
		else if(!strcmp("setcptype",cmd2,true)){
			if(Race_getPlrState(playerid) == race_state_edit){
				if(Race_getPlrEditState(playerid) == race_state_edit_setcpinfo){
					if(!isnull(cmd3)){
						if(IsNumeric(cmd3)){
							new
								type = strval(cmd3);
							Race_setPlrCPType(playerid,Race_getPlrcpid(playerid),type);
							//Race_editcpInDB(Race_getPlrrid(playerid),Race_getPlrcpid(playerid), .t = size);
							Race_setPlrRacingCP(playerid,Race_getPlrcpid(playerid));
							Race_send(playerid,"race_cmd_race_edit_setcptype_succeed");
							Race_send(playerid,"race_cmd_race_edit_setcptype_succeed_hint1");
							Race_send(playerid,"race_cmd_race_edit_setcptype_succeed_hint2");
							Race_send(playerid,"race_cmd_race_edit_setcptype_succeed_hint3");							
						}
						else {
							Race_send(playerid,"race_cmd_race_edit_setcptype_failed_errorinput");
							Race_send(playerid,"race_cmd_race_edit_setcptype_help");
						}
					}
					else {
						Race_send(playerid,"race_cmd_race_edit_setcptype_failed_errorinput");
						Race_send(playerid,"race_cmd_race_edit_setcptype_help");
					}
				}
				else if(Race_getPlrEditState(playerid) == race_state_edit_none){
					Race_send(playerid,"race_cmd_race_edit_setcptype_failed_notinset");
					Race_send(playerid,"race_cmd_race_edit_setcptype_failed_notinset_hint1");
					Race_send(playerid,"race_cmd_race_edit_setcptype_help");
				}
			}
			else {
				Race_send(playerid,"race_cmd_race_edit_setcptype_failed_notediting");
			}
		}
		else if(!strcmp("savecp",cmd2,true)){
			if(Race_getPlrState(playerid) == race_state_edit){
				if(Race_getPlrEditState(playerid) == race_state_edit_setcpinfo){
					new
						cpid = Race_getPlrcpid(playerid);
					Race_setPlrEditState(playerid,race_state_edit_none);
					if(cpid < Race_getPlrCPAmount(playerid)){
						Race_DB_editcp(Race_getPlrrid(playerid),Race_getPlrcpid(playerid),Race_getPlrCPType(playerid,cpid),Race_getPlrCPSize(playerid,cpid),Race_getPlrCPPosx(playerid,cpid),Race_getPlrCPPosy(playerid,cpid),Race_getPlrCPPosz(playerid,cpid),Race_getPlrCPAngel(playerid,cpid));
						Race_send(playerid,"race_cmd_race_edit_savecp_succeed_saveold");
					}
					else {
						Race_DB_createcp(Race_getPlrrid(playerid),Race_getPlrCPType(playerid,cpid),Race_getPlrCPSize(playerid,cpid),Race_getPlrCPPosx(playerid,cpid),Race_getPlrCPPosy(playerid,cpid),Race_getPlrCPPosz(playerid,cpid),Race_getPlrCPAngel(playerid,cpid));
						Race_setPlrCPAmount(playerid,Race_getPlrCPAmount(playerid)+1);
						Race_send(playerid,"race_cmd_race_edit_savecp_succeed_savenew");
					}
					Race_send(playerid,"race_cmd_race_edit_savecp_succeed_hint1");
					Race_send(playerid,"race_cmd_race_edit_savecp_succeed_hint2");
				}
				else if(Race_getPlrEditState(playerid) == race_state_edit_none){
					Race_send(playerid,"race_cmd_race_edit_savecp_failed_notinset");
					Race_send(playerid,"race_cmd_race_edit_savecp_failed_notinset_hint1");
					Race_send(playerid,"race_cmd_race_edit_savecp_failed_notinset_hint2");
					Race_send(playerid,"race_cmd_race_edit_savecp_help");
				}
			}
			else {
				Race_send(playerid,"race_cmd_race_edit_savecp_failed_notediting");
			}
		}
		else if(!strcmp("saverace",cmd2,true)){
			if(Race_getPlrState(playerid) == race_state_edit){
				if(Race_getPlrEditState(playerid) == race_state_edit_none){
					Race_DB_edit(Race_getPlrrid(playerid), .builder = pName(playerid), .lenth = Race_prefixPlrDistance(playerid));
					Race_clearPlrCache(playerid);
					Race_send(playerid,"race_cmd_race_edit_saverace_succeed");
				}
				else if(Race_getPlrEditState(playerid) == race_state_edit_setcpinfo){
					Race_send(playerid,"race_cmd_race_edit_saverace_failed_inset");
					Race_send(playerid,"race_cmd_race_edit_saverace_failed_inset_hint");
					Race_send(playerid,"race_cmd_race_edit_saverace_help");
				}
			}
			else {
				Race_send(playerid,"race_cmd_race_edit_saverace_failed_notediting");
			}
		}
		else {
			Race_send(playerid,"race_cmd_race_edit_invalidcmd",params);
		}
	}
	else if(!strcmp("build",cmd1,true)){
		if(!strcmp("help",cmd2,true)){
			Race_Dialogprocess(playerid,race_dg_help_build);
		}
		else if(!strcmp("start",cmd2,true)){
			if(Race_getPlrState(playerid) == race_state_none){
				if(!isnull(cmd3)){
					if(!isnull(cmd4)){
						if(strlen(cmd3) > 2 && strlen(cmd3) < MAX_RACE_NAME){
							if(IsSTDStr(cmd3)){
								if(strlen(cmd4) > 2 && strlen(cmd4) < MAX_RACE_PASSWORD){
									if(IsSTDStr(cmd4)){
										if(Race_getridFromName(cmd3) == INVALID_RACE_ID){
											Race_setPlrState(playerid,race_state_build);
											Race_setPlrBuildState(playerid,race_state_build_setcppos);
											Race_setPlrSlot(playerid,Race_getSlot());
											Race_setPlrrid(playerid,Race_DB_create(cmd3,cmd4));
											Race_setPlrName(playerid,cmd3);
											Race_setPlrPassword(playerid,cmd4);
											Race_setPlrcpid(playerid,0);
											Race_send(playerid,"race_cmd_race_build_start_succeed");	
											Race_send(playerid,"race_cmd_race_build_start_succeed_hint");
										}
										else {
											Race_send(playerid,"race_cmd_race_build_start_failed_name_alreadyexist");
										}
									}
									else {
										Race_send(playerid,"race_cmd_race_build_start_failed_password_invalid");
										Race_send(playerid,"race_cmd_race_build_start_help");
									}
								}
								else {
									Race_send(playerid,"race_cmd_race_build_start_failed_password_outofindex",MAX_RACE_PASSWORD-1);
									Race_send(playerid,"race_cmd_race_build_start_help");	
								}
							}
							else {
								Race_send(playerid,"race_cmd_race_build_start_failed_paswword_invalid");
								Race_send(playerid,"race_cmd_race_build_start_help");	
							}
						}
						else {
							Race_send(playerid,"race_cmd_race_build_start_failed_name_invalid",MAX_RACE_PASSWORD-1);
							Race_send(playerid,"race_cmd_race_build_start_help");	
						}
					}
					else {
						Race_send(playerid,"race_cmd_race_build_start_failed_password_empty");
						Race_send(playerid,"race_cmd_race_build_start_help");	
					}
				}
				else {
					Race_send(playerid,"race_cmd_race_build_start_failed_name_empty");
					Race_send(playerid,"race_cmd_race_build_start_help");					
				}
			}
			else if(Race_getPlrState(playerid) == race_state_race){
				Race_send(playerid,"race_cmd_race_build_start_failed_racing");
			}
			else if(Race_getPlrState(playerid) == race_state_edit){
				Race_send(playerid,"race_cmd_race_build_start_failed_editing");
			}
			else if(Race_getPlrState(playerid) == race_state_build){
				Race_send(playerid,"race_cmd_race_build_start_failed_building");
			}
			else {
				Race_send(playerid,"race_cmd_race_build_start_failed_unkownreason");
			}
		}
		else if(!strcmp("leave",cmd2,true) || !strcmp("likai",cmd2,true) || !strcmp("exit",cmd2,true)){
			if(Race_getPlrState(playerid) == race_state_build){
				//leave build;
				//Race_clearCache(Race_getPlrrid(playerid));
				Race_clearPlrCache(playerid);
				Race_send(playerid,"race_cmd_race_build_leave_succeed");
				Race_send(playerid,"race_cmd_race_build_leave_succeed_hint");
			}
			else {
				Race_send(playerid,"race_cmd_race_build_leave_failed");
			}
		}
		else if(!strcmp("setcptype",cmd2,true)){
			if(Race_getPlrState(playerid) == race_state_build){
				if(Race_getPlrBuildState(playerid) == race_state_build_setcpinfo){
					if(IsNumeric(cmd3)){
						new
							type = strval(cmd3);
						if(type >=0){
							Race_setPlrCPType(playerid,Race_getPlrcpid(playerid),type);
							Race_setPlrRacingCP(playerid,Race_getPlrcpid(playerid));
							Race_send(playerid,"race_cmd_race_build_setcptype_succeed",type);
						}
						else {
							Race_send(playerid,"race_cmd_race_build_setcptype_failed_negativenum");
						}
					}
					else {
						Race_send(playerid,"race_cmd_race_build_setcptype_failed_invalid");
					}
				}
				else {
					Race_send(playerid,"race_cmd_race_build_setcptype_failed_cannotset");
				}
			}
		}
		else if(!strcmp("setcpsize",cmd2,true)){
			if(Race_getPlrState(playerid) == race_state_build){
				if(Race_getPlrBuildState(playerid) == race_state_build_setcpinfo){
					if(IsFloatric(cmd3)){
						new
							Float:size = floatstr(cmd3);
						if(size > 0 && size < 10000){
							Race_setPlrCPSize(playerid,Race_getPlrcpid(playerid),size);
							Race_setPlrRacingCP(playerid,Race_getPlrcpid(playerid));
							Race_send(playerid,"race_cmd_race_build_setcpsize_succeed",size);
							Race_send(playerid,"race_cmd_race_build_setcpsize_succeed_hint");
						}
						else {
							Race_send(playerid,"race_cmd_race_build_setcpsize_failed_outofindex");
						}
					}
					else {
						Race_send(playerid,"race_cmd_race_build_setcpsize_failed_invalidinput");
					}
				}
				else {
					Race_send(playerid,"race_cmd_race_build_setcpsize_failed_cannotset");
				}
			}
			else {
				Race_send(playerid,"race_cmd_race_build_setcpsize_failed_cannotset");
			}
		}
		else if(!strcmp("setcp",cmd2,true) || !strcmp("setcppos",cmd2,true)){
			if(Race_getPlrState(playerid) == race_state_build){
					if(Race_getPlrBuildState(playerid) == race_state_build_setcpinfo){
						//set curcp to curpos
						//Race_setPlrCPSize(playerid,Race_getPlrcpid(playerid),10);
						Race_setPlrCPPosx(playerid,Race_getPlrcpid(playerid),pX(playerid));
						Race_setPlrCPPosy(playerid,Race_getPlrcpid(playerid),pY(playerid));
						Race_setPlrCPPosz(playerid,Race_getPlrcpid(playerid),pZ(playerid));
						//Race_setPlrCPPos(playerid,Race_getPlrcpid(playerid),pX(playerid),pY(playerid),pZ(playerid));
						//Race_setPlrCPType(playerid,Race_getPlrcpid(playerid),0);
						Race_setPlrRacingCP(playerid,Race_getPlrcpid(playerid));
						Race_send(playerid,"race_cmd_race_build_setcppos_succeed");
						Race_send(playerid,"race_cmd_race_build_setcppos_succeed_hint1");
						Race_send(playerid,"race_cmd_race_build_setcppos_succeed_hint2");
						Race_send(playerid,"race_cmd_race_build_setcppos_succeed_hint3");
					}
					else if(Race_getPlrBuildState(playerid) == race_state_build_setcppos){
						//create cp, set to cur pos
						Race_setPlrBuildState(playerid,race_state_build_setcpinfo);
						Race_setPlrCPSize(playerid,Race_getPlrcpid(playerid),10);
						Race_setPlrCPPosx(playerid,Race_getPlrcpid(playerid),pX(playerid));
						Race_setPlrCPPosy(playerid,Race_getPlrcpid(playerid),pY(playerid));
						Race_setPlrCPPosz(playerid,Race_getPlrcpid(playerid),pZ(playerid));
						Race_setPlrCPType(playerid,Race_getPlrcpid(playerid),0);
						//Race_setPlrCPPos(playerid,Race_getPlrcpid(playerid),pX(playerid),pY(playerid),pZ(playerid));
						Race_setPlrRacingCP(playerid,Race_getPlrcpid(playerid));
						Race_send(playerid,"race_cmd_race_build_setcppos_succeed");
						Race_send(playerid,"race_cmd_race_build_setcppos_succeed_hint1");
						Race_send(playerid,"race_cmd_race_build_setcppos_succeed_hint2");
						Race_send(playerid,"race_cmd_race_build_setcppos_succeed_hint3");
						
						Race_send(playerid,"race_cmd_race_build_setcppos_succeed_startset");
					}
			}
			else {
				Race_send(playerid,"race_cmd_race_build_setcppos_failed_cannotuse");
			}
		}
		else if(!strcmp("savecp",cmd2,true)){
			if(Race_getPlrState(playerid) == race_state_build){
				if(Race_getPlrBuildState(playerid) == race_state_build_setcpinfo){
					new
						cpid = Race_getPlrcpid(playerid);
					Race_DB_createcp(Race_getPlrrid(playerid),Race_getPlrCPType(playerid,cpid),Race_getPlrCPSize(playerid,cpid),Race_getPlrCPPosx(playerid,cpid),Race_getPlrCPPosy(playerid,cpid),Race_getPlrCPPosz(playerid,cpid),Race_getPlrCPAngel(playerid,cpid));
					Race_setPlrCPAmount(playerid,Race_getPlrCPAmount(playerid)+1);
					Race_setPlrBuildState(playerid,race_state_build_setcppos);
					Race_removePlrRacingCP(playerid);
					Race_setPlrcpid(playerid,Race_getPlrcpid(playerid)+1);
					Race_send(playerid,"race_cmd_race_build_savecp_succeed");
					Race_send(playerid,"race_cmd_race_build_savecp_succeed_hint");
				}
				else {
					Race_send(playerid,"race_cmd_race_build_savecp_failed_inset");
				}
			}
			else {
				Race_send(playerid,"race_cmd_race_build_savecp_failed_cannoutuse");
			}
		}
		else if(!strcmp("saverace",cmd2,true)){
			if(Race_getPlrState(playerid) == race_state_build){
				if(Race_getPlrBuildState(playerid) == race_state_build_setcppos){
					//dialog for inputting race info
					Race_setPlrBuilder(playerid,pName(playerid));
					Race_setPlrBuildState(playerid,race_state_build_info);
					Race_Dialogprocess(playerid,race_dg_sr_setdes);
					Race_prefixPlrDistance(playerid);
					Race_send(playerid,"race_cmd_race_build_saverace_succeed");
				}
				else if(Race_getPlrBuildState(playerid) == race_state_build_setcpinfo){
					Race_send(playerid,"race_cmd_race_build_saverace_failed_inset");
				}
			}
			else {
				Race_send(playerid,"race_cmd_race_build_saverace_failed_cannotuse");
			}
		}
	}		
	else {
		Race_send(playerid,"race_cmd_race_build_invalidcmd",params);
	}
	return true;
}
pzcmd(race){rzcmd(cmd_race);}
pzcmd(r){rzcmd(cmd_race);}
pzcmd(saiche){rzcmd(cmd_race);}

/*
forward Race_changeslate();
public Race_changeslate(){ debug_public_track("Race_changeslate(){");
	new
		File:open_hdl = fopen("wl/race/race.list",io_read),
		filestr[MAX_FILE_STR],
		line,
		starttranslate;
	while(fread(open_hdl,filestr)){
		//if(strfind(filestr,"dangerous") != -1)starttranslate = true;
		//if(!starttranslate)continue
		stripNewLine(filestr);
		new
			filepath[256];
		format(filepath,sizeof(filepath),"wl/race/%s.race",filestr);
		gini_open(filepath);
		new
			name[256],
			builder[256],
			password[256],
			description[256],
			raced_times,
			lastrundate[256],
			interior,
			cpAmount,
			Float:lenth;
		format(name,256,gini_reads(data_race_Name));
		format(builder,256,gini_reads(data_race_Builder));
		format(password,256,gini_reads(data_race_Password));
		format(description,256,gini_reads(data_race_Description));
		format(lastrundate,256,gini_reads(data_race_LastRunDate));
		raced_times = gini_readi(data_race_RaceTimes);
		interior = gini_readi(data_race_Interior);
		cpAmount = gini_readi(data_race_cpAmount);
		lenth = gini_readf(data_race_Distance);
		new 
			rid = Race_DB_create(name,password);
		Race_DB_edit(rid,name,password,builder,description,raced_times,lastrundate,interior,cpAmount,lenth);	
		for(new cpid,tmpstr[MAX_MSG_STR];cpid < cpAmount;cpid++){
			new
				Float:x,Float:y,Float:z,
				Float:a,Float:s,
				t;
			format(tmpstr,sizeof(tmpstr),"%s%03d",data_race_cp,cpid);
			sscanf(gini_reads(tmpstr),"p,fffffi",x,y,z,a,s,t);
			Race_DB_createcp(rid,t,s,x,y,z,a);
		}
		gini_close();		
		printf("race translated, amount:%d",++line);
	}
	fclose(open_hdl);
}
*/


#else
Race_struct(){
	return true;
}
Race_DialogResponse(playerid, dialogid, response, listitem, inputtext[]){
	#pragma unused playerid, dialogid, response, listitem, inputtext
	return false;
}
Race_EnterRaceCheckpoint(playerid){
	#pragma unused playerid
	return true;
}
Race_playerConnect(playerid){
	#pragma unused playerid
}
Race_playerDisconnect(playerid){
	#pragma unused playerid
}
Race_playerDeath(playerid){
	#pragma unused playerid
}
#endif





























