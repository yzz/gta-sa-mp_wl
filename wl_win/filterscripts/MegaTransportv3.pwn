//------------------------------------------------------------------------------
//NPC SCRIPT MADY BY FLAKE AND REDIRECT_LEFT
//
//Contains:
//1 beagle driver
//1 coach driver
//1 boat driver
//3 pilots - For LS LV and SF
//
// special thanks to redirect_left for fexing errors :)
//------------------------------------------------------------------------------
//==============================================================================
//edited by yezizhu
#include <a_samp>
#define COLOR_GREEN 0x33AA33AA
new Boat;
new coach,Coach2;
new Beagle;
new Plane1,Plane2,Plane3;
new Taxi1;

public OnGameModeInit()
{
	ConnectNPC("Boater","Boater");
	ConnectNPC("Coach","Coach");
	ConnectNPC("Beagle","Beagle");
	ConnectNPC("Coach2","Coach2");
    ConnectNPC("Taxi1","Taxi1");
	ConnectNPC("Pilot_ymtisd","at400_lv");
	ConnectNPC("Pilot_pip","at400_sf");
	ConnectNPC("Pilot_Flake","at400_ls");


	Boat =	AddStaticVehicle(484,-1988.0057,116.6116,27.6411,0.6686,75,59);
	coach =	AddStaticVehicle(437,-1988.0057,116.6116,27.6411,0.6686,75,59);
	Coach2 = AddStaticVehicle(437,-1988.0057,116.6116,27.6411,0.6686,75,59);
	Beagle = AddStaticVehicle(511,-1988.0057,116.6116,27.6411,0.6686,75,59);
	Plane1 = AddStaticVehicle(577,-1988.0057,116.6116,27.6411,0.6686,75,59);
	Plane2 = AddStaticVehicle(577,-1988.0057,116.6116,27.6411,0.6686,75,59);
	Plane3 = AddStaticVehicle(577,-1988.0057,116.6116,27.6411,0.6686,75,59);
	Taxi1 = AddStaticVehicle(420,-1988.0057,116.6116,27.6411,0.6686,75,59);
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

	print("  Mega Transport Pack Loaded!");
	print("  Made by Memoryz and Flake!"); //Please do not remove this, this is all I ask in return
	return 1;
}

public OnPlayerSpawn(playerid)
{
    if(!IsPlayerNPC(playerid)) return 0;

	new playername[64];
	GetPlayerName(playerid,playername,64);

 	if(!strcmp(playername,"Boater",true)) {
        PutPlayerInVehicle(playerid, Boat, 0);
        SetSpawnInfo(playerid,0,255,1958.33, 1343.12, 15.36, 269.15, 0, 0, 0, 0, 0, 0 );
        new Text3D:boat = Create3DTextLabel("NPC_BoatDriver",0x33AA33AA,30.0,40.0,50.0,40.0,0);
     	Attach3DTextLabelToPlayer(boat, playerid, 0.0, 0.0, 0.5);
		SetPlayerColor(playerid,0xFFFF00AA);
	}
	else if(!strcmp(playername,"Coach",true)) {
	    SetSpawnInfo(playerid,0,255,1958.33, 1343.12, 15.36, 269.15, 0, 0, 0, 0, 0, 0 );
		PutPlayerInVehicle(playerid, coach, 0);
	    new Text3D:Coach = Create3DTextLabel("NPC_BusDriver",0x33AA33AA,30.0,40.0,50.0,40.0,0);
     	Attach3DTextLabelToPlayer(Coach, playerid, 0.0, 0.0, 0.5);
		SetPlayerColor(playerid,0xFFFF00AA);
	}
	else if(!strcmp(playername,"Beagle",true)) {
        SetSpawnInfo(playerid,0,255,1958.33, 1343.12, 15.36, 269.15, 0, 0, 0, 0, 0, 0 );
	    PutPlayerInVehicle(playerid, Beagle, 0);
	    new Text3D:beagle = Create3DTextLabel("NPC_BeagleDriver",0x33AA33AA,30.0,40.0,50.0,40.0,0);
     	Attach3DTextLabelToPlayer(beagle, playerid, 0.0, 0.0, 0.5);
		SetPlayerColor(playerid,0xFFFF00AA);
	}
    else if(!strcmp(playername,"Pilot_ymtisd",true)) {
	    SetSpawnInfo(playerid,0,255,1958.33, 1343.12, 15.36, 269.15, 0, 0, 0, 0, 0, 0 );
   		PutPlayerInVehicle(playerid, Plane1, 0);
   		new Text3D:PTD1 = Create3DTextLabel("NPC_PilotYmtisd",0x33AA33AA,30.0,40.0,50.0,40.0,0);
     	Attach3DTextLabelToPlayer(PTD1, playerid, 0.0, 0.0, 0.5);
		SetPlayerColor(playerid,0xFFFF00AA);
	}
	else if(!strcmp(playername,"Pilot_Flake",true)) {
	    SetSpawnInfo(playerid,0,255,1958.33, 1343.12, 15.36, 269.15, 0, 0, 0, 0, 0, 0 );
	  	PutPlayerInVehicle(playerid, Plane2, 0);
	  	new Text3D:PTD2 = Create3DTextLabel("NPC_PilotFlake",0x33AA33AA,30.0,40.0,50.0,40.0,0);
     	Attach3DTextLabelToPlayer(PTD2, playerid, 0.0, 0.0, 0.5);
		SetPlayerColor(playerid,0xFFFF00AA);
	}
	else if(!strcmp(playername,"Pilot_Pip",true)) {
	    SetSpawnInfo(playerid,0,255,1958.33, 1343.12, 15.36, 269.15, 0, 0, 0, 0, 0, 0 );
   		PutPlayerInVehicle(playerid, Plane3, 0);
   		new Text3D:PTD3 = Create3DTextLabel("NPC_PilotPip",0x33AA33AA,30.0,40.0,50.0,40.0,0);
     	Attach3DTextLabelToPlayer(PTD3, playerid, 0.0, 0.0, 0.5);
		SetPlayerColor(playerid,0xFFFF00AA);
 	}
    else if(!strcmp(playername,"Coach2",true)) {
	    SetSpawnInfo(playerid,0,255,1958.33, 1343.12, 15.36, 269.15, 0, 0, 0, 0, 0, 0 );
		PutPlayerInVehicle(playerid, Coach2, 0);
	    new Text3D:tCoach2 = Create3DTextLabel("NPC_CoachDriver",0x33AA33AA,30.0,40.0,50.0,40.0,0);
     	Attach3DTextLabelToPlayer(tCoach2, playerid, 0.0, 0.0, 0.5);
		SetPlayerColor(playerid,0xFFFF00AA);

	}
	else if(!strcmp(playername,"Taxi1",true)) {
	    SetSpawnInfo(playerid,0,255,1958.33, 1343.12, 15.36, 269.15, 0, 0, 0, 0, 0, 0 );
		PutPlayerInVehicle(playerid, Taxi1, 0);
	    new Text3D:tTaxi1 = Create3DTextLabel("NPC_TaxiDriver",0x33AA33AA,30.0,40.0,50.0,40.0,0);
     	Attach3DTextLabelToPlayer(tTaxi1, playerid, 0.0, 0.0, 0.5);
		SetPlayerColor(playerid,0xFFFF00AA);
	}

    return 1;
}
////////////////////////////////////////////////////////////////////////////////
//End of the script
