#ifndef DASM_INST_SWITCH_C
#define DASM_INST_SWITCH_C
#include "dasm_inst_switch.h"

void SwitchInst(byte inst){
	switch(inst){
		case I_NOP:
			Nop();
		break;

		case I_DISP:
			Display();
		break;

		case I_LDAI:
			Load_A_Imm();
		break;

		case I_LDAA:
			Load_A_Adr();
		break;

		case I_STAA:
			Store_A_Adr();
		break;

		case I_PUA:
			Put_A();
		break;

		case I_POA:
			Pop_A();
		break;

		case I_TAB:
			T_A_B();
		break;

		case I_TAC:
			T_A_C();
		break;

		case I_LDBI:
			Load_B_Imm();
		break;

		case I_LDBA:
			Load_B_Adr();
		break;

		case I_STBA:
			Store_B_Adr();
		break;

		case I_PUB:
			Put_B();
		break;

		case I_POB:
			Pop_B();
		break;

		case I_TBA:
			T_B_A();
		break;

		case I_TBC:
			T_B_C();
		break;

		case I_LDCI:
			Load_C_Imm();
		break;

		case I_LDCA:
			Load_C_Adr();
		break;

		case I_STCA:
			Store_C_Adr();
		break;

		case I_PUC:
			Put_C();
		break;

		case I_POC:
			Pop_C();
		break;

		case I_TCB:
			T_C_B();
		break;

		case I_TCA:
			T_C_A();
		break;

		case I_ADAI:
			Add_A_Imm();
		break;

		case I_ADAA:
			Add_A_Adr();
		break;

		case I_ADAB:
			Add_A_B();
		break;

		case I_ADAC:
			Add_A_C();
		break;

		case I_SUAI:
			Sub_A_Imm();
		break;

		case I_SUAA:
			Sub_A_Adr();
		break;

		case I_SUAB:
			Sub_A_B();
		break;

		case I_SUAC:
			Sub_A_C();
		break;

		case I_MUAI:
			Mul_A_Imm();
		break;

		case I_MUAA:
			Mul_A_Adr();
		break;

		case I_MUAB:
			Mul_A_B();
		break;

		case I_MUAC:
			Mul_A_C();
		break;

		case I_ANAI:
			And_A_Imm();
		break;

		case I_ANAA:
			And_A_Adr();
		break;

		case I_ANAB:
			And_A_B();
		break;

		case I_ANAC:
			And_A_C();
		break;

		case I_ORAI:
			Or_A_Imm();
		break;

		case I_ORAA:
			Or_A_Adr();
		break;

		case I_ORAB:
			Or_A_B();
		break;

		case I_ORAC:
			Or_A_C();
		break;

		case I_XOAI:
			Xor_A_Imm();
		break;

		case I_XOAA:
			Xor_A_Adr();
		break;

		case I_XOAB:
			Xor_A_B();
		break;

		case I_XOAC:
			Xor_A_C();
		break;

		case I_ADBI:
			Add_B_Imm();
		break;

		case I_ADBA:
			Add_B_Adr();
		break;

		case I_ADB:
			Add_B_A();
		break;

		case I_ADBC:
			Add_B_C();
		break;

		case I_SUBI:
			Sub_B_Imm();
		break;

		case I_SUBA:
			Sub_B_Adr();
		break;

		case I_SUB:
			Sub_B_A();
		break;

		case I_SUBC:
			Sub_B_C();
		break;

		case I_MUBI:
			Mul_B_Imm();
		break;

		case I_MUBA:
			Mul_B_Adr();
		break;

		case I_MUB:
			Mul_B_A();
		break;

		case I_MUBC:
			Mul_B_C();
		break;

		case I_ANBI:
			And_B_Imm();
		break;

		case I_ANBA:
			And_B_Adr();
		break;

		case I_ANB:
			And_B_A();
		break;

		case I_ANBC:
			And_B_C();
		break;

		case I_ORBI:
			Or_B_Imm();
		break;

		case I_ORBA:
			Or_B_Adr();
		break;

		case I_ORB:
			Or_B_A();
		break;

		case I_ORBC:
			Or_B_C();
		break;

		case I_XOBI:
			Xor_B_Imm();
		break;

		case I_XOBA:
			Xor_B_Adr();
		break;

		case I_XOB:
			Xor_B_A();
		break;

		case I_XOBC:
			Xor_B_C();
		break;

		case I_ADCI:
			Add_C_Imm();
		break;

		case I_ADCA:
			Add_C_Adr();
		break;

		case I_ADCB:
			Add_C_B();
		break;

		case I_ADC:
			Add_C_A();
		break;

		case I_SUCI:
			Sub_C_Imm();
		break;

		case I_SUCA:
			Sub_C_Adr();
		break;

		case I_SUCB:
			Sub_C_B();
		break;

		case I_SUC:
			Sub_C_A();
		break;

		case I_MUCI:
			Mul_C_Imm();
		break;

		case I_MUCA:
			Mul_C_Adr();
		break;

		case I_MUCB:
			Mul_C_B();
		break;

		case I_MUC:
			Mul_C_A();
		break;

		case I_ANCI:
			And_C_Imm();
		break;

		case I_ANCA:
			And_C_Adr();
		break;

		case I_ANCB:
			And_C_B();
		break;

		case I_ANC:
			And_C_A();
		break;

		case I_ORCI:
			Or_C_Imm();
		break;

		case I_ORCA:
			Or_C_Adr();
		break;

		case I_ORCB:
			Or_C_B();
		break;

		case I_ORC:
			Or_C_A();
		break;

		case I_XOCI:
			Xor_C_Imm();
		break;

		case I_XOCA:
			Xor_C_Adr();
		break;

		case I_XOCB:
			Xor_C_B();
		break;

		case I_XOC:
			Xor_C_A();
		break;

		case I_NOT:
			Not_A();
		break;

		case I_NOTB:
			Not_B();
		break;

		case I_NOTC:
			Not_C();
		break;

		case I_NOTA:
			Not_Adr();
		break;

		case I_LSH:
			Left_Shift_A();
		break;

		case I_RSH:
			Right_Shift_A();
		break;

		case I_LSHB:
			Left_Shift_B();
		break;

		case I_RSHB:
			Right_Shift_B();
		break;

		case I_LSHC:
			Left_Shift_C();
		break;

		case I_RSHC:
			Right_Shift_C();
		break;

		case I_LSHA:
			Left_Shift_Adr();
		break;

		case I_RSHA:
			Right_Shift_Adr();
		break;

		case I_INC:
			Inc_A();
		break;

		case I_INCB:
			Inc_B();
		break;

		case I_INCC:
			Inc_C();
		break;

		case I_INCA:
			Inc_Adr();
		break;

		case I_DEC:
			Dec_A();
		break;

		case I_DECB:
			Dec_B();
		break;

		case I_DECC:
			Dec_C();
		break;

		case I_DECA:
			Dec_Adr();
		break;

		case I_JREL:
			Jump_Rel_Imm();
		break;

		case I_JUMP:
			Jump_Abs();
		break;

		case I_JZER:
			Jump_Zero();
		break;

		case I_JOVR:
			Jump_Over();
		break;

		case I_JUDR:
			Jump_Under();
		break;

		case I_JGTR:
			Jump_Greater();
		break;

		case I_JLES:
			Jump_Less();
		break;

		case I_JEQU:
			Jump_Equal();
		break;

		case I_STIA:
			Store_Imm_Adr();
		break;

		case I_SEND:
			Send();
		break;

		case I_CALL:
			Call();
		break;

		case I_RET:
			Ret();
		break;


		default:
			FL = FL | FLAG_HALT;
		break;
	}
}

#endif