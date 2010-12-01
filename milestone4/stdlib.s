;
; stdlib.s
;
; This file implements standard library wrappers for user code
; to access RTOS services. Services will obtain their parameters
; from the user stack. The wrappers are implemented in assembly code
; as the wrappers must invoke a TRAP instruction, which can only
; be done in assembly.
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

;short InputKeyboardCharacter(void);
_InputKeyboardCharacter:
	rts
;int IsKeyboardCharacterAvailable(void);
_IsKeyboardCharacterAvailable:
	rts
;short InputDebugCharacter(void);
_InputDebugCharacter:
	rts
;int IsDebugCharacterAvailable(void);
_IsDebugCharacterAvailable:
	rts
;void OutputDebugCharacter (short);
_OutputDebugCharacter:
	rts
;int IsDebugPortBusy(void);
_IsDebugPortBusy:
	rts
;unsigned long GetSystemTickCount(void);
_GetSystemTickCount:
	rts
;unsigned long GetGlobalDataAddress(void);
_GetGlobalDataAddress:
	rts




