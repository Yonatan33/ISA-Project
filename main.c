#define _CRT_SECURE_NO_WARNINGS


#include "GlobalUse.h"
#include "fileHandlers.h"
#include "general.h"


void setBeforeStart(char *argv[]) {
	PC = 0;
	clockCycle = 0;
	diskCycle = 0;
	insideInterrupt = 0;
	jumpFlag = 0;
	diskON = 0;
	initFilePointers(argv);
	initInstructionArray(fimemin);
	rewind(fimemin);
	readDMemIn();
	readIrq2In();
	//readDiskIn();
}

void executeInstruction(Inst* currentInstruction) {
	unsigned int rd = currentInstruction->rd;
	unsigned int rs = currentInstruction->rs;
	unsigned int rt = currentInstruction->rt;
	currentInstruction->instructionFunc(rd, rs, rt);
}


/*Implementation of the fetch-decode-execute loop*/
void run() {
	Inst* currentInstruction;
	while (PC <= MAX_IMEM_SIZE) {
		currentInstruction = &(instructionArray[PC]);
		writeTraceOutput(currentInstruction->opcode);		/*Writing to trace output before PC and registers are changed*/
		if (currentInstruction->isType2) {
			registersArray[1].value = currentInstruction->immediate;
			PC++;
			clockCycle++;
			promoteTimer();
			promoteDiskCycle();
		}
		PC++;
		clockCycle++;
		promoteTimer();
		promoteDiskCycle();
		executeInstruction(currentInstruction);
		/*Function is executed, PC is promoted, now need to check for interrupts and change PC accordingly*/
		checkInterrupts(currentInstruction);
		jumpFlag = 0;

	}
}

void setBeforeExit() {
	closeFiles();
}
int main(int argc, char *argv[]) {
	// we expect to get 13 files
	if (argc != 14) {
		printf("Not enough input files. Exit program.\n");
		exit(1);
	}
	setBeforeStart(argv);
	run();
	setBeforeExit();

	return 0;
}


