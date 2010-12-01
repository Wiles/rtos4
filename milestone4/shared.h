/*
 * shared.h
 *
 * The following are shared declarations for both RTOS and user level tasks.
 *
 * First are official RTOS service numbers. This
 * file is public and will be shared between user level (standard
 * library service wrappers) and the kernel level (service implementation)
 *
 * This also defines the TASK structure that is shared between the
 * task developer (to initialize necessary information for the RTOS
 * kernel to create a PDB, etc.) and the RTOS which needs that information
 * to build the PDB list, etc.
 */


#ifndef __SHARED_H__


#define BASS_RELINQUISH				1
#define BASS_SLEEP				2



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

