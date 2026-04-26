#ifndef DASM_TYPE_H
#define DASM_TYPE_H

#include <stdint.h>

typedef uint8_t byte;
typedef uint16_t word;
typedef int8_t sbyte;
typedef int16_t sword;

byte highbyte(word w);
byte lowbyte(word w);
word packBytes(byte h, byte l);

#endif