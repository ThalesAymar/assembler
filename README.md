# Hack Assembler em C

Implementação de um **Assembler para a arquitetura Hack**, desenvolvida em linguagem C

O programa traduz arquivos escritos em Assembly Hack (`.asm`) para código de máquina Hack (`.hack`), realizando as duas passadas exigidas pela especificação da plataforma.

Desenvolvido por Thales Souza como parte da disciplina de Compiladores.
Link no Drive para vídeo comentando e validando o projeto: https://drive.google.com/drive/folders/1nuxJ8GGP60MBYMexdgQb3ew4F44T2_XT?usp=sharing


---

# Funcionalidades

* Tradução de instruções **A** (`@valor` ou `@símbolo`)
* Tradução de instruções **C** (`dest=comp;jump`)
* Suporte completo a **labels** (`(LOOP)`)
* Resolução automática de variáveis
* Tabela de símbolos pré-definida da arquitetura Hack
* Geração automática do arquivo `.hack` com o mesmo nome do arquivo de entrada

---

# Estrutura do projeto


## main.c

Ponto de entrada do programa.

Responsável por:

* validar os argumentos da linha de comando;
* chama a primeira e segunda passada.

---

## assembler.c

Coordena todo o processo de montagem.

Responsabilidades:

* criar o arquivo `.hack`;
* executar a primeira passada;
* executar a segunda passada;
* controlar a tabela de símbolos;
* converter cada instrução para binário.

---

## parser.c

Responsável pela análise sintática das instruções.

Implementa:

* identificação do tipo da instrução;
* separação dos campos `dest`, `comp` e `jump` das instruções C.

---

## symboltable.c

Implementa a tabela de símbolos do assembler.

Responsável por:

* armazenar labels;
* armazenar variáveis;
* inicializar os símbolos pré-definidos;
* buscar endereços associados aos símbolos.

---

## code.c

Responsável pela tradução dos mnemônicos para código binário.

Implementa:

* tabela `comp`;
* tabela `dest`;
* tabela `jump`;
* geração das instruções A;
* verificação de valores numéricos.

---

# Funcionamento

O assembler utiliza o algoritmo clássico de **duas passadas**.

## Primeira passada

Percorre todo o arquivo procurando apenas por labels.

Cada label encontrada é adicionada à tabela de símbolos juntamente com o endereço ROM correspondente.

Exemplo:

```asm
(LOOP)
@i
M=M+1
```

gera a entrada

```
LOOP → endereço da próxima instrução
```

As labels não geram instruções de máquina.

---

## Segunda passada

O arquivo é percorrido novamente.

Nesta etapa:

* instruções A são traduzidas;
* instruções C são traduzidas;
* variáveis são inseridas automaticamente na tabela de símbolos a partir do endereço 16.

Exemplo:

```asm
@counter
```

Caso `counter` ainda não exista:

```
counter → 16
```

A próxima variável receberá o endereço 17, e assim sucessivamente.

---


# Tradução das instruções

## A-instruction

Entrada:

```asm
@21
```

Saída:

```
0000000000010101
```

Também suporta símbolos:

```asm
@LOOP
```

ou

```asm
@counter
```

---

## C-instruction

Entrada:

```asm
D=M+1
```

É dividida em:

```
dest = D
comp = M+1
jump = null
```

e traduzida para:

```
1111110111010000
```

---

# Compilação

Exemplo utilizando GCC:

```bash
gcc *.c -o assembler
```

ou

```bash
make
```

caso exista um Makefile.

---

# Execução

```
assembler arquivo.asm
```

ou

```bash
./assembler arquivo.asm
```

O programa produzirá automaticamente:

```
arquivo.hack
```

no mesmo diretório do arquivo de entrada.

---

# Exemplo

Entrada:

```asm
@2
D=A
@3
D=D+A
@0
M=D
```

Saída:

```
0000000000000010
1110110000010000
0000000000000011
1110000010010000
0000000000000000
1110001100001000
```

---

# Algoritmos utilizados

* Tabela de símbolos implementada em vetor.
* Busca linear para resolução de símbolos.
* Parsing utilizando `strtok()`.
* Algoritmo de duas passadas para resolução de labels e variáveis.

---

# Objetivo

Este projeto foi desenvolvido com fins educacionais para compreender o funcionamento interno de um assembler e a tradução de linguagem Assembly para código de máquina na arquitetura Hack proposta pelo curso **Nand2Tetris**.
