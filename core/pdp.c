#include "pdp.h"

/**********

Set Register Values

**********/
int set_reg(uint16_t reg_val, uint16_t reg_set){

	if(reg_set == 00)
		R0 = reg_val;
	else if(reg_set == 01)
		R1 = reg_val;
	else if(reg_set == 02)
		R2 = reg_val;
	else if(reg_set == 03)
		R3 = reg_val;
	else if(reg_set == 04)
		R4 = reg_val;
	else if(reg_set == 05)
		R5 = reg_val;
	else if(reg_set == 06)
		R6 = reg_val;
	else if(reg_set == 07)
		R7 = reg_val;

return 0;

}

/**********

Store Simulation Results

**********/
int fetch_instructions(uint16_t *oct, instr_single *s, instr_double *d,
		       uint16_t *PC, var_data *data, sim_output *sim,
		       int n_lines, int n_single, int n_double, int n_data,
		       int *n_sim) {

int ret = ERROR_NONE;

int j = 0;
int k = 0;

/***** Look through all ascii values *****/
for(int i = n_data; i < n_lines; i++) {
	/***** Check against single/double instructions *****/
	for(j = 0, k = 0; (j < n_single) || (k < n_double); j++,k++) {
		/***** If single op PC is the same as ascii PC, instruction found *****/	
		if(PC[i] == s[j].PC) {
			sim[*n_sim].type = 2;
			sim[*n_sim].addr = s[j].PC;
			++(*n_sim);
			/***** Check to see if fetch accesses memory *****/
			if(s[j].dd == 07) {
				if(s[j].mode_dd == 02){
					sim[*n_sim].type = 0;
					sim[*n_sim].addr = s[j].PC + 02;
					++(*n_sim);
					set_reg(s[j].PC + 04, s[j].dd);
				}else if(s[j].mode_dd == 03){
					sim[*n_sim].type = 0;
					sim[*n_sim].addr = s[j].PC + 02;
					++(*n_sim);
					sim[*n_sim].type = 1;
					sim[*n_sim].addr = s[j].dd_reg;
					++(*n_sim);
					set_reg(s[j].PC + 04, s[j].dd);
				}else if(s[j].mode_dd == 06){
					sim[*n_sim].type = 0;
					sim[*n_sim].addr = s[j].PC + 02;
					++(*n_sim);
					sim[*n_sim].type = 1;
					sim[*n_sim].addr = s[j].dd_reg + (s[j].PC + 04);
					++(*n_sim);
					set_reg(s[j].PC + 04, s[j].dd);
				}else if(s[j].mode_dd == 07){
					sim[*n_sim].type = 0;
					sim[*n_sim].addr = s[j].PC + 02;
					++(*n_sim);
					sim[*n_sim].type = 0;
					sim[*n_sim].addr = s[j].dd_reg + (s[j].PC + 04);
					++(*n_sim);
					sim[*n_sim].type = 1;
					sim[*n_sim].addr = oct[s[j].dd_reg + (s[j].PC + 04)];
					++(*n_sim);
					set_reg(s[j].PC + 04, s[j].dd);
				}
			}else if(s[j].mode_dd == 06){
				sim[*n_sim].type = 0;
				sim[*n_sim].addr = s[j].PC + 02;
				++(*n_sim);
			}else if(s[j].mode_dd == 07){
				sim[*n_sim].type = 0;
				sim[*n_sim].addr = s[j].PC + 02;
				++(*n_sim);
			}
			break;
		} 
		/***** If double op PC is the same as ascii PC, instruction found *****/	
		if(PC[i] == d[k].PC) {
			sim[*n_sim].type = 2;
			sim[*n_sim].addr = d[k].PC;
			++(*n_sim);
			/***** Check Address Mode for Memory Access *****/
			if(d[k].ss == 07) {
				if(d[k].mode_ss == 02){
					sim[*n_sim].type = 0;
					sim[*n_sim].addr = d[k].PC + 02;
					++(*n_sim);
					set_reg(d[k].PC + 02, d[k].ss);
				}else if(d[k].mode_ss == 03){
					sim[*n_sim].type = 0;
					sim[*n_sim].addr = d[k].PC + 02;
					++(*n_sim);
					sim[*n_sim].type = 0;
					sim[*n_sim].addr = d[k].ss_reg;
					++(*n_sim);
					set_reg(d[k].PC + 02, d[k].ss);
				}else if(d[k].mode_ss == 06){
					sim[*n_sim].type = 0;
					sim[*n_sim].addr = d[k].PC + 02;
					++(*n_sim);
					sim[*n_sim].type = 0;
					sim[*n_sim].addr = d[k].ss_reg + (d[k].PC + 04);
					++(*n_sim);
					set_reg(d[k].PC + 02, d[k].ss);
				}else if(d[k].mode_ss == 07){
					sim[*n_sim].type = 0;
					sim[*n_sim].addr = d[k].PC + 02;
					++(*n_sim);
					sim[*n_sim].type = 0;
					sim[*n_sim].addr = oct[d[k].PC + 02];
					set_reg(d[k].PC + 02, d[k].ss);
				}
			}else if(d[k].mode_ss == 06){
				sim[*n_sim].type = 0;
				sim[*n_sim].addr = d[k].PC + 02;
				++(*n_sim);
			}else if(d[k].mode_ss == 07){
				sim[*n_sim].type = 0;
				sim[*n_sim].addr = d[k].PC + 02;
				++(*n_sim);
			}
			/***** Check Address Mode for Memory Access *****/
			if(d[k].dd == 07){
				if(d[k].mode_dd == 02){
					sim[*n_sim].type = 0;
					sim[*n_sim].addr = d[k].PC + 04;
					++(*n_sim);
					set_reg(d[k].PC + 04, d[k].dd);
				}else if(d[k].mode_dd == 03){
					sim[*n_sim].type = 0;
					sim[*n_sim].addr = d[k].PC + 04;
					++(*n_sim);
					sim[*n_sim].type = 1;
					sim[*n_sim].addr = d[k].dd_reg;
					++(*n_sim);
					set_reg(d[k].PC + 04, d[k].dd);
				}else if(d[k].mode_dd == 06){
					sim[*n_sim].type = 0;
					sim[*n_sim].addr = d[k].PC + 04;
					++(*n_sim);
					sim[*n_sim].type = 1;
					sim[*n_sim].addr = d[k].dd_reg + (d[k].PC + 06);
					++(*n_sim);
					set_reg(d[k].PC + 04, d[k].dd);
				}else if(d[k].mode_dd == 07){
					sim[*n_sim].type = 0;
					sim[*n_sim].addr = d[k].PC + 04;
					++(*n_sim);
					sim[*n_sim].type = 1;
					sim[*n_sim].addr = oct[d[k].PC + 04];
					++(*n_sim);
					set_reg(d[k].PC + 04, d[k].dd);
				}
			}else if(d[k].mode_dd == 06){
				sim[*n_sim].type = 0;
				sim[*n_sim].addr = d[k].PC + 04;
				++(*n_sim);
			}else if(d[k].mode_dd == 07){
				sim[*n_sim].type = 0;
				sim[*n_sim].addr = d[k].PC + 04;
				++(*n_sim);
			}
			break;
		}
	}
}

return ret;

}

