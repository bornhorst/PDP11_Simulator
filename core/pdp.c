#include "pdp.h"

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
			sim[*n_sim].addr = PC[i];
			++(*n_sim);
			/***** Check to see if fetch accesses memory *****/
			if(s[j].dd_reg == oct[i+1]) {
				for(int m = 0; m < n_data; m++) {
					if(((s[j].dd_reg + (PC[i+1]+02)) - MAX_ADDR) == data[m].PC) {
					sim[*n_sim].type = 1;
					sim[*n_sim].addr = data[m].PC;
					++(*n_sim);
					}
				} 
			}
		} 
		/***** If double op PC is the same as ascii PC, instruction found *****/	
		if(PC[i] == d[k].PC) {
			sim[*n_sim].type = 2;
			sim[*n_sim].addr = PC[i];
			++(*n_sim);
			/***** Check to see if fetch accesses memory *****/
			if(d[k].ss_reg == oct[i+1]) {
				for(int m = 0; m < n_data; m++) {
					if(((d[k].ss_reg + (PC[i+1]+02)) - MAX_ADDR) == data[m].PC) {
					sim[*n_sim].type = 0;
					sim[*n_sim].addr  = data[m].PC;
					++(*n_sim);
					}	 						
				}	 
			}
			/***** Check to see if fetch accesses memory *****/
			if(d[k].dd_reg == oct[i+2]) {
				for(int m = 0; m < n_data; m++) {
					if(((d[k].dd_reg + (PC[i+2]+02)) - MAX_ADDR) == data[m].PC) {
					sim[*n_sim].type = 1;
					sim[*n_sim].addr  = data[m].PC;
					++(*n_sim);
					} 
				} 
			}
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
	*index_out = 9999;
}else if((mode & ss_pc_mask) == ss_REL){
	*index_out = index + 1; 
}else if((mode & ss_pc_mask) == ss_REL_DEF){
	*index_out = 9999;
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

/***** Check DD Mode *****/
if(type == DOUBLE) {
	if((mode & dd_pc_mask) == dd_IMM){ 
		*index_out = index + 2;
	}else if((mode & dd_pc_mask) == dd_ABS){
		*index_out = 9999;
	}else if((mode & dd_pc_mask) == dd_REL){
		*index_out = index + 2;
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
	if((opcode & mask) == JMP)
		valid = 1;
	else if((opcode & mask) == SWAB)
		valid = 1;
	else if((opcode & mask) == BR) {
		snprintf(msg, BUFF_SIZE, "BR");
		valid = 1;
	} else if((opcode & mask) == BNE) {
		snprintf(msg, BUFF_SIZE, "BNE");
		valid = 1;
	} else if((opcode & mask) == BEQ)
		valid = 1;
	else if((opcode & mask) == BGE)
		valid = 1;
	else if((opcode & mask) == BLT)
		valid = 1;
	else if((opcode & mask) == BGT)
		valid = 1;
	else if((opcode & mask) == BLE) {
		snprintf(msg, BUFF_SIZE, "BLE");
		valid = 1;
	} else if((opcode & mask) == CLR)
		valid = 1;
	else if((opcode & mask) == COM)
		valid = 1;
	else if((opcode & mask) == INC)
		valid = 1;
	else if((opcode & mask) == DEC) {
		snprintf(msg, BUFF_SIZE, "DEC");
		valid = 1;
	} else if((opcode & mask) == NEG)
		valid = 1;
	else if((opcode & mask) == ADC)
		valid = 1;
	else if((opcode & mask) == SBC)
		valid = 1;
	else if((opcode & mask) == ROR)
		valid = 1;
	else if((opcode & mask) == ROL)
		valid = 1;
	else if((opcode & mask) == ASR)
		valid = 1;
	else if((opcode & mask) == ASL)
		valid = 1;
	else if((opcode & mask) == MOV) {
		snprintf(msg, BUFF_SIZE, "MOV");
		valid 	= 1;
	} else if((opcode & mask) == CMP) {
		snprintf(msg, BUFF_SIZE, "CMP");
		valid = 1;
	} else if((opcode & mask) == BIT)
		valid = 1;
	else if((opcode & mask) == BIC)
		valid = 1;
	else if((opcode & mask) == BIS)
		valid = 1;
	else if((opcode & mask) == ADD)
		valid = 1;
	else if((opcode & (mask | 077000)) == MUL) {
		snprintf(msg, BUFF_SIZE, "MUL");
		valid = 1;
	} else if((opcode & (mask | 077000)) == DIV) {
		snprintf(msg, BUFF_SIZE, "DIV");
		valid = 1;
	} else if((opcode & (mask | 077000)) == ASH)
		valid = 1;
	else if((opcode & (mask | 077000)) == ASHC)
		valid = 1;
	else if((opcode & (mask | 077000)) == XOR)
		valid = 1;
	else if((opcode | mask) == HALT) {
		snprintf(msg, BUFF_SIZE, "HALT");
		valid = 1;
	} else
		valid = 0;
} else {
	/***** Byte Instruction Opcodes *****/
	if((opcode & mask) == BPL)
		valid = 1;
	else if((opcode & mask) == BMI)
		valid = 1;
	else if((opcode & mask) == BHI)
		valid = 1;
	else if((opcode & mask) == BLOS)
		valid = 1;
	else if((opcode & mask) == BVC)
		valid = 1;
	else if((opcode & mask) == BVS)
		valid = 1;
	else if((opcode & mask) == BCC)
		valid = 1;
	else if((opcode & mask) == BCS)
		valid = 1;
	else if((opcode & mask) == CLRB)
		valid = 1;
	else if((opcode & mask) == COMB)
		valid = 1;
	else if((opcode & mask) == INCB)
		valid = 1;
	else if((opcode & mask) == DECB)
		valid = 1;
	else if((opcode & mask) == NEGB)
		valid = 1;
	else if((opcode & mask) == ADCB)
		valid = 1;
	else if((opcode & mask) == SBCB)
		valid = 1;
	else if((opcode & mask) == RORB)
		valid = 1;
	else if((opcode & mask) == ROLB)
		valid = 1;
	else if((opcode & mask) == ASRB)
		valid = 1;
	else if((opcode & mask) == ASLB)
		valid = 1;
	else if((opcode & mask) == MOVB)
		valid = 1;
	else if((opcode & mask) == CMPB)
		valid = 1;
	else if((opcode & mask) == BITB)
		valid = 1;
	else if((opcode & mask) == BICB)
		valid = 1;
	else if((opcode & mask) == BISB)
		valid = 1;
	else if((opcode & mask) == SUB)
		valid = 1;
	else
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
uint32_t single_byte_mask 	= 01 << 15;
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
	if((oct[i] & single_byte_mask) == single_byte_mask) {
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
		if(valid_opcode(oct[i], d_op_mask, BYTE, d[*n_double].instr)) { 
			//check_addr_mode(oct[i], dd_mode_mask | ss_mode_mask, 
		        //  		DOUBLE, &d[*n_double].ss_reg, &d[*n_double].dd_reg);
			++(*n_double);
		} else if(valid_opcode(oct[i], s_op_mask, BYTE, s[*n_single].instr)) { 
			//check_addr_mode(oct[i], dd_mode_mask, SINGLE, 
			//		&ss_dummy, &s[*n_single].dd_reg);
			++(*n_single);
		} else if(valid_opcode(temp_branch, s_op_mask, BYTE, s[*n_single].instr)) {
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
	if((oct[i] & single_byte_mask) != single_byte_mask) {
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
			//check_addr_mode(oct[i], dd_mode_mask | ss_mode_mask, 
			//		DOUBLE, &d[*n_double].ss_reg, &d[*n_double].dd_reg);
			++(*n_double);
		} else if(valid_opcode(oct[i], s_op_mask, WORD, s[*n_single].instr)) {
			//check_addr_mode(oct[i], dd_mode_mask, SINGLE, 
			//	        &ss_dummy, &s[*n_single].dd_reg);
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
int obj2ascii(){

const char     *mac11_deb 	= "cd ascii; ./macro11 pdp.mac "
			          "-o pdp.obj -l pdp.lst -e AMA";
const char     *mac11		= "cd ascii; ./macro11 pdp.mac "
				  "-o pdp.obj -l pdp.lst";
const char     *o2a 		= "cd ascii; ./obj2ascii pdp.obj pdp.ascii"; 	 
int 		ret 		= ERROR_NONE;

/***** Run on Command Line *****/
#if AMA
ret = system(mac11_deb);
#else
ret = system(mac11);
#endif

ret = system(o2a);

return ret;

}
