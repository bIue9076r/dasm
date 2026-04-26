#ifndef DASM_ALU_C
#define DASM_ALU_C
#include "dasm_cpu.h"
#include "dasm_alu.h"

// ALU Operation Handlers

byte Add(byte b1, byte b2){
	flag_clear();
	word res = b1 + b2;
	if(res > 255){
		FL = FL | FLAG_OVERFLOW;
	}
	
	return (res & 0xFF);
}

byte Sub(byte b1, byte b2){
	flag_clear();
	word res = b1 - b2;
	if((sword)res < 0){
		FL = FL | FLAG_UNDERFLOW;
	}

	if((res & 0xFF) == 0){
		FL = FL | FLAG_ZERO;
	}

	return (res & 0xFF);
}

byte Mul(byte b1, byte b2){
	flag_clear();
	word res = b1 * b2;
	if(res > 255){
		FL = FL | FLAG_OVERFLOW;
	}

	if((res & 0xFF) == 0){
		FL = FL | FLAG_ZERO;
	}

	return (res & 0xFF);
}

byte And(byte b1, byte b2){
	flag_clear();
	byte res = b1 & b2;

	if(res == 0){
		FL = FL | FLAG_ZERO;
	}

	return res;
}

byte Orr(byte b1, byte b2){
	flag_clear();
	byte res = b1 | b2;

	if(res == 0){
		FL = FL | FLAG_ZERO;
	}

	return res;
}

byte Xor(byte b1, byte b2){
	flag_clear();
	byte res = b1 ^ b2;

	if(res == 0){
		FL = FL | FLAG_ZERO;
	}

	return res;
}

byte Not(byte b){
	flag_clear();
	byte res = ~b;

	if(res == 0){
		FL = FL | FLAG_ZERO;
	}

	return res;
}

byte Lsh(byte b){
	flag_clear();
	word res = b << 1;
	
	if((b & 0x80) > 0){
		FL = FL | FLAG_OVERFLOW;
	}

	if((res & 0xFF) == 0){
		FL = FL | FLAG_ZERO;
	}
	
	return (res & 0xFF);
}

byte Rsh(byte b){
	flag_clear();
	word res = b >> 1;

	if((b & 0x01) > 0){
		FL = FL | FLAG_UNDERFLOW;
	}

	if((res & 0xFF) == 0){
		FL = FL | FLAG_ZERO;
	}

	return (res & 0xFF);
}

byte Inc(byte b){
	byte res = b + 1;

	if(b == 0xFF){
		FL = FL | FLAG_OVERFLOW;
	}

	return res;
}

byte Dec(byte b){
	byte res = b - 1;

	if(b == 0x00){
		FL = FL | FLAG_UNDERFLOW;
	}

	return res;
}


#endif
