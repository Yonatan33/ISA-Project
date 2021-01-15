#ifndef GlobalUse
#define GlobalUse

/*Header defining the variables, constants, structs, and data structures that are in wide use throughout the entire program*/

/*********************************  General defenitions  *********************************/

#define LINE_LEN 7
#define NUM_OF_REGISTERS 16
#define NUM_OF_IOREGISTERS 22
#define NUM_OF_OPCODES 22
#define MAX_IMEM_SIZE 1024
#define MAX_DMEM_SIZE 4096
#define MAX_LINE_SIZE 500
#define MAX_TIME 
#define START_VALUE 0
#define DISK_CYCLE_SIZE 1024
#define NUM_OF_DISK_SECTORS 128
#define DISK_SECTOR_SIZE 128
#define MONITOR_SIZE_X 352
#define MONITOR_SIZE_Y 288

/*********************************  IORegisters names as numbers  *********************************/

#define IRQ_0_ENABLE 0
#define IRQ_1_ENABLE 1
#define IRQ_2_ENABLE 2
#define IRQ_0_STATUS 3
#define IRQ_1_STATUS 4
#define IRQ_2_STATUS 5
#define IRQHANDLER 6
#define IRQRETURN 7
#define CLKS 8
#define LEDS 9
#define RESERVED 10
#define TIMERENABLE 11
#define TIMERCURRENT 12
#define TIMERMAX 13
#define DISKCMD 14
#define DISKSECTOR 15
#define DISKBUFFER 16
#define DISKSTATUS 17
#define MONITORCMD 18
#define MONITORX 19
#define MONITORY 20
#define MONITORDATA 21

/*********************************  Variables In Wide Use  *********************************/

int PC;										/*PC - Program Counter*/
int clockCycle, diskCycle;					/*Cycle counters fot the clock, the disk and the timer*/
int insideInterrupt;						/*Flag to indicate if we are handling an interruption*/
int jumpFlag;								/*Flag to indicate if the instruction executed performed a jump*/
int diskON;
int instructionsCount;



/*********************************  Structs  *********************************/

//instruction struct : 
typedef struct iMEMCommand {
	unsigned int opcode; // 8 bits
	unsigned int rd; // 4 bits
	unsigned int rs; // 4 bits
	unsigned int rt; // 4 bits
	int immediate; // 20 bits
	int isType2; // flag for instructions using immediate
	void(*instructionFunc)(unsigned int rd, unsigned int rs, unsigned int rt);	//Pointer to execution function
}Inst;

typedef struct RegisterStruct {
	int value;
	char name[6];
} Register;

typedef struct regIO {
	int myRegNum;
	int myNumOfBits;
	unsigned int myValue;
	char* myName;
}registerIO;



/*********************************  Data Structures  *********************************/


Register registersArray[NUM_OF_REGISTERS];				/*Array for user registers*/

registerIO IORegisters[NUM_OF_IOREGISTERS];				/*Array for IO registers*/

Inst instructionArray[MAX_IMEM_SIZE];					/*Array for holding all instructions read from imem file. instruction's PC is its array index.
														 Memory pre-allocated, no need for dynamic*/


int dmemArray[MAX_DMEM_SIZE];							/*Array for holding the data memory (stack)*/

int diskArray[NUM_OF_DISK_SECTORS][DISK_SECTOR_SIZE];	/*Array for holding the disk content*/

int* irq2values;										/*Array for holding interruption times recieved from irq2in.txt*/

int monitorArray[MONITOR_SIZE_X][MONITOR_SIZE_Y];		/*Array for holding pixel values*/













#endif

