/**====================================================================================
								gcmd	
								


Description:
	Command system
		Own its individual command syntax
		Support "dcmd" syntax
		Support individual teleport command

Legal:
	Copyright (C) 2009 ,GCS Team
	
	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
	MA 02110-1301, USA.

Version:
	0.4.1
	
Changelog:
	08/07/17:
		0.4.0 -> 0.4.1
		Fix a bug that doesn;t work for some ids.
		Remove some debug info.
	08/06/08:
		0.3.1 -> 0.4.0
		Add new stuff,efficent tele command.
			
			gcmd_tele(command[],Float:x,Float:y,Float:z,Float:a,interior,ignorevec)
		0.3.0 -> 0.3.1
		Fix bug:
			When player input "/",it'll take the first command as it.
		User-opeartion changed:
			gcmd_getCommand(const cmd_identify,retstr[][])
			to
			gcmd_getCommand(const cmd_identify,retstr)
		Fix gcmd_getCommand(const cmd_identify,retstr[][]) bug,which will cause overflow crash.
	08/06/07:
		0.2.4 -> 0.3.0
		Add some documentation(s)
		Fix bug about no null param when using params[idx]
		Optimizate the code,takes more efficent.
		Remove strPool for efficent(both time&size)
		0.2.3 -> 0.2.4
		Param(s) use(s) less memory
	08/06/06:
		Edit some code for efficent
		Fix mix-name issues
		Similar dcmd support(means can translate dcmd to gcmd easily).
	08/05/29:
		Fix some bugs
	08/05/24:
		Second version
		Mostly rewrite for speed,readable,convenient
		Fix some issue
	08/05/1:
		First version

Bug:
	If using return value in gcmd(identify),it'll give warnning 209
	To remove the warnning,just edit all "return value;" to "return;"

Functions:
	@public:
		gcmd_struction() - Setup gcmd,use in OnGameModeInit/OnFilterScriptInit
		gcmd(cmd_identify[]) - To process a command.
		gcmd_tele(command[],Float:coordx,Float:coordy,Float:coordz,Float:p_facingangel,p_Interior,ignoreVec,remindtext[])
			- 1 command = 1 teleportion
		gcmd_create(cmd_identify[],{Float,_}:...) - Create a command with different types(support 10 different types)
		gcmd_delete(cmd_identify[]) - Delete a command
		gcmd_setPlayerAbleUse(playerid,cmd_identify[],enable) - (Dis/En)able player to use the command
		gcmd_getCommand(cmd_identify,retstr[][]) - get the commands' types
	@private:
		F private:
			gcmd(cmd_identify[]):
				param(format,{Float,_}:...) - for param like sscanf,defaultlly splited by whitespace
				player() - get the player who typed the command
				params(parampos) - get the param with string
				paramc(parampos,charpos) - get the char from the param
				parami(parampos) - get the param with integer
				paramf(parampos) - get the param with float
				paramn(parampos) - check the param is null or not
				paramsame(parampos,cmpstr[]) - check the param is same as cmpstr
			param(formation[],{Float,_}:...)
				gcmd_IsFloat - check if is Float
				gcmd_IsInt - Check if is Integer
			
		G private:
			gcmd_integerparam(parampos) - to integer the param
			gcmd_floatparam(parampos) - to float the param
			gcmd_EmptyPos() - get empty data to store
			gcmd_getStrSign(str) - get the string's sign
			gcmd_equal - check if is equal,faster than strcmp
			gcmd_replace - replace current character(s)
			gcmd_split - Split string from other string
			
Callbacks:
	gcmd_OnPlayerCommandText(playerid,cmdtext[]) - OnPlayerCommandText(playerid,cmdtext[])
	
Definitions:

	MAX_CMD - How many commands you can add
	MAX_CMD_COMMANDS - How many commands can store in a cmd_identify
	MAX_CMD_COMMAND_LENGTH - The maximum length of a command
	MAX_CMD_IDENTIFY_LENGTH - The maximum length of a cmd_identify
	MAX_CMD_POOL_LENGTH - The maximum length of a command_pool
	MAX_PARAM_AMOUNT - How many params to store
	MAX_CMD_SORT_TIMES - The maximun times for sorting command(for speed)
	INVALID_CMD_ID - 
	INVALID_CMD_COMMANDPOOL -
	
Variables:
	Global:
		gcs_n_gcmd_param
		gcs_n_gcmd_lastplayer
		gcs_n_gcmd_lasttext
		gcs_n_gcmd_lasttextlen
		gcs_n_gcmd_lasttextsign
		gcs_n_gcmd_lastparamamount
	Static:
		gcs_s_gcmd_commandpool
		gcs_s_gcmd
		gcs_s_gcmd_Amount
		gcs_s_gcmd_sort_pos
		gcs_s_gcmd_usetimes

=======================================================================================*/
#define GCMD_MAIN_USE			(true)


#if !defined MAX_STRING
	#define MAX_STRING	(128)
