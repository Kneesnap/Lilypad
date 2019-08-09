#ifndef FUNCTIONS
#define FUNCTIONS

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include "Overlay.h"
#include <time.h>

struct vec4
{
	float x, y, z, w;
};
struct vec3
{
	float x, y, z;
};
struct vec2
{
	int x, y;
};

namespace ProcessFunctions
{
	template < class TypeValue > TypeValue ReadMemory(DWORD Address);
	template < class TypeValue > TypeValue WriteMemory(DWORD Address);
	void CheckDWM();
	DWORD GetModuleBase(DWORD dwProcessIdentifier, TCHAR *lpszModuleName);
	HANDLE GetHandle();
}

template <class TypeValue>
TypeValue ProcessFunctions::ReadMemory(DWORD Address)
{
	TypeValue Value;
	ReadProcessMemory(pHandle, (LPCVOID*)Address, &Value, sizeof(TypeValue), 0);
	return Value;
}

template <class TypeValue>
TypeValue ProcessFunctions::WriteMemory(DWORD Address)
{
	TypeValue Value;
	WriteProcessMemory(pHandle, (LPCVOID*)Address, &Value, sizeof(TypeValue), 0);
	return Value;
}

#endif



