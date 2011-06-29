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
	��Ȩ(c) <2010> <yezizhu>  

	ʹ�ø�����֤����������������Ȩ�ޣ���ѣ��κ��˿��Եõ����������������ĵ���һ��������
	���Ҿ�Ӫ�����������κ����ƣ����������Ƶ�ʹ�á����ơ��޸ġ��ϲ������桢���С����Ŵ���֤�顢���߳��۸������Ŀ�����Ȩ����
	ͬʱ���������Щ�������û�������ЩȨ����ʹ����������������  
	
	���ϵİ�Ȩ֪ͨ��Ȩ��֪ͨӦ�ð��������и������Ŀ����л�������������������ʵ�����С�
	
	�������������������ṩ��û���κ���ʽ�ĵ�������������ȷ�ػ��߰����ģ�������Щ���ǲ�����ҵ���ʵĵ��������ơ�
	�ʺ�һ���ض�����;���Ҳ����ַ������ߺͰ�Ȩ���������κγ��϶�ʹ�ø������漰���κ�Ҫ���𺦻����������ζ���Ӧ����
	�����������������û���ֻ�Ǻ�ͬ��ʽ��������Ȩ����������ʽ�������������������÷�Χ�ڡ������������ϵ����������ʹ�û�����������������������Ϊ��  
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
	System_send(playerid,"[�ʺ�]��������ʱȡ�����Ի����ù���");
	return true;
	sscanf(params,"sss",g_splitcmd[0],g_splitcmd[1],g_splitcmd[2]);
	if(compare("set",1)){
		if(compare("autonos",2)){
			if(sb_gpAutoNos(playerid)){
				sb_spAutoNos(playerid,false);
				System_send(playerid,"[���Ի�����]��ȡ��������Nos");
			}else{
				sb_spAutoNos(playerid,true);
				System_send(playerid,"[���Ի�����]�㿪��������Nos");
			}
		}else if(compare("autohealvec",2)){
			if(sb_gpAutoHealVec(playerid)){
				sb_spAutoHealVec(playerid,false);
				System_send(playerid,"[���Ի�����]��ȡ�������޳�Ѫ");
			}else{
				sb_spAutoHealVec(playerid,true);
				System_send(playerid,"[���Ի�����]�㿪�������޳�Ѫ");
			}
		}else if(compare("autorepairvec",2)){
			if(sb_gpAutoRepairVec(playerid)){
				sb_spAutoRepairVec(playerid,false);
				System_send(playerid,"[���Ի�����]��ȡ�����Զ��޸���ͨ����");
			}else{
				sb_spAutoRepairVec(playerid,true);
				System_send(playerid,"[���Ի�����]�㿪�����Զ��޸���ͨ����");
			}
		}else if(compare("noswhenentervec",2)){
			if(sb_gpAddNowWhenEnterVec(playerid)){
				sb_spAddNowWhenEnterVec(playerid,false);
				System_send(playerid,"[���Ի�����]��ȡ���˽��뽻ͨ��������Nos�Ĺ���");
			}else{
				sb_spAddNowWhenEnterVec(playerid,true);
				System_send(playerid,"[���Ի�����]�㿪���˽��뽻ͨ��������Nos�Ĺ���");
			}
		}/*else if(compare("godmode",2)){
			if(sb_gpGodmode(playerid)){
				sb_spGodmode(playerid,false);
				System_send(playerid,"[���Ի�����]��ر���godmode");
			}else{
				sb_spGodmode(playerid,true);
				System_send(playerid,"[���Ի�����]�㿪����godmode");
			}
		}*/
		else if(compare("help",2)){
			System_send(playerid,"=========[���Ի���ϸ���ð���/��Ϣ]==========");
			System_send(playerid,"    /s set autonos          -  ����Nos����,��ǰ״̬:%d",sb_gpAutoNos(playerid));
			System_send(playerid,"    /s set autohealvec      -  ���������޳�Ѫ����,��ǰ״̬:%d",sb_gpAutoHealVec(playerid));
			System_send(playerid,"    /s set autorepairvec    -  �������Զ��޸���ͨ��������,��ǰ״̬:%d",sb_gpAutoRepairVec(playerid));
			System_send(playerid,"    /s set noswhenentervec  -  ���뽻ͨ��������Nos����,��ǰ״̬:%d",sb_gpAutoRepairVec(playerid));
			//System_send(playerid,"    /s set godmode          -  ����godmode(����������Ч),��ǰ״̬:%d",sb_gpGodmode(playerid));
			System_send(playerid,"===================================");
		}else{
			System_send(playerid,"[���Ի�����]�������������'%s'������,����/s set help �鿴����",params);
		}
	}else if(compare("register",1)){
		if(isnull(cmd_(2))){
			System_send(playerid,"[���Ի�����-����һ���ʺ�]��������Ի��ʺ�����");
			return true;
		}
		if(fexist(sb_getFile(cmd_(2)))){
			System_send(playerid,"[���Ի�����-����һ���ʺ�]��������ʺ��Ѵ���");
			return true;
		}
		if(isnull(cmd_(3))){
			System_send(playerid,"[���Ի�����-����һ���ʺ�]��������Ի��ʻ�����");
			return true;
		}
		if(!sb_pregister(playerid,cmd_(2),cmd_(3))){
			System_send(playerid,"[���Ի�����-����һ���ʺ�]ע��ʧ�ܣ�����ϵ����Ա");
		}
		System_send(playerid,"[���Ի�����-����һ���ʺ�]ע��ɹ������ס�ʺ�����!");
		System_send(playerid,"�ʺ�:%s",sb_gpAccountName(playerid));
		System_send(playerid,"����:%s",sb_gpAccountPass(playerid));
		System_send(playerid,"[���Ի�����-����һ���ʺ�]���Ժ����ʹ��/s reset [�ʺ�] [����] ��ʱ�޸�");
	}else if(compare("login",1)){
		if(isnull(cmd_(2))){
			System_send(playerid,"[���Ի�����-��½]��������Ի��ʺ�����");
			return true;
		}
		if(!sb_plogin(playerid,cmd_(2))){
			System_send(playerid,"[���Ի�����-��½]��������ʺŲ�����");
			return true;
		}
		System_send(playerid,"[���Ի�����-��½]��½�ɹ�");
	}else if(compare("reset",1)){
		if(isnull(cmd_(2))){
			System_send(playerid,"[���Ի�����-���������ʺ�]��������Ի��ʻ�����");
			return true;
		}
		if(!fexist(sb_getFile(cmd_(2)))){
			System_send(playerid,"[���Ի�����-��½]��������ʺŲ�����");
			return true;
		}
		if(isnull(cmd_(3))){
			System_send(playerid,"[���Ի�����-���������ʺ�]��������Ի��ʻ�����");
			return true;
		}
		gini_open(sb_getFile(cmd_(2)));
		if(!compare(gini_reads(subaccount_Pass),3)){
			System_send(playerid,"[���Ի�����-���������ʺ�]���������ȷ������");
			return true;
		}
		sb_spDatatoFile(playerid,sb_getFile(cmd_(2)));
		System_send(playerid,"[���Ի�����-���������ʺ�]�������óɹ���");
	}else if(compare("help",1)){
		System_send(playerid,"=========[���Ի����ð���]==========");
		System_send(playerid,"    /s register [�ʺ�] [����]  -  ע��һ���ʺ�");
		System_send(playerid,"    /s login    [�ʺ�]         -  ʹ���ض��ʺŵĸ��Ի�����");
		System_send(playerid,"    /s reset    [�ʺ�] [����]  -  ��������һ���ʺŵ���Ϣ");
		System_send(playerid,"    /s set help                -  ��ϸ���ð���/���Ի�������Ϣ");
		System_send(playerid,"===================================");
	}else{
		System_send(playerid,"[���Ի�����]�������������'%s'������,����/s help �鿴����",params);
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






























