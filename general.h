#ifndef GENERAL
#define GENERAL


#include "files.h"
#include <string.h>
#include <stdlib.h>

#define LINE_LEN 7

#define NUMBER_OF_REGISTERS 16
#define MAX_TIME 

//instruction struct : 
typedef struct Instruction {
	unsigned int opcode; // 8 bits
	unsigned int rd; // 4 bits
	unsigned int rs; // 4 bits
	unsigned int rt; // 4 bits
	int immediate; // 20 bits
	int isType2; // flag for instructions using immediate
}Inst;

// create new instruction:
Inst* initInstruction();








#endif
