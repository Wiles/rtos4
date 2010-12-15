/*!
 * \file support.c
 *	\author Ig Kolenko, Samuel Lewis, Adrian Hyde, Dan Evans, Hekar Khani
 *
 * \brief
 * Additional C based support routines for RTOS
 * \remark
 * Most of these functions are unnecessary under the Windows simulation, but
 * they're kept here to keep the RTOS library as similar to the RTOS codebase
 * as possible.
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