#endif




#if GCMD_MAIN_USE
/**=======================================================
*Date:2009/4/24
*Author:GCS Team
*Name:getargAsString
*Params:
*  argString,argPos,Pos
*Describe: get arg as string
========================================================*/
#define getFunctionArgAsString(%0,%1,%2) \
	(%2) = 0; \
	while((%0[(%2)] = getarg((%1),(%2)))) (%2)++
	
/**====================================================
Date:2009/5/23
Author:Nero_3D - 10
Description:
	methode = 0--> big to small
	methode = 1--> small to big
Note:
	syntax edit by GCS Team
==================================================*/

stock gcmd_SortArray(array[],source[],methode = 0,a_size = sizeof array,s_size = sizeof source){
	for(new i;i<a_size;i++)array[i] = -1;
	switch(methode){
		case 0:{
			for(new i,j,k;i<s_size;i++){
				for(j=0;j<a_size;j++){
					if(source[i]>((array[j]==-1)?(-1):(source[array[j]]))){
						for(k = a_size-2;k >= j;k--){
							array[k+1]=array[k];
						}
						array[j] = i;
						break;
					}
				}
			}
		}
		case 1:{
			for(new i,j,k;i < s_size;i++){
				for(j = 0;j<a_size;j++){
					if(source[i] < ((array[j] == -1)?(0x7F800000):(source[array[j]]))){
						for(k = a_size-2;k>=j;k--){
							array[k+1]=array[k];
						}
						array[j] = i;
						break;
					}
				}
			}
		}
		default:{
			return false;
		}
	}
	return true;
}

/**----------------------------------------------------------------------------*-
Aurhor:yless - Alex
Function:
sscanf
Params:
string[] - String to extract parameters from.
format[] - Parameter types to get.
{Float,_}:... - Data return variables.
Return:
0 - Successful, not 0 - fail.
Notes:
A fail is either insufficient variables to store the data or insufficient
data for the format string - excess data is disgarded.
 
A string in the middle of the input data is extracted as a single word, a
string at the end of the data collects all remaining text.
 
The format codes are:
 
c - A character.
d, i - An integer.
h, x - A hex number (e.g. a colour).
f - A float.
s - A string.
z - An optional string.
pX - An additional delimiter where X is another character.
'' - Encloses a litteral string to locate.
u - User, takes a name, part of a name or an id and returns the id if they're connected.
 
Now has IsNumeric integrated into the code.
 
Added additional delimiters in the form of all whitespace and an
optioanlly specified one in the format string.
-*----------------------------------------------------------------------------*/

