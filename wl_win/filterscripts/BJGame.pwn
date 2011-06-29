#include <a_samp>
#define LOOP(%1,%2) for(new %1; %1<%2;%1++)

#define COLOR_YELLOW    0xFFFF00AA

forward DeleteGame(gameid); //Game[gameid][4]
forward CreateGame();
forward UpdateGame(gameid); //sets textdraws
forward CloseWindow(playerid); //Closes the game window

PlayerNearPlayer(player1,player2,Float:distance)
{
	new Float:tmp[2][3];
	GetPlayerPos(player1,tmp[0][0],tmp[0][1],tmp[0][2]);
	GetPlayerPos(player2,tmp[1][0],tmp[1][1],tmp[1][2]);
	return ((((tmp[1][0]-tmp[0][0])*(tmp[1][0]-tmp[0][0]))+((tmp[1][1]-tmp[0][1])*(tmp[1][1]-tmp[0][1]))+((tmp[1][2]-tmp[0][2])*(tmp[1][2]-tmp[0][2])))<distance*distance);
}

GiveCardName(card,name[],size = sizeof(name))
{
	new face = (card/4)+1; // Ace = 1, Jack = 11, Queen = 12, King = 13
	new suit = card - ((card/4)*4); // Hearts = 0, Clubs = 1, Diamonds = 2, Spades = 3
	switch(face)
	{
	    case 1: format(name,size,"Ace of ");
	    case 11: format(name,size,"Jack of ");
	    case 12: format(name,size,"Queen of ");
	    case 13: format(name,size,"King of ");
	    default: format(name,size,"%d of ",face);
	}
	switch(suit)
	{
	    case 0: format(name,size,"%s~r~Hearts~w~",name);
	    case 1: format(name,size,"%s~p~Clubs~w~",name);
	    case 2: format(name,size,"%s~r~Diamonds~w~",name);
	    case 3: format(name,size,"%s~p~Spades~w~",name);
	}
}

new Game[100][5]; // Half of MAX_PLAYERS -- 4 being maximum players per game, 5 = The Bet Placed
new GameStep[100]; //0 = game not created, 1 = game created, 2 = looking for players, 3 = game started and cards given out, 4 = player 1's turn, 5 = player 2's turn, 6 = player 3's turn, 7 = players 4's turn
new PlayerGamePosition[MAX_PLAYERS]; // Gives the position of the player
new PlayerGame[MAX_PLAYERS]; // Gives the gameid that the player is in
new GameCards[100][52]; // Each game has a deck of 52, the value of each card is the player's position
new Text:GameText[MAX_PLAYERS][5]; //MAX_PLAYERS times 5 equals 1000, MAX_TEXTDRAWS equals 1024
new PlayerHolding[MAX_PLAYERS];
new PlayerInviting[MAX_PLAYERS];
new PlayerCards[MAX_PLAYERS][5]; // The order of the cards received
new Text:null;

public DeleteGame(gameid)
{
	LOOP(playerid,4)
	{
	    if(Game[gameid][playerid]>-1)
	    {
			PlayerGame[Game[gameid][playerid]]=-1;
			PlayerGamePosition[Game[gameid][playerid]]=-1;
			PlayerHolding[Game[gameid][playerid]]=0;
			PlayerInviting[Game[gameid][playerid]]=-1;
			ClearAnimations(playerid);
			LOOP(loop,5)PlayerCards[Game[gameid][playerid]][loop]=-1;
	    }
	    Game[gameid][playerid]=-1;
	}
	LOOP(card,52)GameCards[gameid][card]=-1;
	GameStep[gameid]=0;
	return 1;
}
public CloseWindow(playerid)
{
	LOOP(text,5)
	{
	    if(_:GameText[playerid][text]){TextDrawDestroy(GameText[playerid][text]);GameText[playerid][text]=Text:INVALID_TEXT_DRAW;}
	}
	return 1;
}

public CreateGame()
{
	//Find an open game
	new gameid;
	LOOP(loop,100)if(!GameStep[loop]){gameid=loop;break;}
	GameStep[gameid]=1;
	return gameid;
}

