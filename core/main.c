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
var_data	data	[LINE_SIZE];	// data that gets stored before instructions
uint16_t	memory	[LINE_SIZE];	// memory addresses
instr_single    s_instr [LINE_SIZE];	// single operand structs
instr_double    d_instr [LINE_SIZE];	// double operand structs
int		n_data;			// # of stored data values
int		n_single, n_double;	// # of single/double operand instrs
uint16_t        PC	[LINE_SIZE];	// program counter
sim_output	sim_o	[LINE_SIZE];	// simulator output
int		n_sim;			// # sim outputs
int		index;			// index to octal offset
int		ret;			// return value

/***** Initialize Variables *****/
n_lines 	= 0;
starting_instr 	= 0;
cmd 		= NULL;
start_addr 	= 0177777;
addr_temp 	= 0x0;
n_single 	= 0;
n_double 	= 0;
n_data		= 0;
n_sim 		= 0;
index		= 0;
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
			 &starting_instr, data, &n_data);
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

	/***** Get Data PC and Memory Address *****/
	for(int i = 0; i < n_lines; i++) {
		for(int j = 0; j < n_data; ++j) {
			if(((data[j].PC + MAX_ADDR) - (PC[i] + 2)) == oct16[i]) { 
				data[j].memory[data[j].n_memory] = oct16[i];
				++data[j].n_memory;
			}
		}
	}

	/***** Use Address Modes to Store Operand Register Values *****/
	for(int i = 0; i < n_lines; i++) {
		/***** Single Operand Address Modes *****/
		for(int j = 0; j < n_single; j++) {
			if(PC[i] == s_instr[j].PC) {
				ret = dd_addr_mode(oct16[i], i, &index, 0);
				if(index != 9999)
					s_instr[j].dd_reg = oct16[index];
				else
					s_instr[j].dd_reg = 000000;
			} 
		}
		/***** Double Operand Address Modes *****/
		for(int j = 0; j < n_double; j++) {
			if(PC[i] == d_instr[j].PC) {
				ret = dd_addr_mode(oct16[i], i, &index, 1);
				if(index != 9999)
					d_instr[j].dd_reg = oct16[index];
				else
					d_instr[j].dd_reg = 000000;
				ret = ss_addr_mode(oct16[i], i, &index);
				if(index != 9999)
					d_instr[j].ss_reg = oct16[index];
				else
					d_instr[j].ss_reg = 000000;
			} 
		}
	} 

	int j = 0;
	int k = 0;
	n_sim = 0;
	
	for(int i = 4; i < n_lines; i++) {
		for(j = 0, k = 0; (j < n_single) || (k < n_double); j++,k++) {
		printf("%o %o %o\n", PC[i], s_instr[j].PC, d_instr[k].PC);	
			if(PC[i] == s_instr[j].PC) {
				sim_o[n_sim].type = 2;
				sim_o[n_sim].addr = PC[i];
				++n_sim;
				if(s_instr[j].dd_reg == oct16[i+1]) {
					printf("s_instr[%d].dd_reg: %06o oct16: %06o\n", j, s_instr[j].dd_reg, oct16[i+1]);
					for(int m = 0; m < n_data; m++) {
						if(((s_instr[j].dd_reg + (PC[i+1]+02)) - MAX_ADDR) == data[m].PC) {
						sim_o[n_sim].type = 1;
						sim_o[n_sim].addr = data[m].PC;
						++n_sim;
						}
					} 
				}
			} 
			if(PC[i] == d_instr[k].PC) {
				sim_o[n_sim].type = 2;
				sim_o[n_sim].addr = PC[i];
				++n_sim;
				if(d_instr[k].ss_reg == oct16[i+1]) {
					printf("d_instr[%d].ss_reg: %06o oct16: %06o\n", j, d_instr[k].ss_reg, oct16[i+1]);
					for(int m = 0; m < n_data; m++) {
						if(((d_instr[k].ss_reg + (PC[i+1]+02)) - MAX_ADDR) == data[m].PC) {
						sim_o[n_sim].type = 0;
						sim_o[n_sim].addr  = data[m].PC;
						++n_sim;
						}	 						
					}	 
				}
				if(d_instr[k].dd_reg == oct16[i+2]) {
					printf("d_instr[%d].dd_reg: %06o oct16: %06o\n", j, d_instr[k].dd_reg, oct16[i+2]);
					for(int m = 0; m < n_data; m++) {
						if(((d_instr[k].dd_reg + (PC[i+2]+02)) - MAX_ADDR) == data[m].PC) {
						sim_o[n_sim].type = 1;
						sim_o[n_sim].addr  = data[m].PC;
						++n_sim;
						} 
					} 
				}
			}
		}
	}

	printf("\nSIMULATOR RESULTS\n");
	for(int i = 0; i < n_sim; i++) {
		printf("%d %06o\n", sim_o[i].type, sim_o[i].addr);
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
for(int i = 0; i < n_lines+1; i++){
	printf("%s\n", line[i]);
}
printf("\nOCTAL-----PC\n");
for(int i = 0; i < n_lines; i++){
	printf("%06o    %03o\n", oct16[i], PC[i]);
}
printf("\nPROGRAM_DATA\n");
for(int i = 0; i < n_data; i++) {
	printf("%06o %o ", data[i].data, data[i].PC);
	for(int j = 0; j < data[i].n_memory; j++) {
		printf("%06o ", data[i].memory[j]);
	}
	printf("\n");
} 
printf("\nSINGLE_OPERAND_INSTRUCTIONS\n");
for(int i = 0; i < n_single; i++) {
	printf("%-5s %03o %01o %01o %06o   %o\n", s_instr[i].instr, s_instr[i].opcode, 
		s_instr[i].mode_dd, s_instr[i].dd, s_instr[i].dd_reg, s_instr[i].PC);
}
printf("\nDOUBLE_OPERAND_INSTRUCTIONS\n");
for(int i = 0; i < n_double; i++) {
	printf("%-5s %01o %01o %01o %01o %01o %06o %06o   %o\n", d_instr[i].instr, 
		d_instr[i].opcode, d_instr[i].mode_ss, d_instr[i].ss, 
		d_instr[i].mode_dd, d_instr[i].dd, d_instr[i].ss_reg, 
		d_instr[i].dd_reg, d_instr[i].PC);
}
#endif

/***** Free Memory *****/
for(int i = 0; i < n_lines; i++){
	free(line[i]);
}

return ret;

}