stock gcmd_sscanf(string[], format[], {Float,_}:...){
#if defined isnull
	if (isnull(string))
#else
	if (string[0] == 0 || (string[0] == 1 && string[1] == 0))
#endif
	{
		return format[0];
	}
	new
		formatPos = 0,
		stringPos = 0,
		paramPos = 2,
		paramCount = numargs(),
		delim = ' ';
	while (string[stringPos] && string[stringPos] <= ' '){
		stringPos++;
	}
	while (paramPos < paramCount && string[stringPos]){
		switch (format[formatPos++]){
			case '\0':{
				return 0;
			}
			case 'i', 'd':{
				new
					neg = 1,
					num = 0,
					ch = string[stringPos];
				if (ch == '-'){
					neg = -1;
					ch = string[++stringPos];
				}
				do{
					stringPos++;
					if ('0' <= ch <= '9'){
						num = (num * 10) + (ch - '0');
					}else{
						return -1;
					}
				}
				while ((ch = string[stringPos]) > ' ' && ch != delim);
				setarg(paramPos, 0, num * neg);
			}
			case 'h', 'x':{
				new
					num = 0,
					ch = string[stringPos];
				do
				{
					stringPos++;
					switch (ch)
					{
						case 'x', 'X':
						{
							num = 0;
							continue;
						}
						case '0' .. '9':
						{
							num = (num << 4) | (ch - '0');
						}
						case 'a' .. 'f':
						{
							num = (num << 4) | (ch - ('a' - 10));
						}
						case 'A' .. 'F':
						{
							num = (num << 4) | (ch - ('A' - 10));
						}
						default:
						{
							return -1;
						}
					}
				}
				while ((ch = string[stringPos]) > ' ' && ch != delim);
				setarg(paramPos, 0, num);
			}
			case 'c':{
				setarg(paramPos, 0, string[stringPos++]);
			}
			case 'f':{//Edited
				//setarg(paramPos,0,_:floatstr(string[stringPos]))
				new
					changestr[16],
					changepos = 0,
					strpos = stringPos;
				while(changepos < 16 && string[strpos] && string[strpos] != delim){
					changestr[changepos++] = string[strpos++];
					//stringPos++;
				}
				changestr[changepos] = '\0'; 
				setarg(paramPos, 0, _:floatstr(changestr));
			}
			case 'p':{
				delim = format[formatPos++];
				continue;
			}
			case '\'':{
			new
				end = formatPos - 1,
				ch;
			while ((ch = format[++end]) && ch != '\''){}
			if (!ch){
				return -1;
			}
			format[end] = '\0';
			if ((ch = strfind(string, format[formatPos], false, stringPos)) == -1){
				if (format[end + 1]){
					return -1;
				}
				return 0;
			}
			format[end] = '\'';
			stringPos = ch + (end - formatPos);
			formatPos = end + 1;
			}
			case 'u':{
				new
					end = stringPos - 1,
					id = 0,
					bool:num = true,
					ch;
				while ((ch = string[++end]) && ch != delim){
					if (num){
						if ('0' <= ch <= '9'){
							id = (id * 10) + (ch - '0');
						}else{
							num = false;
						}
					}
				}
				if (num && IsPlayerConnected(id)){
					setarg(paramPos, 0, id);
				}else{
					#if !defined foreach
						#define foreach(%1,%2) for (new %2 = 0; %2 < MAX_PLAYERS; %2++) if (IsPlayerConnected(%2))
						#define __SSCANF_FOREACH__
					#endif
					string[end] = '\0';
					num = false;
					new
						name[MAX_PLAYER_NAME];
					id = end - stringPos;
					foreach (Player, playerid){
						GetPlayerName(playerid, name, sizeof (name));
						if (!strcmp(name, string[stringPos], true, id)){
							setarg(paramPos, 0, playerid);
							num = true;
							break;
						}
					}
					if (!num){
						setarg(paramPos, 0, INVALID_PLAYER_ID);
					}
					string[end] = ch;
					#if defined __SSCANF_FOREACH__
						#undef foreach
						#undef __SSCANF_FOREACH__
						#endif
				}
				stringPos = end;
			}
			case 's', 'z':{
				new
					i = 0,
					ch;
				if (format[formatPos]){
					while ((ch = string[stringPos++]) && ch != delim){
						setarg(paramPos, i++, ch);
					}
					if (!i){
						return -1;
					}
				}else{
					while ((ch = string[stringPos++])){
						setarg(paramPos, i++, ch);
					}
				}
				stringPos--;
				setarg(paramPos, i, '\0');
			}
			default:{
				continue;
			}
		}
		while (string[stringPos] && string[stringPos] != delim && string[stringPos] > ' '){
			stringPos++;
		}
		while (string[stringPos] && (string[stringPos] == delim || string[stringPos] <= ' ')){
			stringPos++;
		}
		paramPos++;
	}
	do{
		if ((delim = format[formatPos++]) > ' '){
			if (delim == '\''){
				while ((delim = format[formatPos++]) && delim != '\'') {}
			}else if (delim != 'z'){
				return delim;
			}
		}
	}
	while (delim > ' ');
	return 0;
}

#if !defined sscanf
	#define sscanf gcmd_sscanf
#endif


#endif
//===========================================================================================
#if GCMD_MAIN_USE

#define MAX_CMD					(1000)//Edit it to suit ur choice
#define MAX_CMD_COMMANDS		(5)
#define MAX_CMD_COMMAND_LENGTH	(16)
#define MAX_CMD_IDENTIFY_LENGTH	(18)
#define MAX_CMD_POOL_LENGTH		((MAX_CMD_IDENTIFY_LENGTH+2)+(MAX_CMD_COMMAND_LENGTH+2)*MAX_CMD_COMMANDS)
#define MAX_CMD_SORT_TIMES		(5000)//Edit it to change sort time
#define MAX_PARAM_AMOUNT		(12)
#define INVALID_CMD_ID			(-1)
#define INVALID_CMD_COMMANDPOOL	(-1)

enum{
	e_gcmd_param_data_none,
	e_gcmd_param_data_string,
	e_gcmd_param_data_integer,
	e_gcmd_param_data_float,
	e_gcmd_param_data_amount
}

enum e_gcmd_data{
	e_gcmd_string_pos,
	e_gcmd_string_len[1+MAX_CMD_COMMANDS],
	e_gcmd_string_sign[1+MAX_CMD_COMMANDS],
	bool:e_gcmd_pAbleUse[MAX_PLAYERS],
	e_gcmd_usetimes
};

enum e_gcmd_param_data{
	e_gcmd_param_string[MAX_STRING],
	Float:e_gcmd_param_float,
	e_gcmd_param_integer,
	bool:e_gcmd_param_floated,
	bool:e_gcmd_param_integered,
};




static stock
	gcs_s_gcmd_commandpool[MAX_CMD][MAX_CMD_POOL_LENGTH],
	gcs_s_gcmd[MAX_CMD][e_gcmd_data],
	gcs_s_gcmd_Amount,
	gcs_s_gcmd_sort_pos[MAX_CMD],
	gcs_s_gcmd_usetimes;

