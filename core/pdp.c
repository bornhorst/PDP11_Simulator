#include "pdp.h"

int check_addr_mode(uint16_t mode, uint16_t mask) {

int valid = 0;

uint16_t d1_mask = 0000070;
uint16_t d2_mask = 0007000;

printf("addr mode: %06o\n", (mode & mask));
/***** Single Operand *****/
if((mode & mask) == s_REG)
	valid = 1;
else if((mode & mask) == s_REG_DEF)
	valid = 1;
else if((mode & mask) == s_AUT_INC)
	valid = 1;
else if((mode & mask) == s_AUT_INC_DEF)
	valid = 1;
else if((mode & mask) == s_AUT_DEC)
	valid = 1;
else if((mode & mask) == s_AUT_DEC_DEF)
	valid = 1;
else if((mode & mask) == s_IND)
	valid = 1;
else if((mode & mask) == s_IND_DEF)
	valid = 1;
else if((mode & mask) == s_IMM)
	valid = 1;
else if((mode & mask) == s_ABS)
	valid = 1;
else if((mode & mask) == s_REL)
	valid = 1;
else if((mode & mask) == s_REL_DEF)
	valid = 1;
/***** Double Operand - Mode DD *****/
else if((mode & d1_mask) == d1_REG)  
	valid = 0;
else if((mode & d1_mask) == d1_REG_DEF)
	valid = 0;
else if((mode & d1_mask) == d1_AUT_INC)
	valid = 0;
else if((mode & d1_mask) == d1_AUT_INC_DEF)
	valid = 0;
else if((mode & d1_mask) == d1_AUT_DEC)
	valid = 0;
else if((mode & d1_mask) == d1_AUT_DEC_DEF)
	valid = 0;
else if((mode & d1_mask) == d1_IND)
	valid = 0;
else if((mode & d1_mask) == d1_IND_DEF)
	valid = 0;
else
	valid = ERROR;

/*-----
 	
Here we have to check the second operand as well
because each operand can have a different mode.

-----*/

/***** Double Operand - Mode SS *****/
if(valid == 0) {
	if((mode & d2_mask) == d2_REG)
		valid = 1;
	else if((mode & d2_mask) == d2_REG_DEF)
		valid = 1;
	else if((mode & d2_mask) == d2_AUT_INC)
		valid = 1;
	else if((mode & d2_mask) == d2_AUT_INC_DEF)
		valid = 1;
	else if((mode & d2_mask) == d2_AUT_DEC)
		valid = 1;
	else if((mode & d2_mask) == d2_AUT_DEC_DEF)
		valid = 1;
	else if((mode & d2_mask) == d2_IND)
		valid = 1;
	else if((mode & d2_mask) == d2_IND_DEF)
		valid = 1;
	else
		valid = ERROR;
}

return valid;

}

