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


//加载
#pragma tabsize 0

//===================加载DM=====================
enum E_mode_dm_data{
	E_mode_dm_Command_Name[24],
	E_mode_dm_Command_Type1[24],
	E_mode_dm_Command_Type2[24],
	E_mode_dm_Command_Type3[24],
	E_mode_dm_Description[MAX_STRING],
	
	Float:E_mode_dm_Area_minx,Float:E_mode_dm_Area_miny,
	Float:E_mode_dm_Area_maxx,Float:E_mode_dm_Area_maxy,
	
	
	
	E_mode_dm_Interior,

	Float:E_mode_dm_Spawn_x1,Float:E_mode_dm_Spawn_y1,Float:E_mode_dm_Spawn_z1,
	Float:E_mode_dm_Spawn_x2,Float:E_mode_dm_Spawn_y2,Float:E_mode_dm_Spawn_z2,
	Float:E_mode_dm_Spawn_x3,Float:E_mode_dm_Spawn_y3,Float:E_mode_dm_Spawn_z3,
	Float:E_mode_dm_Spawn_x4,Float:E_mode_dm_Spawn_y4,Float:E_mode_dm_Spawn_z4,
	Float:E_mode_dm_Spawn_x5,Float:E_mode_dm_Spawn_y5,Float:E_mode_dm_Spawn_z5,
	Float:E_mode_dm_Spawn_x6,Float:E_mode_dm_Spawn_y6,Float:E_mode_dm_Spawn_z6,
	Float:E_mode_dm_Spawn_x7,Float:E_mode_dm_Spawn_y7,Float:E_mode_dm_Spawn_z7,
	Float:E_mode_dm_Spawn_x8,Float:E_mode_dm_Spawn_y8,Float:E_mode_dm_Spawn_z8,
	Float:E_mode_dm_Spawn_x9,Float:E_mode_dm_Spawn_y9,Float:E_mode_dm_Spawn_z9,
	Float:E_mode_dm_Spawn_x10,Float:E_mode_dm_Spawn_y10,Float:E_mode_dm_Spawn_z10,
	
