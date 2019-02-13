#include "pdp.h"

#define DEBUG


/**********

PDP-11 SIMULATOR

**********/
int main(int argc, char *argv[]){

/***** Vars *****/
int 		n_lines;		// # lines read from file
char 	       *fn;			// filename 
char 	       *line	[LINE_SIZE];	// lines as string
unsigned long 	oct_num	[LINE_SIZE];	// lines as u_long
uint16_t	oct16	[LINE_SIZE];	// lines as u_16

/***** Command Line Args *****/
if(argc == 2)
	fn = argv[1];
else{
	printf("Format: ./pdp filepath/filename\n");
	return -1;
}

/***** File I/O *****/
n_lines = rd_ascii_file(fn, line);

/***** String -> Octal *****/
str_to_oct(line, oct_num, oct16, n_lines);

#ifdef DEBUG
for(int i = 0; i < n_lines; i++){
	printf("%s\n", line[i]);
}
printf("\n");
for(int i = 0; i < n_lines; i++){
	printf("%06o\n", oct16[i]);
}
#endif

/***** Free Memory *****/
for(int i = 0; i < n_lines; i++){
	free(line[i]);
}

return 0;

}
