#ifndef DASM_PACK_C
#define DASM_PACK_C
#include <stdio.h>
#include "dasm_cpu.h"
#include "dasm_pack.h"

#ifndef DASM_SET_NON_STATIC_ROM
void PackRom(char* path){
	FILE* file = fopen(path,"wb");
	if(file == NULL){
		printf("Error packing rom\n");
		return;
	}

	fwrite(ROM,sizeof(byte) * MAX_ROM, 1, file);
	fclose(file);
	return;
}

void LoadRom(char* path){
	FILE* file = fopen(path,"rb");
	if(file == NULL){
		printf("Error loading rom\n");
		return;
	}

	fread(ROM,sizeof(byte) * MAX_ROM, 1, file);
	fclose(file);
	return;
}
#endif

#endif