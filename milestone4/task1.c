/*
 * \file task1.c
 *	\author Ig Kolenko, Samuel Lewis, Adrian Hyde, Dan Evans, Hekar Khani
 *
 * \brief
 * \remark
 * 
 */

#include "shared.h"
#include "stdlib.h"

/*
 * prototype
 */

void Task1_main (void);


/*
 * declare the TASK structure as a ROM structure (use const keyword)
 * that pre-defines the necessary information the RTOS needs to launch
 * the task. The RTOS will look for these ROM objects during initialization
 * as the RTOS knows EXACTLY which programs it will run by default.
 */

TASK taskTask1 = {
	NULL,
	"Task1",
	0,
	100,
	(void *)Task1_main
};



/*
 * void Task1_main (void);
 *
 * This is the starting point of the Task1 main function.
 */

void
Task1_main (void)
{
	unsigned short i = 0;
	unsigned char *p = (unsigned char *)0x0000E011L;
	/*
	 * the manipulation of the counter i, and the
	 * pointer p, is done JUST FOR DEMO PURPOSES.
	 * REMEMBER ... a user level task MUST NOT TOUCH
	 * hardware directly! In the future, stuff like that
	 * will be handled via an OS service!
	 *
	 * Here, we check to see whether i has its high bit on.
	 * after 32768 iterations, the high bit will flip its value,
	 * thus, we end up flashing the first 7 segment LED every
	 * 32768 times through the Relinquish request!
	 */
	
	while (1) {
		i++;
		if (i & 0x8000)
			*p = 0;
		else
			*p = 0xFF;

		Relinquish();
	}	/* end while */
}	/* end Task1_main */

