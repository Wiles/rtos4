;
; \file stdlib.s
;
; \remark
; This file implements standard library wrappers for user code
; to access RTOS services. Services will obtain their parameters
; from the user stack. The wrappers are implemented in assembly code
; as the wrappers must invoke a TRAP instruction, which can only
; be done in assembly.
;
; History:
;  Added BASS service numbers. And ASM wrappers
;

BASS_RELINQUISH			equ 1
BASS_SLEEP				equ 2
BASS_GET_KEYBOARD		equ 3
BASS_KEYBOARD_STATUS	equ 4
BASS_GET_DEBUG			equ 5
BASS_DEBUG_IN_STATUS	equ 6
BASS_WRITE_DEBUG		equ 7
BASS_DEBUG_BUSY			equ 8
BASS_TICK_COUNT			equ 9
BASS_GLOBAL_ADDRESS		equ 10
BASS_GETCLOCKTIME 		equ 11

;
; void Relinquish (void);
;
; This OS service wrapper will ask the OS to give up the
; remainder of the current application's time slice, thus
; schedule another program to run.
; 

_Relinquish:
	move.l	#BASS_RELINQUISH, d0
	trap	#1
	rts


;
; void Sleep (unsigned long duration);
;
; This OS service wrapper will ask the OS to put the
; current task to sleep. The duration is provided as a
; parameter to this wrapper, which the OS will pull from
; the user stack.
;

_Sleep:
	move.l	#BASS_SLEEP, d0
	trap	#1
	rts

;
;short InputKeyboardCharacter(void);
;
; Asks the OS for a character from the keyboard
; Task is blocked if no characters are available
;
_InputKeyboardCharacter:
	move.l #BASS_GET_KEYBOARD, d0
	trap #1
	rts
;
;int IsKeyboardCharacterAvailable(void);
; 
; Asks the OS if there are any characters
; In the keyboard buffer
;
_IsKeyboardCharacterAvailable:
	move.l #BASS_KEYBOARD_STATUS, d0
	trap #1
	rts
	
;
;short InputDebugCharacter(void);
;
; Asks the OS for a character from the debug buffer
; Task is blocked if no characters are available
;
_InputDebugCharacter:
	move.l #BASS_GET_DEBUG, d0
	trap #1
	rts

;
;int IsDebugCharacterAvailable(void);
;
; Asks the OS if there are any characters
; In the debug buffer
;
_IsDebugCharacterAvailable:
	move.l #BASS_DEBUG_IN_STATUS, d0
	trap #1
	rts
	
;
;void OutputDebugCharacter (short character);
;
; Asks the OS to output the provided character to the
; Debug port
;
_OutputDebugCharacter:
	move.l #BASS_WRITE_DEBUG, d0
	trap #1
	rts

;
;int IsDebugPortBusy(void);
;
; Ask the OS if the debug port is ready for data
;
_IsDebugPortBusy:
	move.l #BASS_DEBUG_BUSY, d0
	trap #1
	rts
	
;
;unsigned long GetSystemTickCount(void);
;
; Ask the OS for the number of Tick counts since
; start up.
;
_GetSystemTickCount:
	move.l #BASS_TICK_COUNT, d0
	trap #1	
	rts
	
;
;unsigned long GetGlobalDataAddress(void);
;
; Asks the OS for the tasks global data address
;
_GetGlobalDataAddress:
	move.l #BASS_GLOBAL_ADDRESS, d0
	trap #1
	rts
	
;void GetClockTime(struct systemtime *);
;
;This wrapper will get the current clock time
;It will the passed to a time struct and the time extracted 
; as minutes, hours, and seconds
_GetClockTime:
	move.l #BASS_GETCLOCKTIME, d0                     
	trap   #1
	rts