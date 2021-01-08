#ifndef REGISTERS
#define REGISTERS

#include <string.h>
#include <stdlib.h>
#include "general.h"

#define START_VALUE 0

typedef struct RegisterStruct {
	int value;
	int number;
	char name[6];
} Register;

typedef struct regIO {
	int myRegNum;
	int myNumOfBits;
	unsigned int myValue;
}registerIO;

// array for all registers
Register registersArray[NUM_OF_REGISTERS];


registerIO IORegisters[NUM_OF_IOREGISTERS] = {
	{ 0, 1, START_VALUE},		/*IORegisters[0] - irq0enable*/
	{ 1, 1, START_VALUE},		/*IORegisters[1] - irq1enable*/
	{ 2, 1, START_VALUE},		/*IORegisters[2] - irq2enable*/
	{ 3, 1, START_VALUE},		/*IORegisters[3] - irq0status*/
	{ 4, 1, START_VALUE},		/*IORegisters[4] - irq1status*/
	{ 5, 1, START_VALUE},		/*IORegisters[5] - irq2status*/
	{ 6, 12, START_VALUE},		/*IORegisters[6] - irqhandler*/
	{ 7, 12, START_VALUE},		/*IORegisters[7] - irqreturn*/
	{ 8, 32, START_VALUE},		/*IORegisters[8] - clks*/
	{ 9, 32, START_VALUE},		/*IORegisters[9] - leds*/
	{ 10, 32, START_VALUE},		/*IORegisters[10] - reserved*/
	{ 11, 1, START_VALUE},		/*IORegisters[11] - timerenable*/
	{ 12, 32, START_VALUE},		/*IORegisters[12] - timercurrent*/
	{ 13, 32, START_VALUE},		/*IORegisters[13] - timermax*/
	{ 14, 2, START_VALUE},		/*IORegisters[14] - diskcmd*/
	{ 15, 7, START_VALUE},		/*IORegisters[15] - disksector*/
	{ 16, 12, START_VALUE},		/*IORegisters[16] - diskbuffer*/
	{ 17, 1, START_VALUE},		/*IORegisters[17] - diskstatus*/
	{ 18, 1, START_VALUE},		/*IORegisters[18] - monitorcmd*/
	{ 19, 11, START_VALUE},		/*IORegisters[19] - monitorx*/
	{ 20, 10, START_VALUE},		/*IORegisters[20] - disksector*/
	{ 21, 8, START_VALUE}		/*IORegisters[21] - monitordata*/
};


#endif // !REGISTERS
