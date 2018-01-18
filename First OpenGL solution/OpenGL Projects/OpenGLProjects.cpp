// OpenGLProjects.cpp : Defines the entry point for the console application.
//

#define WIN32_LEAN_AND_MEAN
#pragma comment(linker, "/SUBSYSTEM:CONSOLE")
#include "stdafx.h"
#include "windows.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintStruct;
	/*				Device Context													*/
	HDC hDC;
	/*				Text for display												*/
	LPCWSTR string = TEXT("Hello World!");
	/*				Switch message condition that is met will execute				*/			
	switch (message)
	{
	case WM_CREATE:
		return 0;
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
		break;
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &paintStruct);
		/*		Set text colour to blue				*/
		SetTextColor(hDC, COLORREF(0x00FF0000));
		/*		Display text in middle of window	*/
		TextOut(hDC, 150, 150, string, sizeof(string) - 1);
		EndPaint(hwnd, &paintStruct);
		return 0;
		break;
	}

	return (DefWindowProc(hwnd, message, wParam, lParam));
}
int APIENTRY WinMain(HINSTANCE	hInstance,
				  HINSTANCE		hprevInstance,
				  LPSTR			lpCmdLine,
				  int			nCmdShow)
{

	WNDCLASSEX	windowClass;		//window class
	HWND		hwnd;				//window handle
	MSG			msg;				//message
	bool		done;				//flag saying when app is complete
	LPCWSTR		className = TEXT("MyClass"); 
	LPCWSTR		windowTitle = TEXT("A Real Win App");


	/*					Fill out the window class structure					*/
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = className;
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	/*					Register window class								*/
	if (!RegisterClassEx(&windowClass))
	{
		return 0;
	}
	/*					Class registered, so now create window				*/
	hwnd = CreateWindowEx(NULL,
						  className,
						  windowTitle,
						  WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_SYSMENU,
						  100, 100,
						  400, 400,
						  NULL,
						  NULL,
						  hInstance,
						  NULL);
	/*					Check if window creation failed						*/
	if (!hwnd)
		return 0;

	done = false;
	while (!done)
	{
		PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


    return 0;
}

