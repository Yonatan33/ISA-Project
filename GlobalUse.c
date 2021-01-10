#include "GlobalUse.h"

dmemArray[MAX_DMEM_SIZE] = { 0 };
diskArray[NUM_OF_DISK_SECTORS][DISK_SECTOR_SIZE] = { 0 };
monitorArray[MONITOR_SIZE_X][MONITOR_SIZE_Y] = { 0 };


Register registersArray[NUM_OF_REGISTERS] = {
	{0, "$zero"},	/*registersArray[0]*/
	{0, "$imm"},	/*registersArray[1]*/
	{0, "$v0"},		/*registersArray[2]*/
	{0, "$a0"},		/*registersArray[3]*/
	{0, "$a1"},		/*registersArray[4]*/
	{0, "$t0"},		/*registersArray[5]*/
	{0, "$t1"},		/*registersArray[6]*/
	{0, "$t2"},		/*registersArray[7]*/
	{0, "$t3"},		/*registersArray[8]*/
	{0, "$s0"},		/*registersArray[9]*/
	{0, "$s1"},		/*registersArray[10]*/
	{0, "$s2"},		/*registersArray[11]*/
	{0, "$gp"},		/*registersArray[12]*/
	{0, "$fp"},		/*registersArray[13]*/
	{0, "$rp"},		/*registersArray[14]*/
	{0, "$ra"}		/*registersArray[15]*/
};

registerIO IORegisters[NUM_OF_IOREGISTERS] = {
	{ 0, 1, START_VALUE, "irq0enable"},		/*IORegisters[0] - irq0enable*/
	{ 1, 1, START_VALUE, "irq1enable"},		/*IORegisters[1] - irq1enable*/
	{ 2, 1, START_VALUE, "irq2enable"},		/*IORegisters[2] - irq2enable*/
	{ 3, 1, START_VALUE, "irq0status"},		/*IORegisters[3] - irq0status*/
	{ 4, 1, START_VALUE, "irq1status"},		/*IORegisters[4] - irq1status*/
	{ 5, 1, START_VALUE, "irq2status"},		/*IORegisters[5] - irq2status*/
	{ 6, 12, START_VALUE, "irqhandler"},	/*IORegisters[6] - irqhandler*/
	{ 7, 12, START_VALUE, "irqreturn"},		/*IORegisters[7] - irqreturn*/
	{ 8, 32, START_VALUE, "clks"},			/*IORegisters[8] - clks*/
	{ 9, 32, START_VALUE, "leds"},			/*IORegisters[9] - leds*/
	{ 10, 32, START_VALUE, "reserved"},		/*IORegisters[10] - reserved*/
	{ 11, 1, START_VALUE, "timerenable"},	/*IORegisters[11] - timerenable*/
	{ 12, 32, START_VALUE, "timercurrent"},	/*IORegisters[12] - timercurrent*/
	{ 13, 32, START_VALUE, "timermax"},		/*IORegisters[13] - timermax*/
	{ 14, 2, START_VALUE, "diskcmd"},		/*IORegisters[14] - diskcmd*/
	{ 15, 7, START_VALUE, "disksector"},	/*IORegisters[15] - disksector*/
	{ 16, 12, START_VALUE, "diskbuffer"},	/*IORegisters[16] - diskbuffer*/
	{ 17, 1, START_VALUE, "diskstatus"},	/*IORegisters[17] - diskstatus*/
	{ 18, 1, START_VALUE, "monitorcmd"},	/*IORegisters[18] - monitorcmd*/
	{ 19, 11, START_VALUE, "monitorx"},		/*IORegisters[19] - monitorx*/
	{ 20, 10, START_VALUE, "monitory"},		/*IORegisters[20] - monitory*/
	{ 21, 8, START_VALUE, "monitordata"}	/*IORegisters[21] - monitordata*/
};

