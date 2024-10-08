#ifndef MP_DRAWING_H
#define MP_DRAWING_H

#include <windows.h>

void MP_drawLine(DWORD** window_p, int width, int height, HDC hdc, int x1, int y1, int x2, int y2);
void MP_drawNum(DWORD** window_p, int width, int height, HDC hdc, int num, int x, int y, int segmentLength, int segmentThickness);
void MP_drawFPS(DWORD** window_p, int width, int height, HDC hdc, double frameTime);

#endif // GRAPHICS_H