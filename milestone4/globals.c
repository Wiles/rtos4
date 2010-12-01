/*
 * globals.c
 *
 * This file declares global variables for our RTOS.
 */

#include "rtos.h"
#include "globals.h"

/* 
 * allocate an array of PDBs
 */

PDB pdb[MAX_PDBS];

/*
 * markers for current and first PDBs in our circular list
 */

PDB *pdb_Current;
PDB *pdb_First;

/*
 * keep track of # of timer interrupts - a crude clock!
 */

unsigned long gTickCount;

