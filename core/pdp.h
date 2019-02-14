#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/*********

DEFINES

**********/

/***** State *****/
#define ERROR_NONE	0
#define ERROR	       -1

/***** Buffer Size *****/
#define BUFF_SIZE 	20

/***** File I/O Buffer *****/
#define LINE_SIZE	500

/***** Memory Size *****/
#define ADDR_SIZE 	0177777

/***** Octals *****/
#define ZERO		00
#define ONE		01
#define TWO 		02
#define THREE 		03
#define FOUR		04
#define FIVE  		05
#define SIX		06
#define SEVEN 		07	

/**********

FUNCTIONS

***********/

/***** File I/O *****/
int rd_ascii_file(char *, char **, int *);

/***** String to Octal *****/
int str_to_oct(char **, unsigned long *, uint16_t *, int);

/***** Obj2Ascii *****/
int obj2ascii();
