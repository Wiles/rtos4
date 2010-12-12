;
; \file bootstrap.s
;
; \remark
; this file provides bootstrap rom/memory/peripheral checking
; plus launch of OS initialization and final work to launch first task
;


;
; constants and other items are included in final ROM assembly
; via locator using file romconst.asm
;



Startup:

	;
	; first, do a ROM test. this assumes that the
	; ROM holds a value at the final long integer location in ROM
	; ($FC0000 + 192KB - 4) with a checksum value
	; uncomment the bne statement below to actually do real ROM test
	; otherwise, go through the motions for OS build/test purposes
	;

RomTest:
	move.l	#ROM_START, a0
	move.l	#ROM_CHECKSUM, a1
	clr.l	d0

RomLoop:
	add.b	(a0)+, d0
	cmp.l	a0, a1
	bne	RomLoop

	move.l	ROM_CHECKSUM, d1
	cmp.l	d0, d1
;	bne	RomError
	bra	MemoryTests



;
; void RomError (void);
;
; this will loop forever on detecting a ROM error
;

RomError:
	bra	RomError		; loop forever on an error!
	


	; next, do RAM tests. We'll do two of them here ...

MemoryTests:
	; first, a basic memory test to determing potential wiring
	; faults (stuck bits, miswired bits, etc.)

	move.l	#RAM_START, a0
	move.l	#RAM_END, a1

MemTest1:
	move.b	#$00, d0
	move.l	#MemTest2, a5
	jmp	MemoryTest

MemTest2:
	move.b	#$FF, d0
	move.l	#MemTest3, a5
	jmp	MemoryTest
	
MemTest3:
	move.b	#$55, d0
	move.l	#MemTest4, a5
	jmp	MemoryTest
	
MemTest4:
	move.b	#$AA, d0
	move.l	#PersistenceTest, a5
	jmp	MemoryTest
	
PersistenceTest:
	; second, a persistence memory test to determing memory cell faults

MemTest5:
	move.b	#$00, d0
	move.l	#MemTest6, a5
	jmp	MemoryTest2

MemTest6:
	move.b	#$FF, d0
	move.l	#MemTest7, a5
	jmp	MemoryTest2
	
MemTest7:
	move.b	#$55, d0
	move.l	#MemTest8, a5
	jmp	MemoryTest2
	
MemTest8:
	move.b	#$AA, d0
	move.l	#PeripheralTest, a5
	jmp	MemoryTest2
	

	; next, do peripheral testing

PeripheralTest:
	; check various important hardware items to ensure
	; they're functional before proceeding

	; TODO: to be implemented later ...


bootstrap_complete:
	; at this point, we're done the basic power on self test
	; work, so now we can launch the OS

	jsr	_InitOS

	; now that OS has completed its full initialization, we
	; can ready the first task to execute, which is simply
	; our normal "Restore PDB" operation. Call up our
	; common subroutine to support this.

	jsr	RestoreCpuContext



;
; MemTest()
;
; this pseudo-function will do a basic memory test
;
; input:
; A0 = start address
; A1 = end address
; A5 = return address for pseudo-function
; D0 = test value
;
; output:
; nothing
;
; uses:
; A2 = temporary pointer to RAM
;
; if an error occurs, jump to RamError
;

MemoryTest:
	move.l	a0, a2

MemoryTestLoop:
	move.b	d0, (a2)
	cmp.b	(a2)+, d0
	bne	RamError
	cmp.l	a2, a1
	bne	MemoryTestLoop

	jmp	(a5)	; return


;
; MemoryTest2()
;
; this pseudo-function will do a persistence memory test
;
; input:
; A0 = start address
; A1 = end address
; A5 = return address for pseudo-function
; D0 = test value
;
; output:
; nothing
;
; uses:
; A2 = temporary pointer to RAM
;
; if an error occurs, jump to RamError
;

MemoryTest2:
	move.l	a0, a2

MemoryTest2Loop1:
	move.b	d0, (a2)+
	cmp.l	a2, a1
	bne	MemoryTest2Loop1

	move.l	a0, a2

MemoryTest2Loop2:
	cmp.b	(a2)+, d0
	bne	RamError
	cmp.l	a2, a1
	bne	MemoryTest2Loop2

	jmp	(a5)	; return


;
; void RamError (void);
;
; this will loop forever on detecting a ROM error
;

RamError:
	bra	RamError		; loop forever on an error!



