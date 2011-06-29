#define FILTERSCRIPT
#include <a_samp>
#pragma tabsize 0
//Dialog style
#define DIALOGID 1338
//Colors
#define COLOR_YELLOW 0xFFFF00AA
#define COLOR_RED 0xAA3333AA
//Variables
static pmodelid[MAX_PLAYERS];
static pvehicleid[MAX_PLAYERS];
//Fowards
forward ModCar(playerid);

#if defined FILTERSCRIPT
////////////////////////////////////////////////////////////////////////////////
public OnPlayerCommandText(playerid, cmdtext[]) {
	if(strcmp(cmdtext, "/tunecar", true) == 0) {
		new playerstate = GetPlayerState(playerid);
		if(playerstate == PLAYER_STATE_DRIVER) {
		    return ModCar(playerid);
		}
		else {
		   return SendClientMessage(playerid, COLOR_RED, "[ERROR]: You must be in a car being the driver.");
		}
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////////////
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == DIALOGID)
	{
		if(response)
		{
			if(listitem == 0) //Paintjobs
			{
				ShowPlayerDialog(playerid, DIALOGID+1, DIALOG_STYLE_LIST, "Select a Paintjob", "Paint Job 1\nPaint Job 2\nPaint Job 3\nBACK", "Select", "Exit");
			}
			if(listitem == 1) //Colors
			{
				ShowPlayerDialog(playerid, DIALOGID+2, DIALOG_STYLE_LIST, "Select a Color", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nBACK", "Select", "Exit");
			}
			if(listitem == 2) //Exhausts
			{
				ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
			}
			if(listitem == 3) //Front Bumpers
			{
				ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
			}
			if(listitem == 4) //Rear Bumpers
			{
				ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
			}
			if(listitem == 5) //Roofs
			{
				ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Select a Roof", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nBACK", "Select", "Exit");
			}
			if(listitem == 6) //Spoilers
			{
				ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Select a Spoiler", "Alien Spoiler\nX-Flow Spoiler\nBACK", "Select", "Exit");
			}
			if(listitem == 7) //SideSkirts
			{
				ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
			}
            if(listitem == 8) //Bullbars
			{
				ShowPlayerDialog(playerid, DIALOGID+9, DIALOG_STYLE_LIST, "Select a Bullbar", "Locos Low Chrome Grill\nLocos Low Chrome Bars\nLocos Low Chrome Lights\nLocos Low Chrome Bullbar\nBACK", "Select", "Exit");
			}
			if(listitem == 9) //Wheels
			{
				ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Select a Wheel type", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nNext Page\nBACK", "Select", "Exit");
			}
			if(listitem == 10) //Car stereo
			{
				ShowPlayerDialog(playerid, DIALOGID+11, DIALOG_STYLE_LIST, "Select a Car Stereo.", "Bass Boost\nSuper Bass Boost\nUltra Bass Boost\nKing Bass Boost\nBACK", "Select", "Exit");
			}
			if(listitem == 11) //Tune car menu 2
			{
				ShowPlayerDialog(playerid, DIALOGID+12, DIALOG_STYLE_LIST, "Tune car menu", "Hydraulics\nNitro x10\nRepair Car\nBACK", "Select", "Exit");
			}
			if(listitem == 12) //Wheels2
			{
				ShowPlayerDialog(playerid, DIALOGID+13, DIALOG_STYLE_LIST, "Select a Wheel type", "Trance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\nBACK", "Select", "Exit");
			}
       }
   }

   if(dialogid == DIALOGID+1) //Paintjobs
   {
		if(response)
		{
			if(listitem == 0)
			{
				if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 560 ||
				pmodelid[playerid] == 575 ||
				pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536 ||
				pmodelid[playerid] == 535 ||
				pmodelid[playerid] == 576 ||
				pmodelid[playerid] == 558)
		        {
					new car = GetPlayerVehicleID(playerid);
					ChangeVehiclePaintjob(car,0);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added paintjob number 1 to the car.");
                    ShowPlayerDialog(playerid, DIALOGID+1, DIALOG_STYLE_LIST, "Select a Paintjob", "Paint Job 1\nPaint Job 2\nPaint Job 3\nBACK", "Select", "Exit");

				}
				else
				{
				   SendClientMessage(playerid,COLOR_RED,"[ERROR]: Paintjob is only for Wheel Arch Angel and Loco Low Co. types of cars!");
			       ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
				}
			}
			if(listitem == 1)
			{
				if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 560 ||
				pmodelid[playerid] == 575 ||
				pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536 ||
				pmodelid[playerid] == 535 ||
				pmodelid[playerid] == 576 ||
				pmodelid[playerid] == 558)
                {
					new car = GetPlayerVehicleID(playerid);
					ChangeVehiclePaintjob(car,1);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added paintjob number 2 to the car.");
                    ShowPlayerDialog(playerid, DIALOGID+1, DIALOG_STYLE_LIST, "Select a Paintjob", "Paint Job 1\nPaint Job 2\nPaint Job 3\nBACK", "Select", "Exit");

				}
				else
				{
				   SendClientMessage(playerid,COLOR_RED,"[ERROR]: Paintjob is only for Wheel Arch Angel and Loco Low Co. types of cars!");
			       ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
				}
			}
			if(listitem == 2)
			{
				if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 560 ||
				pmodelid[playerid] == 575 ||
				pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536 ||
				pmodelid[playerid] == 535 ||
				pmodelid[playerid] == 576 ||
				pmodelid[playerid] == 558)
			    {
			   	   new car = GetPlayerVehicleID(playerid);
                   ChangeVehiclePaintjob(car,2);
                   PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				   SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added paintjob number 3 to the car.");
                   ShowPlayerDialog(playerid, DIALOGID+1, DIALOG_STYLE_LIST, "Select a Paintjob", "Paint Job 1\nPaint Job 2\nPaint Job 3\nBACK", "Select", "Exit");
				}
				else
				{
				   SendClientMessage(playerid,COLOR_RED,"[ERROR]: Paintjob is only for Wheel Arch Angel and Loco Low Co. types of cars!");
			       ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
				}
			}
			if(listitem == 3)
			{
				ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
			}
	   }
   }

   if(dialogid == DIALOGID+2) //Colours
   {
		if(response)
		{
			if(listitem == 0)
			{
		            new car = GetPlayerVehicleID(playerid);
		            ChangeVehicleColor(car,0,0);//Black
		            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You painted your car to black.");
		            ShowPlayerDialog(playerid, DIALOGID+2, DIALOG_STYLE_LIST, "Select a Color", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nBACK", "Select", "Exit");
				
			}
			if(listitem == 1)
			{
			        new car = GetPlayerVehicleID(playerid);
			        ChangeVehicleColor(car,1,1);//White
			        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			        SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You painted your car to white.");
			        ShowPlayerDialog(playerid, DIALOGID+2, DIALOG_STYLE_LIST, "Select a Color", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nBACK", "Select", "Exit");
				
			}
			if(listitem == 2)
			{
			        new car = GetPlayerVehicleID(playerid);
			        ChangeVehicleColor(car,3,3);//Red
			        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			        SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You painted your car to red.");
			        ShowPlayerDialog(playerid, DIALOGID+2, DIALOG_STYLE_LIST, "Select a Color", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nBACK", "Select", "Exit");
				
			}
			if(listitem == 3)
			{
			        new car = GetPlayerVehicleID(playerid);
			        ChangeVehicleColor(car,79,79); //Blue
			        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			        SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You painted your car to blue.");
			        ShowPlayerDialog(playerid, DIALOGID+2, DIALOG_STYLE_LIST, "Select a Color", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nBACK", "Select", "Exit");
				
			}
			if(listitem == 4)
			{
			        new car = GetPlayerVehicleID(playerid);
			        ChangeVehicleColor(car,86,86);//Green
			        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			        SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You painted your car to green.");
			        ShowPlayerDialog(playerid, DIALOGID+2, DIALOG_STYLE_LIST, "Select a Color", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nBACK", "Select", "Exit");
			
			}
			if(listitem == 5)
			{
			        new car = GetPlayerVehicleID(playerid);
			        ChangeVehicleColor(car,6,6);//Yellow
			        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			        SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You painted your car to yellow.");
			        ShowPlayerDialog(playerid, DIALOGID+2, DIALOG_STYLE_LIST, "Select a Color", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nBACK", "Select", "Exit");

			}
			if(listitem == 6)
           {
			        new car = GetPlayerVehicleID(playerid);
			        ChangeVehicleColor(car,126,126);//Pink
			        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			        SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You painted your car to pink.");
			        ShowPlayerDialog(playerid, DIALOGID+2, DIALOG_STYLE_LIST, "Select a Color", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nBACK", "Select", "Exit");
			}
			if(listitem == 7)
			{
			        new car = GetPlayerVehicleID(playerid);
			        ChangeVehicleColor(car,66,66);//Brown
			        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	          		SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You painted your car to brown.");
			        ShowPlayerDialog(playerid, DIALOGID+2, DIALOG_STYLE_LIST, "Select a Color", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nBACK", "Select", "Exit");
            }
            if(listitem == 8)
			{
        		    ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
            }
		}
   }

   if(dialogid == DIALOGID+3) //Exhausts
   {
		if(response)
		{
			if(listitem == 0)//Wheel Arch Cars Alien Exausts
			{
                if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 560)
		        {
		            new car = GetPlayerVehicleID(playerid);
		            if(pmodelid[playerid] == 562)
		            {
		            	AddVehicleComponent(car,1034);
		            	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		            	SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien Exhaust component on Elegy.");
		            	ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponent(car,1046);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien Exhaust component on Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponent(car,1065);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien Exhaust component on Jetser.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponent(car,1064);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien Exhaust component on Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponent(car,1028);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien Exhaust component on Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponent(car,1089);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				 	    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien Exhaust component on Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
	    			}
	    			}
	  			 	else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Wheel Arch Angels Car types!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
                    }
            }
			if(listitem == 1)//Wheel Arch Cars X-Flow Exausts
            {
                if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 560)
                {
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 562)
			        {
			            AddVehicleComponent(car,1037);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow Exhaust component on Elegy.");
			            ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponent(car,1045);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow Exhaust component on Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponent(car,1066);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow exaust component on Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponent(car,1059);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow Exhaust component on Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponent(car,1029);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow Exhaust component on Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponent(car,1092);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow Exhaust component on Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Wheel Arch Angels Car types!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
            }
			if(listitem == 2)//Locos Low Co. Cars Chromer Exausts
            {
                if(pmodelid[playerid] == 575 ||
				pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536 ||
				pmodelid[playerid] == 576 ||
				pmodelid[playerid] == 535)

			    {
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 575)
			        {
			            AddVehicleComponent(car,1044);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		             	SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chromer Exhaust component on Brodway.");
			            ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 534)
					{
					    AddVehicleComponent(car,1126);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chromer Exhaust component on Remington.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 567)
					{
					    AddVehicleComponent(car,1129);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	                    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chromer Exhaust component on Savanna.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 536)
					{
					    AddVehicleComponent(car,1104);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chromer Exhaust component on Blade.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 535)
					{
					    AddVehicleComponent(car,1113);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chromer Exhaust component on Slamvan.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 576)
					{
					    AddVehicleComponent(car,1136);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					   	SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chromer Exhaust component on Tornado.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Locos Low Car types!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
            }
			if(listitem == 3)//Locos Low Co. Cars Salmin Exausts
            {
                if(pmodelid[playerid] == 575 ||
				pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536 ||
				pmodelid[playerid] == 576 ||
				pmodelid[playerid] == 535)
			    {
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 575)
			        {
			            AddVehicleComponent(car,1043);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO] You have succesfully added Locos Low Slamin Exhaust component on Brodway.");
			            ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 534)
					{
					    AddVehicleComponent(car,1127);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO] You have succesfully added Locos Low Slamin Exhaust component on Remingon.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 567)
					{
					    AddVehicleComponent(car,1132);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO] You have succesfully added Locos Low Slamin Exhaust component on Savanna.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 536)
					{
					    AddVehicleComponent(car,1105);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO] You have succesfully added Locos Low Slamin Exhaust component on Blade.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}

					else if(pmodelid[playerid] == 535)
					{
					    AddVehicleComponent(car,1114);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO] You have succesfully added Locos Low Slamin Exhaust component on Slamvan.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}

					else if(pmodelid[playerid] == 576)
					{
					    AddVehicleComponent(car,1135);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO] You have succesfully added Locos Low Slamin Exhaust component on Tornado.");
					    ShowPlayerDialog(playerid, DIALOGID+3, DIALOG_STYLE_LIST, "Select a Exhaust", "Wheel Arch Alien Exhaust\nWheel Arch X-Flow Exhaust\nLocos Low Chromer Exhaust\nLocos Low Slamin Exhaust\nBACK", "Select", "Exit");
					}
                    }
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Locos Low Car types!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
            }
			if(listitem == 4)//BACK
            {
                 ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
            }
	    }
   }

   if(dialogid == DIALOGID+4)//Front Bumpers
   {
		if(response)
		{
			if(listitem == 0)//Wheel Arch Cars Alien Front Bumper
			{
                   if(pmodelid[playerid] == 562 ||
				   pmodelid[playerid] == 565 ||
				   pmodelid[playerid] == 559 ||
				   pmodelid[playerid] == 561 ||
				   pmodelid[playerid] == 560)
				   {
		            new car = GetPlayerVehicleID(playerid);
		            if(pmodelid[playerid] == 562)
		            {
		            	AddVehicleComponent(car,1171);
		            	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	              		SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien front bumper component on Elegy.");
		            	ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponent(car,1153);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien front bumper component on Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponent(car,1160);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien front bumper component on Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponent(car,1155);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien front bumper component on Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponent(car,1169);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien front bumper component on Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponent(car,1166);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				 	    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien front bumper component on Uraus.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Wheel Arch Angels Car types!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
	                }
            }
			if(listitem == 1)//Wheel Arch Cars X-Flow Front Bumper
            {
                   if(pmodelid[playerid] == 562 ||
	               pmodelid[playerid] == 565 ||
	               pmodelid[playerid] == 559 ||
	               pmodelid[playerid] == 561 ||
                   pmodelid[playerid] == 560)
		           {

			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 562)
			        {
			            AddVehicleComponent(car,1172);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow front bumper component on Elegy.");
			            ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponent(car,1152);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch  X-Flow front bumper component on Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponent(car,1173);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch  X-Flow front bumper component on Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponent(car,1157);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch  X-Flow front bumper component on Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponent(car,1170);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch  X-Flow front bumper component on Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponent(car,1165);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch  X-Flow front bumper component on Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Wheel Arch Angels Car types!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
		    }
			if(listitem == 2)//Locos Low Co. Car Chromer Front Bumper
            {
                if(pmodelid[playerid] == 575 ||
				pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536 ||
				pmodelid[playerid] == 576 ||
				pmodelid[playerid] == 535)
				{
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 575)
			        {
			            AddVehicleComponent(car,1174);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chromer front bumper component on Brodway.");
			            ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 534)
					{
					    AddVehicleComponent(car,1179);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chromer front bumper component on Remington.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 567)
					{
					    AddVehicleComponent(car,1189);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]:You have succesfully added Locos Low Chromer front bumper component on Savanna.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 536)
					{
					    AddVehicleComponent(car,1182);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chromer front bumper component on Blade.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 535)
					{
					    AddVehicleComponent(car,1115);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chromer front bumper component on Slamvan.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 576)
					{
					    AddVehicleComponent(car,1191);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chromer front bumper component on Tornado.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Locos Low Car types!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
			}
			if(listitem == 3)//Locos Low Co. Salmin Front Bumper
            {
                if(pmodelid[playerid] == 575 ||
				pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536 ||
	            pmodelid[playerid] == 576 ||
				pmodelid[playerid] == 576)
			    {
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 575)
			        {
			            AddVehicleComponent(car,1175);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Slamin front bumper component on Brodway.");
			            ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 534)
					{
					    AddVehicleComponent(car,1185);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Slamin front bumper component on Remington.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 567)
					{
					    AddVehicleComponent(car,1188);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Slamin front bumper component on Savanna.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 536)
					{
					    AddVehicleComponent(car,1181);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Slamin front bumper component on Blade.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
                    else if(pmodelid[playerid] == 535)
					{
					    AddVehicleComponent(car,1116);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Slamin front bumper component on Slamvan.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 576)
					{
					    AddVehicleComponent(car,1190);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Slamin front bumper component on Tornado.");
					    ShowPlayerDialog(playerid, DIALOGID+4, DIALOG_STYLE_LIST, "Select a Front Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Locos Low Car types!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
                    }
            }
			if(listitem == 4)//BACK
            {
                 ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
            }
        }
   }

   if(dialogid == DIALOGID+5)//Rear Bumpers
   {
		if(response)
		{
			if(listitem == 0)//Wheel Arch Cars Alien Rear Bumper
			{
                if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 560)
		        {
                    new car = GetPlayerVehicleID(playerid);
		            if(pmodelid[playerid] == 562)
		            {
		            	AddVehicleComponent(car,1149);
		            	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	              		SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien rear bumper component on Elegy.");
		            	ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponent(car,1150);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien rear bumper component on Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponent(car,1159);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien rear bumper component on Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponent(car,1154);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien rear bumper component on Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponent(car,1141);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien rear bumper component on Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponent(car,1168);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				 	    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien rear bumper component on Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Wheel Arch Angels Car types!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
            }
			if(listitem == 1)//Wheel Arch Cars X-Flow Rear Bumper
            {
                if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 560)
		        {

					new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 562)
			        {
			            AddVehicleComponent(car,1148);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch  X-Flow rear bumper component on Elegy.");
		                ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponent(car,1151);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch  X-Flow rear bumper component on Flash.");
				        ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponent(car,1161);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch  X-Flow rear bumper component on Jester.");
				        ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponent(car,1156);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch  X-Flow rear bumper component on Stratum.");
				        ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponent(car,1140);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch  X-Flow rear bumper component on Sultan.");
				        ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponent(car,1167);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch  X-Flow rear bumper component on Uranus.");
				        ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Wheel Arch Angels Car types!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
            }
			if(listitem == 2)//Locos Low Co. Cars Chromer Rear Bumper
            {
                if(pmodelid[playerid] == 575 ||
				pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536 ||
				pmodelid[playerid] == 576 ||
				pmodelid[playerid] == 535)
			    {
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 575)
			        {
			            AddVehicleComponent(car,1176);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chromer rear bumper component on Brodway.");
			            ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 534)
					{
					    AddVehicleComponent(car,1180);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chromer rear bumper component on Remington.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 567)
					{
					    AddVehicleComponent(car,1187);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chromer rear bumper component on Savanna.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 536)
					{
					    AddVehicleComponent(car,1184);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chromer rear bumper component on Blade.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 535)
					{
					    AddVehicleComponent(car,1109);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chromer rear bumper component on Slamvan.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 576) 
					{
					    AddVehicleComponent(car,1192);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chromer rear bumper component on Tornado.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Locos Low Car types!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
            }
			if(listitem == 3)//Locos Low Co. Cars Salmin Rear Bumper
            {
                if(pmodelid[playerid] == 575 ||
				pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536 ||
				pmodelid[playerid] == 576 ||
				pmodelid[playerid] == 535)
			    {
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 575)
			        {
			            AddVehicleComponent(car,1177);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Slamin rear bumper component on Brodway.");
			            ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 534)
					{
					    AddVehicleComponent(car,1178);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Slamin rear bumper component on Remington.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 567)
					{
					    AddVehicleComponent(car,1186);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Slamin rear bumper component on Savanna.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 536)
					{
					    AddVehicleComponent(car,1183);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Slamin rear bumper component on Blade.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}

					else if(pmodelid[playerid] == 535)
					{
					    AddVehicleComponent(car,1110);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Slamin rear bumper component on Slamvan.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}

					else if(pmodelid[playerid] == 576)
					{
					    AddVehicleComponent(car,1193);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Slamin rear bumper component on Tornado.");
					    ShowPlayerDialog(playerid, DIALOGID+5, DIALOG_STYLE_LIST, "Select a Rear Bumper", "Wheel Arch Alien bumper\nWheel Arch X-Flow bumper\nLocos Low Chromer bumper\nLocos Low Slamin bumper\nBACK", "Select", "Exit");
					}
                    }
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Locos Low Car types!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
            }
            if(listitem == 4)//BACK
            {
                 ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
            }
        }
   }

   if(dialogid == DIALOGID+6)//Roofs
   {
		if(response)
		{
			if(listitem == 0)//Wheel Arch Cars Alien Roof Vent
			{
                if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 560)
		        {

		            new car = GetPlayerVehicleID(playerid);
		            if(pmodelid[playerid] == 562) 
		            {
		            	AddVehicleComponent(car,1035);
		            	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	              		SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien roof vent component on Elegy.");
		            	ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Select a Roof", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 565) 
					{
					    AddVehicleComponent(car,1054);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien roof vent component on Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Select a Roof", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponent(car,1067);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien roof vent component on Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Select a Roof", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponent(car,1055);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien roof vent component on Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Select a Roof", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponent(car,1032);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien roof vent component on Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Select a Roof", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponent(car,1088);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				 	    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien roof vent component on Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Select a Roof", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Wheel Arch Angels Car types!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
            }
	        if(listitem == 1)//Wheel Arch Cars X-Flow Roof Vent
			{
                if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 560)
		        {


			        new car = GetPlayerVehicleID(playerid);    
			        if(pmodelid[playerid] == 562)
			        {
			            AddVehicleComponent(car,1035);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow roof vent component on Elegy.");
			            ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Select a Roof", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 565) 
					{
					    AddVehicleComponent(car,1053);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow roof vent component on Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Select a Roof", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 559) 
					{
					    AddVehicleComponent(car,1068);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow roof vent component on Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Select a Roof", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponent(car,1061);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow roof vent component on Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Select a Roof", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponent(car,1033);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow roof vent component on Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Select a Roof", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponent(car,1091);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow roof vent component on Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Select a Roof", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Wheel Arch Angels Car types!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
			}
			if(listitem == 2)//Locos Low Co. Cars Hardtop Roof
			{
                if(pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536)
			    {
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 567)
			        {
			            AddVehicleComponent(car,1130);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Hardtop Roof component on Brodway.");
			            ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Select a Roof", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nBACK", "Select", "Exit");
					}
	   				else if(pmodelid[playerid] == 536)
					{
					    AddVehicleComponent(car,1128);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Hardtop Roof component on Blade.");
					    ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Select a Roof", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Locos Low Car types Savanna and Blade!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
            }
		    if(listitem == 3)//Locos Low Co. Cars Softtop Roof
			{
                 if(pmodelid[playerid] == 567 ||
				pmodelid[playerid] == 536)
			    {
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 567) 
			        {
			            AddVehicleComponent(car,1131);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Softtop Roof component on Brodway.");
			            ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Select a Roof", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nBACK", "Select", "Exit");
					}
	   				else if(pmodelid[playerid] == 536)
					{
					    AddVehicleComponent(car,1103);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Softtop Roof component on Blade.");
                        ShowPlayerDialog(playerid, DIALOGID+6, DIALOG_STYLE_LIST, "Select a Roof", "Wheel Arch Alien Roof Vent\nWheel Arch X-Flow Roof Vent\nLocos Low Hardtop Roof\nLocos Low Softtop Roof\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Locos Low Car types Savanna and Blade!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
            }
            if(listitem == 4)//BACK
            {
                 ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
            }
	     }
   }
    
   if(dialogid == DIALOGID+7)//Spoilers
   {
		if(response)
		{
			if(listitem == 0)//Wheel Arch Cars Alien Spoilers
			{
                if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 560)
		        {

		            new car = GetPlayerVehicleID(playerid);
		            if(pmodelid[playerid] == 562)
		            {
		            	AddVehicleComponent(car,1147);
		            	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	              		SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien Spoilers component on Elegy.");
		            	ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Select a Spoiler", "Alien Spoiler\nX-Flow Spoiler\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponent(car,1049);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien Spoilers component on Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Select a Spoiler", "Alien Spoiler\nX-Flow Spoiler\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 559) 
					{
					    AddVehicleComponent(car,1162);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien Spoilers component on Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Select a Spoiler", "Alien Spoiler\nX-Flow Spoiler\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 561) 
					{
					    AddVehicleComponent(car,1158);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien Spoilers component on Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Select a Spoiler", "Alien Spoiler\nX-Flow Spoiler\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 560) 
					{
					    AddVehicleComponent(car,1138);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien Spoilers component on Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Select a Spoiler", "Alien Spoiler\nX-Flow Spoiler\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponent(car,1164);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				 	    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien Spoilers component on Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Select a Spoiler", "Alien Spoiler\nX-Flow Spoiler\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Wheel Arch Angels Car types!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
    	    }
            if(listitem == 1)//Wheel Arch Cars X-Flow Spoilers
			{
                if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 560)
		        {
                    new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 562) 
			        {
			            AddVehicleComponent(car,1146);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow Spoilers component on Elegy.");
			            ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Select a Spoiler", "Alien Spoiler\nX-Flow Spoiler\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 565)
					{
					    AddVehicleComponent(car,1150);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow Spoilers component on Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Select a Spoiler", "Alien Spoiler\nX-Flow Spoiler\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 559)
					{
					    AddVehicleComponent(car,1158);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow Spoilers component on Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Select a Spoiler", "Alien Spoiler\nX-Flow Spoiler\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponent(car,1060);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow Spoilers component on Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Select a Spoiler", "Alien Spoiler\nX-Flow Spoiler\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponent(car,1139);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow Spoilers component on Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Select a Spoiler", "Alien Spoiler\nX-Flow Spoiler\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 558)
					{
					    AddVehicleComponent(car,1163);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow Spoilers component on Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+7, DIALOG_STYLE_LIST, "Select a Spoiler", "Alien Spoiler\nX-Flow Spoiler\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to X-Flow Arch Angels Car types!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
            }
            if(listitem == 2)//BACK
            {
                 ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
            }
	   	 }
   }

   if(dialogid == DIALOGID+8)//Sideskirts
   {
		if(response)
		{
			if(listitem == 0)//Wheel Arch Cars Alien Sideskirts
			{
                if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 560)
		        {

		            new car = GetPlayerVehicleID(playerid);
		            if(pmodelid[playerid] == 562)
		            {
		            	AddVehicleComponent(car,1036);
		            	AddVehicleComponent(car,1040);
		            	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	              		SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien Side Skirts component on Elegy.");
		            	ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 565) 
					{
					    AddVehicleComponent(car,1047);
					    AddVehicleComponent(car,1051);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien Sideskirts vent component on Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 559) 
					{
					    AddVehicleComponent(car,1069);
					    AddVehicleComponent(car,1071);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien Side Skirts component on Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponent(car,1056);
					    AddVehicleComponent(car,1062);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien Side Skirts component on Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 560)
					{
					    AddVehicleComponent(car,1026);
					    AddVehicleComponent(car,1027);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien Side Skirts bumper component on Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 558) 
					{
					    AddVehicleComponent(car,1090);
					    AddVehicleComponent(car,1094);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				 	    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch Alien Side Skirts component on Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Wheel Arch Angels Car types!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
		    }
	   	    if(listitem == 1)//Wheel Arch Cars X-Flow Sideskirts
			{
                if(pmodelid[playerid] == 562 ||
				pmodelid[playerid] == 565 ||
				pmodelid[playerid] == 559 ||
				pmodelid[playerid] == 561 ||
				pmodelid[playerid] == 560)
		        {
				    new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 562) 
			        {
			            AddVehicleComponent(car,1039);
			            AddVehicleComponent(car,1041);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow Side Skirts component on Elegy.");
			            ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 565) 
					{
					    AddVehicleComponent(car,1048);
					    AddVehicleComponent(car,1052);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow Side Skirts component on Flash.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 559) 
					{
					    AddVehicleComponent(car,1070);
					    AddVehicleComponent(car,1072);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow Side Skirts component on Jester.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 561)
					{
					    AddVehicleComponent(car,1057);
					    AddVehicleComponent(car,1063);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow Side Skirts component on Stratum.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 560) 
					{
					    AddVehicleComponent(car,1031);
					    AddVehicleComponent(car,1030);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow Side Skirts component on Sultan.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
					}
					else if(pmodelid[playerid] == 558)  
					{
					    AddVehicleComponent(car,1093);
					    AddVehicleComponent(car,1095);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wheel Arch X-Flow Side Skirts component on Uranus.");
					    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Wheel Arch Angels Car types!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
		    }
		    if(listitem == 2)//Locos Low Co. Cars Chrome Strip Sideskirts
			{
                 if(pmodelid[playerid] == 575 ||
	               pmodelid[playerid] == 536 ||
	               pmodelid[playerid] == 576 ||
		 	       pmodelid[playerid] == 567)
                   {
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 575) 
			        {
	       		        AddVehicleComponent(car,1042);
	       		        AddVehicleComponent(car,1099);
	       		        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chrome Strip Side Skirts component on Brodway.");
			            ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
					}
	   				else if(pmodelid[playerid] == 567)
					{
					    AddVehicleComponent(car,1102);
					    AddVehicleComponent(car,1133);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chrome Strip Side Skirts component on Savanna.");
	    		        ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
	                }
	                else if(pmodelid[playerid] == 576) 
					{
					    AddVehicleComponent(car,1134);
					    AddVehicleComponent(car,1137);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chrome Strip Side Skirts component on Tornado.");
	    		        ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
	                }
	                else if(pmodelid[playerid] == 536) 
					{
					    AddVehicleComponent(car,1108);
					    AddVehicleComponent(car,1107);
					    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					    SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chrome Strip Side Skirts component on Blade.");
	                    ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
	                }
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Locos Low Car types Brodway, Savanna Tornado and Blade!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
	        }
	  	    if(listitem == 3)//Locos Low Co. Cars Chrome Flames Sideskirts
			{
                if(pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 534)
			    {
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 534)
			        {
			            AddVehicleComponent(car,1122);
			            AddVehicleComponent(car,1101);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chrome Flames Side Skirts component on Remington.");
			            ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Locos Low Car type Remington!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
			}
			if(listitem == 4)//Locos Low Co. Cars Chrome Arches Sideskirts
			{
                if(pmodelid[playerid] == 534 ||
				pmodelid[playerid] == 534)
			    {
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 534)
			        {
			            AddVehicleComponent(car,1106);
			            AddVehicleComponent(car,1124);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chrome Arches Side Skirts component on Remington.");
			            ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Locos Low Car type Remington!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
			}
			if(listitem == 5)//Locos Low Co. Cars Chrome Trim Sideskirts
			{
                if(pmodelid[playerid] == 535)

			    {
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 535)
			        {
			            AddVehicleComponent(car,1118);
			            AddVehicleComponent(car,1120);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chrome Trim Side Skirts component on Slamvan.");
			            ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Locos Low Car type Slamvan!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
			}
			if(listitem == 6)//Locos Low Co. Cars Chrome Wheelcovers Sideskirts
			{
                if(pmodelid[playerid] == 535)

			    {
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 535)
			        {
			            AddVehicleComponent(car,1119);
			            AddVehicleComponent(car,1121);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chrome Wheelcovers component on Slamvan.");
			            ShowPlayerDialog(playerid, DIALOGID+8, DIALOG_STYLE_LIST, "Select a SideSkirt", "Wheel Arch Alien Side Skirts\nWheel Arch X-Flow Side Skirts\nLocos Low Chrome Strip\nLocos Low Chrome Flames\nLocos Low Chrome Arches\nLocos Low Chrome Trim\nLocos Low Wheelcovers\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Locos Low Car type Slamvan!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
			}
			if(listitem == 7)//BACK
            {
                 ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
            }
         }
   }
   if(dialogid == DIALOGID+9)//Bullbars
   {
		if(response)
		{
			if(listitem == 0)//Locos Low Co. Cars Chrome Grill
			{
                if(pmodelid[playerid] == 534)

			    {
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 534)
			        {
			            AddVehicleComponent(car,1100);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chrome Grill component on Remington.");
			            ShowPlayerDialog(playerid, DIALOGID+9, DIALOG_STYLE_LIST, "Select a Bullbar", "Locos Low Chrome Grill\nLocos Low Chrome Bars\nLocos Low Chrome Lights\nLocos Low Chrome Bullbar\nBACK", "Select", "Exit");
			        }
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Locos Low Car type Remington!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
			}
			if(listitem == 1)//Locos Low Co. Cars Chrome Bars
			{
                 if(pmodelid[playerid] == 534)

			    {
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 534)
			        {
			            AddVehicleComponent(car,1123);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chrome Bars component on Remington.");
			            ShowPlayerDialog(playerid, DIALOGID+9, DIALOG_STYLE_LIST, "Select a Bullbar", "Locos Low Chrome Grill\nLocos Low Chrome Bars\nLocos Low Chrome Lights\nLocos Low Chrome Bullbar\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Locos Low Car type Remington!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
			}
			if(listitem == 2)//Locos Low Co. Cars Chrome Lights
			{
                if(pmodelid[playerid] == 534)

			    {
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 534)
			        {
			            AddVehicleComponent(car,1125);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chrome Lights component on Remington.");
			            ShowPlayerDialog(playerid, DIALOGID+9, DIALOG_STYLE_LIST, "Select a Bullbar", "Locos Low Chrome Grill\nLocos Low Chrome Bars\nLocos Low Chrome Lights\nLocos Low Chrome Bullbar\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Locos Low Car type Remington!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
			}
			if(listitem == 3)//Locos Low Co. Cars Chrome Bullbar
			{
                if(pmodelid[playerid] == 535)

			    {
			        new car = GetPlayerVehicleID(playerid);
			        if(pmodelid[playerid] == 535)
			        {
			            AddVehicleComponent(car,1117);
			            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			            SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Locos Low Chrome Lights component on Slamvan.");
			            ShowPlayerDialog(playerid, DIALOGID+9, DIALOG_STYLE_LIST, "Select a Bullbar", "Locos Low Chrome Grill\nLocos Low Chrome Bars\nLocos Low Chrome Lights\nLocos Low Chrome Bullbar\nBACK", "Select", "Exit");
					}
					}
					else
					{
				    SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can only add this component to Locos Low Car type Slamvan!");
					ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
					}
			}
			if(listitem == 4)//BACK
            {
                 ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
            }
       }
   }
   
   if(dialogid == DIALOGID+10)//Wheels
   {
		if(response)
		{
			if(listitem == 0)//Offroad
			{
                 new car = GetPlayerVehicleID(playerid);
		         AddVehicleComponent(car,1025);
		         PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                 SendClientMessage(playerid,COLOR_YELLOW,"[INFO] You have succesfully added Offroad Wheels.");
	             ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Select a Wheel type", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nNext Page\nBACK", "Select", "Exit");
	        }
            if(listitem == 1)//Mega
			{
                 new car = GetPlayerVehicleID(playerid);
			     AddVehicleComponent(car,1074);
			     PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			     SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Mega Wheels.");
			     ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Select a Wheel type", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nNext Page\nBACK", "Select", "Exit");
			}
            if(listitem == 2)//Wires
			{
                 new car = GetPlayerVehicleID(playerid);
	             AddVehicleComponent(car,1076);
		         SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Wires Wheels.");
			     ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Select a Wheel type", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nNext Page\nBACK", "Select", "Exit");
			}
	        if(listitem == 3)//Twist
			{
                 new car = GetPlayerVehicleID(playerid);
			     AddVehicleComponent(car,1078);
			     PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			     SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Twist Wheels.");
			     ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Select a Wheel type", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nNext Page\nBACK", "Select", "Exit");
			}
			if(listitem == 4)//Groove
			{
                 new car = GetPlayerVehicleID(playerid);
			     AddVehicleComponent(car,1081);
			     PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			     SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Groove Wheels.");
		         ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Select a Wheel type", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nNext Page\nBACK", "Select", "Exit");
			}
			if(listitem == 5)//Import
			{
                 new car = GetPlayerVehicleID(playerid);
                 AddVehicleComponent(car,1082);
                 PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
   			     SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Import Wheels.");
			     ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Select a Wheel type", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nNext Page\nBACK", "Select", "Exit");
			}
			if(listitem == 6)//Atomic
			{
                 new car = GetPlayerVehicleID(playerid);
			     AddVehicleComponent(car,1085);
			     PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			     SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Atomic Wheels.");
                 ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Select a Wheel type", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nNext Page\nBACK", "Select", "Exit");
			}
			if(listitem == 7)//Ahab
			{
                 new car = GetPlayerVehicleID(playerid);
			     AddVehicleComponent(car,1096);
			     PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	          	 SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Ahab Wheels.");
			     ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Select a Wheel type", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nNext Page\nBACK", "Select", "Exit");
			}
			if(listitem == 8)//Virtual
			{
                 new car = GetPlayerVehicleID(playerid);
                 AddVehicleComponent(car,1097);
                 PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	           	 SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Virtual Wheels.");
                 ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Select a Wheel type", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nNext Page\nBACK", "Select", "Exit");
			}
			if(listitem == 9)//Access
			{
                 new car = GetPlayerVehicleID(playerid);
			     AddVehicleComponent(car,1098);
			     PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
	         	 SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Access Wheels.");
			     ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Select a Wheel type", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nNext Page\nBACK", "Select", "Exit");
			}
			if(listitem == 10)//Next page
			{
                 ShowPlayerDialog(playerid, DIALOGID+13, DIALOG_STYLE_LIST, "Select a Wheel type", "Trance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\nBACK", "Select", "Exit");
			}
			if(listitem == 11)//BACK
            {
                 ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
            }

		}
   }

   if(dialogid == DIALOGID+11)//Car Stereo
   {
		if(response)
		{
			if(listitem == 0)//Bass Boost
			{
                 new car = GetPlayerVehicleID(playerid);
		         AddVehicleComponent(car,1086);
		         PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		         SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Stereo Bass Bost system.");
		         ShowPlayerDialog(playerid, DIALOGID+11, DIALOG_STYLE_LIST, "Select a Car Stereo.", "Bass Boost\nSuper Bass Boost\nUltra Bass Boost\nKing Bass Boost\nBACK", "Select", "Exit");
			}
			if(listitem == 1)//Super Bass Boost
			{
		         new car = GetPlayerVehicleID(playerid);
		         AddVehicleComponent(car,1086);
		         PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		         SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Stereo Super Bass Bost system.");
		         ShowPlayerDialog(playerid, DIALOGID+11, DIALOG_STYLE_LIST, "Select a Car Stereo.", "Bass Boost\nSuper Bass Boost\nUltra Bass Boost\nKing Bass Boost\nBACK", "Select", "Exit");
			}
			if(listitem == 2)//Ultra Bass Boost
			{
		         new car = GetPlayerVehicleID(playerid);
		         AddVehicleComponent(car,1086);
                 PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		         SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Stereo Ultra Bass Bost system.");
		         ShowPlayerDialog(playerid, DIALOGID+11, DIALOG_STYLE_LIST, "Select a Car Stereo.", "Bass Boost\nSuper Bass Boost\nUltra Bass Boost\nKing Bass Boost\nBACK", "Select", "Exit");
			}
			if(listitem == 3)//King Bass Boost
			{
		         new car = GetPlayerVehicleID(playerid);
		         AddVehicleComponent(car,1086);
		         PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		         SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added King Stereo Bass Bost system.");
		         ShowPlayerDialog(playerid, DIALOGID+11, DIALOG_STYLE_LIST, "Select a Car Stereo.", "Bass Boost\nSuper Bass Boost\nUltra Bass Boost\nKing Bass Boost\nBACK", "Select", "Exit");
			}
			if(listitem == 4)//BACK
            {
                 ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
            }
		}
   }

   if(dialogid == DIALOGID+12)//Tune car menu 2
   {
		if(response)
		{
			if(listitem == 0)//Hydraulics
			{
		         new car = GetPlayerVehicleID(playerid);
		         AddVehicleComponent(car,1087);
		         PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		         SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Hydraulics to car.");
		         ShowPlayerDialog(playerid, DIALOGID+12, DIALOG_STYLE_LIST, "Tune car menu", "Hydraulics\nNitro x10\nRepair Car\nBACK", "Select", "Exit");
			}
			if(listitem == 1)//Nitro x10
			{
		         new car = GetPlayerVehicleID(playerid);
		         AddVehicleComponent(car,1010);
		         PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		         SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added 10x Nitro to car.");
		         ShowPlayerDialog(playerid, DIALOGID+12, DIALOG_STYLE_LIST, "Tune car menu", "Hydraulics\nNitro x10\nRepair Car\nBACK", "Select", "Exit");
			}
			if(listitem == 2)//Repair Car
			{
		         new car = GetPlayerVehicleID(playerid);
		         SetVehicleHealth(car,1000);
		         PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		         SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully repaired car.");
		         ShowPlayerDialog(playerid, DIALOGID+12, DIALOG_STYLE_LIST, "Tune car menu", "Hydraulics\nNitro x10\nRepair Car\nBACK", "Select", "Exit");
			}
			if(listitem == 3)//BACK
            {
                 ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
            }
		}
	}

   if(dialogid == DIALOGID+13)//Wheels 2
   {
		if(response)
		{
			if(listitem == 0)//Trance
            {
		         new car = GetPlayerVehicleID(playerid);
		         AddVehicleComponent(car,1084);
		         PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		         SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Trance Wheels.");
		         ShowPlayerDialog(playerid, DIALOGID+13, DIALOG_STYLE_LIST, "Select a Wheel type", "Trance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\nBACK", "Select", "Exit");
            }
            if(listitem == 1)//Shadow
            {
		         new car = GetPlayerVehicleID(playerid);
		         AddVehicleComponent(car,1073);
		         PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		         SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Shadow Wheels.");
		         ShowPlayerDialog(playerid, DIALOGID+13, DIALOG_STYLE_LIST, "Select a Wheel type", "Trance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\nBACK", "Select", "Exit");
            }
            if(listitem == 2)//Rimshine
            {
		         new car = GetPlayerVehicleID(playerid);
		         AddVehicleComponent(car,1075);
		         PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		         SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Rimshine Wheels.");
		         ShowPlayerDialog(playerid, DIALOGID+13, DIALOG_STYLE_LIST, "Select a Wheel type", "Trance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\nBACK", "Select", "Exit");
            }
            if(listitem == 3)//Classic
            {
		         new car = GetPlayerVehicleID(playerid);
		         AddVehicleComponent(car,1077);
		         PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		         SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Classic Wheels.");
		         ShowPlayerDialog(playerid, DIALOGID+13, DIALOG_STYLE_LIST, "Select a Wheel type", "Trance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\nBACK", "Select", "Exit");
            }
            if(listitem == 4)//Cutter
            {
		         new car = GetPlayerVehicleID(playerid);
		         AddVehicleComponent(car,1079);
		         PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		         SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Cutter Wheels.");
		         ShowPlayerDialog(playerid, DIALOGID+13, DIALOG_STYLE_LIST, "Select a Wheel type", "Trance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\nBACK", "Select", "Exit");
            }
            if(listitem == 5)//Switch
            {
		         new car = GetPlayerVehicleID(playerid);
		         AddVehicleComponent(car,1080);
		         PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		         SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Switch Wheels.");
		         ShowPlayerDialog(playerid, DIALOGID+13, DIALOG_STYLE_LIST, "Select a Wheel type", "Trance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\nBACK", "Select", "Exit");
            }
            if(listitem == 6)//Dollar
            {
		         new car = GetPlayerVehicleID(playerid);
		         AddVehicleComponent(car,1083);
		         PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		         SendClientMessage(playerid,COLOR_YELLOW,"[INFO]: You have succesfully added Dollar Wheels.");
		         ShowPlayerDialog(playerid, DIALOGID+13, DIALOG_STYLE_LIST, "Select a Wheel type", "Trance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\nBACK", "Select", "Exit");
            }
            if(listitem == 7)//BACK
            {
		         ShowPlayerDialog(playerid, DIALOGID+10, DIALOG_STYLE_LIST, "Select a Wheel type", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nNext Page\nBACK", "Select", "Exit");
            }
         }
    }
}
////////////////////////////////////////////////////////////////////////////////
public OnPlayerStateChange(playerid, newstate, oldstate) {
	if(newstate == PLAYER_STATE_DRIVER) {
	    pvehicleid[playerid] = GetPlayerVehicleID(playerid);
	    pmodelid[playerid] = GetVehicleModel(pvehicleid[playerid]);
	}
	else {
	    pvehicleid[playerid] = 0;
	    pmodelid[playerid] = 0;
	}
	return 1;
}
////////////////////////////////////////////////////////////////////////////////
public ModCar(playerid) {
	switch(pmodelid[playerid]) {
        case 562,565,559,561,560,575,534,567,536,535,576,411,579,602,496,518,527,589,597,419,
		533,526,474,545,517,410,600,436,580,439,549,491,445,604,507,585,587,466,492,546,551,516,
		426,547,405, 409,550,566,406,540,421,529,431,438,437,420,525,552,416,433,427,490,528,
		407,544,470,598,596,599,601,428,499,609,524,578,486,573,455,588,403,514,423,
		414,443,515,456,422,482,530,418,572,413,440,543,583,478,554,402,542,603,475,568,504,457,
        483,508,429,541,415,480,434,506,451,555,477,400,404,489,479,442,458,467,558: {
        ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_LIST, "Tune car menu","Paint Jobs\nColors\nExhausts\nFront Bumper\nRear Bumper\nRoof\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nNext page", "Select", "Exit");
		return SendClientMessage(playerid, COLOR_YELLOW, "[INFO]: Select an item.");
		}
		default: return SendClientMessage(playerid,COLOR_RED,"[ERROR]: You can't modify this vehicle.");
	}
	return 1;
}
////////////////////////////////////////////////////////////////////////////////
#endif
