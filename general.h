#ifndef GENERAL
#define GENERAL


#include "files.h"
#include <string.h>
#include <stdlib.h>

#define LINE_LEN 7

#define NUM_OF_REGISTERS 16
#define NUM_OF_IOREGISTERS 22
#define NUM_OF_OPCODES 22
#define MAX_IMEM_SIZE 1024
#define MAX_TIME 

static int PC;

//instruction struct : 
typedef struct iMEMCommand {
	unsigned int opcode; // 8 bits
	unsigned int rd; // 4 bits
	unsigned int rs; // 4 bits
	unsigned int rt; // 4 bits
	int immediate; // 20 bits
	int isType2; // flag for instructions using immediate
	void(*instructionFunc)(unsigned int rd, unsigned int rs, unsigned int rt);	//Pointer to execution function
}Inst;

void(* instructionFuncArray[NUM_OF_OPCODES])(unsigned int, unsigned int, unsigned int);		/*An array holding all function pointers for executing each instruction. */
// create new instruction
Inst instructionArray[MAX_IMEM_SIZE]; /*An array to hold all instructions read from imem file. instruction's PC is its array index*/
void initInstructionArray(); 












#endif