/**********

Assign both source and destination values

**********/
int store_reg_vals(uint16_t *oct, instr_single *s, instr_double *d,
		   uint16_t *PC, int n_lines, int n_single, int n_double) {

int ret 	= ERROR_NONE;

int index 	= 0;
int SINGLE 	= 0;
int DOUBLE	= 1;

/***** Use Address Modes to Store Operand Register Values *****/
for(int i = 0; i < n_lines; i++) {
	/***** Single Operand Address Modes *****/
	for(int j = 0; j < n_single; j++) {
		if(PC[i] == s[j].PC) {
			ret = dd_addr_mode(oct[i], i, &index, SINGLE);
			if(index != 9999)
				s[j].dd_reg = oct[index];
			else
				s[j].dd_reg = 000000;
		} 
	}
	/***** Double Operand Address Modes *****/
	for(int j = 0; j < n_double; j++) {
		if(PC[i] == d[j].PC) {
			ret = dd_addr_mode(oct[i], i, &index, DOUBLE);
			if(index != 9999)
				d[j].dd_reg = oct[index];
			else
				d[j].dd_reg = 000000;
			ret = ss_addr_mode(oct[i], i, &index);
			if(index != 9999)
				d[j].ss_reg = oct[index];
			else
				d[j].ss_reg = 000000;
		} 
	}
} 

return ret;

}

