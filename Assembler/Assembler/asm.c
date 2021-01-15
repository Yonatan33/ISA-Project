#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************  constants  *****************************/

#define MEM_SIZE_BITS (16)
#define MEM_SIZE 1024
#define REGISTERS_NUM 16
#define MAX_LINE 500
#define MAX_MEM 4096
#define MAX_LABEL_SIZE 50
#define NUM_OF_OPCODES 22

/*****************************  variables and data structures  *****************************/
//unsigned int mem[MEM_SIZE];
static int PC = 0, labelsCount = 0, numOfCommands = 0;
static char* registers[16] = { "$zero", "$imm", "$v0", "$a0", "$a1", "$t0", "$t1", "$t2", "$t3", "$s0", "$s1", "$s2", "$gp", "$sp", "$fp", "$ra" };
static char* opcodes[22] = { "add", "sub", "and",  "or",  "xor",  "mul",  "sll",  "sra",  "srl",  "beq",  "bne",  "blt",  "bgt",  "ble",  "bge",
							"jal",  "lw",  "sw",  "reti",  "in",  "out",  "halt" };
static char labelsDS[MEM_SIZE][2][MAX_LABEL_SIZE + 1];
static int dmem[MAX_MEM] = { 0 };
static int imem[MEM_SIZE];


/*****************************  Functions supporting both walkthroughs on the assembly program  *****************************/

/*return 1 if line has no label/command in it
* return 0 otherwise
*/
int checkLineForLackOfContent(char* line) {
	char * firstWord, copyLine[MAX_LINE];
	char* delimiter = ", \n\t";
	strcpy(copyLine, line);
	firstWord = strtok(copyLine, delimiter);
	if (firstWord == NULL) {
		return 1;
	}
	else if (firstWord[0] == '#') {
		return 1;
	}
	return 0;
}
/*Reading next line in the input file, ignoring comments and empty lines
* return pointer to line, or NULL if EOF
*/
char* readNextLine(char* line, int max_size, FILE* inputFile) {
	char* flag = NULL;
	if (!(flag = fgets(line, MAX_LINE, inputFile))) {
		return NULL;
	}
	while (checkLineForLackOfContent(line) && flag != NULL) {
		flag = fgets(line, MAX_LINE, inputFile);
	}
	if (flag == NULL) {
		return NULL;
	}
	return line;
}

/*True if line argument ends with ':'
 *False otherwise
 */
int isLabel(char* line) {
	char * firstWord, copyLine[MAX_LINE];
	char* delimiter = " \ \,";
	strcpy(copyLine, line);
	firstWord = strtok(copyLine, delimiter);
	if (strstr(firstWord, ":")) {
		return 1;
	}
	return 0;
}

/*Check if given line has the ".word" pseudo command*/
int isWord(char* line) {
	char * firstWord, copyLine[MAX_LINE];
	char* delimiter = " ";
	strcpy(copyLine, line);
	firstWord = strtok(copyLine, delimiter);
	if (strstr(firstWord, ".word")) {
		return 1;
	}
	return 0;
}

/*This function assumes line HAS LABEL in it*/
char* getLabelName(char* line) {
	char * firstWord, copyLine[MAX_LINE];
	char* delimiter = ":";
	strcpy(copyLine, line);
	firstWord = strtok(copyLine, delimiter);
	return firstWord;
}

/*True if label is in it's own line
* False otherwise.
*/
int isLabelSeparate(char* line) {
	int count = 0;
	char * tempWord, copyLine[MAX_LINE];
	char * delimiter = " ";
	strcpy(copyLine, line);
	tempWord = strtok(line, delimiter);
	count++;
	while (tempWord != NULL) {
		if (tempWord[0] == '#') {
			break;
		}
		count++;
		tempWord = strtok(NULL, delimiter);
	}
	if (count > 2) {
		return 0;
	}
	return 1;
}

