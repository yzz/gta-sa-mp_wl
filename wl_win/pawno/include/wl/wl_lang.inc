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


lang_addNew(const lang_identify[]){	
	new
		langid;
	langid = GetGVarInt("wl_lang_amount");
	SetGVarString("wl_lang_identify",lang_identify,langid);
	SetGVarInt("wl_lang_amount",langid+1);
}	
	
#define getargAsString(%0,%1,%2) \
	(%2) = 0; \
	while((%0[(%2)] = getarg((%1),(%2)))) (%2)++

stock wl_setPlayerLang(playerid,langid){
	SetPVarInt(playerid,"wl_plr_lang",langid);
	return true;
}
stock wl_getPlayerLang(playerid){
	return GetPVarInt(playerid,"wl_plr_lang");
}



#define MAX_MSG_FORMAT			(10)
enum E_wl_lang_formatnation_data {
	E_wl_lang_formatnation_none,
	E_wl_lang_formatnation_integer,
	Float:E_wl_lang_formatnation_float,
	E_wl_lang_formatnation_string[MAX_MSG_STR]
};
static
	wlf[MAX_MSG_FORMAT][E_wl_lang_formatnation_data],//wl_lang_formatnation[10][E_wl_lang_formatnation_data],
	E_wl_lang_formatnation_data:wl_lang_formatnation_var_type[MAX_MSG_FORMAT];

stock E_wl_lang_formatnation_data:gfnum(index){
	return wl_lang_formatnation_var_type[index];
}
#define formatnation_INTEGER	E_wl_lang_formatnation_data:1
#define formatnation_FLOAT		E_wl_lang_formatnation_data:2
#define formatnation_STRING		E_wl_lang_formatnation_data:3

