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



#define SUBACCOUNT_DIRECTION			"wl/subaccount/"
#define MAX_SUBACCOUNT_ACCOUNT_LEN		(36)
#define MAX_SUBACCOUNT_PASSWORD_LEN		(36)
#define subaccount_Name					"accountName"
#define subaccount_Pass					"accountPass"
#define subaccount_AutoHealVec			"set_autoHealVec"
#define subaccount_AutoRepairVec		"set_autoRepairVec"
#define subaccount_AutoNos				"set_autoNos"
#define subaccount_NosWhenEnterVec		"set_NosWhenEnterVec"
//#define subaccount_Godmode				"set_Godmode"

forward sb_pcreate(playerid,accountName[]);
forward sb_pregister(playerid,accountName[],accountPass[]);
forward sb_plogin(playerid,accountName[]);



static stock
	gsb_pAccount[MAX_PLAYERS][MAX_SUBACCOUNT_ACCOUNT_LEN],
	gsb_pPassword[MAX_PLAYERS][MAX_SUBACCOUNT_PASSWORD_LEN],
	gsb_pAutoHealVec[MAX_PLAYERS],
	gsb_pAutoRepairVec[MAX_PLAYERS],
	gsb_PAutoNos[MAX_PLAYERS],
	gsb_pAddNosWhenEnterVec[MAX_PLAYERS];
	//gsb_pGodmode[MAX_PLAYERS];
	

stock sb_spAccountName(playerid,accountName[]){
	format(gsb_pAccount[playerid],MAX_SUBACCOUNT_ACCOUNT_LEN,"%s",accountName);
	return true;
}
stock sb_gpAccountName(playerid){
	return gsb_pAccount[playerid];
}

stock sb_spAccountPass(playerid,accountPass[]){
	format(gsb_pPassword[playerid],MAX_SUBACCOUNT_PASSWORD_LEN,"%s",accountPass);
	return true;
}
stock sb_gpAccountPass(playerid){
	return gsb_pPassword[playerid];
}

stock sb_spAutoHealVec(playerid,set){
	gsb_pAutoHealVec[playerid] = set;
	return true;
}

stock sb_gpAutoHealVec(playerid){
	return gsb_pAutoHealVec[playerid];
}
	
stock sb_spAutoRepairVec(playerid,set){
	gsb_pAutoRepairVec[playerid] = set;
	return true;
}

stock sb_gpAutoRepairVec(playerid){
	return gsb_pAutoRepairVec[playerid];
}

stock sb_spAutoNos(playerid,set){
	gsb_PAutoNos[playerid] = set;
	return true;
}

stock sb_gpAutoNos(playerid){
	return gsb_PAutoNos[playerid];
}

stock sb_spAddNowWhenEnterVec(playerid,set){
	gsb_pAddNosWhenEnterVec[playerid] = set;
	return true;
}
stock sb_gpAddNowWhenEnterVec(playerid){
	return gsb_pAddNosWhenEnterVec[playerid];
}
/*
stock sb_spGodmode(playerid,set){
	gsb_pGodmode[playerid] = set;
	return true;
}
stock sb_gpGodmode(playerid){
	return gsb_pGodmode[playerid];
}
*/
sb_playerConnect(playerid){
	sb_spAccountName(playerid,"");
	sb_spAccountPass(playerid,"");
	sb_spAutoHealVec(playerid,true);
	sb_spAutoRepairVec(playerid,true);
	sb_spAutoNos(playerid,true);
	sb_spAddNowWhenEnterVec(playerid,true);
	//sb_spGodmode(playerid,true);
}

sb_playerDisconnect(playerid){
	sb_spAccountName(playerid,"");
	sb_spAccountPass(playerid,"");
	sb_spAutoHealVec(playerid,true);
	sb_spAutoRepairVec(playerid,true);
	sb_spAutoNos(playerid,true);
	sb_spAddNowWhenEnterVec(playerid,true);
	//sb_spGodmode(playerid,true);
}

sb_playerSpawn(playerid){
	#pragma unused playerid
	//sb_useGodmode(playerid);
	return true;
}

stock sb_getFile(accountName[]){
	new
		tmpstr[128];
	format(tmpstr,sizeof(tmpstr),"%s%s.sb",SUBACCOUNT_DIRECTION,accountName);
	return tmpstr;
}
	

public sb_pcreate(playerid,accountName[]){ debug_public_track("sb_pcreate(playerid,accountName[]){");
	new
		account[128];
	format(account,sizeof(account),"%s%s",SUBACCOUNT_DIRECTION,accountName);
	if(fexist(account)) return false;
	fclose(fopen(account,io_write));
	return true;
}

