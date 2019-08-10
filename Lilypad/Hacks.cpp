#include "main.h"
#include "Hacks.h"

// Options:
BYTE BOOL_TRUE[] = { 0x01, 0x00, 0x00, 0x00 };
BYTE BOOL_FALSE[] = { 0x00, 0x00, 0x00, 0x00 };

byte* ReadMemory(int address, int size) {
	byte* result;

	result = (byte*)malloc(size);
	ReadProcessMemory(GetCurrentProcess(), (void*)address, result, size, 0);
	return result;
}


void WriteMemory(int address, LPVOID bytes, int length) {
	WriteProcessMemory(GetCurrentProcess(), (void*)address, bytes, length, 0);
}

void WriteByte(int address, byte value) {
	WriteMemory(address, &value, 1);
}

void WriteInteger(int address, int value) {
	WriteMemory(address, &value, 4);
}

void WriteShort(int address, short value) {
	WriteMemory(address, &value, 2);
}

void WriteBoolean(int address, BOOL state) {
	WriteMemory(address, (state ? &BOOL_TRUE : &BOOL_FALSE), 4);
}

byte* NopCode(int address, int size) {
	byte* result;
	int i;

	result = ReadMemory(address, size); // Read old code.
	for (i = 0; i < size; i++) // Write nop.
		WriteByte(address + i, 0x90);

	return result;
}

// Read:
int ReadByte(int address) {
	return *ReadMemory(address, 1);
}

int ReadInteger(int address) {
	return *((int*)ReadMemory(address, 4));
}

short ReadShort(int address) {
	return *((short*)ReadMemory(address, 2));
}

// Utils:
bool isGamePaused() {
	return ReadByte(0x478548);
}

// Toggle Functions:
void ToggleCollisionBypass(BOOL new_state) {
	WriteBoolean(0x475934, new_state);
}

void ToggleFreezeTime(BOOL new_state) {
	WriteBoolean(0x475938, new_state);
}

void ToggleInfiniteLives(BOOL new_state) {
	WriteBoolean(0x47593C, new_state);
}

int oldBrightness;
byte* caveCode1;
byte* caveCode2;
void ToggleCaveBright(BOOL new_state) {
	if (new_state) { // Enable.
		caveCode1 = NopCode(0x43CEEE, 6); // Preent light from decreasing.
		caveCode2 = NopCode(0x43CEB2, 5); // Remove maximum light cap.		
		oldBrightness = ReadInteger(0x497A10);
		WriteInteger(0x497A10, INT_MAX - 100); // Sets the brightness high. Subtracting 100 maxes croak not make it wrap around.
	} else { // Disable
		WriteMemory(0x43CEEE, caveCode1, 6);
		WriteMemory(0x43CEB2, caveCode2, 5);
		WriteInteger(0x497A10, oldBrightness); // Restore original brightness.
	}
}

FreecamOffset FreecamOffsets[FREECAM_OFFSET_TYPE_LENGTH] = {
	{
		0x497164, // ca_current.vx
		VK_KEY_A,
		VK_KEY_D,
		25,
		CAMERA_Z,
		false,
		0
	},
	{
		0x497168, // ca_current.vy
		VK_SPACE,
		VK_SHIFT,
		25,
		-1,
		false,
		0
	},
	{
		0x49716C, // ca_current.vz
		VK_KEY_S,
		VK_KEY_W,
		25,
		CAMERA_X,
		false,
		0
	},
	{
		0x497144, // ca_next_target_ofs.vx
		VK_KEY_J,
		VK_KEY_L,
		7,
		TARGET_Y,
		true,
		0
	},
	{
		0x497146, // ca_next_target_ofs.vy
		VK_KEY_K,
		VK_KEY_I,
		-7,
		-1,
		true,
		0
	},
	{
		0x497148, // ca_next_target_ofs.vz
		VK_KEY_1,
		VK_KEY_2,
		7,
		TARGET_X,
		true,
		0
	}
};

int GetFreeCamAddress(FreecamOffsetType offsetType) {
	return FreecamOffsets[offsetType].address;
}

int OldFreecamData[FREECAM_OFFSET_TYPE_LENGTH];
void ToggleFreecam(BOOL new_state) {
	FreecamOffset* offset;
	int i;

	if (new_state) { // Enable.
		for (i = 0; i < FREECAM_OFFSET_TYPE_LENGTH; i++) { // Load camera data.
			offset = &FreecamOffsets[i];
			if (offset->target) {
				offset->value = (int) ReadShort(offset->address);
			} else {
				offset->value = ReadInteger(offset->address);
			}
			OldFreecamData[i] = offset->value;
		}
	} else { // Disable.
		for (i = 0; i < FREECAM_OFFSET_TYPE_LENGTH; i++) { // Apply old camera data.
			offset = &FreecamOffsets[i];
			if (offset->target) {
				WriteShort(offset->address, (short)OldFreecamData[i]);
			} else {
				WriteInteger(offset->address, OldFreecamData[i]);
			}
		}
	}
}


void handleMove(int type, int rotation) {
	bool sideways;
	FreecamOffset* self;
	FreecamOffset* offset;
	int dKey, iKey, tempKey, valueChange;
	
	self = &FreecamOffsets[type];
	offset = &FreecamOffsets[type];
	sideways = (rotation == 1 || rotation == 3);
	if (offset->alternate != -1 && sideways)
		offset = &FreecamOffsets[offset->alternate];

	dKey = offset->decrKey;
	iKey = offset->incrKey;

	if ((self->alternate != -1 && rotation == 2) || (rotation == 3 && type == CAMERA_X) || (rotation == 1 && type == CAMERA_Z)
		|| (rotation == 1 && type == TARGET_Z) || (rotation == 3 && type == TARGET_X)) { // Flip controls.
		tempKey = dKey;
		dKey = iKey;
		iKey = dKey;
	}

	valueChange = (bPressedKeys[iKey] ? self->valueChange : 0) - (bPressedKeys[dKey] ? self->valueChange : 0);

	//TODO: Maybe camera bounds fix.
	self->value += valueChange;
}

void UpdateFreecam() {
	FreecamOffset offset;
	int i;

	if (isGamePaused())
		return; // Do nothing while game is paused.

	int rotation = ReadByte(0x497214);
	for (i = 0; i < FREECAM_OFFSET_TYPE_LENGTH; i++) {
		offset = FreecamOffsets[i];
		handleMove(i, rotation);

		if (offset.target) {
			WriteShort(offset.address, (short)offset.value);
		} else {
			WriteInteger(offset.address, offset.value);
		}
	}
}


//TODO: Make easier to inject and work.
//TODO: Further modularize modules.