/**********

Check if Opcode is Valid 

**********/
int valid_opcode(uint16_t opcode, uint16_t mask, int type) {

int valid = 0;

/***** Word Instruction Opcodes *****/
if(type) {
	if((opcode & mask) == JMP)
		valid = 1;
	else if((opcode & mask) == SWAB)
		valid = 1;
	else if((opcode & mask) == BR)
		valid = 1;
	else if((opcode & mask) == BNE)
		valid = 1;
	else if((opcode & mask) == BEQ)
		valid = 1;
	else if((opcode & mask) == BGE)
		valid = 1;
	else if((opcode & mask) == BLT)
		valid = 1;
	else if((opcode & mask) == BGT)
		valid = 1;
	else if((opcode & mask) == BLE)
		valid = 1;
	else if((opcode & mask) == CLR)
		valid = 1;
	else if((opcode & mask) == COM)
		valid = 1;
	else if((opcode & mask) == INC)
		valid = 1;
	else if((opcode & mask) == DEC)
		valid = 1;
	else if((opcode & mask) == NEG)
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
	else if((opcode & mask) == MOV)
		valid = 1;
	else if((opcode & mask) == CMP)
		valid = 1;
	else if((opcode & mask) == BIT)
		valid = 1;
	else if((opcode & mask) == BIC)
		valid = 1;
	else if((opcode & mask) == BIS)
		valid = 1;
	else if((opcode & mask) == ADD)
		valid = 1;
	else if((opcode & (mask | 070000)) == MUL)
		valid = 1;
	else if((opcode & (mask | 071000)) == DIV)
		valid = 1;
	else if((opcode & (mask | 072000)) == ASH)
		valid = 1;
	else if((opcode & (mask | 073000)) == ASHC)
		valid = 1;
	else if((opcode & (mask | 074000)) == XOR)
		valid = 1;
	else
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
		    int *n_single, int *n_double, int instr_start) {

int ret = ERROR_NONE;

/***** Word or Byte Instruction *****/
int BYTE = 0;
int WORD = 1;

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
uint16_t s_mode_mask	= 0000077;
uint16_t d_mode_mask	= 0007070;

/***** Assign Byte Instructions to Struct *****/
for(int i = instr_start; i < n_lines; i++) {
	if((oct[i] & single_byte_mask) == single_byte_mask) {
		s[*n_single].opcode 	= (oct[i] & s_op_mask) 		>> 6;
		s[*n_single].mode_dd 	= (oct[i] & s_mode_dd_mask) 	>> 3;
		s[*n_single].dd		= (oct[i] & s_dd_mask);
	
		d[*n_double].opcode	= (oct[i] & d_op_mask) 		>> 12;
		d[*n_double].mode_ss	= (oct[i] & d_mode_ss_mask) 	>> 9;
		d[*n_double].ss		= (oct[i] & d_ss_mask) 		>> 6;
		d[*n_double].mode_dd   	= (oct[i] & d_mode_dd_mask) 	>> 3;
		d[*n_double].dd		= (oct[i] & d_dd_mask);

		/***** Only Assign if Opcode Valid *****/
		if(valid_opcode(s[*n_single].opcode, s_op_mask, BYTE)) { 
			ret = check_addr_mode((s[*n_single].mode_dd << 3), 
					       s_mode_mask);
			++(*n_single);	
		} else if(valid_opcode(d[*n_double].opcode, d_op_mask, BYTE)) { 
			ret = check_addr_mode(((d[*n_double].mode_ss << 9) | 
					       (d[*n_double].mode_dd << 3)), 
					        d_mode_mask);
			++(*n_double);
		}
	}
}

/***** No Valid Instructions *****/
if(((*n_single == 0) && (*n_double == 0)) || (ret == ERROR)) 
	ret = ERROR;
else
	ret = ERROR_NONE;	

/***** Assign Word Instructions to Struct *****/
for(int i = instr_start; i < n_lines; i++) {
	if((oct[i] & single_byte_mask) != single_byte_mask) {
		d[*n_double].opcode	= (oct[i] & d_op_mask) 		>> 12;
		d[*n_double].mode_ss	= (oct[i] & d_mode_ss_mask) 	>> 9;
		d[*n_double].ss		= (oct[i] & d_ss_mask) 		>> 6;
		d[*n_double].mode_dd   	= (oct[i] & d_mode_dd_mask) 	>> 3;
		d[*n_double].dd		= (oct[i] & d_dd_mask);

		s[*n_single].opcode 	= (oct[i] & s_op_mask) 		>> 6;
		s[*n_single].mode_dd 	= (oct[i] & s_mode_dd_mask) 	>> 3;
		s[*n_single].dd		= (oct[i] & s_dd_mask);

		/***** Only Assign if Opcode Valid *****/
		if(valid_opcode((d[*n_double].opcode << 12), d_op_mask, WORD)) { 
			ret = check_addr_mode(((d[*n_double].mode_ss << 9) | 
					       (d[*n_double].mode_dd << 3)), 
					        d_mode_mask);
			++(*n_double);
		} else if(valid_opcode((s[*n_single].opcode << 6), s_op_mask, WORD)) {
			ret = check_addr_mode((s[*n_single].mode_dd << 3), 
					       s_mode_mask);
			++(*n_single);
		}
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

fclose(fp);

return ret;

}

/**********

Convert String to Octal Value

**********/
int str_to_oct(char ** line, unsigned long *oct, uint16_t *oct16, int n_lines,
	       uint16_t *PC, uint16_t start_addr, int *start_instr){

char 	new_line[BUFF_SIZE];
int	ret = ERROR_NONE;

/***** Remove Unwanted Chars and Convert String -> Octal *****/
for(int i = 0; i < n_lines; i++){
	memmove(new_line, line[i]+1, 7);
	oct[i] = strtoul(new_line, NULL, 8);
	oct16[i] = oct[i];

	/***** Increment Program Counter *****/
	if(i > 0)
		PC[i] = PC[i-1] + 2;
	else
		PC[i] = 0;

	/***** Find the First Program Instruction *****/
	if(start_addr == PC[i])
 		*start_instr = i;
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
#ifdef AMA
ret = system(mac11_deb);
#else
ret = system(mac11);
#endif

ret = system(o2a);

return ret;

}
