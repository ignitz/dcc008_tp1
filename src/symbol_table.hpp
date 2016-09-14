#ifndef _SYMBOL_TABLE_
#define _SYMBOL_TABLE_

#include <iostream>
#include <cstdio>
#include <string>
#include <deque>

class Symbol {
private:
public:
  static int id;
  std::string name;
  int value;

  Symbol(std::string name, int value);
};

class SymbolTable {
private:
  std::deque<Symbol*> symbol;
public:
  SymbolTable();
  int getValue(std::string name);
  int getValue(int i);
  bool insertSymbol(std::string name, int value);
  bool checkSymbol(std::string name);
};

#endif
