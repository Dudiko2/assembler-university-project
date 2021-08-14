#ifndef ENCODER_H
#define ENCODER_H

#include "../commands/commands.h"
#include "../operations/operations.h"
#include "../utils/utils.h"

#define MAX_BITS 32

/*
converts num to a it's corresponding binary sequence/array.
the sequence will be BITS wide.
terminates the array with -1.
uses two's complement for negative numbers.
return value needs to be free()'d after use.

the given binary form of num must fit within the array.
1 <= bits <= 32.

returns NULL at error.
*/
int* toBinArray(long int num, int bits);

long int strToInt(char* str);

/*applies two's complement to a binary sequence*/
void twosComplement(int* binArr);

/*flips the digit (logical NOT) of a binary sequence*/
void binFlip(int* binArr);

/*adds one to a binary sequence*/
void binAddOne(int* binArr);

/*returns the number of bits of a binary number*/
int binLen(int* binArr);

/*
allocates a new binary sequence.
the sequence is terminated with -1.
needs to be free()'d after use.
*/
int* newBinArr(int bits);

/*
converts a binary sequence to string
needs to be free()'d after use.
*/
char* binToStr(int* binArr);

/*
converts four bits of a binary sequence, starting at index, to a hexadecimal char
*/
char fourbitsToHex(int* binArr, int index);

/*
converts a binary sequence to a hexadecimal string
needs to be free()'d after use.
*/
char* binToHex(int* binArr);

int binNegative(int* binArr);

Node* encodeCmd(Command* cmd);

#endif