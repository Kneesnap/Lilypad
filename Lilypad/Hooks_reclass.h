#include "Functions.h"

int ix;
DWORD EntityObjStart = 0x0;
DWORD EntlistJmpBack = 0x0;
bool alreadyThere = false;

//playerent * ents[255];
//playerent * entsptr;
//
//
//__declspec(naked) void entityhook()
//{
//	__asm {
//		mov edx, [esi + 0x34]
//		mov eax, [esi + 0x38]
//		mov EntityObjStart, esi
//		pushad
//	}
//
//	__asm {
//		mov eax, EntityObjStart
//		mov[entsptr], eax
//	}
//
//	if (entsptr == nullptr)
//	{
//		goto GIVE_UP;
//	}
//
//	alreadyThere = false;
//
//	for (ix = 0; ix < 254; ix++)
//	{
//		if (ents[ix] == entsptr)
//		{
//			alreadyThere = true;
//			break;
//		}
//	}
//
//	if (alreadyThere)
//	{
//		goto GIVE_UP;
//	}
//	else
//	{
//		for (ix = 0; ix < 254; ix++)
//		{
//			if (ents[ix] == 0)
//			{
//				ents[ix] = entsptr;
//				break;
//			}
//		}
//	}
//
//GIVE_UP:
//	__asm {
//		popad
//		jmp[EntlistJmpBack]
//	}
//}