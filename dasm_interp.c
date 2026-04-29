#include <stdio.h>
#include "dasm_type.h"
#include "dasm_cpu.h"
#include "dasm_alu.h"
#include "dasm_inst_set.h"
#include "dasm_inst_switch.h"

#include "dasm_pack.h"
#include "dasm_inst_str.h"

void Status(void){
	printf("A = 0x%02X\n",A);
	printf("B = 0x%02X\n",B);
	printf("C = 0x%02X\n",C);
	printf("SK = 0x%02X\n",SK);
	printf("ADRR = 0x%04X\n",ADDR);
	printf("FL = 0x%02X\n",FL);
	printf("OZU- -SDH\n");
	printf("%d%d%d%d %d%d%d%d\n",
		(FL & 0x80) >> 7,
		(FL & 0x40) >> 6,
		(FL & 0x20) >> 5,
		(FL & 0x10) >> 4,
		(FL & 0x08) >> 3,
		(FL & 0x04) >> 2,
		(FL & 0x02) >> 1,
		(FL & 0x01)
	);
}

int main(void){
	LoadRom("rom.drom");
	
	while(!(FL & FLAG_HALT)){
		byte inst = RomFetch();
		SwitchInst(inst);
		printf("Inst = %s\n",StrSwitchInst(inst));
		Status();
	}
	return 0;
}
