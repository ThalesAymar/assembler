#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"





CommandType getCommandType(char* token){
	if (token[0] == '@'){
		return A_COMMAND;
	}
	else if(token[0] == '('){
		return L_COMMAND;
	}
	else{
		return C_COMMAND;
	}
}


CInstruction parseCInstruction(char* instruction){
    char* dest = NULL;
    char* comp = NULL;
    char* jump = NULL;

    char* left = strtok(instruction, "=");
    char* right = strtok(NULL, "=");

    if(right != NULL){
        dest = left;
        comp = strtok(right, ";");
        jump = strtok(NULL, ";");
    }
    else{
        comp = strtok(left, ";");
        jump = strtok(NULL, ";");
    }
    
    CInstruction c = {dest, comp, jump};
    
    return c;
}
