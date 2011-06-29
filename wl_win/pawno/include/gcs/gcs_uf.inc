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



#include <a_samp>
#if defined gcs_uf
	#endinput
#endif
#define gcs_uf

/*
const DarkGray = 0xa9a9a900;
const Silver = 0xc0c0c000;
const LightGray = 0xd3d3d300;
const Gainsboro = 0xdcdcdc00;
const LightSlateGray = 0x77889900;
const SlateGray = 0x70809000;
const LightSteelBlue = 0xb0c4de00;
const SteelBlue = 0x4682b400;
const RoyalBlue = 0x4169e100;
const MidnightBlue = 0x19197000;
const Navy = 0x00008000;
const DarkBlue = 0x00008b00;
const MediumBlue = 0x0000cd00;
const Blue = 0x0000ff00;
const DodgerBlue = 0x1e90ff00;
const CornflowerBlue = 0x6495ed00;
const DeepSkyBlue = 0x00bfff00;
const LightSkyBlue = 0x87cefa00;
const SkyBlue = 0x87ceeb00;
const LightBlue = 0xadd8e600;
const PowderBlue = 0xb0e0e600;
const PaleTurquoise = 0xafeeee00;
const Cyan = 0x00ffff00;
const Aqua = 0x00ffff00;
const Turquoise = 0x40e0d000;
const MediumTurquoise = 0x48d1cc00;
const DarkTurquoise = 0x00ced100;
const LightSeaGreen = 0x20b2aa00;
const CadetBlue = 0x5f9ea000;
const DarkCyan = 0x008b8b00;
const Teal = 0x00808000;
const SeaGreen = 0x2e8b5700;
const DarkOliveGreen = 0x556b2f00;
const DarkGreen = 0x00640000;
const Green = 0x00800000;
const ForestGreen = 0x228b2200;
const MediumSeaGreen = 0x3cb37100;
const DarkSeaGreen = 0x8fbc8f00;
const MediumAquamarine = 0x66cdaa00;
const Aquamarine = 0x7fffd400;
const PaleGreen = 0x98fb9800;
const LightGreen = 0x90ee9000;
const SpringGreen = 0x00ff7f00;
const MediumSpringGreen = 0x00fa9a00;
const LawnGreen = 0x7cfc0000;
const Chartreuse = 0x7fff0000;
const GreenYellow = 0xadff2f00;
const Lime = 0x00ff0000;
const LimeGreen = 0x32cd3200;
const YellowGreen = 0x9acd3200;
const OliveDrab = 0x6b8e2300;
const Olive = 0x80800000;
const DarkKhaki = 0xbdb76b00;
const PaleGoldenrod = 0xeee8aa00;
const Cornsilk = 0xfff8dc00;
const Beige = 0xf5f5dc00;
const LightYellow = 0xffffe000;
const Lightgoldenrodyellow = 0xfafad200;
const LemonChiffon = 0xfffacd00;
const Wheat = 0xf5deb3;
const Burlywood = 0xdeb88700;
const Tan = 0xd2b48c00;
const Khaki = 0xf0e68c00;
const Yellow = 0xffff0000;
const Gold = 0xffd70000;
const Orange = 0xffa50000;
const SandyBrown = 0xf4a46000;
const DarkOrange = 0xff8c0000;
const Goldenrod = 0xdaa52000;
const Peru = 0xcd863f00;
const DarkGoldenrod = 0xb8860b00;
const Chocolate = 0xd2691e00;
const Sienna = 0xa0522d00;
const SaddleBrown = 0x8b451300;
const Maroon = 0x80000000;
const DarkRed = 0x8b000000;
const Brown = 0xa52a2a00;
const Firebrick = 0xb2222200;
const IndianRed = 0xcd5c5c00;
const RosyBrown = 0xbc8f8f00;
const DarkSalmon = 0xe9967a00;
const LightCoral = 0xf0808000;
const Salmon = 0xfa807200;
const LightSalmon = 0xffa07a00;
const Coral = 0xff775000;
const Tomato = 0xff634700;
const OrangeRed = 0xff450000;
const Red = 0xff000000;
const Crimson = 0xdc143c00;
const MediumVioletRed = 0xc7158500;
const DeepPink = 0xff149300;
const HotPink = 0xff69b400;
const PaleVioletPink = 0xdb709300;
const Pink = 0xffc0cb00;
const LightPink = 0xffb6c100;
const Thistle = 0xd8bfd800;
const Magenda = 0xff00ff00;
const Fuchsia = 0xff00ff00;
const Violet = 0xee82ee00;
const Plum = 0xdda0dd00;
const Orchid = 0xda70d600;
const MediumOrchid = 0xba55d300;
const DarkOrchid = 0x9932cc00;
const DarkViolet = 0x9400d300;
const DarkMagenda = 0x8b008b00;
const Purple = 0x80008000;
const Indigo = 0x4b008200;
const DarkSlateBlue = 0x483d8b;
const BlueViolet = 0x8a2be200;
const MediumPurple = 0x9370db00;
const SlateBlue = 0x6a70db00;
const MediumSlateBlue = 0x7b68ee00;
const Brass = 0xb5a64200;
const CoolCopper = 0xd9871900;
const Copper = 0xbf00df00;
const CornFlower = 0xbfefdf00;
const DarkBrown = 0xda0b0000;
const Feldsper = 0xfed0e000;
const RichBlue = 0x0cb0e000;
const Mouse = 0x99999900;
*/
//Support un-utf8.by GCS Team
stock gini_fwrite(File:handle,const string[]){
	new i;
	for(i = 0;string[i];i++){
		fputchar(handle, string[i],false);
	}
	//fputchar(handle,'\0',false);
	return true;
}



