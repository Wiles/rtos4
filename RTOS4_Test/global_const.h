/*!
 * \file global_const.h
 * \author Hekar Khani, Tom Kempton
 * \date December 8, 2010
 * \description Constants and definitions for the WP_Project Application
 */

#ifndef GLOBAL_CONST_H
#define GLOBAL_CONST_H

extern const TCHAR *SureExit;

#define RED RGB (255, 0, 0)
#define GREEN RGB (0, 255, 0)
#define BLUE RGB (0, 0, 255)
#define GREY RGB (192, 192, 192)
#define BLACK RGB (0, 0, 0)

#define VIEW_BUTTON_SIZE 120

#define KEYBOARD_IN "Keyboard"
#define SERIAL_IN "SerialIn"
#define SERIAL_OUT "SerialOut"

enum WmCommandIdentifers
{
	/*!
	 * Identifier for selecting the keyboard 
	 * as the current view.
	 */
	IDC_VIEW_KEYBOARD_BUFFER = 100,

	/*!
	 * 
	 */
	IDC_VIEW_SERIAL_IN_BUFFER,

	/*!
	 * 
	 */
	IDC_VIEW_SERIAL_OUT_BUFFER
};

enum Views
{
	/*!
	 *
	 */
	VIEW_KEYBOARD_BUFFER = 0,

	VIEW_SERIAL_IN_BUFFER,

	VIEW_SERIAL_OUT_BUFFER
};

typedef struct RTOSTESTDATA
{
	/*!
	 *
	 */
	int CurrentView;
} RTOSTESTDATA;

#endif // GLOBAL_CONST_H
