/*!
 * \file global_const.h
 * \author Hekar Khani, Tom Kempton
 * \date December 8, 2010
 * \description Constants and definitions for the WP_Project Application
 */

#ifndef GLOBAL_CONST_H
#define GLOBAL_CONST_H

extern const TCHAR *SureExit;

// Colors

#define RED RGB (255, 0, 0)
#define GREEN RGB (0, 255, 0)
#define BLUE RGB (0, 0, 255)
#define GREY RGB (192, 192, 192)
#define BLACK RGB (0, 0, 0)

/*!
 * Width of radio buttons at the
 * top of the window
 */
#define VIEW_BUTTON_SIZE 120

#define KEYBOARD_IN "Keyboard"
#define SERIAL_IN "SerialIn"
#define SERIAL_OUT "SerialOut"
#define OTHER "Other"


/*!
 * Identifiers for control commands
 */
enum WmCommandIdentifers
{
	/*!
	 * Identifier for selecting the keyboard 
	 * as the current view.
	 */
	IDC_VIEW_KEYBOARD_BUFFER = 100,

	/*!
	 * Command to display serial buffer by
	 * changing the current view.
	 */
	IDC_VIEW_SERIAL_IN_BUFFER,

	/*!
	 * Command to display the output
	 * serial buffer by changing 
	 * the current view.
	 */
	IDC_VIEW_SERIAL_OUT_BUFFER,

	/*!
	 * Other output pane. Shows status
	 * informations.
	 */
	IDC_VIEW_OTHER
};

/*!
 * Current view pane in the application
 */
enum Views
{
	/*!
	 * Keyboard buffer view pane
	 */
	VIEW_KEYBOARD_BUFFER = 0,
	
	/*!
	 * Serial input buffer view pane
	 */
	VIEW_SERIAL_IN_BUFFER,
	
	/*!
	 * Serial output buffer view pane
	 */
	VIEW_SERIAL_OUT_BUFFER,

	/*!
	 * View pane for other misc. items
	 */
	VIEW_OTHER
};


/*!
 * Identifiers for timers
 */
enum WmTimers
{
	/*!
	 * Interrupt 7 timer
	 */
	IDT_INTERRUPT_7 = 101,

	/*!
	 * Timer for firing 
	 */
	IDT_INTERRUPT_DEBUG_OUT
};

/*!
 * 
 */
typedef struct RTOSTESTDATA
{
	/*!
	 * 
	 */
	int CurrentView;
} RTOSTESTDATA;

#endif // GLOBAL_CONST_H
