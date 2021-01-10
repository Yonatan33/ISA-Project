#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "general.h"

// Read all lines from the input file
// break the string into hexa numbers, then store them in structure's fields
// Put each instruction in it's PC place in the instructions array.
void initInstructionArray(FILE* imemInFile) {
	int localPC = 0;
	unsigned int temp;
	int tempImmediate;
	char currentInstructionLine[LINE_LEN]; //here we will get the line from file as string
	char currentInstructionImm[LINE_LEN+3];
	while (fgets(currentInstructionLine, LINE_LEN, imemInFile) != NULL) {
		temp = (unsigned int)strtol(currentInstructionLine, NULL, 16);
		instructionArray[localPC].opcode = 0xFF & (temp >> 12);
		instructionArray[localPC].rd = 0xF & (temp >> 8);
		instructionArray[localPC].rs = 0xF & (temp >> 4);
		instructionArray[localPC].rt = 0xF & temp;
		instructionArray[localPC].instructionFunc = instructionFuncArray[instructionArray[localPC].opcode];
		// checks if any of the registers uses reg number 1,
		// then we need to use the immediate
		if (instructionArray[localPC].rd == 1 || instructionArray[localPC].rs == 1 || instructionArray[localPC].rt == 1) {
			instructionArray[localPC].isType2 = 1;
			
			if (fgets(currentInstructionImm, LINE_LEN, imemInFile)) {
				currentInstructionImm[5] = '0';
				currentInstructionImm[6] = '0';
				currentInstructionImm[7] = '0';
				currentInstructionImm[8] = '\n';
				currentInstructionImm[9] = '\0';
				tempImmediate = (int)strtoul(currentInstructionImm, NULL, 16);
				instructionArray[localPC].immediate = tempImmediate >> 12;
			}
			localPC++;
		}
		localPC++;
	}	
}



