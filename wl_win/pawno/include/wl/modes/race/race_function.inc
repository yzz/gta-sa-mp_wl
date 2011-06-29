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


stock Race_setPlrName(playerid,name[]){
	SetPVarString(playerid,"wl_race_plr_r_name",name);
}
stock Race_getPlrName(playerid){
	new
		name[MAX_RACE_NAME];
	GetPVarString(playerid,"wl_race_plr_r_name",name,sizeof(name));
	return name;
}

stock Race_setPlrPassword(playerid,password[]){
	SetPVarString(playerid,"wl_race_plr_r_password",password);
	return true;
}
stock Race_getPlrPasswrod(playerid){
	new
		password[MAX_RACE_PASSWORD];
	GetPVarString(playerid,"wl_race_plr_r_password",password,sizeof(password));
	return password;
}

stock Race_setPlrBuilder(playerid,builder[]){
	SetPVarString(playerid,"wl_race_plr_r_builder",builder);
	return true;
}
stock Race_getPlrBuilder(playerid){
	new
		builder[MAX_RACE_BUILDER];
	GetPVarString(playerid,"wl_race_plr_r_builder",builder,sizeof(builder));
	return builder;
}

stock Race_setPlrDescription(playerid,description[]){
	SetPVarString(playerid,"wl_race_plr_r_description",description);
	return true;
}
stock Race_getPlrDescription(playerid){
	new
		description[MAX_RACE_DESCRIPTION];
	GetPVarString(playerid,"wl_race_plr_r_description",description,sizeof(description));
	return description;
}

stock Race_setPlrLastrundate(playerid,lastrundate[]){
	SetPVarString(playerid,"wl_race_plr_r_lastrundata",lastrundate);
	return true;
}
stock Race_getPlrLastrundate(playerid){
	new
		lastrundate[36];
	GetPVarString(playerid,"wl_race_plr_r_lastrundata",lastrundate);
	return lastrundate;
}

stock Race_setPlrRacedTimes(playerid,raced_times){
	SetPVarInt(playerid,"wl_race_plr_r_raced_times",raced_times);
	return true;
}
stock Race_getPlrRacedTimes(playerid){
	return GetPVarInt(playerid,"wl_race_plr_r_raced_times");
}

stock Race_setPlrInterior(playerid,interior){
	SetPVarInt(playerid,"wl_race_plr_r_interior",interior);
	return true;
}
stock Race_getPlrInterior(playerid){
	return GetPVarInt(playerid,"wl_race_plr_r_interior");
}

stock Race_setPlrCPAmount(playerid,cpAmount){
	SetPVarInt(playerid,"wl_race_plr_r_cpAmount",cpAmount);
	return true;
}
stock Race_getPlrCPAmount(playerid){
	return GetPVarInt(playerid,"wl_race_plr_r_cpAmount");
}

stock Race_setPlrDistance(playerid,Float:distance){
	SetPVarFloat(playerid,"wl_race_plr_r_distance",distance);
	return true;
}
stock Float:Race_getPlrDistance(playerid){
	return GetPVarFloat(playerid,"wl_race_plr_r_distance");
}

/*
stock Race_Formatcpid(const cpid,const tail[]){
	new
		tmpstr[MAX_MSG_STR];
	format(tmpstr,sizeof(tmpstr),"wl_race_plr_r_cp%d_%s",cpid,tail);
	return tmpstr;
}


#define Race_setPlrCPType(%1,%2,%3)
	SetPVarInt((%1),Race_Formatcpid((%2),"type"),(%3))
	
#define Race_getPlrCPType(%1,%2)
	GetPVarInt((%1),Race_Formatcpid((%2),"type"))
*/	

stock Race_setPlrCPType(playerid,cpid,type){
	new
		id[MAX_MSG_STR];
	format(id,sizeof(id),"wl_race_plr_r_cp%d_type",cpid);
	SetPVarInt(playerid,id,type);
	return true;
}
stock Race_getPlrCPType(playerid,cpid){
	new
		id[MAX_MSG_STR];
	format(id,sizeof(id),"wl_race_plr_r_cp%d_type",cpid);
	return GetPVarInt(playerid,id);
}

stock Race_setPlrCPSize(playerid,cpid,Float:size){
	new
		id[MAX_MSG_STR];
	format(id,sizeof(id),"wl_race_plr_r_cp%d_size",cpid);
	SetPVarFloat(playerid,id,size);
	return true;
}
stock Float:Race_getPlrCPSize(playerid,cpid){
	new
		id[MAX_MSG_STR];
	format(id,sizeof(id),"wl_race_plr_r_cp%d_size",cpid);
	return GetPVarFloat(playerid,id);
}

stock Race_setPlrCPPosx(playerid,cpid,Float:x){
	new
		id[MAX_MSG_STR];
	format(id,sizeof(id),"wl_race_plr_r_cp%d_posx",cpid);
	SetPVarFloat(playerid,id,x);
	return true;
}
stock Float:Race_getPlrCPPosx(playerid,cpid){
	new
		id[MAX_MSG_STR];
	format(id,sizeof(id),"wl_race_plr_r_cp%d_posx",cpid);
	return GetPVarFloat(playerid,id);
}

stock Race_setPlrCPPosy(playerid,cpid,Float:y){
	new
		id[MAX_MSG_STR];
	format(id,sizeof(id),"wl_race_plr_r_cp%d_posy",cpid);
	SetPVarFloat(playerid,id,y);
	return true;
}
stock Float:Race_getPlrCPPosy(playerid,cpid){
	new
		id[MAX_MSG_STR];
	format(id,sizeof(id),"wl_race_plr_r_cp%d_posy",cpid);
	return GetPVarFloat(playerid,id);
}

