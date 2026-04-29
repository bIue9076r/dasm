#ifndef DASM_CPU_H
#define DASM_CPU_H
#include "dasm_type.h"
// Some systems cannot have 0x8000+ bytes
#ifndef DASM_SET_NON_STATIC_ROM
#define DASM_STATIC_ROM
#endif

#ifndef DASM_SET_NON_STATIC_MEM
#define DASM_STATIC_MEM
#endif

#ifndef DASM_SET_NON_STATIC_STK
#define DASM_STATIC_STK
#endif

#define MAX_STACK 0x0100
#define MAX_ROM 0x8000
#define MAX_MEM 0x0800

#ifdef DASM_STATIC_STK
extern byte STK[MAX_STACK];	// Stack
#endif

#ifdef DASM_STATIC_ROM
extern byte ROM[MAX_ROM];	// ROM
#endif

#ifdef DASM_STATIC_MEM
extern byte MEM[MAX_MEM];	// Memory
#endif

extern word ADDR;			// Address

word preIncAddr(void);

word postIncAddr(void);

#define PADR preIncAddr()
#define ADRP postIncAddr()

byte GetRom(word addr);
void SetRom(word addr, byte b);

extern byte SK;
extern byte FL;

byte RomFetch(void);
byte RomFetchPeek(void);
byte GetMem(word addr);
void SetMem(word addr, byte b);
byte StkPop();
void StkPut(byte b);

#define FLAG_OVERFLOW 0x80
#define FLAG_ZERO 0x40
#define FLAG_UNDERFLOW 0x20
#define FLAG_HIGH_1 0x10
#define FLAG_LOW_8 0x08
#define FLAG_INT 0x04
#define FLAG_DIS 0x02
#define FLAG_HALT 0x01

void flag_clear(void);

extern byte A;	// Register A
extern byte B;	// Register B
extern byte C;	// Register C

#endif