new stock
	gcs_n_gcmd_param[MAX_PARAM_AMOUNT][e_gcmd_param_data],
	gcs_n_gcmd_lastplayer = INVALID_PLAYER_ID,
	gcs_n_gcmd_lasttext[256],
	gcs_n_gcmd_lasttextlen,
	gcs_n_gcmd_lasttextsign,
	gcs_n_gcmd_lastparamamount;

#endif






#if GCMD_MAIN_USE
/**
*/
stock gcmd_getStrSign(const str[]){
	new
		i,j;
	while(str[i]) j += str[i++];
	return j;
}
#endif


#if GCMD_MAIN_USE
/**
Func:gcmd(cmd_identify[])

Note:
	Handles a command.
	It must use "return;" instead of "return value;",or it will give warrning 209
*/
#define gcmd(%1) \
	forward ggcmd_%1(playerid,params[]); \
	public ggcmd_%1(playerid,params[]) \
		if((params[0] == '\1' )?(!(params[0] = '\0')):true)


/**
Func:player()

Note:
	Get the player who called the command.
*/
#define player() \
	gcs_n_gcmd_lastplayer

/**
Func:params(parampos)

Note:
	Return the param with string
*/
#define params(%1) \
	gcs_n_gcmd_param[(%1)][e_gcmd_param_string]

/**
Func:paramc(parampos,charpos)

Note:
	Return the character(Haven't been tested)
*/
#define paramc(%1,%2) \
	((%1) <= gcs_n_gcmd_lastparamamount)?gcs_n_gcmd_param[(%1)][e_gcmd_param_string][(%2)]:'\0'

/**
Func:paramf(parampos)

Note:
	Return the param with tag:Float
*/
#define paramf(%1) \
	gcs_n_gcmd_param[(%1)][e_gcmd_param_floated]?gcs_n_gcmd_param[(%1)][e_gcmd_param_float]:gcmd_floatparam((%1))
	//((%1) <= gcs_n_gcmd_lastparamamount)?(gcs_n_gcmd_param[(%1)][e_gcmd_param_floated]?gcs_n_gcmd_param[(%1)][e_gcmd_param_float]:gcmd_floatparam((%1))):0.0




/**
Func:parami(parampos)

Note:
	Eeturn the param with tag:Integer
*/
#define parami(%1) \
	gcs_n_gcmd_param[(%1)][e_gcmd_param_integered]?gcs_n_gcmd_param[(%1)][e_gcmd_param_integer]:gcmd_integerparam((%1))
	//((%1) <= gcs_n_gcmd_lastparamamount)?(gcs_n_gcmd_param[(%1)][e_gcmd_param_integered]?gcs_n_gcmd_param[(%1)][e_gcmd_param_integer]:gcmd_integerparam((%1))):0

/**
Func:paramn(parampos)

Note:
	Check if is null param
*/
#define paramn(%1) \
	((%1) <= gcs_n_gcmd_lastparamamount)?(!gcs_n_gcmd_param[(%1)][e_gcmd_param_string][0]):true
	//!gcs_n_gcmd_param[(%1)][e_gcmd_param_string][0]
	//gcs_n_gcmd_param[(%1)][e_gcmd_param_string][0]?false:true
/**
Func:paramsame(parampos,const cmpstr[])

Note:
	Check if is equal
*/
#define paramsame(%1,%2) \
	(!strcmp(params((%1)),(%2)))
	
/**
Func:gcmd_IsInt(identify,pos)

Note:
	Check if is integer,used in param
*/
#define gcmd_IsInt(%1,%2) \
	new bool:%1 = true; \
	for(new %1pos;gcs_n_gcmd_param[(%2)][e_gcmd_param_string][%1pos] != '\0';(%1pos)++) \
	if((gcs_n_gcmd_param[(%2)][e_gcmd_param_string][%1pos] > '9' || gcs_n_gcmd_param[(%2)][e_gcmd_param_string][%1pos] < '0') && !(%1 = false)) break

/**
Func:gcmd_IsInt(identify,pos)

Note:
	Check if is float,used in param
*/
#define gcmd_IsFloat(%1,%2) \
	new bool:%1 = true; \
	for(new %1Pos,bool:%1Dot = false;gcs_n_gcmd_param[(%2)][e_gcmd_param_string][%1Pos] != '\0';(%1Pos)++) \
		if((gcs_n_gcmd_param[(%2)][e_gcmd_param_string][%1Pos] > '9' || gcs_n_gcmd_param[(%2)][e_gcmd_param_string][%1Pos] < '0')) \
			if(gcs_n_gcmd_param[(%2)][e_gcmd_param_string][%1Pos] != '.' && !(%1 = false)) break; \
			else \
				if(!(%1Dot)) %1Dot = true; \
				else if(!(%1 = false)) break
				

