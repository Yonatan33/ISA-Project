#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>;
#include "general.h"
#include "files.h"
#include "registers.h"

// takes the line we are working on right now, choose the wanted word 
// and make it an int.
// inputs: currentLine - string,the line we are dealing with; whichReg - rd, rs, or rt
// output: the address of the reg as an int
int register2Val(char currentLine, int whichReg) {
		char tempReg[REGISTER_ADDRESS_LEN];
		strncpy(tempReg, currentLine[OPPCODE_LEN+whichReg*REGISTER_ADDRESS_LEN], REGISTER_ADDRESS_LEN); //move the copy buffer according to the reg position in the code
		return strtoul(tempReg, , 16);
}

// takes a line out of the input file
// break the string into hexa numbers, then store them in structure's fields
Inst* initInstruction() {
	Inst* newInstruction;
	char currentInstructionLine[LINE_LEN]; //here we will get the line from file as string

	if (fgets(currentInstructionLine, LINE_LEN, fimemin) != NULL) {
		// take in the opcode
		char tempOpcode[OPPCODE_LEN], *trash;
		strncpy(tempOpcode, currentInstructionLine, OPPCODE_LEN);
		newInstruction.opcode = strtoul(tempOpcode, trash, 16); // makes line to int in base 16

		// take the registers:
		newInstruction.rd = register2Val(currentInstructionLine, 0);
		newInstruction.rs = register2Val(currentInstructionLine, 1);
		newInstruction.rt = register2Val(currentInstructionLine, 2);


		// check if we need to use the immediate
		if (newInstruction.rd == 1 ||
			newInstruction.rs == 1 ||
			newInstruction.rt == 1) {
			newInstruction.isType2 = 1;

			//take the immediate value in the struct
			char currentInstructionImm[LINE_LEN - 1];
			fgets(currentInstructionImm, LINE_LEN - 1, fimemin);
			newInstruction.immediate = strtoul(currentInstructionImm, trash, 16);
			getchar();

		}
	}
	
	return newInstruction;
}



//Instruction *currInstruction: pointer to the current instruction on the memory
//Functionality: function adds the arguments in register rs and rt, saves it to rd
void add(Inst* currentInstruction) {
	registersArray[currentInstruction->rd].value =
		registersArray[currentInstruction->rs].value + registersArray[currentInstruction->rt].value;
}

//Instruction *currInstruction: pointer to the current instruction
//Functionality: function subtracts the arguments in register rt from rs, saves it to rd
void sub(Inst* currentInstruction) {
	registersArray[currentInstruction->rd].value =
		registersArray[currentInstruction->rs].value - registersArray[currentInstruction->rt].value;
}


//Instruction *currInstruction: pointer to the current instruction
//Functionality: function subtracts the arguments in register rs and rt, saves it to rd
void sub(Inst* currentInstruction, int PC, int *REG) {
	registersArray[currentInstruction->rd].value =
		registersArray[currentInstruction->rs].value + registersArray[currentInstruction->rt].value;
	PC++;
}

//Instruction *currInstruction: pointer to the current instruction
//Functionality: function subtracts the arguments in register rs and rt, saves it to rd
void sub(Inst* currentInstruction, int PC, int *REG) {
	registersArray[currentInstruction->rd].value =
		registersArray[currentInstruction->rs].value + registersArray[currentInstruction->rt].value;
	PC++;
}


//Instruction *currentInstruction: pointer to the current instruction
//REG - register array
//Output arguments : PC
//Functionality: function subs tha arguments in register rs and rt
void sub(Inst* currentInstruction, int PC, Register *REG) {
	REG[currentInstruction->rd] = REG[currentInstruction->rs] - REG[currentInstruction->rt];
	PC += 1;
	return PC;
}

//Input argument:
//Instruction *curr_ptr: pointer to the current instruction on the memory
//PC: the current PC , REG -register array
//Output arguments :New PC
//Functionality: function "and" tha arguments in register rs and rt
int and (Inst1* curr_ptr, int PC, int *REG) {
	REG[curr_ptr->rd] = REG[curr_ptr->rs] & REG[curr_ptr->rt];
	PC += 1;
	return PC;
}

//Input argument:
//Instruction *curr_ptr: pointer to the current instruction on the memory
//PC: the current PC , REG -register array
//Output arguments : New PC
//Functionality: function "or" tha arguments in register rs and rt
int or (Inst1* curr_ptr, int PC, int *REG) {
	REG[curr_ptr->rd] = REG[curr_ptr->rs] | REG[curr_ptr->rt];
	PC += 1;
	return PC;
}

xor
mul

//Input argument:
//Instruction *curr_ptr: pointer to the current instruction on the memory
//PC: the current PC , REG -register array
//Outputarguments : New PC
//Functionality: function shift logical left
int sll(Inst* curr_ptr, int PC, int *REG) {
	REG[curr_ptr->rd] = REG[curr_ptr->rs] << REG[curr_ptr->rt];
	PC += 1;
	return PC;
}

//Input argument:
//Instruction *curr_ptr: pointer to the current instruction on the memory
//PC: the current PC , REG -register array
//Output: New PC
//Functionality: function shift right arithmetic
int sra(Inst* curr_ptr, int PC, int *REG) {
	REG[curr_ptr->rd] = REG[curr_ptr->rs] >> REG[curr_ptr->rt];
	PC += 1;
	return PC;
}


//Input argument:
//Instruction *curr_ptr: pointer to the current instruction on the memory
//PC: the current PC , REG -register array
//Output: New PC
//Functionality: function shift right logical
int srl(Inst* curr_ptr, int PC, int *REG) {
	if (REG[curr_ptr->rs] >= 0) {
		if (REG[curr_ptr->rt] > 0) {
			int mask = REG[curr_ptr->rs] >> 31 << 31 >> (REG[curr_ptr->rt]) << 1;
			REG[curr_ptr->rd] = mask ^ (REG[curr_ptr->rs] >> REG[curr_ptr->rt]);
		}
		else if (REG[curr_ptr->rt] < 0) {
			printf("Cannot Shift By A Neggative Value. No Action Taken.\n");
		}
	}
	else {
		printf("Cannot Shift A Neggative Number. No Action Taken.\n");
	}
	PC += 1;
	return PC;
}


void applyOpcode(Inst* currentInstruction, ) {
	switch (currentInstruction->opcode) {
	case(0):
		new_PC = add(curr_ptr, PC, REG);
		break;
	case(1):
		new_PC = sub(curr_ptr, PC, REG);
		break;
	case(2):
		new_PC = and (curr_ptr, PC, REG);
		break;
	case(3):
		new_PC = or (curr_ptr, PC, REG);
		break;
	case(4):
		new_PC = sll(curr_ptr, PC, REG);
		break;
	case(5):
		new_PC = sra(curr_ptr, PC, REG);
		break;
	case(6):
		new_PC = srl(curr_ptr, PC, REG);
		break;
}
