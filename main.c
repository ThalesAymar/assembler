#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "symboltable.h"




int main(int argc, char *argv[]) {
	FILE *arq = fopen("teste.txt", "r");
	
	if(arq == NULL){
        printf("Erro ao abrir arquivo\n");
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
            case A_COMMAND:
                printf("%s e A_COMMAND\n", p.currentToken );  // 2 PASSADA PEGAR TUDO MENOS @
                st.romAddress++;
                break;
            case C_COMMAND:
                printf("%s e C_COMMAND\n", p.currentToken ); // 2 PASSADA PEGAR dest = comp;jump
                st.romAddress++;
                break;
            case L_COMMAND:
                printf("%s e L_COMMAND\n", p.currentToken ); // 1 PASSADA PEGAR TUDO MENOS ()
                addEntry(&st, p.currentToken, st.romAddress);
                break;
            default:
            	printf("Nao achou" ); 
                break;
		}
	}
	
	
	for(int i = 0; i < st.count; i++){
		printf("Symbol: %s , Address: %d , Na posicao: %d \n", st.table[i].symbol, st.table[i].address, i);
	}
		
	return 0;
}




