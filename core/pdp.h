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

VARIABLES

**********/

/**********

STRUCTS

**********/
typedef struct {
	uint16_t 	opcode;
	uint8_t		mode_dd;
	uint8_t		dd;
} instr_single;

typedef struct {
	uint8_t 	opcode;
	uint8_t		mode_ss;
	uint8_t		ss;
	uint8_t		mode_dd;
	uint8_t		dd;
} instr_double;

/**********

FUNCTIONS

***********/

/***** File I/O *****/
int rd_ascii_file(char *, char **, int *);

/***** String to Octal *****/
int str_to_oct(char **, unsigned long *, uint16_t *, int);

/***** Obj2Ascii *****/
int obj2ascii();

/***** Byte Instruction *****/
int get_byte_instrs(uint16_t *, instr_single *, instr_double *, int);

/***** Word Instruction *****/
int get_instruction(uint16_t *, instr_single *, instr_double *, int, int *, int *);
