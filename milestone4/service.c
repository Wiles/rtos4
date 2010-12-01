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


