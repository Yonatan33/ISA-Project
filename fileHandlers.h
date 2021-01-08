#ifndef FILE_HANDLERS
#define FILE_HANDLERS

#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_FILES 13
#define DMEM_LINE_SIZE 8
#define MAX_DMEM_SIZE 4096
// variables declerations:
FILE* fimemin; // instructions memory
FILE* fdmemin; // data memory
FILE* fdiskin;
FILE* firq2in;
FILE* fdmemout;
FILE* fregout;
FILE* ftrace;
FILE* fhwregtrace;
FILE* fcycles;
FILE* fleds;
FILE* fmonitor;
FILE* fmonitor2;
FILE* fdiskout;

static int f_num = 0;
static int dmemArray[MAX_DMEM_SIZE] = { 0 };
void initFilePointers(char** argv);
void readDMemIn();
void closeFiles();
FILE* get_file_pointer(const char file_name, char mode);

#endif