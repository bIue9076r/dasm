#include <stdio.h>
#include <stdlib.h>
#include "dasm_type.h"
#include "dasm_cpu.h"
#include "dasm_alu.h"
#include "dasm_inst_set.h"
#include "dasm_inst_switch.h"
#include "dasm_pack.h"

#define INVALID_LABEL 0x5000

typedef struct inst_s {
	char* inst;
	char* arg1;
	char* arg2;
} inst_t;

typedef struct label_s {
	char* Name;
	word position;
} label_t;

typedef struct macro_s {
	char* Name;
	word value;
} macro_t;

typedef struct context_s {
	int inst_size;
	int labels_size;
	int macros_size;
	inst_t* inst_list;
	label_t* labels;
	macro_t* macros;
} context_t;

void appendInstuction(context_t* ctx, char* inst, char* arg1, char* arg2){
	inst_t* temp = malloc((ctx->inst_size + 1) * sizeof(inst_t));
	
	for(int i = 0; i < ctx->inst_size; i++){
		temp[i].inst = ctx->inst_list[i].inst;
		temp[i].arg1 = ctx->inst_list[i].arg1;
		temp[i].arg2 = ctx->inst_list[i].arg2;
	}

	temp[ctx->inst_size].inst = inst;
	temp[ctx->inst_size].arg1 = arg1;
	temp[ctx->inst_size].arg2 = arg2;
	
	free(ctx->inst_list);
	ctx->inst_list = temp;
	ctx->inst_size++;
}

void appendLabel(context_t* ctx, char* name, word pos){
	label_t* temp = malloc((ctx->labels_size + 1) * sizeof(label_t));
	
	for(int i = 0; i < ctx->labels_size; i++){
		temp[i].Name = ctx->labels[i].Name;
		temp[i].position = ctx->labels[i].position;
	}

	temp[ctx->labels_size].Name = name;
	temp[ctx->labels_size].position = pos;
	
	free(ctx->labels);
	ctx->labels = temp;
	ctx->labels_size++;
}

void appendMacro(context_t* ctx, char* name, word val){
	macro_t* temp = malloc((ctx->macros_size + 1) * sizeof(macro_t));
	
	for(int i = 0; i < ctx->macros_size; i++){
		temp[i].Name = ctx->macros[i].Name;
		temp[i].value = ctx->macros[i].value;
	}

	temp[ctx->macros_size].Name = name;
	temp[ctx->macros_size].value = val;
	
	free(ctx->macros);
	ctx->macros = temp;
	ctx->macros_size++;
}

void freeContext(context_t* ctx){
	for(int i = 0; i < ctx->inst_size; i++){
		if(ctx->inst_list[i].inst != NULL){
			free(ctx->inst_list[i].inst);
		}
		if(ctx->inst_list[i].arg1 != NULL){
			free(ctx->inst_list[i].arg1);
		}
		if(ctx->inst_list[i].arg2 != NULL){
			free(ctx->inst_list[i].arg2);
		}
	}
	if(ctx->inst_list != NULL){
		free(ctx->inst_list);
	}

	for(int i = 0; i < ctx->labels_size; i++){
		if(ctx->labels[i].Name != NULL){
			// Labels resuse instruction name
			// free(ctx->labels[i].Name);
		}
	}
	if(ctx->labels != NULL){
		free(ctx->labels);
	}

	for(int i = 0; i < ctx->macros_size; i++){
		if(ctx->macros[i].Name != NULL){
			free(ctx->macros[i].Name);
		}
	}
	if(ctx->macros != NULL){
		free(ctx->macros);
	}

}

// POP A;			# 0x06
// LDD A, 10;		# 0x02 0x10
// STR A, 1000;		# 0x04 0x10 0x00
// JEQ 0x00 1000;	# 0x7A 0x00 0x10 0x00

// LDD
// POP
// PUT
// STR

// TAB
// TAC
// TBA
// TBC
// TCA
// TCB

// ADD
// SUB
// MUL
// ORR
// XOR
// NOT
// LSH
// RSH
// INC
// DEC

// JRE
// JMP
// JZE
// JUN
// JOV
// JLT
// JGT
// JEQ

#define INSTN_NOP 0xFFDD0067
#define INSTN_DIS 0xFFE32020
#define INSTN_HLT 0xFFDFC7BD
#define INSTN_LDD 0xFFE50939
#define INSTN_POP 0xFFDBBCB7
#define INSTN_PUT 0xFFD889A7
#define INSTN_STR 0xFFD79DD3
#define INSTN_TAB 0xFFE2408D
#define INSTN_TAC 0xFFE1D300
#define INSTN_TBA 0xFFE27E9C
#define INSTN_TBC 0xFFE1A212
#define INSTN_TCA 0xFFE2511A
#define INSTN_TCB 0xFFE1E231
#define INSTN_ADD 0xFFEA5567
#define INSTN_SUB 0xFFDEFF14
#define INSTN_MUL 0xFFDDFE26
#define INSTN_ORR 0xFFDAC3E9
#define INSTN_XOR 0xFFD57BD1
#define INSTN_NOT 0xFFDB532B
#define INSTN_LSH 0xFFE0AEBF
#define INSTN_RSH 0xFFDD2967
#define INSTN_INC 0xFFE53792
#define INSTN_DEC 0xFFE91A48
#define INSTN_JRE 0xFFE33086
#define INSTN_JMP 0xFFDFDA47
#define INSTN_JZE 0xFFE1C506
#define INSTN_JUN 0xFFDF08ED
#define INSTN_JOV 0xFFDD221D
#define INSTN_JLT 0xFFDE881B
#define INSTN_JGT 0xFFDF9DD3
#define INSTN_JEQ 0xFFE11F3A

