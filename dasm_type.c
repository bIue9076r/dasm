#ifndef DASM_TYPE_C
#define DASM_TYPE_C
#include "dasm_type.h"

byte highbyte(word w){
	return (w & 0xFF00) >> 8;
}

byte lowbyte(word w){
	return (w & 0xFF);
}

word packBytes(byte h, byte l){
	return (h << 8) | (l);
}

#endif