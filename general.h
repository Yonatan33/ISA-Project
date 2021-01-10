#ifndef GENERAL
#define GENERAL

#include <string.h>
#include <stdlib.h>
#include "GlobalUse.h"
#include "diskHandler.h"
#include "monitorHandler.h"
#include "fileHandlers.h"

void initInstructionArray(FILE* imemInFile);
void checkInterrupts(Inst* prevInstruction);
void promoteTimer();
void writeLedsOut();
void promoteDiskCycle();
void(*instructionFuncArray[NUM_OF_OPCODES])(unsigned int, unsigned int, unsigned int);		/*An array holding all function pointers for executing each instruction. */

#endif
