RTOS 2008 - Barebones
=====================


This is a barebones implementation of RTOS 2008, which will
be targetted for the Atari ST series of 680x0 based computers.

The RTOS consists of the following files:

ROM
---
vector.s	vector table
romconst.s	miscellaneous constants and declarations for RTOS assembly code
bootstrap.s	bootstrap memory testing
osinit.c	operating system initialization support
ipl6.s		IPL6 interrupt handler (calls support in timer.c)
timer.c		support for pre-emption, SLEEP service wakeup
trap.s		TRAP #1 interrupt handler (calls support in service.c)
service.c	support for RELINQUISH and SLEEP services
ossupport.s	miscellaneous RTOS support functions (in assembly)
support.c	miscellaneous RTOS support functions (in C)
rtos.h		declarations for RTOS constants, structures, prototypes
shared.h	public header exposing service numbers (shared by RTOS and tasks)

RAM
---
globals.c	RTOS global variable declarations
stack.c		task stack reservation (only until dynamic memory support added)
globals.h	header file for shared global variable declarations


Applications (in ROM)
---------------------

task1.c		task #1 code
task2.c		task #2 code
stdlib.c	standard library wrappers (to invoke TRAP to OS)
stdlib.h	prototypes for standard library functions
shared.h	see above

note: both of the task source files above define a TASK structure variable
that will be stored in ROM (the variable is defined with the code
thus, gets compiled into CODE space. This is important, as these
are pre-defined values! Modern compilers would use the "const"
keyword to do the same thing)


Build Support
-------------

readme.txt	this file
makefile	to automate builds using DEV68K package
rtos.loc	locator file to assemble RTOS correctly

