#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*********
DEFINES
**********/
#define MAX_BUFF 	20

#define MAX_ADDR 	02000000

#define ONE		01
#define TWO 		02
#define THREE 		03
#define FOUR		04
#define FIVE  		05
#define SIX		06
#define SEVEN 		07	

#define MAX_LINES	500

/********
ASCII File I/O
*********/
int rd_ascii_file(char *, char **line);
