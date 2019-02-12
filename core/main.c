#include "pdp.h"

int main(int argc, char *argv[]){

int line_num = 0;

char *filename;

char *line[MAX_LINES];

unsigned long oct_num[MAX_LINES];

if(argc == 2)
	filename = argv[1];
else if(argc < 2){
	printf("./pdp 'filename'\n");
	return -1;
}else{
	printf("Too many arguments!\n");
	return -1;
}

line_num = rd_ascii_file(filename, line);

convert_to_octal(line, oct_num, line_num);

for(int i = 0; i < line_num; i++){
	printf("%lo\n", oct_num[i]);
}

for(int i = 0; i < line_num; i++){
	printf("%s\n", line[i]);
	free(line[i]);
}

return 0;

}
