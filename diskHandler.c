#include "diskHandler.h"



void readDiskToMem(int sector, int memoryAddress) {
	int sectorOffset;
	for (sectorOffset = 0; sectorOffset < DISK_SECTOR_SIZE; sectorOffset++) {
		if (memoryAddress + sectorOffset < MAX_DMEM_SIZE) {				/*Stop at end of memory*/		
			dmemArray[memoryAddress + sectorOffset] = diskArray[sector][sectorOffset];
		}
	}
}

void writeMemToDisk(int sector, int memoryAddress) {
	int sectorOffset;
	for (sectorOffset = 0; sectorOffset < DISK_SECTOR_SIZE; sectorOffset++) {		
		if (memoryAddress + sectorOffset < MAX_DMEM_SIZE) {				/*Stop at end of memory*/
			diskArray[sector][sectorOffset] = dmemArray[memoryAddress + sectorOffset];
		}
	}
}


/* Read or Write disk data. If given memory address is too large (too close to memory size and sector won't fit -
 * operation will stop at the end of the memory.
*/
void diskRW() {
	int sector, memoryAddress, rwStatus, sectorOffset;
	sector = IORegisters[DISKSECTOR].myValue;
	memoryAddress = IORegisters[DISKBUFFER].myValue;
	rwStatus = IORegisters[DISKCMD].myValue;
	for (sectorOffset = 0; sectorOffset < DISK_SECTOR_SIZE; sectorOffset++) {
		if (rwStatus == 1) {				/*Read from disk to buffer*/
			readDiskToMem(sector, memoryAddress);
		}		
		else if (rwStatus == 2) {			/*Write to disk*/
			writeMemToDisk(sector, memoryAddress);
		}
	}

}