/**********

Assign source value

**********/
int ss_addr_mode(uint16_t mode, int index, int *index_out) {

/***** Masks for Address Modes *****/
uint16_t ss_mode_mask	= 0007000;
uint16_t ss_pc_mask 	= 0007700;

/***** Check SS Mode *****/
if((mode & ss_pc_mask) == ss_IMM){
	*index_out = index + 1;
}else if((mode & ss_pc_mask) == ss_ABS){
	*index_out = index + 1;
}else if((mode & ss_pc_mask) == ss_REL){
	*index_out = index + 1; 
}else if((mode & ss_pc_mask) == ss_REL_DEF){
	*index_out = index + 1;
}else if((mode & ss_mode_mask) == ss_REG){
	*index_out = 9999;
}else if((mode & ss_mode_mask) == ss_REG_DEF){
	*index_out = 9999;
}else if((mode & ss_mode_mask) == ss_AUT_INC){
	*index_out = 9999;
}else if((mode & ss_mode_mask) == ss_AUT_INC_DEF){
	*index_out = 9999;
}else if((mode & ss_mode_mask) == ss_AUT_DEC){
	*index_out = 9999;
}else if((mode & ss_mode_mask) == ss_AUT_DEC_DEF){
	*index_out = 9999;
}else if((mode & ss_mode_mask) == ss_IND){
	*index_out = 9999;
}else if((mode & ss_mode_mask) == ss_IND_DEF){
	*index_out = 9999;
}else
	*index_out = 9999;

return 0;

}