int upper(char c){
	return (c >= 'a' && c <= 'z')?(c - 32):(c);
}

int lower(char c){
	return (c >= 'A' && c <= 'Z')?(c + 32):(c);
}

int isAlphabet(char c){
	return (c >= 'A' && c <= 'Z');
}

int32_t stn(char* str){
	int32_t r = 0xFFFFFFFF;
	int32_t p = 0;
	for(int i = 0; str[i] != 0; i++){
		char c = upper(str[i]);
		if(isAlphabet(c)){
			r = 2*(p + r) + (r ^ (p + 1)*c) + r*r*(p - 2) + i*2*r - ~(i*r*c);
			p++;
		}
	}
	return (r + p);
}

#define MODE_DEC 1
#define MODE_HEX 2
#define MODE_BIN 3

word parseWord(char* str){
	// 0x10
	// 0b10
	// 10
	word ret = 0;
	int mode = MODE_DEC;
	int mode_set = 0;
	int sign = 1;
	if(*str == '-'){
		sign = -1;
		str++;
	}

	if(*str == '0'){
		str++;
		if(lower(*str) == 'x'){
			mode = MODE_HEX;
		}

		if(lower(*str) == 'b'){
			mode = MODE_BIN;
		}
	}

	while(*str != 0){
		char c = *str;
		switch(mode){
			case MODE_DEC:
				if(c >= '0' && c <= '9'){
					ret = ret * 10;
					ret = ret + (c - '0');
				}
			break;

			case MODE_HEX:
				if(c >= '0' && c <= '9'){
					ret = ret * 16;
					ret = ret + (c - '0');
				}

				if(c >= 'A' && c <= 'F'){
					ret = ret * 16;
					ret = ret + 10 + (c - 'A');
				}
			break;

			case MODE_BIN:
				if(c >= '0' && c <= '1'){
					ret = ret * 2;
					ret = ret + (c - '0');
				}
			break;
		}
		
		str++;
	}
	
	return sign*ret;
}

int checkInst(char* inst){
	switch(stn(inst)){
		case INSTN_NOP:
		case INSTN_DIS:
		case INSTN_HLT:
		case INSTN_LDD:
		case INSTN_POP:
		case INSTN_PUT:
		case INSTN_STR:
		case INSTN_TAB:
		case INSTN_TAC:
		case INSTN_TBA:
		case INSTN_TBC:
		case INSTN_TCA:
		case INSTN_TCB:
		case INSTN_ADD:
		case INSTN_SUB:
		case INSTN_MUL:
		case INSTN_ORR:
		case INSTN_XOR:
		case INSTN_NOT:
		case INSTN_LSH:
		case INSTN_RSH:
		case INSTN_INC:
		case INSTN_DEC:
		case INSTN_JRE:
		case INSTN_JMP:
		case INSTN_JZE:
		case INSTN_JUN:
		case INSTN_JOV:
		case INSTN_JLT:
		case INSTN_JGT:
		case INSTN_JEQ:
			return 1;
		break;

		default:
			// Check if label
			while(*inst != 0){
				if(*(inst + 1) == 0 && (*inst == ':')){
					return 2;
				}
				inst++;
			}
			
			return -1;
		break;
	}
}

