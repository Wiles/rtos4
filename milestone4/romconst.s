;
; romconst.asm
;
; this file contains ROM constants and other declarations
; useful to share amongst all ROM assembly source files
;


; 192KB of ROM ($30000 bytes)

; (note: due to a bug in the assembler, we have to explicitly set
; the values for these constants, rather than having assembler
; perform mathematics on the values)
;
; TODO: change these to the true END of their ranges for a full RTOS,
; as these minimal end values are suitable for simply testing support

ROM_START	equ $00fc0000
ROM_END		equ ($00fc0000 + $10)
;ROM_END		equ ($00fc0000 + $30000)
ROM_CHECKSUM	equ ($00fc0000 + $10 - $4)
;ROM_CHECKSUM	equ ($00fc0000 + $30000 - $4)

; 512KB of RAM
; note: RAM starts at 8 bytes in, due to quirk in Atari hardware

RAM_START	equ ($00000000 + $8)
RAM_END		equ ($00000000 + $10)
;RAM_END		equ ($00000000 + $80000)

;
; PDB structure declaration in assembly
;

NextPDB			equ 0
ApplicationID		equ 4
ApplicationName		equ 8
AmountOfGlobalSpace	equ 40
PointerToGlobalSpace	equ 44
AmountOfStackSpace	equ 48
PointerToStackSpace	equ 52

Reg_D0			equ 56
Reg_D1			equ 60
Reg_D2			equ 64
Reg_D3			equ 68
Reg_D4			equ 72
Reg_D5			equ 76
Reg_D6			equ 80
Reg_D7			equ 84

Reg_A0			equ 88
Reg_A1			equ 92
Reg_A2			equ 96
Reg_A3			equ 100
Reg_A4			equ 104
Reg_A5			equ 108
Reg_A6			equ 112

Reg_SP			equ 116
Reg_PC			equ 120
Reg_SR			equ 124

Status			equ 126
Reason			equ 130

SleepDuration		equ 134

;
; future PDB objects added here
; ensure you adjust SizePDB accordingly
;

SizePDB			equ 138



;
; useful ROM constants
;


READY		equ 'R'
BLOCKED		equ 'B'

REASON_NONE	equ 0
REASON_SLEEP	equ 1

MAX_PDBS	equ 2

