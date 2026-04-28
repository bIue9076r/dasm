#ifndef DASM_INST_SET_C
#define DASM_INST_SET_C
#include "dasm_inst_set.h"

void Nop(void){
	return;
}

void Display(void){
	FL = FL | FLAG_DIS;
}

// A

void Load_A_Imm(void){
	A = ROM[ADRP];
}

void Load_A_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	A = MEM[addr];
}

void Store_A_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	MEM[addr] = A;
}

void Put_A(void){
	STK[SK--] = A;
}

void Pop_A(void){
	STK[SK++] = A;
}

void T_A_B(void){
	B = A;
}

void T_A_C(void){
	C = A;
}

// B

void Load_B_Imm(void){
	B = ROM[ADRP];
}

void Load_B_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	B = MEM[addr];
}

void Store_B_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	MEM[addr] = B;
}

void Put_B(void){
	STK[SK--] = B;
}

void Pop_B(void){
	STK[SK++] = B;
}

void T_B_A(void){
	A = B;
}

void T_B_C(void){
	C = B;
}

// C

void Load_C_Imm(void){
	C = ROM[ADRP];
}

void Load_C_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	C = MEM[addr];
}

void Store_C_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	MEM[addr] = C;
}

void Put_C(void){
	STK[SK--] = C;
}

void Pop_C(void){
	STK[SK++] = C;
}

void T_C_A(void){
	A = C;
}

void T_C_B(void){
	B = C;
}

// Operations

void Add_A_Imm(void){
	byte b = ROM[ADRP];
	A = Add(A, b);
}

void Add_A_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	A = Add(A, MEM[addr]);
}

void Add_A_B(void){
	A = Add(A, B);
}

void Add_A_C(void){
	A = Add(A, C);
}

void Sub_A_Imm(void){
	byte b = ROM[ADRP];
	A = Sub(A, b);
}

void Sub_A_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	A = Sub(A, MEM[addr]);
}

void Sub_A_B(void){
	A = Sub(A, B);
}

void Sub_A_C(void){
	A = Sub(A, C);
}

void Mul_A_Imm(void){
	byte b = ROM[ADRP];
	A = Mul(A, b);
}

void Mul_A_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	A = Mul(A, MEM[addr]);
}

void Mul_A_B(void){
	A = Mul(A, B);
}

void Mul_A_C(void){
	A = Mul(A, C);
}

void And_A_Imm(void){
	byte b = ROM[ADRP];
	A = And(A, b);
}

void And_A_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	A = And(A, MEM[addr]);
}

void And_A_B(void){
	A = And(A, B);
}

void And_A_C(void){
	A = And(A, C);
}

void Or_A_Imm(void){
	byte b = ROM[ADRP];
	A = Orr(A, b);
}

void Or_A_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	A = Orr(A, MEM[addr]);
}

void Or_A_B(void){
	A = Orr(A, B);
}

void Or_A_C(void){
	A = Orr(A, C);
}

void Xor_A_Imm(void){
	byte b = ROM[ADRP];
	A = Xor(A, b);
}

void Xor_A_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	A = Xor(A, MEM[addr]);
}

void Xor_A_B(void){
	A = Xor(A, B);
}

void Xor_A_C(void){
	A = Xor(A, C);
}

void Add_B_Imm(void){
	byte b = ROM[ADRP];
	B = Add(B, b);
}

void Add_B_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	B = Add(B, MEM[addr]);
}

void Add_B_A(void){
	B = Add(B, A);
}

void Add_B_C(void){
	B = Add(B, C);
}

void Sub_B_Imm(void){
	byte b = ROM[ADRP];
	B = Sub(B, b);
}

void Sub_B_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	B = Sub(B, MEM[addr]);
}

void Sub_B_A(void){
	B = Sub(B, A);
}

void Sub_B_C(void){
	B = Sub(B, C);
}

void Mul_B_Imm(void){
	byte b = ROM[ADRP];
	B = Mul(B, b);
}

void Mul_B_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	B = Mul(B, MEM[addr]);
}

void Mul_B_A(void){
	B = Mul(B, A);
}

void Mul_B_C(void){
	B = Mul(B, C);
}

void And_B_Imm(void){
	byte b = ROM[ADRP];
	B = And(B, b);
}

void And_B_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	B = And(B, MEM[addr]);
}

void And_B_A(void){
	B = And(B, A);
}

void And_B_C(void){
	B = And(B, C);
}

void Or_B_Imm(void){
	byte b = ROM[ADRP];
	B = Orr(B, b);
}

void Or_B_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	B = Orr(B, MEM[addr]);
}

void Or_B_A(void){
	B = Orr(B, A);
}

void Or_B_C(void){
	B = Orr(B, C);
}

void Xor_B_Imm(void){
	byte b = ROM[ADRP];
	B = Xor(B, b);
}

void Xor_B_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	B = Xor(B, MEM[addr]);
}

void Xor_B_A(void){
	B = Xor(B, A);
}

void Xor_B_C(void){
	B = Xor(B, C);
}

void Add_C_Imm(void){
	byte b = ROM[ADRP];
	C = Add(C, b);
}

