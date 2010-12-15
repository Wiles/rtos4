/*!
 * \file globals.h
 *	\author Ig Kolenko, Samuel Lewis, Adrian Hyde, Dan Evans, Hekar Khani
 *
 * \brief
 * This file declares external global variables for our RTOS.
 * \remark
 * Most of these globals are commented in the globals.cpp file.
 */

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "rtos.h"

extern PDB pdb[MAX_PDBS];

extern PDB *pdb_Current;
extern PDB *pdb_First;
extern unsigned long gTickCount;

extern char application_stack_memory[TOTAL_STACK_MEMORY];

#define KEYBOARD_DATA_SIZE 256
extern short keyboard_data[KEYBOARD_DATA_SIZE];
extern unsigned char keyboard_head;
extern unsigned char keyboard_tail;

#define SERIAL_DATA_SIZE 256
extern short serial_in_data[SERIAL_DATA_SIZE];
extern unsigned char serial_in_head;
extern unsigned char serial_in_tail;

#define SERIAL_OUT_DATA_SIZE 256
extern short serial_out_data[SERIAL_OUT_DATA_SIZE];
extern unsigned char serial_out_head;
extern unsigned char serial_out_tail;

#endif /* __GLOBALS_H__ */
