
#include "pdp.h"

int main(){

int line_num = 0;

char *filename;

char *line[MAX_LINES];

filename = "practice.ascii";

line_num = rd_ascii_file(filename, line);

for(int i = 0; i < line_num; i++){
	printf("%s\n", line[i]);
	memmove(line[i], line[i]+1, 6);
	printf("%s\n", line[i]);
	free(line[i]);
}

return 0;

}
