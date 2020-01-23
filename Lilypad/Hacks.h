#ifndef HACKS
#define HACKS

#include "main.h"
#include "Utils.h"
#include "DirectX.h"

extern void ToggleCollisionBypass(BOOL);
extern void ToggleFreezeTime(BOOL);
extern void ToggleInfiniteLives(BOOL);
extern void ToggleCaveBright(BOOL);
extern void ToggleFreecam(BOOL);

extern void UpdateFreecam();
extern void SetupFrogger1997();


enum FreecamOffsetType {
	CAMERA_X,
	CAMERA_Y,
	CAMERA_Z,
	TARGET_X,
	TARGET_Y,
	TARGET_Z,
	FREECAM_OFFSET_TYPE_LENGTH,
};

struct FreecamOffset {
	int address;
	int decrKey;
	int incrKey;
	int valueChange;
	int alternate;
	bool target;
	int value;
};

#endif