int expandContext(context_t* ctx){
	word position = 0x00;
	char* inst = NULL;
	char* arg1 = NULL;
	char* arg2 = NULL;

	for(int i = 0; i < ctx->inst_size; i++){
		printf("[%s] [%s], [%s];\n",
			ctx->inst_list[i].inst,
			ctx->inst_list[i].arg1,
			ctx->inst_list[i].arg2
		);

		inst = ctx->inst_list[i].inst;
		arg1 = ctx->inst_list[i].arg1;
		arg2 = ctx->inst_list[i].arg2;
		if(arg2 != NULL){
			int arg2_n = stn(arg2);
			int arg1_n = stn(arg1);
			int inst_n = stn(inst);
			char arg2_f = upper(arg2[0]);
			char arg1_f = upper(arg1[0]);
			word val1 = 0x0;
			word val2 = 0x0;
			switch(inst_n){
				case INSTN_NOP: case INSTN_DIS: case INSTN_HLT:
				case INSTN_TAB: case INSTN_TAC: case INSTN_TBA:
				case INSTN_TBC: case INSTN_TCA: case INSTN_TCB:
				case INSTN_POP: case INSTN_PUT: case INSTN_NOT:
				case INSTN_LSH: case INSTN_RSH: case INSTN_INC:
				case INSTN_DEC: case INSTN_JRE: case INSTN_JMP:
					printf("Syntax Error: [%s] has less arguments\n",inst);
					return -1;
				break;

				case INSTN_LDD:
					if(arg1_f >= 'A' && arg1_f <= 'C'){
						val1 = parseWord(arg2);
						for(int i = 0; i < ctx->macros_size; i++){
							if(stn(ctx->macros[i].Name) == arg2_n){
								val1 = ctx->macros[i].value;
							}
						}

						switch(arg1_f){
							case 'A':
								if(val1 < 0x100){
									ROM[position++] = I_LDAI;
									ROM[position++] = lowbyte(val1);
								}else{
									ROM[position++] = I_LDAA;
									ROM[position++] = highbyte(val1);
									ROM[position++] = lowbyte(val1);
								}
							break;

							case 'B':
								if(val1 < 0x100){
									ROM[position++] = I_LDBI;
									ROM[position++] = lowbyte(val1);
								}else{
									ROM[position++] = I_LDBA;
									ROM[position++] = highbyte(val1);
									ROM[position++] = lowbyte(val1);
								}
							break;

							case 'C':
								if(val1 < 0x100){
									ROM[position++] = I_LDCI;
									ROM[position++] = lowbyte(val1);
								}else{
									ROM[position++] = I_LDCA;
									ROM[position++] = highbyte(val1);
									ROM[position++] = lowbyte(val1);
								}
							break;
						}
					}else{
						printf("Syntax Error: [%s] has only register 1st position arguments\n",inst);
						return -1;
					}
				break;

				case INSTN_STR:
					val1 = parseWord(arg1);
					for(int i = 0; i < ctx->macros_size; i++){
						if(stn(ctx->macros[i].Name) == arg1_n){
							val1 = ctx->macros[i].value;
						}
					}

					val2 = parseWord(arg2);
					for(int i = 0; i < ctx->macros_size; i++){
						if(stn(ctx->macros[i].Name) == arg2_n){
							val2 = ctx->macros[i].value;
						}
					}

					if(arg1_f >= 'A' && arg1_f <= 'C'){
						switch(arg1_f){
							case 'A':
								ROM[position++] = I_STAA;
							break;

							case 'B':
								ROM[position++] = I_STBA;
							break;

							case 'C':
								ROM[position++] = I_STCA;
							break;
						}
						ROM[position++] = highbyte(val2);
						ROM[position++] = lowbyte(val2);
					}else{
						ROM[position++] = I_STIA;
						ROM[position++] = lowbyte(val1);
						ROM[position++] = highbyte(val2);
						ROM[position++] = lowbyte(val2);
					}
				break;

				case INSTN_ADD:
					if(arg1_f >= 'A' && arg1_f <= 'C'){
						val1 = parseWord(arg2);
						for(int i = 0; i < ctx->macros_size; i++){
							if(stn(ctx->macros[i].Name) == arg2_n){
								val1 = ctx->macros[i].value;
							}
						}

						switch(arg1_f){
							case 'A':
								if(arg2_f >= 'A' && arg2_f <= 'C'){
									switch(arg2_f){
										case 'A':
											printf("Syntax Error: [%s] cannot add register to self\n",inst);
											return -1;
										break;

										case 'B':
											ROM[position++] = I_ADAB;
										break;

										case 'C':
											ROM[position++] = I_ADAC;
										break;
									}
								}else{
									if(val1 < 0x100){
										ROM[position++] = I_ADAI;
										ROM[position++] = lowbyte(val1);
									}else{
										ROM[position++] = I_ADAA;
										ROM[position++] = highbyte(val1);
										ROM[position++] = lowbyte(val1);
									}
								}
							break;

							case 'B':
								if(arg2_f >= 'A' && arg2_f <= 'C'){
									switch(arg2_f){
										case 'A':
											ROM[position++] = I_ADBA;
										break;

										case 'B':
											printf("Syntax Error: [%s] cannot add register to self\n",inst);
											return -1;
										break;

										case 'C':
											ROM[position++] = I_ADBC;
										break;
									}
								}else{
									if(val1 < 0x100){
										ROM[position++] = I_ADBI;
										ROM[position++] = lowbyte(val1);
									}else{
										ROM[position++] = I_ADBA;
										ROM[position++] = highbyte(val1);
										ROM[position++] = lowbyte(val1);
									}
								}
							break;

							case 'C':
								if(arg2_f >= 'A' && arg2_f <= 'C'){
									switch(arg2_f){
										case 'A':
											ROM[position++] = I_ADCA;
										break;

										case 'B':
											ROM[position++] = I_ADCB;
										break;

										case 'C':
											printf("Syntax Error: [%s] cannot add register to self\n",inst);
											return -1;
										break;
									}
								}else{
									if(val1 < 0x100){
										ROM[position++] = I_ADCI;
										ROM[position++] = lowbyte(val1);
									}else{
										ROM[position++] = I_ADCA;
										ROM[position++] = highbyte(val1);
										ROM[position++] = lowbyte(val1);
									}
								}
							break;
						}
					}else{
						printf("Syntax Error: [%s] has only register 1st position arguments\n",inst);
						return -1;
					}
				break;

				case INSTN_SUB:
					if(arg1_f >= 'A' && arg1_f <= 'C'){
						val1 = parseWord(arg2);
						for(int i = 0; i < ctx->macros_size; i++){
							if(stn(ctx->macros[i].Name) == arg2_n){
								val1 = ctx->macros[i].value;
							}
						}

						switch(arg1_f){
							case 'A':
								if(arg2_f >= 'A' && arg2_f <= 'C'){
									switch(arg2_f){
										case 'A':
											printf("Syntax Error: [%s] cannot sub register to self\n",inst);
											return -1;
										break;

										case 'B':
											ROM[position++] = I_SUAB;
										break;

										case 'C':
											ROM[position++] = I_SUAC;
										break;
									}
								}else{
									if(val1 < 0x100){
										ROM[position++] = I_SUAI;
										ROM[position++] = lowbyte(val1);
									}else{
										ROM[position++] = I_SUAA;
										ROM[position++] = highbyte(val1);
										ROM[position++] = lowbyte(val1);
									}
								}
							break;

							case 'B':
								if(arg2_f >= 'A' && arg2_f <= 'C'){
									switch(arg2_f){
										case 'A':
											ROM[position++] = I_SUBA;
										break;

										case 'B':
											printf("Syntax Error: [%s] cannot sub register to self\n",inst);
											return -1;
										break;

										case 'C':
											ROM[position++] = I_SUBC;
										break;
									}
								}else{
									if(val1 < 0x100){
										ROM[position++] = I_SUBI;
										ROM[position++] = lowbyte(val1);
									}else{
										ROM[position++] = I_SUBA;
										ROM[position++] = highbyte(val1);
										ROM[position++] = lowbyte(val1);
									}
								}
							break;

							case 'C':
								if(arg2_f >= 'A' && arg2_f <= 'C'){
									switch(arg2_f){
										case 'A':
											ROM[position++] = I_SUCA;
										break;

										case 'B':
											ROM[position++] = I_SUCB;
										break;

										case 'C':
											printf("Syntax Error: [%s] cannot sub register to self\n",inst);
											return -1;
										break;
									}
								}else{
									if(val1 < 0x100){
										ROM[position++] = I_SUCI;
										ROM[position++] = lowbyte(val1);
									}else{
										ROM[position++] = I_SUCA;
										ROM[position++] = highbyte(val1);
										ROM[position++] = lowbyte(val1);
									}
								}
							break;
						}
					}else{
						printf("Syntax Error: [%s] has only register 1st position arguments\n",inst);
						return -1;
					}
				break;

				case INSTN_MUL:
					if(arg1_f >= 'A' && arg1_f <= 'C'){
						val1 = parseWord(arg2);
						for(int i = 0; i < ctx->macros_size; i++){
							if(stn(ctx->macros[i].Name) == arg2_n){
								val1 = ctx->macros[i].value;
							}
						}

						switch(arg1_f){
							case 'A':
								if(arg2_f >= 'A' && arg2_f <= 'C'){
									switch(arg2_f){
										case 'A':
											printf("Syntax Error: [%s] cannot mul register to self\n",inst);
											return -1;
										break;

										case 'B':
											ROM[position++] = I_MUAB;
										break;

										case 'C':
											ROM[position++] = I_MUAC;
										break;
									}
								}else{
									if(val1 < 0x100){
										ROM[position++] = I_MUAI;
										ROM[position++] = lowbyte(val1);
									}else{
										ROM[position++] = I_MUAA;
										ROM[position++] = highbyte(val1);
										ROM[position++] = lowbyte(val1);
									}
								}
							break;

							case 'B':
								if(arg2_f >= 'A' && arg2_f <= 'C'){
									switch(arg2_f){
										case 'A':
											ROM[position++] = I_MUBA;
										break;

										case 'B':
											printf("Syntax Error: [%s] cannot mul register to self\n",inst);
											return -1;
										break;

										case 'C':
											ROM[position++] = I_MUBC;
										break;
									}
								}else{
									if(val1 < 0x100){
										ROM[position++] = I_MUBI;
										ROM[position++] = lowbyte(val1);
									}else{
										ROM[position++] = I_MUBA;
										ROM[position++] = highbyte(val1);
										ROM[position++] = lowbyte(val1);
									}
								}
							break;

							case 'C':
								if(arg2_f >= 'A' && arg2_f <= 'C'){
									switch(arg2_f){
										case 'A':
											ROM[position++] = I_MUCA;
										break;

										case 'B':
											ROM[position++] = I_MUCB;
										break;

										case 'C':
											printf("Syntax Error: [%s] cannot mul register to self\n",inst);
											return -1;
										break;
									}
								}else{
									if(val1 < 0x100){
										ROM[position++] = I_MUCI;
										ROM[position++] = lowbyte(val1);
									}else{
										ROM[position++] = I_MUCA;
										ROM[position++] = highbyte(val1);
										ROM[position++] = lowbyte(val1);
									}
								}
							break;
						}
					}else{
						printf("Syntax Error: [%s] has only register 1st position arguments\n",inst);
						return -1;
					}
				break;

				case INSTN_ORR:
					if(arg1_f >= 'A' && arg1_f <= 'C'){
						val1 = parseWord(arg2);
						for(int i = 0; i < ctx->macros_size; i++){
							if(stn(ctx->macros[i].Name) == arg2_n){
								val1 = ctx->macros[i].value;
							}
						}

						switch(arg1_f){
							case 'A':
								if(arg2_f >= 'A' && arg2_f <= 'C'){
									switch(arg2_f){
										case 'A':
											printf("Syntax Error: [%s] cannot or register to self\n",inst);
											return -1;
										break;

										case 'B':
											ROM[position++] = I_ORAB;
										break;

										case 'C':
											ROM[position++] = I_ORAC;
										break;
									}
								}else{
									if(val1 < 0x100){
										ROM[position++] = I_ORAI;
										ROM[position++] = lowbyte(val1);
									}else{
										ROM[position++] = I_ORAA;
										ROM[position++] = highbyte(val1);
										ROM[position++] = lowbyte(val1);
									}
								}
							break;

							case 'B':
								if(arg2_f >= 'A' && arg2_f <= 'C'){
									switch(arg2_f){
										case 'A':
											ROM[position++] = I_ORBA;
										break;

										case 'B':
											printf("Syntax Error: [%s] cannot or register to self\n",inst);
											return -1;
										break;

										case 'C':
											ROM[position++] = I_ORBC;
										break;
									}
								}else{
									if(val1 < 0x100){
										ROM[position++] = I_ORBI;
										ROM[position++] = lowbyte(val1);
									}else{
										ROM[position++] = I_ORBA;
										ROM[position++] = highbyte(val1);
										ROM[position++] = lowbyte(val1);
									}
								}
							break;

							case 'C':
								if(arg2_f >= 'A' && arg2_f <= 'C'){
									switch(arg2_f){
										case 'A':
											ROM[position++] = I_ORCA;
										break;

										case 'B':
											ROM[position++] = I_ORCB;
										break;

										case 'C':
											printf("Syntax Error: [%s] cannot or register to self\n",inst);
											return -1;
										break;
									}
								}else{
									if(val1 < 0x100){
										ROM[position++] = I_ORCI;
										ROM[position++] = lowbyte(val1);
									}else{
										ROM[position++] = I_ORCA;
										ROM[position++] = highbyte(val1);
										ROM[position++] = lowbyte(val1);
									}
								}
							break;
						}
					}else{
						printf("Syntax Error: [%s] has only register 1st position arguments\n",inst);
						return -1;
					}
				break;

				case INSTN_XOR:
					if(arg1_f >= 'A' && arg1_f <= 'C'){
						val1 = parseWord(arg2);
						for(int i = 0; i < ctx->macros_size; i++){
							if(stn(ctx->macros[i].Name) == arg2_n){
								val1 = ctx->macros[i].value;
							}
						}

						switch(arg1_f){
							case 'A':
								if(arg2_f >= 'A' && arg2_f <= 'C'){
									switch(arg2_f){
										case 'A':
											printf("Syntax Error: [%s] cannot xor register to self\n",inst);
											return -1;
										break;

										case 'B':
											ROM[position++] = I_XOAB;
										break;

										case 'C':
											ROM[position++] = I_XOAC;
										break;
									}
								}else{
									if(val1 < 0x100){
										ROM[position++] = I_XOAI;
										ROM[position++] = lowbyte(val1);
									}else{
										ROM[position++] = I_XOAA;
										ROM[position++] = highbyte(val1);
										ROM[position++] = lowbyte(val1);
									}
								}
							break;

							case 'B':
								if(arg2_f >= 'A' && arg2_f <= 'C'){
									switch(arg2_f){
										case 'A':
											ROM[position++] = I_XOBA;
										break;

										case 'B':
											printf("Syntax Error: [%s] cannot xor register to self\n",inst);
											return -1;
										break;

										case 'C':
											ROM[position++] = I_XOBC;
										break;
									}
								}else{
									if(val1 < 0x100){
										ROM[position++] = I_XOBI;
										ROM[position++] = lowbyte(val1);
									}else{
										ROM[position++] = I_XOBA;
										ROM[position++] = highbyte(val1);
										ROM[position++] = lowbyte(val1);
									}
								}
							break;

							case 'C':
								if(arg2_f >= 'A' && arg2_f <= 'C'){
									switch(arg2_f){
										case 'A':
											ROM[position++] = I_XOCA;
										break;

										case 'B':
											ROM[position++] = I_XOCB;
										break;

										case 'C':
											printf("Syntax Error: [%s] cannot xor register to self\n",inst);
											return -1;
										break;
									}
								}else{
									if(val1 < 0x100){
										ROM[position++] = I_XOCI;
										ROM[position++] = lowbyte(val1);
									}else{
										ROM[position++] = I_XOCA;
										ROM[position++] = highbyte(val1);
										ROM[position++] = lowbyte(val1);
									}
								}
							break;
						}
					}else{
						printf("Syntax Error: [%s] has only register 1st position arguments\n",inst);
						return -1;
					}
				break;

				case INSTN_JZE:
					val1 = parseWord(arg1);
					for(int i = 0; i < ctx->macros_size; i++){
						if(stn(ctx->macros[i].Name) == arg1_n){
							val1 = ctx->macros[i].value;
						}
					}

					val2 = parseWord(arg2);
					for(int i = 0; i < ctx->macros_size; i++){
						if(stn(ctx->macros[i].Name) == arg2_n){
							val2 = ctx->macros[i].value;
						}
					}

					for(int i = 0; i < ctx->labels_size; i++){
						if(stn(ctx->labels[i].Name) == arg2_n){
							val2 = ctx->labels[i].position;
						}
					}

					ROM[position++] = I_JZER;
					ROM[position++] = lowbyte(val1);
					ROM[position++] = highbyte(val1);
					ROM[position++] = lowbyte(val1);
				break;

				case INSTN_JUN:
					val1 = parseWord(arg1);
					for(int i = 0; i < ctx->macros_size; i++){
						if(stn(ctx->macros[i].Name) == arg1_n){
							val1 = ctx->macros[i].value;
						}
					}

					val2 = parseWord(arg2);
					for(int i = 0; i < ctx->macros_size; i++){
						if(stn(ctx->macros[i].Name) == arg2_n){
							val2 = ctx->macros[i].value;
						}
					}

					for(int i = 0; i < ctx->labels_size; i++){
						if(stn(ctx->labels[i].Name) == arg2_n){
							val2 = ctx->labels[i].position;
						}
					}

					ROM[position++] = I_JUDR;
					ROM[position++] = lowbyte(val1);
					ROM[position++] = highbyte(val1);
					ROM[position++] = lowbyte(val1);
				break;

				case INSTN_JOV:
					val1 = parseWord(arg1);
					for(int i = 0; i < ctx->macros_size; i++){
						if(stn(ctx->macros[i].Name) == arg1_n){
							val1 = ctx->macros[i].value;
						}
					}

					val2 = parseWord(arg2);
					for(int i = 0; i < ctx->macros_size; i++){
						if(stn(ctx->macros[i].Name) == arg2_n){
							val2 = ctx->macros[i].value;
						}
					}

					for(int i = 0; i < ctx->labels_size; i++){
						if(stn(ctx->labels[i].Name) == arg2_n){
							val2 = ctx->labels[i].position;
						}
					}

					ROM[position++] = I_JOVR;
					ROM[position++] = lowbyte(val1);
					ROM[position++] = highbyte(val1);
					ROM[position++] = lowbyte(val1);
				break;

				case INSTN_JLT:
					val1 = parseWord(arg1);
					for(int i = 0; i < ctx->macros_size; i++){
						if(stn(ctx->macros[i].Name) == arg1_n){
							val1 = ctx->macros[i].value;
						}
					}

					val2 = parseWord(arg2);
					for(int i = 0; i < ctx->macros_size; i++){
						if(stn(ctx->macros[i].Name) == arg2_n){
							val2 = ctx->macros[i].value;
						}
					}

					for(int i = 0; i < ctx->labels_size; i++){
						if(stn(ctx->labels[i].Name) == arg2_n){
							val2 = ctx->labels[i].position;
						}
					}

					ROM[position++] = I_JLES;
					ROM[position++] = lowbyte(val1);
					ROM[position++] = highbyte(val1);
					ROM[position++] = lowbyte(val1);
				break;

				case INSTN_JGT:
					val1 = parseWord(arg1);
					for(int i = 0; i < ctx->macros_size; i++){
						if(stn(ctx->macros[i].Name) == arg1_n){
							val1 = ctx->macros[i].value;
						}
					}

					val2 = parseWord(arg2);
					for(int i = 0; i < ctx->macros_size; i++){
						if(stn(ctx->macros[i].Name) == arg2_n){
							val2 = ctx->macros[i].value;
						}
					}

					for(int i = 0; i < ctx->labels_size; i++){
						if(stn(ctx->labels[i].Name) == arg2_n){
							val2 = ctx->labels[i].position;
						}
					}

					ROM[position++] = I_JGTR;
					ROM[position++] = lowbyte(val1);
					ROM[position++] = highbyte(val1);
					ROM[position++] = lowbyte(val1);
				break;

				case INSTN_JEQ:
					val1 = parseWord(arg1);
					for(int i = 0; i < ctx->macros_size; i++){
						if(stn(ctx->macros[i].Name) == arg1_n){
							val1 = ctx->macros[i].value;
						}
					}

					val2 = parseWord(arg2);
					for(int i = 0; i < ctx->macros_size; i++){
						if(stn(ctx->macros[i].Name) == arg2_n){
							val2 = ctx->macros[i].value;
						}
					}

					for(int i = 0; i < ctx->labels_size; i++){
						if(stn(ctx->labels[i].Name) == arg2_n){
							val2 = ctx->labels[i].position;
						}
					}

					ROM[position++] = I_JEQU;
					ROM[position++] = lowbyte(val1);
					ROM[position++] = highbyte(val1);
					ROM[position++] = lowbyte(val1);
				break;
			}
			continue;
		}

		if(arg1 != NULL){
			int arg1_n = stn(arg1);
			int inst_n = stn(inst);
			char arg1_f = upper(arg1[0]);
			word val = 0x0;
			switch(inst_n){
				case INSTN_NOP: case INSTN_DIS: case INSTN_HLT:
				case INSTN_TAB: case INSTN_TAC: case INSTN_TBA:
				case INSTN_TBC: case INSTN_TCA: case INSTN_TCB:
					printf("Syntax Error: [%s] has less arguments\n",inst);
					return -1;
				break;

				case INSTN_POP:
					if(arg1_f >= 'A' && arg1_f <= 'C'){
						switch(arg1_f){
							case 'A':
								ROM[position++] = I_POA;
							break;

							case 'B':
								ROM[position++] = I_POB;
							break;

							case 'C':
								ROM[position++] = I_POC;
							break;
						}
					}else{
						printf("Syntax Error: [%s] has only register arguments\n",inst);
						return -1;
					}
				break;

				case INSTN_PUT:
					if(arg1_f >= 'A' && arg1_f <= 'C'){
						switch(arg1_f){
							case 'A':
								ROM[position++] = I_PUA;
							break;

							case 'B':
								ROM[position++] = I_PUB;
							break;

							case 'C':
								ROM[position++] = I_PUC;
							break;
						}
					}else{
						printf("Syntax Error: [%s] has only register arguments\n",inst);
						return -1;
					}
				break;

				case INSTN_NOT:
					if(arg1_f >= 'A' && arg1_f <= 'C'){
						switch(arg1_f){
							case 'A':
								ROM[position++] = I_NOT;
							break;

							case 'B':
								ROM[position++] = I_NOTB;
							break;

							case 'C':
								ROM[position++] = I_NOTC;
							break;
						}
					}else{
						val = parseWord(arg1);
						for(int i = 0; i < ctx->macros_size; i++){
							if(stn(ctx->macros[i].Name) == arg1_n){
								val = ctx->macros[i].value;
							}
						}

						ROM[position++] = I_NOTA;
						ROM[position++] = highbyte(val);
						ROM[position++] = lowbyte(val);
					}
				break;

				case INSTN_LSH:
					if(arg1_f >= 'A' && arg1_f <= 'C'){
						switch(arg1_f){
							case 'A':
								ROM[position++] = I_LSH;
							break;

							case 'B':
								ROM[position++] = I_LSHB;
							break;

							case 'C':
								ROM[position++] = I_LSHC;
							break;
						}
					}else{
						val = parseWord(arg1);
						for(int i = 0; i < ctx->macros_size; i++){
							if(stn(ctx->macros[i].Name) == arg1_n){
								val = ctx->macros[i].value;
							}
						}

						ROM[position++] = I_LSHA;
						ROM[position++] = highbyte(val);
						ROM[position++] = lowbyte(val);
					}
				break;

				case INSTN_RSH:
					if(arg1_f >= 'A' && arg1_f <= 'C'){
						switch(arg1_f){
							case 'A':
								ROM[position++] = I_RSH;
							break;

							case 'B':
								ROM[position++] = I_RSHB;
							break;

							case 'C':
								ROM[position++] = I_RSHC;
							break;
						}
					}else{
						val = parseWord(arg1);
						for(int i = 0; i < ctx->macros_size; i++){
							if(stn(ctx->macros[i].Name) == arg1_n){
								val = ctx->macros[i].value;
							}
						}

						ROM[position++] = I_RSHA;
						ROM[position++] = highbyte(val);
						ROM[position++] = lowbyte(val);
					}
				break;

				case INSTN_INC:
					if(arg1_f >= 'A' && arg1_f <= 'C'){
						switch(arg1_f){
							case 'A':
								ROM[position++] = I_INC;
							break;

							case 'B':
								ROM[position++] = I_INCB;
							break;

							case 'C':
								ROM[position++] = I_INCC;
							break;
						}
					}else{
						val = parseWord(arg1);
						for(int i = 0; i < ctx->macros_size; i++){
							if(stn(ctx->macros[i].Name) == arg1_n){
								val = ctx->macros[i].value;
							}
						}

						ROM[position++] = I_INCA;
						ROM[position++] = highbyte(val);
						ROM[position++] = lowbyte(val);
					}
				break;

				case INSTN_DEC:
					if(arg1_f >= 'A' && arg1_f <= 'C'){
						switch(arg1_f){
							case 'A':
								ROM[position++] = I_DEC;
							break;

							case 'B':
								ROM[position++] = I_DECB;
							break;

							case 'C':
								ROM[position++] = I_DECC;
							break;
						}
					}else{
						val = parseWord(arg1);

						for(int i = 0; i < ctx->macros_size; i++){
							if(stn(ctx->macros[i].Name) == arg1_n){
								val = ctx->macros[i].value;
							}
						}

						ROM[position++] = I_DECA;
						ROM[position++] = highbyte(val);
						ROM[position++] = lowbyte(val);
					}
				break;

				case INSTN_JRE:
					val = parseWord(arg1);
					ROM[position++] = I_JREL;
					ROM[position++] = lowbyte(val);
				break;

				case INSTN_JMP:
					val = parseWord(arg1);
					for(int i = 0; i < ctx->macros_size; i++){
						if(stn(ctx->macros[i].Name) == arg1_n){
							val = ctx->macros[i].value;
						}
					}

					for(int i = 0; i < ctx->labels_size; i++){
						if(stn(ctx->labels[i].Name) == arg1_n){
							val = ctx->labels[i].position;
						}
					}

					ROM[position++] = I_JUMP;
					ROM[position++] = highbyte(val);
					ROM[position++] = lowbyte(val);
				break;

				case INSTN_LDD: case INSTN_STR: case INSTN_ADD: case INSTN_SUB:
				case INSTN_MUL: case INSTN_ORR: case INSTN_XOR: case INSTN_JZE:
				case INSTN_JUN: case INSTN_JOV: case INSTN_JLT: case INSTN_JGT:
				case INSTN_JEQ:
					printf("Syntax Error: [%s] has more arguments\n",inst);
					return -1;
				break;
			}
			continue;
		}

		if(inst != NULL){
			int inst_n = stn(inst);
			switch(inst_n){
				case INSTN_NOP:
					ROM[position++] = I_NOP;
				break;

				case INSTN_DIS:
					ROM[position++] = I_DISP;
				break;

				case INSTN_HLT:
					ROM[position++] = I_HALT;
				break;

				case INSTN_TAB:
					ROM[position++] = I_TAB;
				break;

				case INSTN_TAC:
					ROM[position++] = I_TAC;
				break;

				case INSTN_TBA:
					ROM[position++] = I_TBA;
				break;

				case INSTN_TBC:
					ROM[position++] = I_TBC;
				break;

				case INSTN_TCA:
					ROM[position++] = I_TCA;
				break;

				case INSTN_TCB:
					ROM[position++] = I_TCB;
				break;

				case INSTN_LDD: case INSTN_POP: case INSTN_PUT: case INSTN_STR: case INSTN_ADD:
				case INSTN_SUB: case INSTN_MUL: case INSTN_ORR: case INSTN_XOR: case INSTN_NOT:
				case INSTN_LSH: case INSTN_RSH: case INSTN_INC: case INSTN_DEC: case INSTN_JRE:
				case INSTN_JMP: case INSTN_JZE: case INSTN_JUN: case INSTN_JOV: case INSTN_JLT:
				case INSTN_JGT: case INSTN_JEQ:
					printf("Syntax Error: [%s] has more arguments\n",inst);
					return -1;
				break;

				default:
					for(int i = 0; i < ctx->labels_size; i++){
						if(stn(ctx->labels[i].Name) == inst_n){
							ctx->labels[i].position = position;
						}
					}
				break;
			}
			continue;
		}
	}

	return 0;
}

