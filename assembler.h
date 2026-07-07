#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>

#include "parser.h"
#include "symboltable.h"
#include "code.h"


void makeOutputName(const char* input, char* output);

void firstPass(FILE* in, SymbolTable* st);

void secondPass(FILE* in, FILE* out, SymbolTable* st);


#endif
