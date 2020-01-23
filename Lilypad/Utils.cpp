#include "Main.h"
#include "Utils.h"

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