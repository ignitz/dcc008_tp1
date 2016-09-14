#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

#define MSG_NOME_PROGRAMA		"Montador Wombat2\n"
#define MSG_COPYRIGHT 			"(C) 2016 Yuri Niitsuma <ignitzhjfk@gmail.com>\n         Lucas Machado <seuemailcabuloso@emai.com>\n"
#define MSG_USO							"    Uso: %s NOME_ARQUIVO [NOME_ARQUIVO_SAIDA]\n"

// Primeira passada do montador
void
pass_one(FILE *entrada)
{
	initialize_symbol_table();
	int location_counter = 0;
	char *line, *token_aux;

	while((line = get_next_line(entrada))){
		char *token = strtok(line, "\t ");
		while(token){
			if(token[0] == ';'){ // Comentario, ignora resto da linha
				break;
			}
			if(token[strlen(token)-1] == ':'){ // Label, insere na tabela de simbolos
				token[strlen(token)-1] = '\0';
				if (token[0] == '_') {
					insert_symbol(token, location_counter);
				}
				else { // Declara var
					token_aux = token;
					token = strtok(NULL, "\t ");
					if (strcmp(token, ".data") == 0) { // Reservar bytes na memória
						token = strtok(NULL, "\t ");
						token = strtok(NULL, "\t ");
						printf("%s %s\n", token_aux, token);
						insert_symbol(token_aux, atoi(token));
					}
					else {
						fprintf(stderr, "Erro em passOne: %s\n", token);
						exit(1);
					}
				}

			} else if(get_opcode_param_by_name(token) >= 0){
				location_counter += 2; // Verifica se eh opcode e conta como mais byte deslocado
			}
			token = strtok(NULL, "\t ");
		}
		free(line);
	}
}

// Segunda passada do montador
void
pass_two(FILE *entrada, FILE *objeto)
{
	print_symbol_table(); // DEBUG

	char  *line; // String temporária para linha do assembly
	char  *token;
	int   buffer; // A saída
	int   end; // Flag para indicar se houve exit
	fseek(entrada, 0, SEEK_SET); // Posiciona no início do arquivo

	while (line = get_next_line(entrada)) {
		token = strtok(line, "\t ");
		buffer = end = 0;

		while (token) {
			if (token[0] == ';') {
				break;
			}

			if (token[strlen(token)-1] != ':') { // Se não for label
				if (get_opcode_param_by_name(token) >= 0) {
					buffer = get_operands(token);
					if (buffer == 0)
						end = 1;
				}
			}
			token = strtok(NULL, "\t ");
		}

		if (buffer) {
			// fwrite(&buffer, sizeof(int), 1, objeto);
			fprintf(objeto, "%04X\n", buffer);
			print_binary(buffer);
		}
		else if (buffer == 0 && end == 1) {
			// fwrite(&buffer, sizeof(int), 1, objeto); // Vai ter que gravar em texto
			fprintf(objeto, "%04X\n", buffer);
			print_binary(buffer);
		}
	}
	free(line);
}

int
main(int argc, char *argv[])
{
	int i;
	int saida = 0;

	char *e = argv[1]; // Definicao do arquivo de entrada
	char *s;

	if (argc < 2){
		fprintf(stderr, MSG_NOME_PROGRAMA);
		fprintf(stderr, MSG_COPYRIGHT);
		fprintf(stderr, MSG_USO, argv[0]);
		return 0;
	}

	for(i = 2; i < argc; i++){
		// Verifica se nome de saida foi passado
		if(strcmp(argv[i], "-o") == 0){
			saida = 1;
			s = argv[i+1];
		}
	}

	if(saida == 0){
		s = "exec.out"; // Nome padrão para geracao de executavel
	}

	FILE *entrada = fopen(e, "r");
	FILE *objeto = fopen(s, "w+");

	pass_one(entrada); // Passada 1 para definicao da tabela de simbolos
	pass_two(entrada, objeto); // Codificacao com enderecos descomplicados

	fclose(entrada);
	fclose(objeto);

	return 0;
}
