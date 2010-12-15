/*!
 * \file task1.c
 *	\author Ig Kolenko, Samuel Lewis, Adrian Hyde, Dan Evans, Hekar Khani
 *
 * \brief
 * \remark
 * 	Modified to test GetGlobalAddress
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
	long global = GetGlobalDataAddress();
	while (1) {
		Relinquish();
	}
}	/* end Task1_main */

