#include "passOne.hpp"

// Primeira passada do montador
void
pass_one(std::ifstream& file, SymbolTable& table_symbol, bool bVerbose) {
	using namespace std;

  TableOpcode table_opcode;                  // Tabela para Opcodes
	std::string line, symbol, literal, strOpcode;  // campos da instrução
	int location_counter, store_location;       // variáveis diversas
	location_counter = 0;                       // monta a primeira instrução em 0
	std::vector<string> fields;                 // tokens

	while (getline(file, line)) { // obtenha uma linha de entrada
		if (clearLine(line))
			continue;           // Se a linha não contiver instruções

		if (bVerbose) cout << "DEBUG: " << line << endl;

		boost::split(fields, line, // Separa a linha em tokens
				boost::is_any_of("\t "), boost::token_compress_on);

		if (fields[0].back() == ':') { // Insere o simbolo na tabela
      // Prefixo "_" eh label
      store_location = (fields[0].front() == '_') ? location_counter : 0;
			fields[0].pop_back();

			if (table_symbol.checkSymbol(fields[0])) { // Verifica se label ja existe
				std::cerr << "Redeclaração do símbolo: " << fields[0] << std::endl;
				exit(EXIT_FAILURE);
			}
			else {
				table_symbol.insertSymbol(fields[0], store_location, fields[2]);
			}

			fields[0].push_back(':');
		} // end of while (getline(file, line))

		strOpcode = table_opcode.extract_opcode(fields);

		if (table_opcode.isOpcode(strOpcode)) {
			location_counter += 2;
		}
		else if (strOpcode.compare(".data")) {
			location_counter += 0;
		}
		else {
			std::cerr << "Opcode desconhecido: " << strOpcode << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	// modifica symbol
	table_symbol.redefine(location_counter);

	file.clear();
	file.seekg(0, file.beg); // Posiciona no inicio do arquivo novamente

}
