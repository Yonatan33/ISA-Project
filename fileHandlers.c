#define _CRT_SECURE_NO_WARNINGS

#include "fileHandlers.h"




// open a file and check that its not null
// if it's NULL print an error and exit the simulator otherwise return the file's address
// input: file name, mode = "r" or "w"
// output: file address
FILE* get_file_pointer(const char file_name, char mode) {
	FILE* tmp_ptr = NULL;
	tmp_ptr = fopen(file_name, mode);
	if (tmp_ptr == NULL) {
		printf("Error opening file %d, named: %s", f_num, file_name); // print error to indicate which file has the problem
		exit(1);
	}
	f_num++;
	return tmp_ptr;

}

// initialize all file ptrs:
void initFilePointers(char** argv) {
	fimemin = get_file_pointer(argv[f_num], "r");
	fdmemin = get_file_pointer(argv[f_num], "r");
	fdiskin = get_file_pointer(argv[f_num], "r");
	firq2in = get_file_pointer(argv[f_num], "r");
	fdmemout = get_file_pointer(argv[f_num], "w");
	fregout = get_file_pointer(argv[f_num], "w");
	ftrace = get_file_pointer(argv[f_num], "w");
	fhwregtrace = get_file_pointer(argv[f_num], "w");
	fcycles = get_file_pointer(argv[f_num], "w");
	fleds = get_file_pointer(argv[f_num], "w");
	fmonitor = get_file_pointer(argv[f_num], "w");
	fmonitor2 = get_file_pointer(argv[f_num], "w");
	fdiskout = get_file_pointer(argv[f_num], "w");
}

void readDMemIn() {
	char dmemLine[DMEM_LINE_SIZE + 2];	/*  add 1 for '\n' and 1 for '\0'  */
	int index = 0;
	while (fgets(dmemLine, DMEM_LINE_SIZE + 2, fdmemin) != NULL) {
		dmemArray[index] = strtol(dmemLine, NULL, 16);
		index++;
	}

}

void closeFiles() {
	fclose(fimemin);
	fclose(fdmemin);
	fclose(fdiskin);
	fclose(firq2in);
	fclose(fdmemout);
	fclose(fregout);
	fclose(ftrace);
	fclose(fhwregtrace);
	fclose(fcycles);
	fclose(fleds);
	fclose(fmonitor);
	fclose(fmonitor);
	fclose(fdiskout);
}