/**
 *  Strips Newline from the end of a string.
 *  Idea: Y_Less, Bugfixing (when length=1) by DracoBlue
 *  @param   string
 */
stock stripNewLine(string[]){
	new len = strlen(string);
	if (string[0]==0) return ;
	if ((string[len - 1] == '\n') || (string[len - 1] == '\r')) {
		string[len - 1] = 0;
		if (string[0]==0) return ;
		if ((string[len - 2] == '\n') || (string[len - 2] == '\r')) string[len - 2] = 0;
	}
}

/*----------------------------------------------------------------------------*-
By: Alex - Y_less
Function:
	strconcat
Params:
	...
Return:
	All passed strings concatenated.
Notes:
	-
-*----------------------------------------------------------------------------*/

stock strconcat(str1[], str2[]){
	new
		str[128],
		c,
		i,
		j;
	while ((c = str1[i++])) str[j++] = c;
	i = 0;
	while ((c = str2[i++])) str[j++] = c;
	str[j] = '\0';
	return str;
}
/**====================================================
Date:2009/5/23
Author:Nero_3D - 10
Description:
	methode = 0--> big to small
	methode = 1--> small to big
Note:
	syntax edit by GCS Team
==================================================*/

stock SortArray(array[],source[],methode = 0,a_size = sizeof array,s_size = sizeof source){
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
/**====================================================
Date:2009/8/5
Author:Orginal in pawn-lang.pdf
Describe:...
==========================================*/
stock strtok(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}

//------------------------------------------------

stock strrest(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}
	new offset = index;
	new result[128];
	while ((index < length) && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}

//----------------------------------------------------------

/**====================================================
Date:2009/12/19
Author:Andre9977 
Describe:check a vehicle type
==========================================*/
stock IsCopCar(carid)
{
    new Operative[] = { 523, 427, 490, 528, 596, 597, 598, 599 };
    for(new i = 0; i < sizeof(Operative); i++)
    {
		if(GetVehicleModel(carid) == Operative[i]) return 1;
    }
    return 0;
}

stock IsBike(carid)
{
    new Bikes[] = { 509, 481, 510 };
    for(new i = 0; i < sizeof(Bikes); i++)
    {
        if(GetVehicleModel(carid) == Bikes[i]) return 1;
    }
    return 0;
}

stock IsMotorBike(carid)
{
    new MotorBikes[] = { 581, 462, 521, 463, 522, 523, 461, 448, 471, 468, 586 };
    for(new i = 0; i < sizeof(MotorBikes); i++)
    {
        if(GetVehicleModel(carid) == MotorBikes[i]) return 1;
    }
    return 0;
}

stock IsAirVehicle(carid)
{
    new AirVeh[] = { 592, 577, 511, 512, 593, 520, 553, 476, 519, 460, 513, 548, 425, 417, 487, 488, 497, 563, 447, 469 };
    for(new i = 0; i < sizeof(AirVeh); i++)
    {
        if(GetVehicleModel(carid) == AirVeh[i]) return 1;
    }
    return 0;
}

stock IsABoat(carid)
{
    new Boats[] = { 472, 473, 493, 495, 484, 430, 454, 453, 452, 446 };
    for(new i = 0; i < sizeof(Boats); i++)
    {
if(GetVehicleModel(carid) == Boats[i]) return 1;
    }
    return 0;
}
//----------------------------------------------------------

/**====================================================
Date:2009/5/14
Author:unknown
Describe:check a string if is integer|float
==========================================*/
stock IsNumeric(const string[]){
	for (new i = 0;string[i]; i++){
		if (string[i] > '9' || string[i] < '0'){
			return false;
		}
	}
	return true;
}

stock IsFloatric(const string[]){
	for(new i,j;string[i];i++){
		if((string[i] > '9' || string[i] < '0')){
			if(string[i] == '.'){
				if(j) return false;
				else j = true;
			}else return false;
		}
	}
	return true;
}

stock IsSTDStr(const str[]){
	
	for(new i;str[i];i++){
		if( 
			!( \
			(str[i] >= 'a' && str[i] <= 'z') || \
			(str[i] >= 'A' && str[i] <= 'Z') || \
			(str[i] >= '0' && str[i] <= '9') || \
			(str[i] == '_') \
			)
		) return false;
	}
	
	return true;
}




/**=====================================================
*Date:2009/5/3
*Author:GCS Team
*Describe:Get x,y infront
=======================================================*/

stock Float:getBackfrontXY(&Float:x,&Float:y,Float:a,Float:distance){
	new
		Float:tmpx=x,
		Float:tmpy=y;
	x = tmpx-(distance * floatsin(-a, degrees));
	y = tmpy-(distance * floatcos(-a, degrees));
}

/**=====================================================
*Date:2009/5/3
*Author:GCS Team
*Describe:Get x,y infront
=======================================================*/
stock Float:getInfrontXY(&Float:x,&Float:y,Float:a,Float:distance){
	new
		Float:tmpx=x,
		Float:tmpy=y;
	x = tmpx+(distance * floatsin(-a, degrees));
	y = tmpy+(distance * floatcos(-a, degrees));
}
/**=====================================================
*Date:2009/5/3
*Author:many guys
*Describe:Get x,y infront of player
=======================================================*/
stock Float:getPlayerInfrontXY(playerid, &Float:x, &Float:y, Float:distance){
	new Float:a;
	GetPlayerPos(playerid, x, y, a);
	if (IsPlayerInAnyVehicle(playerid)) GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
	else GetPlayerFacingAngle(playerid, a);
	x += (distance * floatsin(-a, degrees));
	y += (distance * floatcos(-a, degrees));
	return a;
}
/**======================================================
*Date:2009/5/2
*Author:GCS Team
*Name:abort
*Describe:to abort server(crash server)
========================================================*/
stock abort(){
	print("Server aborting...");
	SendClientMessageToAll(0,"Server abort.");
	for(new i;i<MAX_PLAYERS;i++){
		OnPlayerDisconnect(i,0);
	}
	print("Server abort.");
	OnGameModeExit();
	SendClientMessageToAll(0,"");
}
/**=======================================================
*Date:2009/4/24
*Author:GCS Team
*Name:getargAsString
*Params:
*  argString,argPos,Pos
*Describe: get arg as string
========================================================*/
#define getargAsString(%0,%1,%2) \
	(%2) = 0; \
	while((%0[(%2)] = getarg((%1),(%2)))) (%2)++
/**=======================================================
*Date:2009/4/25
*Author:GCS Team
*Name:setargAsString
*Params:
*  argString,argPos,Pos
*Describe: set arg as string
========================================================*/	
#define setargAsString(%0,%1,%2) \
	(%2) = 0; \
	while((%0[(%2)]) && setarg((%1),(%2),(%0[(%2)]))) (%2)++

/**======================================================
*Date:2009/4/6
*Name:KillPlayer
*Author:Too many guys...
*Describe:kill player
=======================================================*/
stock KillPlayer(playerid){
	SetPlayerHealth(playerid,0);
}
#define kill(%1) \
	SetPlayerHealth((%1),0)


/**======================================================
*Date:2009/3/21
*Name:remindPlayerText
*Author:Gcs Team
*Describe:remind a player with some text while using sound
=======================================================*/
//======================================================

#define remindPlayerText(%1,%2,%3) do{ \
	new \
		sendformatstring1[MAX_STRING], \
		sendformatstring2[MAX_STRING]; \
	format(sendformatstring1,sizeof(sendformatstring1),(%2),%3); \ 
	format(sendformatstring2,sizeof(sendformatstring2),"~n~~n~~n~~n~~n~~n~~n~~n~~n~%s",sendformatstring1); \
	GameTextForPlayer((%1),sendformatstring2,3000,3); \
	PlayerPlaySound((%1),1057); \
}while(FALSE)
stock remindPlayerText(playerid,const remind_text[]){
	new
		sendformatstring[MAX_STRING];
	format(sendformatstring,sizeof(sendformatstring),"~n~~n~~n~~n~~n~~n~~n~~n~~n~%s",remind_text);
	GameTextForPlayer(playerid,sendformatstring,3000,3);
	PlayerPlaySound(playerid,1057);
	return true;
}
//===========================================================
/**===============================================================
*Date:2009/4/4
*Author:GCS Team
*Name:passString(Ex)
*Describe:
*Due to CallRemoteFunction cannot pass any var by reference,
*decided to make a function to help pass by reference
*
*--:passString_get();
*---:To get the passString;
*--:passString_send(const string[]);
*---:To edit the passString:
*--:params
*---:Globle-->DatapassString[2000]
*----:To save passString
*
*Note:
*Unconvenitent and far far slow....

=================================================================*/
//========================================================================
/*
forward passString_send(const string[]);
static
	DatapassString[2000];

stock passString_get(){
	//printf("passString-->'%s'",DatapassString);
	return DatapassString;
}

public passString_send(const string[]){
	///printf("passString '%s' change to '%s'",DatapassString,string);
	new
		i,
		j = strlen(string);
	while(i<j){
		DatapassString[i] = string[i];
		i++;
	}
	DatapassString[i] = '\0';
	//printf("passString--->'%s'",DatapassString);
	return true;
}
*/
//==================================================================
/**===============================================================
*Date:2009/3/14
*Author:GCS Team
*Name:loopPlayer(Ex)
*Other:IPC(playerid)
*Describe:
*loopPlayer(Player) will loop connected player
*eg:
	loopPlayer(playerid){
		if(GetPlayerState(playerid) == 0){}
	}
*loopPlayerEx(Player) will loop MAX_PLAYERS's
*eg:
	loopPlayerEx(playerid){
		if(IsPlayerConnected(playerid)){}
	}
*IPC(playerid) = IsPlayerConnected(playerid) check player if has connected or not.
*Easy to output and for speed

=================================================================*/
//tag:player loop process