stock wl_lang_send(playerid,color,lang_identify[],{Float,_}:...){
	new
		numformat = numargs() - 3,
		input[MAX_MSG_STR],
		output[MAX_MSG_STR];
	GetGVarString(lang_identify,input,sizeof(input),wl_getPlayerLang(playerid));
	new
		charpos,formatpos;
	for(new i;i < MAX_MSG_FORMAT;i++) wl_lang_formatnation_var_type[i] = E_wl_lang_formatnation_data:0;
	while(input[charpos]){
		if(input[charpos] == '%'){
			switchloop:
			switch(input[charpos+1]){
				case '%':{
					charpos++;
				}
				case '0'..'9','.':{
					charpos++;
					goto switchloop;
				}
				case 'i','I','d','D':{
					charpos++;
					wl_lang_formatnation_var_type[formatpos++] = formatnation_INTEGER;
					if(formatpos >= MAX_MSG_FORMAT)break;
				}
				case 'f','F':{
					charpos++;
					wl_lang_formatnation_var_type[formatpos++] = formatnation_FLOAT;
					if(formatpos >= MAX_MSG_FORMAT)break;
				}	
				case 's','S':{
					charpos++;
					wl_lang_formatnation_var_type[formatpos++] = formatnation_STRING;
					if(formatpos >= MAX_MSG_FORMAT)break;
				}
				default:{
					charpos++;
				}
			}
		}
		else {
			charpos++;
		}
	}
	new
		tmpstr[MAX_MSG_STR],tmpint,Float:tmpflt;
	for(new i,j,m;i < MAX_MSG_FORMAT;i++){
		if(wl_lang_formatnation_var_type[i] == formatnation_INTEGER){
			tmpint = getarg(3+m);
			wlf[j][E_wl_lang_formatnation_integer] = tmpint;
			j++;
			m++;
		}
		else if(wl_lang_formatnation_var_type[i] == formatnation_FLOAT){
			tmpflt = Float:getarg(3+m);
			wlf[j][E_wl_lang_formatnation_float] = tmpflt;
			j++;
			m++;
		}
		else if(wl_lang_formatnation_var_type[i] == formatnation_STRING){
			new
				tmppos;
			getargAsString(tmpstr,(3+m),tmppos);
			//tmpstr[strlen(tmpstr)+1] = '\0';
			tmpstr[tmppos+1] = '\0';
			new pos;
			for(pos = 0;tmpstr[pos];pos++){
				wlf[j][E_wl_lang_formatnation_string][pos] = tmpstr[pos];
			}
			wlf[j][E_wl_lang_formatnation_string][pos] = '\0';
			//format(wlf[j][E_wl_lang_formatnation_string],MAX_MSG_STR,"%s",tmpflt);
			//printf "tmpstr:%s",tmpstr
			//printf "cache:%s",wlf[j][E_wl_lang_formatnation_string]
			j++;
			m++;
		}
	}
	switch(numformat){
		case 0:{
			format(output,sizeof(output),"%s",input);
		}
		case 1:{
			format(output,sizeof(output),input,wlf[0][gfnum(0)]);
		}
		case 2:{
			format(output,sizeof(output),input,wlf[0][gfnum(0)],wlf[1][gfnum(1)]);
		}
		case 3:{
			format(output,sizeof(output),input,wlf[0][gfnum(0)],wlf[1][gfnum(1)],wlf[2][gfnum(2)]);
		}
		case 4:{
			format(output,sizeof(output),input,wlf[0][gfnum(0)],wlf[1][gfnum(1)],wlf[2][gfnum(2)],wlf[3][gfnum(3)]);
		}
		case 5:{
			format(output,sizeof(output),input,wlf[0][gfnum(0)],wlf[1][gfnum(1)],wlf[2][gfnum(2)],wlf[3][gfnum(3)],wlf[4][gfnum(4)]);
		}
		case 6:{
			format(output,sizeof(output),input,wlf[0][gfnum(0)],wlf[1][gfnum(1)],wlf[2][gfnum(2)],wlf[3][gfnum(3)],wlf[4][gfnum(4)],wlf[5][gfnum(5)]);
		}
		case 7:{
			format(output,sizeof(output),input,wlf[0][gfnum(0)],wlf[1][gfnum(1)],wlf[2][gfnum(2)],wlf[3][gfnum(3)],wlf[4][gfnum(4)],wlf[5][gfnum(5)],wlf[6][gfnum(6)]);
		}
		case 8:{
			format(output,sizeof(output),input,wlf[0][gfnum(0)],wlf[1][gfnum(1)],wlf[2][gfnum(2)],wlf[3][gfnum(3)],wlf[4][gfnum(4)],wlf[5][gfnum(5)],wlf[6][gfnum(6)],wlf[7][gfnum(7)]);
		}
		case 9:{
			format(output,sizeof(output),input,wlf[0][gfnum(0)],wlf[1][gfnum(1)],wlf[2][gfnum(2)],wlf[3][gfnum(3)],wlf[4][gfnum(4)],wlf[5][gfnum(5)],wlf[6][gfnum(6)],wlf[7][gfnum(7)],wlf[8][gfnum(8)]);
		}
		case 10:{
			format(output,sizeof(output),input,wlf[0][gfnum(0)],wlf[1][gfnum(1)],wlf[2][gfnum(2)],wlf[3][gfnum(3)],wlf[4][gfnum(4)],wlf[5][gfnum(5)],wlf[6][gfnum(6)],wlf[7][gfnum(7)],wlf[8][gfnum(8)],wlf[9][gfnum(9)]);
		}
	}
	SendClientMessage(playerid,color,output);
	if(!input[0] || !output[0]){
		printf (" [Warning]Possible error, textID '%s' does not exist", lang_identify);
	}
}

