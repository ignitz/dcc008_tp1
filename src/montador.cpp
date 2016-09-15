// C++
#include <iostream>
#include <cstdio>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include "symbol_table.hpp"

#include "passOne.hpp"

#define MSG_NOME_PROGRAMA		"Montador Wombat2\n"
#define MSG_COPYRIGHT 			"(C) 2016 Yuri Niitsuma <ignitzhjfk@gmail.com>\n         Lucas Machado <seuemailcabuloso@emai.com>\n"
#define MSG_USO							"    Uso: montador NOME_ARQUIVO [NOME_ARQUIVO_SAIDA]\n"

int
main(int argc, char *argv[])
{
	using namespace std;
	bool bSaida = true;
	std::string sEntrada = argv[1]; // Definicao do arquivo de entrada
	std::string sSaida;

	if (argc < 2){
		std::cout << MSG_NOME_PROGRAMA << MSG_COPYRIGHT << MSG_USO;
		return -1;
	}

	for(int i = 2; i < argc; i++){ // Verifica se nome de saida foi passado
		if(string("-o") == string(argv[i])) {
			bSaida = false;
			sSaida = argv[i+1];
		}
	}

	if(bSaida){
		sSaida = "exec.out"; // Nome padrão para geracao de executavel
	}

	ifstream fEntrada(sEntrada, ios::in);
	fstream fObjeto(sSaida, ios::out | ios::in | ios::trunc);

	// Checa se os arquivos estão abertos
	if (!fEntrada.is_open() || !fObjeto.is_open()) {
		cout << "Erro ao tentar abrir o arquivo " <<
					(fEntrada.is_open()? sSaida : sEntrada) << endl;
		exit(EXIT_FAILURE);
	}

	SymbolTable table;  // inicialização geral
	pass_one(fEntrada, table);
	table.printSymbols();

	// TODO
	// pass_two(entrada, objeto); // Codificacao com enderecos descomplicados

	fEntrada.close();
	fObjeto.close();
	//
	return 0;
}
