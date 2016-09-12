#ifndef util_H_INCLUDED
#define util_H_INCLUDED

#define MAX_OPCODE 27
#define MAX_TABLE 1000

// Tabela de instrucoes
typedef struct {
	char name[15];
	int v; // Valor do opcode
} Tabela_Opcodes;

// Tabela de simbolos, alocada com MAX posicoes
struct {
	char name[16];
	int address;
	int in_use;
} symbol_table[MAX_TABLE];

void initialize_symbol_table();
int get_symbol_address(char *name);
void insert_symbol(char *name, int address);

int get_opcode_param_by_name(char *name);

char *get_next_line(FILE *f);

int get_operands(int buffer);

// DEBUG
void print_symbol_table();
void print_binary(int x);

#endif