/**
Func: gcmd_equal(const str1[],const str2[],start1,end1,start2,end2)

Note:
	Check if is equal strings
*/
stock gcmd_equal(const str1[],const str2[],start1,end1,start2,end2){
	if((end1-start1) != (end2-start2)){
		return false;
	}
	while(str1[start1] && str2[start2] && start1 <= end1){
		if(str1[start1++] != str2[start2++]){
			return false;
		}
	}
	return true;
}

/**
Func:gcmd_replace(source[],const dest[],start,end)

Note:
	Replace current string
*/
stock gcmd_replace(source[],const dest[],start,end){
	new
		pos;
	while(start <= end && dest[pos]){
		source[start++] = dest[pos++];
	}
}

/**
Func:gcmd_split(const str[],start,end)

Note:
	Split string from another string
*/
stock gcmd_split(const str[],start,end){
	new
		retStr[MAX_STRING],
		pos;
	while(str[start] && start <= end){
		retStr[pos++] = str[start++];
	}
	retStr[pos] = '\0';
	return retStr;
}

/**
Func:gcmd_integerparam(const parampos)

Note:
	return the Interged of the param
*/
stock gcmd_integerparam(const parampos){
	if(!gcs_n_gcmd_param[parampos][e_gcmd_param_integered]){
		gcs_n_gcmd_param[parampos][e_gcmd_param_integered] = true;
		gcs_n_gcmd_param[parampos][e_gcmd_param_integer] = strval(gcs_n_gcmd_param[parampos][e_gcmd_param_string]);
	}
	return gcs_n_gcmd_param[parampos][e_gcmd_param_integer];
}

/**
Func:Float:gcmd_floatparam(const parampos)

Note:
	return the Floated of the param
*/
stock Float:gcmd_floatparam(const parampos){
	if(!gcs_n_gcmd_param[parampos][e_gcmd_param_floated]){
		gcs_n_gcmd_param[parampos][e_gcmd_param_floated] = true;
		gcs_n_gcmd_param[parampos][e_gcmd_param_float] = floatstr(gcs_n_gcmd_param[parampos][e_gcmd_param_string]);
	}
	return gcs_n_gcmd_param[parampos][e_gcmd_param_float];
}

/*
//not necessary to use
stock gcmd_stringparam(const parampos)
*/

				
/**
Func:param(formation[],{Float,_}:...)

Note:
	Like sscanf,but it only support string,user,integer and float.
	It is far more faster than using sscanf
	formation[] - 
		string(s,S,z,Z)
		user/playerid(u,U,p,P) - if the playerid is unconnection,also return false.
		integer(i,I,d,D)
		float(f,F)
		And:
			string > float > integer > user
			if you dont want to check in some places,use whitespace(' ') to format the pos
	{Float,_}:... - check if is appointed string(equal)
		And:
			If you dont want to check in some places,use null("") to ignore the pos
	
	Some Examples:
		param("iffff") - 
		param("i fi","","","","test") - 
		param("issf","","test") - 	
*/
stock param(formation[],{Float,_}:...){
	//struction
	new
		argPos = 1,
		argStrPos,
		argStr[128],
		copy_format[128];
	new const 
		argAmount = numargs()-1;
		
	for(new i = 1;i < (argAmount+1);i++,argPos++){//check if is same string() 
		getFunctionArgAsString(argStr,argPos,argStrPos);
		if(argStr[0]){
			if(strcmp(argStr,gcs_n_gcmd_param[i][e_gcmd_param_string])) return false;
		}
	}
	for(new i;formation[i];i++){//pass string
		copy_format[i] = formation[i];
	}
	new
		i,j;
	for(i = 0,j = 1;copy_format[i];i++,j++){
		switch(copy_format[i]){
			case 'u','U','p','P':{
				if(paramn(j))return false;
				gcmd_IsInt(IsInt,j);
				if(IsInt && IsPlayerConnected(strval(gcs_n_gcmd_param[j][e_gcmd_param_string]))) 
					copy_format[i] = e_gcmd_param_data_integer;
				else return false;
			}
			case 's','S','z','Z':{
				if(paramn(j)) return false;
				copy_format[i] = e_gcmd_param_data_string;
			}
			case 'i','I','d','D':{
				if(paramn(j)) return false;
				gcmd_IsInt(IsInt,j);
				if(IsInt) copy_format[i] = e_gcmd_param_data_integer;
				else return false;
			}
			case 'f','F':{
				if(paramn(j)) return false;
				gcmd_IsFloat(IsFloat,j);
				if(IsFloat) copy_format[i] = e_gcmd_param_data_float;
				else return false;
			}
			default:{
				copy_format[i] = e_gcmd_param_data_none;
			}
		}
	}
	for(new k;k < i;k++){
		switch(copy_format[k]){
			case e_gcmd_param_data_integer:{
				gcmd_integerparam((k+1));
			}
			case e_gcmd_param_data_float:{
				gcmd_floatparam((k+1));
			}
		}
	}
	return true;
}

