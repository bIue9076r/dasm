DASM = dasm_type.c dasm_cpu.c dasm_alu.c dasm_inst_set.c dasm_inst_switch.c dasm_pack.c
all:
	@echo "[Start] dint.c"
	@gcc dasm_interp.c dasm_inst_str.c $(DASM) -o ./dint
	@echo "[Finish] dint.c"
	@echo "[Start] dasm.c"
	@gcc dasm_comp.c $(DASM) -o ./dasm
	@echo "[Finish] dasm.c"
