#include "passOne.hpp"

// Primeira passada do montador
void
pass_one(std::ifstream& file, SymbolTable& table) {
	using namespace std;

  TableOpcode table_opcode;                  // Tabela para Opcodes
	std::string line, symbol, literal, strOpcode;  // campos da instrução
	int location_counter, store_location;       // variáveis diversas
	location_counter = 0;                       // monta a primeira instrução em 0
	std::vector<string> fields;                 // tokens

	while (getline(file, line)) { // obtenha uma linha de entrada
		if (clearLine(line))
			continue;           // Se a linha não contiver instruções

		boost::split(fields, line, // Separa a linha em tokens
				boost::is_any_of("\t "), boost::token_compress_on);

		if (fields[0].back() == ':') { // Insere o simbolo na tabela
      // Prefixo "_" eh label
      store_location = (fields[0].front() == '_') ? location_counter : 0;
			fields[0].pop_back();
			table.insertSymbol(fields[0], store_location);
			fields[0].push_back(':');
		}


		strOpcode = table_opcode.extract_opcode(fields);

    std::cout << line << std::endl;
		if (table_opcode.isOpcode(strOpcode)) {
			location_counter += 2;
			/* code */
		}
		else {
			std::cerr << "Opcode desconhecido: " << strOpcode << std::endl;
			exit(EXIT_FAILURE);
		}

	}
	// When you finish reading all the contents of your file,
	// the state of the stream would be eof, thus all subsequent input operations will fail.
	file.clear();
	file.seekg(0, file.beg); // Posiciona no inicio do arquivo novamente

	// sort_literal_table( );	// e ordenar a tabela de literais
	// remove_redundant_literals( );	// e remover literais duplicadas
}
