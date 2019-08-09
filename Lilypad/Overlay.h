#ifndef WINDOW
#define WINDOW

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include "Functions.h"
#include "Main.h"
#include <dwmapi.h>
#include <io.h>
#include <Fcntl.h>
#include <TlHelp32.h>

#pragma comment(lib, "dwmapi.lib")

struct overlay_t
{
	WNDCLASSEX Class;
	char Name[256];
	int Width, Height;
	HWND Window;
	MSG Message;
	MARGINS Margin;
};
extern overlay_t Overlay;

struct target_t
{
	char Name[256];
	HWND Window;
	RECT Size;
	DWORD Style;
	BOOL Checked;
};
extern target_t Target;


namespace OverlayFunctions
{
	void CreateClass(WNDPROC winproc, char * windowname);
	void GetTargetWindow();
	void CreateWindowOverlay();
}


extern HINSTANCE hInstance;
extern HANDLE pHandle;
extern DWORD pid;
extern DWORD Module;
#endif // !WINDOW
