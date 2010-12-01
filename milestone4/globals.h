/*
 * globals.h
 *
 * This file declares external global variables for our RTOS.
 */

#ifndef __GLOBALS_H__

#include "rtos.h"

extern PDB pdb[MAX_PDBS];

extern PDB *pdb_Current;
extern PDB *pdb_First;
extern unsigned long gTickCount;

extern char application_stack_memory[TOTAL_STACK_MEMORY];

#define __GLOBALS_H__
#endif
