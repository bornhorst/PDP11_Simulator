#include "pdp.h"

/**********

Read Data from ASCII File

**********/
int rd_ascii_file(char *filename, char **line){

int 	i = 0;
char	buf[MAX_BUFF];

FILE *fp;

fp = fopen(filename, "r");

if(fp == NULL){
	printf("Can't open file!\n");
	return -1;
}
	
while(fscanf(fp, "%s", buf) != EOF){
	line[i] = (char*)malloc(MAX_BUFF*sizeof(char));
	snprintf(line[i], sizeof line[i], "%s", buf); 
	i++;
}

fclose(fp);

return i;

}

/**********

Convert String to Octal Value

**********/
int convert_to_octal(char ** line, unsigned long *oct, int num_lines){

char new_line[MAX_BUFF];

for(int i = 0; i < num_lines; i++){
	memmove(new_line, line[i]+1, 7);
	oct[i] = strtoul(new_line, NULL, 8);
}

return 0;

}
