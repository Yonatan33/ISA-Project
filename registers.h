#ifndef REGISTERS
#define REGISTERS

#include <string.h>
#include <stdlib.h>
#include "general.h"

typedef struct RegisterStruct {
	int value;
	int number;
	char name[6];
} Register;

// array for all registers
Register registersArray[NUMBER_OF_REGISTERS];


#endif // !REGISTERS


