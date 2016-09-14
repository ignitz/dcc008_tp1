#include "symbol_table.hpp"


/**************************
 * Symbol
 */
int Symbol::id = 0;

Symbol::Symbol(std::string name, int value) {
  id++;
  this->name = name;
  this->value = value;
}

/**************************
 * SymbolTable
 */
SymbolTable::SymbolTable() {
  // Tá tranquilo Entei
}

int
SymbolTable::getValue(int i) {
  if (i >= 1 && i <= (int) this->symbol.size())
    return this->symbol.at(i-1)->value;
  else
    return -1;
}

int
SymbolTable::getValue(std::string name) {
  int size = this->symbol.size();
  for (int i = 0; i < size; i++)
    if (this->symbol.at(i)->name.compare(name) == 0) return this->symbol.at(i)->value;
  return -1;
}

bool
SymbolTable::checkSymbol(std::string name) {
  int size = this->symbol.size();
  for (int i = 0; i < size; i++)
    if (this->symbol.at(i)->name.compare(name) == 0) return true;
  return false;
}

bool
SymbolTable::insertSymbol(std::string name, int value) {
  if (this->checkSymbol(name)) // Verifica se ja tem na tabela
    return false;
  this->symbol.push_back(new Symbol(name, value));
  return true;
}
