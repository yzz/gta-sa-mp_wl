/*----------------------------------------------------------------------------*-
					====================================
					 y_testing - Run unit tests easilly 
					====================================
Description:
	Runs any functions named as tests when the Testing_Run function is called.
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the SA:MP script information include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2008
	the Initial Developer. All Rights Reserved.
	
	Special Thanks to:
	
	SA:MP Team past, present and future
Version:
	1.0
Changelog:
	06/08/10:
		First version
-*----------------------------------------------------------------------------*/

#include <YSI\y_scripting>

#if defined RUN_TESTS
	#define Test:%1() forward bool:Test_@%1(); public bool:Test_@%1()
	#define TestInit:%1() forward Init_@%1(); public Init_@%1()
	#define TestClose:%1() forward Shut_@%1(); public Shut_@%1()
#else
	#define Test:%1() stock bool:Test_@%1()
	#define TestInit:%1() stock Init_@%1()
	#define TestClose:%1() stock Shut_@%1()
#endif

/*----------------------------------------------------------------------------*-
Function:
	Testing_Run
Params:
	&tests - Number of tests run.
	&fails - Number of tests which failed.
	buffer[33] - The name of the first test which failed.
Return:
	Wether all tests were sucessful or not.
Notes:
	-

native Testing_Run(&tests, &fails, buffer[33] = "");

-*----------------------------------------------------------------------------*/

stock bool:Testing_Run(&tests, &fails, lastfail[33] = "")
{
	#if defined RUN_TESTS
		new
			idx,
			buffer[33];
		tests = 0;
		fails = 0;
		while ((idx = Scripting_GetPublic(idx, buffer, "Test_@")))
		{
			++tests;
			// Call the setup function if there is one.
			buffer[0] = 'I';
			buffer[1] = 'n';
			buffer[2] = 'i';
			buffer[3] = 't';
			CallLocalFunction(buffer, "");
			// Call the test.
			buffer[0] = 'T';
			buffer[1] = 'e';
			buffer[2] = 's';
			buffer[3] = 't';
			if (!CallLocalFunction(buffer, ""))
			{
				if (fails)
				{
					++fails;
				}
				else
				{
					// Copy the string over.
					while ((lastfail[fails] = buffer[fails])) ++fails;
					fails = 1;
				}
			}
			// Call the shutdown function if there is one.
			buffer[0] = 'S';
			buffer[1] = 'h';
			buffer[2] = 'u';
			buffer[3] = 't';
			CallLocalFunction(buffer, "");
		}
		return fails == 0;
	#else
		#pragma unused tests, fails, lastfail
		return true;
	#endif
}
