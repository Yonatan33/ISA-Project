#define _CRT_SECURE_NO_WARNINGS

#include "fileHandlers.h";
#include "general.h";
#include "registers.h";


void setBeforeStart(char *argv[]) {
	PC = 0;
	initFilePointers(argv);
	initInstructionArray();
	rewind(fimemin);
	readDMemIn();
}

void executeInstruction(Inst* currentInstruction) {
	unsigned int rd = currentInstruction->rd;
	unsigned int rs = currentInstruction->rs;
	unsigned int rt = currentInstruction->rt;
	currentInstruction->instructionFunc(rd, rs, rt);
}

void run() {
	Inst* currentInstruction;
	while (PC <= MAX_IMEM_SIZE) {
		currentInstruction = &instructionArray[PC];
		if (currentInstruction->isType2) {
			registersArray[1].value = currentInstruction->immediate;
			PC++;
		}
		PC++;
		executeInstruction(currentInstruction);
		
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
	static int PC = 0;
	return 0;
}


