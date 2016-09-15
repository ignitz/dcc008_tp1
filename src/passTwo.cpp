#include "passTwo.hpp"

#define String std::string

#define HEAD_MIF "DEPTH = 256;\nWIDTH = 8;\nADDRESS_RADIX = HEX;\nDATA_RADIX = BIN;\nCONTENT\nBEGIN\n\n"
#define END_MIF "END;\n"
// don't forget END;

void
pass_two(std::ifstream& file, std::fstream& objeto, SymbolTable& table_symbol, bool bVerbose) {
  using namespace std;
  if (bVerbose) cout << "DEBUG: Iniciando Pass_Two" << endl;

  file.clear();
	file.seekg(0, file.beg); // Posiciona no inicio do arquivo novamente

  TableOpcode table_opcode;
  String line, output, opcode;  // campos da instrução
  vector<string> fields;        // tokens

  output += HEAD_MIF;

  while (getline(file, line)) {
    if (clearLine(line))
			continue;           // Se a linha não contiver instruções

    if (bVerbose) cout << "DEBUG: " << line << endl;

    boost::split(fields, line, // Separa a linha em tokens
          boost::is_any_of("\t "), boost::token_compress_on);

    if (fields[0].back() == ':') {
      if (fields[0].front() == '_') {
        fields.erase(fields.begin()); // Elimina label
      }
      // TODO
      // Tratamento das variáveis

    }

    // table_opcode.get_opcode_value


  }

  if (bVerbose) table_symbol.printSymbols();

  // Finaliza gravando em arquivo
  output += END_MIF;
  objeto << output;
} // end passtwo