stock wl_lang_sendAll(color,lang_identify[],{Float,_}:...){
	new
		numformat = numargs() - 2,
		input[MAX_MSG_STR],
		output[MAX_MSG_STR];
	for(new playerid;playerid < MAX_PLAYERS;playerid++){
		if(!IsPlayerConnected(playerid)) continue;
		if(GetGVarInt("wl_lang_formatted",wl_getPlayerLang(playerid))){
			goto formatend;
		}
		GetGVarString(lang_identify,input,sizeof(input),wl_getPlayerLang(playerid));
		
		new
			charpos,formatpos;
		for(new i;i < MAX_MSG_FORMAT;i++) wl_lang_formatnation_var_type[i] = E_wl_lang_formatnation_data:0;
		while(input[charpos]){
			if(input[charpos] == '%'){
				switchloop:
				switch(input[charpos+1]){
					case '%':{
						charpos++;
					}
					case '0'..'9','.':{
						charpos++;
						goto switchloop;
					}
					case 'i','I','d','D':{
						charpos++;
						wl_lang_formatnation_var_type[formatpos++] = formatnation_INTEGER;
						if(formatpos >= MAX_MSG_FORMAT)break;
					}
					case 'f','F':{
						charpos++;
						wl_lang_formatnation_var_type[formatpos++] = formatnation_FLOAT;
						if(formatpos >= MAX_MSG_FORMAT)break;
					}	
					case 's','S':{
						charpos++;
						wl_lang_formatnation_var_type[formatpos++] = formatnation_STRING;
						if(formatpos >= MAX_MSG_FORMAT)break;
					}
					default:{
						charpos++;
					}
				}
			}
			else {
				charpos++;
			}
		}


		new
			tmpstr[MAX_MSG_STR],tmpint,Float:tmpflt;
		for(new i,j,m;i < MAX_MSG_FORMAT;i++){
			if(wl_lang_formatnation_var_type[i] == formatnation_INTEGER){
				tmpint = getarg(2+m);
				wlf[j][E_wl_lang_formatnation_integer] = tmpint;
				j++;
				m++;
			}
			else if(wl_lang_formatnation_var_type[i] == formatnation_FLOAT){
				tmpflt = Float:getarg(2+m);
				wlf[j][E_wl_lang_formatnation_float] = tmpflt;
				j++;
				m++;
			}
			else if(wl_lang_formatnation_var_type[i] == formatnation_STRING){
				new
					tmppos;
				getargAsString(tmpstr,(2+m),tmppos);
				//tmpstr[strlen(tmpstr)+1] = '\0';
				tmpstr[tmppos+1] = '\0';
				new pos;
				for(pos = 0;tmpstr[pos];pos++){
					wlf[j][E_wl_lang_formatnation_string][pos] = tmpstr[pos];
				}
				wlf[j][E_wl_lang_formatnation_string][pos] = '\0';
				//format(wlf[j][E_wl_lang_formatnation_string],MAX_MSG_STR,"%s",tmpflt);
				//printf "tmpstr:%s",tmpstr
				//printf "cache:%s",wlf[j][E_wl_lang_formatnation_string]
				j++;
				m++;
			}
		}
		switch(numformat){
			case 0:{
				format(output,sizeof(output),"%s",input);
			}
			case 1:{
				format(output,sizeof(output),input,wlf[0][gfnum(0)]);
			}
			case 2:{
				format(output,sizeof(output),input,wlf[0][gfnum(0)],wlf[1][gfnum(1)]);
			}
			case 3:{
				format(output,sizeof(output),input,wlf[0][gfnum(0)],wlf[1][gfnum(1)],wlf[2][gfnum(2)]);
			}
			case 4:{
				format(output,sizeof(output),input,wlf[0][gfnum(0)],wlf[1][gfnum(1)],wlf[2][gfnum(2)],wlf[3][gfnum(3)]);
			}
			case 5:{
				format(output,sizeof(output),input,wlf[0][gfnum(0)],wlf[1][gfnum(1)],wlf[2][gfnum(2)],wlf[3][gfnum(3)],wlf[4][gfnum(4)]);
			}
			case 6:{
				format(output,sizeof(output),input,wlf[0][gfnum(0)],wlf[1][gfnum(1)],wlf[2][gfnum(2)],wlf[3][gfnum(3)],wlf[4][gfnum(4)],wlf[5][gfnum(5)]);
			}
			case 7:{
				format(output,sizeof(output),input,wlf[0][gfnum(0)],wlf[1][gfnum(1)],wlf[2][gfnum(2)],wlf[3][gfnum(3)],wlf[4][gfnum(4)],wlf[5][gfnum(5)],wlf[6][gfnum(6)]);
			}
			case 8:{
				format(output,sizeof(output),input,wlf[0][gfnum(0)],wlf[1][gfnum(1)],wlf[2][gfnum(2)],wlf[3][gfnum(3)],wlf[4][gfnum(4)],wlf[5][gfnum(5)],wlf[6][gfnum(6)],wlf[7][gfnum(7)]);
			}
			case 9:{
				format(output,sizeof(output),input,wlf[0][gfnum(0)],wlf[1][gfnum(1)],wlf[2][gfnum(2)],wlf[3][gfnum(3)],wlf[4][gfnum(4)],wlf[5][gfnum(5)],wlf[6][gfnum(6)],wlf[7][gfnum(7)],wlf[8][gfnum(8)]);
			}
			case 10:{
				format(output,sizeof(output),input,wlf[0][gfnum(0)],wlf[1][gfnum(1)],wlf[2][gfnum(2)],wlf[3][gfnum(3)],wlf[4][gfnum(4)],wlf[5][gfnum(5)],wlf[6][gfnum(6)],wlf[7][gfnum(7)],wlf[8][gfnum(8)],wlf[9][gfnum(9)]);
			}
		}
		SetGVarString("wl_lang_formatted_str",output,wl_getPlayerLang(playerid));
		SetGVarInt("wl_lang_formatted",true,wl_getPlayerLang(playerid));
		formatend:
		SendClientMessage(playerid,color,output);
	}
	for(new i;i < GetGVarInt("wl_lang_amount");i++){
		SetGVarInt("wl_lang_formatted",false,i);
	}
	
	if(!input[0] || !output[0]){
		printf (" [Warning]Possible error, textID '%s' does not exist", lang_identify);
	}
}

