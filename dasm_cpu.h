#ifndef DASM_CPU_H
#define DASM_CPU_H
#include "dasm_type.h"

#define MAX_STACK 0x0100
#define MAX_ROM 0x4000
#define MAX_MEM 0x0800

extern byte STK[0x100];		// Stack
extern byte ROM[0x4000];	// ROM
extern byte MEM[0x0800];	// Memory
extern word ADDR;			// Address

extern word preIncAddr(void);

extern word postIncAddr(void);

#define PADR preIncAddr()
#define ADRP postIncAddr()

extern byte SP;
extern byte FL;

#define FLAG_OVERFLOW 0x80
#define FLAG_ZERO 0x40
#define FLAG_UNDERFLOW 0x20
#define FLAG_HIGH_1 0x10
#define FLAG_LOW_8 0x08
#define FLAG_LOW_4 0x04
#define FLAG_LOW_2 0x02
#define FLAG_HALT 0x01

void flag_clear(void);

extern byte A;	// Register A
extern byte B;	// Register B
extern byte C;	// Register C

#endif