	E_mode_dm_Weapon_ID1,E_mode_dm_Weapon_Ammo1,
	E_mode_dm_Weapon_ID2,E_mode_dm_Weapon_Ammo2,
	E_mode_dm_Weapon_ID3,E_mode_dm_Weapon_Ammo3,
	E_mode_dm_Weapon_ID4,E_mode_dm_Weapon_Ammo4,
	E_mode_dm_Weapon_ID5,E_mode_dm_Weapon_Ammo5,
	E_mode_dm_Weapon_ID6,E_mode_dm_Weapon_Ammo6,
	E_mode_dm_Weapon_ID7,E_mode_dm_Weapon_Ammo7,
	E_mode_dm_Weapon_ID8,E_mode_dm_Weapon_Ammo8,
	E_mode_dm_Weapon_ID9,E_mode_dm_Weapon_Ammo9,
	E_mode_dm_Weapon_ID10,E_mode_dm_Weapon_Ammo10,
	E_mode_dm_GangZone
};
new stock
	wl_n_mode_DMInfo[][E_mode_dm_data] = {
		/*
		格式:
		DM名称(只可以数字加英文),DM命令1,DM命令2,DM命令3,
		DM描述(支持中文,最多64个汉字)
		DM范围(最小的x,最小的y.最大的x,最大的y),DM场景(interior)
		DM出生点1(x,y,z)
		DM出生点2(x,y,z)
		DM出生点3(x,y,z)
		DM出生点4(x,y,z)
		DM出生点5(x,y,z)
		DM出生点6(x,y,z)
		DM出生点7(x,y,z)
		DM出生点8(x,y,z)
		DM出生点9(x,y,z)
		DM出生点10(x,y,z)
		DM武器1(武器ID，子弹数量)
		DM武器2(武器ID，子弹数量)
		DM武器3(武器ID，子弹数量)
		DM武器4(武器ID，子弹数量)
		DM武器5(武器ID，子弹数量)
		DM武器6(武器ID，子弹数量)
		DM武器7(武器ID，子弹数量)
		DM武器8(武器ID，子弹数量)
		DM武器9(武器ID，子弹数量)
		DM武器10(武器ID，子弹数量)
		需要增加的话,请遵循这个格式
		注意：最后一项不能有逗号
		*/

		{
			"testDM","dm0","smgdm","smgdm",//想不出命令就重复，一定要3个
			"[DM]这是smgDM",//DM介绍
			1041.1852,-1449.3239,1612.2349,-1133.2903,//范围
			0,//DM场景
			1243.8718,-1253.5200,63.0423,//出生点1
			1243.8718,-1253.5200,53.0423,//出生点2
			1243.8718,-1253.5200,43.0423,//出生点3
			1243.8718,-1253.5200,33.0423,//出生点4
			1243.8718,-1253.5200,23.0423,//出生点5
			1243.8718,-1253.5200,63.0423,//出生点6(不想添加时就复制粘贴，一定要补满10个...)
			1243.8718,-1253.5200,53.0423,//出生点7
			1243.8718,-1253.5200,43.0423,//出生点8
			1243.8718,-1253.5200,33.0423,//出生点9
			1243.8718,-1253.5200,23.0423,//出生点10
			46,1,//武器1
			30,550,//武器2
			34,50,//武器3
			22,300,//武器4
			26,300,//武器5
			0,0,//武器6(不想添加时就添0，一定要补满10个。。。)
			0,0,//武器7
			0,0,//武器8
			0,0,//武器9
			0,0//武器10(注意这里没有逗号)
		},
		{
			"combatDM","dm1","DM1","combat",
			"[DM]用手中的霰弹枪把敌人打成筛子吧!",
			1056.0000,2077.0000,1095.0000,2141.0000,
			0,
			1057.7683,2086.4182,10.8203,
			1089.5157,2120.2161,15.3504,
			1091.6443,2081.8274,15.3504,
			1091.0151,2084.9360,10.8203,
			1088.7902,2114.9031,10.8203,
			1059.9670,2137.2949,10.8203,
			1057.7683,2086.4182,10.8203,
			1089.5157,2120.2161,15.3504,
			1091.6443,2081.8274,15.3504,
			1091.0151,2084.9360,10.8203,
			8,1,
			27,3000,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0
		},
		{
			"m4dm","dm2","DM2","hm",
			"[DM]用手中的M4在航母上大展英姿吧!",
			-1500.0000,450.0000,-1200.0000,550.0000,
			0,
			-1437.7148,496.0567,2.2911,
			-1384.9562,507.4424,3.0391,
			-1372.0028,492.1532,11.1953,
			-1346.4930,493.1400,11.2027,
			-1406.6224,502.5273,11.1953,
			-1296.6367,490.5563,11.1953,
			-1296.6367,490.5563,11.1953,
			-1372.0028,492.1532,11.1953,
			-1346.4930,493.1400,11.2027,
			-1406.6224,502.5273,11.1953,
			8,1,
			39,10,
			40,1,
			31,3000,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
		},
		{
			"sniperdm","DM3","dm3","sniperdm",
			"[DM]狙击手，你在何方？P.S:请不要攻击出生在一起的队友",
			2497.0000,2617.0000,2750.0000,2858.0000,
			0,
			2506.3518,2690.4971,77.8438,
			2593.0759,2638.6758,114.0313,
			2733.1345,2686.7844,59.0234,
			2718.2251,2773.3337,77.3594,
			2632.8125,2832.1208,127.5781,
			2617.0896,2721.0649,36.5386,
			2502.5227,2777.8811,10.8203,
			2541.2358,2832.1047,27.8203,
			2657.0847,2778.3584,19.3222,
			2502.5227,2777.8811,10.8203,
			46,1,
			8,1,
			34,3000,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
		},
		{
			"hoboDM","dm4","hobo","DM4",
			"[DM]在hobo village展开战争!",
			-1400.0,2400.0,-1200.0,2650.0,
			0,
			-1310.0760,2492.9099,89.8672,
			-1321.1389,2510.7017,92.5406,
			-1287.1678,2516.2808,87.1493,
			-1292.8119,2528.2119,90.3828,
			-1303.9823,2525.5469,87.5139,
			-1304.3525,2544.7600,93.3047,
			-1319.7288,2540.3416,87.5320,
			-1333.7350,2526.8264,87.0469,
			-1316.7979,2526.1299,87.5368,
			-1333.5190,2525.4910,87.0469,
			16,15,
			8,1,
			29,3000,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0
		},
		{
			"rocketDM","dm5","rocket","DM5",
			"[DM]用火箭筒摧毁所有的敌人!",
			1117.0,2723.0,1425.0,2864.0,
			0,
			1405.7540,2739.9429,10.8203,
			1397.1189,2821.0918,10.8126,
			1155.6052,2833.8052,10.6044,
			1141.1361,2769.9368,10.1611,
			1272.0931,2788.6680,10.8203,
			1405.7540,2739.9429,10.8203,
			1397.1189,2821.0918,10.8126,
			1155.6052,2833.8052,10.6044,
			1141.1361,2769.9368,10.1611,
			1272.0931,2788.6680,10.8203,
			8,1,
			35,30,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0
		},
		{
			"graveDM","dm6","gravedm","DM6",
			"[DM]欢迎来到墓地，小心别鬼魂缠身哦",
			800.0,-1135.0,960.0,-1055.0,
			0,
			809.1396,-1075.1472,24.4025,
			818.5464,-1103.4952,25.7937,
			812.2061,-1127.6393,23.8281,
			895.6911,-1101.7120,25.8438,
			862.0466,-1094.1764,34.9408,
			900.0239,-1065.6310,28.3515,
			925.5893,-1122.3473,24.0012,
			940.9395,-1070.3365,31.2456,
			809.1396,-1075.1472,24.4025,
			818.5464,-1103.4952,25.7937,
			8,1,
			24,3000,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0
		},
		{
			"offDM","dm7","sawnoff","DM7",
			"[DM]在驾校里边跑边战斗吧!",
			-2100.0,-300.0,-2000.0,-100.0,
			0,
			-2050.049,-279.8535,35.33, 
			-2093.431,-237.1391,35.33, 
			-2093.181,-143.2068,35.33,
			-2078.73,-105.0092,35.33, 
			-2016.274,-118.4865,35.33,
			-2050.049,-279.8535,35.33, 
			-2093.431,-237.1391,35.33, 
			-2093.181,-143.2068,35.33,
			-2078.73,-105.0092,35.33, 
			-2016.274,-118.4865,35.33,
			8,1,
			22,300,
			16,5,
			32,3000,
			26,3000,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0
		},
		{
			"drugDM","dm8","drugdm","DM8",
			"[DM]用一把AK47在毒品工厂大开杀戒吧!",
			2110.0000,-2354.0000,2577.0000,-2179.0000,
			0,
			2234.7278,-2216.4338,13.5469,
			2180.9182,-2248.0801,20.6719,
			2201.0315,-2208.8774,20.7321,
			2225.7698,-2256.9917,20.2153,
			2174.4878,-2251.7939,13.3036,
			2126.1797,-2276.6431,20.6719,
			2178.3879,-2250.4514,20.6719,
			2130.3113,-2281.7437,14.7827,
			2143.4695,-2294.4392,20.6760,
			2231.7056,-2284.5820,14.3751,
			16,10,
			8,1,
			34,30,
			30,3000,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0
		},
		{
			"tennisDM","dm9","tennis","DM9",
			"[DM]用手雷当网球尽情的扔吧!小心被炸下山",
			-380.0000,1950.0000,-290.0000,2020.0000,
			0,
			-363.2212,1971.4437,131.0585,
			-325.3206,2003.1737,131.1794,
			-363.2212,1971.4437,131.0585,
			-325.3206,2003.1737,131.1794,
			-363.2212,1971.4437,131.0585,
			-325.3206,2003.1737,131.1794,
			-363.2212,1971.4437,131.0585,
			-325.3206,2003.1737,131.1794,
			-363.2212,1971.4437,131.0585,
			-325.3206,2003.1737,131.1794,
			8,1,
			16,50,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0
		},
		{
			"KatanaDM","DM10","katana","dm10",
			"[DM]握好手里的日本刀，决斗吧！",
			1400.0,-1950.0,1500.0,-1850.0,
			0,
			1489.6902,-1894.7603,22.2167,
			1489.1102,-1913.8151,24.1825,
			1437.8219,-1915.4242,24.4147,
			1440.1511,-1895.9089,23.1484,
			1461.3010,-1909.1840,23.4947,
			1489.6902,-1894.7603,22.2167,
			1489.1102,-1913.8151,24.1825,
			1437.8219,-1915.4242,24.4147,
			1440.1511,-1895.9089,23.1484,
			1461.3010,-1909.1840,23.4947,
			8,1,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0
		},
		{
			"ChainsawDM","DM11","chainsaw","dm11",
			"[DM]拿好电锯，预备！杀！",
			1250.0,2000.0,1500.0,2250.0,
			0,
			1372.6930,2195.9158,9.7578,
			1393.2479,2167.5540,9.7578,
			1398.0347,2123.9136,14.6250,
			1329.5696,2199.3672,14.6250,
			1302.4229,2104.9380,11.0156,
			1372.6930,2195.9158,9.7578,
			1393.2479,2167.5540,9.7578,
			1398.0347,2123.9136,14.6250,
			1329.5696,2199.3672,14.6250,
			1302.4229,2104.9380,11.0156,
			9,1,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0
		},
		{
			"FireDM","DM12","molotov","dm12",
			"[DM]Fire in the hole!",
			-1965.0,-1000.0,-1940.0,-725.0,
			0,
			-1954.5729,-988.2839,35.8909,
			-1954.5695,-925.2104,35.8909,
			-1954.5139,-858.4214,35.8909,
			-1954.7365,-792.1997,35.8909,
			-1956.0470,-735.4742,35.8909,
			-1954.5729,-988.2839,35.8909,
			-1954.5695,-925.2104,35.8909,
			-1954.5139,-858.4214,35.8909,
			-1954.7365,-792.1997,35.8909,
			-1956.0470,-735.4742,35.8909,
			18,30,
			37,300,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0,
			0,0
		}
	};




















