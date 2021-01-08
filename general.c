#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>;
#include "general.h"
#include "fileHandlers.h"
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



void jumpTenBits(unsigned int rd) {
	PC = registersArray[rd].value & 0x3FF;
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

/*Brench if Equal - if content of rs, rt registers is the same, jump the PC to rd's content (last 10 bits)*/
void beq(unsigned int rd, unsigned int rs, unsigned int rt) {
	if (registersArray[rs].value == registersArray[rt].value) {
		jumpTenBits(rd);
	}
}

/*Brench if Not Equal - if content of rs, rt registers is different, jump the PC to rd's content (last 10 bits)*/
void bne(unsigned int rd, unsigned int rs, unsigned int rt) {
	if (!(registersArray[rs].value == registersArray[rt].value)) {
		jumpTenBits(rd);
	}
}

/*Brench if Less Than - if content of rs is smaller than the content of rt, jump the PC to rd's content (last 10 bits)*/
void blt(unsigned int rd, unsigned int rs, unsigned int rt) {
	if (registersArray[rs].value < registersArray[rt].value) {
		jumpTenBits(rd);
	}
}

/*Brench if Greater Than - if content of rs is bigger than the content of rt, jump the PC to rd's content (last 10 bits)*/
void bgt(unsigned int rd, unsigned int rs, unsigned int rt) {
	if (registersArray[rs].value > registersArray[rt].value) {
		jumpTenBits(rd);
	}
}

/*Brench if Less than or Equal - if content of rs is smaller (or equal) than the content of rt, jump the PC to rd's content (last 10 bits)*/
void ble(unsigned int rd, unsigned int rs, unsigned int rt) {
	if (registersArray[rs].value <= registersArray[rt].value) {
		jumpTenBits(rd);
	}
}

/*Brench if Greater than or Equqal - if content of rs is bigger (or equal) than the content of rt, jump the PC to rd's content (last 10 bits)*/
void bge(unsigned int rd, unsigned int rs, unsigned int rt) {
	if (registersArray[rs].value >= registersArray[rt].value) {
		jumpTenBits(rd);
	}
}

/*Jump And Link - set the $ra register to the next PC (already there), and jump the PC to rd's content (last 10 bits)*/
void jal(unsigned int rd, unsigned int rs, unsigned int rt) {
	registersArray[15].value = PC;
	jumpTenBits(rd);
}

/*Load Word = take sum of registers rs,rt contents, and use it as index in dmem array's data, put it in rd's content*/
void lw(unsigned int rd, unsigned int rs, unsigned int rt) {
	registersArray[rd].value = dmemArray[registersArray[rs].value + registersArray[rt].value];
}

/*Store Word = take sum of registers rs,rt contents, and use it as index in dmem array's data, put rd's content in this index*/
void sw(unsigned int rd, unsigned int rs, unsigned int rt) {
	dmemArray[registersArray[rs].value + registersArray[rt].value] = registersArray[rd].value;
}

/*Return to the instruction from interrupt - put in PC the content of IOregisters[7]*/
void reti(unsigned int rd, unsigned int rs, unsigned int rt) {
	PC = IORegisters[7].myValue;
}

/*Same as Load Word, but now from the IORegisters array, taking the register's content*/
void in(unsigned int rd, unsigned int rs, unsigned int rt) {
	registersArray[rd].value = IORegisters[registersArray[rs].value + registersArray[rt].value].myValue;
}

/*Same as Store Word, but now from the IORegisters array, taking the register's content*/
void out(unsigned int rd, unsigned int rs, unsigned int rt) {
	IORegisters[registersArray[rs].value + registersArray[rt].value].myValue = registersArray[rd].value;
}

/*Exits the program by adjusting PC to break from main run loop */
void halt(unsigned int rd, unsigned int rs, unsigned int rt) {
	PC = MAX_IMEM_SIZE + 1;
}





void(*instructionFuncArray[NUM_OF_OPCODES])(unsigned int, unsigned int, unsigned int) = {
	{&add},
	{&sub},
	{&and},
	{&or },
	{&xor},
	{&mul},
	{&sll},
	{&sra},
	{&srl},
	{&beq},
	{&bne},
	{&blt},
	{&bgt},
	{&ble},
	{&bge},
	{&jal},
	{&lw},
	{&sw},
	{&reti},
	{&in},
	{&out},
	{&halt}
};
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

