#include "pdp.h"

#define DEBUG


/**********

PDP-11 Simulator

**********/
int main(int argc, char *argv[]){

/***** Vars *****/
int 		line_num = 0;
char 		*filename;
char 		*line[MAX_LINES];
unsigned long 	oct_num[MAX_LINES];

/***** Command Line Args *****/
if(argc == 2)
	filename = argv[1];
else if(argc < 2){
	printf("./pdp 'filename'\n");
	return -1;
}else{
	printf("Too many arguments!\n");
	return -1;
}

/***** File I/O *****/
line_num = rd_ascii_file(filename, line);

/***** String -> Octal *****/
convert_to_octal(line, oct_num, line_num);

#ifdef DEBUG
for(int i = 0; i < line_num; i++){
	printf("%s\n", line[i]);
}
printf("\n");
for(int i = 0; i < line_num; i++){

	printf("%lo\n", oct_num[i]);
}
#endif

/***** Free Memory *****/
for(int i = 0; i < line_num; i++){
	free(line[i]);
}

return 0;

}
