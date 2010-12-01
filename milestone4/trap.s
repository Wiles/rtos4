;
; trap.s
;
; This file provides support for TRAP handling.
; It will support the potential of task switching in addition
; to providing access to RTOS services. Support is provided in
; two pieces: an assembly prologue/epilogue to enter/exit the RTOS,
; and a C based routine to manage timer oriented work.
;

trap1_handler:
	; disable interrupts here!
	or	#$0700, sr
	jsr	SaveCpuContext
	jsr	_SupportBASS
	jsr	RestoreCpuContext

	; if we get here, it's a huge huge problem!

trap1_error:
	bra	trap1_error

