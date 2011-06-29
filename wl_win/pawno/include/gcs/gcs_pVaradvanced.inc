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




#if defined _gcs_pVaradvanced_included
	#endinput
#endif
#define _gcs_pVaradvanced_included
#pragma library gcs_pVaradvanced

/*
#undef PLAYER_VARTYPE_NONE	
#undef PLAYER_VARTYPE_INT
#undef PLAYER_VARTYPE_STRING
#undef PLAYER_VARTYPE_FLOAT
#define PLAYER_VARTYPE_NONE 	GLOBAL_VARTYPE_NONE
#define PLAYER_VARTYPE_INT 		GLOBAL_VARTYPE_INT
#define PLAYER_VARTYPE_STRING 	GLOBAL_VARTYPE_STRING
#define PLAYER_VARTYPE_FLOAT 	GLOBAL_VARTYPE_FLOAT

static
	g_gcs_PVadv_identify[800][128];
gcs_PVadv_setIdentify(slotid,identify[]){
	format(g_gcs_PVadv_identify[slotid],sizeof(g_gcs_PVadv_identify[]),"%s",identify);
}

gcs_PVadv_idenfity_unusedSlot(){
	for(new i,j = sizeof(g_gcs_PVadv_identify[]);i < j;i++){
		if(g_gcs_PVadv_identify[i][0] == '\0') return i;
	}
	return false;
}
gcs_PVadv_isIdentifyExist(identify[]){
	return (GetGVarType(identify,65535) == GLOBAL_VARTYPE_INT);
}
gcs_PVadv_setIdentifyInGVar(identify[]){
	SetGVarInt(identify,0,65535);
}
gcs_PVadv_removeIdFromGVar(identify[]){
	if(GetGVarType(identify) == GLOBAL_VARTYPE_INT){
		DeleteGVar(identify,65535);
	}
}

gcs_PVadv_storeIdentify(identify[]){
	if(!gcs_PVadv_isIdentifyExist(identify)){
		//printf("add %s",identify);
		gcs_PVadv_setIdentifyInGVar(identify);
		gcs_PVadv_setIdentify(gcs_PVadv_idenfity_unusedSlot(),identify);
	}
}


PVadv_SetPVarInt(playerid,identify[],value){
	SetGVarInt(identify,value,playerid);
	gcs_PVadv_storeIdentify(identify);
}
#define SetPVarInt(%1,%2,%3) PVadv_SetPVarInt(%1,%2,%3)
	
PVadv_SetPVarString(playerid,identify[],value[]){
	SetGVarString(identify,value,playerid);
	gcs_PVadv_storeIdentify(identify);
}
#define SetPVarString(%1,%2,%3) PVadv_SetPVarString(%1,%2,%3)

PVadv_SetPVarFloat(playerid,identify[],Float:value){
	SetGVarFloat(identify,value,playerid);
	gcs_PVadv_storeIdentify(identify);
}
#define SetPVarFloat(%1,%2,%3) PVadv_SetPVarFloat(%1,%2,%3)
//#define SetPVarInt(%1,%2,%3) SetGVarInt(%2,%3,%1)
#define GetPVarInt(%1,%2) GetGVarInt(%2,%1)
//#define SetPVarString(%1,%2,%3) SetGVarString(%2,%3,%1)
#define GetPVarString(%1,%2,%3,%4) GetGVarString(%2,%3,%4,%1)
//#define SetPVarFloat(%1,%2,%3) SetGVarFloat(%2,%3,%1)
#define GetPVarFloat(%1,%2) GetGVarFloat(%2,%1)
#define DeletePVar(%1,%2) DeleteGVar(%2,%1)
#define GetPVarsUpperIndex(%1) GetGVarsUpperIndex(%1)
#define GetPVarNameAtIndex(%1,%2,%3,%4) GetGVarNameAtIndex(%2,%3,%4,%1)
#define GetPVarType(%1,%2) GetGVarType(%2,%1) 


#define pVar_si(%1) SetPVarInt(%1)
#define pVar_gi(%1) GetPVarInt(%1)
#define pVar_ss(%1) SetPVarString(%1)
stock pVar_gs(playerid,varname[]){
	new
		g_pVarString[256];
	GetPVarString(playerid, varname, g_pVarString, sizeof(g_pVarString));
	//printf("str:%s",g_pVarString);
	return g_pVarString;
}	
//#define pVar_gs(%1,%2) GetPVarStringEx(%1,%2)
#define pVar_sf(%1) SetPVarFloat(%1)
#define pVar_gf(%1) GetPVarFloat(%1)
#define pVar_delete(%1) DeletePVar(%1)
#define pVar_exist(%1) GetPVarType(%1)

#define pV_si(%1) SetPVarInt(%1)
#define pV_gi(%1) GetPVarInt(%1)
#define pV_ss(%1) SetPVarString(%1)
stock pV_gs(playerid,varname[]){
	new
		g_pVarString[256];
	GetPVarString(playerid, varname, g_pVarString, sizeof(g_pVarString));
	//printf("str:%s",g_pVarString);
	return g_pVarString;
}	
//#define pV_gs(%1,%2) GetPVarStringEx(%1,%2)
#define pV_sf(%1) SetPVarFloat(%1)
#define pV_gf(%1) GetPVarFloat(%1)
#define pV_delete(%1) DeletePVar(%1)
#define pV_exist(%1) GetPVarType(%1)


PVadv_OnPlayerDisconnect(playerid){
	SetTimerEx("PVadv_plrdisconnect",500,false,"i",playerid);
}

forward PVadv_plrdisconnect(playerid);
public PVadv_plrdisconnect(playerid){
	for(new i,j = sizeof(g_gcs_PVadv_identify[]);i < j;i++){
		if(g_gcs_PVadv_identify[i][0] != '\0'){
			if(gcs_PVadv_isIdentifyExist(g_gcs_PVadv_identify[i])){
				//printf ("remove %s %d",g_gcs_PVadv_identify[i],playerid);
				DeleteGVar(g_gcs_PVadv_identify[i],playerid);
			}
		}
	}
}
*/