#include <a_samp>
#include <a_http>

#define delay_fight_time			(800)

//#define HTTP(%1) HTTP_LOOP(%1)
stock HTTP_LOOP(){}

//viewfaction&id=3422207
main(){}
new
	structinfo[][] = 
		{
			//new income
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=ATlp6wXI7sF1DWiuRF7ZO4bp==&zapp_uin=346265676",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AUzVrb4AUjmE9VMVuMIS8GeV==&zapp_uin=1473948330",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AUCAU4IytT5LVlCK2lB6TE7J==&zapp_uin=1784283639",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AfzjDTzmARjMo3L8dGV9Hm7h==&zapp_uin=1941512739",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AVV6kJJZNkkCxcH6ikJDbWiZ==&zapp_uin=1713452350", 
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AZ9vV89esctNW1QKU8nhaM8X==&zapp_uin=1946223017", 
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AUYjHZHHaXayO1vhJBFYTGv5==&zapp_uin=1653945720",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AZiMGE9qksOXTA1neZZI_nKX==&zapp_uin=1715094515",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AbH_KRXz23f3lu_zSOPZ9YrO==&zapp_uin=1337910720",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AWcgPLE70VLExunijFOKkjA2==&zapp_uin=1726804762", 
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AXeGbOwoOb8LLJGyUCJ8K1Vd==&zapp_uin=1761742560",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AfRcGDLnOBJ8nrdGp1OU64hD==&zapp_uin=1528712604",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AUg1oCrINo_zO4vEoz61V9nG==&zapp_uin=1527052064",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AcZsszFrB91QVO1WVbk7UuoG==&zapp_uin=1335838430", //到这里了(change name )
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AZjj9JGoon47M5e0qTb5Hy5W==&zapp_uin=2206781843", 
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AQzDFFyzVvXzk-HXzgVYPbV6==&zapp_uin=2206476510",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=Aaifg-VX5eEwgrkxQzSUObVE==&zapp_uin=1946810610",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AY3rt0BrOpgw6r4NuQJ7AZTs==&zapp_uin=1342229694",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AU6wWyayTsbu1s09HKRY1nHG==&zapp_uin=1336860125", 
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=ATv-dMue3oDy_bB-_DmiAmr0==&zapp_uin=1550889546",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=Ae6xZ4-qNkEF305M2pinT2ps==&zapp_uin=1531846723",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AeM7K5smdtoHZRPT4joKn072==&zapp_uin=1476821617",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AVTpOkMJhhbnceSYucLiSYwW==&zapp_uin=1446313039",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=Adoih9D9GoMvjET1J-31qNss==&zapp_uin=1522107633",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=Ad2lfA0niyrPumi-R2xkojzq==&zapp_uin=1600340619",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AQpzqWbdgjmmMn9zsw1ZqSCw==&zapp_uin=1826486432",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AR5zBQO2QwY8ic0SQi-iJghQ==&zapp_uin=1825227296",
			//end //special...old pass sid cannot make caicai
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AaP_O0j7M8O0Ts2A024AwmqR==&zapp_uin=1826893431",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=ATzTyNjTsNhmnqoaQQne5U7j==&zapp_uin=1737756572",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=ARHgw4ppkum3AQtBIVAE93-s==&zapp_uin=1776601913",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AYvCnOQvkscy4gF7SjZoyUy9==&zapp_uin=1586245288",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AfJiav6-V9r9-HcgsKeiYnEm==&zapp_uin=1820559359",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AXNpI188qA7mIce8RLAvT9bm==&zapp_uin=809438274",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=ATou2-85nd0SYM_GdScRl1kf==&zapp_uin=1824944908",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AYJntJwpN_Nb8LIoMdeGaDaK==&zapp_uin=1781951982",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AZobJbqd3VZdS2rBhgZ-t0td==&zapp_uin=1779163596",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AeF5Rrbny6-YjX30D2KkIYDX==&zapp_uin=1759006425",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AWW5wo3uIzxrpsMtXJr1LTBA==&zapp_uin=1820200992",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AVTwsz5Gx1-Hqfhi2gSTbJxQ==&zapp_uin=1433865165",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AZcCEEV6I1NK7UnotCqNLmms==&zapp_uin=1779039129",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=ARMhc8PCufuUNWBKvdutLxPx==&zapp_uin=1601877497",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AfUr6SFKbz3BmZmclHtryVEj==&zapp_uin=1764694172",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=Aev_1kXfu-bXNs0E_wiirbYS==&zapp_uin=1779513963",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AfwR9JO3NSOg33dHhO84QdnM==&zapp_uin=1781671412",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AckXG3lGduaRNBh1SKMWDFJ9==&zapp_uin=1820109950",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=ASbvfZksCdxY5GVwXvmDNNeG==&zapp_uin=1825121804",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=ATgFJ8aRB7gibU1-xi4TBrRR==&zapp_uin=1714047771",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AeRLZir3MSj4WzOaTbzYl8gG==&zapp_uin=1749613480",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AUIsQBYXwF1uPDySxWfMDNZi==&zapp_uin=1781098746",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=Afrp1xcyvsD6weKiGijaX_XK==&zapp_uin=1826617968",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=ASc9RRmcwwQILg8VJW-4atMw==&zapp_uin=1825519492",
			//old
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=Af9Uu1sRX1_i5MEkztXTN9An==&zapp_uin=1781576837",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AT7XznVHrPKGxfAqOuMquXYL==&zapp_uin=528999491",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=ARdYrAaCGfSqWa4XvLl5bkcZ==&zapp_uin=1755012868",
			//been gongfeng shouhushen
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=ATger8nFmj_DQ2wHBkjonUL2==&zapp_uin=1779465943",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AXH-uhtK_WG-bBOf0CTMdwOG==&zapp_uin=1760284314",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AZrXJkCy-gi9x68cqouXdYg9==&zapp_uin=1824627255",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AXWlZKtrN_ZkRlPrIyxTazht==&zapp_uin=1805115052",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AZjkw4XC8aSpQeHPISd5zdsy==&zapp_uin=1825549487",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=ARB6PDFryLbxZ1276bUl6Py2==&zapp_uin=1779443060",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=Aa6peT1jR24dXC45Wm_gMdjn==&zapp_uin=1737815078",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AewgBg9LajaOkyDCUAw3folk==&zapp_uin=1780382026",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AVpA6eMLhtt26E-auIabdto3==&zapp_uin=1529713462",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AblsQ4IdamqVXktonwY5kc87==&zapp_uin=1748063297",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AV1fdBs5qbtW2n0zB4PSfO6b==&zapp_uin=1171238295",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=FZoLnAJVWGi72D+H2b91Xw====&zapp_uin=624534405",//white
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=ATL82hdjPI5GRRt51u95sWD9==&zapp_uin=2469983721",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AQO3Wu6km57RQBChcSL0XLxG==&zapp_uin=2448174592",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AUoNQ8KU2XeGaufi7oz1oyX-==&zapp_uin=2442616261",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AYG2xIjSmJpaTcXTMyFbmyCF==&zapp_uin=2467470792",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AcS245cbQC4EF7837ouyvkFG==&zapp_uin=1319614114",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=Ae6__kDOU4l5wNBrLnBx7Qod==&zapp_uin=1911956595",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=Ae4brk2i3xa7hOxL-SDYCaxC==&zapp_uin=2447190680",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AaXfzOh-6XjWIF3n9hMnnhsS==&zapp_uin=2447123017",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AUn86gquWZbZ867j_KllPc5M==&zapp_uin=2440321571",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AbX0n-1LqcEEX8FFmEu84WvG==&zapp_uin=847957050",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=Aevspf7ZhriKVNmkHKYYqDAx==&zapp_uin=2463509550",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AXlEV0PVwvT0704lQRhxW7fB==&zapp_uin=2414264243",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AYkZ_vw_ue0R2ZNm1dpTgb-B==&zapp_uin=2466148959",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AXU8ifXNKMQxRALNAoOpGfCe==&zapp_uin=2457900318",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AQtLpRJO_XkeCzr86UKFzsnE==&zapp_uin=1183471232",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AZGlp0htMhfswCmcPsnKQPs5==&zapp_uin=2436708675",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AUg6EyAgUNJ2Isxp_vyTAlPT==&zapp_uin=2284990856",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=Aa5CazAXY-2FK0VfY_Ec6YHB==&zapp_uin=2460244494",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AaSBLK7ZTr6nry78n2GcP3Pf==&zapp_uin=1980468501",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AdMSlVYcVNFm9HLm-IeLsT-o==&zapp_uin=2421619699"
		};


