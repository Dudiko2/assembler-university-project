#include "encoder.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Node* encodeNumSave(int bytesPerArg, char** args);

int* toBinArray(long int num, int bits) {
    int remainder;
    int i;
    int positive;
    int* bin;

    bin = newBinArr(bits);
    i = bits - 1;

    if (!bin)
        return NULL;

    positive = num >= 0;
    num = positive ? num : num * -1;

    do {
        remainder = num % 2;
        num /= 2;
        bin[i] = remainder;
        i--;
    } while (num && i > 0);

    if (num) {
        /*msg : doesn't fit*/
        free(bin);
        return NULL;
    }

    if (!positive) {
        twosComplement(bin);
    }

    return bin;
}

long int strToInt(char* str) {
    return strtol(str, (char**)NULL, 10);
}

void twosComplement(int* binArr) {
    binFlip(binArr);
    binAddOne(binArr);
}

void binFlip(int* binArr) {
    int i;
    int digit;

    for (i = 0; (digit = binArr[i]) != -1; i++) {
        binArr[i] = !digit;
    }
}

void binAddOne(int* binArr) {
    int i = binLen(binArr) - 1;
    int add = 1;

    while (i >= 0 && add) {
        binArr[i] += add;
        add = 0;

        if (binArr[i] > 1) {
            binArr[i] = 0;
            add = 1;
        }
        i--;
    }
}

int binLen(int* binArr) {
    int i;

    for (i = 0; binArr[i] != -1; i++)
        ;

    return i;
}

int* newBinArr(int bits) {
    int* bin;

    if (bits < 1 || bits > MAX_BITS)
        return NULL;

    bin = calloc(bits + 1, sizeof(int));
    bin[bits] = -1;

    return bin;
}

char* binToStr(int* binArr) {
    int i;
    int len;
    char* str;

    len = binLen(binArr);

    str = calloc(len + 1, sizeof(char));

    for (i = 0; binArr[i] != -1; i++) {
        str[i] = binArr[i] + '0';
    }

    return str;
}

char fourbitsToHex(int* binArr, int index) {
    int factor = 1;
    int res = 0;
    int bits;

    for (bits = 0; (index - bits) >= 0 && bits < 4; bits++) {
        res += (binArr[index - bits] * factor);
        factor *= 2;
    }

    if (res > 9) {
        res -= 10;
        res += 'A';
    } else {
        res += '0';
    }

    return res;
}

char* binToHex(int* binArr) {
    int bits;
    int len;
    int i;
    char* hex;

    bits = binLen(binArr);
    len = bits / 4;

    hex = calloc(len + 1, sizeof(char));

    for (i = bits - 1; i > 0; i -= 4, len--) {
        hex[len - 1] = fourbitsToHex(binArr, i);
    }

    return hex;
}

int binNegative(int* binArr) {
    return binArr[0];
}

Node* encodeCmd(Command* cmd) {
    /*Should add addresses to it*/
    char* op = cmd->op;
    char** args = cmd->arguments;

    if (strMatch(op, ".db")) {
        return encodeNumSave(1, args);
    } else if (strMatch(op, ".dh")) {
        return encodeNumSave(2, args);
    } else if (strMatch(op, ".dw")) {
        return encodeNumSave(4, args);
    }

    return NULL;
}

static Node* encodeNumSave(int bytesPerArg, char** args) {
    /*Should add addresses to it*/
    Node* head = NULL;
    int bits = bytesPerArg * 8;
    int i;
    long int num;
    int* bin = NULL;

    for (i = 0; args[i]; i++) {
        /*convert arg to int and store in num*/
        num = strToInt(args[i]);
        /*turn num to binary using toBinArray*/
        bin = toBinArray(num, bits);
        /*insert bin into linked list*/
        if (!bin) {
            freeListShallow(head);
            return NULL;
        }

        insertLast(&head, bin);
    }

    return head;
}