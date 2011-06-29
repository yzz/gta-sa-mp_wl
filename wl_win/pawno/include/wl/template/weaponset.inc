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


// INCLUDES //



// COLORS //
#define COLOR_BASIC 0x0066FFAA
/*
#define COLOR_RED 0xFF0000FF
#define COLOR_GREY 0xAFAFAFAA
#define COLOR_GREEN 0x33AA33AA
#define COLOR_YELLOW 0xFFFF00AA
#define COLOR_WHITE 0xFFFFFFAA
*/


/////////// Weapon prices ////////////

// INSTRUCTIONS :
// Change the 0 to the amount you want the weapon to be sold
// V = Weapon Price
// A = Weapon amount on buy

// Melee Weapons
  #define VBrassKnuckles 0
  #define ABrassKnuckles 1
  #define VGolfclub 0
  #define AGolfclub 1
  #define VNiteStick 0
  #define ANiteStick 1
  #define VKnife 0
  #define AKnife 1
  #define VBaseballBat 0
  #define ABaseballBat 1
  #define VShovel 0
  #define AShovel 1
  #define VPoolCue 0
  #define APoolCue 1
  #define VKatana 0
  #define AKatana 1
  #define VChainsaw 0
  #define AChainsaw 1
  #define VPurpleDildo 0
  #define APurpleDildo 1
  #define VSmallWhiteVibrator 0
  #define ASmallWhiteVibrator 1
  #define VLargeWhiteVibrator 0
  #define ALargeWhiteVibrator 1
  #define VSilverVibrator 0
  #define ASilverVibrator 1
  #define VFlower 0
  #define AFlower 1
  #define VCane 0
  #define ACane 1

// Thrown Weapons
  #define VGrenade 0
  #define AGrenade 1000
  #define VTearGas 0
  #define ATearGas 1000
  #define VMolotovCocktail 0
  #define AMolotovCocktail 1000
  
// Pistols
  #define V9mm 0
  #define A9mm 1000
  #define VSilenced9mm 0
  #define ASilenced9mm 1000
  #define VDesertEagle 0
  #define ADesertEagle 1000

// Shotguns
  #define VShotgun 0
  #define AShotgun 1000
  #define VSawn-offShotgun 0
  #define ASawn-offShotgun 1000
  #define VCombatShotgun 0
  #define ACombatShotgun 1000

// SMG's
  #define VSMG 0
  #define ASMG 1000
  #define VUZI 0
  #define AUZI 1000
  #define VTec-9 0
  #define ATec-9 1000

// Rifles
  #define VAK-47 0
  #define AAK-47 1000
  #define VM4 0
  #define AM4 1000
  #define VCountryRifle 0
  #define ACountryRifle 1000
  #define VSniperRifle 0
  #define ASniperRifle 1000

// Special
  #define VRocketLauncher 0
  #define ARocketLauncher 1000
  #define VHeatSeekingRocketLauncher 0
  #define AHeatSeekingRocketLauncher 1000
  #define VFlamethrower 0
  #define AFlamethrower 1000
  #define VMini-gun 0
  #define AMini-gun 1000
  #define VSatchelChargeandDetonator 0
  #define ASatchelChargeandDetonator 1000

// Extras
  #define VSprayCan 0
  #define ASprayCan 1000
  #define VFireExtinguisher 0
  #define AFireExtinguisher 1000
  #define VCamera 0
  #define ACamera 1000
  #define VNightvisionGoogles 0
  #define ANightvisionGoogles 1
  #define VThermalGoogles 0
  #define AThermalGoogles 1
  #define VParachute 0
  #define AParachute 1

// Health and Armour
  #define VHealth 0
  #define VArmour 0
  #define VHealthandArmour 0
  
zcmd(wuqi,playerid,params[]){
	SendClientMessage(playerid, COLOR_GREEN, "[系统]你可以输入/wuqi购买武器");
	ShowPlayerDialog(playerid, 20320, DIALOG_STYLE_LIST, "武器商店", "手持类\n投掷类\n手枪\n霰弹枪\n冲锋枪\n步枪\n特殊武器\n其它\n血/甲", "选择", "取消");
	return true;
}