//===============================================
#define zcmd_tele2(%0,%1,%2) \
	zcmd(%0,playerid,params[]) return gcmd_rpText(playerid,(%1)),gtele_teleportPlayer(playerid,%2)	
	
zcmd_tele2(taa,"Welcome to old airport",409.2281,2573.1426,16.3672,90.0,409.2281,2573.1426,50.3672,90.0,0);	
zcmd_tele2(tls,"Welcome to Los Angeles",1384.4961,-2442.0063,13.5547,90.0,1384.4961,-2442.0063,63.5547,90.0,0);	
zcmd_tele2(tmfa,"Welcome to MFA's village",-1077.4032,-1648.0542,75.9494,267.7598,-1077.4032,-1648.0542,125.9494,267.7598,0);	

//=========================加载传送命令=================================
#define zcmd_tele1(%0,%1,%2,%3,%4,%5,%6,%7) \
	zcmd(%0,playerid,params[]) return gcmd_rpText(playerid,(%7)),gcmd_telep(playerid,(%1),(%2),(%3),(%4),(%5),(%6))

zcmd_tele1(jefferson,2228.5488,-1160.0876,25.5190,90.0,0,false,"Welcome to Jefferson Motel");
zcmd_tele1(motel,2228.5488,-1160.0876,25.5190,90.0,0,false,"Welcome to Jefferson Motel");
zcmd_tele1(carlhome,1245.6436,-763.9819,92.1559,180.0,0,false,"Welcome to Little Carl's house");
zcmd_tele1(carlhome2,892.4420,-1657.9996,13.2752,0.0,0,false,"Welcome to Big Carl's house");
zcmd_tele1(bigcarlhome,892.4420,-1657.9996,13.2752,0.0,0,false,"Welcome to Big Carl's house");
zcmd_tele1(seville,2766.1255,-1979.4883,13.1039,180.0,0,false,"Welcome to fangye's house");
zcmd_tele1(village,-436.1484,-433.3588,16.2678,310.1183,0,false,"Welcome to fangye's village");
zcmd_tele1(mfa,-1077.4032,-1648.0542,75.9494,267.7598,0,false,"Welcome to MFA's village");
zcmd_tele1(mfahome,-1077.4032,-1648.0542,75.9494,267.7598,0,false,"Welcome to MFA's village");
zcmd_tele1(mfadejia,-1077.4032,-1648.0542,75.9494,267.7598,0,false,"Welcome to MFA's village");
//zcmd_tele1(008home,-2072.851318,-2307.423828,30.722333,178.513198,0,false,"Welcome to 008's house");
//zcmd_tele1(008dejia,-2072.851318,-2307.423828,30.722333,178.513198,0,false,"Welcome to 008's house");
zcmd_tele1(lxd,-2461.1838,-126.0066,25.5062,270.0,0,false,"Welcome to LXD's house");
zcmd_tele1(lxdhome,-2461.1838,-126.0066,25.5062,270.0,0,false,"Welcome to LXD's house");
zcmd_tele1(lxddejia,-2461.1838,-126.0066,25.5062,270.0,0,false,"Welcome to LXD's house");
zcmd_tele1(dyq,-1754.3215,954.6960,24.4693,90.0,0,false,"Welcome to dyq's building");
zcmd_tele1(dyqhome,-1754.3215,954.6960,24.4693,90.0,0,false,"Welcome to dyq's building");
zcmd_tele1(financial,-1754.3215,954.6960,24.4693,90.0,0,false,"Welcome to dyq's building");
zcmd_tele1(leon,-1639.7650,1203.3917,6.9491,90.0,0,false,"Welcome to Leon's car palace");
zcmd_tele1(kaka,-2622.9937,1402.0154,6.8285,0.0,0,false,"Welcome to kaka's club");
zcmd_tele1(jizzy,-2622.9937,1402.0154,6.8285,0.0,0,false,"Welcome to kaka's club");
zcmd_tele1(boat1,-2308.2756,1546.6807,18.7734,90.0,0,true,"Welcome to fangye's boat1");
zcmd_tele1(boat2,-1477.4603,1488.8739,8.2501,270.0,0,true,"Welcome to fangye's boat2");
zcmd_tele1(zhai,-1041.3837,1550.6311,32.8284,127.5056,0,false,"Welcome to Zhai's house");
zcmd_tele1(zhaihome,-1041.3837,1550.6311,32.8284,127.5056,0,false,"Welcome to Zhai's house");
zcmd_tele1(zhaidejia,-1041.3837,1550.6311,32.8284,127.5056,0,false,"Welcome to Zhai's house");
zcmd_tele1(ailde,-688.9996,966.5593,11.8931,90.0,0,false,"Welcome to Ailde's house");
zcmd_tele1(aildehome,-688.9996,966.5593,11.8931,90.0,0,false,"Welcome to Ailde's house");
zcmd_tele1(aildedejia,-688.9996,966.5593,11.8931,90.0,0,false,"Welcome to Ailde's house");
zcmd_tele1(cc,-688.9996,966.5593,11.8931,90.0,0,false,"Welcome to Ailde's house");
zcmd_tele1(catskimmer,-1424.2201,2168.2451,49.4010,117.6809,0,false,"Welcome to Cat's skimmer");
zcmd_tele1(village2,-795.8416,2262.4250,63.4364,151.9472,0,true,"Welcome to fangye's hidden village");
zcmd_tele1(hidvillage,-795.8416,2262.4250,63.4364,151.9472,0,true,"Welcome to fangye's hidden village");
zcmd_tele1(5g,-380.8053,2238.2166,41.9717,194.5694,0,false,"Welcome to 5g's village");
zcmd_tele1(5gvillage,-380.8053,2238.2166,41.9717,194.5694,0,false,"Welcome to 5g's village");
zcmd_tele1(wlcbase,693.5462,1946.0432,5.2682,0.0,0,false,"Welcome to wlc's club");
zcmd_tele1(wlcclub,693.5462,1946.0432,5.2682,0.0,0,false,"Welcome to wlc's club");
zcmd_tele1(wlchome,693.5462,1946.0432,5.2682,0.0,0,false,"Welcome to wlc's club");
zcmd_tele1(duduktv,2181.7629,1677.8236,10.7935,180.0,0,false,"Welcome to Dudu's KTV");
zcmd_tele1(caligula,2181.7629,1677.8236,10.7935,180.0,0,false,"Welcome to Dudu's KTV");
zcmd_tele1(4dragon,2031.6479,1007.5502,10.5474,180.0,0,false,"Welcome to 4dragon");
zcmd_tele1(4long,2031.6479,1007.5502,10.5474,180.0,0,false,"Welcome to 4dragon");
zcmd_tele1(hand,2418.7131,1123.6705,10.5474,0.0,0,false,"Welcome to hand's company");
zcmd_tele1(handgs,2418.7131,1123.6705,10.5474,0.0,0,false,"Welcome to hand's company");
zcmd_tele1(handcompany,2418.7131,1123.6705,10.5474,0.0,0,false,"Welcome to hand's company");
zcmd_tele1(fly,2418.7131,1123.6705,10.5474,0.0,0,false,"Welcome to hand's company");
zcmd_tele1(diner,2631.0803,1849.1490,10.5474,270.0,0,false,"Welcome to fangye's diner");
zcmd_tele1(yanwu,2508.7913,2125.3960,10.5474,270.0,0,false,"have fun with a lap dance");
zcmd_tele1(lapdance,2508.7913,2125.3960,10.5474,270.0,0,false,"have fun with a lap dance");
zcmd_tele1(iMben,1352.0454,-621.5497,108.8599,198.5411,0,false,"Welcome to iMben's house");
zcmd_tele1(pc133,1733.4950,-1063.5541,23.6790,180.0,0,false,"Welcome to pc's Mulholland park");
zcmd_tele1(mulholland,1733.4950,-1063.5541,23.6790,180.0,0,false,"Welcome to pc's Mulholland park");
zcmd_tele1(pc100,1793.4999,-2127.6533,13.2740,0.0,0,false,"Welcome to pc's EL Corona garage");
zcmd_tele1(elcorona,1793.4999,-2127.6533,13.2740,0.0,0,false,"Welcome to pc's EL Corona garage");
zcmd_tele1(waunny,2607.7107,2305.5024,10.7835,133.1047,0,false,"Welcome to Waunny's hotel");
zcmd_tele1(vrock,2607.7107,2305.5024,10.7835,133.1047,0,false,"Welcome to V Rock owned by Waunny");
zcmd_tele1(rainyday,1286.7000,2522.6560,10.6113,105.5283,0,false,"Welcome to panda and 009's house");
zcmd_tele1(carlgym,2222.0261,-1726.5759,13.3972,118.1132,0,false,"Welcome to Little Carl's gym");
zcmd_tele1(cxd,-2026.7245,-50.3388,35.3830,0.0,0,false,"Welcome to CXD's house");
zcmd_tele1(cxdhome,-2026.7245,-50.3388,35.3830,0.0,0,false,"Welcome to CXD's house");
zcmd_tele1(cxddejia,-2026.7245,-50.3388,35.3830,0.0,0,false,"Welcome to CXD's house");
zcmd_tele1(kevin,-2103.7600,901.7340,76.7109,352.3944,0,false,"Welcome to kevin's house");
zcmd_tele1(kevinhome,-2103.7600,901.7340,76.7109,352.3944,0,false,"Welcome to kevin's house");
zcmd_tele1(kevindejia,-2103.7600,901.7340,76.7109,352.3944,0,false,"Welcome to kevin's house");
zcmd_tele1(dt123,2555.9551,1563.1183,10.6407,256.7091,0,false,"Welcome to dt123's house");
zcmd_tele1(dt123home,2555.9551,1563.1183,10.6407,256.7091,0,false,"Welcome to dt123's house");
zcmd_tele1(dt123dejia,2555.9551,1563.1183,10.6407,256.7091,0,false,"Welcome to dt123's house");
zcmd_tele1(kaka2,2036.8386,1623.0779,10.8125,276.3776,0,false,"Welcome to kaka's house");
zcmd_tele1(kakahome,2036.8386,1623.0779,10.8125,276.3776,0,false,"Welcome to kaka's house");
zcmd_tele1(kakadejia,2036.8386,1623.0779,10.8125,276.3776,0,false,"Welcome to kaka's house");
zcmd_tele1(hdc,2036.8386,1623.0779,10.8125,276.3776,0,false,"Welcome to HDC");
//zcmd_tele1(LHS,2023.9238,1342.5016,10.5238,12.1041,0,false,"Welcome to LHS's house");
//zcmd_tele1(LHShome,2023.9238,1342.5016,10.5238,12.1041,0,false,"Welcome to LHS's house");
//zcmd_tele1(LHSdejia,2023.9238,1342.5016,10.5238,12.1041,0,false,"Welcome to LHS's house");
//zcmd_tele1(paloschi,315.6220,-1773.6825,4.7220,354.4633,0,false,"Welcome to paloschi's house");
zcmd_tele1(santa,315.6220,-1773.6825,4.7220,354.4633,0,false,"Welcome to Santa Maria Beach");
zcmd_tele1(sp_x,2351.9866,-1165.5199,27.4542,179.6879,0,false,"Welcome to sp_x's house");
zcmd_tele1(sp_xhome,2351.9866,-1165.5199,27.4542,179.6879,0,false,"Welcome to sp_x's house");
zcmd_tele1(sp_xdejia,2351.9866,-1165.5199,27.4542,179.6879,0,false,"Welcome to sp_x's house");
//zcmd_tele1(tjhome,-2106.6863,902.0564,76.6017,164.6403,0,false,"Welcome to mo_tj's house");
//zcmd_tele1(tjdejia,-2106.6863,902.0564,76.6017,164.6403,0,false,"Welcome to mo_tj's house");
//zcmd_tele1(mkhome,-1438.1394,-1529.0452,101.7508,174.3923,0,false,"Welcome to mk's house");
//zcmd_tele1(mkdejia,-1438.1394,-1529.0452,101.7508,174.3923,0,false,"Welcome to mk's house");
//zcmd_tele1(w006,2236.7903,150.7842,26.4844,349.7480,0,false,"Welcome to w006's house");
//zcmd_tele1(w006home,2236.7903,150.7842,26.4844,349.7480,0,false,"Welcome to w006's house");
//zcmd_tele1(w006dejia,2236.7903,150.7842,26.4844,349.7480,0,false,"Welcome to w006's house");
zcmd_tele1(david,1404.4568,1897.3773,11.3384,159.3198,0,false,"Welcome to david's house");
zcmd_tele1(davidhome,1404.4568,1897.3773,11.3384,159.3198,0,false,"Welcome to david's house");
zcmd_tele1(daviddejia,1404.4568,1897.3773,11.3384,159.3198,0,false,"Welcome to david's house");
zcmd_tele1(mdx,-2816.2205,-1524.7087,140.8438,98.9240,0,true,"Welcome to mdx's house");
zcmd_tele1(mdxhome,-2816.2205,-1524.7087,140.8438,98.9240,0,true,"Welcome to mdx's house");
zcmd_tele1(mdxdejia,-2816.2205,-1524.7087,140.8438,98.9240,0,true,"Welcome to mdx's house");
zcmd_tele1(heroman,-2443.2078,751.2242,35.1786,177.8841,0,false,"Welcome to heroman's house");
zcmd_tele1(jasmine,941.0325,1732.4612,8.8516,277.6877,0,false,"Welcome to Jasmine's house");
zcmd_tele1(008house,-2106.2681,900.6922,76.7109,191.4563,0,false,"Welcome to MRG 008's house");
zcmd_tele1(cl,1490.0344,2843.3645,10.8203,122.2138,0,false,"Welcome to ChinaLong's vice leader's base");
//zcmd_tele1(jide,2491.3135,-1681.7820,13.0640,272.2010,0,false,"Welcome to jide's house");
//zcmd_tele1(jidehome,2491.3135,-1681.7820,13.0640,272.2010,0,false,"Welcome to jide's house");
zcmd_tele1(cjj,2491.3135,-1681.7820,13.0640,272.2010,0,false,"Welcome to CJJ");
zcmd_tele1(ddt,2440.3633,697.8047,11.1038,272.3094,0,false,"Welcome to ddt's house");
zcmd_tele1(ddthome,2440.3633,697.8047,11.1038,272.3094,0,false,"Welcome to ddt's house");
zcmd_tele1(woozie,-2169.8464,642.3659,1057.5861,270.0000,1,true,"Welcome to SOS dan");
zcmd_tele1(sosdan,-2169.8464,642.3659,1057.5861,270.0000,1,true,"Welcome to SOS dan");//Player's house
zcmd_tele1(aa,409.2281,2573.1426,16.3672,90.0,0,false,"Welcome to old airport");
zcmd_tele1(ls,1384.4961,-2442.0063,13.5547,90.0,0,false,"Welcome to Los Angeles");
zcmd_tele1(sf,-1224.4486,48.1323,13.9070,135.0,0,false,"Welcome to San Fransisco");
zcmd_tele1(lv,1339.0537,1268.9032,10.5474,0.0,0,false,"Welcome to Las Venturas");
zcmd_tele1(lc,-748.0042,488.2530,1371.5521,256.7060,1,true,"Welcome to Liberty City");
zcmd_tele1(zyc,-748.0042,488.2530,1371.5521,256.7060,1,true,"Welcome to Liberty City");
zcmd_tele1(cafe,-781.8113,489.3232,1376.1954,256.7060,1,true,"Saint Mark's");
zcmd_tele1(chilliad,-2306.9426,-1658.9847,483.6752,29.4973,0,false,"Welcome to Chilliad");
zcmd_tele1(qiannian,-2306.9426,-1658.9847,483.6752,29.4973,0,false,"Welcome to Chilliad");
zcmd_tele1(chilliad2,-2399.7344,-2208.1670,32.9955,296.2202,0,false,"The foot of Chilliad");
zcmd_tele1(qiannian2,-2399.7344,-2208.1670,32.9955,296.2202,0,false,"The foot of Chilliad");
zcmd_tele1(qiuming,-51.3313,-2439.7346,324.7934,180.0,0,false,"Welcome to qiuming");
zcmd_tele1(qiuming2,382.1812,-2042.9825,7.5630,182.6865,0,false,"The foot of qiuming");
zcmd_tele1(drift1,-2409.7190,-600.5191,132.3425,270.0,0,false,"Drift 1");
zcmd_tele1(drift2,-344.5910,1528.6195,75.0840,265.2350,0,false,"Drift 2");
zcmd_tele1(ldz,-344.5910,1528.6195,75.0840,265.2350,0,false,"Welcome to LDZ");
zcmd_tele1(drift3,2267.1614,1398.3538,42.5474,267.7794,0,false,"Drift 3");
zcmd_tele1(drift4,-537.4770,-177.1084,78.1115,90.2531,0,false,"Drift 4");
zcmd_tele1(drift5,2073.2759,2438.5293,49.2527,179.3376,0,false,"Drift 5");
zcmd_tele1(drift6,2221.1450,1960.2709,31.5076,268.7906,0,false,"Drift 6");
zcmd_tele1(drift7,1131.4598,-2037.9740,68.7579,272.6977,0,false,"Drift 7");
zcmd_tele1(WhiteHouse,1131.4598,-2037.9740,68.7579,272.6977,0,false,"Drift 7");
zcmd_tele1(BaiGong,1131.4598,-2037.9740,68.7579,272.6977,0,false,"Drift 7");
zcmd_tele1(bisai,-2006.2069,157.2752,27.2661,0.0,0,false,"Let's race");
zcmd_tele1(wangcar,-2006.2069,157.2752,27.2661,0.0,0,false,"Let's race");
zcmd_tele1(sfck,-2006.2069,157.2752,27.2661,0.0,0,false,"Let's race");
zcmd_tele1(doherty,-2006.2069,157.2752,27.2661,0.0,0,false,"Let's race");//cities
zcmd_tele1(navy,-2265.9375,2291.0320,4.4824,0.0,0,false,"Welcome to navy dock");
zcmd_tele1(bayside,-2265.9375,2291.0320,4.4824,0.0,0,false,"Welcome to navy dock");
zcmd_tele1(swimming,-2021.7587,-997.3379,31.8990,1.5683,0,false,"Go and Swim");
zcmd_tele1(bikepark,1862.3948,-1381.0874,13.1864,270.0,0,false,"Get a bike and go");
zcmd_tele1(ball,-2080.6860,296.6321,69.7566,249.7365,0,true,"oh ball's");
zcmd_tele1(beach1,-2941.6489,443.9067,3.0963,249.7365,0,false,"Welcome to the beach");
zcmd_tele1(bowl,-1611.0452,163.4491,3.5547,359.4314,0,false,"big bowl");
zcmd_tele1(bridge1,-1519.8152,676.1623,139.2734,17.2311,0,true,"bridge 1");
zcmd_tele1(bridge2,-1128.3569,849.8029,84.0078,17.2311,0,true,"bridge 2");
zcmd_tele1(bridge3,-2681.6519,1594.9670,217.2739,139.8741,0,true,"go away");
zcmd_tele1(eggs,-2681.6519,1594.9670,217.2739,139.8741,0,true,"go away");
zcmd_tele1(cg,-69.3315,-1132.8688,1.0781,328.8393,0,false,"c and g hut");
zcmd_tele1(dam,-762.0638,2063.2610,60.1875,157.7577,0,false,"dam busters");
zcmd_tele1(shuiba,-762.0638,2063.2610,60.1875,157.7577,0,false,"dam busters");
zcmd_tele1(derby,1383.4088,2184.9304,11.0234,157.7577,0,true,"demolition derby");
zcmd_tele1(golf,-2652.9641,-288.8345,7.5435,49.0670,0,false,"go golfing");
zcmd_tele1(leap,1960.2781,1595.4114,75.7188,27.8704,0,true,"leap");
zcmd_tele1(5towers,1649.2350,-1677.8900,21.4301,197.9418,0,true,"Welcome to 5 towers");
zcmd_tele1(tie,-533.0924,2592.3591,53.4154,273.7692,0,false,"Welcome to Tierra Ronada");
zcmd_tele1(tunnel,1409.2642,-1328.0328,8.5632,273.7692,0,false,"Welcome to the tunnel");
zcmd_tele1(andy,-377.0659,-1441.3119,25.7266,323.9030,0,false,"Welcome to Andrew");
zcmd_tele1(srs,-1429.2487,-952.5726,200.9666,37.4669,0,false,"Sniper Rifle in Hut");
zcmd_tele1(seif,2323.7029,1283.2653,97.6163,59.4004,0,true,"Welcome to seif");
zcmd_tele1(camelstoe,2323.7029,1283.2653,97.6163,59.4004,0,true,"Welcome to seif");
zcmd_tele1(69park,-1705.7960,1338.4753,7.1786,129.8291,0,false,"Welcome to 69 park");//old places
zcmd_tele1(lspd,1536.1317,-1675.9449,13.1099,180.0,0,false,"Welcome to LSPD");
zcmd_tele1(lsjj,1536.1317,-1675.9449,13.1099,180.0,0,false,"Welcome to LSPD");
zcmd_tele1(dillimore,637.1514,-571.7906,15.9867,354.6856,0,false,"Welcome to Dillimore");
zcmd_tele1(sfpd,-1605.0063,729.8975,11.4600,274.2862,0,false,"Welcome to SFPD");
zcmd_tele1(sfjj,-1605.0063,729.8975,11.4600,274.2862,0,false,"Welcome to SFPD");
zcmd_tele1(lvpd,2290.0459,2417.2661,10.4761,271.4613,0,false,"Welcome to LVPD");
zcmd_tele1(lvjj,2290.0459,2417.2661,10.4761,271.4613,0,false,"Welcome to LVPD");
zcmd_tele1(jsjd4,2743.7339,-2405.9058,13.4507,22.2303,0,false,"Welcome to spare base");
zcmd_tele1(ufobar,-71.5914,1365.4630,9.6196,180.0,0,false,"Welcome to the UFO bar");//police stations and army bases
zcmd_tele1(smoke1,2549.5527,-1284.4288,1060.9844,177.7050,2,true,"Welcome to Smoke's drag factory");
zcmd_tele1(smoke2,2543.1655,-1317.6013,1031.4219,163.0697,2,true,"Welcome to Smoke's drag factory");
zcmd_tele1(sexshop,2109.7295,2074.8213,10.8203,266.4132,0,false,"Welcome to the sex shop");
zcmd_tele1(quarry1,636.7983,871.0867,-42.9609,103.9410,0,false,"Welcome to the rock quarry1");
zcmd_tele1(gongdi1,636.7983,871.0867,-42.9609,103.9410,0,false,"Welcome to the rock quarry1");
zcmd_tele1(quarry2,-1889.6552,-1644.8467,21.7500,103.9410,0,false,"Welcome to the rock quarry2");
zcmd_tele1(gongdi2,-1889.6552,-1644.8467,21.7500,103.9410,0,false,"Welcome to the rock quarry2");
zcmd_tele1(quarry3,2717.9788,855.2516,10.8984,92.9579,0,false,"Welcome to the rock quarry3");
zcmd_tele1(gongdi3,2717.9788,855.2516,10.8984,92.9579,0,false,"Welcome to the rock quarry3");//special places
zcmd_tele1(trans1,2386.5757,1011.6674,10.3890,0.0,0,false,"Trans Fender1");
zcmd_tele1(gaiche1,2386.5757,1011.6674,10.3890,0.0,0,false,"Trans Fender1");
zcmd_tele1(trans2,-1936.3749,226.5488,33.7273,0.0,0,false,"Trans Fender2");
zcmd_tele1(gaiche2,-1936.3749,226.5488,33.7273,0.0,0,false,"Trans Fender2");
zcmd_tele1(trans3,1041.8151,-1041.7441,31.3417,0.0,0,false,"Trans Fender3");
zcmd_tele1(gaiche3,1041.8151,-1041.7441,31.3417,0.0,0,false,"Trans Fender3");
zcmd_tele1(arch,-2707.1746,217.3418,3.7500,90.0,0,false,"wheel arch angels SULTAN");
zcmd_tele1(gaiche4,-2707.1746,217.3418,3.7500,90.0,0,false,"wheel arch angels SULTAN");
zcmd_tele1(loco,2644.9507,-2015.6716,13.1256,180.0,0,false,"loco low do SAVANNA");
zcmd_tele1(gaiche5,2644.9507,-2015.6716,13.1256,180.0,0,false,"loco low do SAVANNA");//garages
zcmd_tele1(mafia,979.5461,2156.4888,10.2957,360.0000,0,false,"Welcome to mafia factory");
zcmd_tele1(69area,215.1086,1914.3699,17.6406,0,0,false,"Welcome to 69 area");
zcmd_tele1(armybase,215.1086,1914.3699,17.6406,0,0,false,"Welcome to 69 area");
zcmd_tele1(basin,-1594.1318,103.7966,3.2765,180.0,0,false,"Welcome to Easter Basin");
zcmd_tele1(ocean,-2914.0911,465.8986,4.6411,180.0,0,false,"Welcome to Ocean Flats");
zcmd_tele1(knight1,-2462.0234,133.2496,35.1719,306.2618,0,false,"Welcome to Future War EX1");
zcmd_tele1(knight2,2482.3096,1526.3453,11.5118,310.9852,0,false,"Welcome to Future War EX2");
zcmd_tele1(8truck,-1402.6631,-254.6999,1043.5010,354.1802,0,true,"Welcome to 8 truck raceway");//special places
zcmd_tele1(cs1,-3184.0950,1378.6230,39.5265,90.0,0,false,"Aircraft Carrier - by th21");//
zcmd_tele1(cs2,-2810.4521,-702.0084,67.3884,90.0,0,false,"Nazi Zombie FS - By V1ceC1ty");//
zcmd_tele1(cs3,914.8998,-319.2097,51.2545,90.0,0,false,"ELIMINATION - By V1ceC1ty");//
zcmd_tele1(cs4,1457.1715,-1516.4901,66.7497,90.0,0,false,"Deathmatch arena - By V1ceC1ty");//
zcmd_tele1(cs5,1702.5566,-3491.3135,20.8811,90.0,0,false,"Militia Forest");//
zcmd_tele1(cs6,5852.9780,-4559.7324,-45.8128,338.1001,0,false,"Sea Desert");
zcmd_tele1(hdfx,5852.9780,-4559.7324,-45.8128,338.1001,0,false,"Sea Desert");
zcmd_tele1(cs7,1729.2975,-1421.3094,218.6206,146.7231,0,false,"Super Carrier!");
zcmd_tele1(wlzj,1729.2975,-1421.3094,218.6206,146.7231,0,false,"Super Carrier!");//cs
//=======================================================================

