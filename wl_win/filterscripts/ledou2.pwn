#include <a_samp>
#include <a_http>

#define delay_fight_time			(800)

main(){}

new
	structinfo[][] = 
		{
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=gtney7JeS6+eUDQfWc3U8g==&zapp_uin=1826893431",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=BI78TdB91hj0+1a9x8GZ+w==&zapp_uin=1737756572",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=Z7CgArWWEYYOW8B4KIqRXw==&zapp_uin=1776601913",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=eVrawxdwAWmKNNFyHaTqqw==&zapp_uin=1586245288",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AYcA5HiDBiurvGi9N7wL7g==&zapp_uin=1820559359",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=nx1oBXegVWMpuYzT+U8JbA==&zapp_uin=809438274",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AQnOkSSKkurrQUY/xp8PMQ==&zapp_uin=1824944908",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=RHgIesQkHuvJnod8MiReAw==&zapp_uin=1781951982",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=2lt2rUbB4X6azvFzryJhtA==&zapp_uin=1779163596",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=moYsgQchUnyi7oPDDoT8/w==&zapp_uin=1759006425",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=+aRO+IA82qo7rMUA0Cqeug==&zapp_uin=1820200992",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=fg4YGSHTyoryJfapiJlndA==&zapp_uin=1825519492",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=lvFCrZYuiDG3sRMFnLFoow==&zapp_uin=1433865165",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=9cKySo9wq1KPnZmbE6bsyw==&zapp_uin=1779039129",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=o9/gkcsTCMxQ5z1zZOAKrA==&zapp_uin=1601877497",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=T9j8BWaWW3ewKl5XSMVJ6A==&zapp_uin=1764694172",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=Gp0hAY9auJjB0sABVY7MQw==&zapp_uin=1779513963",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=SlWhREVHywG9ou9IkI++cA==&zapp_uin=1781671412",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=AjgJOZDvtKBSYb8/ZDmepA==&zapp_uin=1820109950",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=VAe6uUOPLz4FG0pMvZAQUQ==&zapp_uin=1825121804",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=7r89c1xJF65RWqBl5LDacQ==&zapp_uin=1714047771",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=o4cSjk3cl58bnXeX4tO2JA==&zapp_uin=1749613480",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=Z3IYjJzEPPXovXsulygAMg==&zapp_uin=1781098746",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=2k8t+OsjFzyuACT/QzASwQ==&zapp_uin=1826617968",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=K2Sy0f/ywF7yJfapiJlndA==&zapp_uin=1825519492",
			//old
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=cLJ8gKY50Xs1X0WNgCpsIA==&zapp_uin=1826486432",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=/kn70/vNFmWPT2+lx+roeA==&zapp_uin=1781576837",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=IelzmwxWjz8ZQY5maj2KAA==&zapp_uin=528999491",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=7QeOqPOq1BRaKFBM09YuaA==&zapp_uin=1755012868",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=l4GmaUOw0iCQsrq2jFx9nw==&zapp_uin=1779465943",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=G0tUnGAGvzgJIGlTm5rWyQ==&zapp_uin=1760284314",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=eHAHDnX2ntHl2+5AAsayug==&zapp_uin=1824627255",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=gvW+dp3UJvcRYELuDe2PZw==&zapp_uin=1805115052",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=+5mSEk/LAhJI5t8jpF0+Ig==&zapp_uin=1825549487",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=n1LIlW/G1T8VQmiX+eyEAA==&zapp_uin=1779443060",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=yhq+A3CuE9vOJXfSC9tuOA==&zapp_uin=1737815078",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=uUC+fNh/ObSyqLajQBJ2lw==&zapp_uin=1780382026",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=Fxf87MWRYKOraNCU61RdIQ==&zapp_uin=1529713462",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=HzuACKfpz7/MN/MGW5aHqw==&zapp_uin=1748063297",
			"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=pY6Gvs0FxgOSNrH+ZtYA/Q==&zapp_uin=1171238295"
		};



