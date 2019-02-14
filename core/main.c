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

	/***** String -> Octal *****/
	ret = str_to_oct(line, oct_num, oct16, n_lines);

	if(ret == ERROR)
		return ret;
}

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

return ret;

}
