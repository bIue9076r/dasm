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
	A = RomFetch();
}

void Load_A_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	A = GetMem(addr);
}

void Store_A_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	SetMem(addr,A);
}

void Put_A(void){
	StkPut(A);
}

void Pop_A(void){
	A = StkPop();
}

void T_A_B(void){
	B = A;
}

void T_A_C(void){
	C = A;
}

// B

void Load_B_Imm(void){
	B = RomFetch();
}

void Load_B_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	B = GetMem(addr);
}

void Store_B_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	SetMem(addr,B);
}

void Put_B(void){
	StkPut(B);
}

void Pop_B(void){
	B = StkPop();
}

void T_B_A(void){
	A = B;
}

void T_B_C(void){
	C = B;
}

// C

void Load_C_Imm(void){
	C = RomFetch();
}

void Load_C_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	C = GetMem(addr);
}

void Store_C_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	SetMem(addr,C);
}

void Put_C(void){
	StkPut(C);
}

void Pop_C(void){
	C = StkPop();
}

void T_C_A(void){
	A = C;
}

void T_C_B(void){
	B = C;
}

// Operations

void Add_A_Imm(void){
	byte b = RomFetch();
	A = Add(A, b);
}

void Add_A_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	A = Add(A, GetMem(addr));
}

void Add_A_B(void){
	A = Add(A, B);
}

void Add_A_C(void){
	A = Add(A, C);
}

void Sub_A_Imm(void){
	byte b = RomFetch();
	A = Sub(A, b);
}

void Sub_A_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	A = Sub(A, GetMem(addr));
}

void Sub_A_B(void){
	A = Sub(A, B);
}

void Sub_A_C(void){
	A = Sub(A, C);
}

void Mul_A_Imm(void){
	byte b = RomFetch();
	A = Mul(A, b);
}

void Mul_A_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	A = Mul(A, GetMem(addr));
}

void Mul_A_B(void){
	A = Mul(A, B);
}

void Mul_A_C(void){
	A = Mul(A, C);
}

void And_A_Imm(void){
	byte b = RomFetch();
	A = And(A, b);
}

void And_A_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	A = And(A, GetMem(addr));
}

void And_A_B(void){
	A = And(A, B);
}

void And_A_C(void){
	A = And(A, C);
}

void Or_A_Imm(void){
	byte b = RomFetch();
	A = Orr(A, b);
}

void Or_A_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	A = Orr(A, GetMem(addr));
}

void Or_A_B(void){
	A = Orr(A, B);
}

void Or_A_C(void){
	A = Orr(A, C);
}

void Xor_A_Imm(void){
	byte b = RomFetch();
	A = Xor(A, b);
}

void Xor_A_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	A = Xor(A, GetMem(addr));
}

void Xor_A_B(void){
	A = Xor(A, B);
}

void Xor_A_C(void){
	A = Xor(A, C);
}

void Add_B_Imm(void){
	byte b = RomFetch();
	B = Add(B, b);
}

void Add_B_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	B = Add(B, GetMem(addr));
}

void Add_B_A(void){
	B = Add(B, A);
}

void Add_B_C(void){
	B = Add(B, C);
}

void Sub_B_Imm(void){
	byte b = RomFetch();
	B = Sub(B, b);
}

void Sub_B_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	B = Sub(B, GetMem(addr));
}

void Sub_B_A(void){
	B = Sub(B, A);
}

void Sub_B_C(void){
	B = Sub(B, C);
}

void Mul_B_Imm(void){
	byte b = RomFetch();
	B = Mul(B, b);
}

void Mul_B_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	B = Mul(B, GetMem(addr));
}

void Mul_B_A(void){
	B = Mul(B, A);
}

void Mul_B_C(void){
	B = Mul(B, C);
}

void And_B_Imm(void){
	byte b = RomFetch();
	B = And(B, b);
}

void And_B_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	B = And(B, GetMem(addr));
}

void And_B_A(void){
	B = And(B, A);
}

void And_B_C(void){
	B = And(B, C);
}

