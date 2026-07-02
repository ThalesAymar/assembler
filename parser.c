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