public sb_pregister(playerid,accountName[],accountPass[]){ debug_public_track("sb_pregister(playerid,accountName[],accountPass[]){");
	if(fexist(sb_getFile(accountName)))return false;
	sb_spAccountName(playerid,accountName);
	sb_spAccountPass(playerid,accountPass);
	sb_spDatatoFile(playerid,sb_getFile(accountName));
	return true;
}

public sb_plogin(playerid,accountName[]){ debug_public_track("sb_plogin(playerid,accountName[]){");
	if(!fexist(sb_getFile(accountName)))return false;
	sb_spDatafromFile(playerid,sb_getFile(accountName));
	return true;
}

stock sb_spDatatoFile(playerid,account[]){
	gini_open(account);
	gini_writes(subaccount_Name,sb_gpAccountName(playerid));
	gini_writes(subaccount_Pass,sb_gpAccountPass(playerid));
	gini_writei(subaccount_AutoHealVec,sb_gpAutoHealVec(playerid));
	gini_writei(subaccount_AutoRepairVec,sb_gpAutoRepairVec(playerid));
	gini_writei(subaccount_AutoNos,sb_gpAutoNos(playerid));
	gini_writei(subaccount_NosWhenEnterVec,sb_gpAddNowWhenEnterVec(playerid));
	//gini_writei(subaccount_Godmode,sb_gpGodmode(playerid));
	gini_save();
	gini_close();
	return true;
}

stock sb_spDatafromFile(playerid,account[]){
	gini_open(account);
	sb_spAccountName(playerid,gini_reads(subaccount_Name));
	sb_spAccountPass(playerid,gini_reads(subaccount_Pass));
	sb_spAutoHealVec(playerid,gini_readi(subaccount_AutoHealVec));
	sb_spAutoRepairVec(playerid,gini_readi(subaccount_AutoRepairVec));
	sb_spAutoNos(playerid,gini_readi(subaccount_AutoNos));
	sb_spAddNowWhenEnterVec(playerid,gini_readi(subaccount_NosWhenEnterVec));
	//sb_spGodmode(playerid,gini_readi(subaccount_Godmode));
	gini_close();
	return true;
}