/**
*/
stock gcmd_EmptyPos(){
	if(gcs_s_gcmd_Amount >= MAX_CMD)return INVALID_CMD_ID;
	for(new i;i < MAX_CMD;i++){
		if(gcs_s_gcmd[i][e_gcmd_string_pos] == INVALID_CMD_COMMANDPOOL){
			return i;
		}
	}
	return INVALID_CMD_ID;
}

/**
*/
stock gcmd_EmptyPool(){
	for(new i;i < MAX_CMD;i++){
		if(!gcs_s_gcmd_commandpool[i][0])return i;
	}
	return INVALID_CMD_COMMANDPOOL;
}

/**
*/
stock gcmd_EmptySort(){
	for(new i,j = sizeof gcs_s_gcmd_sort_pos;i < j;i++){
		if(gcs_s_gcmd_sort_pos[i] == INVALID_CMD_ID){
			return i;
		}
	}
	return INVALID_CMD_ID;
}

/**
Func:gcmd_create(const cmd_identify[],{Float,_}:...)

Note:
	Add command to the system
*/
stock gcmd_create(const cmd_identify[],{Float,_}:...){
	if(gcs_s_gcmd_Amount > MAX_CMD)return false;
	for(new i;cmd_identify[i];i++){
		if(!(
			(cmd_identify[i] >= 'a' && cmd_identify[i] <= 'z' ) || 
			(cmd_identify[i] >= 'A' && cmd_identify[i] <= 'Z') ||
			(cmd_identify[i] == '_') ||
			(cmd_identify[i] >= '0' && cmd_identify[i] <= '9')
			)
		){
			printf "[gcmd]%s create failed,illegal symbol(Only a-z,A-Z,0-9 and _ is legal)",cmd_identify
			return false;
		}
	}
	new 
		id = gcmd_EmptyPos(),
		argAmount = numargs()-1,
		pos;
	gcs_s_gcmd[id][e_gcmd_string_pos] = gcmd_EmptyPool();
	pos = gcs_s_gcmd[id][e_gcmd_string_pos];
	if(id == INVALID_CMD_ID || pos == INVALID_CMD_COMMANDPOOL){
		printf "[gcmd]%s create failed,overflow.",cmd_identify
		return false;
	}
	if(argAmount > 10){
		printf "[gcmd]%s create failed,too much commands(%d)",cmd_identify,argAmount
		return false;
	}
	gcs_s_gcmd[id][e_gcmd_string_len][0] = strlen(cmd_identify);
	gcs_s_gcmd[id][e_gcmd_string_sign][0] = gcmd_getStrSign(cmd_identify);
	gcmd_replace(gcs_s_gcmd_commandpool[pos],cmd_identify,0,strlen(cmd_identify));
	new
		argPos = 1,
		argStrPos,
		argStr[MAX_STRING];
	for(new i ;i < MAX_CMD_COMMANDS && argAmount;i++,argPos++,argAmount--){
		getFunctionArgAsString(argStr,argPos,argStrPos);
		gcmd_replace(
			gcs_s_gcmd_commandpool[pos],
			argStr,
			((MAX_CMD_IDENTIFY_LENGTH+2)+i*(MAX_CMD_COMMAND_LENGTH+2)),
			(((MAX_CMD_IDENTIFY_LENGTH+2)+i*(MAX_CMD_COMMAND_LENGTH+2))+strlen(argStr))
		);
		gcs_s_gcmd[id][e_gcmd_string_len][i+1] = strlen(argStr);
		gcs_s_gcmd[id][e_gcmd_string_sign][i+1] = gcmd_getStrSign(argStr);
	}
	for(new i;i<MAX_PLAYERS;i++) gcs_s_gcmd[id][e_gcmd_pAbleUse][i] = true;
	gcs_s_gcmd_sort_pos[gcmd_EmptySort()] = pos;
	gcs_s_gcmd_Amount++;
	
	
	new output[MAX_STRING];
	new poss;
	for(new i,j = strlen(gcs_s_gcmd_commandpool[pos])-1;i <= j;i++){
		if(i == j){
			gcs_s_gcmd_commandpool[pos][j-1] = '\0';
			break;
		}
		if(gcs_s_gcmd_commandpool[pos][i] == ' '){
			if(gcs_s_gcmd_commandpool[pos][i+1] != ' '){
				output[poss++] = ' ';
				continue;
			}
		}else output[poss++] = gcs_s_gcmd_commandpool[pos][i];
	}
	output[poss] = '\0';
	printf "[gcmd]%d,%s",gcs_s_gcmd_Amount,output
				
		
	return true;
}


