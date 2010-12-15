/*!
 * \file stdlib.h
 *	\author Ig Kolenko, Samuel Lewis, Adrian Hyde, Dan Evans, Hekar Khani
 *
 * \brief
 * This file provides prototypes for standard library
 * functions that wrap access to the RTOS services
 * \remark
 * History:
 *  Added function prototypes for service calls
 */

#ifndef __STDLIB_H__

/*!
 * \brief
 * Give up the CPU for a single re-scheduling
 */
void Relinquish (void);

/*!
 * \brief
 * Sleep for the given duration
 * \param duration - Milliseconds to sleep for
 */
void Sleep (unsigned long duration);

/*!
 * \brief
 * Get the next available keyboard character from the
 * system's keyboard buffer.
 * This function will block if no characters are available.
 * The task will be unblocked when a character becomes available
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
 * This function will block if no characters are available.
 * The task will be unblocked when a character becomes available
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
 * Returns that Address of the calling tasks global data
 * \return
 *	Address to tasks global data
 */
unsigned long GetGlobalDataAddress(void);

/*!
 * \brief
 * Returns the system tick count formated into hours, minutes, and seconds
 * \return
 *	systemtime struct for tick count information
 */
void GetClockTime(struct systemtime *);

#define __STDLIB_H__
#endif

