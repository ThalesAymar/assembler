#ifndef CODE_H
#define CODE_H




typedef struct{
    char* mnemonic;
    char* binary;
} Code;


char* getDestCode(char *mnemonic);

char* getCompCode(char *mnemonic);

char* getJumpCode(char *mnemonic);

void writeAInstruction(FILE* out, int value);

int isNumber(char* s);

#endif
