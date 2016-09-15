#ifndef _TAB_OPCODE_
#define _TAB_OPCODE_

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

/*
 * Elemento opcode com mneumonico e valor representado
 */
class Opcode {
public:
  std::string name;
  int value;
  Opcode(std::string name, int value);
};

/*
 * Tabela de Opcodes da classe acima
 */
class TableOpcode {
private:
  std::vector<Opcode*> opcode;
  
public:
  /* Verifica se um vetor de strings contém um opcode no primeiro iostream
   * ou no segundo, caso o primeiro seja label
   */
  std::string extract_opcode(std::vector<std::string> fields);

  // Verifica se uma string é um opcode
  bool isOpcode(std::string name);
  TableOpcode();
};

#endif