new
	ledouaccount[150][1024];
new ledoupassword[150][1024];

//12猴王
//11月敏
//9 剑君
//7 菜菜
//10羊魔
//2 教主
//3 帅帅
//4 姜公
//-1selfclient
new ledouhttpqueryclient[][] = 
	{
		"+10",
		"+10",
		"+2",
		"+3",
		"+4",
		"+917736653",
		"+624534405", 
		"+121547921",
		"+568428967",
		"+982618390",
		"+346265676",
		"=445605449",
		"+1760284314",
		"+1529713462",
		"+1737756572",
		"+1826617968",
		"+1171238295",
		"+1737815078",
		"-1",
		"-1",
		"-1"
		//"+1776601913"
		/*
		"=7", 
		"=9",
		"=11",
		"=12",
		"=-1",
		"=-1",
		"=-1"
		*/
	};



forward ledou_fight_query(type,accountindex,clientindex);
forward ledou_query_result(index, response_code, data[]);
forward ledou_caicai_query(accountindex);
forward ledou_eatcaicai_query(accountindex);
forward ledou_refight_query(accountindex);
forward ledou_selffight_query();	
forward ledou_login_query(accountindex);
forward ledou_query_order(const order[]);


public ledou_query_order(const order[]){
	printf("-------------->[order]%s<--------------",order);
	if(!strcmp(order,"_start")){
		ledou_infoget_struct();
	}
	else if(!strcmp(order,"finish_getinfo")){ //"finish getinfo"
		ledou_login_query(0);
	}
	else if(!strcmp(order,"finish_login")){ // finish login
		ledou_caicai_query(0);
	}
	else if(!strcmp(order,"finish_caicai")){ // finish caicai
		ledou_fight_query(1,0,0);
		//ledou_selffight_query();
		//ledou_eatcaicai_query(0);
		SetTimer("ledou_selffight_query",1000*60*60,false);
		SetTimerEx("ledou_eatcaicai_query",1000*60*60*7,false,"i",0);
	}
	else if(!strcmp(order,"finish_selffight")){ //"finish_selffight"
		
	}	
	else if(!strcmp(order,"refight_aftereatcaicai")){ //"refight_aftereatcaicai"
		ledou_fight_query(1,0,0);
	}
	else if(!strcmp(order,"finish_eatcaicai")){
	}
}


