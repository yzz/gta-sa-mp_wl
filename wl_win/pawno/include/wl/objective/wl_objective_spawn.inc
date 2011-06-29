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


//#include <wl\objective\wl_objective_spawn_h>
/*
enum e_wl_obj_spawn_Data{
	Float:e_wl_obj_spawn_x,
	Float:e_wl_obj_spawn_y,
	Float:e_wl_obj_spawn_z,
	Float:e_wl_obj_spawn_a,
	e_wl_obj_spawn_Interior,
	e_wl_obj_spawn_String[MAX_STRING]
};



static const stock
	wl_s_obj_spawnInfo[][e_wl_obj_spawn_Data] = {
	//格式:出生点坐标X，出生点坐标Y，出生点坐标Z，出生面向角度，场景，提示内容
	//需要增加的话,请遵循这个格式
	//注意：最后一项不能有逗号
		{409.2281,2573.1426,16.3672,90.0, 0, ">> 出生在 /aa 大型特技场"},
		{1384.4961,-2442.0063,13.5547,90.0, 0,">> 出生在 /ls"},
		{1318.9706,1266.0952,10.8203,90.0, 0, ">> 出生在 /lv"},
		{-1642.7762,-197.9458,14.1484,90.0, 0, ">> 出生在 /sf"}//结尾不能有逗号
	};
*/
wl_obj_spawn_SpawnPlayer(playerid){
	new
		pos = random(sizeof(wl_s_obj_spawnInfo));
	TeleportPlayer(
		playerid,
		wl_s_obj_spawnInfo[pos][e_wl_obj_spawn_x],
		wl_s_obj_spawnInfo[pos][e_wl_obj_spawn_y],
		wl_s_obj_spawnInfo[pos][e_wl_obj_spawn_z],
		wl_s_obj_spawnInfo[pos][e_wl_obj_spawn_a],
		wl_s_obj_spawnInfo[pos][e_wl_obj_spawn_Interior],
		true
	);
	System_send(playerid,wl_s_obj_spawnInfo[pos][e_wl_obj_spawn_String]);
	return true;
}

