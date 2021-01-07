#define _CRT_SECURE_NO_WARNINGS

#include "general.h"
#include "registers.h"


Register registersArray[NUMBER_OF_REGISTERS] = {
	{0, 0, "$zero"},
	{0, 1, "$imm"},
	{0, 2, "$v0"},
	{0, 3, "$a0"},
	{0, 4, "$a1"},
	{0, 5, "$t0"},
	{0, 6, "$t1"},
	{0, 7, "$t2"},
	{0, 8, "$t3"},
	{0, 9, "$s0"},
	{0, 10, "$s1"},
	{0, 11, "$s2"},
	{0, 12, "$gp"},
	{0, 13, "$fp"},
	{0, 14, "$rp"},
	{0, 15, "$ra"}
};



