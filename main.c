#define _CRT_SECURE_NO_WARNINGS

#include "files.h";
#include "general.h";
#include "registers.h";


void setBeforeStart(char *argv[]) {
	PC = 0;
	initFilePointers(argv);
	initCommands();
	rewind(fimemin);
}

void executeInstruction() {



}

void run() {
	while (PC <= MAX_IMEM_SIZE) {
		executeInstruction();

	}
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