#define loopPlayer(%1) for(new %1 = 0; %1 < MAX_PLAYERS;%1++) if(IsPlayerConnected((%1))) //&& !IsPlayerNPC((%1)))

#define loopPlayerEx(%1) for(new %1 = 0;%1 < MAX_PLAYERS;%1++) //if(!IsPlayerNPC((%1)))


#define IPC(%1) IsPlayerConnected(%1)

#define looper(%1,%2,%3,%4) \
	for(new %1 = (%2);(%1)<(%3);%1++) if(%4)	
//===============================================================
/**===============================================================
*Date:2009/3/14
*Author:GCS Team
*Name:TeleportPlayer(playerid,Float:x,Float:y,Float:z);
*Describe:To teleport player with object load,automatic teleport vehicle too,etc.
*Feel like to avoid falling when loading objects
*Future:Help facing to anti-hack teleport.
=================================================================*/
	
	
stock bool:PlayerTeleporting(playerid){
	if(IPC(playerid) && GetPVarInt(playerid,"gcs_plr_teleporting"))return true;
	return false;
}
forward TeleportPlayer_End(playerid,Float:x,Float:y,Float:z,Float:angle,pinterior,bool:ignoreVec,virtualworld);
stock TeleportPlayer(playerid,Float:x,Float:y,Float:z,Float:angle = -65535.0,pinterior = -20,bool:ignoreVec=false,virtualworld = -20){
	/*
	if(PlayerTeleporting(playerid)){
		SendClientMessage(playerid,0x0000FFAA,"[传送]传送失败,一项传送进行中");
		return false;
	}
	*/
	if(!ignoreVec && GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
		SetVehiclePos(GetPlayerVehicleID(playerid),x,y,z);
		if(angle == -65535.0) GetVehicleZAngle(GetPlayerVehicleID(playerid),angle);
	}
	else{
		SetPlayerPos(playerid,x,y,z);
		if(angle == -65535.0) GetPlayerFacingAngle(playerid,angle);
	}
	if(pinterior == -20) pinterior = GetPlayerInterior(playerid);
	if(virtualworld == -20) virtualworld = GetPlayerVirtualWorld(playerid);
	SetPVarInt(playerid,"gcs_plr_teleporting",true);
	SetTimerEx("TeleportPlayer_End",GetPlayerPing(playerid)*2+1500,false,"iffffiii",playerid,x,y,z,angle,pinterior,ignoreVec,virtualworld);
	return true;
}
public TeleportPlayer_End(playerid,Float:x,Float:y,Float:z,Float:angle,pinterior,bool:ignoreVec,virtualworld){
	if(!ignoreVec && GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
		SetVehicleVirtualWorld(GetPlayerVehicleID(playerid),virtualworld);
		SetVehicleZAngle(GetPlayerVehicleID(playerid),angle);
		SetVehiclePos(GetPlayerVehicleID(playerid),x,y,z);
		LinkVehicleToInterior(GetPlayerVehicleID(playerid),pinterior);
	}else
	{
		SetPlayerVirtualWorld(playerid,virtualworld);
		SetPlayerPos(playerid,x,y,z);
		SetPlayerFacingAngle(playerid,angle);
	}
	if(pinterior != -20)
	SetPlayerInterior(playerid,pinterior);
	PlayerPlaySound(playerid, 1056,0,0,0);
	SetPVarInt(playerid,"gcs_plr_teleporting",false);
	return true;
}

