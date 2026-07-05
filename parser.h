#ifndef PARSER_H
#define PARSER_H


typedef struct{
	int numLine;
	char currentLine[256];
	char* currentToken;
} Parser;

typedef enum{
    A_COMMAND, //comeca com @
    C_COMMAND, //dest = comp; jump
    L_COMMAND // resto
} CommandType;

typedef struct{
	char* name;
	CommandType type;
} Command;

typedef struct{
    char *dest;
    char *comp;
    char *jump;
} CInstruction;


CInstruction parseCInstruction(char *instruction);


CommandType getCommandType(char* token);


#endif


