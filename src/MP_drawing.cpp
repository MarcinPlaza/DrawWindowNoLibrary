#include "MP_drawing.h"
#include <windows.h>
#include <iostream>
void MP_drawLine(DWORD** window_p, int width, int height, HDC hdc, int x1, int y1, int x2, int y2) {
    DWORD* ws_cpy = *window_p;
    
    int domain = abs(x2 - x1);
    int range = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = domain - range;

    while (true) {
        // Set the pixel on the HDC at the current x1, y1
        int curr = (y1*width)+x1;
        //SetPixel(hdc, x1, y1, RGB(0, 0, 0)); // Black color
        //std::cout<<curr<<std::endl;
        ws_cpy[curr] = 0x0000aaff;

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -range) {
            err -= range;
            x1 += sx;
        }
        if (e2 < domain) {
            err += domain;
            y1 += sy;
        }
    }
}

void MP_drawNum(DWORD** window_p, int width, int height, HDC hdc, int num, int x, int y, int segmentLength, int segmentThickness) {

    // Lambda function to draw a horizontal segment
    auto drawHorizontal = [&](int x1, int y1) {
        for (int i = 0; i < segmentThickness; i++){
            MP_drawLine(window_p, width, height, hdc, x1, y1+i, x1 + segmentLength, y1+i);
        }
    };

    // Lambda function to draw a vertical segment
    auto drawVertical = [&](int x1, int y1) {
        for (int i = 0; i < segmentThickness; i++){
            MP_drawLine(window_p, width, height, hdc, x1+i, y1, x1+i, y1 + segmentLength);
        }
        
    };

    // Lambda functions to draw each segment (A-G)
    auto drawSegmentA = [&]() {
        drawHorizontal(x, y);  // A is the top horizontal line
    };
    auto drawSegmentB = [&]() {
        drawVertical(x + segmentLength, y);  // B is the right-top vertical line
    };
    auto drawSegmentC = [&]() {
        drawVertical(x + segmentLength, y + segmentLength);  // C is the right-bottom vertical line
    };
    auto drawSegmentD = [&]() {
        drawHorizontal(x, y + 2 * segmentLength);  // D is the bottom horizontal line
    };
    auto drawSegmentE = [&]() {
        drawVertical(x, y + segmentLength);  // E is the left-bottom vertical line
    };
    auto drawSegmentF = [&]() {
        drawVertical(x, y);  // F is the left-top vertical line
    };
    auto drawSegmentG = [&]() {
        drawHorizontal(x, y + segmentLength);  // G is the middle horizontal line
    };

    // Now, depending on the number, call the relevant segment-drawing lambdas
    if (num == 0) {  // Segments: A, B, C, D, E, F
        drawSegmentA();
        drawSegmentB();
        drawSegmentC();
        drawSegmentD();
        drawSegmentE();
        drawSegmentF();
    } else if (num == 1) {  // Segments: B, C
        drawSegmentB();
        drawSegmentC();
    } else if (num == 2) {  // Segments: A, B, G, E, D
        drawSegmentA();
        drawSegmentB();
        drawSegmentG();
        drawSegmentE();
        drawSegmentD();
    } else if (num == 3) {  // Segments: A, B, G, C, D
        drawSegmentA();
        drawSegmentB();
        drawSegmentG();
        drawSegmentC();
        drawSegmentD();
    } else if (num == 4) {  // Segments: F, G, B, C
        drawSegmentF();
        drawSegmentG();
        drawSegmentB();
        drawSegmentC();
    } else if (num == 5) {  // Segments: A, F, G, C, D
        drawSegmentA();
        drawSegmentF();
        drawSegmentG();
        drawSegmentC();
        drawSegmentD();
    } else if (num == 6) {  // Segments: A, F, G, E, D, C
        drawSegmentA();
        drawSegmentF();
        drawSegmentG();
        drawSegmentE();
        drawSegmentC();
        drawSegmentD();
    } else if (num == 7) {  // Segments: A, B, C
        drawSegmentA();
        drawSegmentB();
        drawSegmentC();
    } else if (num == 8) {  // Segments: A, B, C, D, E, F, G
        drawSegmentA();
        drawSegmentB();
        drawSegmentC();
        drawSegmentD();
        drawSegmentE();
        drawSegmentF();
        drawSegmentG();
    } else if (num == 9) {  // Segments: A, B, C, D, F, G
        drawSegmentA();
        drawSegmentB();
        drawSegmentC();
        drawSegmentD();
        drawSegmentF();
        drawSegmentG();
    }
}
void MP_drawFPS(DWORD** window_p, int width, int height, HDC hdc, double frameTime) {
    if (frameTime <= 0) {
        frameTime = 1; // Prevent division by zero
    }

    int fps = static_cast<int>(1000000.0 / frameTime); // Convert microseconds to FPS

    // Draw each digit of FPS
    MP_drawNum(window_p, width, height, hdc, fps % 10, 50, 10, 10, 2); // Draw units
    fps /= 10;
    MP_drawNum(window_p, width, height, hdc, fps % 10, 35, 10, 10, 2); // Draw tens
    fps /= 10;
    MP_drawNum(window_p, width, height, hdc, fps % 10, 20, 10, 10, 2); // Draw hundreds
    fps /= 10;
    MP_drawNum(window_p, width, height, hdc, fps % 10, 5, 10, 10, 2);   // Draw thousands
}