//=========================================================================//
/**===================================================================
*Date:2009/4/10
*Author:Many ppl can do it
*Name:Vec_isValidModel(modelid);
*Describe:To Check if is valid modelid.
=====================================================================*/
#define Vec_isValidModel(%1) \
	((%1) > 400 && (%1) < 600)
	
/**===================================================================
*Date:2009/3/14
*Author:GCS Team
*Name:Vec_isValidNos(vehicleid);
*Describe:To Check if valid to add nos.
=====================================================================*/
static const stock
	gcs_s_uf_Vec_invalidNos[] = {
		581,523,462,521,463,522,461,448,468,586,
		509,481,510,472,473,493,595,484,430,453,
		452,446,454,590,569,537,538,570,449,513,
		520,519,487,417,406,556,444,557
	};
stock Vec_isValidNos(vehicleid){
	for(
		new 
			i,
			amount=sizeof(gcs_s_uf_Vec_invalidNos),
			modelid=GetVehicleModel(vehicleid);
		i<amount;
		i++
	){
		if(modelid == gcs_s_uf_Vec_invalidNos[i])return false;
	}
	return true;
}

//=========================================================================
/**===================================================================
*Date:2009/4/11
*Author:Sandra
*Edit by:GCS Team
*Name:Vec_flip(vecid)
*Describe:Flip player's vehicle
===================================================================*/
stock Vec_flip(vecid){
	new
		Float:vx,Float:vy,Float:vz,Float:va;
	GetVehiclePos(vecid,vx,vy,vz);
	GetVehicleZAngle(vecid,va);
	SetVehiclePos(vecid,vx,vy,vz+0.5);
	SetVehicleZAngle(vecid,va);
	return true;
}
/**===================================================================
*Date:2009/4/11
*Author:Sandra
*Edit by:GCS Team
*Name:Vec_respray(vecid)
*Describe:Respray player's vehicle
===================================================================*/
static
	gcs_uf_resparying;
