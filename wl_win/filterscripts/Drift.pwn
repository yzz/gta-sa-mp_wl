////////////////////////////////////////////////////////////
/////////////// DRIFT POINTS COUNTER BY LUBY ///////////////
/////////////// A little editted by Abhinav,yezizhu/////////
////////////////////////////////////////////////////////////

#include <a_samp> // by I dont know .. :D lol
#include <zcmd>

#define DRIFT_MINKAT 10.0 // by Luby
#define DRIFT_MAXKAT 90.0 // by Luby
#define DRIFT_SPEED 30.0 // by Luby

//////////// Added by Abhinav///////
#define COLOR_Label 0xFFFFFFFF
#define COLOR_LabelOut 0x00000040
#define COLOR_ValueOut 0xFFFFFF40
#define COLOR_Value 0x000000FF

#define Label_X 500
#define Value_X 500
#define TD_Y 100
/////////////////////////////////////
AntiDeAMX()
{
    new a[][] =
    {
        "Unarmed (Fist)",
        "Brass K"
    };
    #pragma unused a
}

new DriftTimer[MAX_PLAYERS]; // Added by Abhinav
new TimerA,TimerB,TimerC; // Added by Abhinav

new DriftPointsNow[MAX_PLAYERS]; // by Luby
new PlayerDriftCancellation[MAX_PLAYERS]; // by Luby
new Float:ppos[MAX_PLAYERS][3]; // by Luby
enum Float:Pos{ Float:sX,Float:sY,Float:sZ }; // by Luby
new Float:SavedPos[MAX_PLAYERS][Pos]; // by Luby

new bool:DriftMode[MAX_PLAYERS]=false; // Added by Abhinav
new DriftBonus[MAX_PLAYERS]=1; // Added by Abhinav
new Float:HealthInit[MAX_PLAYERS]=1000.0; // Added by Abhinav
new bool:AutoFixBool[MAX_PLAYERS]=true; // Added by Abhinav

new Text:TDLabels[3]; // Added by Abhinav
new Text:TDValueDrift[MAX_PLAYERS]; // Added by Abhinav
new Text:TDValueBonus[MAX_PLAYERS]; // Added by Abhinav
new Text:TDValueCash[MAX_PLAYERS]; // Added by Abhinav

forward Drift(); // by Luby
forward AngleUpdate(); // by Luby
forward DriftExit(playerid); // by Luby
forward CheckPlayerState(); // Added by Abhinav

public OnFilterScriptInit(){
		AntiDeAMX();
        TimerA=SetTimer("AngleUpdate", 211, true); // by Luby
        TimerC=SetTimer("CheckPlayerState", 101, true); //by Abhinav
        LoadTextDraws();
		print("====Drint point system loaded");
        return 1;
}

public OnFilterScriptExit(){
	KillTimer(TimerA);
	KillTimer(TimerB);
	KillTimer(TimerC);
	print("====Drint point system unloaded");
	return 1;
}

Float:GetPlayerTheoreticAngle(i) // By Luby
{
        new Float:sin;
        new Float:dis;
        new Float:angle2;
        new Float:x,Float:y,Float:z;
        new Float:tmp3;
        new Float:tmp4;
        new Float:MindAngle;
        
        if(IsPlayerConnected(i)){
        
                GetPlayerPos(i,x,y,z);
                
                dis = floatsqroot(floatpower(floatabs(floatsub(x,ppos[i][0])),2)+floatpower(floatabs(floatsub(y,ppos[i][1])),2));
                
                if(IsPlayerInAnyVehicle(i)){GetVehicleZAngle(GetPlayerVehicleID(i), angle2);}else{GetPlayerFacingAngle(i, angle2);}
                
                if(x>ppos[i][0]){tmp3=x-ppos[i][0];}else{tmp3=ppos[i][0]-x;}
                if(y>ppos[i][1]){tmp4=y-ppos[i][1];}else{tmp4=ppos[i][1]-y;}
                
                if(ppos[i][1]>y && ppos[i][0]>x){
                	sin = asin(tmp3/dis);
                    MindAngle = floatsub(floatsub(floatadd(sin, 90), floatmul(sin, 2)), -90.0);
                }
                
                if(ppos[i][1]<y && ppos[i][0]>x){
                    sin = asin(tmp3/dis);
                    MindAngle = floatsub(floatadd(sin, 180), 180.0);
                }
                
                if(ppos[i][1]<y && ppos[i][0]<x){
                    sin = acos(tmp4/dis);
                    MindAngle = floatsub(floatadd(sin, 360), floatmul(sin, 2));
                }
                
                if(ppos[i][1]>y && ppos[i][0]<x){
                    sin = asin(tmp3/dis);
                    MindAngle = floatadd(sin, 180);
                }
        }
        
        if(MindAngle == 0.0){return angle2;}else{return MindAngle;}
}

