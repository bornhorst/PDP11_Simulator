#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "opcodes.h"

/*********

DEFINES

**********/

/***** State *****/
#define ERROR_NONE	0
#define ERROR	       -1

/***** Buffer Size *****/
#define BUFF_SIZE 	100

/***** File I/O Buffer *****/
#define LINE_SIZE	500

/***** Memory Size *****/
#define MAX_ADDR 	0200000

/**********

VARIABLES

**********/

/**********

STRUCTS

**********/
typedef struct {
	int 		type;
	uint16_t	addr;
	char		descr[BUFF_SIZE];
} sim_output;

typedef struct {
	uint16_t	data;
	uint16_t	PC;
	uint16_t	memory[LINE_SIZE];
	int		n_memory;
} var_data;

typedef struct {
	uint16_t 	opcode;
	uint8_t		mode_dd;
	uint8_t		dd;
	uint16_t	PC;
	uint16_t	dd_reg;
	char 	        instr[BUFF_SIZE];
} instr_single;

typedef struct {
	uint8_t 	opcode;
	uint8_t		mode_ss;
	uint8_t		ss;
	uint8_t		mode_dd;
	uint8_t		dd;
	uint16_t	PC;
	uint16_t	ss_reg;
	uint16_t	dd_reg;
	char	        instr[BUFF_SIZE];
} instr_double;

/**********

FUNCTIONS

***********/

/***** File I/O *****/
int rd_ascii_file(char *, char **, int *);

/***** String to Octal *****/
int str_to_oct(char **, unsigned long *, uint16_t *, int, uint16_t *, 
	       uint16_t, int *, var_data *, int *);

/***** Obj2Ascii *****/
int obj2ascii(char *);

/***** Word Instruction *****/
int get_instruction(uint16_t *, instr_single *, instr_double *, 
		    int, int *, int *, int, uint16_t *);

/***** Determin Valid Opcode *****/
int valid_opcode(uint16_t, uint16_t, int, char *); 

/***** Find Address Mode Source *****/
int ss_addr_mode(uint16_t, int, int *);

/***** Find Address Mode Destination *****/
int dd_addr_mode(uint16_t, int, int *, int);

/***** Store Source/Destination Values *****/
int store_reg_vals(uint16_t *, instr_single *, instr_double *, uint16_t*, int, int, int);

/***** Fetch Simulator Instructions *****/
int fetch_instructions(uint16_t *, instr_single *, instr_double *, uint16_t *, var_data *, 
		       sim_output *, int, int, int, int, int *);

/***** Get Memory Addresses for Data Accesses *****/
int data_mem_addr(uint16_t *, var_data *, uint16_t *, int, int); 