forward Vec_respray_End(vecid,Float:vec_x,Float:vec_y,Float:vec_z,Float:vec_a);
public Vec_respray_End(vecid,Float:vec_x,Float:vec_y,Float:vec_z,Float:vec_a){
	if(gcs_uf_resparying)return false;
	SetVehiclePos(vecid,vec_x,vec_y,vec_z);
	SetVehicleZAngle(vecid,vec_a);
	gcs_uf_resparying = true;
	return true;
}
stock Vec_respray(vecid){
	new
		Float:vx,Float:vy,Float:vz,Float:va;
	GetVehiclePos(vecid,vx,vy,vz);
	GetVehicleZAngle(vecid,va);
	debug_SetTimerEx("Vec_respray_End",500,false,"iffff",vecid,vx,vy,vz,va);
	SetVehiclePos(vecid, 1024.8990,-1024.7573,31.7264);
	SetVehicleZAngle(vecid, 0);
	gcs_uf_resparying = false;
	return true;
}

/**===================================================================
*Date:2009/3/14
*Author:GCS Team
*Name:Skin_isValid(vehicleid);
*Describe:To Check if is valid skin or not.
=====================================================================*/
static const stock gcs_uf_Skin_inValid[] = {
	0,	3,	4,	5,	6,
	8,	42,	65,	74,	86,
	119,149,208,273,289
};
stock Skin_isValid(skinid){
	if(skinid < 0|| skinid > 299)return false;
	for(
		new 
			i,
			amount=sizeof(gcs_uf_Skin_inValid);
		i<amount;
		i++
	){
		if(skinid == gcs_uf_Skin_inValid[i])return false;
	}
	return true;
}

