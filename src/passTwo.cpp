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
  String line, output, fields, opcode;  // campos da instrução

  output += HEAD_MIF;

  while (getline(file, line)) {
    if (bVerbose) cout << "DEBUG: " << line << endl;
    if (clearLine(line))
			continue;           // Se a linha não contiver instruções

    // boost::split(fields, line, // Separa a linha em tokens
  	// 		boost::is_any_of("\t "), boost::token_compress_on);

  }

  output += END_MIF;
  objeto << output;

  if (bVerbose) table_symbol.printSymbols();

	// int location_counter, length, type; // variáveis diversas
	// final int END_STATEMENT = −2; // sinaliza final da entrada
	// final int MAX_CODE = 16; // máximo de bytes de código por instrução
	// byte code[ ] = new byte[MAX_CODE]; //contém código gerado por instrução
  //
  // location_counter = 0; // monta a primeira instrução em 0
  //
	// while (more_input) { // more_input ajustada para falso por END
	// 	type = read_type( );      // obtém campo de tipo da próxima linha
	// 	opcode = read_opcode( );  // obtém campo de opcode da próxima linha
	// 	length = read_length( );  // obtém comprimento de campo da próxima linha
	// 	line = read_line( );      // obtém a linha de entrada propriamente dita
  //
	// 	if (type != 0) { // tipo 0 é para linhas de comentário
	// 		switch(type) { // gerar o código de saída
	// 			case 1: eval_type1(opcode, length, line, code); break;
	// 			case 2: eval_type2(opcode, length, line, code); break;
	// 		 // outros casos aqui
	// 		}
	// 	}
	// 	write_output(code); // escreva o código binário
	// 	write_listing(code, line); // imprima uma linha na listagem
	// 	 location_counter = location_counter + length; // atualize loc_ctr
	// 	 if (type == END_STATEMENT) { // terminamos a entrada?
	// 	 	more_input = false; // se terminamos, execute tarefas de manutenção
	// 	 	finish_up( ); // execute tarefas de manutenção gerais e termine
	// 	 }
	// 	}
	// }

} // end passtwo
