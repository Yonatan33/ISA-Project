
#ifndef GENERAL
#define GENERAL

/*Header for general purposes, defining some of the functions used by main*/

#include <string.h>
#include <stdlib.h>
#include "GlobalUse.h"
#include "diskHandler.h"
#include "monitorHandler.h"
#include "fileHandlers.h"

void initInstructionArray(FILE* imemInFile);
void checkInterrupts(Inst* prevInstruction);
void promoteTimer();
void writeLedsOut(unsigned int rd, unsigned int rs, unsigned int rt);		/*NOT used externally, only here to indicate writeLedOut is in general module*/
void promoteDiskCycle();

void(*instructionFuncArray[NUM_OF_OPCODES])(unsigned int, unsigned int, unsigned int);		/*An array holding all function pointers for executing each instruction. */


#endif
