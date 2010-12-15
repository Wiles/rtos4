/*!
 * \file rtos.h
 *	\author Ig Kolenko, Samuel Lewis, Adrian Hyde, Dan Evans, Hekar Khani
 *
 * \brief
 * This file provides global declarations for the RTOS. This
 * is NOT meant to be shared with user level applications,
 * as the declarations are geared towards RTOS internal support
 *
 * \remark
 * Though many global variables are defined here, they may or may not
 *	be initialized here, so watch out!
 * 
 */

#ifndef __RTOS_H__

#include "shared.h"

#define READY			'R'
#define BLOCKED			'B'

#define REASON_NONE		0
#define REASON_SLEEP	1
#define REASON_KEYBOARD	2
#define REASON_DEBUG_IN	3

#define SUCCESS			0
#ifdef ERROR
#undef ERROR
#endif
#define ERROR			-1

#define MAX_PDBS		2


/*
 * the following defines the total amount of reserved global memory
 * space for application stacks. 
 */

#define TOTAL_STACK_MEMORY	8192

/*
 * addresses of where things start in address space
 */

#define RAM_START		0x00000000L
#define ROM_START		0x00FC0000L
#define VECTOR_START		0x00FC0000L
#define VECTOR_SIZE		0x400L

/*
 * PDB structure used internally by RTOS
 * as per definition in Design Document 2008
 */

typedef struct pdb {
	struct pdb *NextPDB;	/* next PDB in the linked list */

	unsigned long ApplicationID;
	char ApplicationName[MAX_APPNAME_LENGTH];
	unsigned long AmountOfGlobalSpace;	/* future use for App globals */
	unsigned char *PointerToGlobalSpace;
	unsigned long AmountOfStackSpace;
	char *PointerToStackSpace;	/* bottom of stack, A7 points to top */
	
	unsigned long RegD0;
	unsigned long RegD1;
	unsigned long RegD2;
	unsigned long RegD3;
	unsigned long RegD4;
	unsigned long RegD5;
	unsigned long RegD6;
	unsigned long RegD7;

	unsigned long RegA0;
	unsigned long RegA1;
	unsigned long RegA2;
	unsigned long RegA3;
	unsigned long RegA4;
	unsigned long RegA5;
	unsigned long RegA6;

	unsigned long RegSP;	/* user task stack pointer */
	unsigned long RegPC;
	unsigned short RegSR;	/* SR is only 16 bits wide */

	unsigned long Status;	/* status flag (ie: READY, BLOCKED) */
	unsigned long Reason;	/* reason flag */

	unsigned long SleepDuration;	/* for use by SLEEP service */

	/* future PDB members go here */

} PDB;


/*
 * common RTOS C level functions
 */

extern void rtos_memcopy (unsigned char *dest, unsigned char *src, int numBytes);
extern void RoundRobinScheduler (void);
extern char *rtos_strcpy (char *dest, char *src);
extern void InitOS (void);
extern int InitializePDB (int taskID, PDB *p, TASK *t, char *stack, unsigned long initVal);

void DebugOutputInterrupt(void);

/*!
 *
 */
typedef struct systemtime {
	 int hour;
	 int minute;
	 int second;
} RTOS_SYSTEMTIME;

#define __RTOS_H__
#endif