/*
new stock
	g_splitcmd[5][MAX_MSG_STR];
#define cmd_(%1) g_splitcmd[(%1)-1]
#define compare(%1,%2) !strcmp(%1,g_splitcmd[(%2)-1],true)
#define zcmd_advused() sscanf(params,"sssss",g_splitcmd[0],g_splitcmd[1],g_splitcmd[2],g_splitcmd[3],g_splitcmd[4]);
*/
zcmd(subaccount,playerid,params[]){
	System_send(playerid,"[帐号]服务器暂时取消个性化设置功能");
	return true;
	sscanf(params,"sss",g_splitcmd[0],g_splitcmd[1],g_splitcmd[2]);
	if(compare("set",1)){
		if(compare("autonos",2)){
			if(sb_gpAutoNos(playerid)){
				sb_spAutoNos(playerid,false);
				System_send(playerid,"[个性化设置]你取消了无限Nos");
			}else{
				sb_spAutoNos(playerid,true);
				System_send(playerid,"[个性化设置]你开启了无限Nos");
			}
		}else if(compare("autohealvec",2)){
			if(sb_gpAutoHealVec(playerid)){
				sb_spAutoHealVec(playerid,false);
				System_send(playerid,"[个性化设置]你取消了无限车血");
			}else{
				sb_spAutoHealVec(playerid,true);
				System_send(playerid,"[个性化设置]你开启了无限车血");
			}
		}else if(compare("autorepairvec",2)){
			if(sb_gpAutoRepairVec(playerid)){
				sb_spAutoRepairVec(playerid,false);
				System_send(playerid,"[个性化设置]你取消了自动修复交通工具");
			}else{
				sb_spAutoRepairVec(playerid,true);
				System_send(playerid,"[个性化设置]你开启了自动修复交通工具");
			}
		}else if(compare("noswhenentervec",2)){
			if(sb_gpAddNowWhenEnterVec(playerid)){
				sb_spAddNowWhenEnterVec(playerid,false);
				System_send(playerid,"[个性化设置]你取消了进入交通工具添加Nos的功能");
			}else{
				sb_spAddNowWhenEnterVec(playerid,true);
				System_send(playerid,"[个性化设置]你开启了进入交通工具添加Nos的功能");
			}
		}/*else if(compare("godmode",2)){
			if(sb_gpGodmode(playerid)){
				sb_spGodmode(playerid,false);
				System_send(playerid,"[个性化设置]你关闭了godmode");
			}else{
				sb_spGodmode(playerid,true);
				System_send(playerid,"[个性化设置]你开启了godmode");
			}
		}*/
		else if(compare("help",2)){
			System_send(playerid,"=========[个性化详细设置帮助/信息]==========");
			System_send(playerid,"    /s set autonos          -  无限Nos设置,当前状态:%d",sb_gpAutoNos(playerid));
			System_send(playerid,"    /s set autohealvec      -  大世界无限车血设置,当前状态:%d",sb_gpAutoHealVec(playerid));
			System_send(playerid,"    /s set autorepairvec    -  大世界自动修复交通工具设置,当前状态:%d",sb_gpAutoRepairVec(playerid));
			System_send(playerid,"    /s set noswhenentervec  -  进入交通工具添加Nos设置,当前状态:%d",sb_gpAutoRepairVec(playerid));
			//System_send(playerid,"    /s set godmode          -  开启godmode(正常世界有效),当前状态:%d",sb_gpGodmode(playerid));
			System_send(playerid,"===================================");
		}else{
			System_send(playerid,"[个性化设置]你输入的子命令'%s'不存在,输入/s set help 查看帮助",params);
		}
	}else if(compare("register",1)){
		if(isnull(cmd_(2))){
			System_send(playerid,"[个性化设置-开设一个帐号]请输入个性化帐号名称");
			return true;
		}
		if(fexist(sb_getFile(cmd_(2)))){
			System_send(playerid,"[个性化设置-开设一个帐号]你输入的帐号已存在");
			return true;
		}
		if(isnull(cmd_(3))){
			System_send(playerid,"[个性化设置-开设一个帐号]请输入个性化帐户密码");
			return true;
		}
		if(!sb_pregister(playerid,cmd_(2),cmd_(3))){
			System_send(playerid,"[个性化设置-开设一个帐号]注册失败，请联系管理员");
		}
		System_send(playerid,"[个性化设置-开设一个帐号]注册成功，请记住帐号密码!");
		System_send(playerid,"帐号:%s",sb_gpAccountName(playerid));
		System_send(playerid,"密码:%s",sb_gpAccountPass(playerid));
		System_send(playerid,"[个性化设置-开设一个帐号]你以后可以使用/s reset [帐号] [密码] 随时修改");
	}else if(compare("login",1)){
		if(isnull(cmd_(2))){
			System_send(playerid,"[个性化设置-登陆]请输入个性化帐号名称");
			return true;
		}
		if(!sb_plogin(playerid,cmd_(2))){
			System_send(playerid,"[个性化设置-登陆]你输入的帐号不存在");
			return true;
		}
		System_send(playerid,"[个性化设置-登陆]登陆成功");
	}else if(compare("reset",1)){
		if(isnull(cmd_(2))){
			System_send(playerid,"[个性化设置-重新设置帐号]请输入个性化帐户名称");
			return true;
		}
		if(!fexist(sb_getFile(cmd_(2)))){
			System_send(playerid,"[个性化设置-登陆]你输入的帐号不存在");
			return true;
		}
		if(isnull(cmd_(3))){
			System_send(playerid,"[个性化设置-重新设置帐号]请输入个性化帐户密码");
			return true;
		}
		gini_open(sb_getFile(cmd_(2)));
		if(!compare(gini_reads(subaccount_Pass),3)){
			System_send(playerid,"[个性化设置-重新设置帐号]密码错误，请确认密码");
			return true;
		}
		sb_spDatatoFile(playerid,sb_getFile(cmd_(2)));
		System_send(playerid,"[个性化设置-重新设置帐号]重新设置成功！");
	}else if(compare("help",1)){
		System_send(playerid,"=========[个性化设置帮助]==========");
		System_send(playerid,"    /s register [帐号] [密码]  -  注册一个帐号");
		System_send(playerid,"    /s login    [帐号]         -  使用特定帐号的个性化设置");
		System_send(playerid,"    /s reset    [帐号] [密码]  -  重新设置一个帐号的信息");
		System_send(playerid,"    /s set help                -  详细设置帮助/个性化设置信息");
		System_send(playerid,"===================================");
	}else{
		System_send(playerid,"[个性化设置]你输入的子命令'%s'不存在,输入/s help 查看帮助",params);
	}
	return true;
}
pzcmd(s) 		rzcmd(subaccount);		
		
/*
stock sb_useGodmode(playerid){
	if(!GetPlayerVirtualWorld(playerid) && sb_gpGodmode(playerid)){
		SetPlayerHealth(playerid,999999999);
	}
	return true;
}
*/































