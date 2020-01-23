#ifndef DIRECTX
#define DIRECTX

#include "Main.h"
#include "Functions.h"
#include "Overlay.h"

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "Drawing.h"


struct directx_t
{
	IDirect3D9Ex * Object;
	IDirect3DDevice9Ex * Device;
	D3DPRESENT_PARAMETERS Param;
	ID3DXFont * Font;
	ID3DXFont * espFont;
	ID3DXFont * FontWarning;
	ID3DXLine * Line;
};

extern bool bPressedKeys[255];
extern bool bKeys[255];
extern directx_t DirectX;

extern void SetupMenu(wchar_t menuNames[][255], void (*toggleFunctions[])(BOOL), void (*updateFunctions[])(), int keyBinds[], int menuItemCount);

namespace DirectxFunctions
{
	void DirectXInit(HWND hwnd);
	void RenderDirectX();
}



#endif