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



dmwscore:struct(){
	{	
		db_processstart("ALTER TABLE gang_stat ADD COLUMN dmw_score INTEGER NOT NULL DEFAULT 0;");
		db_processthenfree(db_dmworld);
	}
	{
		db_processstart("SELECT id,dmw_score FROM gang_stat;");
		db_processthengetresult(db_dmworld);
		for(new i, j = db_num_rows(dbr), id[11], score[11]; i < j; i++){
			db_get_field_assoc(dbr,"id",id,sizeof(id));
			db_get_field_assoc(dbr,"dmw_score",score,sizeof(score));
			SetGVarInt("wl_gang_dmw_score",strval(score),strval(id));
			db_next_row(dbr);
		}
		db_processend();
	}
}
dmwscore:setGang(gangid,score){
	CallLocalFunction("OnGangdmwScoreChange","iii",gangid,GetGVarInt("wl_gang_dmw_score",gangid),score);
	SetGVarInt("wl_gang_dmw_score",score,gangid);
	db_processstart("UPDATE gang_stat SET dmw_score = %d WHERE id = %d",score,gangid);
	db_processthenfree(db_dmworld);	
	
}
dmwscore:getGang(gangid){
	return GetGVarInt("wl_gang_dmw_score",gangid);
}
dmwscore:setPlayerGang(playerid,score){
	if(gang:getPlayerGang(playerid) != INVALID_GANG_ID){
		dmwscore:setGang(gang:getPlayerGang(playerid),score);
	}
}
dmwscore:getPlayerGang(playerid){
	if(gang:getPlayerGang(playerid) != INVALID_GANG_ID){
		return dmwscore:getGang(gang:getPlayerGang(playerid));
	}
	return 0;
}
dmwscore:amountedPlayerGang(playerid,amounted){
	if(gang:getPlayerGang(playerid) != INVALID_GANG_ID){
		dmwscore:setGang(gang:getPlayerGang(playerid),dmwscore:getGang(gang:getPlayerGang(playerid))+amounted);
	}
}
dmwscore:playerDeath(playerid,killerid){
	if(dmw:getPlayer(playerid)){
		if(killerid != INVALID_PLAYER_ID && (gang:getPlayerGang(killerid) != gang:getPlayerGang(playerid)))dmwscore:amountedPlayerGang(playerid,1);
		if(gang:getPlayerGang(playerid) == INVALID_GANG_ID)return;
		if(killerid != INVALID_PLAYER_ID && (gang:getPlayerGang(playerid) != gang:getPlayerGang(killerid))) dmwscore:amountedPlayerGang(playerid,5);
		if(killerid != INVALID_PLAYER_ID){
			gang:sendgang(gang:getPlayerGang(playerid),"dmw_playerdeath_playergang",pName(playerid),pName(killerid));
			gang:sendgang(gang:getPlayerGang(playerid),"dmw_playerdeath_killergang",pName(killerid),pName(playerid));
		}
		else {
			gang:sendgang(gang:getPlayerGang(playerid),"dmw_playerdeath_plyaergang_nonekiller",pName(playerid));
		}
	}
}
dmwscore:playerLogin(playerid){
	if(gang:getPlayerGang(playerid) != INVALID_GANG_ID){
		SetPlayerScore(playerid,dmwscore:getPlayerGang(playerid));
		GivePlayerMoney(playerid,(0-GetPlayerMoney(playerid))+(0-dmwscore:getPlayerGang(playerid)));
	}
}
dmwscore:OnGangdmwScoreChange(gangid,oldscore,newscore){
	#pragma unused oldscore
	loopPlayer(playerid){
		if(gang:getPlayerGang(playerid) == gangid){
			SetPlayerScore(playerid,newscore);
			GivePlayerMoney(playerid,(0 - GetPlayerMoney(playerid)) + (0 - newscore));
		}
	}
}