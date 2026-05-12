#ifndef DASM_CPU_C
#define DASM_CPU_C
#include "dasm_cpu.h"

#ifdef DASM_STATIC_STK
byte STK[MAX_STACK];	// Stack
#endif

#ifdef DASM_STATIC_MEM
byte MEM[MAX_MEM];		// Memory
#endif

#ifdef DASM_STATIC_ROM
byte ROM[MAX_ROM];		// ROM
#endif

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


byte SK = 0xFF;	// Stack Pointer
byte FL = 0;	// 0000 0000
					// OZU- -SDH
					// O - Overflow
					// Z - Zero
					// U - Underflow
					// S - Sent Interupt
					// D - Sent Display
					// H - Halt

inline void flag_clear(void){
	FL = 0;
}

#ifdef DASM_STATIC_ROM
byte GetRom(word addr){
	return ROM[addr];
}

void SetRom(word addr, byte b){
	ROM[addr] = b;
}
#endif

byte RomFetch(void){
	return GetRom(ADRP);
}

byte RomFetchPeek(void){
	return GetRom(ADDR);
}

#ifdef DASM_STATIC_MEM
byte GetMem(word addr){
	return MEM[addr];
}

void SetMem(word addr, byte b){
	MEM[addr] = b;
}
#endif

#ifdef DASM_STATIC_STK
byte StkPop(){
	return STK[++SK];
}

void StkPut(byte b){
	STK[SK--] = b;
}
#endif

byte A = 0;	// Register A
byte B = 0;	// Register B
byte C = 0;	// Register C

#endif