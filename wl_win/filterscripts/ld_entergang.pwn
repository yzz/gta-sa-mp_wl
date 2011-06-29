#include <a_samp>
#include <a_http>

#define delay_fight_time			(1000)

main(){}

new
	structinfo[][] = 
		{
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
	ledouaccount[200][1024];
		
new ledoupassword[200][1024];

new ledouhttpqueryclient[][] = 
	{
		"121547921"
	};

ledou_struct(){
	for(new i;i < sizeof(structinfo);i++){
		strmid(ledoupassword[i],structinfo[i],55,strfind(structinfo[i],"==&zapp_uin"),1024);
		strmid(ledouaccount[i],structinfo[i],strfind(structinfo[i],"==&zapp_uin")+12,strlen(structinfo[i]),256);
		printf("index:%d account:%s password:%s",i,ledouaccount[i],ledoupassword[i]);
	}
}

forward ledou_fight_query(type,accountindex,clientindex);
forward ledou_query_result(index, response_code, data[]);


public ledou_fight_query(type,accountindex,clientindex){
	new
		httpquery[512];
	static codeindex2;
	format(httpquery,sizeof(httpquery),"dld.qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=%s&zapp_uin=%s",ledoupassword[accountindex],ledouaccount[accountindex]);
	printf("dld.qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=%s&zapp_uin=%s",ledoupassword[accountindex],ledouaccount[accountindex]);
	HTTP(0, HTTP_GET, httpquery,"", "ledou_query_result");
	format(httpquery,sizeof(httpquery),"dld.qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=%s&zapp_sid=%s&cmd=ask&id=3422207",ledouaccount[accountindex],ledoupassword[accountindex]/*,ledouaccount[accountindex]*/);
	printf("dld.qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=%s&zapp_sid=%s&cmd=ask&id=3422207",ledouaccount[accountindex],ledoupassword[accountindex]);
	//HTTP(0, HTTP_GET, httpquery,"", "ledou_query_result");
	//printf("%s : %d",httpquery,codeindex2++);
	clientindex++;
	
	if(clientindex == sizeof(ledouhttpqueryclient)){ //a client unit finished
		accountindex++;
		clientindex = 0;
		if(accountindex == sizeof(structinfo)){ //all account units finished
			SetTimerEx("ledou_fight_query",delay_fight_time,false,"iii",3,accountindex,clientindex); //start clent2
			printf("ledou process has finished, unload ledou.amx within 60seconds");
			//printf("ledou process has finished");
			return false;
		}
		SetTimerEx("ledou_fight_query",delay_fight_time,false,"iii",1,accountindex,clientindex);
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
	//printf("ledou process has started.");
	ledou_struct();
	SetTimerEx("ledou_fight_query",delay_fight_time,false,"iii",1,0,0);
	return true;
}

public OnFilterScriptExit(){
	//printf("ledou process has ended.");
	return true;
}