public DriftExit(playerid){ // By Luby
        PlayerDriftCancellation[playerid] = 0;
        
		 ////////////////// by Abhinav ///////////////////
        new Float:h;
        GetVehicleHealth(GetPlayerVehicleID(playerid),h);
        if(/*DriftPointsNow[playerid]>70 && DriftPointsNow[playerid]<10000 &&*/ h==HealthInit[playerid]) GivePlayerMoney(playerid,DriftPointsNow[playerid]*DriftBonus[playerid]);

        DriftBonus[playerid]=1;
        AutoFixBool[playerid]=true;
       // SetVehicleHealth(GetPlayerVehicleID(playerid),HealthInit[playerid]);
        ////////////////////////////////////////////////////
		SetPVarInt(playerid,"i_driftpoint_pointsold",DriftPointsNow[playerid]);
		new
			DPs[64];
		valstr(DPs,GetPVarInt(playerid,"i_driftpoint_pointsold"),false);
		TextDrawSetString(TDValueDrift[playerid],DPs);
		TextDrawSetString(TDValueBonus[playerid],"X0");
		TextDrawSetString(TDValueCash[playerid],"$0");
        DriftPointsNow[playerid] = 0;
}

Float:ReturnPlayerAngle(playerid){ // By Luby
        new Float:Ang;
        if(IsPlayerInAnyVehicle(playerid))GetVehicleZAngle(GetPlayerVehicleID(playerid), Ang); else GetPlayerFacingAngle(playerid, Ang);
        return Ang;
}

public Drift(){ // By Luby
        new Float:Angle1, Float:Angle2, Float:BySpeed;
        new Float:Z;
        new Float:X;
        new Float:Y;
        new Float:SpeedX;
        for(new g=0;g<200;g++){
                GetPlayerPos(g, X, Y, Z);
                SpeedX = floatsqroot(floatadd(floatadd(floatpower(floatabs(floatsub(X,SavedPos[ g ][ sX ])),2),floatpower(floatabs(floatsub(Y,SavedPos[ g ][ sY ])),2)),floatpower(floatabs(floatsub(Z,SavedPos[ g ][ sZ ])),2)));
                Angle1 = ReturnPlayerAngle(g);
                Angle2 = GetPlayerTheoreticAngle(g);
                BySpeed = floatmul(SpeedX, 12);
                if(IsPlayerInAnyVehicle(g) && GetVType(GetPlayerVehicleID(g)) && floatabs(floatsub(Angle1, Angle2)) > DRIFT_MINKAT && floatabs(floatsub(Angle1, Angle2)) < DRIFT_MAXKAT && BySpeed > DRIFT_SPEED){
                        if(PlayerDriftCancellation[g] > 0)KillTimer(PlayerDriftCancellation[g]);
                        PlayerDriftCancellation[g] = 0;
                        DriftPointsNow[g] += floatval( floatabs(floatsub(Angle1, Angle2)) * 3 * (BySpeed*0.1) )/10;
                        PlayerDriftCancellation[g] = SetTimerEx("DriftExit", 3000, 0, "d", g);
                }
                
                if(DriftPointsNow[g] > 70 && DriftPointsNow[g]<10000){
                    ///////////// by Abhinav ////////////////////
                    if(DriftPointsNow[g]<200){
                        DriftBonus[g]=1;
					}
					if(DriftPointsNow[g]>=200 && DriftPointsNow[g]<500){
                        DriftBonus[g]=2;
					}
                    if(DriftPointsNow[g]>=500 && DriftPointsNow[g]<1000){
                        DriftBonus[g]=3;
					}
					if(DriftPointsNow[g]>=1000 && DriftPointsNow[g]<1500){
                        DriftBonus[g]=4;
					}
					if(DriftPointsNow[g]>=1500){
                        DriftBonus[g]=5;
					}
					/*
					TextDrawShowForPlayer(g,TDLabels[0]);
					TextDrawShowForPlayer(g,TDLabels[1]);
					TextDrawShowForPlayer(g,TDLabels[2]);
					
	                TextDrawShowForPlayer(g,TDValueDrift[g]);
	                TextDrawShowForPlayer(g,TDValueBonus[g]);
	                TextDrawShowForPlayer(g,TDValueCash[g]);
	                */
	                new DPs[128],DBn[128],Cash[128],csh;
	                
	                valstr(DPs,DriftPointsNow[g],false);
	                format(DBn,sizeof(DBn),"X%i",DriftBonus[g]);
	                csh=DriftPointsNow[g]*DriftBonus[g];
	                format(Cash,sizeof(Cash),"$%i",csh);
	                
                    TextDrawSetString(TDValueDrift[g],DPs);
                    TextDrawSetString(TDValueBonus[g],DBn);
                    TextDrawSetString(TDValueCash[g],Cash);
					////////////////////////////////////////
                }
                SavedPos[ g ][ sX ] = X;
                SavedPos[ g ][ sY ] = Y;
                SavedPos[ g ][ sZ ] = Z;
        }
}