new
	ledouaccount[][] = 
		{
			"1824944908",
			"1826486432",
			"1781576837",
			"1781951982",
			"1779163596",
			"528999491",
			"1826893431",
			"1737756572",
			"1776601913",
			"1586245288",
			"1820559359",
			"809438274",
			"1755012868",
			"1759006425",
			"1779465943",
			"1820200992",
			"1825519492",
			"1760284314",
			"1824627255",
			"1433865165",
			"1779039129",
			"1825227296",
			"1601877497",
			"1805115052",
			"1764694172",
			"1825549487",
			"1779443060", 
			"1737815078",
			"1779513963",
			"1780382026",
			"1529713462",
			"1748063297",
			"1781671412",
			"1820109950",
			"1825121804",
			"1171238295",
			"1714047771",
			"1749613480",
			"1781098746",
			"1826617968"
		};
		
new ledoupassword[][] =
	{
		"ewSetAf/gn8j3tHCfGnPzg",
		"dIx/ePhDEzg1X0WNgCpsIA",
		"vx9Dsm97ATyPT2%20lx%20roeA",
		"AGUAsqyMNA%207fa8ZQLI8Cw",
		"9fsaBidpl3DgmP1CC43uZQ",
		"Xp8UsPt0tnEZQY5maj2KAA",
		"6VWJUhvKdMqUJdfzTtiaxw",
		"zfTEsHfk2x3NhMvttLorBw",
		"S0z+CWljQqAZKIPX8s9HCw",
		"5lfp2HosvxtV22ZjW2GCdQ",
		"GX844jkhSyxBcUEOOWsR9Q",
		"ZrUfvRGAMU2My9Is7g0bOQ",
		"2sWoWq8B2OZaKFBM09YuaA",
		"mUbKTF5S4cpgMoWdKeDBZA",
		"jPoUK13gEOOQsrq2jFx9nw",
		"P/OOnyGmribBRFrLqSH0bw",
		"rk103UpJEge/QbnvDkmhWw",
		"jHeY1b6eA/YJIGlTm5rWyQ",
		"W6fbxOK91Svl2%205AAsayug",
		"Vv4nDZ7ZATlYknmfWOH10A",
		"oaoRIAo8LyAh3hFMyOPwtw",
		"YRH5RurWMTMlfq%20N99uz1Q",
		"IEORooUhicBCv0F93mDsMg",
		"7pIwh8mPA0oRYELuDe2PZw",
		"KaPQG8anMJ4bRkJG9/ZnPA",
		"fcdpruvjTbBI5t8jpF0Ig",
		"Gm7TYXpD9O8VQmiX%20eyEAA",
		"IfEhNjNhfYzOJXfSC9tuOA",
		"HbSDFImMZZwO4W4yaDhzMQ",
		"xPHg3uGxGfOyqLajQBJ2lw",
		"3Vmvo3F6TWCraNCU61RdIQ",
		"CqOvyLSQrvbMN/MGW5aHqw",
		"ygfY65RhcIcpaX7BSjqMYg",
		"lgDvKjPjk9QtlFr/elcrVg",
		"gOmKOYaWHSZIp/9AwIbmSg",	
		"hmRqa7yFsqLkr/WMWqekvw",
		"It7X8oMcSs/HMkUMge/P2w",
		"s8HOKV0kYTLDMKxJMsc2YA",
		"WS5WoDFLlXwFRb5GM/Nhvw",
		"Q3amGLs685wAl0fYE3xuuA"
	};

new ledouhttpqueryclient[][] = 
	{
		"-1", //selfclient
		"-1", 
		"7", //caicai
		"917736653",
		"346265676",
		"445605449",
		"121547921"
	};

ledou_struct(){
	for(new i;i < sizeof(structinfo);i++){
		strmid(ledoupassword[i],structinfo[i],55,strfind(structinfo[i],"==&zapp_uin"),256);
		strmid(ledouaccount[i],structinfo[i],strfind(structinfo[i],"==&zapp_uin")+12,strlen(structinfo[i]),256);
		//printf("index:%d account:%s password:%s",i,ledouaccount[i],ledoupassword[i]);
	}
}

forward ledou_fight_query(type,accountindex,clientindex);
forward ledou_query_result(index, response_code, data[]);


