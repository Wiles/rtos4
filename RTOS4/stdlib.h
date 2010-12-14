/*!
 * \file stdlib.h
 *	\author Ig Kolenko, Samuel Lewis, Adrian Hyde, Dan Evans, Hekar Khani
 *
 * \brief
 * This file provides prototypes for standard library
 * functions that wrap access to the RTOS services
 * \remark
 */

#ifndef __STDLIB_H__

#include "shared.h"

/*!
 * \brief
 * Give up the CPU for a single re-scheduling
 */
#ifndef X86_TEST
void Relinquish (void);
#endif

/*!
 * \brief
 * Sleep for the given duration
 * \param duration - Milliseconds to sleep for
 */
#ifndef X86_TEST
void Sleep (unsigned long duration);
#endif

/*!
 * \brief
 * Get the next available keyboard character from the
 * system's keyboard buffer.
 * \return
 *	Next available character as a short
 */
short InputKeyboardCharacter(void);

/*!
 * \brief
 * Check if there is a keyboard character available
 *	in the system's keyboard buffer
 * \return
 *	TRUE - if a keyboard character is available in the
 * 		system's keyboard buffer
 *	FALSE - otherwise
 */
int IsKeyboardCharacterAvailable(void);

/*!
 * \brief
 * Get the next available character from the
 * system's debugging buffer.
 * \return
 *	Next available character as a short
 */
short InputDebugCharacter(void);

/*!
 * \brief
 * Check if there is a character available
 *	in the system's debugging buffer
 * \return
 *	TRUE - if a character is available in the
 * 		system's debugging buffer
 *	FALSE - otherwise
 */
int IsDebugCharacterAvailable(void);

/*!
 * \brief
 * Output a character to the system's debugging
 * device
 * \param character - Character to output
 */
void OutputDebugCharacter (short character);

/*!
 * \brief
 * Check if system's debugging device port is busy
 * \return
 *	TRUE - if system's debugging device port
 *			is busy
 *	FALSE - otherwise
 */
int IsDebugPortBusy(void);

/*!
 * \brief
 * Returns the system tick count
 * \return
 *	Current system tick count
 */
unsigned long GetSystemTickCount(void);

/*!
 * \brief
 * HEKAR TODO: FILL IN THIS COMMENT
 * \return
 *	
 */
unsigned long GetGlobalDataAddress(void);

/*!
 * \brief
 * HEKAR TODO: FILL IN THIS COMMENT
 * \return
 *	
 */
void GetClockTime(struct systemtime *);

#define __STDLIB_H__
#endif

