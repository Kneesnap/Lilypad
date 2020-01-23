#include "Frogger2.h"


void UpdateFreecam2() {
	int x, y, z;

	//TODO: Do nothing while game is paused.

	x = ReadInteger(0x471160);
	y = ReadInteger(0x471164);
	z = ReadInteger(0x471168);

	if (bPressedKeys[VK_KEY_D])
		x += 1000000;
	if (bPressedKeys[VK_KEY_A])
		x -= 1000000;

	if (bPressedKeys[VK_SPACE])
		y += 1000000;
	if (bPressedKeys[VK_SHIFT])
		y -= 1000000;

	if (bPressedKeys[VK_KEY_S])
		z += 1000000;
	if (bPressedKeys[VK_KEY_W])
		z -= 1000000;

	WriteInteger(0x471160, x);
	WriteInteger(0x471164, y);
	WriteInteger(0x471168, z);
}

#define Frogger2MenuItems 1
wchar_t wMenuItems2[Frogger2MenuItems][255] =
{
	L"B: Freecam",
};

void (*MenuToggles2[])(BOOL) = {
	NULL,
};

int KeyBinds2[Frogger2MenuItems] = {
	VK_KEY_B
};


void (*MenuUpdate2[])() = {
	UpdateFreecam2,
};

void SetupFrogger2() {
	SetupMenu(wMenuItems2, MenuToggles2, MenuUpdate2, KeyBinds2, Frogger2MenuItems);
}