weaponset_playerSpawn(playerid){
	if(!GetPlayerVirtualWorld(playerid)){
		ShowPlayerDialog(playerid, 20320, DIALOG_STYLE_LIST, "Weapon Shop", "Melee weapons\nThrown\nPistols\nShotguns\nSMG's\nRifles\nSpecials\nExtras\nHealth and Armour", "Select", "Exit");
	}
}

weaponset_DialogResponse(playerid, dialogid, response, listitem)
{
if(dialogid == 20320 && response)
{
switch(listitem)
{
case 0:
{
ShowPlayerDialog(playerid, 20321, DIALOG_STYLE_LIST, "Weapon Shop [Melee Weapons]", "Brass Knuckles\nGolf Club\nNite Stick\nKnife\nBaseball Bat\nShovel\nPool Cue\nKatana\nChainsaw\nPurple Dildo\nSmall White Vibrator\nLarge White Vibrator\nSilver Vibrator\nFlowers\nCane", "Buy", "Cancel");
}
case 1:
{
ShowPlayerDialog(playerid, 20322, DIALOG_STYLE_LIST, "Weapon Shop [Thrown]", "Grenade\nTear Gas\nMolotov Cocktails", "Buy", "Cancel");
}
case 2:
{
ShowPlayerDialog(playerid, 20323, DIALOG_STYLE_LIST, "Weapon Shop [Pistols]", "9mm\nSilenced 9mm\nDesert Eagle", "Buy", "Cancel");
}
case 3:
{
ShowPlayerDialog(playerid, 20324, DIALOG_STYLE_LIST, "Weapon Shop [Shotguns]", "Shotgun\nSawn-off Shotgun\nCombat Shotgun", "Buy", "Cancel");
}
case 4:
{
ShowPlayerDialog(playerid, 20325, DIALOG_STYLE_LIST, "Weapon Shop [SMG]", "SMG\nUZI\nTec-9", "Buy", "Cancel");
}
case 5:
{
ShowPlayerDialog(playerid, 20326, DIALOG_STYLE_LIST, "Weapon Shop [Rifles]", "AK-47\nM4\nCountry Rifle\nSniper Rifle", "Buy", "Cancel");
}
case 6:
{
ShowPlayerDialog(playerid, 20327, DIALOG_STYLE_LIST, "Weapon Shop [Specials]", "Rocket Launcher\nHeat Seeking Rocket Launcher\nFlamethrower\nMini-gun\nSatchel Charge Kit", "Buy", "Cancel");
}
case 7:
{
ShowPlayerDialog(playerid, 20328, DIALOG_STYLE_LIST, "Weapon Shop [Extras]", "Spray Can\nFire Extinguisher\nCamera\nNightvision Googles\nThermal Googles\nParachute", "Buy", "Cancel");
}
case 8:
{
ShowPlayerDialog(playerid, 20329, DIALOG_STYLE_LIST, "Weapon Shop [Health and Armour]", "Health\nArmour\nHealth and Armour", "Buy", "Cancel");
}
}
}

if(dialogid == 20321 && response)
{
switch(listitem)
{
case 0:
{
//if( GetPlayerMoney(playerid)  <  VBrassKnuckles) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Brass Knuckle!");
GivePlayerMoney(playerid, -VBrassKnuckles);
GivePlayerWeapon(playerid, 1, ABrassKnuckles);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Brass Knuckle!");
}
case 1:
{
//if( GetPlayerMoney(playerid)  <  VGolfclub) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Golf Club!");
GivePlayerMoney(playerid, -VGolfclub);
GivePlayerWeapon(playerid, 2, AGolfclub);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Golf Club!");
}
case 2:
{
//if( GetPlayerMoney(playerid)  <  VNiteStick) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Nite Stick!");
GivePlayerMoney(playerid, -VNiteStick);
GivePlayerWeapon(playerid, 3, ANiteStick);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Nite Stick!");
}
case 3:
{
//if( GetPlayerMoney(playerid)  <  VKnife) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Knife!");
GivePlayerMoney(playerid, -VKnife);
GivePlayerWeapon(playerid, 4, AKnife);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Knife!");
}
case 4:
{
//if( GetPlayerMoney(playerid)  <  VBaseballBat) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Baseball bat!");
GivePlayerMoney(playerid, -VBaseballBat);
GivePlayerWeapon(playerid, 5, ABaseballBat);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Baseball Bat!");
}
case 5:
{
//if( GetPlayerMoney(playerid)  <  VShovel) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Shovel!");
GivePlayerMoney(playerid, -VShovel);
GivePlayerWeapon(playerid, 6, AShovel);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Shovel!");
}
case 6:
{
//if( GetPlayerMoney(playerid)  <  VPoolCue) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Pool Cue!");
GivePlayerMoney(playerid, -VPoolCue);
GivePlayerWeapon(playerid, 7, APoolCue);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Pool Cue!");
}
case 7:
{
//if( GetPlayerMoney(playerid)  <  VKatana) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Katana!");
GivePlayerMoney(playerid, -VKatana);
GivePlayerWeapon(playerid, 8, AKatana);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Katana!");
}
case 8:
{
//if( GetPlayerMoney(playerid)  <  VChainsaw) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Chainsaw!");
GivePlayerMoney(playerid, -VChainsaw);
GivePlayerWeapon(playerid, 9, AChainsaw);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Chainsaw!");
}
case 9:
{
//if( GetPlayerMoney(playerid)  <  VPurpleDildo) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Purple Dildo!");
GivePlayerMoney(playerid, -VPurpleDildo);
GivePlayerWeapon(playerid, 10, APurpleDildo);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Purple Dildo!");
}
case 10:
{
//if( GetPlayerMoney(playerid)  <  VSmallWhiteVibrator) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Small White Vibrator!");
GivePlayerMoney(playerid, -VSmallWhiteVibrator);
GivePlayerWeapon(playerid, 11, ASmallWhiteVibrator);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Small White Vibrator!");
}
case 11:
{
//if( GetPlayerMoney(playerid)  <  VLargeWhiteVibrator) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Large White Vibrator!");
GivePlayerMoney(playerid, -VLargeWhiteVibrator);
GivePlayerWeapon(playerid, 12, ALargeWhiteVibrator);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Large White Vibrator!");
}
case 12:
{
//if( GetPlayerMoney(playerid)  <  VSilverVibrator) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Silver Vibrator!");
GivePlayerMoney(playerid, -VSilverVibrator);
GivePlayerWeapon(playerid, 13, ASilverVibrator);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Silver Vibrator!");
}
case 13:
{
//if( GetPlayerMoney(playerid)  <  VFlower) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy some Flowers!");
GivePlayerMoney(playerid, -VFlower);
GivePlayerWeapon(playerid, 14, AFlower);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought some Flowers!");
}
case 14:
{
//if( GetPlayerMoney(playerid)  <  VCane) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Cane!");
GivePlayerMoney(playerid, -VCane);
GivePlayerWeapon(playerid, 15, ACane);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Cane!");
}
}
}

if(dialogid == 20322 && response)
{
switch(listitem)
{
case 0:
{
//if( GetPlayerMoney(playerid)  <  VGrenade) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Grenade!");
GivePlayerMoney(playerid, -VGrenade);
GivePlayerWeapon(playerid, 16, AGrenade);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Grenade!");
}
case 1:
{
//if( GetPlayerMoney(playerid)  <  VTearGas) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Tear Gas!");
GivePlayerMoney(playerid, -VTearGas);
GivePlayerWeapon(playerid, 17, ATearGas);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Tear Gas!");
}
case 2:
{
//if( GetPlayerMoney(playerid)  <  VMolotovCocktail) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Molotov Cocktail!");
GivePlayerMoney(playerid, -VMolotovCocktail);
GivePlayerWeapon(playerid, 18, AMolotovCocktail);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Molotov Cocktail!");
}
}
}

if(dialogid == 20323 && response)
{
switch(listitem)
{
case 0:
{
//if( GetPlayerMoney(playerid)  <  V9mm) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a 9mm!");
GivePlayerMoney(playerid, -V9mm);
GivePlayerWeapon(playerid, 22, A9mm);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a 9mm!");
}
case 1:
{
//if( GetPlayerMoney(playerid)  <  VSilenced9mm) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Silenced 9mm!");
GivePlayerMoney(playerid, -VSilenced9mm);
GivePlayerWeapon(playerid, 23, ASilenced9mm);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Silenced 9mm!");
}
case 2:
{
//if( GetPlayerMoney(playerid)  <  VDesertEagle) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Desert Eagle!");
GivePlayerMoney(playerid, -VDesertEagle);
GivePlayerWeapon(playerid, 24, ADesertEagle);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Desert Eagle!");
}
}
}
if(dialogid == 20324 && response)
{
switch(listitem)
{
case 0:
{
//if( GetPlayerMoney(playerid)  <  VShotgun) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Shotgun!");
GivePlayerMoney(playerid, -VShotgun);
GivePlayerWeapon(playerid, 25, AShotgun);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Shotgun!");
}
case 1:
{
//if( GetPlayerMoney(playerid)  <  VSawn-offShotgun) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Sawn-off Shotgun!");
GivePlayerMoney(playerid, -VSawn-offShotgun);
GivePlayerWeapon(playerid, 26, ASawn-offShotgun);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Sawn-off Shotgun!");
}
case 2:
{
//if( GetPlayerMoney(playerid)  <  VCombatShotgun) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Combat Shotgun!");
GivePlayerMoney(playerid, -VCombatShotgun);
GivePlayerWeapon(playerid, 27, ACombatShotgun);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Combat Shotgun!");
}
}
}
if(dialogid == 20325 && response)
{
switch(listitem)
{
case 0:
{
//if( GetPlayerMoney(playerid)  <  VSMG) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a SMG!");
GivePlayerMoney(playerid, -VSMG);
GivePlayerWeapon(playerid, 29, ASMG);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a SMG!");
}
case 1:
{
//if( GetPlayerMoney(playerid)  <  VUZI) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a UZI!");
GivePlayerMoney(playerid, -VUZI);
GivePlayerWeapon(playerid, 28, AUZI);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a UZI!");
}
case 2:
{
//if( GetPlayerMoney(playerid)  <  VTec-9) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Tec-9!");
GivePlayerMoney(playerid, -VTec-9);
GivePlayerWeapon(playerid, 32, ATec-9);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Tec-9!");
}
}
}
if(dialogid == 20326 && response)
{
switch(listitem)
{
case 0:
{
//if( GetPlayerMoney(playerid)  <  VAK-47) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy an AK-47!");
GivePlayerMoney(playerid, -VAK-47);
GivePlayerWeapon(playerid, 30, AAK-47);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought an AK-47!");
}
case 1:
{
//if( GetPlayerMoney(playerid)  <  VM4) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a M4!");
GivePlayerMoney(playerid, -VM4);
GivePlayerWeapon(playerid, 31, AM4);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a M4!");
}
case 2:
{
//if( GetPlayerMoney(playerid)  <  VCountryRifle) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Country Rifle!");
GivePlayerMoney(playerid, -VCountryRifle);
GivePlayerWeapon(playerid, 33, ACountryRifle);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Country Rifle!");
}
case 3:
{
//if( GetPlayerMoney(playerid)  <  VSniperRifle) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Country Rifle!");
GivePlayerMoney(playerid, -VSniperRifle);
GivePlayerWeapon(playerid, 34, ASniperRifle);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Country Rifle!");
}
}
}
if(dialogid == 20327 && response)
{
switch(listitem)
{
case 0:
{
//if( GetPlayerMoney(playerid)  <  VRocketLauncher) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Rocket Launcher!");
GivePlayerMoney(playerid, -VRocketLauncher);
GivePlayerWeapon(playerid, 35, ARocketLauncher);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Rocket Laucher!");
}
case 1:
{
//if( GetPlayerMoney(playerid)  <  VHeatSeekingRocketLauncher) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Heat Seeking Rocket Launcher!");
GivePlayerMoney(playerid, -VHeatSeekingRocketLauncher);
GivePlayerWeapon(playerid, 36, AHeatSeekingRocketLauncher);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Heat Seeking Rocket Launcher!");
}
case 2:
{
//if( GetPlayerMoney(playerid)  <  VFlamethrower) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Flamethrower!");
GivePlayerMoney(playerid, -VFlamethrower);
GivePlayerWeapon(playerid, 37, AFlamethrower);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Country Flamethrower!");
}
case 3:
{
//if( GetPlayerMoney(playerid)  <  VMini-gun) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Mini-gun!");
GivePlayerMoney(playerid, -VMini-gun);
GivePlayerWeapon(playerid, 38, AMini-gun);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Mini-gun!");
}
case 4:
{
//if( GetPlayerMoney(playerid)  <  VSatchelChargeandDetonator) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Satchel Charge Kit!");
GivePlayerMoney(playerid, -VSatchelChargeandDetonator);
GivePlayerWeapon(playerid, 39, ASatchelChargeandDetonator);
GivePlayerWeapon(playerid, 40, ASatchelChargeandDetonator);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Satchel Charge Kit!");
}
}
}
if(dialogid == 20328 && response)
{
switch(listitem)
{
case 0:
{
//if( GetPlayerMoney(playerid)  <  VSprayCan) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Spray Can!");
GivePlayerMoney(playerid, -VSprayCan);
GivePlayerWeapon(playerid, 41, ASprayCan);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Spray Can!");
}
case 1:
{
//if( GetPlayerMoney(playerid)  <  VFireExtinguisher) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Extinguisher!");
GivePlayerMoney(playerid, -VFireExtinguisher);
GivePlayerWeapon(playerid, 42, AFireExtinguisher);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Fire Extinguisher!");
}
case 2:
{
//if( GetPlayerMoney(playerid)  <  VCamera) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Camera!");
GivePlayerMoney(playerid, -VCamera);
GivePlayerWeapon(playerid, 43, ACamera);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Camera!");
}
case 3:
{
//if( GetPlayerMoney(playerid)  <  VNightvisionGoogles) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Nightvision Google!");
GivePlayerMoney(playerid, -VNightvisionGoogles);
GivePlayerWeapon(playerid, 44, ANightvisionGoogles);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Nightvision Google!");
}
case 4:
{
//if( GetPlayerMoney(playerid)  <  VThermalGoogles) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Thermal Google!");
GivePlayerMoney(playerid, -VThermalGoogles);
GivePlayerWeapon(playerid, 45, AThermalGoogles);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Thermal Google!");
}
case 5:
{
//if( GetPlayerMoney(playerid)  <  VParachute) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Parachute!");
GivePlayerMoney(playerid, -VParachute);
GivePlayerWeapon(playerid, 46, AParachute);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought a Parachute!");
}
}
}

if(dialogid == 20329 && response)
{
switch(listitem)
{
case 0:
{
//if( GetPlayerMoney(playerid)  <  VHealth) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Brass Knuckle!");
GivePlayerMoney(playerid, -VHealth);
SetPlayerHealth(playerid, 100);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully refilled your Health Bar!");
}
case 1:
{
//if( GetPlayerMoney(playerid)  <  VArmour) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Golf Club!");
GivePlayerMoney(playerid, -VArmour);
SetPlayerArmour(playerid, 100);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully bought an Armour!");
}
case 2:
{
//if( GetPlayerMoney(playerid)  <  VHealthandArmour) return SendClientMessage(playerid, COLOR_RED, "ERROR : You don't have enough money to buy a Nite Stick!");
GivePlayerMoney(playerid, -VHealthandArmour);
SetPlayerArmour(playerid, 100);
SetPlayerHealth(playerid, 100);
SendClientMessage(playerid, COLOR_GREEN, "WEAPON SHOP : You have succesfully refilled your Health Bar and bought an Armour!");
}
}
}
return 1;
}