/*Assuming line argument will be  a valid command*/
void setPC(char* line) {
	char * delimiter = " ";
	char* tempWord = strtok(line, delimiter);
	int flag = 0;
	while (tempWord != NULL) {
		if (strstr(tempWord, registers[1])) {
			flag = 1;
			break;
		}
		if (!strcmp(tempWord, ".word")) {
			return;
		}
		if (tempWord[0] == '#') {
			break;
		}
		tempWord = strtok(NULL, delimiter);
	}
	if (flag) {
		PC += 2;
	}
	else {
		PC++;
	}
	printf("PC number: %d is set for line: %s\n", PC, line);
}

/*Insert given label to data structure of labels.
* ***IMPOTANT*** - Assumes current PC is the label's PC.
*/
void addLableToDS(char* labelName) {
	char PCasName[MAX_LABEL_SIZE];
	strcpy(labelsDS[labelsCount][0], labelName);
	sprintf(PCasName, "%d", PC);
	strcpy(labelsDS[labelsCount][1], PCasName);
}


void dealWithComma(char* name) {
	name[strlen(name) - 1] = '\0';
}

/*****************************  Implementation of first assembly program walkthrough  *****************************/

/*
 * Go over all of the assembly code for the first time, checking for labels and putting them in the label data structure.
 * */
void prepareLabels(FILE* inputFile) {
	int i;
	char* labelName;
	char line[MAX_LINE];
	for (i = 0; i < MEM_SIZE; i++) {					/*Go over MEM_SIZE lines at most*/
		if (readNextLine(line, MAX_LINE, inputFile) == NULL) {
			break;
		}
		else if (isWord(line)) {
			continue;
		}
		else if (isLabel(line)) {
			labelName = getLabelName(line);
			addLableToDS(labelName);
			labelsCount++;
			if (isLabelSeparate == 0) {     /*Label and command in the same line*/
				setPC(line);
			}
			else {       /*Label is in its own line*/
				readNextLine(line, MAX_LINE, inputFile);
				setPC(line);
			}
		}
		else {
			setPC(line);
		}
	}
}


/*check if the line is of a valid command*/

int isCommand(char* line) {
	char label[MAX_LABEL_SIZE], code[8], first[8], second[8], third[8], imm[MAX_LABEL_SIZE], comment[MAX_LINE];
	if (isLabel(line)) {
		if (isLabelSeparate(line)) {
			return 0;
		}
		if (sscanf(line, "%s %s %s %s %s %s %s", label, code, first, second, third, imm, comment)) { /*Label and command in the same line*/
			if (!(code == NULL || first == NULL || second == NULL || third == NULL || imm == NULL)) {
				dealWithComma(first);
				dealWithComma(second);
				dealWithComma(third);
				return 1;
			}
			return 0;
		}
		else {
			return 0;
		}
	}
	else {
		if (sscanf(line, "%s %s %s %s %s %s", code, first, second, third, imm, comment)) { /*Line without label at start*/
			if (!(code == NULL || first == NULL || second == NULL || third == NULL || imm == NULL)) {
				dealWithComma(first);
				dealWithComma(second);
				dealWithComma(third);
				return 1;
			}
			return 0;
		}
		return 0;

	}
}


/*Update the dmem array of words*/
void writeDMem(char* line) {
	int scanCheck;
	char *address, *data, addressHolder[MAX_LABEL_SIZE], dataHolder[MAX_LABEL_SIZE];
	int addressNum, dataNum;
	char command[MAX_LINE];
	/*translate hex strings if needed*/

	scanCheck = sscanf(line, "%s %s %s", command, addressHolder, dataHolder);
	if (scanCheck != -1) {
		if (strstr(addressHolder, "0x") || strstr(addressHolder, "0X")) {
			address = &(addressHolder[2]);
			addressNum = strtoul(address, NULL, 16);
		}
		else {
			addressNum = atoi(addressHolder);
		}
		if (strstr(dataHolder, "0x") || strstr(dataHolder, "0X")) {
			data = &(dataHolder[2]);
			dataNum = strtoul(data, NULL, 16);;
		}
		else {
			dataNum = atoi(dataHolder);
		}
		dmem[addressNum] = dataNum;
	}
}

