#include <stdint.h>


/***** Addressing Modes *****/
static const uint16_t dd_REG		= 0000000;
static const uint16_t dd_REG_DEF	= 0000010;
static const uint16_t dd_AUT_INC	= 0000020;
static const uint16_t dd_AUT_INC_DEF	= 0000030;
static const uint16_t dd_AUT_DEC	= 0000040;
static const uint16_t dd_AUT_DEC_DEF	= 0000050;
static const uint16_t dd_IND		= 0000060;
static const uint16_t dd_IND_DEF	= 0000070;

static const uint16_t ss_REG		= 0000000;
static const uint16_t ss_REG_DEF	= 0001000;
static const uint16_t ss_AUT_INC	= 0002000;
static const uint16_t ss_AUT_INC_DEF	= 0003000;
static const uint16_t ss_AUT_DEC	= 0004000;
static const uint16_t ss_AUT_DEC_DEF	= 0005000;
static const uint16_t ss_IND		= 0006000;
static const uint16_t ss_IND_DEF	= 0007000;

/***** Program Counter Addressing *****/
static const uint16_t dd_IMM		= 0000027;
static const uint16_t dd_ABS		= 0000037;
static const uint16_t dd_REL		= 0000067;
static const uint16_t dd_REL_DEF	= 0000077;

static const uint16_t ss_IMM		= 0002700;
static const uint16_t ss_ABS		= 0003700;
static const uint16_t ss_REL		= 0006700;
static const uint16_t ss_REL_DEF	= 0007700;

/***** Halt Command - Stops Program *****/
static const uint16_t HALT	= 0000000; 

/***** Single Operand - Word *****/
static const uint16_t JMP 	= 0000100;
static const uint16_t SWAB	= 0000300;
static const uint16_t BR	= 0000400;
static const uint16_t BNE 	= 0001000;
static const uint16_t BEQ 	= 0001400;
static const uint16_t BGE 	= 0002000;
static const uint16_t BLT 	= 0002400;
static const uint16_t BGT 	= 0003000;
static const uint16_t BLE 	= 0003400;
static const uint16_t CLR 	= 0005000;
static const uint16_t COM	= 0005100;
static const uint16_t INC	= 0005200;
static const uint16_t DEC	= 0005300;
static const uint16_t NEG	= 0005400;
static const uint16_t ADC	= 0005500;
static const uint16_t SBC	= 0005600;
static const uint16_t ROR	= 0006000;
static const uint16_t ROL	= 0006100;
static const uint16_t ASR	= 0006200;
static const uint16_t ASL 	= 0006300;

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

