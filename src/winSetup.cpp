#include "winSetup.h"
#include <windows.h>

void MakeBitMap(HWND hwnd, HBITMAP* Bitmap, BITMAPINFO Bmi, DWORD** window_p, int Width, int Height)
{
	// Create the bitmap info header:
	Bmi.bmiHeader.biSize = sizeof(Bmi.bmiHeader);
	Bmi.bmiHeader.biWidth = Width;
	Bmi.bmiHeader.biHeight = -Height;
	Bmi.bmiHeader.biPlanes = 1;
	Bmi.bmiHeader.biBitCount = GetDeviceCaps(GetDC(hwnd), BITSPIXEL);
	Bmi.bmiHeader.biCompression = BI_RGB;
	Bmi.bmiHeader.biSizeImage = 0;
	Bmi.bmiHeader.biXPelsPerMeter = 0;
	Bmi.bmiHeader.biYPelsPerMeter = 0;
	Bmi.bmiHeader.biClrUsed = 0;
	Bmi.bmiHeader.biClrImportant = 0;

	// DIB = Device Independent Bitmap, a bitmap we can use regardless of device:
	*Bitmap = CreateDIBSection 
	(
		GetDC(hwnd),
		&Bmi,
		DIB_RGB_COLORS,
		(void**)window_p,
		0,
		0
	);

	// Get a handle (pointer) to the bits of the bitmap:
	GetDIBits
	(
		GetDC(hwnd),
		*Bitmap,
		0,
		Height,
		*window_p,
		&Bmi,
		DIB_RGB_COLORS
	);

	// Write some colour value to the buffer:
	DWORD* ws_cpy = *window_p; // This creates a local copy of our bitmap pointer
	int MapSize = Width * Height; // Just to be explicit, probably would get optimized to this by compiler
	for (int c = 0; c < MapSize; c++) ws_cpy[c] = 0x0000aaff; // aRGB in hexadecimal format
}

