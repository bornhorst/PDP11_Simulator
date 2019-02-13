#include "pdp.h"

/**********

Read Data from ASCII File

**********/
int rd_ascii_file(char *filename, char **line){

int 	i = 0;
char	buf[BUFF_SIZE];

FILE *fp;

fp = fopen(filename, "r");

if(fp == NULL){
	printf("Can't open file!\n");
	printf("Format: ./pdp filepath/filename\n");
	return -1;
}

/***** Read Ascii Line by Line *****/
while(fscanf(fp, "%s", buf) != EOF){
	line[i] = (char*)malloc(BUFF_SIZE*sizeof(char));
	snprintf(line[i], sizeof line[i], "%s", buf); 
	i++;
}

fclose(fp);

return i;

}

/**********

Convert String to Octal Value

**********/
int str_to_oct(char ** line, unsigned long *oct, uint16_t *oct16, int n_lines){

char new_line[BUFF_SIZE];

/***** Remove Unwanted Chars and Convert String -> Octal *****/
for(int i = 0; i < n_lines; i++){
	memmove(new_line, line[i]+1, 7);
	oct[i] = strtoul(new_line, NULL, 8);
	oct16[i] = oct[i];
}

return 0;

}
