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


const 
	weather_changetime = 180,
	weather_changetime_mix = 60,
	weather_changetime_max = 120,
	weather_random_amount = 10;
enum {
	weather_normal,
	weather_brain,
	weather_rain,
	weather_hot,
	weather_foggy,
	weather_stromy,
	weather_danger,
	weather_type_amount
	
};
static
	const weather_prob[100] = {
		weather_normal,weather_normal,weather_normal,weather_normal,weather_normal,
		weather_normal,weather_normal,weather_normal,weather_normal,weather_normal,
		weather_normal,weather_normal,weather_normal,weather_normal,weather_normal,
		weather_normal,weather_normal,weather_normal,weather_normal,weather_normal,
		weather_normal,weather_normal,weather_normal,weather_normal,weather_normal,
		weather_normal,weather_normal,weather_normal,weather_normal,weather_normal,
		weather_normal,weather_normal,weather_normal,weather_normal,weather_normal,
		weather_brain,weather_brain,weather_brain,weather_brain,weather_brain,
		weather_brain,weather_brain,weather_brain,weather_brain,weather_brain,
		weather_normal,weather_normal,weather_normal,weather_normal,weather_normal,
		weather_normal,weather_normal,weather_normal,weather_normal,weather_normal,
		weather_normal,weather_normal,weather_normal,weather_normal,weather_normal,
		weather_normal,weather_normal,weather_normal,weather_normal,weather_normal,
		weather_hot,weather_hot,weather_hot,weather_hot,weather_hot,
		weather_hot,weather_hot,weather_hot,weather_hot,weather_hot,
		weather_hot,weather_hot,weather_hot,weather_hot,weather_hot,
		weather_hot,weather_hot,weather_hot,weather_hot,weather_hot,
		weather_hot,weather_hot,weather_hot,weather_hot,weather_hot,
		weather_hot,weather_hot,weather_hot,weather_hot,weather_hot,
		weather_hot,weather_hot,weather_hot,weather_hot,weather_hot
	};
