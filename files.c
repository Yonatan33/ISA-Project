#define _CRT_SECURE_NO_WARNINGS

#include "files.h"




// open a file and check that its not null
// if it's NULL print an error and exit the simulator otherwise return the file's address
// input: file name, mode = "r" or "w"
// output: file address
FILE* get_file_pointer(const char file_name, char mode) {
	FILE* tmp_ptr = NULL;
	tmp_ptr = fopen(file_name, mode);
	if (tmp_ptr == NULL) {
		printf("problem with %d", f_num); // print error to indicate which file has the problem
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