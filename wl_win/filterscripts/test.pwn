#include <a_samp>
#include <a_http>
main(){}

public OnFilterScriptInit(){
	//debug_setpublictrack();
	return true;
}

public hoho
{}

what public 

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

str[1]abc[991]; 

str[2]abc[992]; 

str[11]abc[993]; 

str[22]abc[994]; 

str[111]abc[995]; 

str[222]abc[996]; 

str[1111]abc[997]; 

str[2222]abc[999]; 