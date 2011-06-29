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

#define WL_MODE_NAME		"wl" //Do not modtify
#define WL_VERSION			"0.6.8.3"
#define WL_BUILD_TIME		"201106280030"

#define MAX_FILE_STR	(256)
#define MAX_MSG_STR		(128)
#define MAX_DIALOG_STR	(2046)
#define MAX_SQL_STR		(1024)

#include <wl\wl_main>

//===========================================================================================//
/*
*	Copyright
*		You can add some more infomation, 
*		but do not remove any COPYRIGHT information.
*/
wl_copyright(){
	printf ("===============================================================================");
	printf ("  GameMode:%s",WL_MODE_NAME);
	printf ("  Version: %s",WL_VERSION);
	printf ("  Build:   %s",WL_BUILD_TIME);
	printf ("  Contributors(Alphabetical order):");
	printf ("    FGJin, fly_luck,  [ITC]dyq  [ITC]fangye  [ITC]Super_wlc  [ITC]RR_LXD");
	printf ("    mk124  Shindo(aka. ssh)  vvg, yezizhu(aka. yzz)");
	printf ("  This is a part of OpenGTA project, visit www.opengta.org for more info.");
	printf ("  Contact us: imyezizhu@opengta.org");
	printf ("  Copyright: yezizhu & GCS Team");
	printf ("===============================================================================");
}
zcmd(wl,playerid,params[]){
	System_send (playerid,"===============================================================================");
	System_send (playerid,"  GameMode:%s",WL_MODE_NAME);
	System_send (playerid,"  Version: %s",WL_VERSION);
	System_send (playerid,"  Build:   %s",WL_BUILD_TIME);
	System_send (playerid,"  Contributors(Alphabetical order):");
	System_send (playerid,"    FGJin, fly_luck,  [ITC]dyq  [ITC]fangye  [ITC]Super_wlc  [ITC]RR_LXD");
	System_send (playerid,"    mk124  Shindo(aka. ssh)  vvg, yezizhu(aka. yzz)");
	System_send (playerid,"  This is a part of OpenGTA project, visit www.opengta.org for more info.");
	System_send (playerid,"  Contact us: imyezizhu@opengta.org");
	System_send (playerid,"  Copyright: yezizhu & GCS Team");
	System_send (playerid,"===============================================================================");	
	return true;
}
/*
*
*
*
*
*/
//===========================================================================================//
stock debug_public_track(str[]){
	//printf("%s",str);
	new y,d,m,h,minute,s;
	getdate(y,d,m);
	gettime(h,minute,s);
	printf("[%04d/%02d/%02d-%02d:%02d:%02d]%s",y,d,m,h,minute,s,str);
}
main(){
	wl_copyright();
}

public OnPlayerLogin(playerid){ debug_public_track("OnPlayerLogin(playerid)");
	dmw_playerLogin(playerid);
	return true;
}

forward autoRestart();
public autoRestart(){ debug_public_track("autoRestart()");
	new
		h,m,s;
	gettime(h,m,s);
	if(h == 7 && m == 50){
		SendRconCommand("exit");
	}
}

AntiDeAMX()
{
    new a[][] =
    {
        "Unarmed (Fist)",
        "Brass K"
    };
    #pragma unused a
}






















