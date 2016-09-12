#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

// A máquina possui uma memória de 256 posições, numeradas de 0 a 255.
// Cada registrador pode armazenar uma palavra de 16 bits.
// Existem 8 registradores de uso geral, os quais são nomeados de “R0” a “R7”.

Tabela_Opcodes opcode_table[MAX_OPCODE] = {
  {"exit", 0}, {"loadi", 1}, {"storei", 2},
  {"add", 3}, {"subtract", 4}, {"multiply", 5},
  {"divide", 6}, {"jump", 7}, {"jmpz", 8},
  {"jmpn", 9}, {"move", 10}, {"load", 11},
  {"store", 12}, {"loadc", 13}, {"clear", 14},
  {"moveSp", 15}, {"slt", 16}, {"call", 17},
  {"loadSp", 18}, {"storeSp", 19}, {"ret", 20},
  {"loadRa", 21}, {"storeRa", 22}, {"addi", 23},
  {"sgt", 24}, {"seq", 25}, {"jmpp", 26}
};

// Inicializa a tabela de simbolos
void initialize_symbol_table() {
  int i;
  for (i = 0; i < MAX_TABLE; i++) {
    symbol_table[i].address = 0;
		symbol_table[i].in_use = 0;
  }
}

// Retorna o endereco de um simbolo da tabela
int get_symbol_address(char *name) {
  int i = 0;
  while (i < MAX_TABLE && strcmp(symbol_table[i].name, name) != 0) i++;
  return (i == MAX_TABLE) ? -1 : symbol_table[i].address;
}

// Insere um simbolo na tabela
void insert_symbol(char *name, int address) {
  int i = 0;
  while (symbol_table[i].in_use) i++;
  strcpy(symbol_table[i].name, name);
  symbol_table[i].address = address;
  symbol_table[i].in_use = 1;
}

// Retorna um parametro de alguma instrucao da tabela de instrucoes
// Recebe como entrada o nome do opcode
int get_opcode_param_by_name(char *name)
{
	int i;
	for(i = 0; i < MAX_OPCODE; i++){
		if(strcmp(opcode_table[i].name, name) == 0)
			return opcode_table[i].v;
	}
	return -1;
}

// Retorna a proxima linha de um stream
char *get_next_line(FILE *f) {
	int cont = 0, max = 32;
	char *line = (char *)malloc(max*sizeof(char));
	char c;
	while(1){
		c = fgetc(f);
		if(c==EOF || c=='\n'){
			break;
		}
		if(c=='\r'){ // Quebra de linhas do Windows
			fgetc(f);
			break;
		}
		if(cont==(max-1)){
			line = (char *)realloc(line, (2*max)*sizeof(char));
			max = 2*max;
		}
		line[cont] = c;
		cont++;
	}
	line[cont] = '\0';
	if(c==EOF && cont==0){
		free(line);
		return NULL;
	}
	return line;
}


/*
  Funções utilizadas para DEBUG
*/
// Printa toda a tabela de símbolos
void print_symbol_table() {
  int i = 0;
  for (i = 0; i < MAX_TABLE; i++) {
    if (symbol_table[i].in_use)
      printf("%02X\t%s\n", symbol_table[i].address, symbol_table[i].name);
    else
      break;
  }
}

void print_binary(int x) {
  printf("%04X\n", x);
  for (int i = 0; i < 16; i++) {
    printf("%d", (x & 0x8000) >> 15);
    x <<= 1;
  }
  printf("\n");
}

int get_operands(int buffer) {
  // buffer <<= 11;
  switch (buffer) {
    case 0: // "exit"
      // 5 - 11
      // op - un11
      buffer = 0;
      break;
    case 1: // "loadi"
      // 5 - 3 - 8
      // op - reg - addr
      break;
    case 2: // "storei"
      // 5 - 3 - 8
      // op - reg - addr
      break;
    case 3: // "add"
      // 5 - 3 - 3 - 5
      // op - reg - reg - un5
      break;
    case 4: // "subtract"
      // 5 - 3 - 3 - 5
      // op - reg - reg - un5
      break;
    case 5: // "multiply"
      // 5 - 3 - 3 - 5
      // op - reg - reg - un5
      break;
    case 6: // "divide"
      // 5 - 3 - 3 - 5
      // op - reg - reg - un5
      break;
    case 7: // "jump"
      // 5 - 3 - 8
      // op - un3 - addr
      break;
    case 8: // "jmpz"
      // 5 - 3 - 8
      // op - reg - addr
      break;
    case 9: // "jmpn"
      // 5 - 3 - 8
      // op - reg - addr
      break;
    case 10: // "move"
      // 5 - 3 - 3 - 5
      // op - reg - reg - un5
      break;
    case 11: // "load"
      // 5 - 3 - 3 - 5
      // op - reg - reg - un5
      break;
    case 12: // "store"
      // 5 - 3 - 3 - 5
      // op - reg - reg - un5
      break;
    case 13: // "loadc"
      // 5 - 3 - 8
      // op - reg - sgn5
      break;
    case 14: // "clear"
      // 5 - 3 - 8
      // op - reg - un8
      break;
      // 5 - 3 - 8
      // op - un3 - sgn8
    case 15: // "moveSp"
      break;
    case 16: // "slt"
      // 5 - 3 - 3 - 3 - 2
      // op - reg - reg - reg - x
      break;
    case 17: // "call"
      // 5 - 3 - 8
      // op - un3 - addr
      break;
    case 18: // "loadSp"
      // 5 - 3 - 8
      // op - reg - unsgn8
      break;
    case 19: // "storeSp"
      // 5 - 3 - 8
      // op - reg - unsgn8
      break;
    case 20: // "ret"
      // 5 - 11
      // op - un11
      break;
    case 21: // "loadRa"
      // 5 - 3 - 8
      // op - un3 - unsgn8
      break;
      // 5 - 3 - 8
      // op - un3 - unsgn8
    case 22: // "storeRa"
      break;
    case 23: // "addi"
      // 5 - 3 - 8
      // op - reg - sgn5
      break;
    case 24: // "sgt"
      // 5 - 3 - 3 - 3 - 2
      // op - reg - reg - reg - un2
      break;
    case 25: // "seq"
      // 5 - 3 - 3 - 3 - 2
      // op - reg - reg - reg - un2
      break;
    case 26: // "jmpp"
      // 5 - 3 - 8
      // op - reg - addr
      break;
    default:
      fprintf(stderr, "Operando inválido\n");
      exit(1);
      return 0;
  }

  return buffer;
}
