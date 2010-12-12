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

short keyboard_data[256];
char keyboard_head;
char keyboard_tail;

short serial_in_data[256];
char serial_in_head;
char serial_in_tail;

short serial_out_data[256];
char serial_out_head;
char serial_out_tail;