public UpdateGame(gameid)
{
	new OVER;
	LOOP(player,4)
	{
	    if(Game[gameid][player]>-1)
	    {
     		new playerid = Game[gameid][player];
			ApplyAnimation(playerid,"WUZI","Wuzi_stand_loop",4,1,0,0,1,0);
			ApplyAnimation(playerid,"WUZI","Wuzi_stand_loop",4,1,0,0,1,0);
			//For adding new players
	        if((GameText[playerid][0]==Text:INVALID_TEXT_DRAW)||!_:GameText[playerid][0])
	        {
				GameText[playerid][0] = TextDrawCreate(320,120,"~y~Player Slot 1~n~~w~");
		        TextDrawUseBox(GameText[playerid][0],1);
		        TextDrawBoxColor(GameText[playerid][0],0x00000077);
		        TextDrawAlignment(GameText[playerid][0],2);
		        TextDrawShowForPlayer(playerid,GameText[playerid][0]);
			}
	        if((GameText[playerid][1]==Text:INVALID_TEXT_DRAW)||!_:GameText[playerid][1])
	        {
				GameText[playerid][1] = TextDrawCreate(320,145,"~y~Player Slot 2~n~~w~");
		        TextDrawUseBox(GameText[playerid][1],1);
		        TextDrawBoxColor(GameText[playerid][1],0x00000077);
		        TextDrawAlignment(GameText[playerid][1],2);
		        TextDrawShowForPlayer(playerid,GameText[playerid][1]);
			}
	        if((GameText[playerid][2]==Text:INVALID_TEXT_DRAW)||!_:GameText[playerid][2])
	        {
				GameText[playerid][2] = TextDrawCreate(320,170,"~y~Player Slot 3~n~~w~");
		        TextDrawUseBox(GameText[playerid][2],1);
		        TextDrawBoxColor(GameText[playerid][2],0x00000077);
		        TextDrawAlignment(GameText[playerid][2],2);
		        TextDrawShowForPlayer(playerid,GameText[playerid][2]);
			}
	        if((GameText[playerid][3]==Text:INVALID_TEXT_DRAW)||!_:GameText[playerid][3])
	        {
				GameText[playerid][3] = TextDrawCreate(320,194.5,"~y~Player Slot 4~n~~w~");
		        TextDrawUseBox(GameText[playerid][3],1);
		        TextDrawBoxColor(GameText[playerid][3],0x00000077);
		        TextDrawAlignment(GameText[playerid][3],2);
		        TextDrawShowForPlayer(playerid,GameText[playerid][3]);
			}
	        if((GameText[playerid][4]==Text:INVALID_TEXT_DRAW)||!_:GameText[playerid][4])
	        {
				GameText[playerid][4] = TextDrawCreate(320,219,"~y~Scores");
		        TextDrawUseBox(GameText[playerid][4],1);
		        TextDrawBoxColor(GameText[playerid][4],0x00000077);
		        TextDrawAlignment(GameText[playerid][4],2);
		        TextDrawShowForPlayer(playerid,GameText[playerid][4]);
			}

			//Setting Textdraws appropriately
			new string[5][256]; // I believe 256 to be the largest a string can be for textdraws
			new cardname[30];
			LOOP(loop,4)
			{
			    if(Game[gameid][loop]>=0)
			    {
					GetPlayerName(Game[gameid][loop],string[loop],sizeof(string[]));
					format(string[loop],sizeof(string[]),"~y~%s~n~~w~",string[loop]);
					//Check Cards and Name Them
					LOOP(cards,5)
					{
						if(PlayerCards[Game[gameid][loop]][cards]>-1)
						{
						    GiveCardName(PlayerCards[Game[gameid][loop]][cards],cardname);
						    if(Game[gameid][loop]==playerid)format(string[loop],sizeof(string[]),"%s: %s ",string[loop],cardname);
						    else if(GameStep[gameid]>=8)format(string[loop],sizeof(string[]),"%s: %s ",string[loop],cardname);
						    else if((GameCards[gameid][PlayerCards[Game[gameid][loop]][cards]]-(GameCards[gameid][PlayerCards[Game[gameid][loop]][cards]]/5)*5)==0)format(string[loop],sizeof(string[]),"%s: %s ",string[loop],cardname);
						    else if(GameStep[gameid]<8)format(string[loop],sizeof(string[]),"%s: ~r~??~w~ ",string[loop]);
						    else if(GameStep[gameid]>=8)format(string[loop],sizeof(string[]),"%s: %s ",string[loop],cardname);
						}
					}
					format(string[loop],sizeof(string[]),"%s :",string[loop]);
				}
				else
				{
				    format(string[loop],sizeof(string[]),"~y~Player Slot %d~n~~w~",loop);
				}

				TextDrawSetString(GameText[playerid][loop],string[loop]);
			}
			if(GameStep[gameid]==2)
			{
			    format(string[4],sizeof(string[]),"Waiting For Players");
			    if(Game[gameid][1]>-1)
				{
				    if(Game[gameid][0]==playerid)
				    {
					    GetPlayerName(Game[gameid][0],string[4],sizeof(string[]));
	                    format(string[4],sizeof(string[]),"%s -- Press ~k~~PED_FIREWEAPON~ to begin game.",string[4]);
						SendClientMessage(Game[gameid][player],COLOR_YELLOW,"[21点]按LMB(鼠标左键开始)");
						//SendClientMessage(Game[gameid][loop2],COLOR_YELLOW,string[4]);
					}else{
					    GetPlayerName(Game[gameid][0],string[4],sizeof(string[]));
	                    format(string[4],sizeof(string[]),"Waiting for %s to start the game.",string[4]);
						SendClientMessage(Game[gameid][player],COLOR_YELLOW,"[21点]等待发起者开始");
					}
				}
				TextDrawSetString(GameText[playerid][4],string[4]);
			}
			//Give each player 2 cards then set to dealer's turn to hit/stay
			if(GameStep[gameid]==3)
			{
					LOOP(loop,2)
					{
						if(Game[gameid][player]>-1)
						{

							CardLabel:
							new tmp = random(52);
							if(GameCards[gameid][tmp]>=0)goto CardLabel;
							LOOP(cards,5)
							{
							    if(PlayerCards[Game[gameid][player]][cards]==-1)
							    {
									GameCards[gameid][tmp]=player*5+cards;
									PlayerCards[Game[gameid][player]][cards]=tmp;
							        break;
							    }
							}
						}
					}
			}
			//Everyone takes turns, 4 = 0, 5 = 1, 6 = 2, 7 = 3
			if(GameStep[gameid]==4)
			{
			    new winners[4];
			    new won;
			    string[4]="";
				LOOP(loop,4)
				{
				    if(Game[gameid][loop]>-1)
				    {
					    new tmpstring2[64];
					    if(PlayerCards[Game[gameid][loop]][2]==-1)
					    {
				   			new tmp;
				   			if(PlayerCards[Game[gameid][loop]][0]/4==0)tmp+=11;
				   			if(PlayerCards[Game[gameid][loop]][1]/4==0)tmp+=11;
				   			if(PlayerCards[Game[gameid][loop]][1]/4>=9)tmp+=10;
				   			if(PlayerCards[Game[gameid][loop]][0]/4>=9)tmp+=10;
					        if(tmp==21){tmpstring2="Black Jack";winners[loop]=1;won=1;} //Won by instant blackjack
					    }else if(PlayerCards[Game[gameid][loop]][4]>-1)
					    {
					        new tmp;
					        LOOP(loop2,5)if(PlayerCards[Game[gameid][loop]][loop2]>-1)if((PlayerCards[Game[gameid][loop]][loop2]/4)+1>10)tmp+=10;else tmp+=((PlayerCards[Game[gameid][loop]][loop2]/4)+1);
					        if(tmp<=21){tmpstring2="5 Card Jimmy";winners[loop]=2;won=1;} //Won by 5 card jimmy
					    }else
					    {
					        new tmp;
					        new tmp2;
					        LOOP(loop2,5)
					        {
					            if(PlayerCards[Game[gameid][loop]][loop2]>-1)
					            {
						            if((PlayerCards[Game[gameid][loop]][loop2]/4)+1>=10)
						            {
										tmp+=10;
										tmp2+=10;
						            }else if(PlayerCards[Game[gameid][loop]][loop2]/4==0)
						            {
						                if(tmp!=tmp2)tmp2+=1;
						                else tmp2+=11;
						                tmp+=1;
						            }else {tmp+=(PlayerCards[Game[gameid][loop]][loop2]/4)+1; tmp2+=(PlayerCards[Game[gameid][loop]][loop2]/4)+1;}
					            }
					        }
					        if((tmp==21)||(tmp2==21)) //Won by standard black jack

					        {
					            tmpstring2="Black Jack";
					            winners[loop]=1;
					            won++;
					        }
					    }
					    new tmpstring[24];
					    GetPlayerName(Game[gameid][loop],tmpstring,sizeof(tmpstring));
				        if(winners[loop])
						{
							format(string[4],sizeof(string[]),"%s~n~%s won by %s!",string[4],tmpstring,tmpstring2);
						}
			        }
				}
				if(won)
				{
					format(string[4],sizeof(string[]),"Game Over!~n~%s",string[4]);
				    TextDrawSetString(GameText[playerid][4],string[4]);
					if(winners[PlayerGamePosition[playerid]])
					{
						GetPlayerName(playerid,string[4],sizeof(string[]));
						new tmp;LOOP(loop,4)if(Game[gameid][loop]>-1)tmp++;
				  		format(string[4],sizeof(string[]),"[21点]%s 赢了 $%d.",string[4],(Game[gameid][4]*tmp)/won);
				  		GivePlayerMoney(playerid,(Game[gameid][4]*tmp)/won);
				  		LOOP(loop2,4)if(Game[gameid][loop2]>-1){
							SendClientMessage(Game[gameid][loop2],COLOR_YELLOW,string[4]);
							SendClientMessage(Game[gameid][loop2],COLOR_YELLOW,"[21点]输入/bj likai关闭窗口)");
						}
					}
				    OVER=1;
				    continue;
				}
			}
			if((GameStep[gameid]>=4)&&(GameStep[gameid]<=7))
			{
			    new tmps;
				LOOP(loop,4)
				{
				    if(Game[gameid][loop]>-1)
				    {
				        if(PlayerHolding[Game[gameid][loop]]){tmps++;}
				    }else tmps++;
				}
				if(tmps==4)
				{
				    new bestscore;
				    new scoreholder;
        			new currentscore;
        			new playerscore[4];
				    LOOP(loop,4)
				    {
				        if(Game[gameid][loop]>-1)
				        {
					        new tmp;
					        new tmp2;
					        LOOP(loop2,5)
					        {
					            if(PlayerCards[Game[gameid][loop]][loop2]>-1)
					            {
						            if((PlayerCards[Game[gameid][loop]][loop2]/4)+1>=10)
						            {
										tmp+=10;
										tmp2+=10;
						            }else if(PlayerCards[Game[gameid][loop]][loop2]/4==0)
						            {
						                if(tmp!=tmp2)tmp2+=1;
						                else tmp2+=11;
						                tmp+=1;
						            }else {tmp+=(PlayerCards[Game[gameid][loop]][loop2]/4)+1; tmp2+=(PlayerCards[Game[gameid][loop]][loop2]/4)+1;}
					            }
					        }
					        if(tmp2>21){currentscore=tmp;playerscore[loop]=tmp;}
					        else {currentscore=tmp2;playerscore[loop]=tmp2;}
					        if((currentscore>bestscore)&&(currentscore<22)){scoreholder=loop;bestscore=currentscore;}
				        }
					}
					new tmp2;
					LOOP(loop,4)if(playerscore[loop]==bestscore)tmp2++;
					LOOP(loop,4)if(playerscore[loop]==bestscore)
					{
						new tmpstring[24];
						GetPlayerName(Game[gameid][scoreholder],tmpstring,sizeof(tmpstring));
						format(string[4],sizeof(string[]),"Game Over!~n~~n~%s has ~g~WON!~w~",tmpstring);
	 				}
                    if(playerscore[PlayerGamePosition[playerid]]==bestscore)
					{
						GetPlayerName(playerid,string[4],sizeof(string[]));
				  		new tmp;LOOP(loop,4)if(Game[gameid][loop]>-1)tmp++;
				  		format(string[4],sizeof(string[]),"[21点]%s 赢了 $%d.",string[4],(Game[gameid][4]*tmp)/tmp2);
				  		GivePlayerMoney(playerid,(Game[gameid][4]*tmp)/tmp2);
				  		LOOP(loop2,4)if(Game[gameid][loop2]>-1){
							SendClientMessage(Game[gameid][loop2],COLOR_YELLOW,string[4]);
							SendClientMessage(Game[gameid][loop2],COLOR_YELLOW,"[21点]输入/bj likai关闭窗口)");
						}
					}
                    TextDrawSetString(GameText[playerid][4],string[4]);
					OVER=1;
					continue;
				}
			    if(GameStep[gameid]-4==PlayerGamePosition[playerid]) // Player's turn
			    {
			        if(PlayerHolding[playerid])
			        {
			            new tmp2;
			            LOOP(loop2,4)if(Game[gameid][loop2]==-1)tmp2++;
			            GameStep[gameid]++;
						if(GameStep[gameid]==7-tmp2+1)GameStep[gameid]=4;
			            UpdateGame(gameid);
			            return;
			        }
			    	format(string[4],sizeof(string[]),"Your turn, press ~k~~PED_JUMPING~ to hit and ~k~~PED_SPRINT~ to stay.",string[4]);
					SendClientMessage(Game[gameid][player],COLOR_YELLOW,"[21点]到你了，要牌请按左SHIFT，不要牌请按空格");
			    }else{
			   		GetPlayerName(Game[gameid][GameStep[gameid]-4],string[4],sizeof(string[]));
			        format(string[4],sizeof(string[]),"%s's turn",string[4]);
					SendClientMessage(Game[gameid][player],COLOR_YELLOW,"[21点]到其他玩家了。");
				}
			}
			if((GameStep[gameid]>3)&&(GameStep[gameid]<8))
			{
	    		new Losers[4]; // -1 = not there, 0 = loser, 1 = not loser
				LOOP(loop,4)
				{
				    if(Game[gameid][loop]>-1)
				    {
					    new tmp;
					    new tmp2;
					    LOOP(loop2,5)
					    {
					        if(PlayerCards[Game[gameid][loop]][loop2]>-1)
					        {
						        if((PlayerCards[Game[gameid][loop]][loop2]/4)+1>=10)
						        {
									tmp+=10;
									tmp2+=10;
						        }else if(PlayerCards[Game[gameid][loop]][loop2]/4==0)
						        {
						            if(tmp!=tmp2)tmp2+=1;
						            else tmp2+=11;
									tmp+=1;
								}else {tmp+=(PlayerCards[Game[gameid][loop]][loop2]/4)+1; tmp2+=(PlayerCards[Game[gameid][loop]][loop2]/4)+1;}
					    	}
					    }
						if(tmp>21)
						{
							PlayerHolding[Game[gameid][loop]]=1;
							new tmpstring[24];
							Losers[loop]=0;
							GetPlayerName(Game[gameid][loop],tmpstring,sizeof(tmpstring));
							format(string[4],sizeof(string[]),"%s~n~%s has ~r~BUSTED!~w~",string[4],tmpstring);
						}else Losers[loop]=1;
					}else Losers[loop]=-1;
				}
				new tmpp;
				new winner=-1;
				LOOP(loop,4)if(Losers[loop]==1){tmpp++;}
				if(tmpp==1)LOOP(loop,4)if(Losers[loop]==1)winner=loop;
				if(winner>-1)
				{
				    new tmpstring[24];
					GetPlayerName(Game[gameid][winner],tmpstring,sizeof(tmpstring));
				    format(string[4],sizeof(string[]),"%s~n~%s has ~g~WON!~w~",string[4],tmpstring);
					OVER=1;
				}
				if(OVER){strdel(string[4],0,strfind(string[4],"~n~",true));format(string[4],sizeof(string[]),"Game Over!~n~%s",string[4]);}
				TextDrawSetString(GameText[playerid][4],string[4]);
				if(winner == PlayerGamePosition[playerid])
				{
					GetPlayerName(playerid,string[4],sizeof(string[]));
					new tmp;LOOP(loop,4)if(Game[gameid][loop]>-1)tmp++;
					format(string[4],sizeof(string[]),"[21点]%s 赢了 $%d.",string[4],(Game[gameid][4]*tmp));
		  			GivePlayerMoney(playerid,(Game[gameid][4]*tmp));
				  	LOOP(loop2,4)if(Game[gameid][loop2]>-1){
						SendClientMessage(Game[gameid][loop2],COLOR_YELLOW,string[4]);
						SendClientMessage(Game[gameid][loop2],COLOR_YELLOW,"[21点]输入/bj likai关闭窗口)");
					}
				}
			}
		}
	}
	if(OVER)GameStep[gameid]=8;
	if(GameStep[gameid]==3){GameStep[gameid]=4;UpdateGame(gameid);}
	if(GameStep[gameid]==8){GameStep[gameid]=9;UpdateGame(gameid);DeleteGame(gameid);}
}

