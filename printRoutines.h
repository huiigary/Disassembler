/* This file contains the prototypes and constants needed to use the
   routines defined in printRoutines.c
*/

#ifndef _PRINTROUTINES_H_
#define _PRINTROUTINES_H_

#include <stdio.h>

int printPosition(FILE *, unsigned long);
int printInstruction(FILE *);
int printByte(FILE *, unsigned int code);
int printTwoBytes(FILE *, int code, int fn, int reg1, int reg2);
int printNineBytes(FILE *, int code, int fn, unsigned long long val);
int printTenBytes(FILE *, int code, int reg1, int reg2, unsigned long long val);
int printPos(FILE *, unsigned int address);
int printQuadValue(FILE *, unsigned long long value);
int printByteValue(FILE *, unsigned char value);
int printPosSpace(FILE *, unsigned int address);
#endif /* PRINTROUTINES */
