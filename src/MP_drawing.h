#ifndef MP_DRAWING_H
#define MP_DRAWING_H

#include <windows.h>

void MP_drawLine(HDC hdc, int x1, int y1, int x2, int y2);
void MP_drawNum(HDC hdc, int num, int x, int y, int segmentLength, int segmentThickness);
void MP_drawFPS(HDC hdc, double frameTime);

#endif // GRAPHICS_H