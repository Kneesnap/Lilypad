#include "main.h"

// Options:
BYTE BOOL_TRUE[] = { 0x01, 0x00, 0x00, 0x00 };
BYTE BOOL_FALSE[] = { 0x00, 0x00, 0x00, 0x00 };

void WriteMemory(int address, LPVOID bytes, int length) {
	WriteProcessMemory(GetCurrentProcess(), (void*)address, bytes, length, 0);
}

void WriteBoolean(int address, BOOL state) {
	WriteMemory(address, (state ? &BOOL_TRUE : &BOOL_FALSE), 4);
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