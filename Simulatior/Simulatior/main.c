#define _CRT_SECURE_NO_WARNINGS


#include "GlobalUse.h"
#include "fileHandlers.h"
#include "general.h"

/*Make all the preparations befor execution:
 *Open all the files.
 *Set all the variables that need to be set to a starting value.
 *Read Data from input files and put in data structures.
*/
void setBeforeStart(char *argv[]) {
	PC = 0;
	clockCycle = 0;
	diskCycle = 0;
	insideInterrupt = 0;
	jumpFlag = 0;
	diskON = 0;
	instructionsCount = 0;
	initFilePointers(argv);
	initInstructionArray(fimemin);
	rewind(fimemin);
	readDMemIn();
	readIrq2In();
	readDiskIn();

}

/*Call the instruction's function*/
void executeInstruction(Inst* currentInstruction) {
	unsigned int rd = currentInstruction->rd;
	unsigned int rs = currentInstruction->rs;
	unsigned int rt = currentInstruction->rt;
	currentInstruction->instructionFunc(rd, rs, rt);
}


/*Implementation of the fetch-decode-execute loop:
*Check the PC
*Get the PC's related instruction
*Update the immediate befor writing the regtrace.
*Promote all relevant counters.
*Execute the instruction.
*Write the HWregtrace.
*Check for interrupts.
*Update more counters.
*/
void run() {
	Inst* currentInstruction;
	while (PC <= MAX_IMEM_SIZE) {
		currentInstruction = &(instructionArray[PC]);
		if (currentInstruction->isType2) {
			registersArray[1].value = currentInstruction->immediate;
		}
		writeTraceOutput(currentInstruction->opcode);		/*Writing to trace output before PC and registers (except for immediate) are changed*/
		if (currentInstruction->isType2) {
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
		writeHWRegTraceOut(currentInstruction);
		/*Function is executed, PC is promoted, now need to check for interrupts and change PC accordingly*/
		checkInterrupts(currentInstruction);
		jumpFlag = 0;
		instructionsCount++;

	}
}


/*Write to files, free memory and close opened files*/
void setBeforeExit(int* pointerToFree) {
	writeDMemOut();
	writeRegOut();
	writeMonitorOut();
	writeMonitorYUVOut();
	writeDiskOut();
	writeCycles();
	free(pointerToFree);
	closeFiles();
}
int main(int argc, char *argv[]) {
	int* pointerToFree;
	// we expect to get 13 files
	if (argc != 14) {
		printf("Not enough input files. Exit program.\n");
		exit(1);
	}
	setBeforeStart(argv);
	pointerToFree = irq2values;
	run();
	setBeforeExit(pointerToFree);

	return 0;
}


