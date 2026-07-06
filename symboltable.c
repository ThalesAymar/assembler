#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symboltable.h"


void addEntry(SymbolTable* st, char* symbol, int address){
	
	Symbol s = {strdup(symbol), address};
	
	st->table[st->count] = s;
	st->count++;
}






void initTable(SymbolTable* st){
	addEntry(st, "R0", 0);
	addEntry(st, "R1", 1);
	addEntry(st, "R2", 2);
	addEntry(st, "R3", 3);
	addEntry(st, "R4", 4);
	addEntry(st, "R5", 5);
	addEntry(st, "R6", 6);
	addEntry(st, "R7", 7);
	addEntry(st, "R8", 8);
	addEntry(st, "R9", 9);
	addEntry(st, "R10", 10);
	addEntry(st, "R11", 11);
	addEntry(st, "R12", 12);
	addEntry(st, "R13", 13);
	addEntry(st, "R14", 14);
	addEntry(st, "R15", 15);
	addEntry(st, "SCREEN",16384);
	addEntry(st, "KBD",24576);
	addEntry(st, "SP", 0);
	addEntry(st, "LCL", 1);
	addEntry(st, "ARG", 2);
	addEntry(st, "THIS", 3);
	addEntry(st, "THAT", 4);
}





int contains(SymbolTable* st, char* symbol){
	
	
	for(int i = 0; i < st->count; i++){
		 if (strcmp(symbol, st->table[i].symbol) == 0) {
            return 1;
        }
	}
	
	return 0;
}



int getAddress(SymbolTable* st, char* symbol){
	
	
	for(int i = 0; i < st->count; i++){
		 if (strcmp(symbol, st->table[i].symbol) == 0) {
            return st->table[i].address;
        }
	}
	
	printf("Endereço do comando nao encontrado\n");
	exit(-1);
}