/**
Func:gcmd_delete(const cmd_identify[])

Note:
	Remove command from the system
*/
stock gcmd_delete(const cmd_identify[]){
	new
		len = strlen(cmd_identify);
	for(new i,j = sizeof gcs_s_gcmd_sort_pos;i < j;i++){
		if(
			gcmd_equal(
				gcs_s_gcmd_commandpool[gcs_s_gcmd[gcs_s_gcmd_sort_pos[i]][e_gcmd_string_pos]],
				cmd_identify,0,len,0,len
			)
		){
			gcs_s_gcmd_commandpool[gcs_s_gcmd[gcs_s_gcmd_sort_pos[i]][e_gcmd_string_pos]][0] = '\0';
			for(new k = 1;gcs_s_gcmd_commandpool[gcs_s_gcmd[gcs_s_gcmd_sort_pos[i]][e_gcmd_string_pos]][k];k++){
				gcs_s_gcmd_commandpool[gcs_s_gcmd[gcs_s_gcmd_sort_pos[i]][e_gcmd_string_pos]][k] = ' ';
			}
			gcs_s_gcmd[gcs_s_gcmd_sort_pos[i]][e_gcmd_string_pos] = INVALID_CMD_COMMANDPOOL;
			gcs_s_gcmd_sort_pos[i] = INVALID_CMD_ID;
			gcs_s_gcmd_Amount--;
			return true;
		}
	}
	return false;
}

/**
*/
stock gcmd_setPlayerAbleUse(playerid,const cmd_identify[],bool:enable){
	for(new i,j = strlen(cmd_identify);i < MAX_CMD;i++){
		if(
			gcs_s_gcmd[i][e_gcmd_string_len][0] == j &&
			gcmd_equal(gcs_s_gcmd_commandpool[gcs_s_gcmd[i][e_gcmd_string_pos]],cmd_identify,0,j,0,j)
		){
			if(playerid == INVALID_PLAYER_ID){
				for(new k; k < MAX_PLAYERS;k++){
					gcs_s_gcmd[i][e_gcmd_pAbleUse][k] = enable;
				}
			}else gcs_s_gcmd[i][e_gcmd_pAbleUse][playerid] = enable;
			return true;
		}
	}
	return false;
}

/**
*/
stock gcmd_getCommand(const cmd_identify[],retstr[]){//Low efficency,TODO
	for(new i,len = strlen(cmd_identify);i < MAX_CMD;i++){
		if(
			gcs_s_gcmd[i][e_gcmd_string_pos] != INVALID_CMD_COMMANDPOOL &&
			gcs_s_gcmd[i][e_gcmd_string_len][0] == len &&
			!strcmp(
				gcs_s_gcmd_commandpool[gcs_s_gcmd[i][e_gcmd_string_pos]],
				cmd_identify,false,len
			)
		){
			new pos = gcs_s_gcmd[i][e_gcmd_string_pos];
			new poss;
			for(i = 0;gcs_s_gcmd_commandpool[pos][i];i++){
				//printf "%c,%d,%d,%d",gcs_s_gcmd_commandpool[pos][i],len,i,poss
				if(gcs_s_gcmd_commandpool[pos][i] == ' '){
					if(gcs_s_gcmd_commandpool[pos][i+1] && gcs_s_gcmd_commandpool[pos][i+1] != ' '){
						retstr[poss++] = ' ';
						continue;
					}
				}else{
					retstr[poss++] = gcs_s_gcmd_commandpool[pos][i];
				}
			}
			retstr[poss] = '\0';
			return true;
		}
	}
	return false;
}



