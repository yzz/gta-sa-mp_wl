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


#if defined _gcs_streamer_object_included
	#endinput
#endif
#define _gcs_streamer_object_included
#pragma library gcs_streamer_object



#define MAX_OBJECTS				(3000)
#define OBJECT_DISTANCE			(220)
#define MAX_DYM_OBJECTS			(240)
#define INVALID_DYM_OBJECT_ID	(-1)


enum e_gcs_object{
	e_gcs_object_modelid,
	Float:e_gcs_object_ox,
	Float:e_gcs_object_oy,
	Float:e_gcs_object_oz,
	Float:e_gcs_object_rx,
	Float:e_gcs_object_ry,
	Float:e_gcs_object_rz
}

static
	gcs_objects[MAX_OBJECTS][e_gcs_object],
	gcs_objAmount;

stock gcs_obj_GetUnusedSlot(){
	new
		objAmount = -1;
	for(new i;i < MAX_OBJECTS;i++){
		if(!gcs_objects[i][e_gcs_object_modelid]){
			objAmount = i;
		}
	}
	if(objAmount == -1){
		print("Warning:Objects overload");
		SendClientMessageToAll(0,"Warning:Objects overload");
		return MAX_OBJECTS-1;
	}
	return objAmount;
}
	
stock gcs_obj_Create(om,Float:ox,Float:oy,Float:oz,Float:rx,Float:ry,Float:rz){
	new
		id = gcs_obj_GetUnusedSlot();
	gcs_objects[id][om] = om;
	gcs_objects[id][ox] = ox;
	gcs_objects[id][oy] = oy;
	gcs_objects[id][oz] = oz;
	gcs_objects[id][rx] = rx;
	gcs_objects[id][ry] = ry;
	gcs_objects[id][rz] = rz;
	return id;
}

forward gcs_obj_Stream();
public gcs_obj_Stream(){
	new
		tmpval[36]，
		Float:cx,Float:cy,Float:cz,
		objid,
		Float:distance
	for(new playerid;playerid < MAX_PLAYERS;playerid++){
		if(IsPlayerConnected(playerid)){
			GetPlayerCameraPos(playerid,cx,cy,cz);
			for(new i;i < MAX_DYM_OBJECTS;i++){
				format(tmpval,sizeof(tmpval),"gcs_obj_oid_%d",i);
				objid = GetPVarInt(playerid,tmpval);
				if(objid != INVALID_DYM_OBJ_ID){
					distance = getDisBetweenPoints(cx,cy,cz,gcs_objects[id][ox],gcs_objects[id][oy],gcs_objects[id][oz]);
					
				}





gcs_obj_playerConnect(playerid){
	new
		tmpval[36];
	for(new i;i < MAX_DYM_OBJECTS;i++){
		format(tmpval,sizeof(tmpval),"gcs_obj_oid_%d",i);
		SetPVarInt(playerid,tmpval,INVALID_DYM_OBJECT_ID);
	}
}









