#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>;
#include "general.h"
#include "files.h"
#include "registers.h"

// takes a line out of the input file
// break the string into hexa numbers, then store them in structure's fields
Inst* initInstruction() {
	Inst newInstruction;
	char currentInstructionLine[LINE_LEN]; //here we will get the line from file as string

	if (fgets(currentInstructionLine, LINE_LEN, fimemin) != NULL) {

		unsigned int temp = (int)strtol(currentInstructionLine, NULL, 16);
		newInstruction.opcode = 0xFF000 & temp;
		newInstruction.rd = 0x00F00 & temp;
		newInstruction.rs = 0x000F0 & temp;
		newInstruction.rd = 0x0000F & temp;

		// checks if any of the registers uses reg number 1,
		// then we need to use the immediate
		if (newInstruction.rd == 1 ||
			newInstruction.rs == 1 ||
			newInstruction.rt == 1) {
			newInstruction.isType2 = 1;

			//take the immediate value in the struct
			char currentInstructionImm[LINE_LEN - 1];
			fgets(currentInstructionImm, LINE_LEN - 1, fimemin);
			newInstruction.immediate = (int)strtol(currentInstructionImm, NULL, 16);

		}
	}

	return &newInstruction;
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
//Functionality: rs bitwise-and with rt, store in rd
void and(Inst* currentInstruction) {
	registersArray[currentInstruction->rd].value =
		registersArray[currentInstruction->rs].value & registersArray[currentInstruction->rt].value;
}


//Instruction *currInstruction: pointer to the current instruction
//Functionality: rs bitwise-or with rt, store in rd
void or (Inst* currentInstruction) {
	registersArray[currentInstruction->rd].value =
		registersArray[currentInstruction->rs].value | registersArray[currentInstruction->rt].value;
}


//Instruction *currInstruction: pointer to the current instruction
//Functionality: rs bitwise-xor with rt, store in rd
void xor (Inst* currentInstruction) {
	registersArray[currentInstruction->rd].value =
		registersArray[currentInstruction->rs].value ^ registersArray[currentInstruction->rt].value;
}


//Instruction *currInstruction: pointer to the current instruction
//Functionality: rs multiplied with rt, store in rd
void mul(Inst* currentInstruction) {
	registersArray[currentInstruction->rd].value =
		registersArray[currentInstruction->rs].value * registersArray[currentInstruction->rt].value;
}


//Instruction *currInstruction: pointer to the current instruction
//Functionality: rs is logical left shifted by rt, stored in rd
void sll(Inst* currentInstruction) {
	registersArray[currentInstruction->rd].value =
		registersArray[currentInstruction->rs].value << registersArray[currentInstruction->rt].value;
}


//Instruction *currInstruction: pointer to the current instruction
//Functionality: rs is arithmetical right shifted by rt, stored in rd
void sra(Inst* currentInstruction) {
	registersArray[currentInstruction->rd].value =
		registersArray[currentInstruction->rs].value >> registersArray[currentInstruction->rt].value;
}

// not sure it's OK - how to make a shift logical or arithmetical
//Instruction *currInstruction: pointer to the current instruction
//Functionality: rs is logical right shifted by rt, stored in rd
void srl(Inst* currentInstruction) {
	registersArray[currentInstruction->rd].value =
		(unsigned)registersArray[currentInstruction->rs].value >> registersArray[currentInstruction->rt].value;
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

