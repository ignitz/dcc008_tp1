#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

// enum Opcode {
//   Exit,
//   Load
  // "exit",
  // "loadi",
  // "storei",
  // "add",
  // "subtract",
  // "multiply",
  // "divide",
  // "jump",
  // "jmpz",
  // "jmpn",
  // "move",
  // "load",
  // "store",
  // "loadc",
  // "clear",
  // "moveSp",
  // "slt",
  // "call",
  // "loadSp",
  // "storeSp",
  // "ret",
  // "loadRa",
  // "storeRa",
  // "addi",
  // "sgt",
  // "seq",
  // "jmpp"
// }

bool clearLine(std::string& line);

void print( std::vector <std::string> & v );

std::string extract_opcode(std::vector<std::string> fields);
#endif