/**********

Assign destination value

**********/
int dd_addr_mode(uint16_t mode, int index, int *index_out, int type) {

int DOUBLE = 1;

/***** Masks for Address Modes *****/
uint16_t dd_mode_mask	= 0000070;
uint16_t dd_pc_mask 	= 0000077;
uint16_t ss_pc_mask 	= 0007700;

/***** Check DD Mode *****/
if(type == DOUBLE) {
	if((mode & dd_pc_mask) == dd_IMM){ 
		if(((mode & ss_pc_mask) == ss_IMM) || ((mode & ss_pc_mask) == ss_ABS) ||
		   ((mode & ss_pc_mask) == ss_REL) || ((mode & ss_pc_mask) == ss_REL_DEF))
			*index_out = index + 2;
		else
			*index_out = index + 1;
	}else if((mode & dd_pc_mask) == dd_ABS){
		if(((mode & ss_pc_mask) == ss_IMM) || ((mode & ss_pc_mask) == ss_ABS) ||
		   ((mode & ss_pc_mask) == ss_REL) || ((mode & ss_pc_mask) == ss_REL_DEF))
			*index_out = index + 2;
		else
			*index_out = index + 1;	
	}else if((mode & dd_pc_mask) == dd_REL){
		if(((mode & ss_pc_mask) == ss_IMM) || ((mode & ss_pc_mask) == ss_ABS) ||
		   ((mode & ss_pc_mask) == ss_REL) || ((mode & ss_pc_mask) == ss_REL_DEF))
			*index_out = index + 2;
		else
			*index_out = index + 1;
	}else if((mode & dd_pc_mask) == dd_REL_DEF){
		if(((mode & ss_pc_mask) == ss_IMM) || ((mode & ss_pc_mask) == ss_ABS) ||
		   ((mode & ss_pc_mask) == ss_REL) || ((mode & ss_pc_mask) == ss_REL_DEF))
			*index_out = index + 2;
		else
			*index_out = index + 1;
	}else if((mode & dd_mode_mask) == dd_REG){
		*index_out = 9999;
	}else if((mode & dd_mode_mask) == dd_REG_DEF){
		*index_out = 9999;
	}else if((mode & dd_mode_mask) == dd_AUT_INC){
		*index_out = 9999;
	}else if((mode & dd_mode_mask) == dd_AUT_INC_DEF){
		*index_out = 9999;
	}else if((mode & dd_mode_mask) == dd_AUT_DEC){
		*index_out = 9999;
	}else if((mode & dd_mode_mask) == dd_AUT_DEC_DEF){
		*index_out = 9999;
	}else if((mode & dd_mode_mask) == dd_IND){
		*index_out = 9999;
	}else if((mode & dd_mode_mask) == dd_IND_DEF){
		*index_out = 9999;
	}else
		*index_out = 9999;
} else {
	if((mode & dd_pc_mask) == dd_IMM){ 
		*index_out = index + 1;
	}else if((mode & dd_pc_mask) == dd_ABS){
		*index_out = 9999;
	}else if((mode & dd_pc_mask) == dd_REL){
		*index_out = index + 1;
	}else if((mode & dd_pc_mask) == dd_REL_DEF){
		*index_out = 9999;
	}else if((mode & dd_mode_mask) == dd_REG){
		*index_out = 9999;
	}else if((mode & dd_mode_mask) == dd_REG_DEF){
		*index_out = 9999;
	}else if((mode & dd_mode_mask) == dd_AUT_INC){
		*index_out = 9999;
	}else if((mode & dd_mode_mask) == dd_AUT_INC_DEF){
		*index_out = 9999;
	}else if((mode & dd_mode_mask) == dd_AUT_DEC){
		*index_out = 9999;
	}else if((mode & dd_mode_mask) == dd_AUT_DEC_DEF){
		*index_out = 9999;
	}else if((mode & dd_mode_mask) == dd_IND){
		*index_out = 9999;
	}else if((mode & dd_mode_mask) == dd_IND_DEF){
		*index_out = 9999;
	}else
		*index_out = 9999;
}

return 0;

}

/**********

Decode memory access for data variables

***********/
int data_mem_addr(uint16_t *oct, var_data *data, uint16_t *PC, int n_lines, 
		  int n_data) {

int ret = ERROR_NONE;

/***** Store memory accesses for each data variable *****/
for(int i = 0; i < n_lines; i++) {
	for(int j = 0; j < n_data; ++j) {
		if(((data[j].PC + MAX_ADDR) - (PC[i] + 02)) == oct[i]) { 
			data[j].memory[data[j].n_memory] = oct[i];
			++data[j].n_memory;
		}
	}
}

return ret;

}

