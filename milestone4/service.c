/*!
 * \file service.c
 *	\author Samuel Lewis, Adrian Hyde, Dan Evans, Hekar Khani
 * \brief
 * This file will implement support for OS service calling. According to
 * requirements, we must support Basic Atari System Services (BASS) as 
 * well as Graphical Atari System Services (GASS).
 * \remark
 * As of now this file does the tasks defined for group 1 of the RTOS project. 
 * These include: 
 * 
 */

#include "shared.h"
#include "rtos.h"
#include "globals.h"

 /*!
  * \brief Service call handler for RTOS
  * \remark
  * This function implements service call support for the basic
  * services. It will mark whether a reschedule of a new task is
  * necessary in terms of supporting the request.
  */
void SupportBASS (void)
{
	/* Initialize our variables */
	PDB *p;
	unsigned long *ptrUSP;
	int fSchedule;
	int hr;
	int min;
	int sec;
	struct systemtime *pTime;


	/* force re-scheduling */
	fSchedule = FALSE;

	/*
	 * since service params on user stack,
	 * obtain a pointer to the data on the stack, which will
	 * be one long integer higher than current USP value,
	 * as there's a return address for the standard library
	 * support wrapper function call. To keep the interface
	 * trivial, we'll assume that all service calls supply
	 * 32 bit values to the OS.
	 */

	ptrUSP = (unsigned long *)(pdb_Current->RegSP + sizeof (long));

	switch (pdb_Current->RegD0) {
	case BASS_RELINQUISH:
		fSchedule = TRUE;
		break;

	case BASS_SLEEP:
		pdb_Current->SleepDuration = ptrUSP[0];
		pdb_Current->Status = BLOCKED;
		pdb_Current->Reason = REASON_SLEEP;
		fSchedule = TRUE;
		break;
	case BASS_GET_KEYBOARD:
		if( keyboard_head != keyboard_tail)
		{
			pdb_Current->RegD0 = keyboard_data[keyboard_tail];
			++keyboard_tail;
		}
		else
		{
			pdb_Current->Status = BLOCKED;
			pdb_Current->Reason = REASON_KEYBOARD;
			fSchedule = TRUE;
		}
		break;
	case BASS_KEYBOARD_STATUS:
		if( keyboard_head != keyboard_tail )
		{
			pdb_Current->RegD0 = TRUE;
		}
		else
		{
			pdb_Current->RegD0 = FALSE;
		}
		break;
	case BASS_GET_DEBUG:
		if( serial_in_head != serial_in_tail )
		{
			pdb_Current->RegD0 = serial_in_data[serial_in_tail];
			++serial_in_tail;
		}
		else
		{
			pdb_Current->Status = BLOCKED;
			pdb_Current->Reason = REASON_DEBUG_IN;
			fSchedule = TRUE;
		}
		break;
	case BASS_DEBUG_IN_STATUS:
		if( serial_in_head != serial_in_tail )
		{
			pdb_Current->RegD0 = TRUE;
		}
		else
		{
			pdb_Current->RegD0 = FALSE;
		}
		break;
	case BASS_WRITE_DEBUG:
		break;
	case BASS_DEBUG_BUSY:
		break;
	case BASS_TICK_COUNT:
		pdb_Current->RegD0 = gTickCount;
		break;
	case BASS_GLOBAL_ADDRESS:
		pdb_Current->RegD0 = pdb_Current->PointerToGlobalSpace;
		break;
	case BASS_GETCLOCKTIME:
		/* grab the service parameters from the stack */
		pTime = (struct systemtime *) ptrUSP[0];
		/* TODO: FIX DIVISION FOR THE TWO OPERATIONS BELOW */
		/* we will use gTickCount/3 to mimic the actual hour */
		/*	pTime->hour = gTickCount/3; */
		/* we will use gTickCount/2 to mimic the actual minute */
		/* pTime->minute = gTickCount/2; */
		/* we will use gTickCount to mimic the actual second */
		pTime->second = gTickCount;
		break;
	default:
		pdb_Current->RegD0 = ERROR;
		break;
	}	/* end switch */

	/*
	 * if required, schedule a new task to run
	 */

	if (fSchedule)
		RoundRobinScheduler();

}	/* end SupportBASS */


