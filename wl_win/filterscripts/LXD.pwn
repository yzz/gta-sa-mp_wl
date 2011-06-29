#include <a_samp>

//Main
#define VERSION "第二步 - 电影城 v1.1 Build 091204"
#define TOTAL_NPC 8

//DEBUG Settings
#define DEBUG

//Defines
#define SELECT_NPC_COMMAND "/selectnpc"
#define OPEN_NPC_NAME "/showname"
#define SHOW_BOUNDS "/showbounds"
#define DIALOG_ID 102

//Colors
#define RED 0xA10000AA
#define GREEN 0x33AA33AA

//Vars
new bool:NPCNameShow;
new bool:BoundsShow;
new Text3D:textid[TOTAL_NPC];
new NPCIDs[TOTAL_NPC];

//Vehicles
new Bul;
//new Elegy1; // for Drift1 - 咔吧掉
new Elegy; // for Drift
new Inf1; // for RunInMadd
new Inf2; // for LSEyeOut
new Inf3; // for TestDrive
new Inf4; // for OffControl
new Inf5; // for FollowMe
new Inf6; // for FollowMe2

forward SetPlayerToNPCVehicle(playerid,vehicleid);

public OnFilterScriptInit()
{

	// NPCS
	ConnectNPC("DrifterLDZ","LXDLDZ");
	//ConnectNPC("Drifter1","Drift1"); - 咔吧掉
	ConnectNPC("Drifter","Drift");
	ConnectNPC("DrifterMadd","RunInMadd");
	ConnectNPC("DrifterLS","LSEyeOut");
	ConnectNPC("DrifterTD","TestDrive");
	ConnectNPC("DrifterOff","OffControl");
	ConnectNPC("DrifterFM","FollowMe");
	ConnectNPC("DrifterFM2","FollowMe2");
	
	Bul = AddStaticVehicle(541,-342.7927,1540.4495,75.1911,178.9945,6,1);
	//Elegy1 = AddStaticVehicle(562,0.0,0.0,5.0,0.0,6,1); - 咔吧掉
	Elegy = AddStaticVehicle(562,1.0,1.0,5.0,0.0,7,1);
	Inf1 = AddStaticVehicle(411,3.0,3.0,5.0,0.0,6,1);
	Inf2 = AddStaticVehicle(411,5.0,5.0,5.0,0.0,118,1);
	Inf3 = AddStaticVehicle(411,7.0,7.0,5.0,0.0,66,1);
	Inf4 = AddStaticVehicle(411,9.0,9.0,5.0,0.0,65,1);
	Inf5 = AddStaticVehicle(411,15.0,9.0,5.0,0.0,68,1);
	Inf6 = AddStaticVehicle(411,18.0,9.0,5.0,0.0,70,1);
	
	BoundsShow = true;
	
	printf("\n* Shindo's NPC System - LXD计划 %s 已加载.\n", VERSION);
	return 1;
}

public OnFilterScriptExit()
{
	printf("\n* Shindo's NPC System - LXD计划 %s 已退出.\n", VERSION);
	return 1;
}

