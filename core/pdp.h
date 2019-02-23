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

/***** Single Operand - Word *****/
static const uint16_t JMP 	= 000100;
static const uint16_t SWAB	= 000300;
static const uint16_t BR	= 000400;
static const uint16_t BNE 	= 001000;
static const uint16_t BEQ 	= 001400;
static const uint16_t BGE 	= 002000;
static const uint16_t BLT 	= 002400;
static const uint16_t BGT 	= 003000;
static const uint16_t BLE 	= 003400;
static const uint16_t CLR 	= 005000;
static const uint16_t COM	= 005100;
static const uint16_t INC	= 005200;
static const uint16_t DEC	= 005300;
static const uint16_t NEG	= 005400;
static const uint16_t ADC	= 005500;
static const uint16_t SBC	= 005600;
static const uint16_t ROR	= 006000;
static const uint16_t ROL	= 006100;
static const uint16_t ASR	= 006200;
static const uint16_t ASL 	= 006300;

/***** Double Operand - Word *****/
static const uint16_t MOV 	= 0010000;
static const uint16_t CMP 	= 0020000;
static const uint16_t BIT 	= 0030000;
static const uint16_t BIC 	= 0040000;
static const uint16_t BIS 	= 0050000;
static const uint16_t ADD 	= 0060000;
static const uint16_t MUL 	= 0070000;
static const uint16_t DIV 	= 0071000;
static const uint16_t ASH 	= 0072000;
static const uint16_t ASHC 	= 0073000;
static const uint16_t XOR 	= 0074000;

/**** Single Operand - Byte *****/
static const uint16_t BPL 	= 0100000;
static const uint16_t BMI 	= 0100400;
static const uint16_t BHI 	= 0101000;
static const uint16_t BLOS 	= 0101400;
static const uint16_t BVC 	= 0102000;
static const uint16_t BVS 	= 0102400;
static const uint16_t BCC 	= 0103000;
static const uint16_t BCS 	= 0103400;
static const uint16_t CLRB 	= 0105000;
static const uint16_t COMB 	= 0105100;
static const uint16_t INCB 	= 0105200;
static const uint16_t DECB 	= 0105300;
static const uint16_t NEGB 	= 0105400;
static const uint16_t ADCB 	= 0105500;
static const uint16_t SBCB 	= 0105600;
static const uint16_t RORB 	= 0106000;
static const uint16_t ROLB 	= 0106100;
static const uint16_t ASRB 	= 0106200;
static const uint16_t ASLB 	= 0106300;

/***** Double Operand - Byte *****/
static const uint16_t MOVB 	= 0110000;
static const uint16_t CMPB 	= 0120000;
static const uint16_t BITB 	= 0130000;
static const uint16_t BICB 	= 0140000;
static const uint16_t BISB 	= 0150000;
static const uint16_t SUB 	= 0160000;

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
int str_to_oct(char **, unsigned long *, uint16_t *, int, uint16_t *);

/***** Obj2Ascii *****/
int obj2ascii();

/***** Word Instruction *****/
int get_instruction(uint16_t *, instr_single *, instr_double *, 
		    int, int *, int *);

/***** Determin Valid Opcode *****/
int valid_opcode(uint16_t, uint16_t, int); 