void jumpTenBits(unsigned int rd) {
	PC = registersArray[rd].value & 0x3FF;
	jumpFlag = 1;
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
	insideInterrupt = 0;
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

Register registersArray[NUM_OF_REGISTERS] = {
	{0, "$zero"},	/*registersArray[0]*/
	{0, "$imm"},	/*registersArray[1]*/
	{0, "$v0"},		/*registersArray[2]*/
	{0, "$a0"},		/*registersArray[3]*/
	{0, "$a1"},		/*registersArray[4]*/
	{0, "$t0"},		/*registersArray[5]*/
	{0, "$t1"},		/*registersArray[6]*/
	{0, "$t2"},		/*registersArray[7]*/
	{0, "$t3"},		/*registersArray[8]*/
	{0, "$s0"},		/*registersArray[9]*/
	{0, "$s1"},		/*registersArray[10]*/
	{0, "$s2"},		/*registersArray[11]*/
	{0, "$gp"},		/*registersArray[12]*/
	{0, "$fp"},		/*registersArray[13]*/
	{0, "$rp"},		/*registersArray[14]*/
	{0, "$ra"}		/*registersArray[15]*/
};

registerIO IORegisters[NUM_OF_IOREGISTERS] = {
	{ 0, 1, START_VALUE},		/*IORegisters[0] - irq0enable*/
	{ 1, 1, START_VALUE},		/*IORegisters[1] - irq1enable*/
	{ 2, 1, START_VALUE},		/*IORegisters[2] - irq2enable*/
	{ 3, 1, START_VALUE},		/*IORegisters[3] - irq0status*/
	{ 4, 1, START_VALUE},		/*IORegisters[4] - irq1status*/
	{ 5, 1, START_VALUE},		/*IORegisters[5] - irq2status*/
	{ 6, 12, START_VALUE},		/*IORegisters[6] - irqhandler*/
	{ 7, 12, START_VALUE},		/*IORegisters[7] - irqreturn*/
	{ 8, 32, START_VALUE},		/*IORegisters[8] - clks*/
	{ 9, 32, START_VALUE},		/*IORegisters[9] - leds*/
	{ 10, 32, START_VALUE},		/*IORegisters[10] - reserved*/
	{ 11, 1, START_VALUE},		/*IORegisters[11] - timerenable*/
	{ 12, 32, START_VALUE},		/*IORegisters[12] - timercurrent*/
	{ 13, 32, START_VALUE},		/*IORegisters[13] - timermax*/
	{ 14, 2, START_VALUE},		/*IORegisters[14] - diskcmd*/
	{ 15, 7, START_VALUE},		/*IORegisters[15] - disksector*/
	{ 16, 12, START_VALUE},		/*IORegisters[16] - diskbuffer*/
	{ 17, 1, START_VALUE},		/*IORegisters[17] - diskstatus*/
	{ 18, 1, START_VALUE},		/*IORegisters[18] - monitorcmd*/
	{ 19, 11, START_VALUE},		/*IORegisters[19] - monitorx*/
	{ 20, 10, START_VALUE},		/*IORegisters[20] - disksector*/
	{ 21, 8, START_VALUE}		/*IORegisters[21] - monitordata*/
};


/*Check if clock interruption was triggered*/
int checkForIrq0() {
	if (IORegisters[TIMERCURRENT].myValue == IORegisters[TIMERMAX].myValue) {
		IORegisters[TIMERCURRENT].myValue = 0;
		return 1;
	}
	if (IORegisters[TIMERCURRENT].myValue > IORegisters[TIMERMAX].myValue) {	/*Triggered while instruction with immediate executed*/
		IORegisters[TIMERCURRENT].myValue = 1;
		return 1;
	}
	return 0;
}

int checkForIrq1() {
	if (diskCycle >= DISK_CYCLE_SIZE) {
		IORegisters[DISKCMD].myValue = 0;
		IORegisters[DISKSTATUS].myValue = 0;
		diskCycle = 0;
		return 1;
	}
	return 0;
}

/*Check if there is an irq2 interruption for current clock cycle
 *Considering the instruction executed - if it used immediate/performed a jump.
*/
int checkForIrq2(Inst* prevInstruction) {
	if (jumpFlag == 0) {
		if (PC < 2) {
			return 0;
		}
	}
	if (prevInstruction->isType2) {
		if (irq2values[0] == clockCycle - 1 || irq2values[0] == clockCycle) {
			return 1;
		}
	}
	else {
		if (irq2values[0] == clockCycle) {
			return 1;
		}
	}
	return 0;
}

void checkInterrupts(Inst* prevInstruction) {
	int irqFlag = 0;								/*Flag to indicate if one or more interrupts are ON (enable + status)*/
	int irq0Flag = 0, irq1Flag = 0, irq2Flag = 0;	/*Flags to indicate if an interruption was recieved after instruction was executed*/
	irq0Flag = checkForIrq0();
	if (irq0Flag) {
		IORegisters[IRQ_0_STATUS].myValue = 1;
	}
	if (irq1Flag) {
		IORegisters[IRQ_1_STATUS].myValue = 1;
	}
	irq2Flag = checkForIrq2(prevInstruction);
	if (irq2Flag) {
		IORegisters[IRQ_2_STATUS].myValue = 1;
		irq2values++;
	}
	irqFlag = ((IORegisters[IRQ_0_ENABLE].myValue & IORegisters[IRQ_0_STATUS].myValue) | 
		(IORegisters[IRQ_1_ENABLE].myValue & IORegisters[IRQ_1_STATUS].myValue) |
		(IORegisters[IRQ_2_ENABLE].myValue & IORegisters[IRQ_2_STATUS].myValue));
	if (irqFlag == 1 && insideInterrupt == 0) {
		insideInterrupt = 1;
		IORegisters[IRQRETURN].myValue = PC;
		PC = IORegisters[IRQHANDLER].myValue;
	}
}

void promoteTimer() {
	if (IORegisters[TIMERENABLE].myValue) {
		IORegisters[TIMERCURRENT].myValue++;
	}
}

void promoteDiskCycle() {
	if (diskON) {
		diskCycle++;
	}
}