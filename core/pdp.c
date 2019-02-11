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