/**********

Check if Opcode is Valid 

**********/
int valid_opcode(uint16_t opcode, uint16_t mask, int type, char *msg) {

int valid = 0;

/***** Word Instruction Opcodes *****/
if(type) {
	if((opcode & mask) == JMP) {
		snprintf(msg, BUFF_SIZE, "JMP");
		valid = 1;
	}else if((opcode & mask) == SWAB){
		snprintf(msg, BUFF_SIZE, "SWAB");
		valid = 1;
	}else if((opcode & mask) == BR){
		snprintf(msg, BUFF_SIZE, "BR");
		valid = 1;
	}else if((opcode & mask) == BNE){
		snprintf(msg, BUFF_SIZE, "BNE");
		valid = 1;
	}else if((opcode & mask) == BEQ){
		snprintf(msg, BUFF_SIZE, "BEQ");
		valid = 1;
	}else if((opcode & mask) == BGE){
		snprintf(msg, BUFF_SIZE, "BGE");
		valid = 1;
	}else if((opcode & mask) == BLT){
		snprintf(msg, BUFF_SIZE, "BLT");
		valid = 1;
	}else if((opcode & mask) == BGT){
		snprintf(msg, BUFF_SIZE, "BGT");
		valid = 1;
	}else if((opcode & mask) == BLE){
		snprintf(msg, BUFF_SIZE, "BLE");
		valid = 1;
	}else if((opcode & mask) == CLR){
		snprintf(msg, BUFF_SIZE, "CLR");
		valid = 1;
	}else if((opcode & mask) == COM){
		snprintf(msg, BUFF_SIZE, "COM");
		valid = 1;
	}else if((opcode & mask) == INC){
		snprintf(msg, BUFF_SIZE, "INC");
		valid = 1;
	}else if((opcode & mask) == DEC){
		snprintf(msg, BUFF_SIZE, "DEC");
		valid = 1;
	}else if((opcode & mask) == NEG){
		snprintf(msg, BUFF_SIZE, "NEG");
		valid = 1;
	}else if((opcode & mask) == ADC){
		snprintf(msg, BUFF_SIZE, "ADC");
		valid = 1;
	}else if((opcode & mask) == SBC){
		snprintf(msg, BUFF_SIZE, "SBC");
		valid = 1;
	}else if((opcode & mask) == ROR){
		snprintf(msg, BUFF_SIZE, "ROR");
		valid = 1;
	}else if((opcode & mask) == ROL){
		snprintf(msg, BUFF_SIZE, "ROL");
		valid = 1;
	}else if((opcode & mask) == ASR){
		snprintf(msg, BUFF_SIZE, "ASR");
		valid = 1;
	}else if((opcode & mask) == ASL){
		snprintf(msg, BUFF_SIZE, "ASL");
		valid = 1;
	}else if((opcode & mask) == MOV){
		snprintf(msg, BUFF_SIZE, "MOV");
		valid 	= 1;
	}else if((opcode & mask) == CMP){
		snprintf(msg, BUFF_SIZE, "CMP");
		valid = 1;
	}else if((opcode & mask) == BIT){
		snprintf(msg, BUFF_SIZE, "BIT");
		valid = 1;
	}else if((opcode & mask) == BIC){
		snprintf(msg, BUFF_SIZE, "BIC");
		valid = 1;
	}else if((opcode & mask) == BIS){
		snprintf(msg, BUFF_SIZE, "BIS");
		valid = 1;
	}else if((opcode & mask) == ADD){
		snprintf(msg, BUFF_SIZE, "ADD");
		valid = 1;
	}else if((mask == 070000) && ((opcode >> 9) == (JSR >> 9))){
		snprintf(msg, BUFF_SIZE, "JSR");
		valid = 1;
	}else if((mask == 070000) && ((opcode >> 6) == (RTS >> 6))){
		snprintf(msg, BUFF_SIZE, "RTS");
		valid = 1;
	}else if((opcode & (mask | 077000)) == MUL){
		snprintf(msg, BUFF_SIZE, "MUL");
		valid = 1;
	}else if((opcode & (mask | 077000)) == DIV){
		snprintf(msg, BUFF_SIZE, "DIV");
		valid = 1;
	}else if((opcode & (mask | 077000)) == ASH){
		snprintf(msg, BUFF_SIZE, "ASH");
		valid = 1;
	}else if((opcode & (mask | 077000)) == ASHC){
		snprintf(msg, BUFF_SIZE, "ASHC");
		valid = 1;
	}else if((opcode & (mask | 077000)) == XOR){
		snprintf(msg, BUFF_SIZE, "XOR");
		valid = 1;
	}else if((opcode | mask) == HALT){
		snprintf(msg, BUFF_SIZE, "HALT");
		valid = 1;
	}else
		valid = 0;
}else {
	/***** Byte Instruction Opcodes *****/
	if((opcode & mask) == BPL){
		snprintf(msg, BUFF_SIZE, "BPL");
		valid = 1;
	}else if((opcode & mask) == BMI){
		snprintf(msg, BUFF_SIZE, "BMI");
		valid = 1;
	}else if((opcode & mask) == BHI){
		snprintf(msg, BUFF_SIZE, "BHI");
		valid = 1;
	}else if((opcode & mask) == BLOS){
		snprintf(msg, BUFF_SIZE, "BLOS");
		valid = 1;
	}else if((opcode & mask) == BVC){
		snprintf(msg, BUFF_SIZE, "BVC");
		valid = 1;
	}else if((opcode & mask) == BVS){
		snprintf(msg, BUFF_SIZE, "BVS");
		valid = 1;
	}else if((opcode & mask) == BCC){
		snprintf(msg, BUFF_SIZE, "BCC");
		valid = 1;
	}else if((opcode & mask) == BCS){
		snprintf(msg, BUFF_SIZE, "BCS");
		valid = 1;
	}else if((opcode & mask) == CLRB){
		snprintf(msg, BUFF_SIZE, "CLRB");
		valid = 1;
	}else if((opcode & mask) == COMB){
		snprintf(msg, BUFF_SIZE, "COMB");
		valid = 1;
	}else if((opcode & mask) == INCB){
		snprintf(msg, BUFF_SIZE, "INCB");
		valid = 1;
	}else if((opcode & mask) == DECB){
		snprintf(msg, BUFF_SIZE, "DECB");
		valid = 1;
	}else if((opcode & mask) == NEGB){
		snprintf(msg, BUFF_SIZE, "NEGB");
		valid = 1;
	}else if((opcode & mask) == ADCB){
		snprintf(msg, BUFF_SIZE, "ADCB");
		valid = 1;
	}else if((opcode & mask) == SBCB){
		snprintf(msg, BUFF_SIZE, "SBCB");
		valid = 1;
	}else if((opcode & mask) == RORB){
		snprintf(msg, BUFF_SIZE, "RORB");
		valid = 1;
	}else if((opcode & mask) == ROLB){
		snprintf(msg, BUFF_SIZE, "ROLB");
		valid = 1;
	}else if((opcode & mask) == ASRB){
		snprintf(msg, BUFF_SIZE, "ASRB");
		valid = 1;
	}else if((opcode & mask) == ASLB){
		snprintf(msg, BUFF_SIZE, "ASLB");
		valid = 1;
	}else if((opcode & mask) == MOVB){
		snprintf(msg, BUFF_SIZE, "MOVB");
		valid = 1;
	}else if((opcode & mask) == CMPB){
		snprintf(msg, BUFF_SIZE, "CMPB");
		valid = 1;
	}else if((opcode & mask) == BITB){
		snprintf(msg, BUFF_SIZE, "BITB");
		valid = 1;
	}else if((opcode & mask) == BICB){
		snprintf(msg, BUFF_SIZE, "BICB");
		valid = 1;
	}else if((opcode & mask) == BISB){
		snprintf(msg, BUFF_SIZE, "BISB");
		valid = 1;
	}else if((opcode & mask) == SUB){
		snprintf(msg, BUFF_SIZE, "SUB");
		valid = 1;
	}else
		valid = 0;
}

return valid;

}

