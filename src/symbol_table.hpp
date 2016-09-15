#ifndef _SYMBOL_TABLE_
#define _SYMBOL_TABLE_

#include <iostream>
#include <cstdio>
#include <string>
#include <deque>

enum TypeSymbol {label, variable};

/*
 * Elemento contendo o Símbolo com seu ID, símbolo e posicao
 */
class Symbol {
public:
  static int id;
  std::string name;
  int value;
  int num_bytes;
  TypeSymbol type;
  Symbol(std::string name, int value);
  Symbol(std::string name, int value, int num_bytes);
  Symbol(std::string name, int value, std::string num_bytes);
  Symbol(std::string name, int value, TypeSymbol type);
};

class SymbolTable {
private:
  std::deque<Symbol*> symbol;
public:
  SymbolTable();
  int getValue(std::string name);
  int getValue(int i);
  bool insertSymbol(std::string name, int value);
  bool insertSymbol(std::string name, int value, std::string num_bytes);
  bool checkSymbol(std::string name);

  /*
   * Adiciona memórias com o tamanho em bytes
   */
  bool redefine(int location_counter);

  void printSymbols();
};

#endif