/*return 1 if the line argument contains "$imm" as one of the 3 registers, and 0 otherwise*/
int isCommandImm(char* line) {
	char label[MAX_LABEL_SIZE], code[8], first[8], second[8], third[8], imm[MAX_LABEL_SIZE], comment[MAX_LINE];
	if (isLabel(line)) {
		if (isLabelSeparate(line)) {
			return 0;
		}
		if (sscanf(line, "%s %s %s %s %s %s %s", label, code, first, second, third, imm, comment)) {
			dealWithComma(first);
			dealWithComma(second);
			dealWithComma(third);
			if (!strcmp(first, registers[1]) || !strcmp(second, registers[1]) || !strcmp(third, registers[1])) {
				return 1;
			}
			return 0;
		}
	}
	else {
		if (sscanf(line, "%s %s %s %s %s %s", code, first, second, third, imm, comment)) {
			dealWithComma(first);
			dealWithComma(second);
			dealWithComma(third);
			if (!strcmp(first, registers[1]) || !strcmp(second, registers[1]) || !strcmp(third, registers[1])) {
				return 1;
			}
			return 0;
		}
	}
	return 0;
}

/*Given a string of the name of the register, return it's number*/
int getRegisterNumber(char* r) {
	int i;
	for (i = 0; i < REGISTERS_NUM; i++) {
		if (!strcmp(r, registers[i])) {
			return i;
		}
	}
	return 17; //should NOT get here
}



/*Given a string of immediate, check if its a known label
  If it's a label, return it's corresponding PC,
  Otherwise, return the string as a number.
*/
int interpreteimmediate(char* imm) {
	int i;
	char * hexImm;
	
	for (i = 0; i < MEM_SIZE; i++) {
		if (labelsDS[i] == NULL) { /*end of labelsDS, no matching label was found*/
			break;
		}
		else if (!strcmp(imm, labelsDS[i][0])) {
			return atoi(labelsDS[i][1]);
		}
	}
	
	if (strstr(imm, "0x") || strstr(imm, "0X")) {
		hexImm = &(imm[2]);
		return strtoul(hexImm, NULL, 16);
	}
	
	
	return atoi(imm);	/*immediate is not a label, nor a hex-ased number therfore must be a decimal number*/
}

/*Extract opcode from text command*/
int getOpcodeNumber(char* command) {
	int i;
	for (i = 0; i < NUM_OF_OPCODES; i++) {
		if (strstr(command, opcodes[i])) {
			if (i == 3) {	/*we check if the command contains the opcode's name, need to handle special case of "or" contained in "xor"*/
				if (strstr(command, "xor")) {
					return i+1;
				}
			}
			return i;
		}
	}
	printf("shouldn't get here");
	return -1;
}

/*According to label status, extract the command integer from the line
  put the immediate value under the immediate pointer given
*/
int parseCommand(char* line, char labelStatus, int* immediate) {
	int command;
	int opcode, rd, rs, rt, immNum;
	char label[MAX_LABEL_SIZE], code[8], first[8], second[8], third[8], imm[MAX_LABEL_SIZE], comment[MAX_LINE];

	if (labelStatus == 'L') {
		if (sscanf(line, "%s %s %s %s %s %s %s", label, code, first, second, third, imm, comment)) {
			opcode = getOpcodeNumber(code);
			dealWithComma(first);
			dealWithComma(second);
			dealWithComma(third);
			rd = getRegisterNumber(first);
			rs = getRegisterNumber(second);
			rt = getRegisterNumber(third);
			immNum = interpreteimmediate(imm);
			command = ((opcode & 0xff) << 12) | ((rd & 15) << 8) | ((rs & 15) << 4) | (rt & 15);
			*immediate = immNum;
			return command;
		}
		else {
			return 0;
		}
	}
	if (labelStatus == 'N') {
		if (sscanf(line, " %s %s %s %s %s %s", code, first, second, third, imm, comment)) {

			opcode = getOpcodeNumber(code);
			dealWithComma(first);
			dealWithComma(second);
			dealWithComma(third);
			rd = getRegisterNumber(first);
			rs = getRegisterNumber(second);
			rt = getRegisterNumber(third);
			immNum = interpreteimmediate(imm);
			command = ((opcode & 0xff) << 12) | ((rd & 15) << 8) | ((rs & 15) << 4) | (rt & 15);
			*immediate = immNum;
			return command;
		}
		else {
			return 0;
		}
	}
	return 0; //should NEVER get here.
}

