// C++
#include <iostream>
#include <cstdio>
#include <string>
#include <iomanip>
#include <fstream>
#include "symbol_table.hpp"
#include "util.hpp"

#define MSG_NOME_PROGRAMA		"Montador Wombat2\n"
#define MSG_COPYRIGHT 			"(C) 2016 Yuri Niitsuma <ignitzhjfk@gmail.com>\n         Lucas Machado <seuemailcabuloso@emai.com>\n"
#define MSG_USO							"    Uso: montador NOME_ARQUIVO [NOME_ARQUIVO_SAIDA]\n"

// Primeira passada do montador
void
pass_one(std::ifstream& file) {
	using namespace std;
	SymbolTable *table = new SymbolTable;  // inicialização geral

	std::string line, symbol, literal, opcode;  // campos da instrução
	int location_counter, length, value, type;  // variáveis diversas
	location_counter = 0;                       // monta a primeira instrução em 0
	int END_STATEMENT = -2;                     // sinaliza final da entrada

	while (getline(file, line)) { // obtenha uma linha de entrada
		length = 0;           //
		type = 0;             // # bytes na instrução

		if (clearLine(&line))
			continue;           // Se a linha não contiver instruções
		std::cout << line << std::endl;

		// if (line_is_not_comment(line)) { // de que tipo (formato) é a instrução
		// 	symbol = check_for_symbol(line);	// essa linha é rotulada?
		// 	if (symbol != null)	// se for, registre símbolo e valor
		// 		enter_new_symbol(symbol, location_counter);
		// 	literal = check_for_literal(line);	// a linha contém uma literal?
		// 	if (literal != null)	// se contiver, entre a linha na tabela
		// 		enter_new_literal(literal);
		// 	// Agora determine o tipo de opcode. −1 significa opcode ilegal.
		//   opcode = extract_opcode(line);	// localize mnemônico do opcode
		// 	type = search_opcode_table(opcode);	 // ache formato, por exemplo OP REG1,REG2
		// 	if (type < 0)	// se não for um opcode, é uma pseudoinstrução?
		// 		type = search_pseudo_table(opcode);
		// 	switch(type) { // determine o comprimento dessa instrução
		// 		case 1: length = get_length_of_type1(line); break;
		// 		case 2: length = get_length_of_type2(line); break;
		// 		// outros casos aqui
		// 	}
		// }
		// write_temp_file(type, opcode, length, line);	 // informação útil para a passagem dois
		// location_counter = location_counter + length;	 // atualize loc_ctr
		// 	if (type == END_STATEMENT) {	// terminamos a entrada?
		// 		more_input = false; // se terminamos, execute tarefas de preparo
		// 		rewind_temp_for_pass_two( );	// tais como rebobinar o arquivo temporário
		// 			sort_literal_table( );	// e ordenar a tabela de literais
		// 			remove_redundant_literals( );	// e remover literais duplicadas
		// 	}
	}
}


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



	pass_one(fEntrada);
	// pass_two(entrada, objeto); // Codificacao com enderecos descomplicados
	//
	fEntrada.close();
	fObjeto.close();
	//
	return 0;
}