#undef formatnation_INTEGER
#undef formatnation_FLOAT
#undef formatnation_STRING	



stock wl_lang_load(){
	new
		langIdentify[256],
		langid;
		
	Ext_fopen(1, "scriptfiles/wl/lang/langAdd.cfg", "r");
	while(Ext_fread(1,langIdentify) == 1/* && !Ext_feof(1)*/){
		new
			directIdentify[256],
			filepath[256];
		//printf("langIdentify:%s",langIdentify);
		//if(isnull(langIdentify))break;
		lang_addNew(langIdentify);
		Ext_fopen(2,"scriptfiles/wl/lang/langContain.cfg","r+");
		while(Ext_fread(2,directIdentify) == 1/* && !Ext_feof(2)*/){
			//printf("directIdentify:%s",directIdentify);
			//if(isnull(directIdentify))break;
			format(filepath,sizeof(filepath),"wl/lang/%s/%s",langIdentify,directIdentify);
			//printf("loading filepath:%s",filepath);
			gini_open(filepath);
			new
				entryid;
			while(strlen(gini_getEntryNameFromID(entryid))){
				//new
				//	valuename[256],
				//	valueset[256];
				//format(valuename,sizeof(valuename),gini_getEntryNameFromID(entryid));
				//format(valueset,sizeof(valueset),gini_reads(gini_getEntryNameFromID(entryid)));
				//stripNewLine(valuename);
				//stripNewLine(valueset);
				//SetGVarString(valuename,valueset,langid);
				SetGVarString(gini_getEntryNameFromID(entryid),gini_reads(gini_getEntryNameFromID(entryid)),langid);
				//printf("%s %d %s %s %d",filepath,entryid,gini_getEntryNameFromID(entryid),gini_reads(gini_getEntryNameFromID(entryid)),langid);
				entryid++;
			}
			gini_close();
		}
		langid++;
		Ext_fclose(2);
	}
	Ext_fclose(1);
	
	//print "over"
}




