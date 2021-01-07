#define _CRT_SECURE_NO_WARNINGS

#include "files.h";
#include "general.h";
#include "registers.h";


int main(int argc, char *argv[]) {
	// we expact to get 13 files
	if (argc != 14) {
		printf("Not enough input files. Exit program.\n");
		exit(1);
	}
	initFilePointers(argv);


	static int PC = 0;
	fetch & decode // taking instruction from imem, execute





		return 0;
}