public ledou_fight_query(type,accountindex,clientindex){
	new
		httpquery[512];
	static codeindex2;
	//printf("type:%d accountindex:%d clientindex:%d",type,accountindex,clientindex);
	if(type == 1){ //login query
		format(httpquery,sizeof(httpquery),"dld.qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=%s&zapp_uin=%s",ledoupassword[accountindex],ledouaccount[accountindex]);
	}
	else if(type == 2){ //fight query
		format(httpquery,sizeof(httpquery),"dld.qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=%s&zapp_sid=%s&cmd=ask&id=3422207",ledouaccount[accountindex],ledoupassword[accountindex]/*,ledouaccount[accountindex]*/);
		/*
		if(!strcmp(ledouhttpqueryclient[clientindex],"-1")){ //selfclient
			format(httpquery,sizeof(httpquery),"qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=%s&zapp_sid=%s==&cmd=fight&B_UID=%s&page=",ledouaccount[accountindex],ledoupassword[accountindex],ledouaccount[accountindex]);
		}
		else { //custom client
			format(httpquery,sizeof(httpquery),"qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=%s&zapp_sid=%s==&cmd=fight&B_UID=%s&page=",ledouaccount[accountindex],ledoupassword[accountindex],ledouhttpqueryclient[clientindex]);
		}
		*/
	}
	//346265676&zapp_sid=augzo3hdQHIJ7bxttZ8LyQ==&cmd=ask&id=3422207
	/*
	else if(type >= 3){ //client2
		switch(type){
			case 4:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=smUoasyuYXtQ+r1kiDh3Ag==&zapp_uin=917736653","", "ledou_query_result");
			}
			case 5:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=917736653&zapp_sid=smUoasyuYXtQ+r1kiDh3Ag==&cmd=fight&B_UID=10&page=","", "ledou_query_result");
			}
			case 6:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=917736653&zapp_sid=smUoasyuYXtQ+r1kiDh3Ag==&cmd=fight&B_UID=2&page=","", "ledou_query_result");
			}
			case 7:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=917736653&zapp_sid=smUoasyuYXtQ+r1kiDh3Ag==&cmd=fight&B_UID=3&page=","", "ledou_query_result");
			}
			case 8:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=917736653&zapp_sid=smUoasyuYXtQ+r1kiDh3Ag==&cmd=fight&B_UID=4&page=","", "ledou_query_result");
			}
			case 9:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=917736653&zapp_sid=smUoasyuYXtQ+r1kiDh3Ag==&cmd=fight&B_UID=1820559359&page=","", "ledou_query_result");
			}
			case 10:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=917736653&zapp_sid=smUoasyuYXtQ+r1kiDh3Ag==&cmd=fight&B_UID=1529713462&page=","", "ledou_query_result");
			}
			case 11:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=917736653&zapp_sid=smUoasyuYXtQ+r1kiDh3Ag==&cmd=fight&B_UID=1826617968&page=","", "ledou_query_result");
			}
			case 12:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=917736653&zapp_sid=smUoasyuYXtQ+r1kiDh3Ag==&cmd=fight&B_UID=1760284314&page=","", "ledou_query_result");
			}
			case 13:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=917736653&zapp_sid=smUoasyuYXtQ+r1kiDh3Ag==&cmd=fight&B_UID=346265676&page=","", "ledou_query_result");
			}
			case 14:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=917736653&zapp_sid=smUoasyuYXtQ+r1kiDh3Ag==&cmd=fight&B_UID=445605449&page=","", "ledou_query_result");
			}
			case 15:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=917736653&zapp_sid=smUoasyuYXtQ+r1kiDh3Ag==&cmd=fight&B_UID=7&page=","", "ledou_query_result");
			}
			case 16:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=917736653&zapp_sid=smUoasyuYXtQ+r1kiDh3Ag==&cmd=fight&B_UID=121547921&page=","", "ledou_query_result");
			} // 10 2 3 4
			//917736653
			case 17:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=augzo3hdQHIJ7bxttZ8LyQ==&zapp_uin=346265676","", "ledou_query_result");
			}
			case 18:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=346265676&zapp_sid=augzo3hdQHIJ7bxttZ8LyQ==&cmd=fight&B_UID=376524939&page=","", "ledou_query_result");
			}
			case 19:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=346265676&zapp_sid=augzo3hdQHIJ7bxttZ8LyQ==&cmd=fight&B_UID=917736653&page=","", "ledou_query_result");
			}
			case 20:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=346265676&zapp_sid=augzo3hdQHIJ7bxttZ8LyQ==&cmd=fight&B_UID=453036186&page=","", "ledou_query_result");
			}
			case 21:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=346265676&zapp_sid=augzo3hdQHIJ7bxttZ8LyQ==&cmd=fight&B_UID=7&page=","", "ledou_query_result");
			}
			case 22:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=346265676&zapp_sid=augzo3hdQHIJ7bxttZ8LyQ==&cmd=fight&B_UID=9&page=","", "ledou_query_result");
			}
			case 23:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=346265676&zapp_sid=augzo3hdQHIJ7bxttZ8LyQ==&cmd=fight&B_UID=346265676&page=","", "ledou_query_result");
			}
			case 24:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=346265676&zapp_sid=augzo3hdQHIJ7bxttZ8LyQ==&cmd=fight&B_UID=346265676&page=","", "ledou_query_result");
			}
			case 25:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=346265676&zapp_sid=augzo3hdQHIJ7bxttZ8LyQ==&cmd=fight&B_UID=346265676&page=","", "ledou_query_result");
			}
			//346265676
			case 26:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=10&page=","", "ledou_query_result");
			}			
			case 27:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=2&page=","", "ledou_query_result");
			}			
			case 28:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=3&page=","", "ledou_query_result");
			}			
			case 29:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=4&page=","", "ledou_query_result");
			}
			case 30:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&zapp_uin=445605449","", "ledou_query_result");
			}			
			case 31:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=917736653&page=","", "ledou_query_result");
			}
			case 32:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=7&page=","", "ledou_query_result");
			}
			case 33:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=937836707&page=","", "ledou_query_result");
			}
			case 34:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=543425691&page=","", "ledou_query_result");
			}
			case 35:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=305337910&page=","", "ledou_query_result");
			}
			case 36:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=1139054999&page=","", "ledou_query_result");
			}
			case 37:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=121547921&page=","", "ledou_query_result");
			}
			case 38:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=fight&B_UID=522710441&page=","", "ledou_query_result");
			}
			//445605449
			case 39:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=346265676&B_UID=346265676&zapp_sid=augzo3hdQHIJ7bxttZ8LyQ==&cmd=exp","", "ledou_query_result");
			}
			case 40:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=445605449&B_UID=445605449&zapp_sid=QfdxVFBDFtIlhdFoOKKpaw==&cmd=exp","", "ledou_query_result");
			}
			case 41:{
				HTTP(0, HTTP_GET, "qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=917736653&B_UID=917736653&zapp_sid=smUoasyuYXtQ+r1kiDh3Ag==&cmd=exp","", "ledou_query_result");
			}
			case 42:{
				printf("ledou process has finished");
				return true;
			}
			
		}
		//printf("index:%d",type);
		type++;
		SetTimerEx("ledou_fight_query",delay_fight_time,false,"iii",type,accountindex,clientindex); //start clent2
		return true;
	}
	*/
	HTTP(0, HTTP_GET, httpquery,"", "ledou_query_result");
	//printf("%s : %d",httpquery,codeindex2++);
	clientindex++;
	if(clientindex == sizeof(ledouhttpqueryclient)){ //a client unit finished
		accountindex++;
		clientindex = 0;
		if(accountindex == sizeof(ledouaccount)){ //all account units finished
			SetTimerEx("ledou_fight_query",delay_fight_time,false,"iii",3,accountindex,clientindex); //start clent2
			//printf("ledou process has finished, unload ledou.amx within 60seconds");
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
	SetTimerEx("ledou_fight_query",delay_fight_time+2549,false,"iii",1,0,0);
	return true;
}

public OnFilterScriptExit(){
	//printf("ledou process has ended.");
	return true;
}


//new ledouhttpqueryhead[] = 	"qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=";
//new ledouhttpquerymid1[] = "&zapp_sid=";
//new ledouhttpquerymid2[] = "==&cmd=fight&B_UID=";
//new ledouhttpquerybottom[] = "&page=";
//new ledouhttpquery[1024];
/*
public ledoutest_timer(){
	new
		timeprefix,
		httpquery[512];
	for(new i;i < sizeof(ledouaccount);i++){
		format(httpquery,sizeof(httpquery),"qzapp.z.qq.com/qpet/cgi-bin/phonepk?cmd=index&zapp_sid=%s==&zapp_uin=%s",ledoupassword[i],ledouaccount[i]);
		pause(400);timeprefix += 400;
		ledou_fight_httpquery(httpquery);
		
		format(httpquery,sizeof(httpquery),"qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=%s&zapp_sid=%s==&cmd=fight&B_UID=%s&page=",ledouaccount[i],ledoupassword[i],"7");
		pause(400);timeprefix += 400;
		ledou_fight_httpquery(httpquery);
		
		format(httpquery,sizeof(httpquery),"qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=%s&zapp_sid=%s==&cmd=fight&B_UID=%s&page=",ledouaccount[i],ledoupassword[i],ledouaccount[i]);
		pause(400);timeprefix += 400;
		ledou_fight_httpquery(httpquery);		

		format(httpquery,sizeof(httpquery),"qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=%s&zapp_sid=%s==&cmd=fight&B_UID=%s&page=",ledouaccount[i],ledoupassword[i],ledouaccount[i]);
		pause(400);timeprefix += 400;
		ledou_fight_httpquery(httpquery);	
		
		//SetTimerEx("ledou_fight_httpquery",timeprefix,0,"s",httpquery);
		//http://qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=1826617968&zapp_sid=Q3amGLs685wAl0fYE3xuuA==&cmd=fight&B_UID=7&page=1
		//http://qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=1826617968&zapp_sid=Q3amGLs685wAl0fYE3xuuA==&cmd=fight&B_UID=1826617968&page=
		for(new j;j < sizeof(ledouhttpqueryclient);j++){
			format(httpquery,sizeof(httpquery),"qzapp.z.qq.com/qpet/cgi-bin/phonepk?zapp_uin=%s&zapp_sid=%s==&cmd=fight&B_UID=%s&page=",ledouaccount[i],ledoupassword[i],ledouhttpqueryclient[j]);
			pause(400);timeprefix += 400;
			ledou_fight_httpquery(httpquery);
			//timeprefix += 400;
			//SetTimerEx("ledou_fight_httpquery",timeprefix,0,"s",httpquery);
			//printf("set %s (%s) attack %s",ledouaccount[i],ledoupassword[i],ledouhttpqueryclient[j]);
		}
	}
	pause(5000);
	printf("Ledou ended, total used time :%d ms",timeprefix);
}
*/

/*
pause(ms){
	new
		tick = GetTickCount();
	while(GetTickCount() - tick < ms){}
}
*/

//forward ledoutest(index, response_code, data[]);
//forward ledoutest_timer();
//public ledoutest(index, response_code, data[]){
	/*
	new
		tmpstr[500];
	format(tmpstr,sizeof(tmpstr),data);
	print("=======");
	printf("index:%d response_code:%d data:%d",index,response_code,strlen(data));
	print(tmpstr);
	if(strfind(tmpstr,"落花",.ignorecase = true) != -1){
		printf("win");
	}
	else if(strfind(tmpstr,"寰堟姳姝夛",.ignorecase = true) != -1){
		printf("already");		
	}
	else if(strfind(tmpstr,"摆平",.ignorecase = true) != -1){
		printf("lose");	
	}
	else if(strfind(tmpstr,"不足",.ignorecase = true) != -1){
		printf("lack strenth");	
	}
	else {
		printf("unknown");
	}
	
	print("=======");
	*/
	/*
	落花 - 胜利
	换个好友 - 已挑
	摆平 - 失败
	*/
//}