/**********

Get all Instructions

Store them as either Single 
or Double Operand Instructions

**********/
int get_instruction(uint16_t *oct, instr_single *s, 
		    instr_double *d, int n_lines, 
		    int *n_single, int *n_double, int instr_start,
		    uint16_t *PC) {

int ret = ERROR_NONE;

/***** Word or Byte Instruction *****/
int BYTE = 0;
int WORD = 1;

int SINGLE = 0;
int DOUBLE = 1;

/***** Masks for Single Operand Values *****/
uint32_t sbm		 	= 01 << 15;
uint16_t s_op_mask 		= 077700;
uint16_t s_mode_dd_mask 	= 000070;
uint16_t s_dd_mask 		= 000007;

/***** Masks for Double Operand Values *****/
uint16_t d_op_mask		= 070000;
uint16_t d_mode_ss_mask		= 007000;
uint16_t d_ss_mask		= 000700;
uint16_t d_mode_dd_mask		= 000070;
uint16_t d_dd_mask		= 000007;

/***** Masks for Address Modes *****/
uint16_t ss_mode_mask	= 0007000;
uint16_t dd_mode_mask	= 0000070;
uint16_t ss_dummy;

/***** Branch Offset Mask *****/
uint16_t br_offset_mask = 0000377;
uint16_t temp_branch	= 0000000;

/***** Assign Byte Instructions to Struct *****/
for(int i = instr_start; i < n_lines; i++) {
	if((oct[i] & sbm) == sbm) {
		s[*n_single].opcode 	= (oct[i] & s_op_mask) 		>> 6;
		s[*n_single].mode_dd 	= (oct[i] & s_mode_dd_mask) 	>> 3;
		s[*n_single].dd		= (oct[i] & s_dd_mask);
		s[*n_single].PC		= PC[i];
	
		d[*n_double].opcode	= (oct[i] & d_op_mask) 		>> 12;
		d[*n_double].mode_ss	= (oct[i] & d_mode_ss_mask) 	>> 9;
		d[*n_double].ss		= (oct[i] & d_ss_mask) 		>> 6;
		d[*n_double].mode_dd   	= (oct[i] & d_mode_dd_mask) 	>> 3;
		d[*n_double].dd		= (oct[i] & d_dd_mask);
		d[*n_double].PC		= PC[i];

		temp_branch = oct[i] - (oct[i] & br_offset_mask);

		/***** Only Assign if Opcode Valid *****/
		if(valid_opcode(oct[i], (d_op_mask|sbm), BYTE, d[*n_double].instr)) { 
			++(*n_double);
		} else if(valid_opcode(oct[i], (s_op_mask|sbm), BYTE, s[*n_single].instr)) { 
			++(*n_single);
		} else if(valid_opcode(temp_branch, (s_op_mask|sbm), BYTE, s[*n_single].instr)) {
			s[*n_single].opcode 	= (temp_branch & s_op_mask) 	 >> 6;
			s[*n_single].mode_dd	= (temp_branch & s_mode_dd_mask) >> 3;
			s[*n_single].dd		= (temp_branch & s_dd_mask);
			++(*n_single);
		} else
			continue;
	}
}

/***** Assign Word Instructions to Struct *****/
for(int i = instr_start; i < n_lines; i++) {
	if((oct[i] & sbm) != sbm) {
		d[*n_double].opcode	= (oct[i] & d_op_mask) 		>> 12;
		d[*n_double].mode_ss	= (oct[i] & d_mode_ss_mask) 	>> 9;
		d[*n_double].ss		= (oct[i] & d_ss_mask) 		>> 6;
		d[*n_double].mode_dd   	= (oct[i] & d_mode_dd_mask) 	>> 3;
		d[*n_double].dd		= (oct[i] & d_dd_mask);
		d[*n_double].PC		= PC[i];

		s[*n_single].opcode 	= (oct[i] & s_op_mask) 		>> 6;
		s[*n_single].mode_dd 	= (oct[i] & s_mode_dd_mask) 	>> 3;
		s[*n_single].dd		= (oct[i] & s_dd_mask);
		s[*n_single].PC		= PC[i];

		temp_branch = oct[i] - (oct[i] & br_offset_mask);

		/***** Only Assign if Opcode Valid *****/
		if(valid_opcode(oct[i], d_op_mask, WORD, d[*n_double].instr)) { 
			++(*n_double);
		} else if(valid_opcode(oct[i], s_op_mask, WORD, s[*n_single].instr)) {
			++(*n_single);
		} else if(valid_opcode(temp_branch, s_op_mask, WORD, s[*n_single].instr)) {
			s[*n_single].opcode 	= (temp_branch & s_op_mask) 	 >> 6;
			s[*n_single].mode_dd 	= (temp_branch & s_mode_dd_mask) >> 3;
			s[*n_single].dd		= (temp_branch & s_dd_mask);
			++(*n_single);
		} else if((i == n_lines-1) && valid_opcode(oct[i], HALT, WORD, 
							   s[*n_single].instr)) {
			s[*n_single].PC = PC[i];
			++(*n_single);
		} else
			continue;
	}
}		

/***** No Valid Instructions *****/
if(((*n_single == 0) && (*n_double == 0)) || (ret == ERROR))
	ret = ERROR;
else
	ret = ERROR_NONE;

return ret;

}

