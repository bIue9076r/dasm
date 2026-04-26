#ifndef DASM_INST_STR_H
#define DASM_INST_STR_H
#include "dasm_inst_set.h"
#include "dasm_inst_switch.h"

extern char* INST_STRS[0x100];
char* StrSwitchInst(byte inst);

#endif