public AngleUpdate(){ // By Luby
        for(new g=0;g<=MAX_PLAYERS;g++){
				if(GetPVarInt(g,"i_driftpoint_DriftMode") == -1) continue;
                new Float:x, Float:y, Float:z;
                if(IsPlayerInAnyVehicle(g))GetVehiclePos(GetPlayerVehicleID(g), x, y, z); else GetPlayerPos(g, x, y, z);
                ppos[g][0] = x;
                ppos[g][1] = y;
                ppos[g][2] = z;
        }
}

floatval(Float:val){ // By Luby
        new str[256];
        format(str, 256, "%.0f", val);
        return todec(str);
}

todec(str[]){ // By Luby
        return strval(str);
}

LoadTextDraws(){ // by Abhinav
	TDLabels[0]=TextDrawCreate(Label_X,TD_Y,"Drift Points");
	TextDrawColor(TDLabels[0],COLOR_Label);
	TextDrawSetShadow(TDLabels[0],0);
	TextDrawSetOutline(TDLabels[0],1);
	TextDrawLetterSize(TDLabels[0],0.5,2);
	TextDrawBackgroundColor(TDLabels[0],COLOR_LabelOut);
	TextDrawFont(TDLabels[0],1);
	
	TDLabels[1]=TextDrawCreate(Label_X,TD_Y+50,"Drift Bonus");
	TextDrawColor(TDLabels[1],COLOR_Label);
	TextDrawSetShadow(TDLabels[1],0);
	TextDrawSetOutline(TDLabels[1],1);
	TextDrawLetterSize(TDLabels[1],0.5,2);
	TextDrawBackgroundColor(TDLabels[1],COLOR_LabelOut);
	TextDrawFont(TDLabels[1],1);
	
	TDLabels[2]=TextDrawCreate(Label_X,TD_Y+100,"Drift Cash");
	TextDrawColor(TDLabels[2],COLOR_Label);
	TextDrawSetShadow(TDLabels[2],0);
	TextDrawSetOutline(TDLabels[2],1);
	TextDrawLetterSize(TDLabels[2],0.5,2);
	TextDrawBackgroundColor(TDLabels[2],COLOR_LabelOut);
	TextDrawFont(TDLabels[2],1);
	
	new i;
	for(i=0;i<=MAX_PLAYERS;i++){
		TDValueDrift[i]=TextDrawCreate(Value_X,TD_Y+20,"0");
		TextDrawColor(TDValueDrift[i],COLOR_Value);
		TextDrawSetShadow(TDValueDrift[i],0);
		TextDrawSetOutline(TDValueDrift[i],1);
		TextDrawLetterSize(TDValueDrift[i],0.5,2);
		TextDrawBackgroundColor(TDValueDrift[i],COLOR_ValueOut);
		TextDrawFont(TDValueDrift[i],3);
		
		TDValueBonus[i]=TextDrawCreate(Value_X,TD_Y+70,"X1");
		TextDrawColor(TDValueBonus[i],COLOR_Value);
		TextDrawSetShadow(TDValueBonus[i],0);
		TextDrawSetOutline(TDValueBonus[i],1);
		TextDrawLetterSize(TDValueBonus[i],0.5,2);
		TextDrawBackgroundColor(TDValueBonus[i],COLOR_ValueOut);
		TextDrawFont(TDValueBonus[i],3);
		
		TDValueCash[i]=TextDrawCreate(Value_X,TD_Y+120,"$0");
		TextDrawColor(TDValueCash[i],COLOR_Value);
		TextDrawSetShadow(TDValueCash[i],0);
		TextDrawSetOutline(TDValueCash[i],1);
		TextDrawLetterSize(TDValueCash[i],0.5,2);
		TextDrawBackgroundColor(TDValueCash[i],COLOR_ValueOut);
		TextDrawFont(TDValueCash[i],3);
	}
	
	return 1;
}

