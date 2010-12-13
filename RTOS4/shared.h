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
#define __SHARED_H__

/*!
 * Define if we're just testing on the x86 
 * with Visual Studio and Windows.
 */
#define X86_TEST

#define BASS_RELINQUISH			1
#define BASS_SLEEP				2
#define BASS_GET_KEYBOARD		3
#define BASS_KEYBOARD_STATUS	4
#define BASS_GET_DEBUG			5
#define BASS_DEBUG_IN_STATUS	6
#define BASS_WRITE_DEBUG		7
#define BASS_DEBUG_BUSY			8
#define BASS_TICK_COUNT			9
#define BASS_GLOBAL_ADDRESS		10
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


#endif /* __SHARED_H__ */