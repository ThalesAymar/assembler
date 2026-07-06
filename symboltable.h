#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H


typedef struct {
    char* symbol;
    int address;
} Symbol;


typedef struct {
    Symbol table[1000];
    int count;
    int romAddress;
} SymbolTable;



void addEntry(SymbolTable* st, char* symbol, int address);

void initTable(SymbolTable* st);

int contains(SymbolTable* st, char* symbol);

int getAddress(SymbolTable* st, char* symbol);


#endif

