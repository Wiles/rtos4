/*!
 * \file main.cpp
 * \author Hekar Khani, Samuel Lewis, Adrian Hyde, Dan Evans
 * \date December 14, 2010
 * \description
 *	Test application for RTOS Milestone 4. This application
 *  allows us to simulate the theoretical functions
 *  that Team #1 was designated with. Not all the functionality
 *  is in this Windows application. We saw that it was not a 
 *  wise idea to do that. Those functions are in the 
 *  Visual 68k simulation based project.
 */

/*! \mainpage My Personal Index Page
 *
 * \section RTOS4 "RTOS Four"
 * \subsection RTOS4Milestone "RTOS Four Milestone"
 *	Default simulation under Visual 68k
 *
 * \subsection RTOS4Test "RTOS Four Windows Test Application"
 *	Test application for RTOS Milestone 4. This application
 *  allows us to simulate the theoretical functions
 *  that Team #1 was designated with. Not all the functionality
 *  is in this Windows application. We saw that it was not a 
 *  wise idea to do that. Those functions are in the 
 *  Visual 68k simulation based project.
 *
 *	Samuel Lewis, Dan Evans, Adrian Hyde, Hekar Khani
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include "global_const.h"
#include "draw.h"
#include "../RTOS4/globals.h"
#include "../RTOS4/rtos.h"

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
		// Initialize the RT OS
		InitOS ();

		pData = (RTOSTESTDATA *)malloc (sizeof (RTOSTESTDATA));
		if (pData == NULL)
			return -1;

		SetWindowLong (hwnd, GWL_USERDATA, (LONG)pData);

		// Enable the serial debug output timer
		SetTimer (hwnd, IDT_INTERRUPT_DEBUG_OUT, 100, NULL);
		// Enable the interrupt timer
		SetTimer (hwnd, IDT_INTERRUPT_7, 1000, NULL);

		// Keyboard buffer is our default view
		pData->CurrentView = VIEW_KEYBOARD_BUFFER;

		// Create our radio buttons for changing window panes
		CreateWindow ("BUTTON", KEYBOARD_IN, WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 
			0, 0, VIEW_BUTTON_SIZE, 24, hwnd, (HMENU)IDC_VIEW_KEYBOARD_BUFFER, hInst, NULL);
		CreateWindow ("BUTTON", SERIAL_IN, WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 
			VIEW_BUTTON_SIZE, 0, VIEW_BUTTON_SIZE, 24, hwnd, (HMENU)IDC_VIEW_SERIAL_IN_BUFFER, hInst, NULL);
		CreateWindow ("BUTTON", SERIAL_OUT, WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 
			VIEW_BUTTON_SIZE * 2, 0, VIEW_BUTTON_SIZE, 24, hwnd, (HMENU)IDC_VIEW_SERIAL_OUT_BUFFER, hInst, NULL);
		CreateWindow ("BUTTON", OTHER, WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 
			VIEW_BUTTON_SIZE * 3, 0, VIEW_BUTTON_SIZE, 24, hwnd, (HMENU)IDC_VIEW_OTHER, hInst, NULL);

		// Keyboard buffer is our default view
		CheckDlgButton (hwnd, IDC_VIEW_KEYBOARD_BUFFER, TRUE);

		return 0;

	case WM_PAINT:
	{
		pData = (RTOSTESTDATA *)GetWindowLong (hwnd, GWL_USERDATA);
		if (pData == NULL)
			return -1;

		GetClientRect (hwnd, &bounds);

		hdc = BeginPaint (hwnd, &ps);
		
		// Draw each view differently depending on
		// what view state we're in
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
			// Display the tickcount on view other
			char buffer[512];
			sprintf (buffer, "TickCount: %u", GetSystemTickCount());
			ExtTextOut (hdc, 0, 40, 0, NULL, buffer, strlen (buffer), NULL);
			break;
		}
		}

		// Write out the information of each PDB
		// This happens in every view
		int y = 400;
		char buffer[512];
		PDB *pdb = pdb_First;
		int i = 2;
		while (i-- > 0)
		{
			sprintf (buffer, "PDB Name: %s Status: %c Reason %d", pdb->ApplicationName, 
				pdb->Status, pdb->Reason);
			ExtTextOut (hdc, 0, y, 0, NULL, buffer, strlen (buffer), NULL);
			y += 24;
			pdb = pdb->NextPDB;
		}

		EndPaint (hwnd, &ps);
		return 0;
	}
	case WM_COMMAND:
		pData = (RTOSTESTDATA *)GetWindowLong (hwnd, GWL_USERDATA);
		if (pData == NULL)
			return -1;

		// Handle radio button clicks and change
		// view panes accordingly
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
		
		// SetFocus to the window (not the radio buttons)
		// and redraw everything
		SetFocus (hwnd);
		InvalidateRect (hwnd, NULL, TRUE);

		return 0;

	case WM_TIMER:
		pData = (RTOSTESTDATA *)GetWindowLong (hwnd, GWL_USERDATA);
		if (pData == NULL)
			return -1;

		// Handle our timers
		switch (wParam)
		{
		case IDT_INTERRUPT_DEBUG_OUT:
			// Fire off the DebugOutputInterrupt
			DebugOutputInterrupt ();
			break;
		case IDT_INTERRUPT_7:
			// Redraw the screen and execute the Interrupt 7 handler
			// (RoundRobinScheduler)
			InvalidateRect (hwnd, NULL, TRUE);

			gTickCount++;
			RoundRobinScheduler ();
			break;
		}
		break;
	
	case WM_KEYDOWN:
		pData = (RTOSTESTDATA *)GetWindowLong (hwnd, GWL_USERDATA);
		if (pData == NULL)
			return -1;

		// Handle keydowns on a per window pane basis
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
			OutputDebugCharacter (wParam);
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
		// Cleanup our timers
		KillTimer (hwnd, IDT_INTERRUPT_DEBUG_OUT);
		KillTimer (hwnd, IDT_INTERRUPT_7);
		PostQuitMessage (0);
		return 0;
	}

	return DefWindowProc (hwnd, message, wParam, lParam);
}
