#include "Overlay.h"
// https://guidedhacking.com/threads/skyrim-hack-tutorial-series-esp-entitylist-noclip.13072/

HINSTANCE hInstance;
HANDLE pHandle;
DWORD pid;
DWORD Module;

void OverlayFunctions::CreateClass(WNDPROC winproc, char * windowname)
{
	sprintf(Overlay.Name, "%s", windowname);
	Overlay.Class.cbClsExtra = 0;
	Overlay.Class.cbSize = sizeof(WNDCLASSEX);
	Overlay.Class.cbWndExtra = 0;
	Overlay.Class.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	Overlay.Class.hCursor = LoadCursor(0, IDC_ARROW);
	Overlay.Class.hIcon = LoadIcon(0, IDI_APPLICATION);
	Overlay.Class.hIconSm = LoadIcon(0, IDI_APPLICATION);
	Overlay.Class.hInstance = hInstance;
	Overlay.Class.lpfnWndProc = winproc;
	Overlay.Class.lpszClassName = Overlay.Name;
	Overlay.Class.lpszMenuName = Overlay.Name;
	Overlay.Class.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&Overlay.Class))
		exit(1);
}

void OverlayFunctions::GetTargetWindow()
{
	Target.Window = FindWindow(0, "Frogger v3.0e");
	if (!Target.Window)
		Target.Window = FindWindow(0, "Frogger");

	if (Target.Window)
	{  
		GetWindowThreadProcessId(Target.Window, &pid);
		pHandle = ProcessFunctions::GetHandle();
		Target.Checked = true;
		GetWindowRect(Target.Window, &Target.Size);
		Overlay.Width = Target.Size.right - Target.Size.left;
		Overlay.Height = Target.Size.bottom - Target.Size.top;
		Target.Style = GetWindowLong(Target.Window, GWL_STYLE);

		if (Target.Style & WS_BORDER)
		{
			Target.Size.top += 23;
			Overlay.Height -= 23;
		}

		MoveWindow(Overlay.Window, Target.Size.left, Target.Size.top, Overlay.Width, Overlay.Height, true);
		Overlay.Margin = { 0, 0, Overlay.Width, Overlay.Height };

	}
}

void OverlayFunctions::CreateWindowOverlay()
{
	Overlay.Window = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT, Overlay.Name, Overlay.Name, WS_POPUP, 1, 1, Overlay.Width, Overlay.Height, 0, 0, hInstance, 0);
	SetLayeredWindowAttributes(Overlay.Window, RGB(0, 0, 0), 255, LWA_COLORKEY | LWA_ALPHA);
	ShowWindow(Overlay.Window, SW_SHOW);
	DwmExtendFrameIntoClientArea(Overlay.Window, &Overlay.Margin);
}