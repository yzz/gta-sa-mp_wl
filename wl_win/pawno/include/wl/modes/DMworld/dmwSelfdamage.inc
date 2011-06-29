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
sd:selfdamage(self damaged)
*/

#define FILE_DMWORLD_SELFDAMAGE		"wl/DMWorld/selfdamage.cfg"

new 
	Float:sd_brasskunckle 		= 0.0,
	Float:sd_golfclub 			= 0.0,
	Float:sd_nitestick 			= 0.0,
	Float:sd_knife 				= 20.0,
	Float:sd_bat 				= 0.0,
	Float:sd_shovel 				= 0.0,
	Float:sd_poolstick 			= 0.0,
	Float:sd_katana 				= 0.0,
	Float:sd_chainsaw 			= 2.0,
	Float:sd_dildo 				= 0.0,
	Float:sd_dildo2 				= 0.0,
	Float:sd_vibrator 			= 0.0,
	Float:sd_vibrator2 			= 0.0,
	Float:sd_flower 				= 0.0,
	Float:sd_cane 				= 0.0,
	Float:sd_grenade 			= 15.0,
	Float:sd_teargas 			= 5.0,
	Float:sd_moltov 				= 10.0,
	Float:sd_colt45 				= 1.0,
	Float:sd_silenced 			= 1.0,
	Float:sd_deagle 				= 5.0,
	Float:sd_shotgun 			= 5.0,
	Float:sd_sawedoff 			= 2.5,
	Float:sd_shotgspa 			= 5.0,
	Float:sd_uzi 				= 1.0,
	Float:sd_mp5 				= 2.0,
	Float:sd_ak47 				= 2.5,
	Float:sd_m4 					= 3.0,
	Float:sd_tec9 				= 1.0,
	Float:sd_rifle 				= 4.0,
	Float:sd_sniper 				= 6.0,
	Float:sd_rocketlauncher 		= 20.0,
	Float:sd_heatseeker 			= 20.0,
	Float:sd_flamethrower 		= 3.0,
	Float:sd_minigun 			= 10.0,
	Float:sd_satchel 			= 10.0,
	Float:sd_bomb 				= 0.0,
	Float:sd_spraycan 			= 0.5,
	Float:sd_fireextinguisher 	= 0.5;

	


DMWrold_SelfDamage_Struct(){
	if(!fexist(FILE_DMWORLD_SELFDAMAGE)){
		fcreate(FILE_DMWORLD_SELFDAMAGE);
		gini_open(FILE_DMWORLD_SELFDAMAGE);
		gini_writef("weapon_brassknuckle",sd_brasskunckle);
		gini_writef("weapon_golfclub",sd_golfclub);				
		gini_writef("weapon_nitestick",sd_nitestick);				
		gini_writef("weapon_knife",sd_knife);					
		gini_writef("weapon_bat",sd_bat);						
		gini_writef("weapon_shovel",	sd_shovel);				
		gini_writef("weapon_poolstick",sd_poolstick);			
		gini_writef("weapon_katana",	sd_katana);				
		gini_writef("weapon_chainsaw",sd_chainsaw);					
		gini_writef("weapon_dildo",sd_dildo);					
		gini_writef("weapon_dildo2",	sd_dildo2);				
		gini_writef("weapon_vibrator",sd_vibrator);					
		gini_writef("weapon_vibrator2",sd_vibrator2);				
		gini_writef("weapon_flower",sd_flower);				
		gini_writef("weapon_cane",sd_cane);						
		gini_writef("weapon_grenade",sd_grenade);					
		gini_writef("weapon_teargas",sd_teargas);					
		gini_writef("weapon_moltov",sd_moltov);				
		gini_writef("weapon_colt45",sd_colt45);				
		gini_writef("weapon_silenced",sd_silenced);					
		gini_writef("weapon_deagle",sd_deagle);					
		gini_writef("weapon_shotgun",sd_shotgun);					
		gini_writef("weapon_sawedoff",sd_sawedoff);					
		gini_writef("weapon_shotgspa",sd_shotgspa);					
		gini_writef("weapon_uzi",sd_uzi);						
		gini_writef("weapon_mp5",sd_mp5);						
		gini_writef("weapon_ak47",sd_ak47);
		gini_writef("weapon_m4",sd_m4);
		gini_writef("weapon_tec9",sd_tec9);
		gini_writef("weapon_rifle",sd_rifle);
		gini_writef("weapon_sniper",sd_sniper);
		gini_writef("weapon_rocketlauncher",sd_rocketlauncher);
		gini_writef("weapon_heatseeker",sd_heatseeker);
		gini_writef("weapon_flamethrower",sd_flamethrower);
		gini_writef("weapon_minigun",sd_minigun);
		gini_writef("weapon_satchel",sd_satchel);
		gini_writef("weapon_bomb",sd_bomb);
		gini_writef("weapon_spraycan",sd_spraycan);
		gini_writef("weapon_fireextinguisher",sd_fireextinguisher);
		gini_save();
		gini_close();
	}
	gini_open(FILE_DMWORLD_SELFDAMAGE);
	sd_brasskunckle = gini_readf("weapon_brassknuckle");
	sd_golfclub = gini_readf("weapon_golfclub");				
	sd_nitestick = gini_readf("weapon_nitestick");				
	sd_knife = gini_readf("weapon_knife");					
	sd_bat = gini_readf("weapon_bat");						
	sd_shovel = gini_readf("weapon_shovel");				
	sd_poolstick = gini_readf("weapon_poolstick");			
	sd_katana = gini_readf("weapon_katana");				
	sd_chainsaw = gini_readf("weapon_chainsaw");					
	sd_dildo = gini_readf("weapon_dildo");					
	sd_dildo2 = gini_readf("weapon_dildo2");				
	sd_vibrator = gini_readf("weapon_vibrator");					
	sd_vibrator2 = gini_readf("weapon_vibrator2");				
	sd_flower = gini_readf("weapon_flower");				
	sd_cane = gini_readf("weapon_cane");						
	sd_grenade = gini_readf("weapon_grenade");					
	sd_teargas = gini_readf("weapon_teargas");					
	sd_moltov = gini_readf("weapon_moltov");				
	sd_colt45 = gini_readf("weapon_colt45");				
	sd_silenced = gini_readf("weapon_silenced");					
	sd_deagle = gini_readf("weapon_deagle");					
	sd_shotgun = gini_readf("weapon_shotgun");					
	sd_sawedoff = gini_readf("weapon_sawedoff");					
	sd_shotgspa = gini_readf("weapon_shotgspa");					
	sd_uzi = gini_readf("weapon_uzi");						
	sd_mp5 = gini_readf("weapon_mp5");						
	sd_ak47 = gini_readf("weapon_ak47");
	sd_m4 = gini_readf("weapon_m4");
	sd_tec9 = gini_readf("weapon_tec9");
	sd_rifle = gini_readf("weapon_rifle");
	sd_sniper = gini_readf("weapon_sniper");
	sd_rocketlauncher = gini_readf("weapon_rocketlauncher");
	sd_heatseeker = gini_readf("weapon_heatseeker");
	sd_flamethrower = gini_readf("weapon_flamethrower");
	sd_minigun = gini_readf("weapon_minigun");
	sd_satchel = gini_readf("weapon_satchel");
	sd_bomb = gini_readf("weapon_bomb");
	sd_spraycan = gini_readf("weapon_spraycan");
	sd_fireextinguisher = gini_readf("weapon_fireextinguisher");
	gini_close();
	return true;
}
		

