#include "pdp.h"

#define DEBUG


/**********

PDP-11 SIMULATOR

**********/
int main(int argc, char *argv[]){

/***** Vars *****/
int 		n_lines;		// # lines read from file
char 	       *cmd;			// command line instruction 
char	        fn	[BUFF_SIZE];	// filename
char 	       *line	[LINE_SIZE];	// lines as string
unsigned long 	oct_num	[LINE_SIZE];	// lines as u_long
uint16_t	oct16	[LINE_SIZE];	// lines as u_16
instr_single    s_instr [LINE_SIZE];	// single operand structs
instr_double    d_instr [LINE_SIZE];	// double operand structs
int		n_single, n_double;	// # of single/double operand instrs
uint16_t        PC	[LINE_SIZE];	// program counter
int		ret;			// return value

/***** Initial Vars *****/
n_lines = 0;
ret 	= ERROR_NONE;

/***** Command Line Args *****/
if(argc == 2)
	cmd = argv[1];
else{
	printf("Generate Ascii: ./pdp obj2ascii\n"
	       "Run Simulator:  ./pdp pdp.ascii\n");
	ret = ERROR;
	return ret;
}

if(!strcmp(cmd, "obj2ascii")){
	ret = obj2ascii();
	return ret;
} else{ 	
	/***** File I/O *****/	
	snprintf(fn, BUFF_SIZE, "ascii/%s", cmd);
 	ret = rd_ascii_file(fn, line, &n_lines);
	if(ret == ERROR) {
		printf("File I/O Error\n");
		return ret;
	}

	/***** String -> Octal *****/
	ret = str_to_oct(line, oct_num, oct16, n_lines, PC);
	if(ret == ERROR) {
		printf("Conversion Error\n");
		return ret;
	}
	
	/***** Find Valid Instructions *****/
	ret = get_instruction(oct16, s_instr, d_instr, n_lines, &n_single, 
			      &n_double); 
	if(ret == ERROR) {
		printf("No Valid Instructions Found\n");
		return ret;
	}
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
	printf("%03o:%01o:%01o\n", s_instr[i].opcode, s_instr[i].mode_dd,
		s_instr[i].dd);
}
printf("\nDOUBLE_OPERAND_INSTRUCTIONS\n");
for(int i = 0; i < n_double; i++) {
	printf("%01o:%01o:%01o:%01o:%01o\n", d_instr[i].opcode, 
	        d_instr[i].mode_ss, d_instr[i].ss, d_instr[i].mode_dd,
		d_instr[i].dd);
}
#endif

/***** Free Memory *****/
for(int i = 0; i < n_lines; i++){
	free(line[i]);
}

return ret;

}