static
	const weather_type[24*weather_type_amount*weather_random_amount] = {
			4,4,4,4,4,5,5,5,5,5,
			7,7,7,7,7,7,7,7,7,7,
			8,8,8,8,8,16,16,16,16,16,
			10,10,10,10,10,18,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,22,22,22,22,22,

			4,4,4,4,4,5,5,5,5,5,
			7,7,7,7,7,7,7,7,7,7,
			8,8,8,8,8,16,16,16,16,16,
			10,10,10,10,10,18,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,22,22,22,22,22,
			
			4,4,4,4,4,5,5,5,5,5,
			7,7,7,7,7,7,7,7,7,7,
			8,8,8,8,8,16,16,16,16,16,
			10,10,10,10,10,18,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,22,22,22,22,22,
		
			4,4,4,4,4,5,5,5,5,5,
			7,7,7,7,7,7,7,7,7,7,
			8,8,8,8,8,16,16,16,16,16,
			10,10,10,10,10,18,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,22,22,22,22,22,
		
			5,5,5,5,5,5,5,5,5,5,
			7,7,7,7,7,15,15,15,15,15,
			8,8,8,8,8,16,16,16,16,16,
			10,10,10,14,14,14,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,22,22,22,22,22,
	
			1,1,6,6,10,10,10,13,13,13,
			7,7,7,7,7,15,15,15,15,15,
			8,8,8,8,8,16,16,16,16,16,
			13,13,14,14,17,17,17,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,22,22,22,22,22,

			1,1,1,1,1,10,10,10,10,10,
			7,7,7,7,7,15,15,15,15,15,
			8,8,8,8,8,16,16,16,16,16,
			17,17,17,17,17,18,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,22,22,22,22,22,

			1,1,1,1,1,10,10,10,10,10,
			7,7,7,7,7,15,15,15,15,15,
			8,8,8,8,8,16,16,16,16,16,
			14,14,14,14,14,18,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,22,22,22,22,22,
		
			3,3,3,3,3,5,5,5,5,5,
			7,7,7,7,7,15,15,15,15,15,
			8,8,8,8,8,16,16,16,16,16,
			1,1,1,10,10,10,14,14,14,14,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,22,22,22,22,22,

			3,3,5,5,10,10,10,14,14,14,
			7,7,7,7,7,15,15,15,15,15,
			8,8,8,8,8,16,16,16,16,16,
			14,14,14,17,17,17,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,22,22,22,22,22,

			0,0,0,2,2,2,6,6,6,6,
			7,7,7,7,7,15,15,15,15,15,
			8,8,8,8,8,16,16,16,16,16,
			14,14,14,17,17,17,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,22,22,22,22,22,

			5,5,5,5,5,5,5,5,5,5,
			7,7,7,7,7,15,15,15,15,15,
			8,8,8,8,8,16,16,16,16,16,
			17,17,17,17,17,18,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,22,22,22,22,22,

			13,13,13,13,13,14,14,14,14,14,
			7,7,7,7,7,15,15,15,15,15,
			8,8,8,8,8,16,16,16,16,16,
			17,17,17,17,17,18,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,22,22,22,22,22,

			13,13,13,13,13,14,14,14,14,14,
			7,7,7,7,7,15,15,15,15,15,
			8,8,8,8,8,16,16,16,16,16,
			17,17,17,17,17,18,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,22,22,22,22,22,

			13,13,13,13,13,14,14,14,14,14,
			7,7,7,7,7,15,15,15,15,15,
			8,8,8,8,8,16,16,16,16,16,
			17,17,17,17,17,18,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,22,22,22,22,22,

			0,0,0,0,0,2,2,2,2,2,
			7,7,7,7,7,15,15,15,15,15,
			8,8,8,8,8,16,16,16,16,16,
			14,14,14,14,14,18,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,22,22,22,22,22,

			1,1,3,3,5,5,5,10,10,10,
			7,7,7,7,7,15,15,15,15,15,
			8,8,8,8,8,16,16,16,16,16,
			14,14,14,14,14,18,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,22,22,22,22,22,

			1,1,3,3,5,5,5,10,10,10,
			7,7,7,7,7,15,15,15,15,15,
			8,8,8,8,8,16,16,16,16,16,
			14,14,14,17,17,17,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,22,22,22,22,22,

			5,5,5,5,5,10,10,10,10,10,
			15,15,15,15,15,15,15,15,15,15,
			16,16,16,16,16,16,16,16,16,16,
			14,14,14,14,14,18,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,22,22,22,22,22,

			0,0,1,1,2,2,2,3,3,3,
			7,7,7,7,7,15,15,15,15,15,
			16,16,16,16,16,16,16,16,16,16,
			10,10,10,14,14,14,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,21,21,21,21,21,

			1,1,1,1,1,3,3,3,3,3,
			5,5,5,5,5,5,5,5,5,5,
			16,16,16,16,16,16,16,16,16,16,
			10,10,10,14,14,14,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,21,21,21,21,21,

			1,1,1,3,3,3,5,5,5,5,
			7,7,7,7,7,15,15,15,15,15,
			8,8,8,8,8,16,16,16,16,16,
			10,10,10,14,14,14,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,21,21,21,21,21,

			1,1,1,3,3,3,5,5,5,5,
			7,7,7,7,7,15,15,15,15,15,
			8,8,8,8,8,16,16,16,16,16,
			10,10,10,14,14,14,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,21,21,21,21,21,

			1,1,1,3,3,3,5,5,5,5,
			7,7,7,7,7,15,15,15,15,15,
			8,8,8,8,8,16,16,16,16,16,
			10,10,10,14,14,14,18,18,18,18,
			9,9,9,9,9,9,9,9,9,9,
			19,19,19,19,19,19,19,19,19,19,
			21,21,21,21,21,21,21,21,21,21
	};

static
	worldtime_hour = 19,
	worldtime_minute,
	world_weather;
forward ChangeWorldWeather();
public ChangeWorldWeather(){	 debug_public_track("ChangeWorldWeather(){	");
	new
		time_floor = worldtime_hour*weather_type_amount*weather_random_amount,
		weathertype_floor = weather_prob[random(sizeof(weather_prob))]*weather_random_amount,
		weatherid_float = random(weather_random_amount),
		changetime = 1000*(weather_changetime+random(weather_changetime_max-weather_changetime_mix)+weather_changetime_mix);
	world_weather = time_floor+weathertype_floor+weatherid_float;
	SetWeather(weather_type[world_weather]);
	//printf "weather->%04d|time:%04d,type:%04d,id%04d,id:%04d,time:%04d",
	//worldtime_hour,time_floor,weathertype_floor,weatherid_float,world_weather,changetime
	SetTimer("ChangeWorldWeather",changetime,false);
}
forward ChangeWorldTime();
public ChangeWorldTime(){ debug_public_track("ChangeWorldTime(){");
	worldtime_minute++;
	if(worldtime_minute > 59){
		worldtime_minute = 0;
		worldtime_hour++;
		if(worldtime_hour > 20){//worldtime_hour > 23
			worldtime_hour = 4;//worldtime_hour = 0;
		}
		loopPlayer(playerid){
			SetPlayerTime(playerid,worldtime_hour,0 /*worldtime_minute*/);
		}
	}

	return true;
}
wl_tmp_wt_Struction(){
	SetTimer("ChangeWorldTime",1000*1,true);
	ChangeWorldWeather();
}
wl_tmp_wt_PlayerConnect(playerid){
	#pragma unused playerid
	TogglePlayerClock(playerid,true);
}
wl_tmp_wt_PlayerSpawn(playerid){
	SetPlayerTime(playerid,worldtime_hour,worldtime_minute);
}
