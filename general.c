#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>;
#include "general.h"
#include "files.h"
#include "registers.h"

// Read all lines from the input file
// break the string into hexa numbers, then store them in structure's fields
// Put each instruction in it's PC place in the instructions array.
void initInstructionArray() {
	int localPC = 0;
	unsigned int temp;
	char currentInstructionLine[LINE_LEN]; //here we will get the line from file as string
	char currentInstructionImm[LINE_LEN - 1];
	while (fgets(currentInstructionLine, LINE_LEN, fimemin) != NULL) {
		temp = (unsigned int)strtol(currentInstructionLine, NULL, 16);
		instructionArray[localPC].opcode = 0xFF & (temp >> 12);
		instructionArray[localPC].rd = 0xF & (temp >> 8);
		instructionArray[localPC].rs = 0xF & (temp >> 4);
		instructionArray[localPC].rd = 0xF & temp;
		// checks if any of the registers uses reg number 1,
		// then we need to use the immediate
		if (instructionArray[localPC].rd == 1 || instructionArray[localPC].rs == 1 || instructionArray[localPC].rt == 1) {
			instructionArray[localPC].isType2 = 1;
			localPC++;
			if (fgets(currentInstructionImm, LINE_LEN - 1, fimemin)) {
				instructionArray[localPC].immediate = (unsigned int)strtol(currentInstructionImm, NULL, 16);
			}
		}
		localPC++;
	}

	
}





//Instruction *currInstruction: pointer to the current instruction on the memory
//Functionality: function adds the arguments in register rs and rt, saves it to rd
void add(unsigned int rd, unsigned int rs, unsigned int rt) {
	registersArray[rd].value =
		registersArray[rs].value + registersArray[rt].value;
}

//Instruction *currInstruction: pointer to the current instruction
//Functionality: function subtracts the arguments in register rt from rs, saves it to rd
void sub(unsigned int rd, unsigned int rs, unsigned int rt) {
	registersArray[rd].value =
		registersArray[rs].value - registersArray[rt].value;
}


//Instruction *currInstruction: pointer to the current instruction
//Functionality: rs bitwise-and with rt, store in rd
void and(unsigned int rd, unsigned int rs, unsigned int rt) {
	registersArray[rd].value =
		registersArray[rs].value & registersArray[rt].value;
}


//Instruction *currInstruction: pointer to the current instruction
//Functionality: rs bitwise-or with rt, store in rd
void or (unsigned int rd, unsigned int rs, unsigned int rt) {
	registersArray[rd].value =
		registersArray[rs].value | registersArray[rt].value;
}


//Instruction *currInstruction: pointer to the current instruction
//Functionality: rs bitwise-xor with rt, store in rd
void xor (unsigned int rd, unsigned int rs, unsigned int rt) {
	registersArray[rd].value =
		registersArray[rs].value ^ registersArray[rt].value;
}


//Instruction *currInstruction: pointer to the current instruction
//Functionality: rs multiplied with rt, store in rd
void mul(unsigned int rd, unsigned int rs, unsigned int rt) {
	registersArray[rd].value =
		registersArray[rs].value * registersArray[rt].value;
}


//Instruction *currInstruction: pointer to the current instruction
//Functionality: rs is logical left shifted by rt, stored in rd
void sll(unsigned int rd, unsigned int rs, unsigned int rt) {
	registersArray[rd].value =
		registersArray[rs].value << registersArray[rt].value;
}


//Instruction *currInstruction: pointer to the current instruction
//Functionality: rs is arithmetical right shifted by rt, stored in rd
void sra(unsigned int rd, unsigned int rs, unsigned int rt) {
	registersArray[rd].value =
		registersArray[rs].value >> registersArray[rt].value;
}

// not sure it's OK - how to make a shift logical or arithmetical
//Instruction *currInstruction: pointer to the current instruction
//Functionality: rs is logical right shifted by rt, stored in rd
void srl(unsigned int rd, unsigned int rs, unsigned int rt) {
	registersArray[rd].value =
		(unsigned)registersArray[rs].value >> registersArray[rt].value;
}


instructionFuncArray = {
	{&add}, 
	{&sub},
	{&and}, 
	{&or}, 
	{&xor}, 
	{&mul}, 
	{&sll}, 
	{&sra}, 
	{&srl}, 
	{&add}, 
	{&add}, 
	{&add}, 
	{&add}, 
	{&add}, 
	{&add}, 
	{&add}, 
	{&add}, 
	{&add}, 
	{&add}, 
	{&add}, 
	{&add}, 
	{&add},
}
//
////Input argument:
////Instruction *curr_ptr: pointer to the current instruction on the memory
////PC: the current PC , REG -register array
////Output: New PC
////Functionality: function shift right logical
//int srl(Inst* curr_ptr, int PC, int *REG) {
//	if (REG[curr_ptr->rs] >= 0) {
//		if (REG[curr_ptr->rt] > 0) {
//			int mask = REG[curr_ptr->rs] >> 31 << 31 >> (REG[curr_ptr->rt]) << 1;
//			REG[curr_ptr->rd] = mask ^ (REG[curr_ptr->rs] >> REG[curr_ptr->rt]);
//		}
//		else if (REG[curr_ptr->rt] < 0) {
//			printf("Cannot Shift By A Neggative Value. No Action Taken.\n");
//		}
//	}
//	else {
//		printf("Cannot Shift A Neggative Number. No Action Taken.\n");
//	}
//	PC += 1;
//	return PC;
//}
//

