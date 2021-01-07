#ifndef FILES
#define FILES

#include <stdio.h>

#define NUMBER_OF_FILES 13

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

void initFilePointers();
FILE* get_file_pointer(const char file_name, char mode);

#endif