//=======================================================================





//========================================================
/**======================================================
*Date:2009/3/21
*Author:Gcs Team
*Describe:Check point in area or not
=======================================================*/

stock PointInArea(Float:px,Float:py, Float:minx, Float:miny, Float:maxx, Float:maxy)
{
	if (px > minx && px < maxx && py > miny && py < maxy) return true;
	return false;
}
/**
#define PointInArea(%0,%1,%2,%3,%4,%5) 
	((%0 > %2) && (%0 < %4) && (%1 > %3) && (%1 < %5))
*/
//=====================================================
/**================================================
*Date:2009/10/17
*Author:Boylett  
*Describe:Get distance beetween points.
================================================**/
stock Float:getDisBetweenPoints(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2){
    new 
		Float:x, Float:y, Float:z;
    x = x1-x2;
    y = y1-y2;
    z = z1-z2;
    return floatsqroot(x*x+y*y+z*z);
}
/**======================================================
*Date:2009/12/227
*Author:Too many guys
*Describe:Get distance beetween players
======================================================*/
stock Float:getDisBetweenPlayer(p1,p2){
	new
		Float:p1x,Float:p1y,Float:p1z,
		Float:p2x,Float:p2y,Float:p2z;
	GetPlayerPos(p1,p1x,p1y,p1z);
	GetPlayerPos(p2,p2x,p2y,p2z);
	return getDisBetweenPoints(p1x,p1y,p1z,p2x,p2y,p2z);
}
/**======================================================
*Date:2010/9/12
*Author:
*Description:
=======================================================*/
#define sqlquery_processstart(%1)			new sqlquery[MAX_SQL_STR];format(sqlquery,sizeof(sqlquery),%1)
#define sqlquery_processthengetresult(%1) 	new DBResult:dbr;dbr = db_query((%1),sqlquery)
#define sqlquery_processend()				db_free_result(dbr)
#define sqlquery_processthenfree(%1)		db_free_result(db_query((%1),sqlquery))

#define db_processstart(%1)			new sqlquery[MAX_SQL_STR];format(sqlquery,sizeof(sqlquery),%1)
#define db_processthengetresult(%1) 	new DBResult:dbr;dbr = db_query((%1),sqlquery)
#define db_processend()				db_free_result(dbr)
#define db_processthenfree(%1)		db_free_result(db_query((%1),sqlquery))
#define db_processresulted()		if(db_num_rows(dbr))
#define db_processgetfield(%1,%2)	db_get_field_assoc(dbr,(%1),(%2),sizeof((%2)))
#define db_processgetfieldbyindex(%1,%2)	db_get_field(dbr,(%1),(%2),sizeof((%2)))


/**======================================================
*Date:2009/3/21
*Author:Too many guys
*Describe:Check player in area or not
=======================================================*/
stock PlayerInArea(playerid,Float:minx,Float:miny,Float:maxx,Float:maxy){
	new
		Float:px,
		Float:py,
		Float:pz;
	GetPlayerPos(playerid,px,py,pz);
	return PointInArea(px,py,minx,miny,maxx,maxy);
}
/**=====================================================
*Date:2009/3/21
*Author:yless - Alex
*Describe:far more fast then most Point to point distance
=======================================================*/
#define PointToPoint(%0,%1,%2,%3,%4,%5,%6) \
        (((%0 - %3) * (%0 - %3)) + ((%1 - %4) * (%1 - %4)) + ((%2 - %5) * (%2 - %5)) <= %6 * %6)
//========================================================
//========================================================
/**======================================================
*Date:2009/3/21
*Author:Draco Blue
*Describe:to make coding in CommandText more suitable
=======================================================*/

#define dcmd(%1,%2,%3)            if ((strcmp((%3)[1], #%1, true, (%2)) == 0) && ((((%3)[(%2) + 1] == 0) && (dcmd_%1(playerid, "")))||(((%3)[(%2) + 1] == 32) && (dcmd_%1(playerid, (%3)[(%2) + 2]))))) return 1

//=========================================================

/**======================================================
*Date:2009/3/22
*Author:GCS Team
*Describe:add toggle to use menu
=======================================================*/
stock ShowToggleMenu(Menu:menuid,playerid,bool:toggle = true){
	TogglePlayerControllable(playerid,toggle);
	ShowMenuForPlayer(menuid,playerid);
	return true;
}
//=========================================================

