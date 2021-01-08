#define _CRT_SECURE_NO_WARNINGS

#include "general.h"
#include "registers.h"


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





