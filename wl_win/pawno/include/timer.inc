/*
轮到Y_Less的“长篇小说”了：可以传递参数的计时器！！但是以前有BUG。。。害得Nick~~郁闷了半天 真实那个图搁浅了差不多5天。现在应该修复了吧。。
原帖地址：http://forum.sa-mp.com/index.php?topic=638.msg21968#msg21968
太长鸟。。。
偶罢工 8翻译鸟。。。。
开始：
SetTimerEx and KillTimerEx

These functions are an expansion of SetTimer and KillTimer allowing up to 8 parameters to be passed to the function with the timer (you can increase it but I've not found a smooth way to yet so you need to add more code).  This is quite a complex function and you also need to do a bit of work to get it going but it does work.  Also, due to the amount of exra code and defines involved I've made it as an include.

Code:

Put the following code in a blank file called ste.inc and put it in your include folder with your other .inc files:


PAWN Code:
*/
/* SetTimerEx functions and variables
 *
 *  (c) 2006 Alex "Y_Less" Cole
 *
 *  Version 0.1 ste.inc
 */

#if defined _ste_included
#endinput
#endif
#define _ste_included

#if !defined _samp_included
#include <a_samp>
#endif

#define MAX_PARS 8
#define MAX_TIMERS 32

#define func0(%1); if (num == 0 && strcmp(str, "%1") == 0) %1();
#define func1(%1); if (num == 1 && strcmp(str, "%1") == 0) %1(func[0]);
#define func2(%1); if (num == 2 && strcmp(str, "%1") == 0) %1(func[0], func[1]);
#define func3(%1); if (num == 3 && strcmp(str, "%1") == 0) %1(func[0], func[1], func[2]);
#define func4(%1); if (num == 4 && strcmp(str, "%1") == 0) %1(func[0], func[1], func[2], func[3]);
#define func5(%1); if (num == 4 && strcmp(str, "%1") == 0) %1(func[0], func[1], func[2], func[3], func[4]);
#define func6(%1); if (num == 4 && strcmp(str, "%1") == 0) %1(func[0], func[1], func[2], func[3], func[4], func[5]);
#define func7(%1); if (num == 4 && strcmp(str, "%1") == 0) %1(func[0], func[1], func[2], func[3], func[4], func[5], func[6]);
#define func8(%1); if (num == 4 && strcmp(str, "%1") == 0) %1(func[0], func[1], func[2], func[3], func[4], func[5], func[6], func[7]);

enum timerdat
{
	FUNCTION[128],
	TRIGGERED,
	INTERVAL,
	REPEAT,
	NUMPARS,
	PARAMETER[MAX_PARS]
}

new timers[MAX_TIMERS][2];

public SetTimerEx(...){
	static timerd[MAX_TIMERS][timerdat];
	static numt = 0;
	new na = numargs();
	if (!na){
		new i, j = GetTickCount();
		for (i = 0; i < MAX_TIMERS; i++){
			new k = timerd[i][TRIGGERED];
			if (k){
				if (!timers[i][0]){
					timerd[i][TRIGGERED] = 0;
					timerd[i][REPEAT] = 0;
				}else if (j - k >= timerd[i][INTERVAL]){
					break;
				}
			}
		}
		if (i == MAX_TIMERS){
			return 0;
		}
		STE_function_list(timerd[i][FUNCTION], timerd[i][NUMPARS], timerd[i][PARAMETER]);
		if (timerd[i][REPEAT] == 1){
			timerd[i][TRIGGERED] = GetTickCount();
			timers[i][1] = SetTimer("SetTimerEx", timerd[i][INTERVAL], 0);
		}else{
			timerd[i][TRIGGERED] = 0;
		}
	}else{
		if (na < 3 || numt == MAX_TIMERS){
			return 0;
		}
		new str[128];
		new i = 0, j = 0;
		for ( ; i < sizeof (str); i++){
			j = getarg(0, i);
			if (j != 0){
				str[i] = j;
			}else{
				break;
			}
		}
		for (j = 0; j < MAX_TIMERS; j++){
			if (!timerd[j][TRIGGERED]){
				break;
			}
		}
		for ( ; i; i--){
			timerd[j][FUNCTION][i - 1] = str[i - 1];
		}
		timerd[j][TRIGGERED] = GetTickCount();
		i = getarg(1);
		timerd[j][INTERVAL] = i;
		i = getarg(2);
		timerd[j][REPEAT] = i ? 1 : 0;
		na -= 3;
		timerd[j][NUMPARS] = na;
		for (i = 0; i < na && i < MAX_PARS; i++){
			timerd[j][PARAMETER][i] = getarg(i + 3);
		}
		numt++;
		i = SetTimer("SetTimerEx", timerd[j][INTERVAL], 0);
		timers[j][0] = i;
		timers[j][1] = i;
		return i;
	}
	return 0;
}

