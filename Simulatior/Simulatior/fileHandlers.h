#ifndef FILE_HANDLERS
#define FILE_HANDLERS


/* Header designed to handle operations done on files
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "GlobalUse.h"

#define DMEM_LINE_SIZE 8

 /*********************************  File pointers  *********************************/

FILE* fimemin;		// instructions memory input
FILE* fdmemin;		// data memory input
FILE* fdiskin;		// disk input
FILE* firq2in;		// irq2 interrupt times input
FILE* fdmemout;		// data memory output
FILE* fregout;		// register data output
FILE* ftrace;		//trace output
FILE* fhwregtrace;  //IOregisters trace output
FILE* fcycles;		//clock cycles output
FILE* fleds;		//leds output
FILE* fmonitor;		//monitor output
FILE* fmonitor2;	//monitor's yuv output
FILE* fdiskout;		//disk data output


 /*********************************  Variables and functions implemented  *********************************/

static int f_num = 1; //opened fils counter

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