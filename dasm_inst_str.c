#ifndef DASM_INST_STR_C
#define DASM_INST_STR_C
#include "dasm_inst_str.h"

char* INST_STRS[0x100] = {
	"NOP","DISP","LDAI", "LDAA", "STAA", "PUA", "POA", "TAB", "TAC", "LDBI",
	"LDBA", "STBA", "PUB", "POB", "TBA", "TBC", "LDCI", "LDCA", "STCA", "PUC",
	"POC", "TCB", "TCA", "ADAI", "ADAA", "ADAB", "ADAC", "SUAI", "SUAA", "SUAB",
	"SUAC", "MUAI", "MUAA", "MUAB", "MUAC", "ANAI", "ANAA", "ANAB", "ANAC", "ORAI",
	"ORAA", "ORAB", "ORAC", "XOAI", "XOAA", "XOAB", "XOAC", "ADBI", "ADBA", "ADB",
	"ADBC", "SUBI", "SUBA", "SUB", "SUBC", "MUBI", "MUBA", "MUB", "MUBC", "ANBI",
	"ANBA", "ANB", "ANBC", "ORBI", "ORBA", "ORB", "ORBC", "XOBI", "XOBA", "XOB",
	"XOBC", "ADCI", "ADCA", "ADCB", "ADC", "SUCI", "SUCA", "SUCB", "SUC", "MUCI",
	"MUCA", "MUCB", "MUC", "ANCI", "ANCA", "ANCB", "ANC", "ORCI", "ORCA", "ORCB",
	"ORC", "XOCI", "XOCA", "XOCB", "XOC", "NOT", "NOTB", "NOTC", "NOTA", "LSH",
	"RSH", "LSHB", "RSHB", "LSHC", "RSHC", "LSHA", "RSHA", "INC", "INCB", "INCC",
	"INCA", "DEC", "DECB", "DECC", "DECA", "JREL", "JUMP", "JZER", "JOVR", "JUDR",
	"JGTR", "JLES", "JEQU", "STIA",
};

char* StrSwitchInst(byte inst){
	if(inst > I_STIA){
		return "HALT";
	}

	return INST_STRS[inst];
}

#endif