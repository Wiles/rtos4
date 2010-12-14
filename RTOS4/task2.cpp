/*!
 * \file task2.c
 *	\author Ig Kolenko, Samuel Lewis, Adrian Hyde, Dan Evans, Hekar Khani
 *
 * \brief
 * \remark
 * 
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

void
Task2_main (void)
{
}