public OnPlayerSpawn(playerid)
{
    if(!IsPlayerNPC(playerid)) return 0; // We only deal with NPC players in this script

	new playername[64];
	GetPlayerName(playerid,playername,64);
	
	new str[50];

 	if(!strcmp(playername,"DrifterLDZ",true)) {
        PutPlayerInVehicle(playerid, Bul, 0);
        SetSpawnInfo(playerid,0,115,1958.33,1343.12,15.36,269.15,0,0,0,0,0,0);
        ////ShowPlayerMarkers(1);
        format(str,sizeof(str),"Drifter-LDZ\n(ID:%d)",playerid);
        NPCIDs[0] = playerid;
        textid[0] = Create3DTextLabel(str,GREEN,0.0,0.0,0.0,15.0,0);
	    Attach3DTextLabelToVehicle(textid[0], Bul, 0.0, 0.0, 0.0);
	    SetPlayerColor(playerid,0xFFFF00AA);
		NPCNameShow = true;
	}
	/*else if(!strcmp(playername,"Drifter1",true)) { - 咔吧掉
        PutPlayerInVehicle(playerid, Elegy1, 0);
        SetSpawnInfo(playerid,0,115,1958.33,1343.12,15.36,269.15,0,0,0,0,0,0);
        //ShowPlayerMarkers(1);
	}*/
	else if(!strcmp(playername,"Drifter",true)) {
        PutPlayerInVehicle(playerid, Elegy, 0);
        SetSpawnInfo(playerid,0,115,1958.33,1343.12,15.36,269.15,0,0,0,0,0,0);
        //ShowPlayerMarkers(1);
        format(str,sizeof(str),"Drifter-SF Two Circles\n(ID:%d)",playerid);
        NPCIDs[1] = playerid;
        textid[1] = Create3DTextLabel(str,GREEN,0.0,0.0,0.0,15.0,0);
	    Attach3DTextLabelToVehicle(textid[1], Elegy, 0.0, 0.0, 0.0);
	    SetPlayerColor(playerid,0xFFFF00AA);
	    NPCNameShow = true;
	}
	else if(!strcmp(playername,"DrifterMadd",true)) {
        PutPlayerInVehicle(playerid, Inf1, 0);
        SetSpawnInfo(playerid,0,115,1958.33,1343.12,15.36,269.15,0,0,0,0,0,0);
        //ShowPlayerMarkers(1);
        format(str,sizeof(str),"Drifter-RunInMadd\n(ID:%d)",playerid);
        NPCIDs[2] = playerid;
        textid[2] = Create3DTextLabel(str,GREEN,0.0,0.0,0.0,15.0,0);
	    Attach3DTextLabelToVehicle(textid[2], Inf1, 0.0, 0.0, 0.0);
	    SetPlayerColor(playerid,0xFFFF00AA);
	    NPCNameShow = true;
	}
	else if(!strcmp(playername,"DrifterLS",true)) {
        PutPlayerInVehicle(playerid, Inf2, 0);
        SetSpawnInfo(playerid,0,115,1958.33,1343.12,15.36,269.15,0,0,0,0,0,0);
        //ShowPlayerMarkers(1);
        format(str,sizeof(str),"Drifter-LSEyeOut\n(ID:%d)",playerid);
        NPCIDs[3] = playerid;
        textid[3] = Create3DTextLabel(str,GREEN,0.0,0.0,0.0,15.0,0);
	    Attach3DTextLabelToVehicle(textid[3], Inf2, 0.0, 0.0, 0.0);
	    SetPlayerColor(playerid,0xFFFF00AA);
	    NPCNameShow = true;
	}
	else if(!strcmp(playername,"DrifterTD",true)) {
        PutPlayerInVehicle(playerid, Inf3, 0);
        SetSpawnInfo(playerid,0,115,1958.33,1343.12,15.36,269.15,0,0,0,0,0,0);
        //ShowPlayerMarkers(1);
        format(str,sizeof(str),"Drifter-SFTestDrive\n(ID:%d)",playerid);
        NPCIDs[4] = playerid;
        textid[4] = Create3DTextLabel(str,GREEN,0.0,0.0,0.0,15.0,0);
	    Attach3DTextLabelToVehicle(textid[4], Inf3, 0.0, 0.0, 0.0);
	    SetPlayerColor(playerid,0xFFFF00AA);
	    NPCNameShow = true;
	}
	else if(!strcmp(playername,"DrifterOff",true)) {
        PutPlayerInVehicle(playerid, Inf4, 0);
        SetSpawnInfo(playerid,0,115,1958.33,1343.12,15.36,269.15,0,0,0,0,0,0);
        //ShowPlayerMarkers(1);
        format(str,sizeof(str),"Drifter-OffControl(Rally)\n(ID:%d)",playerid);
        NPCIDs[5] = playerid;
        textid[5] = Create3DTextLabel(str,GREEN,0.0,0.0,0.0,15.0,0);
	    Attach3DTextLabelToVehicle(textid[5], Inf4, 0.0, 0.0, 0.0);
	    SetPlayerColor(playerid,0xFFFF00AA);
	    NPCNameShow = true;
	}
	else if(!strcmp(playername,"DrifterFM",true)) {
        PutPlayerInVehicle(playerid, Inf5, 0);
        SetSpawnInfo(playerid,0,115,1958.33,1343.12,15.36,269.15,0,0,0,0,0,0);
        //ShowPlayerMarkers(1);
        format(str,sizeof(str),"Drifter-FollowMe\n(ID:%d)",playerid);
        NPCIDs[6] = playerid;
        textid[6] = Create3DTextLabel(str,GREEN,0.0,0.0,0.0,15.0,0);
	    Attach3DTextLabelToVehicle(textid[6], Inf5, 0.0, 0.0, 0.0);
	    SetPlayerColor(playerid,0xFFFF00AA);
	    NPCNameShow = true;
	}
	else if(!strcmp(playername,"DrifterFM2",true)) {
        PutPlayerInVehicle(playerid, Inf6, 0);
        SetSpawnInfo(playerid,0,115,1958.33,1343.12,15.36,269.15,0,0,0,0,0,0);
        //ShowPlayerMarkers(1);
        format(str,sizeof(str),"Drifter-FollowMe2\n(ID:%d)",playerid);
        NPCIDs[7] = playerid;
        textid[7] = Create3DTextLabel(str,GREEN,0.0,0.0,0.0,15.0,0);
	    Attach3DTextLabelToVehicle(textid[7], Inf6, 0.0, 0.0, 0.0);
	    SetPlayerColor(playerid,0xFFFF00AA);
	    NPCNameShow = true;
	}
    return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	if (strcmp(SELECT_NPC_COMMAND, cmdtext, true) == 0)
	{
	    new content[2048];
		format(content,sizeof(content),"1.雷达站NPC\n\
										2.SF市区NPC\n\
										3.LS山区NPC\n\
										4.LS市区NPC\n\
										5.城市交界越野NPC\n\
										6.SF双环NPC\n\
										7.综合NPC - FollowMe\n\
										8.综合NPC - FollowMe2");
		ShowPlayerDialog(playerid, DIALOG_ID, DIALOG_STYLE_LIST, " 请选择一个NPC, 然后你将会被传送到相应的NPC的车上."\
																							, content, "确定", "取消" );
		return 1;
	}
	
	if (IsPlayerAdmin(playerid))
	{
	    if (strcmp(OPEN_NPC_NAME, cmdtext, true) == 0)
	    {
	        if (NPCNameShow)
	        {
				for (new i=0;i<sizeof(textid);i++)
				{
				    Delete3DTextLabel(textid[i]);
				}
				NPCNameShow = false;
				SendClientMessage(playerid,GREEN,"[提示:] NPC名称显示已关闭.");
	        } else {
	            new str[50];
	            
	            //Drifter-LDZ
	            format(str,sizeof(str),"Drifter-LDZ\n(ID:%d)",NPCIDs[0]);
		        textid[0] = Create3DTextLabel(str,GREEN,0.0,0.0,0.0,15.0,0);
			    Attach3DTextLabelToVehicle(textid[0], Bul, 0.0, 0.0, 0.0);
			    //Dirfter-SF Two Circles
			    format(str,sizeof(str),"Drifter-SF Two Circles\n(ID:%d)",NPCIDs[1]);
		        textid[1] = Create3DTextLabel(str,GREEN,0.0,0.0,0.0,15.0,0);
			    Attach3DTextLabelToVehicle(textid[1], Elegy, 0.0, 0.0, 0.0);
			    //Drifter-RunInMadd
       			format(str,sizeof(str),"Drifter-RunInMadd\n(ID:%d)",NPCIDs[2]);
		        textid[2] = Create3DTextLabel(str,GREEN,0.0,0.0,0.0,15.0,0);
			    Attach3DTextLabelToVehicle(textid[2], Inf1, 0.0, 0.0, 0.0);
			    //Drifter-LSEyeOut
       			format(str,sizeof(str),"Drifter-LSEyeOut\n(ID:%d)",NPCIDs[3]);
		        textid[3] = Create3DTextLabel(str,GREEN,0.0,0.0,0.0,15.0,0);
			    Attach3DTextLabelToVehicle(textid[3], Inf2, 0.0, 0.0, 0.0);
			    //Drifter-SFTestDrive
       			format(str,sizeof(str),"Drifter-SFTestDrive\n(ID:%d)",NPCIDs[4]);
		        textid[4] = Create3DTextLabel(str,GREEN,0.0,0.0,0.0,15.0,0);
			    Attach3DTextLabelToVehicle(textid[4], Inf3, 0.0, 0.0, 0.0);
			    //Drifter-OffControl(Rally)
       			format(str,sizeof(str),"Drifter-OffControl(Rally)\n(ID:%d)",NPCIDs[5]);
		        textid[5] = Create3DTextLabel(str,GREEN,0.0,0.0,0.0,15.0,0);
			    Attach3DTextLabelToVehicle(textid[5], Inf4, 0.0, 0.0, 0.0);
			    //Drifter-FM
       			format(str,sizeof(str),"Drifter-FollowMe\n(ID:%d)",NPCIDs[6]);
		        textid[6] = Create3DTextLabel(str,GREEN,0.0,0.0,0.0,15.0,0);
			    Attach3DTextLabelToVehicle(textid[6], Inf5, 0.0, 0.0, 0.0);
			    //Drifter-FM2
       			format(str,sizeof(str),"Drifter-FollowMe2\n(ID:%d)",NPCIDs[7]);
		        textid[7] = Create3DTextLabel(str,GREEN,0.0,0.0,0.0,15.0,0);
			    Attach3DTextLabelToVehicle(textid[7], Inf6, 0.0, 0.0, 0.0);
	            
	            NPCNameShow = true;
	            SendClientMessage(playerid,GREEN,"[提示:] NPC名称显示已开启.");
	        }
	        return 1;
	    }
	    
	    if (strcmp(SHOW_BOUNDS, cmdtext, true) == 0)
	    {
	        if (BoundsShow)
	        {
	            BoundsShow = false;
				EnableStuntBonusForAll(false);
				SendClientMessage(playerid,GREEN,"[提示:] 特技奖励已关闭.");
	        } else {
				BoundsShow = true;
				EnableStuntBonusForAll(true);
				SendClientMessage(playerid,GREEN,"[提示:] 特技奖励已开启.");
	        }
	        return 1;
	    }
	}
	return 0;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == DIALOG_ID)
	{
	    #if defined DEBUG
	        if (IsPlayerAdmin(playerid))
				SendClientMessage(playerid, GREEN, "[DEBUG] OnDialogResponse called.");
	    #endif
	    if (response)
	    {
		    #if defined DEBUG
		        if (IsPlayerAdmin(playerid))
					SendClientMessage(playerid, GREEN, "[DEBUG] OnDialogResponse - response = 1.");
		    #endif
	        switch (listitem)
	        {
	            case 0:
				{
    				#if defined DEBUG
		        	if (IsPlayerAdmin(playerid))
						SendClientMessage(playerid, GREEN, "[DEBUG] OnDialogResponse - listitem = 0.");
  					#endif
				    SetPlayerToNPCVehicle(playerid,Bul);
				}
    			case 1:
				{
					#if defined DEBUG
		        	if (IsPlayerAdmin(playerid))
						SendClientMessage(playerid, GREEN, "[DEBUG] OnDialogResponse - listitem = 1.");
  					#endif
				    SetPlayerToNPCVehicle(playerid,Inf3);
				}
     			case 2:
				{
					#if defined DEBUG
		        	if (IsPlayerAdmin(playerid))
						SendClientMessage(playerid, GREEN, "[DEBUG] OnDialogResponse - listitem = 2.");
  					#endif
				    SetPlayerToNPCVehicle(playerid,Inf1);
				}
				case 3:
				{
					#if defined DEBUG
		        	if (IsPlayerAdmin(playerid))
						SendClientMessage(playerid, GREEN, "[DEBUG] OnDialogResponse - listitem = 3.");
  					#endif
				    SetPlayerToNPCVehicle(playerid,Inf2);
				}
				case 4:
				{
					#if defined DEBUG
		        	if (IsPlayerAdmin(playerid))
						SendClientMessage(playerid, GREEN, "[DEBUG] OnDialogResponse - listitem = 4.");
  					#endif
				    SetPlayerToNPCVehicle(playerid,Inf4);
				}
				case 5:
				{
					#if defined DEBUG
		        	if (IsPlayerAdmin(playerid))
						SendClientMessage(playerid, GREEN, "[DEBUG] OnDialogResponse - listitem = 5.");
  					#endif
				    SetPlayerToNPCVehicle(playerid,Elegy);
				}
				case 6:
				{
					#if defined DEBUG
		        	if (IsPlayerAdmin(playerid))
						SendClientMessage(playerid, GREEN, "[DEBUG] OnDialogResponse - listitem = 6.");
  					#endif
				    SetPlayerToNPCVehicle(playerid,Inf5);
				}
				case 7:
				{
					#if defined DEBUG
		        	if (IsPlayerAdmin(playerid))
						SendClientMessage(playerid, GREEN, "[DEBUG] OnDialogResponse - listitem = 7.");
  					#endif
				    SetPlayerToNPCVehicle(playerid,Inf6);
				}
	        }
	    }
	}
    return true;
}

