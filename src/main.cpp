// Some macro definitions, not needed for our current project, but you are quite likely to run into situations when they are useful.
#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

// You do not need any of the above, but it can get useful, see the link or, if the link is dead, google the term "#ifndef UNICODE"

// This is where the interesting stuff starts:
// First, we need access to the Windows API (Application Programming Interface):
#include <windows.h>
#include "winSetup.h"
#include "MP_drawing.h"

/*
	HDC = Handle to Device Context
	
	Device Context, as defined on Microsoft Docs: 

		A device context is a structure that defines a set of graphic objects and 
		their associated attributes, as well as the graphic modes that affect output.
*/
HDC hdc_main; // Represents our physical device
HDC hdc_comp; // A virtual device which we will use to draw "behind the scenes"

// A pointer to the buffer that we will be using to play with pixels =) 
DWORD* window_bmp_p;

// The Windows API specific bitmap 
HBITMAP whole_screen; // Handle to a bitmap
BITMAPINFO bmi; // A data struct holding info necessary to create a bitmap

// Windows requires this to draw:
PAINTSTRUCT ps;

int screenw = 500; //GetSystemMetrics(SM_CXSCREEN);
int screenh = 500; // GetSystemMetrics(SM_CYSCREEN);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);





void Prepare_Screen(HWND hwnd)
{
	MakeBitMap(hwnd, &whole_screen, bmi, &window_bmp_p, screenw, screenh);
	hdc_main = GetDC(hwnd);
	hdc_comp = CreateCompatibleDC(hdc_main);
	SelectObject(hdc_comp, whole_screen);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	// Register the window class:
	const wchar_t CLASS_NAME[] = L"TheWindowClass";

	WNDCLASS wc = { 0 };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	//ShowCursor(false);

	// Create the window:
	/*
		The "Ex" suffix inf "CreateWindowEx" allows us to use "extended window styles" (the first argument). 
		Not actually required for what we are doing, but you might find it fun to play with.
		If you want to, you can just use "Create Window" and omit the first argument.
	*/ 
	HWND hwnd = CreateWindowEx( 
		WS_EX_TRANSPARENT, //WS_EX_TRANSPARENT, WS_EX_OVERLAPPEDWINDOW  // Optional, "extended" window styles.
		CLASS_NAME,                     // Window class
		L"YT_Tutorial",					// Window text
		WS_POPUP | WS_VISIBLE,			// Window style

		// Position and size:
		0, 0,
		screenw,
        screenh,
        //GetSystemMetrics(SM_CXSCREEN), // 400
		//GetSystemMetrics(SM_CYSCREEN), // 600

		// Just leave this as is:
		NULL,       // Parent window
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	Prepare_Screen(hwnd);

	ShowWindow(hwnd, nCmdShow);

	// Run the message loop:
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
int anim = 0;
bool temp = false;
// This is where the messages are handled. As you expand your program, you will essentially use this as your starting point (tutorial upcoming).
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{   
    //timer stuff for fps
    static LARGE_INTEGER frequency;
    static BOOL frequencyInitialized = FALSE;
    // Initialize the performance frequency only once
    if (!frequencyInitialized) {
        QueryPerformanceFrequency(&frequency);
        frequencyInitialized = TRUE;
    }
    // Variables for performance counter
    LARGE_INTEGER start, end;
    // Start measuring time
    QueryPerformanceCounter(&start);


    //actual loop
    HDC hdc = BeginPaint(hwnd, &ps);
    
	/*
    // Animation logic
        if (anim > 500) {
            temp = true;
        }
        if (anim < 2) {
            temp = false;
        }
        if (temp) {
            anim--;
        } else {
            anim++;
        }

    MP_drawLine( &window_bmp_p, screenw, screenh, hdc, 0, 500 - anim, 500, anim);
    MP_drawLine(&window_bmp_p, screenw, screenh, hdc, 500 - anim, 0, anim, 500);

	QueryPerformanceCounter(&end);
    double frameTime = (double)(end.QuadPart - start.QuadPart) * 1000000.0 / frequency.QuadPart;
    // Draw the FPS
    MP_drawFPS(&window_bmp_p, screenw, screenh, hdc, frameTime);
	*/

	//I want this to work+++++++++++++++++++++++++++++++++++++++++++++++
	/*
	window_bmp_p[1] = 0x0000aaff;
	window_bmp_p[2] = 0x0000aaff;
	window_bmp_p[3] = 0x0000aaff;
	*/

	
    BitBlt(hdc, 0, 0, screenw, screenh, hdc_comp, 0, 0, SRCCOPY);
	EndPaint(hwnd, &ps);

	RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}