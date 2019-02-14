#include "pdp.h"

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
	(*n_lines)++;
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