public OnFilterScriptInit()
{
	LOOP(loop,100)
	{
		LOOP(loop2,4)Game[loop][loop2]=-1;
		LOOP(loop2,52)GameCards[loop][loop2]=-1;
	}
	LOOP(loop,MAX_PLAYERS)
	{
	    PlayerGame[loop]=-1;
	    PlayerGamePosition[loop]=-1;
	    PlayerInviting[loop]=-1;
		LOOP(loop2,5)
		{
			if(_:GameText[loop][loop2])TextDrawDestroy(GameText[loop][loop2]);
			PlayerCards[loop][loop2]=-1;
		}
	}
	if(!_:null)null = TextDrawCreate(0,0,"  "); //Removes a common bug, to be shown under OnFilterScriptInit and OnGameModeInit
	TextDrawShowForPlayer(0,null);
	return 1;
}

public OnGameModeInit()
{
	null = TextDrawCreate(0,0,"  "); //Removes a common bug, to be shown under OnFilterScriptInit and OnGameModeInit
	TextDrawShowForPlayer(0,null);
	return 1;
}

public OnFilterScriptExit()
{
	return 1;
}

public OnPlayerCommandText(playerid,cmdtext[])
{
	if(!strcmp(cmdtext,"/bj help",true)){
		ShowPlayerDialog(playerid,1,DIALOG_STYLE_MSGBOX,"21点帮助:", \
		"\
		/bj start [金钱] 玩21点\n\n/bj invite [玩家ID] 邀请玩家加入\n\n/bj quxiao 取消你的邀请\n\n\
		/bj jieshou 接受他人的邀请\n\n/bj jujue 拒绝别人的邀请\n\n/bj likai 快速退出21点游戏\n\n\n\
		玩法:\n\n和现实中的21点一样，开始后，左SHIFT键-要牌，空格键-不要牌\
		","确定","取消");
		return true;
	}
	if(!strcmp(cmdtext,"/bj start ",true,10))
	{
	    if(PlayerGame[playerid]>-1)return SendClientMessage(playerid,COLOR_YELLOW,"[21点]你已经参加了21点游戏.");
		if(IsPlayerInAnyVehicle(playerid))return SendClientMessage(playerid,COLOR_YELLOW,"[21点]你不能在车上玩21点.");
	    new BetAmount = strval(cmdtext[10]);
		if(!strlen(cmdtext[10]) || BetAmount<0)return SendClientMessage(playerid,COLOR_YELLOW,"[21点]使用方法:/bj start [金钱]");
		if(GetPlayerMoney(playerid)<BetAmount)return SendClientMessage(playerid,COLOR_YELLOW,"[21点]你没有这么多钱.");
		GivePlayerMoney(playerid,-BetAmount);
		new gameid = CreateGame();
	    Game[gameid][0]=playerid;
	    Game[gameid][4]=BetAmount;
	    GameStep[gameid]=2;
	    PlayerGame[playerid]=gameid;
	    PlayerGamePosition[playerid]=0;
		new tmpstring[128];
		format(tmpstring,sizeof(tmpstring),"[21点]你发起了21点游戏，(赌博金额$%d) 输入/bj yaoqing [玩家ID] 可以邀请他人加入",BetAmount);
		SendClientMessage(playerid,COLOR_YELLOW,tmpstring);
	    UpdateGame(gameid);
	    return 1;
	}
	/*
	if(!strcmp(cmdtext,"/addcrd ",true,8))
	{
			    new face = strval(cmdtext[8])+1;
			    new card = strval(cmdtext[strfind(cmdtext," ",true,8)+1]);
			    new tmp = (face*4)+card;
			    if(GameCards[PlayerGame[playerid]][tmp]>-1)return SendClientMessage(playerid,COLOR_YELLOW,"Card taken");
				new tmp2;
				LOOP(cards,5)
				{
				    if(PlayerCards[playerid][cards]==-1)
				    {
						GameCards[PlayerGame[playerid]][tmp]=playerid*5+cards;
						PlayerCards[playerid][cards]=tmp;
				        break;
				    }
				}
				new tmp23[50];
				GetPlayerName(playerid,tmp23,sizeof(tmp23));
				format(tmp23,sizeof(tmp23),"%s decides to hit.",tmp23);
				LOOP(loop2,4)if(Game[PlayerGame[playerid]][loop2]!=playerid)SendClientMessage(Game[PlayerGame[playerid]][loop2],COLOR_YELLOW,tmp23);
				GameStep[PlayerGame[playerid]]++;
				LOOP(loop2,4)if(Game[PlayerGame[playerid]][loop2]==-1)tmp2++;
				if(GameStep[PlayerGame[playerid]]==7-tmp2+1)GameStep[PlayerGame[playerid]]=4;
				UpdateGame(PlayerGame[playerid]);
				return 1;
	}*/
	if(!strcmp(cmdtext,"/bj yaoqing ",true,12))
	{
	    if(PlayerInviting[playerid]>-1)return SendClientMessage(playerid,COLOR_YELLOW,"[21点]你已经邀请了其他人，请输入/bj quxiao 取消你的邀请.");
		if(IsPlayerInAnyVehicle(playerid))return SendClientMessage(playerid,COLOR_YELLOW,"[21点]不能在车上玩21点");
	    new person = strval(cmdtext[12]);
	    if(IsPlayerConnected(person))
	    {
	        if(GetPlayerMoney(person)<Game[PlayerGame[playerid]][4])return SendClientMessage(playerid,COLOR_YELLOW,"[21点]对方没那么多钱.");
			new string[200];
			LOOP(loop,MAX_PLAYERS)if(PlayerInviting[loop]==person){printf("%d",loop);return SendClientMessage(playerid,COLOR_YELLOW,"[21点]对方已经被其他人邀请.");}
	        if((PlayerGame[person]==-1))//PlayerGame[person]==-1
	        {
	            PlayerInviting[playerid]=person;
				GetPlayerName(playerid,string,sizeof(string));
				format(string,sizeof(string),"[21点]%s邀请你加入21点(赌博金额$%d).输入/bj jieshou/jujue 接受/拒绝他的邀请.",string,Game[PlayerGame[playerid]][4]);
				SendClientMessage(person,COLOR_YELLOW,string);
				GetPlayerName(person,string,sizeof(string));
				format(string,sizeof(string),"[21点]你邀请了%s玩21点(赌博金额$%d).",string,Game[PlayerGame[playerid]][4]);
				SendClientMessage(playerid,COLOR_YELLOW,string);
				return 1;
	        }else{
	            return 1;
	        }
	    }
	}
	if(!strcmp(cmdtext,"/bj jieshou",true))
	{
		LOOP(player,MAX_PLAYERS)
		{
		    if(PlayerInviting[player]==playerid)
		    {
		        if(PlayerNearPlayer(playerid,player,5000))//yezizhu : 5->5000
		        {
			        LOOP(position,4)
			        {
			            if(Game[PlayerGame[player]][position]==-1)
			            {
			                PlayerGame[playerid] = PlayerGame[player];
			                PlayerGamePosition[playerid]=position;
			                Game[PlayerGame[player]][position]=playerid;
			                GivePlayerMoney(playerid,-Game[PlayerGame[player]][4]);
			                UpdateGame(PlayerGame[player]);
			                return 1;
			            }
			        }
			        PlayerInviting[playerid]=-1;
		        }else SendClientMessage(playerid,COLOR_YELLOW,"[21点]双方相隔太远，邀请失败.");
		    }
		}
	}
	if(!strcmp(cmdtext,"/bj quxiao",true))
	{
		if(PlayerInviting[playerid]>-1)
		{
			new tmpstring[100];
			GetPlayerName(playerid,tmpstring,sizeof(tmpstring));
			format(tmpstring,sizeof(tmpstring),"[21点]%s取消了对你的邀请",tmpstring);
			SendClientMessage(PlayerInviting[playerid],COLOR_YELLOW,tmpstring);
			GetPlayerName(PlayerInviting[playerid],tmpstring,sizeof(tmpstring));
			format(tmpstring,sizeof(tmpstring),"[21点]你取消了对%s的邀请",tmpstring);
			SendClientMessage(playerid,COLOR_YELLOW,tmpstring);
			PlayerInviting[playerid]=-1;
			return 1;
		}else return SendClientMessage(playerid,COLOR_YELLOW,"[21点]你没有发出任何邀请.");
	}
	if(!strcmp(cmdtext,"/bj jujue",true))
	{
		LOOP(player,MAX_PLAYERS)
		{
		    if(PlayerInviting[player]==playerid)
		    {
		        PlayerInviting[playerid]=-1;
		        new tmpstring[80];
				GetPlayerName(playerid,tmpstring,sizeof(tmpstring));
				format(tmpstring,sizeof(tmpstring),"[21点]%s拒绝了你的邀请",tmpstring);
				SendClientMessage(player,COLOR_YELLOW,tmpstring);
				GetPlayerName(player,tmpstring,sizeof(tmpstring));
				format(tmpstring,sizeof(tmpstring),"[21点]你拒绝了%s的邀请",tmpstring);
				SendClientMessage(playerid,COLOR_YELLOW,tmpstring);
				return 1;
		    }
		}return SendClientMessage(playerid,COLOR_YELLOW,"[21点]现在没有人邀请你玩21点(输入/bj help查看帮助).");
	}
	if(!strcmp(cmdtext,"/bj likai",true))
	{
	    if(PlayerGame[playerid]>-1)
	    {
	        if(GameStep[PlayerGame[playerid]]<3)
	        {
	        	LOOP(loop,4)if((Game[PlayerGame[playerid]][loop]>-1))if(Game[PlayerGame[playerid]][loop]!=playerid)
				{
				    new tmpstring[100];
				    GetPlayerName(playerid,tmpstring,sizeof(tmpstring));
				    format(tmpstring,sizeof(tmpstring),"[21点]%s不玩了，金钱已退回.",tmpstring);
				    SendClientMessage(Game[PlayerGame[playerid]][loop],COLOR_YELLOW,tmpstring);
				    GivePlayerMoney(Game[PlayerGame[playerid]][loop],Game[PlayerGame[playerid]][4]);
				}
				SendClientMessage(playerid,COLOR_YELLOW,"[21点]你不玩了，金钱已退回.");
				GivePlayerMoney(playerid,Game[PlayerGame[playerid]][4]);
	        }
	        else
	        {
				LOOP(loop,4)if((Game[PlayerGame[playerid]][loop]>-1))if(Game[PlayerGame[playerid]][loop]!=playerid)
				{
				    new tmpstring[100];
				    GetPlayerName(playerid,tmpstring,sizeof(tmpstring));
				    new tmp;
				    LOOP(loop2,4)if(Game[PlayerGame[playerid]][loop]>-1)tmp++;
				    format(tmpstring,sizeof(tmpstring),"[21点]%s退出了21点,$%d平分给剩下的玩家.",tmpstring,Game[PlayerGame[playerid]][4]*tmp);
				    GivePlayerMoney(Game[PlayerGame[playerid]][loop],Game[PlayerGame[playerid]][4]*tmp);
				    SendClientMessage(Game[PlayerGame[playerid]][loop],COLOR_YELLOW,tmpstring);
				}
				SendClientMessage(playerid,COLOR_YELLOW,"[21点]你强制离开了21点游戏.");
			}
			DeleteGame(PlayerGame[playerid]);
		}
		CloseWindow(playerid);
		return 1;
	}
	return 0;
}