/**======================================================
*Date:2009/3/22
*Author:GCS Team
*Describe:return player's name,far faster than before
=======================================================*/
gcs_uf_OnPlayerConnect_pn(playerid){
	new
		plrName[MAX_PLAYER_NAME];
	GetPlayerName(playerid,plrName,MAX_PLAYER_NAME);
	SetPVarString(playerid,"gcs_plr_name",plrName);
	return true;
}

stock _PlayerName(playerid){
	new
		plrName[MAX_PLAYER_NAME];
	GetPVarString(playerid,"gcs_plr_name",plrName,sizeof(plrName));
	return plrName;
}
//=====================================================
/**======================================================
*Date:2009/3/22
*Author:GCS Team
*Describe:Search player with pattern name
=======================================================*/
stock searchPlayer(playerid,const pattern[]){
	new
		tmpstr[MAX_MSG_STR],
		ppName[MAX_PLAYER_NAME],
		bool:tmpbool;
	loopPlayer(i){
		GetPlayerName(i,ppName,sizeof(ppName));
		if(strfind(ppName,pattern) != -1){
			tmpbool = true;
			format(tmpstr,sizeof tmpstr,"[查找结果]%s(%d)",ppName,i);
			SendClientMessage(playerid,0xEFEFF7AA,tmpstr);
		}
	}
	if(tmpbool) SendClientMessage(playerid,0xEFEFF7AA,"[查找]查找完毕");
	else SendClientMessage(playerid,0xEFEFF7AA,"[查找]没有查找到符合你的搜索内容的");
	return true;
}

/**====================================================== 
*Date:2010/04/04
*Author:GCS Team
*Description:
	Hide/Show the player(marker&nametag)
=======================================================*/
stock HidePlayer(playerid,showplayerid){
	p_setMarkerTransparency(playerid,showplayerid,0);
	ShowPlayerNameTagForPlayer(playerid, showplayerid, false);
}

stock ShowPlayer(playerid,showplayerid,transparency = 128){
	p_setMarkerTransparency(playerid,showplayerid,transparency);
	ShowPlayerNameTagForPlayer(playerid, showplayerid, true);
}


/*----------------------------------------------------------------------------*-
Function:
	hexstr
Params:
	string[] - String to convert to a number.
Return:
	value of the passed hex string.
Notes:
	by y_less
-*----------------------------------------------------------------------------*/

stock hexstr(string[])
{
	new
		ret,
		val,
		i;
	if (string[0] == '0' && (string[1] == 'x' || string[1] == 'X')) i = 2;
	while (string[i])
	{
		ret <<= 4;
		val = string[i++] - '0';
		if (val > 0x09) val -= 0x07;
		if (val > 0x0F) val -= 0x20;
		if (val < 0x01) continue;
		if (val < 0x10) ret += val;
	}
	return ret;
}


/**====================================================== 
*Date:2010/04/04
*Author:GCS Team
*Description:
	Make the players marker transparency to the player while keeping chat colour the same.
	Default is set to 255(non-transparency)
=======================================================*/
stock p_setMarkerTransparency(playerid,showplayerid,transparency = 0){
	if(transparency > 256) transparency = 256;
	else if(transparency < 0) transparency = 0;
	SetPlayerMarkerForPlayer(playerid,showplayerid,transparencyColor(GetPlayerColor(showplayerid),transparency));
}


stock getZoneMidpoint(&Float:midx,&Float:midy,&Float:midz,Float:minx,Float:maxx,Float:miny,Float:maxy,Float:minz,Float:maxz){
	midx = minx+(minx+maxx)/2;
	midy = miny+(miny+maxy)/2;
	midx = minz+(minz+maxz)/2;
}

stock convertSecondToTime(second,&rethour,&retminute,&retsecond){
	rethour = (second/3600)%3600;
	retminute = (second/60)%60;
	retsecond = ((second/1)%60);
}

stock transparencyColor(color,transparency){
	return ((color>>8<<8)+transparency);
}

/**====================================================== 
*Date:2010/10/31
*Author:yzz
*Description: like sleep().
=======================================================*/
stock idle(const time_ms){
	new
		tick = GetTickCount();
	while(GetTickCount() - tick < time_ms){ }
}

/**====================================================== 
*Date:2010/08/28
*Author:GCS Team
*Describe:getDoubleRelationList
=======================================================*/
stock getDoubleRelationList(list1,list2){
	return (((list1+1)*1000)+(list2+1));
}

