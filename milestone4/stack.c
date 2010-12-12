/*!
 * \file stack.c
 *
 * \brief
 * This file reserves user accessable memory for application
 * stacks. Needed for OS initialization.
 */

#include "rtos.h"

char application_stack_memory[TOTAL_STACK_MEMORY];

/* TODO: eventually, this will disappear once dynamic memory support is added */
