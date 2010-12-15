/*!
 * \file shared.h
 *	\author Ig Kolenko, Samuel Lewis, Adrian Hyde, Dan Evans, Hekar Khani
 *
 * \brief
 * The following are shared declarations for both RTOS and user level tasks.
 * \remark
 * First are official RTOS service numbers. This
 * file is public and will be shared between user level (standard
 * library service wrappers) and the kernel level (service implementation)
 *
 * This also defines the TASK structure that is shared between the
 * task developer (to initialize necessary information for the RTOS
 * kernel to create a PDB, etc.) and the RTOS which needs that information
 * to build the PDB list, etc.
 * 
 */
 
#ifndef __SHARED_H__

/*!
 * \brief Relenquish cpu to another task
 */
#define BASS_RELINQUISH			1
/*!
 * \brief Sleep for provided number of seconds
 */
#define BASS_SLEEP				2
/*!
 * \brief get a keyboard character
 */
#define BASS_GET_KEYBOARD		3
/*!
 * \brief Is there available information in keyboard buffer
 */
#define BASS_KEYBOARD_STATUS	4
/*!
 * \brief get a debug character
 */
#define BASS_GET_DEBUG			5
/*!
 * \brief Is there available information in debug buffer
 */
#define BASS_DEBUG_IN_STATUS	6
/*!
 * \brief write provided character to debug port
 * D1 - Character to write
 */
#define BASS_WRITE_DEBUG		7
/*!
 * \brief is the debug port busy
 */
#define BASS_DEBUG_BUSY			8
/*!
 * \brief retreive system tick count
 */
#define BASS_TICK_COUNT			9
/*!
 * \brief retrieve task global memory address
 */
#define BASS_GLOBAL_ADDRESS		10
/*!
 * \brief get tick count formated into time
 * A1 - Time struct
 */
#define BASS_GETCLOCKTIME 		11



#define NULL					0L
#define TRUE					1
#define FALSE					0



#define MAX_APPNAME_LENGTH		32

typedef struct tagTASK {
	struct tagTASK *NextTask;
	char ApplicationName[MAX_APPNAME_LENGTH];
	unsigned long AmountOfGlobalSpace;
	unsigned long AmountOfStackSpace;
	void *PointerToCode;
} TASK;


#define __SHARED_H__
#endif

