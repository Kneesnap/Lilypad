#ifndef DRAWING
#define DRAWING

#include "DirectX.h"

#pragma warning(disable : 4244)

namespace Drawing
{
	void String(int x, int y, char * string, D3DCOLOR color);
	void Rect(int x, int y, int width, int height, D3DCOLOR color);
	void BorderedRect(int x, int y, int width, int height, int fa, int fr, int fg, int fb, D3DCOLOR color);
	void Line(int x, int y, int x1, int y2, D3DCOLOR color);
	void FilledRect(int x, int y, int width, int height, D3DCOLOR color);
	void Circle(int x, int y, int radius, D3DCOLOR color);
}

namespace Color
{
	const int Red = D3DCOLOR_ARGB(255, 255, 000, 000);
	const int White = D3DCOLOR_ARGB(255, 255, 255, 255);
	const int Orange = D3DCOLOR_ARGB(255, 255, 125, 000);
	const int Yellow = D3DCOLOR_ARGB(255, 255, 255, 000);
}





#endif