KillTimerEx(timerid){
	for (new i = 0; i < MAX_TIMERS; i++){
		if (timers[i][0] == timerid){
			KillTimer(timers[i][1]);
			timers[i][1] = 0;
			timers[i][0] = 0;
			return 1;
		}
	}
	return 0;
}
/*
Usage:

Firstly you need to place a function somewhere in your code called:


PAWN Code:
STE_function_list(str[], num, func[])
Because (AFAIK) you can't dynamically call functions from PAWN, only SetTimer can cos it's native you need to create a lookup table of function calls based on names, fortunately thats not as hard as it sounds, this is an example of one line of the lookup table:


PAWN Code:
func3(AfunctionName);
"func" is required by them all, 3 is the number of parameters this function takes (it's not in the brackets due to function redefinition problems) and AFunctionName is obviously the name of a function (note the lack of quotes around it).  So based on that the lookup line for a function called "GetSomething" (remember ALL functions called from your script by timers must be listed here) with 0 parameters would be:


PAWN Code:
func0(GetSomething);
And with 8 (the current max):


PAWN Code:
func8(GetSomething);
The full code for this function (as I have it and with a few example functions) is:


PAWN Code:
*/
STE_function_list(str[], num, func[])
{
/*
========================================================================
||                                                                    ||
||         List all the functions you are going to call below         ||
||                                                                    ||
||     This is VERY important to the functionality of the function    ||
||                                                                    ||
||   List in the format: func<number of parameters>(<function name>)  ||
||   Don't worry about the parameters, they're all sorted themselves  ||
||    Up to 8 parameters per function - pass on the end of the call   ||
||    SetTimerEx(<func>, <interval>, <repeat>, <par1>, <par2>, ...)   ||
||                                                                    ||
========================================================================
*/
func1(TimerCalledFunction);
func0(TimerCalled);
func3(FunctionWith3Parameters);
/*
========================================================================
||                                                                    ||
||         List all the functions you are going to call above         ||
||                                                                    ||
||     This is VERY important to the functionality of the function    ||
||                                                                    ||
========================================================================
*/
}
/*
Actually using the functions couldn't be simplar:


PAWN Code:
SetTimerEx("Funcname", delay, repeat, parameters...);
The first 3 are exactly the same as with SetTimer, you then just tack on as many variables as you want to the end (up to 8, can be 0).

KillTimerEx is exactly the same as KillTimer but you must use it instead or it may not work.

A Few Important Notes:

This function ONLY passes integer parameters, if you want to pass floats I suggest you multiply by 1000, do a floatround on it, pass that then turn back into a float and divide at the other end.  Float support will never be properly added as there is no getarg for floats and no way to tell what it is anyway.  Array support may be added but not atm.

This function, unlike SetTimer DOES work with native functions so you can call GivePlayerMoney with a delay if you really want.

It has the same return values as the normal SetTimer for use with other things or KillTimerEx.

Edit: Just a tiny update, I realised functions are case sensitive and this thing wasn't, so I changed it. 
 
? Last Edit: October 18, 2006, 06:12:34 PM by Y_Less  
 
有人帮忙翻译下么。。。。。。
好长
*/