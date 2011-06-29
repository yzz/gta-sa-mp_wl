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




/*
enum e_wl_objective_object_Data{
	e_wl_objective_object_modelid,
	Float:e_wl_objective_object_ox,
	Float:e_wl_objective_object_oy,
	Float:e_wl_objective_object_oz,
	Float:e_wl_objective_object_rx,
	Float:e_wl_objective_object_ry,
	Float:e_wl_objective_object_rz
};

static const stock
	wl_s_obj_objectInfo[][e_wl_objective_object_Data] = {
	//格式：模型，坐标X，坐标Y，坐标Z，角度X，角度Y，角度Z
	//需要增加的话,请遵循这个格式
	//注意：最后一项不能有逗号
		{16771, 1854.919922, -2700.062256, 913.993896, 0.0000, 0.0000, 0.0000},
		{1634, 1844.271240, -1413.313965, 13.462946, 0.0000, 0.0000, 179.9996},
		{1634, 1848.378784, -1413.330078, 13.466778, 0.0000, 0.0000, 179.9996},
		{1634, 1852.512939, -1413.291504, 13.449255, 0.0000, 0.0000, 179.9996}//结尾不能有逗号
	};
*/
/*
wl_objective_object_struction(){
	Object_Object();
	for(new i,j = sizeof(wl_s_obj_objectInfo);i < j;i++)
	CreateDynamicObject(
		wl_s_obj_objectInfo[i][e_wl_objective_object_modelid],
		wl_s_obj_objectInfo[i][e_wl_objective_object_ox],
		wl_s_obj_objectInfo[i][e_wl_objective_object_oy],
		wl_s_obj_objectInfo[i][e_wl_objective_object_oz],
		wl_s_obj_objectInfo[i][e_wl_objective_object_rx],
		wl_s_obj_objectInfo[i][e_wl_objective_object_ry],
		wl_s_obj_objectInfo[i][e_wl_objective_object_rz]
	);
}
*/

wl_objective_object_struction(){
	//Object_Object();
	Streamer_TickRate(100);
	Streamer_VisibleItems(STREAMER_TYPE_OBJECT, 200);	
	if(!fexist("wl/objects.ini")){
		printf(" 载入obj错误,wl/objects.ini 不存在");
		return;
	}
	new 
		File:ofile = fopen("wl/objects.ini",io_read),
		rstr[256],
		objamount,line;
	while(fread(ofile,rstr)){
		new
			iom,Float:iox,Float:ioy,Float:ioz,Float:irx,Float:iry,Float:irz;
		line++;
		//printf("%d",line);
		if(!sscanf(rstr,"p,iffffff",iom,iox,ioy,ioz,irx,iry,irz)){
			//F_CreateObject(iom,iox,ioy,ioz,irx,iry,irz);
			//printf("%i,%f,%f,%f,%f,%f,%f",om,ox,oy,oz,rx,ry,rz);
			//CreateDynamicObject(om,ox,oy,oz,rx,ry,rz);
			new
				obj = CreateDynamicObject(iom,iox,ioy,ioz,irx,iry,irz,0,0);
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT,obj,E_STREAMER_DRAW_DISTANCE,300.0);
			//CreateDynamicObject(iom,iox,ioy,ioz,irx,iry,irz, .distance = 280.0, .worldid = 0 , .interiorid = 0);//yezizhu:streamer
			//CreateObject(iom,iox,ioy,ioz,irx,iry,irz, .DrawDistance = 280);
			objamount++;
		}else{
			//printf("  obj部分载入失败，问题行:%d",line);
			//printf("  问题行字符串:%s",rstr);
		}
	}
	fclose(ofile);
	printf(" 动态物件(object)载入成功,数量:%d",objamount);
	
}











