/*
 * stdlib.h
 *
 * This file provides prototypes for standard library
 * functions that wrap access to the RTOS services
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

#define __STDLIB_H__
#endif