/**********

Read Data from ASCII File

**********/
int rd_ascii_file(char *filename, char **line, int *n_lines){

char	buf[BUFF_SIZE];
int	ret = ERROR_NONE;

FILE *fp;

fp = fopen(filename, "r");

if(fp == NULL){
	printf("Can't open file!\n");
	printf("Format: ./pdp filepath/filename\n");
	ret = ERROR;
	return ret;
}

/***** Read Ascii Line by Line *****/
while(fscanf(fp, "%s", buf) != EOF){
	line[*n_lines] = (char*)malloc(BUFF_SIZE*sizeof(char));
	snprintf(line[*n_lines], sizeof line[*n_lines], "%s", buf); 
	++(*n_lines);
}

/***** @000000 Needs to be Removed *****/
--(*n_lines);

fclose(fp);

return ret;

}

/**********

Convert String to Octal Value

**********/
int str_to_oct(char ** line, unsigned long *oct, uint16_t *oct16, int n_lines,
	       uint16_t *PC, uint16_t start_addr, int *start_instr, 
	       var_data *data, int *n_data){

char 	new_line[BUFF_SIZE];
int	ret = ERROR_NONE;

/***** Remove Unwanted Chars and Convert String -> Octal *****/
for(int i = 0; i < n_lines; i++){
	memmove(new_line, line[i]+1, 7);
	oct[i] = strtoul(new_line, NULL, 8);
}

for(int i = 0; i < n_lines; i++) {
	oct16[i] = oct[i+1];

	/***** Increment Program Counter *****/
	if(i > 0)
		PC[i] 		= PC[i-1] + 2;
	else
		PC[i] 		= 0;

	/***** Store the PC for the HALT Instruction *****/
	if(i == (n_lines - 1))
		PC[n_lines] 	= PC[i-1] + 2;

	/***** Find the First Program Instruction *****/
	if(start_addr == PC[i])
 		*start_instr = i;
}

/***** Store Program Data before Instructions *****/
for(int i = 0; i < *start_instr; i++) {
	data[i].data 	= oct16[i];
	data[i].PC	= PC[i];
	++(*n_data);
}

return ret;

}

