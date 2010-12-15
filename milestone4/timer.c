/*!
 * \file timer.c
 *	\author Ig Kolenko, Samuel Lewis, Adrian Hyde, Dan Evans, Hekar Khani
 *
 * \brief
 * This file provides implementation support for timer interrupt
 * handler. It is assumed that the CPU context of the current task
 * is already saved, and will handle Sleep service support along with
 * pre-emptive context switching.
 *
 * \remark
 * Though many global variables are defined here, they may or may not
 *	be initialized here, so watch out!
 * 
 */

#include "rtos.h"
#include "globals.h"

/*
 * void TimerSupport (void);
 *
 * This function is called by the IPL handler for the timer
 * interrupt, and supports pre-emptive switching of tasks, as
 * well as waking up tasks from SLEEP state (apps are BLOCKED
 * as a result of requesting a SLEEP).
 */

void
TimerSupport (void)
{
	PDB *p;

	/*
	 * first, locate all sleeping tasks, and adjust sleep counter
	 * in an effort to wake up these tasks. We assume that the
	 * SleepDuration member of the PDB holds a count of how many
	 * timer interrupts should arrive before waking task up.
	 */

	p = pdb_First;
	do {
		if (p->Status == BLOCKED) {
			if (p->Reason == REASON_SLEEP) {
				p->SleepDuration--;
				if (p->SleepDuration == 0) {
					p->Status = READY;
					p->Reason = REASON_NONE;
				}	/* endif */
			}	/* endif */
		}	/* endif */

		p = p->NextPDB;
	} while (p != pdb_First);

	/*
	 * now, preemptively schedule next task
	 * using round robin scheduling
	 */

	RoundRobinScheduler();

	/*
	 * increment our count of timer "ticks" so that we have
	 * potential support for rudimentary timing (similar to
	 * the Windows "GetTickCount" concept)
	 */
	++gTickCount;

	/*
	 * and that's all folks!
	 */

}	/* end TimerSupport */