void Or_B_Imm(void){
	byte b = RomFetch();
	B = Orr(B, b);
}

void Or_B_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	B = Orr(B, GetMem(addr));
}

void Or_B_A(void){
	B = Orr(B, A);
}

void Or_B_C(void){
	B = Orr(B, C);
}

void Xor_B_Imm(void){
	byte b = RomFetch();
	B = Xor(B, b);
}

void Xor_B_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	B = Xor(B, GetMem(addr));
}

void Xor_B_A(void){
	B = Xor(B, A);
}

void Xor_B_C(void){
	B = Xor(B, C);
}

void Add_C_Imm(void){
	byte b = RomFetch();
	C = Add(C, b);
}

void Add_C_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	C = Add(C, GetMem(addr));
}

void Add_C_B(void){
	C = Add(C, B);
}

void Add_C_A(void){
	C = Add(C, A);
}

void Sub_C_Imm(void){
	byte b = RomFetch();
	C = Sub(C, b);
}

void Sub_C_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	C = Sub(C, GetMem(addr));
}

void Sub_C_B(void){
	C = Sub(C, B);
}

void Sub_C_A(void){
	C = Sub(C, A);
}

void Mul_C_Imm(void){
	byte b = RomFetch();
	C = Mul(C, b);
}

void Mul_C_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	C = Mul(C, GetMem(addr));
}

void Mul_C_B(void){
	C = Mul(C, B);
}

void Mul_C_A(void){
	C = Mul(C, A);
}

void And_C_Imm(void){
	byte b = RomFetch();
	C = And(C, b);
}

void And_C_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	C = And(C, GetMem(addr));
}

void And_C_B(void){
	C = And(C, B);
}

void And_C_A(void){
	C = And(C, A);
}

void Or_C_Imm(void){
	byte b = RomFetch();
	C = Orr(C, b);
}

void Or_C_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	C = Orr(C, GetMem(addr));
}

void Or_C_B(void){
	C = Orr(C, B);
}

void Or_C_A(void){
	C = Orr(C, A);
}

void Xor_C_Imm(void){
	byte b = RomFetch();
	C = Xor(C, b);
}

void Xor_C_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	C = Xor(C, GetMem(addr));
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
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	SetMem(addr,Not(GetMem(addr)));
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
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	SetMem(addr,Lsh(GetMem(addr)));
}

void Right_Shift_Adr(void){
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	SetMem(addr,Rsh(GetMem(addr)));
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
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	SetMem(addr,Inc(GetMem(addr)));
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
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	SetMem(addr,Dec(GetMem(addr)));
}

// Jumps

void Jump_Rel_Imm(void){
	sbyte Imm = RomFetchPeek();
	word addr = ADDR + Imm;
	if(addr >= MAX_ROM){
		FL = FL | FLAG_HALT;
		return;
	}

	ADDR = addr;
}

void Jump_Abs(void){
	byte h = RomFetch();
	byte l = RomFetchPeek();
	word addr = packBytes(h,l);
	if(addr >= MAX_ROM){
		FL = FL | FLAG_HALT;
		return;
	}

	ADDR = addr;
}

void Jump_Zero(void){
	byte h = RomFetch();
	byte l = RomFetch();
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
	byte h = RomFetch();
	byte l = RomFetch();
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
	byte h = RomFetch();
	byte l = RomFetch();
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
	byte Imm = RomFetch();
	byte h = RomFetch();
	byte l = RomFetch();
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
	byte Imm = RomFetch();
	byte h = RomFetch();
	byte l = RomFetch();
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
	byte Imm = RomFetch();
	byte h = RomFetch();
	byte l = RomFetch();
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
	byte Imm = RomFetch();
	byte h = RomFetch();
	byte l = RomFetch();
	word addr = packBytes(h,l);
	if(addr >= MAX_MEM){
		FL = FL | FLAG_HALT;
		return;
	}

	SetMem(addr,Imm);
}

void Send(void){
	FL = FL | FLAG_INT;
}

#endif