public CheckPlayerState(){ //by Abhinav
	new i,cs;

	for(i=0;i<=MAX_PLAYERS;i++){
		if(GetPVarInt(i,"i_driftpoint_DriftMode") == -1) continue;
	    cs=GetPlayerState(i);
	    if(DriftMode[i] && cs==PLAYER_STATE_DRIVER && DriftPointsNow[i]>70){
	        new Float:h;
	        GetVehicleHealth(GetPlayerVehicleID(i),h);
	        if(h<HealthInit[i]){
	        	KillTimer(DriftTimer[i]);
	        	DriftExit(i);
	        	GameTextForPlayer(i,"~n~~n~~n~~n~~n~~n~~n~~r~Boom",800,5);
	        	DriftMode[i]=false;
			}
		}
	    if(cs==PLAYER_STATE_DRIVER && DriftMode[i]==false){
	        if(GetPVarInt(i,"i_driftpoint_DriftMode") == 1){
				if(GetVType(GetPlayerVehicleID(i))){
					DriftMode[i]=true;
					GetVehicleHealth(GetPlayerVehicleID(i),HealthInit[i]);
					AutoFixBool[i]=false;
					DriftTimer[i]=SetTimerEx("Drift", 200, true, "i", i);

				}
			}else SetPVarInt(i,"i_driftpoint_DriftMode",-1);
		}
		else if(cs!=PLAYER_STATE_DRIVER && DriftMode[i]==true){
		    KillTimer(DriftTimer[i]);
		    DriftMode[i]=false;
		    AutoFixBool[i]=true;
		}
		else{}
	}
	return 1;
}


GetVType(vid){ // By Abhinav
	
	new Convertibles[4]={480, 533, 439, 555};
	new Industrial[26]={499, 422, 482, 498, 609, 524, 578, 455, 403, 414, 582, 443, 514, 413, 515, 440, 543, 605, 459, 531, 408, 552, 478, 456, 554};
	new LowRider[8]={536, 575, 534, 567, 535, 566, 576, 412};
	new OffRoad[13]={568, 424, 573, 579, 400, 500, 444, 556, 557, 470, 489, 505, 595};
	new Service[19]={416, 433, 431, 438, 437, 523, 427, 490, 528, 407, 544, 596, 596, 597, 598, 599, 432, 601, 420};
	new Saloon[35]={445, 504, 401, 518, 527, 542, 507, 562, 585, 419, 526, 604, 466, 492, 474, 546, 517, 410, 551, 516, 467, 600, 426, 436, 547, 405, 580, 560, 550, 549, 540, 491, 529, 421};
	new Sports[20]={602, 429, 496, 402, 541, 415, 589, 587, 565, 494, 502, 503, 411, 559, 603, 475, 506, 451, 558, 477};
	new Wagons[5]={418, 404, 479, 458, 561};
	
	new modelid=GetVehicleModel(vid);
	new i;
	for(i=0;i<3;i++){
		    if(Convertibles[i]==modelid) return 1;
	}
	for(i=0;i<25;i++){
		    if(Industrial[i]==modelid) return 1;
	}
	for(i=0;i<7;i++){
		    if(LowRider[i]==modelid) return 1;
	}
	for(i=0;i<12;i++){
		    if(OffRoad[i]==modelid) return 1;
	}
	for(i=0;i<19;i++){
		    if(Service[i]==modelid) return 1;
	}
	for(i=0;i<35;i++){
		    if(Saloon[i]==modelid) return 1;
	}
	for(i=0;i<20;i++){
		    if(Sports[i]==modelid) return 1;
	}
	for(i=0;i<5;i++){
		    if(Wagons[i]==modelid) return 1;
	}
	return 0;
}