int evalLine(context_t* ctx, char* inst, char* arg1, char* arg2){
	int res = checkInst(inst);
	if(arg2 != NULL){
		// Three args
		if(*arg1 == '='){
			// Macro assignment
			appendMacro(ctx,inst,parseWord(arg2));
			return 0;
		}

		if(res == 2){
			printf("Error: Invalid Label\n");
			return -1;
		}

		if(res == -1){
			printf("Error: Unknown Instuction\n");
			return -1;
		}

		appendInstuction(ctx,inst,arg1,arg2);
		return 0;
	}

	if(arg1 != NULL){
		// Two args
		if(*arg1 == '='){
			printf("Error: Invalid Macro Assignment\n");
			return -1;
		}

		if(res == 2){
			printf("Error: Invalid Label\n");
			return -1;
		}

		if(res == -1){
			printf("Error: Unknown Instuction\n");
			return -1;
		}
		
		appendInstuction(ctx,inst,arg1,NULL);
		return 0;
	}

	if(inst != NULL){
		if(res == 2){
			char* i = inst;
			while(*i != 0){
				if(*i == ':'){
					*i = 0;
				}
				i++;
			}
			
			appendLabel(ctx,inst,INVALID_LABEL);
			appendInstuction(ctx,inst,NULL,NULL);
			return 0;
		}

		if(res == -1){
			printf("Error: Unknown Instuction\n");
			return -1;
		}

		appendInstuction(ctx,inst,NULL,NULL);
		return 0;
	}
}

