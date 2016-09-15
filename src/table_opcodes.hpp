#ifndef _TAB_OPCODE_
#define _TAB_OPCODE_

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

class Opcode {
public:
  std::string name;
  int value;
  Opcode(std::string name, int value);
};

class TableOpcode {
private:
  std::vector<Opcode*> opcode;
public:
  std::string extract_opcode(std::vector<std::string> fields);
  bool isOpcode(std::string name);
  TableOpcode();
};

#endif
