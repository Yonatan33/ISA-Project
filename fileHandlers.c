#define _CRT_SECURE_NO_WARNINGS

#include "fileHandlers.h"


// open a file and check that its not null
// if it's NULL print an error and exit the simulator otherwise return the file's address
// input: file name, mode = "r" or "w"
// output: file address
FILE* get_file_pointer(const char* file_name, char* mode) {
	FILE* tmp_ptr = NULL;
	tmp_ptr = fopen(file_name, mode);
	if (tmp_ptr == NULL) {
		printf("Error opening file %d, named: %s", f_num, file_name); // print error to indicate which file has the problem
		exit(1);
	}
	f_num++;
	return tmp_ptr;

}

// initialize all file ptrs:
void initFilePointers(char* argv[]) {
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

void readDMemIn(){
	char dmemLine[DMEM_LINE_SIZE + 2];	/*  add 1 for '\n' and 1 for '\0'  */
	int index = 0;
	while (fgets(dmemLine, DMEM_LINE_SIZE + 2, fdmemin) != NULL) {
		dmemArray[index] = (int)strtoul(dmemLine, NULL, 16);
		index++;
	}
}

/*Go over irq2in.txt file twice -
  Once to take it's size and dynamically allocate the memory
  Twice to insert it's values to irq2values
  Insert data to irq2values array
*/
void readIrq2In() {
	char irq2Line[MAX_LINE_SIZE];
	int linesInFile = 0;
	while (fgets(irq2Line, MAX_LINE_SIZE, firq2in) != NULL) {
		linesInFile++;
	}
	irq2values = (int*) calloc(linesInFile, sizeof(int));
	rewind(firq2in);
	linesInFile = 0;
	while (fgets(irq2Line, MAX_LINE_SIZE, firq2in) != NULL) {
		irq2values[linesInFile] = (unsigned int)strtol(irq2Line, NULL, 10);
		linesInFile++;
	}
}

/*Read the data from the diskin.txt file and put it in diskArray*/
void readDiskIn() {
	char diskLine[MAX_LINE_SIZE];
	int currentLine = 0;
	int sector, offset;
	while (fgets(diskLine, MAX_LINE_SIZE, fdiskin) != NULL) {
		sector = currentLine / NUM_OF_DISK_SECTORS;
		offset = currentLine % DISK_SECTOR_SIZE;
		diskArray[sector][offset] = (int)strtoul(diskLine, NULL, 16);
		currentLine++;
	}
}

unsigned int buildInstructionCode(unsigned int opcode) {
	unsigned int code, rd, rs, rt;
	rd = instructionArray[PC].rd;
	rs = instructionArray[PC].rs;
	rt = instructionArray[PC].rt;
	code = (opcode << 12) | (rd << 8) | (rs << 4) | rt;
	return code;
}

/*write one line of trace to trace file according to assignment instructions*/
void writeTraceOutput(unsigned int opcode) {
	int i;
	
	fprintf(ftrace, "%03X %05X", PC, buildInstructionCode(opcode));
	for (i = 0; i < NUM_OF_REGISTERS; i++) {
		if (i != 1) {
			fprintf(ftrace, " %08X", registersArray[i].value);
		}
		else {
			if ((instructionArray[PC].immediate >> 19)) {	/*check if $imm content is negative, and make sign extension accordingly*/
				fprintf(ftrace, " %08X", (instructionArray[PC].immediate & 0xFFFFFFFF));
			}
			else {
				fprintf(ftrace, " %08X", instructionArray[PC].immediate);
			}
		}
	}
	fprintf(ftrace, "\n");
}

void writeHWRegTraceOut(Inst* currentInstruction) {
	int isImm = 0, cycle, data, rd, rs, rt, ioregsIndex;
	char* name, * mode;
	rd = currentInstruction->rd;
	rs = currentInstruction->rs;
	rt = currentInstruction->rt;

	if (currentInstruction->opcode == 19) {
		mode = "READ";
	}
	else if (currentInstruction->opcode == 20) {
		mode = "WRITE";
	}
	else {
		return;
	}

	isImm = currentInstruction->isType2;
	if (isImm) {
		cycle = clockCycle - 1;
	}
	else {
		cycle = clockCycle;
	}
	ioregsIndex = registersArray[rs].value + registersArray[rt].value;
	name = IORegisters[ioregsIndex].myName;
	data = IORegisters[ioregsIndex].myValue;
	if (ioregsIndex == MONITORCMD) {
		data = 0;
	}
	
	fprintf(fhwregtrace, "%d %s %s %08X\n", cycle, mode, name, data);

}

void writeDMemOut() {
	int i;
	for (i = 0; i < MAX_DMEM_SIZE; i++) {
		fprintf(fdmemout, "%08X\n", dmemArray[i]);
	}
}

void writeRegOut() {
	int i;
	for (i = 2; i < NUM_OF_REGISTERS; i++) {
		fprintf(fregout, "%08X\n", registersArray[i].value);
	}
}

void writeMonitorOut() {
	int x, y;
	for (y = 0; y < MONITOR_SIZE_Y; y++) {
		for(x = 0; x < MONITOR_SIZE_X; x++) {
			fprintf(fmonitor, "%02X\n", monitorArray[x][y]);
		}
	}
}

void writeMonitorYUVOut() {
	int x, y;
	for (y = 0; y < MONITOR_SIZE_Y; y++) {
		for (x = 0; x < MONITOR_SIZE_X; x++) {
			fwrite((unsigned char*)&monitorArray[x][y], sizeof(char), 1, fmonitor2);
		}
	}
}

void writeDiskOut() {
	int sector, sectorOffset;
	for (sector = 0; sector < NUM_OF_DISK_SECTORS; sector++) {
		for (sectorOffset = 0; sectorOffset < DISK_SECTOR_SIZE; sectorOffset++) {
			fprintf(fdiskout, "%08X\n", diskArray[sector][sectorOffset]);
		}
	}
}

void writeCycles() {
	fprintf(fcycles, "%d\n", clockCycle);
	fprintf(fcycles, "%d\n", instructionsCount);
}

void closeFiles() {
	fclose(fimemin);
	fclose(fdmemin);
	fclose(fdiskin);
	fclose(firq2in);
	fclose(fdmemout);
	fclose(fregout);
	fclose(ftrace);
	fclose(fhwregtrace);
	fclose(fcycles);
	fclose(fleds);
	fclose(fmonitor);
	fclose(fmonitor);
	fclose(fdiskout);
}