int ReadLine(char* line, context_t* ctx){
	char* inst = NULL;
	char* arg1 = NULL;
	char* arg2 = NULL;
	char* temp = NULL;
	int inst_size = 0;
	int arg1_size = 0;
	int arg2_size = 0;

	int rep = 0;

	while(*line != 0){
		char c = *line;
		if(c == ' ' || c == '\t' || c == ';'){
			if(c == ';'){
				rep = 1;
			}
			line++;
			break;
		}

		if(inst == NULL){
			inst = malloc(2 * sizeof(char));
			inst[inst_size++] = c;
			inst[inst_size] = 0;
		}else{
			temp = malloc((inst_size + 2) * sizeof(char));
			for(int i = 0; i < inst_size; i++){
				temp[i] = inst[i];
			}
			temp[inst_size++] = c;
			temp[inst_size] = 0;
			free(inst);
			inst = temp;
		}
		line++;
	}

	while(*line != 0){
		char c = *line;
		if(c == ' ' || c == '\t' || c == ';'){
			if(c == ';'){
				rep = 1;
			}
			line++;
			break;
		}

		if(arg1 == NULL){
			arg1 = malloc(2 * sizeof(char));
			arg1[arg1_size++] = c;
			arg1[arg1_size] = 0;
		}else{
			temp = malloc((arg1_size + 2) * sizeof(char));
			for(int i = 0; i < arg1_size; i++){
				temp[i] = arg1[i];
			}
			temp[arg1_size++] = c;
			temp[arg1_size] = 0;
			free(arg1);
			arg1 = temp;
		}
		line++;
	}

	while(*line != 0){
		char c = *line;
		if(c == ' ' || c == '\t' || c == ';'){
			if(c == ';'){
				rep = 1;
			}
			line++;
			break;
		}

		if(arg2 == NULL){
			arg2 = malloc(2 * sizeof(char));
			arg2[arg2_size++] = c;
			arg2[arg2_size] = 0;
		}else{
			temp = malloc((arg2_size + 2) * sizeof(char));
			for(int i = 0; i < arg2_size; i++){
				temp[i] = arg2[i];
			}
			temp[arg2_size++] = c;
			temp[arg2_size] = 0;
			free(arg2);
			arg2 = temp;
		}
		line++;
	}

	if(!rep){
		while(*line != 0){
			char c = *line;
			if(!(c == ' ' || c == '\t' || c == ';')){
				printf("Error: Sytax Error\n");
				return -1;
			}
		}
	}
	
	evalLine(ctx,inst,arg1,arg2);
	
	if(rep){
		while (*line != 0 && (*line == ' ' || *line == '\t' || *line == ';')){
			line++;
		}
		
		if(*line == 0){
			return 0;
		}

		// repeat
		ReadLine(line,ctx);
	}
	return 0;
}