gcmd_OnPlayerCommandText(){
	//if(!gcs_n_gcmd_lasttext[0])return false;
	new i,j,k;
	
	//get maincmd len&sign&text
	for(i = 0,gcs_n_gcmd_lasttextsign = 0;(gcs_n_gcmd_lasttext[i]) && gcs_n_gcmd_lasttext[i] != ' ';i++){
		gcs_n_gcmd_param[0][e_gcmd_param_string][i] = gcs_n_gcmd_lasttext[i];
		gcs_n_gcmd_lasttextsign += gcs_n_gcmd_lasttext[i];
	}
	gcs_n_gcmd_param[0][e_gcmd_param_string][i] = '\0';
	gcs_n_gcmd_lasttextlen = i;

	//start to check if is right command(s)----
	new cmdid;
	//i = 1;
	for(i=0,j=1,k=gcs_s_gcmd_Amount;i < k;j++){
	/*
	if(gcs_n_gcmd_lasttext[0]){
		printf "%d,%d,%d",gcs_n_gcmd_lasttext
		i++;
		continue;
		//return false;
	}		
	*/
		//cmdid = i;
		if(gcs_s_gcmd_sort_pos[i] == INVALID_CMD_ID){
			i++;
			continue;
		}
		cmdid = gcs_s_gcmd_sort_pos[i];
		//l = ((MAX_CMD_IDENTIFY_LENGTH+2)+(j-1)*(MAX_CMD_COMMAND_LENGTH+2));
		if(!gcs_s_gcmd[cmdid][e_gcmd_string_len][j]){
			j = 0;
			i++;
		}else if(
			(gcs_s_gcmd[cmdid][e_gcmd_string_sign][j] == gcs_n_gcmd_lasttextsign) && 
			(gcs_s_gcmd[cmdid][e_gcmd_string_len][j] == gcs_n_gcmd_lasttextlen) &&
			gcmd_equal(
				gcs_s_gcmd_commandpool[gcs_s_gcmd[cmdid][e_gcmd_string_pos]],
				gcs_n_gcmd_param[0][e_gcmd_param_string],
				((MAX_CMD_IDENTIFY_LENGTH+2)+(j-1)*(MAX_CMD_COMMAND_LENGTH+2)),
				gcs_n_gcmd_lasttextlen+((MAX_CMD_IDENTIFY_LENGTH+2)+(j-1)*(MAX_CMD_COMMAND_LENGTH+2)),
				0,gcs_n_gcmd_lasttextlen
			)
			
		){//if player type this command(all variable can use now)
			if(gcs_s_gcmd[cmdid][e_gcmd_pAbleUse][gcs_n_gcmd_lastplayer]){
				//sort pos to improve speed(This function aren't efficent,so dont sort frequently)
				gcs_s_gcmd[cmdid][e_gcmd_usetimes]++;
				if(gcs_s_gcmd_usetimes++ >= MAX_CMD_SORT_TIMES){
					new
						tmpval[MAX_CMD];
					gcs_s_gcmd_usetimes = 0;
					for(i = 0;i < MAX_CMD;i++){
						tmpval[i] = gcs_s_gcmd[i][e_gcmd_usetimes];
						gcs_s_gcmd[i][e_gcmd_usetimes] = 0;
					}
					gcmd_SortArray(gcs_s_gcmd_sort_pos,tmpval);
				}
				
				//struction
				gcs_n_gcmd_lastparamamount = 0;
				//gcs_n_gcmd_lastplayer = playerid;
				for(i = 0;i<MAX_PARAM_AMOUNT;i++){
					gcs_n_gcmd_param[i][e_gcmd_param_string][0] = '\0';
					gcs_n_gcmd_param[i][e_gcmd_param_float] = 0.0;
					gcs_n_gcmd_param[i][e_gcmd_param_integer] = 0;
					gcs_n_gcmd_param[i][e_gcmd_param_floated] = false;
					gcs_n_gcmd_param[i][e_gcmd_param_integered] = false;
				}
				
				//create params which are splited by white space(low efficent)
				new bool:t,l;
				i = 0,j = 0,k = 0,l = 0;
				while(
					(gcs_n_gcmd_param[j][e_gcmd_param_string][k++] = gcs_n_gcmd_lasttext[i]) &&
					l < MAX_PARAM_AMOUNT
				){
					if(gcs_n_gcmd_lasttext[i++] == ' '){
						gcs_n_gcmd_lastparamamount++;
						gcs_n_gcmd_param[j++][e_gcmd_param_string][k-1] = '\0';
						l++;
						t = true;
						k = 0;
					}
				}
				if(t) gcs_n_gcmd_lastparamamount++;
				
				//Call function
				new
					tmpstr[MAX_CMD_IDENTIFY_LENGTH+10];
				format(
					tmpstr,MAX_CMD_IDENTIFY_LENGTH+10,"ggcmd_%s",
					gcmd_split(
						gcs_s_gcmd_commandpool[gcs_s_gcmd[cmdid][e_gcmd_string_pos]],
						0,strfind(gcs_s_gcmd_commandpool[gcs_s_gcmd[cmdid][e_gcmd_string_pos]]," ")-1
					)
				);
				if(gcs_n_gcmd_param[1][e_gcmd_param_string][0]){
					CallRemoteFunction(tmpstr,"is",gcs_n_gcmd_lastplayer,gcs_n_gcmd_lasttext[gcs_n_gcmd_lasttextlen+1]);
					return true;
				}else{
					CallRemoteFunction tmpstr,"i",gcs_n_gcmd_lastplayer
					return true;
				}
			}else return false;
		}
	}
	return false;
}




#define gcmd_process() \
	new gcmdj; \
	for(new gcmdi = 1;cmdtext[gcmdi];gcmdi++) \
		if((cmdtext[gcmdi] == ' ' && cmdtext[gcmdi+1] == ' ')) continue; \
		else gcs_n_gcmd_lasttext[gcmdj++] = cmdtext[gcmdi]; \
	gcs_n_gcmd_lasttext[gcmdj] = '\0'; \
	gcs_n_gcmd_lastplayer = playerid; \
	if(gcmdj && gcmd_OnPlayerCommandText())return true
	

gcmd_struction(){
	for(new i;i<MAX_CMD;i++){
		gcs_s_gcmd[i][e_gcmd_string_pos] = INVALID_CMD_COMMANDPOOL;
		gcs_s_gcmd_sort_pos[i] = INVALID_CMD_ID;
		for(new j = 1,k = sizeof(gcs_s_gcmd_commandpool[]); j < k;j++){
			gcs_s_gcmd_commandpool[i][j] = ' ';
		}
	}
}
#endif








//EOF