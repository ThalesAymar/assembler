#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "symboltable.h"




int main(int argc, char *argv[]) {
	FILE *arq = fopen("teste.txt", "r");
	
	FILE *out = fopen("teste.hack", "w");
	
	if (!arq || !out) {
        printf("Erro ao abrir arquivos.\n");
        return 1;
    }

	
	Parser p;
	
	SymbolTable st;
	st.count = 0;
	st.romAddress = 0;
	
	initTable(&st);
	

    
	while(fgets(p.currentLine, sizeof(p.currentLine), arq) != NULL){
		
		char* comment = strstr(p.currentLine, "//");

		if(comment != NULL){
    		*comment = '\0';
		}
		
		
		p.currentToken = strtok(p.currentLine, " \t\n");
		
		if(p.currentToken == NULL){
    		continue;
		}
		
		
		CommandType type = getCommandType(p.currentToken);
		
		
		switch (type) {
            case L_COMMAND:

				strcpy(label, p.currentToken + 1);   // pula o '('

				label[strlen(label) - 1] = '\0';     // remove ')'
				
                addEntry(&st, p.currentToken, st.romAddress);
                break;
            default:
            	st.romAddress++; 
                break;
		}
	}
	

	/**************************************************
	*												  *
	*												  *
	*				  SEGUNDA PASSADA				  *
	*												  *
	*												  *
	**************************************************/
	
	
	
	rewind(arq);
	st.romAddress = 16; //novas adicoes na tabela comecarao do endereco 16
	
	while(fgets(p.currentLine, sizeof(p.currentLine), arq) != NULL){
		
		char* comment = strstr(p.currentLine, "//");

		if(comment != NULL){
    		*comment = '\0';
		}
		
		
		p.currentToken = strtok(p.currentLine, " \t\n");
		
		if(p.currentToken == NULL){
    		continue;
		}
		
		
		CommandType type = getCommandType(p.currentToken);
		
		CInstruction c;
		int len = strlen(p.currentToken);
		int address;
		char a_command[len];
		 
		
		switch (type) {
            case A_COMMAND:
				
				strncpy(a_command, p.currentToken + 1, len ); // pula o @
                a_command[len-1] = '\0'; // garante terminação da string


				if(isNumber(a_command)){
                	address = atoi(a_command);
				}
				else{
					
					if (!contains(&st, a_command)){
        				addEntry(&st, a_command, st.romAddress++);
    				}
    				
					address = getAddress(&st, a_command);
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

	fclose(arq);
    fclose(out);
		
	return 0;
}




