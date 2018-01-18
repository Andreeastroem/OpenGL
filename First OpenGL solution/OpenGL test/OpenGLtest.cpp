// OpenGLProjects.cpp : Defines the entry point for the console application.
//

#define WIN32_LEAN_AND_MEAN
#pragma comment(linker, "/SUBSYSTEM:WINDOWS")
#include "stdafx.h"
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
//#include <GL/glew.h>


float angle = 0.0f;
bool fullscreen = false;

void drawCube(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glBegin(GL_POLYGON);

		/*      This is the top face*/
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, 0.0f, 0.0f);

		/*      This is the front face*/
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(0.0f, -1.0f, 0.0f);

		/*      This is the right face*/
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -1.0f, 0.0f);
		glVertex3f(0.0f, -1.0f, -1.0f);
		glVertex3f(0.0f, 0.0f, -1.0f);

		/*      This is the left face*/
		glVertex3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);

		/*      This is the bottom face*/
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);

		/*      This is the back face*/
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(0.0f, -1.0f, -1.0f);

	glEnd();
	glPopMatrix();
}

void Render(HDC hDC)
{
	/*		Enable depth testing									*/
	glEnable(GL_DEPTH_TEST);
	
	/*		Clear background colour									*/
	/*		Clear colour and depth buffers							*/
	/*		Resets modelview matrix									*/
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	angle = (int)(angle + 1.0f) % 360;

	glPushMatrix();
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -30.0f);
		glRotatef(angle, 0.0f, 1.0f, 1.0f);
		drawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();

	glFlush();
	/*		Bring back buffer to foreground							*/
	SwapBuffers(hDC);
}

void SetupPixelFormat(HDC hDC)
{
	/*		Pixel format index										*/
	int nPixelFormat;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),			//size of structure
		1,										//default version
		PFD_DRAW_TO_WINDOW,						//window drawing support
		PFD_SUPPORT_OPENGL,						//opengl support
		PFD_DOUBLEBUFFER,						//double buffering support
		PFD_TYPE_RGBA,							//rgba colour mode
		32,										//32 bit colour mode
		0, 0, 0, 0, 0, 0,						//ignore colour mode
		0,										//no alpha buffer
		0,										//ignore shift bit
		0,										//no accumulation buffer
		0, 0, 0, 0,								//ignore accumulation bits
		16,										//16 bit z-buffer size
		0,										//no stencil buffer
		0,										//no aux buffer
		PFD_MAIN_PLANE,							//main drawing plane
		0,										//reserved
		0};										//layer masks ignored
	
	nPixelFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, nPixelFormat, &pfd);
}

//
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	/*		RENDERING CONTEXT										*/
	static HGLRC hRC;
	PAINTSTRUCT paintStruct;
	/*		DEVICE CONTEXT											*/
	static HDC hDC;
	/*		SWITCH MESSAGE, CONDITION THAT IS MET WILL EXECUTE		*/		

	int width, height;

	switch (message)
	{
	case WM_CREATE:
		hDC = GetDC(hwnd);				//get the device context for window
		SetupPixelFormat(hDC);
		hRC = wglCreateContext(hDC);	//create rendering context
		wglMakeCurrent(hDC, hRC);		//make rendering context current
		return 0;
		break;
	case WM_CLOSE:
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);
		PostQuitMessage(0);
		return 0;
		break;
	case WM_SIZE:
		height = HIWORD(lParam);
		width = LOWORD(lParam);

		if (height == 0)
			height = 1;

		glViewport(0, 0, width, height);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(54.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

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
	DWORD		dwExStyle;			//window extended style
	DWORD		dwStyle;			//window style
	RECT		windowRect;
	
	LPCWSTR		className = TEXT("MyClass"); 
	LPCWSTR		windowTitle = TEXT("A Real Win App");

	int width	=	800;
	int height	=	600;
	int bits	=	32;

	windowRect.left		= (long)0;
	windowRect.right	= (long)width;
	windowRect.top		= (long) 0;
	windowRect.bottom	= (long)height;



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

	/*					Check if fullscreen is on							*/
	if (fullscreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = width;					//screen width
		dmScreenSettings.dmPelsHeight = height;					//screen height
		dmScreenSettings.dmBitsPerPel = bits;					//bits per pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN != DISP_CHANGE_SUCCESSFUL))
		{
			MessageBox(NULL, (LPCWSTR)"Display mode failed", NULL, MB_OK);
			fullscreen = false;
		}
	}
	if (fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;						//window extended style
		dwStyle = WS_POPUP;									//windows style
		ShowCursor(FALSE);									//hide mouse point
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;		//window extended style
		dwStyle = WS_OVERLAPPEDWINDOW;						//windows style
	}

	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

	/*					Class registered, so now create window				*/
	hwnd = CreateWindowEx(NULL,
						  className,
						  windowTitle,
						  dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
						  0, 0,
						  windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
						  NULL,
						  NULL,
						  hInstance,
						  NULL);
	/*					Check if window creation failed						*/
	if (!hwnd)
		return 0;

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	done = false;
	while (!done)
	{
		PeekMessage(&msg, hwnd, NULL, NULL, PM_REMOVE);
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

	if (fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}


    return msg.wParam;
}

