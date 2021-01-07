#ifndef GENERAL
#define GENERAL


#include "files.h"
#include <string.h>
#include <stdlib.h>

#define REGISTER_ADDRESS_LEN 1
#define OPPCODE_LEN 2
#define LINE_LEN (OPPCODE_LEN+3*REGISTER_ADDRESS_LEN+2)

#define NUMBER_OF_REGISTERS 16
#define MAX_TIME 

//instruction struct : 
typedef struct Instruction {
	int opcode; // 8 bits
	int rd; // 4 bits
	int rs; // 4 bits
	int rt; // 4 bits
	int immediate; // 20 bits
	int isType2; // flag for instructions using immediate
}Inst;

// create new instruction:
Inst* initInstruction();

int register2Val(char currentLine, int whichReg);

void applyOpcode(Inst* currentInstruction, ) // #complete







#endif