zcmd(drift,playerid,params[]){
	if(isnull(params)){
		SendClientMessage(playerid,0x33AA33AA,"[漂移系统]==========================漂移系统介绍===============================");
		SendClientMessage(playerid,0x33AA33AA,"[漂移系统]/drift on - 开启漂移系统  ||  /drift off - 关闭漂移系统");
		SendClientMessage(playerid,0x33AA33AA,"[漂移系统]/drift [玩家ID] - 查看玩家最近的漂移成绩");
		SendClientMessage(playerid,0x33AA33AA,"[漂移系统]/drift help - 查看漂移系统帮助");
		SendClientMessage(playerid,0x33AA33AA,"[漂移系统]=========================================================");
	}
	else if(!strcmp("help",params,true)){
		SendClientMessage(playerid,0x33AA33AA,"[漂移系统]==========================漂移系统介绍===============================");
		SendClientMessage(playerid,0x33AA33AA,"[漂移系统]/drift on - 开启漂移系统  ||  /drift off - 关闭漂移系统");
		SendClientMessage(playerid,0x33AA33AA,"[漂移系统]/drift [玩家ID] - 查看玩家最近的漂移成绩");
		SendClientMessage(playerid,0x33AA33AA,"[漂移系统]/drift help - 查看漂移系统帮助");
		SendClientMessage(playerid,0x33AA33AA,"[漂移系统]=========================================================");
	}
	else if(!strcmp("on",params,true)){
		SetPVarInt(playerid,"i_driftpoint_DriftMode",1);
		TextDrawShowForPlayer(playerid,TDLabels[0]);
		TextDrawShowForPlayer(playerid,TDLabels[1]);
		TextDrawShowForPlayer(playerid,TDLabels[2]);
		TextDrawShowForPlayer(playerid,TDValueDrift[playerid]);
		TextDrawShowForPlayer(playerid,TDValueBonus[playerid]);
		TextDrawShowForPlayer(playerid,TDValueCash[playerid]);
		SendClientMessage(playerid,0x33AA33AA,"[漂移系统]你打开了drift point 系统,输入/drift off可以关闭");
		SendClientMessage(playerid,0x33AA33AA,"[漂移系统]注意:网络环境较差时慎用漂移系统");
	}
	else if(!strcmp("off",params,true)){
		SetPVarInt(playerid,"i_driftpoint_DriftMode",0);
		DriftMode[playerid]=false;
		AutoFixBool[playerid]=true;
		KillTimer(DriftTimer[playerid]);
		DriftExit(playerid);
        TextDrawHideForPlayer(playerid,TDLabels[0]);
        TextDrawHideForPlayer(playerid,TDLabels[1]);
        TextDrawHideForPlayer(playerid,TDLabels[2]);
        TextDrawHideForPlayer(playerid,TDValueDrift[playerid]);
        TextDrawHideForPlayer(playerid,TDValueBonus[playerid]);
        TextDrawHideForPlayer(playerid,TDValueCash[playerid]);
		SendClientMessage(playerid,0x33AA33AA,"[漂移系统]你关闭了drift point 系统,输入/drift on可以打开");
	}
	else{
		new
			id = strval(params);
		if(IsPlayerConnected(id) && GetPVarInt(id,"i_driftpoint_DriftMode") == 1){
			new
				tmpstr[128];
			GetPlayerName(id,tmpstr,sizeof(tmpstr));
			format(tmpstr,sizeof(tmpstr),"[漂移系统]玩家'%s(%d)'最近的漂移成绩:%d分",tmpstr,id,GetPVarInt(id,"i_driftpoint_pointsold"));
			SendClientMessage(playerid,0x33AA33AA,tmpstr);
		}else{
			SendClientMessage(playerid,0x33AA33AA,"[漂移系统]该玩家没有开启漂移模式");
		}
	}
	return true;
}
pzcmd(d) 	rzcmd(drift);
public OnPlayerCommandText(playerid,cmdtext[]){
	if(ZCMD_ProcessCommand(playerid,cmdtext))return true;
	return false;
}
