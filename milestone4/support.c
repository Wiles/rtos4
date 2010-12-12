/*!
 * \file support.c
 *	\author Ig Kolenko, Samuel Lewis, Adrian Hyde, Dan Evans, Hekar Khani
 *
 * \brief
 * Additional C based support routines for RTOS
 * \remark
 * 
 * 
 */
#include "rtos.h"
#include "globals.h"

/*
 * void BlockCopy (unsigned char *dest, unsigned char *src, int numBytes);
 *
 * This function can be used for OS required block copies
 */

void
rtos_memcopy (unsigned char *dest, unsigned char *src, int numBytes)
{
	while (numBytes--) {
		*dest++ = *src++;
	}	/* end while */
}	/* end rtos_memcopy */



/*
 * void RoundRobinScheduler (void);
 *
 * This function will support a basic round robin scheduler
 * for our RTOS. Depends on global variable pdb_Current for
 * knowledge of which task is currently in use.
 */

void
RoundRobinScheduler (void)
{
	while (1) {
		pdb_Current = pdb_Current->NextPDB;
		if (pdb_Current->Status == READY)
			break;
	}	/* end while */
}	/* end RoundRobinScheduler */



/*
 * char * rtos_strcpy (char *dest, char *src);
 *
 * This function provides a simple strcpy() routine for the RTOS
 */

char *
rtos_strcpy (char *dest, char *src)
{
	while (*src != '\0') {
		*dest++ = *src++;
	}

	return dest;
}	/* end rtos_strcpy */