public OnPlayerDisconnect(playerid, reason)
{
	if(PlayerGame[playerid]>-1)
	{
	    if(PlayerGame[playerid]>-1)
	    {
			LOOP(loop,4)if((Game[PlayerGame[playerid]][loop]>-1))if(Game[PlayerGame[playerid]][loop]!=playerid)
			{
			    new tmpstring[100];
			    GetPlayerName(playerid,tmpstring,sizeof(tmpstring));
			    new tmp;
			    LOOP(loop2,4)if(Game[PlayerGame[playerid]][loop]>-1)tmp++;
			    format(tmpstring,sizeof(tmpstring),"[21点]%s退出了21点,$%d平分给剩下的玩家.",tmpstring,Game[PlayerGame[playerid]][4]*tmp);
			    GivePlayerMoney(Game[PlayerGame[playerid]][loop],Game[PlayerGame[playerid]][4]*tmp);
			    SendClientMessage(Game[PlayerGame[playerid]][loop],COLOR_YELLOW,tmpstring);
			}
			SendClientMessage(playerid,COLOR_YELLOW,"[21点]你强制离开了21点游戏.");
			DeleteGame(PlayerGame[playerid]);
		}
		CloseWindow(playerid);
	}
	return 1;
}

public OnPlayerKeyStateChange(playerid,newkeys,oldkeys)
{
	if(PlayerGame[playerid]>-1)
	{
	    if(GameStep[PlayerGame[playerid]]==2)
	    {
	        if(Game[PlayerGame[playerid]][1]>-1)
	        {
	            if(Game[PlayerGame[playerid]][0]==playerid)
	            {
	                if((newkeys==KEY_FIRE) && (oldkeys == 0))
					{
	                    GameStep[PlayerGame[playerid]]=3;
	                    UpdateGame(PlayerGame[playerid]);
	                    return 1;
	                }
	            }
	        }
	    }
	    if(GameStep[PlayerGame[playerid]]==PlayerGamePosition[playerid]+4)
	    {
            if((newkeys == KEY_SPRINT) && (oldkeys == 0))
            {
                PlayerHolding[playerid] = 1;
				new tmp2;
				LOOP(players,4)
				{
				    if(Game[PlayerGame[playerid]][players]>-1)
				    {
				        new tmp[50];
						GetPlayerName(playerid,tmp,sizeof(tmp));
						format(tmp,sizeof(tmp),"[21点]玩家%s不要牌.",tmp);//[21点]%s decides to stay
						SendClientMessage(Game[PlayerGame[playerid]][players],COLOR_YELLOW,tmp);
				    }else tmp2++;

				}
				GameStep[PlayerGame[playerid]]++;
				if(GameStep[PlayerGame[playerid]]==7-tmp2+1)GameStep[PlayerGame[playerid]]=4;
          		UpdateGame(PlayerGame[playerid]);
          		return 1;
	        }
	    	if((newkeys == KEY_JUMP) && (oldkeys == 0))
	    	{
	         	CardLabel2:
				new tmp = random(52);
				if(GameCards[PlayerGame[playerid]][tmp]>=0)goto CardLabel2;
				new tmp2;
				LOOP(cards,5)
				{
				    if(PlayerCards[playerid][cards]==-1)
				    {
						GameCards[PlayerGame[playerid]][tmp]=playerid*5+cards;
						PlayerCards[playerid][cards]=tmp;
				        break;
				    }
				}
				new tmp23[50];
				GetPlayerName(playerid,tmp23,sizeof(tmp23));
				format(tmp23,sizeof(tmp23),"[21点]玩家%s要牌.",tmp23);//[21点]%s decides to hit
				LOOP(loop2,4)if(Game[PlayerGame[playerid]][loop2]!=playerid)SendClientMessage(Game[PlayerGame[playerid]][loop2],COLOR_YELLOW,tmp23);
				GameStep[PlayerGame[playerid]]++;
				LOOP(loop2,4)if(Game[PlayerGame[playerid]][loop2]==-1)tmp2++;
				if(GameStep[PlayerGame[playerid]]==7-tmp2+1)GameStep[PlayerGame[playerid]]=4;
				UpdateGame(PlayerGame[playerid]);
				return 1;
	        }
	    }
	}
	return 1;
}