/**********

Run macro11/obj2ascii Converter

**********/
int obj2ascii(char *file){

char		buff[100];
char		buff2[200];

char	       *s1		= "cd ascii; ./macro11 ";
char	       *s2		= ".mac -o ";
char	       *s3		= ".obj -l ";
char           *s4		= ".lst"; 
char	       *s5		= " -e AMA";

char	       *s6		= "cd ascii; ./obj2ascii ";
char	       *s7		= ".obj ";
char	       *s8		= ".ascii";

int		ret		= ERROR_NONE;

sprintf(buff, s1);
sprintf(buff + strlen(buff), file);
sprintf(buff + strlen(buff), s2);
sprintf(buff + strlen(buff), file);
sprintf(buff + strlen(buff), s3);
sprintf(buff + strlen(buff), file);
sprintf(buff + strlen(buff), s4);
printf("%s\n", buff);

sprintf(buff2, s6);
sprintf(buff2 + strlen(buff2), file);
sprintf(buff2 + strlen(buff2), s7);
sprintf(buff2 + strlen(buff2), file);
sprintf(buff2 + strlen(buff2), s8);
printf("%s\n", buff2);

/***** Run on Command Line *****/
#if AMA
sprintf(buff + strlen(buff), s5);
ret = system(buff);
#else
ret = system(buff);
#endif

ret = system(buff2);

return ret;

}
