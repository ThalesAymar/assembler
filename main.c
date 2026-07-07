#include <stdio.h>
#include <stdlib.h>

#include "assembler.h"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Uso: assembler.exe arquivo.asm\n");
        return 1;
    }

    FILE* in = fopen(argv[1], "r");

    if (in == NULL) {
        printf("Erro ao abrir %s\n", argv[1]);
        exit(1);
    }

    char outName[256];

    makeOutputName(argv[1], outName);

    FILE* out = fopen(outName, "w");

    if (out == NULL) {

        printf("Erro ao criar %s\n", outName);

        fclose(in);

        exit(1);
    }

    SymbolTable st;

    st.count = 0;
    st.romAddress = 0;

    initTable(&st);
    

    firstPass(in, &st);
    
    
    rewind(in);
    st.romAddress = 16; // proxima adicao na tabela comeca com endereco 16


    secondPass(in, out, &st);

    fclose(in);
    fclose(out);

    printf("Assembly concluido: %s\n", outName);

    return 0;
}
