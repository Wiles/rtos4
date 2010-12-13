/*!
 * \file main.cpp
 * \author Hekar Khani, Tom Kempton
 * \date December 8, 2010
 * \description
 *	Test application for MusicBox child window.
 *	This features 2 MusicBox controls and set of
 *	buttons to manipulate their features and test
 *	them out.
 */

#ifndef UNDER_CE
#include <tchar.h>
#endif
#include <windows.h>
//#include "global_const.h

#pragma warning ( disable : 4996 )

/*!
 * Windows Application instance
 */
static HINSTANCE hInst;

/*!
 * Windows Application Name for identification
 */
static const TCHAR szAppName[] = _T("MBTestApp");

/*!
 * Title of the main window
 */
static const TCHAR szTitle[] = _T("MusicBox Test Application");

/*!
 * Title of the MusicBox Window
 */
static TCHAR MusicBoxTitle[] = _T("MusicBox");

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);



/*!
 * This is the entry point for all Windows programs. It is informed
 * of the current instance handle, the previous instance handle, the
 * current commandline, and the show flag for how the window is to be
 * displayed.
 *
 * \param HINSTANCE hInstance - Current instance of application
 * \param HINSTANCE hPrevInstance - Previous instance of application
 * \param LPSTR lpszCmdParam - Command line arguments
 * \param int nCmdShow - Window state to show
 *
 * \return
 *	Operating system return code
 */
#ifdef UNDER_CE
int CALLBACK WinMain (HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, LPTSTR lpszCmdParam, int nCmdShow)
#else
int CALLBACK WinMain (HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
#endif
{
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	long style;

#ifdef UNDER_CE
	// Find this window and bring it to the foreground
	// Hack to make the window show up on Windows CE
	if ((hwnd = FindWindow (szAppName, NULL)) != NULL) 
	{
		SetForegroundWindow ((HWND)((ULONG) hwnd | 0x01));
		return 0;
	}
#endif

	// proceed with WNDCLASS registration
	if (!hPrevInstance) 
	{
		wndclass.style         = CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc   = WndProc;
		wndclass.cbClsExtra    = 0;
		wndclass.cbWndExtra    = 0;
		wndclass.hInstance     = hInstance;
		wndclass.hIcon         = LoadIcon (NULL, NULL);
		wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);
		wndclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
		wndclass.lpszMenuName  = NULL;
		wndclass.lpszClassName = szAppName;
		RegisterClass (&wndclass);
	}

	hInst = hInstance;

#ifdef UNDER_CE
	// Different styling under Windows CE
	style = WS_BORDER;
#else
	style = WS_OVERLAPPEDWINDOW;
#endif
	// Create our main window
	hwnd = CreateWindow (szAppName, szTitle, style, 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
		NULL, NULL, hInstance, NULL);

	// Show our window
	ShowWindow (hwnd, nCmdShow);
	UpdateWindow (hwnd);

	while (GetMessage (&msg, NULL, 0, 0)) 
	{
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}

	return msg.wParam;
}


/*!
 *
 * \brief
 * This is the Window Procedure for the main window of this application.
 * It processes all messages destined for this main window.
 *
 * \param HWND hwnd - Handle to window
 * \param UINT message - Message identifier
 * \param WPARAM wParam - wParam
 * \param LPARAM lParam - lParam
 */
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, 
	WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		return 0;

	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps);
		EndPaint (hwnd, &ps);
		return 0;

	case WM_COMMAND:
		return 0;

	case WM_CLOSE:
		// Ask the user if they wish to exit
		if (MessageBox (hwnd, _T("Are you sure you wish to quit?"),
                        szTitle, MB_ICONSTOP | MB_YESNO) == IDYES) 
		{
			DestroyWindow (hwnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage (0);
		return 0;
	}

	return DefWindowProc (hwnd, message, wParam, lParam);
}
