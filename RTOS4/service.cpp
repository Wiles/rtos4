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

#include "rtos.h"
#include "globals.h"
#include "stdlib.h"

void SupportBASS (void);

/*!
 * \brief Robin round scheduler
 * \remark
 * This scheduler also checks for input
 * blocking and executes input functions
 * when required.
 */
void RoundRobinScheduler(void)
{
	PDB *pdb = pdb_Current;
	int scheduling = TRUE;

	while (scheduling)
	{
		pdb = pdb->NextPDB;
		if (pdb->Status == BLOCKED)
		{
			pdb_Current = pdb;
			switch (pdb->Reason)
			{
			case REASON_KEYBOARD:
				InputKeyboardCharacter();
				scheduling = FALSE;
				break;
			case REASON_DEBUG_IN:
				InputDebugCharacter();
				scheduling = FALSE;
				break;
			}
		}
		else
		{
			scheduling = FALSE;
		}
		
		pdb_Current = pdb;
	}
}

/*!
 * \brief Fired on debugging input
 * \remark
 * This is the interrupt for handling
 * debugging input from a serial device.
 */
void DebugOutputInterrupt(void)
{

}

short InputKeyboardCharacter(void)
{
	pdb_Current->RegD0 = BASS_GET_KEYBOARD;

	SupportBASS();

	return (short)pdb_Current->RegD0;
}

int IsKeyboardCharacterAvailable(void)
{
	pdb_Current->RegD0 = BASS_KEYBOARD_STATUS;

	SupportBASS();

	return (int)pdb_Current->RegD0;
}

short InputDebugCharacter(void)
{
	pdb_Current->RegD0 = BASS_GET_DEBUG;

	SupportBASS();

	return (short)pdb_Current->RegD0;
}

int IsDebugCharacterAvailable(void)
{
	pdb_Current->RegD0 = BASS_DEBUG_IN_STATUS;

	SupportBASS();

	return (int)pdb_Current->RegD0;
}

void OutputDebugCharacter (short character)
{
	//TODO: void OutputDebugCharacter (short character)
}

int IsDebugPortBusy(void)
{
	pdb_Current->RegD0 = BASS_DEBUG_BUSY;

	SupportBASS();

	return (int)pdb_Current->RegD0;
}

unsigned long GetSystemTickCount(void)
{
	pdb_Current->RegD0 = BASS_TICK_COUNT;

	SupportBASS();

	return pdb_Current->RegD0;
}

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
	unsigned long *ptrUSP;
	int fSchedule;

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
	{
		if (keyboard_head <= keyboard_tail)
		{
			if ((keyboard_head + 1) > keyboard_tail)
			{
				// Block user until key is avaliable
				pdb_Current->Status = BLOCKED;
				pdb_Current->Reason = REASON_KEYBOARD;
				break;
			}
		}

		pdb_Current->Status = READY;
		pdb_Current->Reason = 0;

		short key = keyboard_data[keyboard_head];
		keyboard_data[keyboard_head] = '\0';

		keyboard_head++;

		pdb_Current->RegD0 = key;
		break;
	}
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
	{
		if (serial_in_head <= serial_in_tail)
		{
			if ((serial_in_head + 1) > serial_in_tail)
			{
				// Block user until key is avaliable
				pdb_Current->Status = BLOCKED;
				pdb_Current->Reason = REASON_DEBUG_IN;
				break;
			}
		}

		pdb_Current->Status = READY;
		pdb_Current->Reason = 0;

		short key = serial_in_data[serial_in_head];
		serial_in_data[serial_in_head] = '\0';

		serial_in_head++;

		break;
	}
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
		//TODO: BASS_WRITE_DEBUG
		break;
	case BASS_DEBUG_BUSY:
		//TODO: BASS_DEBUG_BUSY
		break;
	case BASS_TICK_COUNT:
		pdb_Current->RegD0 = gTickCount;
		break;
	case BASS_GLOBAL_ADDRESS:
		pdb_Current->RegD0 = (unsigned long)*pdb_Current->PointerToGlobalSpace;
		break;
	default:
		pdb_Current->RegD0 = ERROR;
		break;
	}	/* end switch */

	/*
	 * if required, schedule a new task to run
	 */

	if (fSchedule)
	{
		RoundRobinScheduler();
	}

}	/* end SupportBASS */


