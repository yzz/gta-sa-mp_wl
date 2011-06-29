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


//#include <wl\objective\wl_objective_borcast_h>

#define COLOR_BORCAST_WARNNING	(COLOR_WARNING)
#define COLOR_BORCAST_TIP		(COLOR_TIP)
#define COLOR_BORCAST_STUDY		(COLOR_STUDY)


#define BORCAST_TIME			(90)//second(s)


enum {
	e_objective_borcast_warning,
	e_objective_borcast_tip,
	e_objective_borcast_study,
	e_objective_borcast_amount
};

static stock
	wl_s_obj_borcast_type;

wl_objective_borcast_struction(){
	wl_objective_borcast_init();
	SetTimer("wl_objective_borcast_run",1000*BORCAST_TIME,1);
}

wl_objective_borcast_init(){
	new
		wl_borcast_warning_amount,
		wl_borcast_study_amount,
		wl_borcast_tip_amount,
		File:ofile,
		rstr[MAX_MSG_STR],
		hstr[MAX_MSG_STR],
		line;

	if(!fexist("wl/borcast_warning.ini")){
		printf(" 载入广播Warning错误,wl/borcast_warning.ini 不存在");
		return;
	}
	ofile = fopen("wl/borcast_warning.ini",io_read);
	line = 1;
	while(fread(ofile,rstr)){
		if(!sscanf(rstr,"s",hstr)){
			stripNewLine(hstr);
			SetGVarString("wl_borcast_warning",hstr, .id = wl_borcast_warning_amount);
			wl_borcast_warning_amount++;
		} 
		else {
			printf("  广播Warning部分载入失败，问题行:%d",line);
		}
	}
	SetGVarInt("wl_borcast_warning_Amount",wl_borcast_warning_amount);
	fclose(ofile);
	printf(" 广播Warning载入成功,数量:%d",wl_borcast_warning_amount);

	//

	if(!fexist("wl/borcast_tip.ini")){
		printf(" 载入广播Tip错误,wl/borcast_tip.ini 不存在");
		return;
	}
	ofile = fopen("wl/borcast_tip.ini",io_read);
	line = 1;
	while(fread(ofile,rstr)){
		if(!sscanf(rstr,"s",hstr)){
			stripNewLine(hstr);
			SetGVarString("wl_borcast_tip",hstr, .id = wl_borcast_tip_amount);
			wl_borcast_tip_amount++;
		} 
		else {
			printf("  广播Tip部分载入失败，问题行:%d",line);
		}
	}
	SetGVarInt("wl_borcast_tip_Amount",wl_borcast_tip_amount);
	fclose(ofile);
	printf(" 广播Tip载入成功,数量:%d",wl_borcast_tip_amount);
	//

	if(!fexist("wl/borcast_study.ini")){
		printf(" 载入广播Study错误,wl/borcast_study.ini 不存在");
		return;
	}
	ofile = fopen("wl/borcast_study.ini",io_read);
	line = 1;
	while(fread(ofile,rstr)){
		if(!sscanf(rstr,"s",hstr)){
			stripNewLine(hstr);
			SetGVarString("wl_borcast_study",hstr, .id = wl_borcast_study_amount);
			wl_borcast_study_amount++;
		} 
		else {
			printf("  广播Study部分载入失败，问题行:%d",line);
		}
	}
	SetGVarInt("wl_borcast_study_Amount",wl_borcast_study_amount);
	fclose(ofile);
	printf(" 广播Study载入成功,数量:%d",wl_borcast_study_amount);

}

forward wl_objective_borcast_run();
public wl_objective_borcast_run(){ debug_public_track("wl_objective_borcast_run(){");
	new
		borcast[MAX_MSG_STR];
	switch((wl_s_obj_borcast_type++)%4){
		case e_objective_borcast_warning:{
			GetGVarString("wl_borcast_warning",borcast, .id = random(GetGVarInt("wl_borcast_warning_Amount")));
			SendClientMessageToAll(COLOR_BORCAST_WARNNING,borcast);
		}
		case e_objective_borcast_tip:{
			GetGVarString("wl_borcast_tip",borcast, .id = random(GetGVarInt("wl_borcast_tip_Amount")));
			SendClientMessageToAll(COLOR_BORCAST_TIP,borcast);
		}
		case e_objective_borcast_study:{
			GetGVarString("wl_borcast_study",borcast, .id = random(GetGVarInt("wl_borcast_study_Amount")));
			SendClientMessageToAll(COLOR_BORCAST_STUDY,borcast);
		}
	}
}
