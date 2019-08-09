#include "main.h"

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
int ReadInteger(int address) {
	return *((int*)ReadMemory(address, 4));
}

//TODO: Make easier to inject and work.
//TODO: More version support.
//TODO: Add mods / cheats.

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