int printable(char c){
	return ((c >= ' ') && (c <= '~')) || (c == '\t') || (c == '\n') || (c == EOF);
}

int ReadFile(char* path, context_t* ctx){
	FILE* file = fopen(path,"r");
	if(file == NULL){
		return -1;
	}

	char* Line = NULL;
	char* temp = NULL;
	int Line_size = 0;
	
	int comment = 0;
	while(!feof(file)){
		char c = fgetc(file);
		if(!printable(c)){
			continue;
		}

		if(c == '\n' || c == EOF){
			comment = 0;
			if(Line_size == 0){
				continue;
			}

			ReadLine(Line,ctx);
			free(Line);
			Line_size = 0;
		}else{
			if(comment){
				continue;
			}

			if(c == '#'){
				comment = 1;
				continue;
			}

			if(Line_size == 0){
				Line = malloc(2*sizeof(char));
				Line[Line_size++] = c;
				Line[Line_size] = 0;
			}else{
				temp = malloc((Line_size + 2)*sizeof(char));
				for(int i = 0; i < Line_size; i++){
					temp[i] = Line[i];
				}
				temp[Line_size++] = c;
				temp[Line_size] = 0;
				free(Line);
				Line = temp;
			}
		}
		
	}
	
	fclose(file);
	return 0;
}

int WriteFile(char* path){
	FILE* file = fopen(path,"w");
	if(file == NULL){
		return -1;
	}

	fwrite(ROM,sizeof(byte) * MAX_ROM,1,file);
	fclose(file);
	return 0;
}

int main(int argc, char** argv){
	char* P = "dasm/main.dasm";
	char* O = "dasm/main.drom";
	context_t context = {
		0,0,0,NULL,NULL,NULL,
	};

	if(argc > 1){
		P = argv[1];
	}

	if(argc > 2){
		O = argv[2];
	}
	
	ReadFile(P,&context);
	expandContext(&context);
	freeContext(&context);
	WriteFile(O);
	return 0;
}