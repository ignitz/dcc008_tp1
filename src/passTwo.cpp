#include "passTwo.hpp"

#define String std::string

#define HEAD_MIF "DEPTH = 256;\nWIDTH = 8;\nADDRESS_RADIX = HEX;\nDATA_RADIX = BIN;\nCONTENT\nBEGIN\n\n"
#define END_MIF "END;\n"
// don't forget END;

void
pass_two(std::ifstream& file, std::fstream& objeto, TableOpcode& table) {
  bool bVerbose = table.verbose;
  using namespace std;
  if (bVerbose) cout << "*********************************\nDEBUG: Iniciando Pass_Two" << endl;

  file.clear();
	file.seekg(0, file.beg); // Posiciona no inicio do arquivo novamente

  String line, output;  // campos da instrução
  vector<string> fields;        // tokens

  output += HEAD_MIF;

  table.location_counter = 0;

  while (getline(file, line)) {
    if (clearLine(line))
			continue;           // Se a linha não contiver instruções

    if (bVerbose) cout << "DEBUG: " << line << endl;

    boost::split(fields, line, // Separa a linha em tokens
          boost::is_any_of("\t "), boost::token_compress_on);

    output += table.get_line_mif(fields);
  }

  if (bVerbose) table.printSymbols();

  // Finaliza gravando em arquivo
  output += END_MIF;
  objeto << output;
} // end passtwo
