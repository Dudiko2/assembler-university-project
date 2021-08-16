#include "encoder.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../io/io.h"

static Node* encodeNumSave(int bytesPerArg, char** args, int* bytesUsed);
static Node* encodeStringSave(char* ascizStr, int* bytesUsed);
static Node* encodeOperationR(int opcode, int funct, int rs, int rt, int rd);
static Node* encodeOperationI(int opcode, int rs, int rt, int immed);

int* toBinArray(long int num, int bits, int useTwosComp) {
    int remainder;
    int i;
    int positive;
    int* bin;
    int bound = useTwosComp ? 1 : 0;

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
    } while (num && i >= bound);

    if (num) {
        /*msg : doesn't fit*/
        free(bin);
        return NULL;
    }

    if (!positive && useTwosComp) {
        twosComplement(bin);
    }

    return bin;
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

int encodeCmd(Command* cmd, Node** encodedList) {
    char* op = cmd->op;
    char** args = cmd->arguments;
    int bytesUsed = 0;
    int rs;
    int rt;
    int rd;
    int immed;
    Node* encoded = NULL;
    CodeOperation* codeOp;

    if (strMatch(op, ".db")) {
        encoded = encodeNumSave(1, args, &bytesUsed);
    } else if (strMatch(op, ".dh")) {
        encoded = encodeNumSave(2, args, &bytesUsed);
    } else if (strMatch(op, ".dw")) {
        encoded = encodeNumSave(4, args, &bytesUsed);
    } else if (strMatch(op, ".asciz")) {
        encoded = encodeStringSave(args[0], &bytesUsed);
    } else if (strMatch(op, "add") ||
               strMatch(op, "sub") ||
               strMatch(op, "and") ||
               strMatch(op, "or") ||
               strMatch(op, "nor")) {
        codeOp = getCodeOperation(op);
        rs = strToInt(args[0] + 1);
        rt = strToInt(args[1] + 1);
        rd = strToInt(args[2] + 1);

        encoded = encodeOperationR(codeOp->opcode, codeOp->funct, rs, rt, rd);
        bytesUsed = 4;
    } else if (strMatch(op, "move") ||
               strMatch(op, "mvhi") ||
               strMatch(op, "mvlo")) {
        codeOp = getCodeOperation(op);
        rs = strToInt(args[0] + 1);
        rd = strToInt(args[1] + 1);

        encoded = encodeOperationR(codeOp->opcode, codeOp->funct, rs, 0, rd);
        bytesUsed = 4;
    } else if (strMatch(op, "addi") ||
               strMatch(op, "subi") ||
               strMatch(op, "andi") ||
               strMatch(op, "ori") ||
               strMatch(op, "nori")) {
        codeOp = getCodeOperation(op);
        rs = strToInt(args[0] + 1);
        rt = strToInt(args[2] + 1);
        immed = strToInt(args[1]);

        encoded = encodeOperationI(codeOp->opcode, rs, rt, immed);
        bytesUsed = 4;
    }

    if (encoded) {
        insertNodeLast(encodedList, encoded);
        return bytesUsed;
    }

    return 0;
}

static Node* encodeNumSave(int bytesPerArg, char** args, int* bytesUsed) {
    Node* head = NULL;
    int bits = bytesPerArg * 8;
    int i;
    long int num;
    int* bin = NULL;

    for (i = 0; args[i]; i++) {
        /*convert arg to int and store in num*/
        num = strToInt(args[i]);
        /*turn num to binary using toBinArray*/
        bin = toBinArray(num, bits, 1);
        /*insert bin into linked list*/
        if (!bin) {
            freeListShallow(head);
            return NULL;
        }

        insertLast(&head, bin);
    }

    *bytesUsed += (i * bytesPerArg);

    return head;
}

static Node* encodeStringSave(char* ascizStr, int* bytesUsed) {
    Node* head = NULL;
    int i;
    int* bin = NULL;
    int c;
    int byte = 8;

    for (i = 1; (c = ascizStr[i]) != '\"'; i++) {
        bin = toBinArray(c, byte, 0);

        if (!bin) {
            freeListShallow(head);
            return NULL;
        }

        insertLast(&head, bin);
    }

    /*insert \0 at end of string*/
    bin = toBinArray(0, byte, 0);
    if (!bin) {
        freeListShallow(head);
        return NULL;
    }

    insertLast(&head, bin);
    *bytesUsed += (i);

    return head;
}

static Node* encodeOperationR(int opcode, int funct, int rs, int rt, int rd) {
    int* binOpcode = NULL;
    int* binFunct = NULL;
    int* binRs = NULL;
    int* binRt = NULL;
    int* binRd = NULL;
    int* bin = NULL;
    int opcodeLen = 6;
    int functLen = 5;
    int rsLen = 5;
    int rtLen = 5;
    int rdLen = 5;
    int i;
    int j;

    binOpcode = toBinArray(opcode, opcodeLen, 0);
    binFunct = toBinArray(funct, functLen, 0);
    binRs = toBinArray(rs, rsLen, 0);
    binRt = toBinArray(rt, rtLen, 0);
    binRd = toBinArray(rd, rdLen, 0);

    bin = toBinArray(0, MAX_BITS, 0);
    if (!binOpcode || !binFunct || !binRs || !binRt || !binRd || !bin) {
        free(binOpcode);
        free(binFunct);
        free(binRs);
        free(binRt);
        free(binRd);
        free(bin);

        return NULL;
    }

    for (i = 0; binOpcode[i] != -1; i++) {
        bin[i] = binOpcode[i];
    }

    for (j = 0; binRs[j] != -1; i++, j++) {
        bin[i] = binRs[j];
    }

    for (j = 0; binRt[j] != -1; i++, j++) {
        bin[i] = binRt[j];
    }

    for (j = 0; binRd[j] != -1; i++, j++) {
        bin[i] = binRd[j];
    }

    for (j = 0; binFunct[j] != -1; i++, j++) {
        bin[i] = binFunct[j];
    }

    free(binOpcode);
    free(binFunct);
    free(binRs);
    free(binRt);
    free(binRd);

    return nodify(bin);
}

static Node* encodeOperationI(int opcode, int rs, int rt, int immed) {
    int* binOpcode = NULL;
    int* binRs = NULL;
    int* binRt = NULL;
    int* binImmed = NULL;
    int* bin = NULL;
    int opcodeLen = 6;
    int rsLen = 5;
    int rtLen = 5;
    int immedLen = 16;
    int i;
    int j;

    binOpcode = toBinArray(opcode, opcodeLen, 0);
    binRs = toBinArray(rs, rsLen, 0);
    binRt = toBinArray(rt, rtLen, 0);
    binImmed = toBinArray(immed, immedLen, 1);

    bin = toBinArray(0, MAX_BITS, 0);
    if (!binOpcode || !binRs || !binRt || !binImmed || !bin) {
        free(binOpcode);
        free(binRs);
        free(binRt);
        free(binImmed);
        free(bin);

        return NULL;
    }

    for (i = 0; binOpcode[i] != -1; i++) {
        bin[i] = binOpcode[i];
    }

    for (j = 0; binRs[j] != -1; i++, j++) {
        bin[i] = binRs[j];
    }

    for (j = 0; binRt[j] != -1; i++, j++) {
        bin[i] = binRt[j];
    }

    for (j = 0; binImmed[j] != -1; i++, j++) {
        bin[i] = binImmed[j];
    }

    free(binOpcode);
    free(binRs);
    free(binRt);
    free(binImmed);

    return nodify(bin);
}