#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assembler.h"
#include "parser.h"
#include "symboltable.h"
#include "code.h"



void makeOutputName(const char* input, char* output) {

    strcpy(output, input);

    char* dot = strrchr(output, '.');

    if (dot != NULL) {
        strcpy(dot, ".hack");
    }
}





void firstPass(FILE* in, SymbolTable* st) {

    Parser p;
    char label[256];

    st->romAddress = 0;

    while (fgets(p.currentLine, sizeof(p.currentLine), in) != NULL) {

        char* comment = strstr(p.currentLine, "//");

        if (comment != NULL) {
            *comment = '\0';
        }

        p.currentToken = strtok(p.currentLine, " \t\n");

        if (p.currentToken == NULL) {
            continue;
        }

        CommandType type = getCommandType(p.currentToken);

        switch (type) {

            case L_COMMAND:

                strcpy(label, p.currentToken + 1); //remove o '('

                label[strlen(label) - 1] = '\0'; // remove o ')'

                addEntry(st, label, st->romAddress);

                break;

            default:

                st->romAddress++;

                break;
        }
    }
}





void secondPass(FILE* in, FILE* out, SymbolTable* st) {

    Parser p;


    while (fgets(p.currentLine, sizeof(p.currentLine), in) != NULL) {

        char* comment = strstr(p.currentLine, "//");

        if (comment != NULL) {
            *comment = '\0';
        }

        p.currentToken = strtok(p.currentLine, " \t\n");

        if (p.currentToken == NULL) {
            continue;
        }

        CommandType type = getCommandType(p.currentToken);
        
        
		CInstruction c;
		
        int len = strlen(p.currentToken);
        char a_command[256];
        int address;
       

        switch (type) {
			case A_COMMAND:

                strncpy(a_command, p.currentToken + 1, sizeof(a_command) - 1); //remove o '@'
                a_command[sizeof(a_command) - 1] = '\0'; // garante a terminacao da string

                if(isNumber(a_command)) {

                    address = atoi(a_command);
                }
                else{

                    if(!contains(st, a_command)) {

                        addEntry(st, a_command, st->romAddress++);
                    }

                    address = getAddress(st, a_command);
                }

                writeAInstruction(out, address);

                break;
                
            case C_COMMAND:

                c = parseCInstruction(p.currentToken);

                fprintf(out, "111%s%s%s\n", getCompCode(c.comp), getDestCode(c.dest), getJumpCode(c.jump));

                break;
                
            default:

                break;
        }
    }
}