void Add_C_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	C = Add(C, MEM[addr]);
}

void Add_C_B(void){
	C = Add(C, B);
}

void Add_C_A(void){
	C = Add(C, A);
}

void Sub_C_Imm(void){
	byte b = ROM[ADRP];
	C = Sub(C, b);
}

void Sub_C_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	C = Sub(C, MEM[addr]);
}

void Sub_C_B(void){
	C = Sub(C, B);
}

void Sub_C_A(void){
	C = Sub(C, A);
}

void Mul_C_Imm(void){
	byte b = ROM[ADRP];
	C = Mul(C, b);
}

void Mul_C_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	C = Mul(C, MEM[addr]);
}

void Mul_C_B(void){
	C = Mul(C, B);
}

void Mul_C_A(void){
	C = Mul(C, A);
}

void And_C_Imm(void){
	byte b = ROM[ADRP];
	C = And(C, b);
}

void And_C_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	C = And(C, MEM[addr]);
}

void And_C_B(void){
	C = And(C, B);
}

void And_C_A(void){
	C = And(C, A);
}

void Or_C_Imm(void){
	byte b = ROM[ADRP];
	C = Orr(C, b);
}

void Or_C_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	C = Orr(C, MEM[addr]);
}

void Or_C_B(void){
	C = Orr(C, B);
}

void Or_C_A(void){
	C = Orr(C, A);
}

void Xor_C_Imm(void){
	byte b = ROM[ADRP];
	C = Xor(C, b);
}

void Xor_C_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	C = Xor(C, MEM[addr]);
}

void Xor_C_B(void){
	C = Xor(C, B);
}

void Xor_C_A(void){
	C = Xor(C, A);
}

void Not_A(void){
	A = Not(A);
}

void Not_B(void){
	B = Not(B);
}

void Not_C(void){
	C = Not(C);
}

void Not_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	MEM[addr] = Not(MEM[addr]);
}

void Left_Shift_A(void){
	A = Lsh(A);
}

void Right_Shift_A(void){
	A = Rsh(A);
}

void Left_Shift_B(void){
	B = Lsh(B);
}

void Right_Shift_B(void){
	B = Rsh(B);
}

void Left_Shift_C(void){
	C = Lsh(C);
}

void Right_Shift_C(void){
	C = Rsh(C);
}

void Left_Shift_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	MEM[addr] = Lsh(MEM[addr]);
}

void Right_Shift_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	MEM[addr] = Rsh(MEM[addr]);
}

void Inc_A(void){
	A = Inc(A);
}

void Inc_B(void){
	B = Inc(B);
}

void Inc_C(void){
	C = Inc(C);
}

void Inc_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	MEM[addr] = Inc(MEM[addr]);
}

void Dec_A(void){
	A = Dec(A);
}

void Dec_B(void){
	B = Dec(B);
}

void Dec_C(void){
	C = Dec(C);
}

void Dec_Adr(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	MEM[addr] = Dec(MEM[addr]);
}

// Jumps

void Jump_Rel_Imm(void){
	sbyte Imm = ROM[ADDR];
	word addr = ADDR + Imm;
	if(addr >= MAX_ROM){
		FL = FL | FLAG_HALT;
		return;
	}

	ADDR = addr;
}

void Jump_Abs(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADDR];
	word addr = packBytes(h,l);
	if(addr >= MAX_ROM){
		FL = FL | FLAG_HALT;
		return;
	}

	ADDR = addr;
}

void Jump_Zero(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_ROM){
		FL = FL | FLAG_HALT;
		return;
	}
	
	if((FL & FLAG_ZERO) > 0){
		ADDR = addr;
	}
}

void Jump_Over(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_ROM){
		FL = FL | FLAG_HALT;
		return;
	}

	if((FL & FLAG_OVERFLOW) > 0){
		ADDR = addr;
	}
}

void Jump_Under(void){
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_ROM){
		FL = FL | FLAG_HALT;
		return;
	}

	if((FL & FLAG_UNDERFLOW) > 0){
		ADDR = addr;
	}
}

void Jump_Greater(void){
	byte Imm = ROM[ADRP];
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_ROM){
		FL = FL | FLAG_HALT;
		return;
	}

	Sub(A,Imm);
	if(!(FL & (FLAG_UNDERFLOW | FLAG_ZERO))){
		ADDR = addr;
	}

	ADDR = addr;
}

void Jump_Less(void){
	byte Imm = ROM[ADRP];
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_ROM){
		FL = FL | FLAG_HALT;
		return;
	}

	Sub(A,Imm);
	if((FL & FLAG_UNDERFLOW) > 0){
		ADDR = addr;
	}
}

void Jump_Equal(void){
	byte Imm = ROM[ADRP];
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_ROM){
		FL = FL | FLAG_HALT;
		return;
	}

	Sub(A,Imm);

	if((FL & FLAG_ZERO) > 0){
		ADDR = addr;
	}
}

void Store_Imm_Adr(void){
	byte Imm = ROM[ADRP];
	byte h = ROM[ADRP];
	byte l = ROM[ADRP];
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	MEM[addr] = Imm;
}

void Send(void){
	FL = FL | FLAG_INT;
}

#endif