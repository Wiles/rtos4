#
# makefile
#
# how to build project1.lst for Visual Simulator
#

rtos.lst: rtos.asm
	asm68k rtos.asm

rtos.asm: rtos.loc vector.s romconst.s bootstrap.s ossupport.s osinit.asm ipl6.s timer.asm trap.s service.asm support.asm task1.asm task2.asm globals.asm stack.asm stdlib.s
	locator rtos.loc

osinit.asm: osinit.c rtos.h globals.h
	cc68k osinit.c -M

timer.asm: timer.c rtos.h globals.h
	cc68k timer.c -M

service.asm: service.c rtos.h globals.h shared.h
	cc68k service.c -M

support.asm: support.c rtos.h globals.h
	cc68k support.c -M

globals.asm: globals.c rtos.h globals.h
	cc68k globals.c -M

stack.asm: stack.c rtos.h globals.h
	cc68k stack.c -M

task1.asm: task1.c stdlib.h shared.h
	cc68k task1.c -M

task2.asm: task2.c stdlib.h shared.h
	cc68k task2.c -M

clean:
	rm *.asm *.lst *.hex *.ASM *.LST *.HEX

