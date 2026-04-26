#ifndef DASM_CPU_C
#define DASM_CPU_C
#include "dasm_cpu.h"

byte STK[0x100];		// Stack
byte ROM[0x4000];	// ROM
byte MEM[0x0800];	// Memory
word ADDR = 0x0000;	// Address

inline word preIncAddr(){
	return (++ADDR >= MAX_ROM)?(ADDR = 0):(ADDR);
}

inline word postIncAddr(){
	word addr = ADDR++;
	if(ADDR >= MAX_ROM){
		ADDR = 0;
	}

	return addr;
}


byte SP = 0xFF;	// Stack Pointer
byte FL = 0;	// 0000 0000
					// OZU- ---H
					// O - Overflow
					// Z - Zero
					// U - Underflow
					// H - Halt

inline void flag_clear(void){
	FL = 0;
}

byte A = 0;	// Register A
byte B = 0;	// Register B
byte C = 0;	// Register C

#endif