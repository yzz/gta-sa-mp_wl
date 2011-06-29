



#define loop_player(%1,%2) \
	for(new %2;(%2) < MAX_PLAYERS;%2++) \
		if(IsPlayerConnected((%2)) && GetPlayerVirtualWorld((%2)) == (%1))
		
#define loop_vehicle(%1,%2) \
	for(new %2;(%2) < MAX_VEHICLES;%2++) \
		if(GetVehicleModel((%2)) && GetVehicleVirtualWorld((%2)) == (%1))

#define loop(%1,%2,%3) \
	loop_%1(%2,%3)
	
	
new stock
	ssstr[128];
#define vw_send(%1,%2,%3,%4) \
	format(ssstr,128,(%3),%4); \
	loop(plr,(%1),ii) \
		SendClientMessage(ii,(%2),ssstr)





stock createVehicle(vModel,Float:vx, Float:vy, Float:vz,vi,vvw){
	new
		vid;
	vid = CreateVehicle(vModel,x,y,z,0,0,0,-1);
	SetVehicleVirtualWorld(vid,vvw);
	LinkVehicleToInterior(vid,vi);
	return vid;
}

stock setWeather(weatherid,virtualworld){
	loop(player,virtualworld,i){
		SetPlayerWeather(i,weatherid);
	}
}

process_vwText(playerid,text[]){
	vw_send(GetPlayerVirtualWorld(playerid),GetPlayerColor(playerid),"%s(%d):%s",pName(playerid),playerid,text);
	return true;
}

