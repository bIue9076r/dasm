#ifndef DASM_ALU_H
#define DASM_ALU_H
#include "dasm_type.h"

// ALU Operation Handlers

byte Add(byte b1, byte b2);
byte Sub(byte b1, byte b2);
byte Mul(byte b1, byte b2);
byte And(byte b1, byte b2);
byte Orr(byte b1, byte b2);
byte Xor(byte b1, byte b2);
byte Not(byte b);
byte Lsh(byte b);
byte Rsh(byte b);
byte Inc(byte b);
byte Dec(byte b);

#endif