//limited usage //todo
stock getTrialRelationList(list1,list2,list3){
	return (((list1+1)*1000000)+((list2+1)*1000)+(list3+1));
}


/**====================================================== 
*Date:2009/3/22
*Author:GCS Team
*Describe:get weapon's slotid
=======================================================*/
stock Weapon_getSlotfromID(weaponid){
	switch(weaponid){
		case WEAPON_GOLFCLUB,WEAPON_NITESTICK,WEAPON_KNIFE,WEAPON_BAT,WEAPON_SHOVEL,WEAPON_POOLSTICK,WEAPON_KATANA,WEAPON_CHAINSAW:{
			return 1;
		}
		case WEAPON_COLT45,WEAPON_SILENCED,WEAPON_DEAGLE:{
			return 2;
		}
		case WEAPON_SHOTGUN,WEAPON_SAWEDOFF,WEAPON_SHOTGSPA:{
			return 3;
		}
		case WEAPON_UZI,WEAPON_MP5,WEAPON_TEC9:{
			return 4;
		}
		case WEAPON_AK47,WEAPON_M4:{
			return 5;
		}
		case WEAPON_RIFLE,WEAPON_SNIPER:{
			return 6;
		}
		case WEAPON_ROCKETLAUNCHER,WEAPON_HEATSEEKER,WEAPON_FLAMETHROWER,WEAPON_MINIGUN:{
			return 7;
		}
		case WEAPON_GRENADE,WEAPON_TEARGAS,WEAPON_MOLTOV,WEAPON_SATCHEL:{
			return 8;
		}
		case WEAPON_SPRAYCAN,WEAPON_FIREEXTINGUISHER,WEAPON_CAMERA:{
			return 9;
		}
		case WEAPON_DILDO,WEAPON_DILDO2,WEAPON_VIBRATOR,WEAPON_VIBRATOR2,WEAPON_FLOWER,WEAPON_CANE:{
			return 10;
		}
		case 44,45,WEAPON_PARACHUTE:{//WEAPON_NIGHTVISION,WEAPON_INFRARED
			return 11;
		}
		case WEAPON_BOMB:{
			return 12;
		}
	}
	return 0;
}


stock strcpy(dest[], const source[], numcells = sizeof(source), maxlength = sizeof(dest)){
	new i;
	for(i=0;source[i] && i<numcells && i<maxlength;i++) dest[i] = source[i];
	dest[(i == maxlength) ? (i - 1) : (i)] = '\0';
}


/**


*/
#define HOLDING(%0) \
	((newkeys & (%0)) == (%0))
	
#define PRESSED(%0) \
	(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
	
#define RELEASED(%0) \
	(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))	
	
	
stock fcreate(const filepath[]){
	return fclose(fopen(filepath,io_write));
}
//==============================================
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

stock sscanf(string[], format[], {Float,_}:...){
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
			case 'f':{
				//setarg(paramPos,0,_:floatstr(string[stringPos]))
				new
					changestr[64],
					changepos = 0,
					strpos = stringPos;
				while(changepos < 64 && string[strpos] && string[strpos] != delim){
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
				if (num && IPC(id)){
					setarg(paramPos, 0, id);
				}else{
					#if !defined foreach
						#define foreach(%1,%2) for (new %2 = 0; %2 < MAX_PLAYERS; %2++) if (IPC(%2))
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







gcs_uf_OnPlayerConnect(playerid){
	//gcs_uf_OnPlayerConnect_sort(playerid);
	gcs_uf_OnPlayerConnect_pn(playerid);
}

gcs_uf_OnPlayerDisconnect(playerid,reason){
	#pragma unused playerid,reason
	//gcs_uf_OnPlayerDisconnect_sort(playerid);
	//gcs_uf_OnPlayerDisconnect_pn(playerid);
}



/*
public OnPlayerConnect(playerid){
	gcs_uf_OnPlayerConnect(playerid);
	gcs_uf_pn_Connect(playerid);
	return gu_OnPlayerConnect(playerid);
}
#define OnPlayerConnect(%1) gu_OnPlayerConnect(%1)
forward gu_OnPlayerConnect(playerid);

public OnPlayerDisconnect(playerid,reason){
	gcs_uf_OnPlayerDisConnect(playerid);
	gcs_uf_pn_Disconnect(playerid);
	return gu_OnPlayerDisconnect(playerid,reason);
}
#define OnPlayerDisconnect(%1) gu_OnPlayerDisconnect(%1)
forward gu_OnPlayerDisconnect(playerid,reason);
*/