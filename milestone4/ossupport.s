;
; ossupport.s
;
; this file supplies support routines for the RTOS, as well as
; the common exception handler
;


;
; void common_handler (void);
;
; This will simply RTE back to the caller to ensure that every
; interrupt vector has some minimal support.
;

common_handler:
	rte

;
; void SaveCpuContext (void);
;
; This function will save away CPU context upon entry into the RTOS.
; Since it's set up to be called as a subroutine, special consideration
; must be taken to ensure the return address is safely pulled from stack
; while the original application's stack frame is removed. We'll use the
; pseudo-function concept of relying on an address register to save the
; return address (we'll use A1 for that purpose)
;
; uses:
; pdb_Current - OS global indicating what the current task is
; A0 - pointer to current task
; A1 - return address for subroutine support
; A2 - temporary storage of USP
;

SaveCpuContext:
	movem.l a0-a1, -(sp)           ; save temporary copy of A0/A1 registers
	move.l _pdb_Current, a0        ; get pdb_Current base address into A0
	move.l (sp)+, Reg_A1(a0)       ; save our temp copy of A1 into PDB
	move.l (sp)+, Reg_A0(a0)       ; save our temp copy of A0 into PDB

	; next, we can remove the return address of this function from
	; the stack, so that we can then gain access to the PC/SR values
	; store in a1 for eventual jump back via that address register

	move.l	(sp)+, a1

	; now get PC/SR

	move.w (sp)+, Reg_SR(a0)       ; save the user task SR register
	move.l (sp)+, Reg_PC(a0)       ; save the user task PC register

	; note: at this point, the supervisor stack will no longer point to
	; the application's stack frame, as we've physically removed the two
	; user task details off the stack and into the PDB!

	; save data registers

	move.l d0, Reg_D0(a0)           ; save the user task D0 Register
	move.l d1, Reg_D1(a0)           ; save the user task D1 register
	move.l d2, Reg_D2(a0)           ; save the user task D2 register
	move.l d3, Reg_D3(a0)           ; save the user task D3 register
	move.l d4, Reg_D4(a0)           ; save the user task D4 register
	move.l d5, Reg_D5(a0)           ; save the user task D5 register
	move.l d6, Reg_D6(a0)           ; save the user task D6 register
	move.l d7, Reg_D7(a0)           ; save the user task D7 register

	; save remaining address registers (remember A0, A1 already saved)

	move.l a2, Reg_A2(a0)           ; save the user task A2 register
	move.l a3, Reg_A3(a0)           ; save the user task A3 register
	move.l a4, Reg_A4(a0)           ; save the user task A4 register
	move.l a5, Reg_A5(a0)           ; save the user task A5 register
	move.l a6, Reg_A6(a0)           ; save the user task A6 register

	; we need to treat SP differently, as we want the USER stack
	; pointer, not the supervisor stack pointer. 

	move.l usp, A2                   ; get a copy of the USP (A2 is safe, as it's saved already!)
	move.l A2, Reg_SP(a0)            ; save the user stack pointer

	; and return to caller via jump thruogh A1 register
	
	jmp	(a1)


;
; void RestoreCpuContext (void);
;
; This function will exit the RTOS back to user level code
; and it assumes that the pdb_Current pointer is already pointing to the correct
; PDB to restore. Since it's set up to be called as a subroutine,
; and it's a subroutine that really doesn't return to the caller,
; it will strip the return address off the supervisor stack before
; exiting with an RTE
;
; uses:
; pdb_Current - global PDB pointer assumed to point to task to restore
; A0 - temporary pointer to Current PDB
; A1 - temporary holder of USP
;

RestoreCpuContext:
	addq.l	#4, sp			; eliminate useless return address

	move.l _pdb_Current, a0         ; get the Current PDB pointer

	; next, restore the user task stack pointer 

	move.l Reg_SP(a0), A1           ; get the user stack pointer
	move.l A1, usp                  ; restore the USP in the CPU

	; next, restore the data registers

	move.l Reg_D0(a0), d0           ; restore the user task D0 register
	move.l Reg_D1(a0), d1           ; restore the user task D1 register
	move.l Reg_D2(a0), d2           ; restore the user task D2 register
	move.l Reg_D3(a0), d3           ; restore the user task D3 register
	move.l Reg_D4(a0), d4           ; restore the user task D4 register
	move.l Reg_D5(a0), d5           ; restore the user task D5 register
	move.l Reg_D6(a0), d6           ; restore the user task D6 register
	move.l Reg_D7(a0), d7           ; restore the user task D7 register

	; repeat for all address registers EXCEPT for A0 and SP, as
	; A0 is our reference to the Current PDB. restore it LAST,
	; just like how we saved it first earlier! We restored SP
	; earlier, as it's the special case of the USP

	move.l Reg_A1(a0), a1           ; restore the user task A1 register
	move.l Reg_A2(a0), a2           ; restore the user task A2 register
	move.l Reg_A3(a0), a3           ; restore the user task A3 register
	move.l Reg_A4(a0), a4           ; restore the user task A4 register
	move.l Reg_A5(a0), a5           ; restore the user task A5 register
	move.l Reg_A6(a0), a6           ; restore the user task A6 register

	; then, restore the stack frame for the new task

	move.l Reg_PC(a0), -(sp)       ; restore the user task PC register in stack frame
	move.w Reg_SR(a0), -(sp)       ; restore the user task SR register in stack frame

	; and finally, load the user's copy of A0 before we RTE

	move.l Reg_A0(a0), a0          ; restore user task A0 

	; at this point, we've 100% reloaded the CPU with ALL the register values
	; that make up the new task's context! now we're free to RTE, to resume
	; processing this task!

	rte

	

