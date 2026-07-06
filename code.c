#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#include "code.h"

Code compTable[] = {

    {"0",   "0101010"},
    {"1",   "0111111"},
    {"-1",  "0111010"},

    {"D",   "0001100"},
    {"A",   "0110000"},
    {"!D",  "0001101"},
    {"!A",  "0110001"},
    {"-D",  "0001111"},
    {"-A",  "0110011"},
    {"D+1", "0011111"},
    {"A+1", "0110111"},
    {"D-1", "0001110"},
    {"A-1", "0110010"},
    {"D+A", "0000010"},
    {"D-A", "0010011"},
    {"A-D", "0000111"},
    {"D&A", "0000000"},
    {"D|A", "0010101"},

    {"M",   "1110000"},
    {"!M",  "1110001"},
    {"-M",  "1110011"},
    {"M+1", "1110111"},
    {"M-1", "1110010"},
    {"D+M", "1000010"},
    {"D-M", "1010011"},
    {"M-D", "1000111"},
    {"D&M", "1000000"},
    {"D|M", "1010101"}

};




Code destTable[] = {
	
	{"M",   "001"},
	{"D",   "010"},
	{"MD",  "011"},
	{"A",   "100"},
	{"AM",  "101"},
	{"AD",  "110"},
	{"AMD", "111"}
	
};



Code jumpTable[] = {

	{"JGT", "001"},
	{"JEQ", "010"},
	{"JGE", "011"},
	{"JLT", "100"},
	{"JNE", "101"},
	{"JLE", "110"},
	{"JMP", "111"}
};




char* getDestCode(char* mnemonic){
	
	
	if (mnemonic == NULL) {
        return "000";
    }
    
    
	for(size_t i = 0; i < sizeof(destTable)/sizeof(destTable[0]); i++){
		if(strcmp(mnemonic, destTable[i].mnemonic) == 0){
			return destTable[i].binary;
		}
	}
}




char* getCompCode(char* mnemonic){
	
	
	if (mnemonic == NULL) {
        printf("Erro: Comp inexistente");
        exit(-2);
    }
    
    
	for(size_t i = 0; i < sizeof(compTable)/sizeof(compTable[0]); i++){
		if(strcmp(mnemonic, compTable[i].mnemonic) == 0){
			return compTable[i].binary;
		}
	}
}



char* getJumpCode(char* mnemonic){
	
	
	if (mnemonic == NULL) {
        return "000";
    }
    
    
	for(size_t i = 0; i < sizeof(jumpTable)/sizeof(jumpTable[0]); i++){
		if(strcmp(mnemonic, jumpTable[i].mnemonic) == 0){
			return jumpTable[i].binary;
		}
	}
}




void writeAInstruction(FILE* out, int value) {

    fputc('0', out);   // bit mais significativo

    for (int i = 14; i >= 0; i--) {
        if (value & (1 << i)){
            fputc('1', out);
    	}
        else{
            fputc('0', out);
    	}
    }

    fputc('\n', out);
}



int isNumber(char* s) {
    while (*s) {
        if (*s < '0' || *s > '9')
            return 0;
        s++;
    }
    return 1;
}
