;-----------------------------------------------------------------------------
; Assembly main line
;-----------------------------------------------------------------------------

include "m8c.inc"       ; part specific constants and macros
include "memory.inc"    ; Constants & macros for SMM/LMM and Compiler
include "PSoCAPI.inc"   ; PSoC API definitions for all User Modules

export _main

_main:

    ; M8C_EnableGInt ; Uncomment this line to enable Global Interrupts
	; Insert your main assembly code here.

begin:	mov A, reg[PRT0DR]
		and A, 01h
		jz off
		or reg[PRT1DR], 01h
		jmp begin
off:	and reg[PRT1DR], ~01h
		jmp begin
		
.terminate:
    jmp .terminate
