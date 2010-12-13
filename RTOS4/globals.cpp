/*!
 * \file globals.c
 *	\author Ig Kolenko, Samuel Lewis, Adrian Hyde, Dan Evans, Hekar Khani
 *
 * \brief
 * This file houses the operating system's global variables 
 * \remark
 * Though many global variables are defined here, they may or may not
 *	be initialized here, so watch out!
 * 
 */

#include "globals.h"

/*!
 * PDB allocation
 */
PDB pdb[MAX_PDBS];

/*!
 * Marker for current PDB in our circular list
 */
PDB *pdb_Current;

/*!
 * Marker first PDB in our circular list
 */
PDB *pdb_First;

/*!
 * keep track of # of timer interrupts - a crude clock!
 */
unsigned long gTickCount;

/*!
 * Data for keyboard input buffer
 */
short keyboard_data[256];

/*!
 * Index for beginning of keyboard data buffer
 */
unsigned char keyboard_head;

/*!
 * Index for end of keyboard data buffer
 */
unsigned char keyboard_tail;

/*!
 * Data for serial input buffer
 */
short serial_in_data[256];

/*!
 * Index for beginning of keyboard data buffer
 */
unsigned char serial_in_head;

/*!
 * Index for end of keyboard data buffer
 */
unsigned char serial_in_tail;

/*!
 * Data for serial out input buffer
 */
short serial_out_data[256];

/*!
 * Index for beginning of serial output data buffer
 */
unsigned char serial_out_head;

/*!
 * Index for end of serial output data buffer
 */
unsigned char serial_out_tail;

