/*
 * \file stdlib.h
 *	\author Ig Kolenko, Samuel Lewis, Adrian Hyde, Dan Evans, Hekar Khani
 *
 * \brief
 * This file provides prototypes for standard library
 * functions that wrap access to the RTOS services
 * \remark
 */

#ifndef __STDLIB_H__

void Relinquish (void);
void Sleep (unsigned long duration);

short InputKeyboardCharacter(void);
int IsKeyboardCharacterAvailable(void);

short InputDebugCharacter(void);
int IsDebugCharacterAvailable(void);

void OutputDebugCharacter (short);
int IsDebugPortBusy(void);

unsigned long GetSystemTickCount(void);
unsigned long GetGlobalDataAddress(void);

void GetClockTime(struct systemtime *);

#define __STDLIB_H__
#endif

