/*
 * osinit.c
 *
 * This file provides RTOS initialization support from the C
 * programming perspective.
 *
 * It will initialize the PDBs with values, and configure other
 * operating system global data.
 */

#include "rtos.h"
#include "globals.h"


/*
 * these were defined along with the tasks ... we weill
 * include external declarations of them here for OS init support
 * REMEMBER: these were defined as ROM variables (constants) as
 * this information MUST be present at boot time in ROM.
 */

extern TASK taskTask1;
extern TASK taskTask2;



/*
 * void InitOS (void);
 *
 * This function will initialize the RTOS OS globals, PDBs, etc.
 *
 * For diagnostic purposes, init the data/addr registers
 * with values that can easily be seen during emulator
 * based debug of RTOS code. We'll use 0x11111111 for task 1
 * and 0x22222222 for task 2. Note that for this cut of the RTOS
 * we have a statically allocated chunk of RAM assigned for all task
 * stack memory, and this is divvied up manually below. 
 *
 * TODO: future revision should dynamically allocate PDB and stack memory!
 */

void
InitOS (void)
{
	PDB *p;
	char *ptrUserStackMem;

	/*
	 * copy ROM vector table to RAM, knowing that the first two
	 * long integers are already mapped to first 2 long integers
	 * of RAM.
	 */

	rtos_memcopy (RAM_START + 2 * sizeof (long), 
		VECTOR_START + 2 * sizeof (long), 
		VECTOR_SIZE - 2 * sizeof (long));

	/*
	 * begin init process
	 */

	pdb_First = NULL;
	pdb_Current = NULL;


	/*
	 * set the pointer to the start of our stack memory
	 * and divvy it up based on TASK structure definition. For
	 * each init, move the pointer to the next block based on
	 * the current task's amount of stack space reserved. 
	 *
	 * TODO: in the future, this user stack memory concept will
	 * be replaced by actual memory allocation support in our RTOS!
	 */

	ptrUserStackMem = application_stack_memory;
	InitializePDB (1, &pdb[0], &taskTask1, ptrUserStackMem, 0x11111111L);

	ptrUserStackMem += pdb[0].AmountOfStackSpace;	
	InitializePDB (2, &pdb[1], &taskTask2, ptrUserStackMem, 0x22222222L);

	ptrUserStackMem += pdb[1].AmountOfStackSpace;	
	/* future tasks can be initialized the same way! */

	/*
	 * ensure pdb_Current points to first task
	 */

	pdb_Current = pdb_First;

	/*
	 * init our timer counter (to provide rudimentary 
	 * timing support)
	 */

	gTickCount = 0;
	
	keyboard_head = 0;
	keyboard_tail = 0;

	serial_in_head = 0;
	serial_in_tail = 0;

	serial_out_head = 0;
	serial_out_tail = 0;
	
	
}	/* end InitOS */



/*
 * void InitializePDB (int taskID, PDB *p, TASK *t, char *pStack, 
 *     unsigned long initVal);
 *
 * This function will perform the PDB initialization so that we can
 * easily expand our list of tasks without repeating lots of code. We
 * supply the task ID value, address of a PDB, address of the TASK
 * structure supplying initialization info for the PDB, a pointer to 
 * stack memory (or NULL to indicate this function will dynamically
 * allocate the memory) and a value used to initialize the registers with.
 *
 * TODO: if the PDB pointer supplied is NULL, this function will
 * dynamically allocate the PDB itself! The PDB SHOULD be in protected memory.
 */

int
InitializePDB (int taskID, PDB *p, TASK *t, char *pStack, unsigned long initVal)
{
	PDB *q;

	if (p == NULL) {
		/* TODO: dynamically allocate PDB memory and check for errors */

		if (p == NULL) {
			return FALSE;
		}
	}	/* endif */

	/*
	 * initialize PDB housekeeping data
	 */

	p->ApplicationID = taskID;
	rtos_strcpy (p->ApplicationName, t->ApplicationName);

	/* TODO: in the future, allocate space for globals and set pointer! */
	p->AmountOfGlobalSpace = t->AmountOfGlobalSpace;
	p->PointerToGlobalSpace = NULL;

	/* TODO: in the future, if pStack is NULL, allocate stack dynamically */
	p->AmountOfStackSpace = t->AmountOfStackSpace;
	if (pStack == NULL) {
		p->PointerToStackSpace = NULL;
	} else {
		p->PointerToStackSpace = pStack;
	}

	/*
	 * remainder of basic PDB init
	 */

	p->RegD0 = initVal;
	p->RegD1 = initVal;
	p->RegD2 = initVal;
	p->RegD3 = initVal;
	p->RegD4 = initVal;
	p->RegD5 = initVal;
	p->RegD6 = initVal;
	p->RegD7 = initVal;

	p->RegA0 = initVal;
	p->RegA1 = initVal;
	p->RegA2 = initVal;
	p->RegA3 = initVal;
	p->RegA4 = initVal;
	p->RegA5 = initVal;
	p->RegA6 = initVal;

	p->RegSP = (unsigned long)(p->PointerToStackSpace +
		p->AmountOfStackSpace);
	p->RegPC = t->PointerToCode;
	p->RegSR = 0x0000;	/* all interrupts available, user mode */
	p->Status = READY;
	p->Reason = REASON_NONE;
	p->SleepDuration = 0;

	/*
	 * add this to the global PDB list using standard
	 * end of linked list insertion techniques
	 */

	if (pdb_First == NULL) {
		pdb_First = p;
	} else {
		q = pdb_First;
		/* find end of list when last element points to first (circular!) */
		while (q->NextPDB != pdb_First) {
			q = q->NextPDB;
		}
		q->NextPDB = p;
	}	/* end while */

	/* 
	 * newest task will be added to end of list, thus
	 * it's "next" will be the first to ensure it's
	 * a circular list
	 */

	p->NextPDB = pdb_First;
}	/* end InitializePDB */


