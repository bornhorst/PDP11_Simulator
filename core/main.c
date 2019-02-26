#include "pdp.h"

/**********

PDP-11 SIMULATOR

**********/
int main(int argc, char *argv[]){

/***** Vars *****/
int 		n_lines;		// # lines read from file
int	        starting_instr;         // first program instruction
char 	       *cmd;			// command line instruction 
uint16_t        start_addr;		// starting address of instruction
unsigned long   addr_temp;		// temp addr used for char/long conversion
char	        fn	[BUFF_SIZE];	// filename
char 	       *line	[LINE_SIZE];	// lines as string
unsigned long 	oct_num	[LINE_SIZE];	// lines as u_long
uint16_t	oct16	[LINE_SIZE];	// lines as u_16
instr_single    s_instr [LINE_SIZE];	// single operand structs
instr_double    d_instr [LINE_SIZE];	// double operand structs
int		n_single, n_double;	// # of single/double operand instrs
uint16_t        PC	[LINE_SIZE];	// program counter
int		ret;			// return value

/***** Initialize Variables *****/
n_lines 	= 0;
starting_instr 	= 0;
cmd 		= NULL;
start_addr 	= 0177777;
addr_temp 	= 0x0;
n_single 	= 0;
n_double 	= 0;
ret 		= ERROR_NONE;

/***** Command Line Args *****/
if(argc == 2)
	cmd 		= argv[1];
else if(argc == 3) {
	cmd 		= argv[1];
        addr_temp 	= strtoul((&argv[2][1]), NULL, 8);
	start_addr	= addr_temp;
} else{
	printf("Generate Ascii: ./pdp obj2ascii\n"
	       "Run Simulator:  ./pdp pdp.ascii "
	       "*<address of first instruction>\n");
	ret = ERROR;
	return ret;
}

/***** Run Simulator *****/
if(!strcmp(cmd, "obj2ascii")){
	ret = obj2ascii();
	return ret;
} else if((!strcmp(cmd, "pdp.ascii")) && (start_addr != 0177777)) { 	

	/***** File I/O *****/	
	snprintf(fn, BUFF_SIZE, "ascii/%s", cmd);
 	ret = rd_ascii_file(fn, line, &n_lines);
	if(ret == ERROR) {
		printf("File I/O Error\n");
		return ret;
	}

	/***** String -> Octal *****/
	ret = str_to_oct(line, oct_num, oct16, n_lines, PC, start_addr, 
			 &starting_instr);
	if(ret == ERROR) {
		printf("Conversion Error\n");
		return ret;
	}
	
	/***** Find Valid Instructions *****/
	ret = get_instruction(oct16, s_instr, d_instr, n_lines, &n_single, 
			      &n_double, starting_instr, PC); 
	if(ret == ERROR) {
		printf("No Valid Instructions Found\n");
		return ret;
	}
} else {
	printf("Generate Ascii: ./pdp obj2ascii\n"
	       "Run Simulator:  ./pdp pdp.ascii "
	       "*<address of first instruction>\n");
	ret == ERROR;
	return ret;
}
	

/***** Print Statements for Debugging *****/
#ifdef DEBUG
printf("\nSTRING-----\n");
for(int i = 0; i < n_lines; i++){
	printf("%s\n", line[i]);
}
printf("\nOCTAL-----PC\n");
for(int i = 0; i < n_lines; i++){
	printf("%06o    %03o\n", oct16[i], PC[i]);
}
printf("\nSINGLE_OPERAND_INSTRUCTIONS\n");
for(int i = 0; i < n_single; i++) {
	printf("%-5s %03o %01o %01o   %o\n", s_instr[i].instr, s_instr[i].opcode, 
		s_instr[i].mode_dd, s_instr[i].dd, s_instr[i].PC);
}
printf("\nDOUBLE_OPERAND_INSTRUCTIONS\n");
for(int i = 0; i < n_double; i++) {
	printf("%-5s %01o %01o %01o %01o %01o   %o\n", d_instr[i].instr, 
		d_instr[i].opcode, d_instr[i].mode_ss, d_instr[i].ss, 
		d_instr[i].mode_dd, d_instr[i].dd, d_instr[i].PC);
}
#endif

/***** Free Memory *****/
for(int i = 0; i < n_lines; i++){
	free(line[i]);
}

return ret;

}
