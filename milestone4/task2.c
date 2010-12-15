/*!
 * \file task2.c
 *	\author Ig Kolenko, Samuel Lewis, Adrian Hyde, Dan Evans, Hekar Khani
 *
 * \brief
 * \remark
 * 		Modified to test GetSystemTickCount
 */
 
#include "shared.h"
#include "stdlib.h"

void Task2_main (void);


/*
 * declare the TASK structure as a ROM structure (use const keyword)
 * that pre-defines the necessary information the RTOS needs to launch
 * the task. The RTOS will look for these ROM objects during initialization
 * as the RTOS knows EXACTLY which programs it will run by default.
 */

TASK taskTask2 = {
	NULL,
	"Task2",
	0,
	200,
	(void *)Task2_main
};



/*
 * void Task2_main (void);
 *
 * This is the starting point of the Task2 main function.
 */

void
Task2_main (void)
{
	/*
	 * For testing purposes this task gets the system
	 * tick count form the OS and outputs the lower byte of that
	 * data to the LEDs
	 */
	unsigned char i = GetSystemTickCount();
	unsigned char *p = (unsigned char *)0x0000E013L;
	

	while (1) {
		i = (char)GetSystemTickCount();
		*p = i;

		Sleep(1);
	}	/* end while */
}	/* end Task2_main */