stock Race_setPlrCPPosz(playerid,cpid,Float:z){
	new
		id[MAX_MSG_STR];
	format(id,sizeof(id),"wl_race_plr_r_cp%d_posz",cpid);
	SetPVarFloat(playerid,id,z);
	return true;
}
stock Float:Race_getPlrCPPosz(playerid,cpid){
	new
		id[MAX_MSG_STR];
	format(id,sizeof(id),"wl_race_plr_r_cp%d_posz",cpid);
	return GetPVarFloat(playerid,id);
}

stock Race_setPlrCPAngel(playerid,cpid,Float:a){
	new
		id[MAX_MSG_STR];
	format(id,sizeof(id),"wl_race_plr_r_cp%d_angel",cpid);
	SetPVarFloat(playerid,id,a);
	return true;
}
stock Float:Race_getPlrCPAngel(playerid,cpid){
	new
		id[MAX_MSG_STR];
	format(id,sizeof(id),"wl_race_plr_r_cp%d_angel",cpid);
	return GetPVarFloat(playerid,id);
}

stock Race_setPlrDialogState(plrid,dialog_state){
	SetPVarInt(plrid,"wl_race_plr_state_dialog",dialog_state);
	return true;
}
stock Race_getPlrDialogState(plrid){
	return GetPVarInt(plrid,"wl_race_plr_state_dialog");
}

stock Race_setPlrDialogPage(plrid,page){
	SetPVarInt(plrid,"wl_race_plr_state_dialog_page",page);
	return true;
}
stock Race_getPlrDialogPage(plrid){
	return GetPVarInt(plrid,"wl_race_plr_state_dialog_page");
}

stock Race_setPlrDialogItem(plrid,item){
	SetPVarInt(plrid,"wl_race_plr_state_dialog_item",item);
	return true;
}
stock Race_getPlrDialogItem(plrid){
	return GetPVarInt(plrid,"wl_race_plr_state_dialog_item");
} 

stock Race_setPlrState(const plrid,const plr_state){
	SetPVarInt(plrid,"wl_race_plr_state",plr_state);
	return true;
}
stock Race_getPlrState(const plrid){
	return GetPVarInt(plrid,"wl_race_plr_state");
}

stock Race_setPlrRaceState(const plrid,const state_race){
	SetPVarInt(plrid,"wl_race_plr_state_race",state_race);
	return true;
}
stock Race_getPlrRaceState(const plrid){
	return GetPVarInt(plrid,"wl_race_plr_state_race");
}

stock Race_setPlrBuildState(const plrid,const state_build){
	SetPVarInt(plrid,"wl_race_plr_state_build",state_build);
	return true;
}
stock Race_getPlrBuildState(const plrid){
	return GetPVarInt(plrid,"wl_race_plr_state_build");
}

stock Race_setPlrSlot(const plrid,const slot){
	SetPVarInt(plrid,"wl_race_plr_slotid",slot);
}
stock Race_getPlrSlot(plrid){
	return GetPVarInt(plrid,"wl_race_plr_slotid");
}

stock Race_setPlrPosition(const plrid,const position){
	SetPVarInt(plrid,"wl_race_plr_position",position);
	return true;
}
stock Race_getPlrPosition(const plrid){
	return GetPVarInt(plrid,"wl_race_plr_position");
}

stock Race_setPlrPositionSlot(const plrid, const positionslot){
	SetPVarInt(plrid,"wl_race_plr_positionslot",positionslot);
	return true;
}
stock Race_getPlrPositionSlot(const plrid){
	return GetPVarInt(plrid,"wl_race_plr_positionslot");
}

stock Race_setPlrPositionSlotValue(const positionslot, const value){
	SetGVarInt("wl_race_plr_positionslotvalue",value,positionslot);
	return true;
}
stock Race_getPlrPositionSlotValue(const positionslot){
	return GetGVarInt("wl_race_plr_positionslotvalue",positionslot);
}

stock Race_setPlrrid(const plrid,const rid){
	SetPVarInt(plrid,"wl_race_plr_rid",rid);
	return true;
}
stock Race_getPlrrid(const plrid){
	return GetPVarInt(plrid,"wl_race_plr_rid");
}

stock Race_setPlrcpid(const plrid,const cpid){
	SetPVarInt(plrid,"wl_race_plr_cpid",cpid);
	return true;
}
stock Race_getPlrcpid(const plrid){
	return GetPVarInt(plrid,"wl_race_plr_cpid");
}

stock Race_setPlrStarttk(const plrid,const tickcount){
	SetPVarInt(plrid,"wl_race_plr_starttk",tickcount);
	return true;
}
stock Race_getPlrStarttk(const plrid){
	return GetPVarInt(plrid,"wl_race_plr_starttk");
}

stock Race_setPlrEndtk(const plrid,const tickcount){
	SetPVarInt(plrid,"wl_race_plr_endtk",tickcount);
	return true;
}
stock Race_getPlrEndtk(const plrid){
	return GetPVarInt(plrid,"wl_race_plr_endtk");
}

stock Race_setPlrEditState(playerid,edit_state){
	SetPVarInt(playerid,"wl_race_state_edit",edit_state);
	return true;
}
stock Race_getPlrEditState(playerid){
	return GetPVarInt(playerid,"wl_race_state_edit");
}