/*Update the imem array with the given command
  If the immediateFlag is 'N', updates one spot in imem.
  If the immediateFlag is 'Y', update also another spot for the immediate.
*/
void writeIMem(int command, int commanImm, char immediateFlag) {
	imem[PC] = command;
	if (immediateFlag == 'N') {
		return;
	}
	if (immediateFlag == 'Y') {
		imem[PC + 1] = commanImm;
		return;
	}
	return;
}

/*According to given line and labelStatus ('L' if exists, 'N' otherwise),
  trigger the functions needed for updating imem and dmem arrays.
  */
void analyzeCommand(char* line, char labelStatus) {
	int command = 0x0, commandImm = 0x0;
	if (isWord(line)) {
		writeDMem(line);
	}
	else {
		if (labelStatus == 'L') {
			command = parseCommand(line, 'L', &commandImm);
		}
		if (labelStatus == 'N') {
			command = parseCommand(line, 'N', &commandImm);
		}
		if (isCommandImm(line)) {
			writeIMem(command, commandImm, 'Y');
			setPC(line);
		}
		else {
			writeIMem(command, 0, 'N');
			setPC(line);
		}
	}
}

/*Go over dmem array and write to dmemin.txt file*/
void writeDMemFile(FILE* dmemOutput) {
	int i;
	for (i = 0; i < MAX_MEM; i++) {
		if (dmem[i] != 0) {
			fprintf(dmemOutput, "%08X\n", dmem[i]);
		}
		else {
			fprintf(dmemOutput, "%08X\n", 0);
		}
	}
}

/*Go over imem array and write to imemin.txt file*/
void writeIMemFile(FILE* imemOutput) {
	int i;
	for (i = 0; i < numOfCommands; i++) {
		fprintf(imemOutput, "%05X\n", imem[i] & 0xfffff);
	}
}

/*****************************  Implementation of second assembly program walkthrough  *****************************/

/*Go over the input file again, write to output files:
  Write all commands to imemin.txt file.
  Write all .word pseudo commands to dmemin.txt. file.

  Arguments imemOutput and dmemOutput are to be said imemin.txt. and dmemin.txt respectively.
*/
void writeMemOutput(FILE* inputFile, FILE* imemOutput, FILE* dmemOutput) {
	int i;
	int command = 0x0, commandImm = 0x0;
	char line[MAX_LINE];
	for (i = 0; i < MAX_LINE; i++) {
		if (!readNextLine(line, MAX_LINE, inputFile)) {
			break;
		}
		if (isLabel(line)) {
			if (isLabelSeparate) {
				continue;
			}
			analyzeCommand(line, 'L');
		}
		
		else {
			analyzeCommand(line, 'N');
		}
	}
	writeIMemFile(imemOutput);
	writeDMemFile(dmemOutput);
}


int main(int argc, char **argv) {

	FILE * input, *imemOutput, *dmemOutput;
	printf("Started\n");
	input = fopen(argv[1], "r");
	imemOutput = fopen(argv[2], "w");
	dmemOutput = fopen(argv[3], "w");
	prepareLabels(input);
	numOfCommands = PC;
	PC = 0;
	labelsDS;
	rewind(input);
	writeMemOutput(input, imemOutput, dmemOutput);
	fclose(input);
	fclose(imemOutput);
	fclose(dmemOutput);
	printf("Hello, World!\n");
	return 0;
}
