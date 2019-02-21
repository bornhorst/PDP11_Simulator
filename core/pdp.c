#include "pdp.h"

/**********

Get all word instructions

**********/
int get_instruction(uint16_t *oct, instr_single *s, 
		    instr_double *d, int n_lines, 
		    int *n_single, int *n_double) {

uint32_t single_byte_mask 	= 01 << 15;
uint16_t s_op_mask 		= 077700;
uint16_t s_mode_dd_mask 	= 000070;
uint16_t s_dd_mask 		= 000007;

uint16_t d_op_mask		= 070000;
uint16_t d_mode_ss_mask		= 007000;
uint16_t d_ss_mask		= 000700;
uint16_t d_mode_dd_mask		= 000070;
uint16_t d_dd_mask		= 000007;

int j = 0;
int k = 0;

for(int i = 0; i < n_lines; i++) { 
	if((oct[i] & single_byte_mask) == single_byte_mask)
		++(*n_single);
	else
		++(*n_double);
}

for(int i = 0; i < n_lines; i++) {
	if((oct[i] & single_byte_mask) == single_byte_mask) {
		s[j].opcode 	= (oct[i] & s_op_mask) >> 6;
		s[j].mode_dd 	= (oct[i] & s_mode_dd_mask) >> 3;
		s[j].dd		= (oct[i] & s_dd_mask);
		++j;	
	}	
}

for(int i = 0; i < n_lines; i++) {
	if((oct[i] & single_byte_mask) != single_byte_mask) {
		d[k].opcode	= (oct[i] & d_op_mask) >> 12;
		d[k].mode_ss	= (oct[i] & d_mode_ss_mask) >> 9;
		d[k].ss		= (oct[i] & d_ss_mask) >> 6;
		d[k].mode_dd   	= (oct[i] & d_mode_dd_mask) >> 3;
		d[k].dd		= (oct[i] & d_dd_mask);
		++k;
	}
}

return 0;

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
int str_to_oct(char ** line, unsigned long *oct, uint16_t *oct16, int n_lines){

char 	new_line[BUFF_SIZE];
int	ret = ERROR_NONE;

/***** Remove Unwanted Chars and Convert String -> Octal *****/
for(int i = 0; i < n_lines; i++){
	memmove(new_line, line[i]+1, 7);
	oct[i] = strtoul(new_line, NULL, 8);
	oct16[i] = oct[i];
}

return ret;

}

/**********

Run macro11/obj2ascii Converter

**********/
int obj2ascii(){

const char     *mac11 = "cd ascii; ./macro11 pdp.mac -o pdp.obj -l pdp.lst";
const char     *o2a = "cd ascii; ./obj2ascii pdp.obj pdp.ascii"; 	 
int 		ret = ERROR_NONE;

/***** Run on Command Line *****/
//ret = system(cd);
ret = system(mac11);
ret = system(o2a);

return ret;

}