stock wl_lang_showdebug(){
	//for(new i;i < WL_LANG_AMOUNT;i++){
	//	printf "%s", wl_lang_str[wl_lang_chineseSimplified][i]
	//}
}



wl_lang_setDefaultLang(){
	//print "a"
	gini_open("wl/GlobalSet.ini");
	//print "b"
	SetGVarInt("wl_GlobalSet_DefaultLang",gini_readi("DefaultLang"));
	//printf "%d %d",GetGVarInt("wl_GlobalSet_DefaultLang"),gini_readi("DefaultLang")
	gini_close();
}
	
wl_lang_OnGameModeInit(){
	wl_lang_load();
	wl_lang_setDefaultLang();
	//wl_lang_showdebug();
	print ("[wl]language loaded.");
	return true;
}
	

wl_lang_OnPlayerConnect(playerid){
	wl_setPlayerLang(playerid,GetGVarInt("wl_GlobalSet_DefaultLang"));
	return true;
}


#define WL_LANG_DMW_ENTER_1											"dmw_enter_1"
#define WL_LANG_DMW_ENTER_2											"dmw_enter_2"
#define WL_LANG_DMW_ENTER_DENIED_NOTEAM								"dmw_enter_denied_noteam"
#define WL_LANG_DMW_ENTER_DENIED_GANGTAGBAN_1						"dmw_enter_denied_gangtagban_1"
#define WL_LANG_DMW_ENTER_DENIED_GANGTAGBAN_2						"dmw_enter_denied_gangtagban_2"
#define WL_LANG_DMW_ENTER_DENIED_NAMEBAN_1							"dmw_enter_denied_nameban_1"
#define WL_LANG_DMW_ENTER_DENIED_NAMEBAN_2							"dmw_enter_denied_nameban_2"
#define WL_LANG_DMW_ENTER_SPAWNGANG									"dmw_enter_spawngang"
#define WL_LANG_DMW_GANGREGISTER_HINT								"dmw_gangnotregisterd_hint"
#define WL_LANG_DMW_EXIT_1											"dmw_exit_1"
#define WL_LANG_DMW_EXIT_DENIED_NOTINT								"dmw_exit_denied_notin" 
#define WL_LANG_DMW_UNKNOWNCMD										"dmw_cmd_unknown"
#define WL_LANG_DMW_DMW_HASBENN_CLOSED								"dmw_been_closed"
#define WL_LANG_DMW_UNABLEATTACK_ATTACKINGANOTHERZONE				"attack_denied_already"
#define WL_LANG_DMW_UNABLEATTACK_NOTINZONE							"attack_denied_noinzone"
#define WL_LANG_DMW_UNABLEATTACK_SELFZONE							"attack_denied_selfzone"
#define WL_LANG_DMW_UNABLEATTACK_NOTOWNER							"attack_denied_notowner"
#define WL_LANG_DMW_ATTACKSTOP_RETREAT_NOTATTACKING_1				"stopat_denied_notating_1" 
#define WL_LANG_DMW_ATTACKSTOP_RETREAT_NOTATTACKING_2				"stopat_denied_notating_2"
#define WL_LANG_DMW_ATTACKSTOP_NOTOWNER								"stopat_denied_notowner" 
#define WL_LANG_DMW_ADMIN_CMD_BANTAG_USAGE							"bantag_usage"
#define WL_LANG_DMW_ADMIN_CMD_BANTAG_FAILED_ALREADYBANNED			"bantag_denied_alreadyban" 
#define WL_LANG_DMW_ADMIN_CMD_BANTAG_SUCCEED						"bantag_pass"
#define WL_LANG_DMW_ADMIN_CMD_BANTAG_FAILED_ILLEAGLTAG				"bantag_denied_illegaltag"
#define WL_LANG_DMW_ADMIN_CMD_BANPLAYERGANG_USAGE					"bangang_usage"
#define WL_LANG_DMW_ADMIN_CMD_BANPLAYERGANG_SUCCEED					"bangang_pass"
#define WL_LANG_DMW_ADMIN_CMD_BANPLAYERGANG_FAILED_NOTGANGMEMBER	"bangang_denied_nogang"
#define WL_LANG_DMW_ADMIN_CMD_BANPLAYERGANG_FAILED_NOTCONNECTED		"bangang_denied_offline"
#define WL_LANG_DMW_ADMIN_CMD_BANPLAYER_USAGE						"banplr_usage"
#define WL_LANG_DMW_ADMIN_CMD_BANPLAYER_SUCCEED						"banplr_pass"
#define WL_LANG_DMW_ADMIN_CMD_BANPLAYER_FAILED						"banplr_denied"
#define WL_LANG_DMW_DMW_ADMISSION_OPEN								"admit_open"
#define WL_LANG_DMW_DMW_ADMISSION_CLOSE								"admit_close"
#define WL_LANG_DMW_GANGDEFNCE_FAILED								"attack_win_toattack"
#define WL_LANG_DMW_GANGATTACK_SUCCEED								"attack_win_todefence"
#define WL_LANG_DMW_ZONECAPTURED_ANNOUNEMENT						"attack_win_toother"
#define WL_LANG_DMW_ATTACKSTOP_NOATTACKLEFT							"attack_lose_lose"
#define WL_LANG_DMW_ATTACKSTOP_RETREAT								"attack_lose_retreat"
#define WL_LANG_DMW_NOT_ALLOWED_IN									"dmw_disallowed_plr"
#define WL_LANG_DMW_ALLOWED_IN										"dmw_allowed_plr"
#define WL_LANG_DMW_ENTER_DNIED_ALREADYIN							"dmw_enter_denied_alreadyin"
#define WL_LANG_DMW_ENTER_DENIED_NOT_LOGGED							"dmw_enter_denied_notlogged"
#define WL_LANG_DMW_ENTER_DENIED_NOT_REGISTERED_GANG_MEMBER			"dmw_enter_denied_nogangallow"

