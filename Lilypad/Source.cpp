#include <Windows.h>
#include <iostream>  
#include "Hooks.h"
//https://guidedhacking.com/threads/skyrim-hack-tutorial-series-esp-entitylist-noclip.13072/

void InitiateHooks()
{
	/*****************FLYING************************/
	//Find the instruction that accesses our Yaxis, our pattern scan ensures we can find it every time
	DWORD flyAddy = FindPattern("Worms W.M.D.exe",
		"\xF3\x0F\x11\x81\x00\x00\x00\x00\x5D\xC2\x04\x00\xCC\x55", "xxxx????xxxxxx");
	MsgBoxAddy(flyAddy);

	//Where we have to jump back to after we take the y axis
	
	FlyingJmpBack = flyAddy + 0x8;
	//place jump to grab our Y axis so we can fly
	//instruction is 6 bytes because we are replacing 2 instructions
	
	PlaceJMP((BYTE*)flyAddy, (DWORD)GetPlayerYaxis, 8);
}



//Our hacks thread, here we overwrite any values that we take from our hooks
DWORD WINAPI OverwriteValues()
{
	/*Loop forever, with a 150 millisecond interval per loop*/
	for(;;Sleep( 20 ))
	{
		//assign/re-assign our value incase anything has changed
		//This is not necessary in some games, it generally is required if the game freezes during injection[long story :S]
		//Read the address and set it up to be overwritten
		//now all we have to do is get user input and modify the player's height
		//allowing us to fly :)
		//Because our offset was of 3C we add it and now we have our Yaxis addy
		YAxisPtr = YaxisRegister + 0x2A0;
	
		//Overwrite values
		//FLY if the space key is held!!
		if(GetAsyncKeyState(VK_DOWN))
		{
			//Display our addy containing the Y axis that we need to adjust
			//MsgBoxAddy(YAxisPtr);
			//Increase our Y axis making us FLY :()
			*(float *)YAxisPtr += 100.0;
		}
		if(GetAsyncKeyState(VK_UP))
		{
			//Bring us back down if we get stuck somewhere
			*(float *)YAxisPtr -= 100.0;
		}

		YAxisPtr2 = YaxisRegister + 0x29C;


		if (GetAsyncKeyState(VK_RIGHT))
		{
			//Display our addy containing the Y axis that we need to adjust
			//MsgBoxAddy(YAxisPtr);
			//Increase our Y axis making us FLY :()
			*(float *)YAxisPtr2 += 100.0;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			//Bring us back down if we get stuck somewhere
			*(float *)YAxisPtr2 -= 100.0;
		}
	}
}

BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,  // handle to DLL module
	DWORD fdwReason,     // reason for calling function
	LPVOID lpReserved)     // reserved
{
	// Perform actions based on the reason for calling.
	switch(fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Initialize once for each new process.
		// Return FALSE to fail DLL load.
		//MessageBoxA(NULL, "Attached successfuly", "", 0);
		InitiateHooks();
		CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)OverwriteValues, NULL, NULL, NULL );	
		break;
	}
	// Successful DLL_PROCESS_ATTACH.
	return TRUE;
}