/*
 * stdlib.h
 *
 * This file provides prototypes for standard library
 * functions that wrap access to the RTOS services
 */

#ifndef __STDLIB_H__

void Relinquish (void);
void Sleep (unsigned long duration);

#define __STDLIB_H__
#endif

