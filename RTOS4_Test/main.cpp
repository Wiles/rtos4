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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include "global_const.h"
#include "draw.h"
#include "../RTOS4/globals.h"

#pragma warning ( disable : 4996 )

/*!
 * Windows Application instance
 */
static HINSTANCE hInst;

/*!
 * Windows Application Name for identification
 */
static const char szAppName[] = "RTOS4App";

/*!
 * Title of the main window
 */
static const char szTitle[] = "RTOS4 Test Application";


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
int CALLBACK WinMain (HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	long style;

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
	RECT bounds;
	HDC hdc;
	RTOSTESTDATA *pData;

	switch (message)
	{
	case WM_CREATE:
		InitOS ();

		pData = (RTOSTESTDATA *)malloc (sizeof (RTOSTESTDATA));
		if (pData == NULL)
			return -1;

		SetWindowLong (hwnd, GWL_USERDATA, (LONG)pData);

		// Enable the interrupt timer
		SetTimer (hwnd, IDT_INTERRUPT_7, 1000, NULL);

		pData->CurrentView = VIEW_KEYBOARD_BUFFER;

		CreateWindow ("BUTTON", KEYBOARD_IN, WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 
			0, 0, VIEW_BUTTON_SIZE, 24, hwnd, (HMENU)IDC_VIEW_KEYBOARD_BUFFER, hInst, NULL);
		CreateWindow ("BUTTON", SERIAL_IN, WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 
			VIEW_BUTTON_SIZE, 0, VIEW_BUTTON_SIZE, 24, hwnd, (HMENU)IDC_VIEW_SERIAL_IN_BUFFER, hInst, NULL);
		CreateWindow ("BUTTON", SERIAL_OUT, WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 
			VIEW_BUTTON_SIZE * 2, 0, VIEW_BUTTON_SIZE, 24, hwnd, (HMENU)IDC_VIEW_SERIAL_OUT_BUFFER, hInst, NULL);
		CreateWindow ("BUTTON", OTHER, WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 
			VIEW_BUTTON_SIZE * 3, 0, VIEW_BUTTON_SIZE, 24, hwnd, (HMENU)IDC_VIEW_OTHER, hInst, NULL);

		CheckDlgButton (hwnd, IDC_VIEW_KEYBOARD_BUFFER, TRUE);

		return 0;

	case WM_PAINT:
		pData = (RTOSTESTDATA *)GetWindowLong (hwnd, GWL_USERDATA);
		if (pData == NULL)
			return -1;

		GetClientRect (hwnd, &bounds);

		hdc = BeginPaint (hwnd, &ps);
		switch (pData->CurrentView)
		{
		case VIEW_KEYBOARD_BUFFER:
			DrawCircularBuffer <short, unsigned char> 
				(hwnd, hdc, keyboard_data, keyboard_head, keyboard_tail, ARRAYSIZE(keyboard_data), 0, 32, 32, 32);
			break;
		case VIEW_SERIAL_IN_BUFFER:
			DrawCircularBuffer <short, unsigned char> 
				(hwnd, hdc, serial_in_data, serial_in_head, serial_in_tail, ARRAYSIZE(serial_in_data), 0, 32, 32, 32);
			break;
		case VIEW_SERIAL_OUT_BUFFER:
			DrawCircularBuffer <short, unsigned char> 
				(hwnd, hdc, serial_out_data, serial_out_head, serial_out_tail, ARRAYSIZE(serial_out_data), 0, 32, 32, 32);
			break;
		case VIEW_OTHER:
		{
			char buffer[512];
			sprintf (buffer, "TickCount: %u", GetSystemTickCount());
			ExtTextOut (hdc, 0, 40, 0, NULL, buffer, strlen (buffer), NULL);
			break;
		}
		}
		EndPaint (hwnd, &ps);
		return 0;
	
	case WM_COMMAND:
		pData = (RTOSTESTDATA *)GetWindowLong (hwnd, GWL_USERDATA);
		if (pData == NULL)
			return -1;

		switch (wParam)
		{
		case IDC_VIEW_KEYBOARD_BUFFER:
			pData->CurrentView = VIEW_KEYBOARD_BUFFER;
			break;
		case IDC_VIEW_SERIAL_IN_BUFFER:
			pData->CurrentView = VIEW_SERIAL_IN_BUFFER;
			break;
		case IDC_VIEW_SERIAL_OUT_BUFFER:
			pData->CurrentView = VIEW_SERIAL_OUT_BUFFER;
			break;
		case IDC_VIEW_OTHER:
			pData->CurrentView = VIEW_OTHER;
			break;
		}
		
		SetFocus (hwnd);
		InvalidateRect (hwnd, NULL, TRUE);

		return 0;

	case WM_TIMER:
		pData = (RTOSTESTDATA *)GetWindowLong (hwnd, GWL_USERDATA);
		if (pData == NULL)
			return -1;

		if (pData->CurrentView == VIEW_OTHER)
		{
			InvalidateRect (hwnd, NULL, TRUE);
		}

		gTickCount++;
		break;
	
	case WM_KEYDOWN:
		pData = (RTOSTESTDATA *)GetWindowLong (hwnd, GWL_USERDATA);
		if (pData == NULL)
			return -1;

		switch (pData->CurrentView)
		{
		case VIEW_KEYBOARD_BUFFER:
			if (wParam == VK_DELETE)
			{
				InputKeyboardCharacter();
			}
			else
			{
				keyboard_data[keyboard_tail++] = wParam;
			}
			break;
		case VIEW_SERIAL_IN_BUFFER:
			if (wParam == VK_DELETE)
			{
				InputDebugCharacter();
			}
			else
			{
				serial_in_data[serial_in_tail++] = wParam;
			}
			break;
		case VIEW_SERIAL_OUT_BUFFER:
			if (wParam == VK_DELETE)
			{
			}
			else
			{
				serial_out_data[serial_out_tail++] = wParam;
			}
			break;
		case VIEW_OTHER:

			break;
		}

		InvalidateRect (hwnd, NULL, TRUE);
		return 0;

	case WM_CLOSE:
		// Ask the user if they wish to exit
		if (MessageBox (hwnd, SureExit,
                        szTitle, MB_ICONSTOP | MB_YESNO) == IDYES) 
		{
			DestroyWindow (hwnd);
		}
		return 0;

	case WM_DESTROY:
		KillTimer (hwnd, IDT_INTERRUPT_7);
		PostQuitMessage (0);
		return 0;
	}

	return DefWindowProc (hwnd, message, wParam, lParam);
}
