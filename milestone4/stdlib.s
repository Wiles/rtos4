;
; stdlib.s
;
; This file implements standard library wrappers for user code
; to access RTOS services. Services will obtain their parameters
; from the user stack. The wrappers are implemented in assembly code
; as the wrappers must invoke a TRAP instruction, which can only
; be done in assembly.
;

BASS_RELINQUISH		equ 1
BASS_SLEEP		equ 2


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



