#include "pdp.h"

int main(int argc, char *argv[]){

int line_num = 0;

char *filename;

char *line[MAX_LINES];

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

for(int i = 0; i < line_num; i++){
	printf("%s\n", line[i]);
	memmove(line[i], line[i]+1, 6);
	printf("%s\n", line[i]);
	free(line[i]);
}

return 0;

}
