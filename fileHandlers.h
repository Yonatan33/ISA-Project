#ifndef FILE_HANDLERS
#define FILE_HANDLERS


/* Header designed to handle operations done on files
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "GlobalUse.h"


#define NUMBER_OF_FILES 13
#define DMEM_LINE_SIZE 8

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


static int f_num = 1;

void initFilePointers(char* argv[]);
void readDMemIn();
void readIrq2In();
void readDiskIn();
void writeTraceOutput(unsigned int opcode);
void writeHWRegTraceOut(Inst* currentInstruction);
void writeDMemOut();
void writeRegOut();
void writeMonitorOut();
void writeMonitorYUVOut();
void writeDiskOut();
void writeCycles();
void closeFiles();


#endif