ledou_infoget_struct(){
	for(new i;i < sizeof(structinfo);i++){
		strmid(ledoupassword[i],structinfo[i],55,strfind(structinfo[i],"==&zapp_uin"),1024);
		strmid(ledouaccount[i],structinfo[i],strfind(structinfo[i],"==&zapp_uin")+12,strlen(structinfo[i]),1024);
		for(new j, k = strlen(ledoupassword[i]);j < k;j++){
			//if(ledoupassword[i][j] == '='){
			//	ledoupassword[i][j] = '\0';
			//}
		}
	} 
	CallLocalFunction("ledou_query_order","s","finish_getinfo");
}

public ledou_login_query(accountindex){	
	new
		httpquery[512];
	static
		login_accountindex;
	if(login_accountindex < sizeof(structinfo)){
		format(httpquery,sizeof(httpquery),"dld.qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=%s&zapp_uin=%s",ledoupassword[login_accountindex],ledouaccount[login_accountindex]);
		HTTP(0, HTTP_GET, httpquery,"", "ledou_query_result");
		SetTimerEx("ledou_login_query",delay_fight_time,false,"i",login_accountindex); 
	}
	if(login_accountindex >= sizeof(structinfo)){
		CallLocalFunction("ledou_query_order","s","finish_login");
	}
	login_accountindex++;
}
public ledou_caicai_query(accountindex){
	new
		httpquery[512];	
	static
		caicai_accountindex;
	//printf("caicai_accountindex:%d,a:%s,p:%s",caicai_accountindex,ledouaccount[caicai_accountindex],ledoupassword[caicai_accountindex]);	
	if(caicai_accountindex < sizeof(structinfo)){
		format(httpquery,sizeof(httpquery),"dld.qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=%s&zapp_sid=%s&cmd=caicai",ledouaccount[caicai_accountindex],ledoupassword[caicai_accountindex]);
		HTTP(0, HTTP_GET, httpquery,"", "ledou_query_result");
		SetTimerEx("ledou_caicai_query",delay_fight_time,false,"i",caicai_accountindex); 
	}
	if(caicai_accountindex >= sizeof(structinfo)){
		CallLocalFunction("ledou_query_order","s","finish_caicai");
	}
	caicai_accountindex++;
}
public ledou_eatcaicai_query(accountindex){
	new
		httpquery[512];	
	static
		eatcaicai_accountindex;
	//printf("eatcaicai_accountindex:%d,a:%s,p:%s",eatcaicai_accountindex,ledouaccount[eatcaicai_accountindex],ledoupassword[eatcaicai_accountindex]);
	if(eatcaicai_accountindex < sizeof(structinfo)){	
		format(httpquery,sizeof(httpquery),"dld.qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=%s&zapp_sid=%s&cmd=eatcaicai",ledouaccount[eatcaicai_accountindex],ledoupassword[eatcaicai_accountindex]);
		HTTP(0, HTTP_GET, httpquery,"", "ledou_query_result");
		SetTimerEx("ledou_eatcaicai_query",delay_fight_time,false,"i",eatcaicai_accountindex); 
	}
	if(eatcaicai_accountindex >= sizeof(structinfo)){ //add up to 12 ledou query
		CallLocalFunction("ledou_query_order","s","finish_eatcaicai");
		new
			y,m,d,
			dayindex;
		getdate(y,m,d);
		dayindex = d;
		//printf("oha:%d",!(dayindex%2));
		if(!(dayindex%2)){
			CallLocalFunction("ledou_query_order","s","refight_aftereatcaicai");
		}	
	}
	eatcaicai_accountindex++;
}	
public ledou_selffight_query(){	
	static 
		selftype;
	switch(selftype){
		/*
		case 1:{
			HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=10&page=","", "ledou_query_result");
		}			
		case 2:{
			HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=2&page=","", "ledou_query_result");
		}			
		case 3:{
			HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=3&page=","", "ledou_query_result");
		}			
		case 4:{
			HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=4&page=","", "ledou_query_result");
		}
		case 5:{
			HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&zapp_uin=445605449","", "ledou_query_result");
		}			
		case 6:{
			HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=917736653&page=","", "ledou_query_result");
		}
		case 7:{
			HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=7&page=","", "ledou_query_result");
		}
		case 8:{
			HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=937836707&page=","", "ledou_query_result");
		}
		case 9:{
			HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=543425691&page=","", "ledou_query_result");
		}
		case 10:{
			HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=305337910&page=","", "ledou_query_result");
		}
		case 11:{
			HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=1139054999&page=","", "ledou_query_result");
		}
		case 12:{
			HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=121547921&page=","", "ledou_query_result");
		}
		case 13:{
			HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=522710441&page=","", "ledou_query_result");
		}
		*/
		//445605449
		case 14:{
			HTTP(0, HTTP_GET, "dld.qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=346265676&zapp_sid=augzo3hdQHIJ7bxttZ8LyQ==&cmd=exp","", "ledou_query_result");
		}
		/*
		case 15:{
			HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&B_UID=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=exp","", "ledou_query_result");
		}
		*/
		case 16:{
			CallLocalFunction("ledou_query_order","s","finish_selffight");
			return true;
		}
		
	}
	selftype++;
	SetTimer("ledou_selffight_query",delay_fight_time,false); //start clent2
	return true;
}
public ledou_fight_query(type,accountindex,clientindex){
	new
		httpquery[512];
	if(type == 1 || type == 2){ //fight query
		if(ledouhttpqueryclient[clientindex][0] == '+'){ //gang ledou
			strdel(ledouhttpqueryclient[clientindex],0,1);
			format(httpquery,sizeof(httpquery),"dld.qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=%s&zapp_sid=%s&cmd=fight&B_UID=%s&page=1&type=2",ledouaccount[accountindex],ledoupassword[accountindex],ledouhttpqueryclient[clientindex]);
			strins(ledouhttpqueryclient[clientindex],"+", 0,1024);
			//printf("gangfight:%s",httpquery);
		}
		else if(ledouhttpqueryclient[clientindex][0] == '='){ //friend ledou
			strdel(ledouhttpqueryclient[clientindex],0,1);
			if(!strcmp(ledouhttpqueryclient[clientindex],"-1")){ //selfclient
				format(httpquery,sizeof(httpquery),"dld.qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=%s&zapp_sid=%s&cmd=fight&B_UID=%s&page=1&type=1",ledouaccount[accountindex],ledoupassword[accountindex],ledouaccount[accountindex]);
				//printf("selffight:%s",httpquery);
			}
			else { //custom client
				format(httpquery,sizeof(httpquery),"dld.qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=%s&zapp_sid=%s&cmd=fight&B_UID=%s&page=1&type=1",ledouaccount[accountindex],ledoupassword[accountindex],ledouhttpqueryclient[clientindex]);
				//printf("customfight:%s",httpquery);
			}		
			strins(ledouhttpqueryclient[clientindex],"=", 0,1024);

		}		

	}
	HTTP(0, HTTP_GET, httpquery,"", "ledou_query_result");
	clientindex++;
	if(clientindex >= sizeof(ledouhttpqueryclient)){ //a client unit finished
		accountindex++;
		clientindex = 0;//
		if(accountindex == sizeof(structinfo)){ //all account units finished
			//SetTimerEx("ledou_fight_query",delay_fight_time,false,"iii",3,accountindex,clientindex); //start clent2
			//printf("ledou process has finished, unload ledou.amx within 60seconds");
			//printf("ledou process has finished");
			return false;
		}
		SetTimerEx("ledou_fight_query",delay_fight_time,false,"iii",1,accountindex,clientindex);
		//printf("new account tested:%d",accountindex);
	}
	else { //continue a client unit
		SetTimerEx("ledou_fight_query",delay_fight_time,false,"iii",2,accountindex,clientindex);
	}
	return true;
}
public ledou_query_result(index, response_code, data[]){
	static codeindex;
	//printf("code index:%d result:%d",codeindex,response_code);
	codeindex++;
	return true;
}


public OnFilterScriptInit(){
	/*
	ledou_infoget_struct();
	print ("ready");
	ledou_caicai_query(0);
	print ("set");
	new tick = GetTickCount();
	while(GetTickCount() - tick < 3000){}
	print ("go");
	ledou_fight_query(1,0,0);
	*/
	SetTimerEx("ledou_query_order",1000,false,"s","_start");//ledou_query_order("start");
	return true;
}

public OnFilterScriptExit(){
	return true;
}