#define WL_LANG_ACC_NOT_PRELOGIN									"acc_not_prelogin"
#define WL_LANG_ACC_CONNECT_ALREADY_REGISTERD						"acc_connect_registerded"
#define WL_LANG_ACC_CMD_REGISTER_FAILED_ALREADY_LOGIN				"acc_cmd_reg_denied_logged"
#define WL_LANG_ACC_CMD_REGISTER_FAILED_ALREADY_REGISTERED			"acc_cmd_reg_denied_reged"
#define WL_LANG_ACC_CMD_REGISTER_FAILED_NOT_ENTER_PASSWORD			"acc_cmd_reg_denied_nopassword"
#define WL_LANG_ACC_CMD_REGISTER_FAILED_INPUT_TOO_LONG				"acc_cmd_reg_denied_toolong"
#define WL_LANG_ACC_CMD_REGISTER_FAILED_INPUT_INVALID				"acc_cmd_reg_denied_invalid"
#define WL_LANG_ACC_CMD_REGISTER_PASS								"acc_cmd_reg_pass"
#define WL_LANG_ACC_CMD_LOGIN_PASS									"acc_cmd_login_pass"
#define WL_LANG_ACC_CMD_LOGIN_FAILED_ALREADY_LOGIN					"acc_login_denied_logged"
#define WL_LANG_ACC_CMD_LOGIN_FAILED_UNREGISTERED					"acc_login_denied_unreg"
#define WL_LANG_ACC_CMD_LOGIN_FAILED_NOT_ENTER_PASSWORD				"acc_login_denied_nopassword"
#define WL_LANG_ACC_CMD_LOGIN_FAILED_INVALID_PASSWORD				"acc_login_denied_invalid"
#define WL_LANG_ACC_CMD_LOGIN_FAILED_INCORRECT_PASSWORD				"acc_login_denied_incorrect"






