;
; ipl6.s
;
; This file provides support for IPL6 (assumed to be a timer).
; It will support pre-emptive multitasking, as well as the ability
; to manage Sleep service support. This code is split into
; two pieces: an assembly prologue/epilogue to enter/exit the RTOS,
; and a C based routine to manage timer oriented work.
;

ipl6_handler:
	; disable interrupts here!
	or	#$0700, sr
	jsr	SaveCpuContext
	jsr	_TimerSupport
	jsr	RestoreCpuContext

	; if we get here, it's a huge huge problem!

ipl6_error:
	bra	ipl6_error
