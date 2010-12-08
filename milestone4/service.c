/*
 * service.c
 *
 * This file will implement support for OS service calling. According to
 * requirements, we must support Basic Atari System Services (BASS) as 
 * well as Graphical Atari System Services (GASS).
 */

#include "shared.h"
#include "rtos.h"
#include "globals.h"

/*
 * void SupportBASS (void);
 *
 * This function implements service call support for the basic
 * services. It will mark whether a reschedule of a new task is
 * necessary in terms of supporting the request.
 */

void
SupportBASS (void)
{
	PDB *p;
	unsigned long *ptrUSP;
	int fSchedule;

	fSchedule = FALSE;	/* no forcible schedule */

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
			pdb_Current->RegD0 = keyboard_date[keyboard_tail];
			++keyboard_tail
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

	/*
	 * TODO:
	 *
	 * future services will be implemented in this switch statement
	 */

	default:
		pdb_Current->RegD0 = ERROR;
		break;
	}	/* end switch */

	/*
	 * if required, schedule a new task to run
	 */

	if (fSchedule)
		RoundRobinScheduler();

	/*
	 * and that's it!
	 */

}	/* end SupportBASS */


