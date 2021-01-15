#include "monitorHandler.h"

/*Implementation of updating the monitor's data*/

void updatePixel() {
	int x, y, data;
	x = IORegisters[MONITORX].myValue;
	y = IORegisters[MONITORY].myValue;
	data = IORegisters[MONITORDATA].myValue;
	monitorArray[x][y] = data;
}