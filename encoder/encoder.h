#ifndef ENCODER_H
#define ENCODER_H

#define MAX_BITS 32

/*
converts num to a it's corresponding binary sequence/array.
the sequence will be nDigits wide.
terminates the array with -1.
uses two's complement for negative numbers.

the given binary form of num must fit within the array.
1 <= nDigits <= 32.

returns NULL at error.
*/
int* toBinArray(long int num, int nDigits);
long int strToInt(char* str);
void twosComplement(int* binArr);
void binFlip(int* binArr);
void binAddOne(int* binArr);
int binLen(int* binArr);
int* newBinArr(int nDigits);

#endif