public SetPlayerToNPCVehicle(playerid,vehicleid)
{
	#if defined DEBUG
	if (IsPlayerAdmin(playerid))
		SendClientMessage(playerid, GREEN, "[DEBUG] SetPlayerToNPCVehicle called.");
	#endif
	if (IsPlayerInVehicle(playerid,vehicleid)) return SendClientMessage(playerid,RED,"[错误:] 你已经在相应的NPC的车上了.");
	new result;
	enum piEn { name[MAX_PLAYER_NAME], id };
	new pi[piEn];
	for (new i=0;i<MAX_PLAYERS;i++)
	{
		if (IsPlayerConnected(i) && !IsPlayerNPC(i))
		{
		    if (i != playerid)
		    {
				if (IsPlayerInVehicle(i,vehicleid))
				{
				    result = 1;
				    pi[id] = i;
				    GetPlayerName(i, pi[name], sizeof(pi[name]));
			    	#if defined DEBUG
					if (IsPlayerAdmin(playerid))
						SendClientMessage(playerid, GREEN, "[DEBUG] SetPlayerToNPCVehicle - name geted.");
					#endif
				    break;
				} else {
					result = 0;
    				#if defined DEBUG
					if (IsPlayerAdmin(playerid))
						SendClientMessage(playerid, GREEN, "[DEBUG] SetPlayerToNPCVehicle - name not geted.");
					#endif
				}
			}
		}
	}
	if (result)
	{
		#if defined DEBUG
		if (IsPlayerAdmin(playerid))
			SendClientMessage(playerid, GREEN, "[DEBUG] SetPlayerToNPCVehicle - result = 1.");
		#endif
		new str[128];
		format(str,sizeof(str),"[错误:] 指定的NPC的车上已经有乘客了,该乘客是%s(%d),使用/tv并选择该乘客的ID也可以看NPC.", pi[name], pi[id]);
		return SendClientMessage(playerid,RED,str);
	} else {
		#if defined DEBUG
		if (IsPlayerAdmin(playerid))
			SendClientMessage(playerid, GREEN, "[DEBUG] SetPlayerToNPCVehicle - result = 0.");
		#endif
		PutPlayerInVehicle(playerid, vehicleid, 1);
		SendClientMessage(playerid,GREEN,"[提示:] 传送成功, 按F下车即可离开NPC车辆.");
	}
	return 1;
}