//===============================加载出生点=================================================
enum e_wl_obj_spawn_Data{
	Float:e_wl_obj_spawn_x,
	Float:e_wl_obj_spawn_y,
	Float:e_wl_obj_spawn_z,
	Float:e_wl_obj_spawn_a,
	e_wl_obj_spawn_Interior,
	e_wl_obj_spawn_String[MAX_STRING]
};

new const stock
	wl_s_obj_spawnInfo[][e_wl_obj_spawn_Data] = {
	//格式:出生点坐标X，出生点坐标Y，出生点坐标Z，出生面向角度，场景，提示内容
	//需要增加的话,请遵循这个格式
	//注意：最后一项不能有逗号
{409.2281,2573.1426,16.3672,90.0,0,">> 出生在 /aa 大型特技场"},
{1384.4961,-2442.0063,13.5547,90.0,0,">> 出生在 /ls"},
{-1224.4486,48.1323,13.9070,135.0,0,">> 出生在 /sf"},
{1339.0537,1268.9032,10.5474,0.0,0,">> 出生在 /lv"},
{2228.5488,-1160.0876,25.5190,90.0,0,">> 出生在 /jefferson 旅馆"},
{-344.5910,1528.6195,75.0840,265.2350,0,">> 出生在 /ldz 赛道"},
{-1639.7650,1203.3917,6.9491,90.0,0,">> 出生在 /leon 车城"},
{2031.6479,1007.5502,10.5474,180.0,0,">> 出生在 /4dragon 赌场"},
{2717.9788,855.2516,10.8984,180.0,0,">> 出生在 /quarry3 工地"},
{-1594.1318,103.7966,3.2765,180.0,0,">> 出生在 /basin"},
{346.1879,-1798.5165,4.5219,180.0,0,">> 出生在 /santa 海滩"},
{-699.9391,952.2872,12.0641,180.0,0,">> 出生在 /ailde"},
{-2914.0911,465.8986,4.6411,180.0,0,">> 出生在 /ocean"},
{-2617.5083,1362.2252,6.7949,180.0,0,">> 出生在 /kaka 俱乐部"},
{-425.2987,2185.0627,41.4807,180.0,0,">> 出生在 /5g 村庄"},
{319.0257,1972.7328,17.3677,180.0,0,">> 出生在 /69area 军事基地"},
{2311.7102,2448.8367,10.5474,180.0,0,">> 出生在 /lvpd 警察局"},
{2766.1255,-1979.4883,13.1039,180.0,0,">> 出生在 /seville GM基地"},
{-2265.9375,2291.0320,4.4824,180.0,0,">> 出生在 /navy 特技场"},
{2482.3096,1526.3453,11.5118,310.9852,0, ">> 出生在 /knight2 DYOM纪念区"}
//{-3184.0950,1378.6230,39.5265,180.0,0,">> 出生在 /cs1 航空母舰-by th21"},
//{5852.9780,-4559.7324,-45.8128,338.1001,0,">> 出生在 /hdfx 海底废墟"},
//{1729.2975,-1421.3094,218.6206,146.7231,0,">> 出生在 /wlzj 未来战舰"}//结尾不能有逗号
	};

//=============================================================================


























































































//=====================================================

























