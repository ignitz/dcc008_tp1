#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_NOME_PROGRAMA "Montador Wombat2\n"
#define MSG_COPYRIGHT "(C) 2016 Yuri Niitsuma <ignitzhjfk@gmail.com>\n         Lucas Machado <seuemailcabuloso@emai.com>"
#define MSG_USO "Uso: %s NOME_ARQUIVO [NOME_ARQUIVO_SAIDA]\n"

// Primeira passada do montador
void pass_one(FILE *entrada)
{

}

// Segunda passada do montador
void pass_two(FILE *entrada, FILE *objeto)
{

}

int main(int argc, char *argv[])
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
		s = "exec.sa"; // Nome padrão para geracao de executavel
	}

	FILE *entrada = fopen(e, "r");
	FILE *objeto = fopen(s, "w+");

	pass_one(entrada); // Passada 1 para definicao da tabela de simbolos
	pass_two(entrada, objeto); // Codificacao com enderecos descomplicados

	fclose(entrada);
	fclose(objeto);

	return 0;
}
