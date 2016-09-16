#include "table_opcodes.hpp"

// Parâmetros para serem passados pelos construtores
#define EXIT      "exit",     0
#define LOADI     "loadi",    1
#define STOREI    "storei",   2
#define ADD       "add",      3
#define SUBTRACT  "subtract", 4
#define MULTIPLY  "multiply", 5
#define DIVIDE    "divide",   6
#define JUMP      "jump",     7
#define JMPZ      "jmpz",     8
#define JMPN      "jmpn",     9
#define MOVE      "move",     10
#define LOAD      "load",     11
#define STORE     "store",    12
#define LOADC     "loadc",    13
#define CLEAR     "clear",    14
#define MOVESP    "moveSp",   15
#define SLT       "slt",      16
#define CALL      "call",     17
#define LOADSP    "loadSp",   18
#define STORESP   "storeSp",  19
#define RET       "ret",      20
#define LOADRA    "loadRa",   21
#define STORERA   "storeRa",  22
#define ADDI      "addi",     23
#define SGT       "sgt",      24
#define SEQ       "seq",      25
#define JMPP      "jmpp",     26

Opcode::Opcode(std::string name, int value) {
  this->name = name;
  this->value = value;
}

bool
TableOpcode::isOpcode(std::string name) {
  int size = this->opcode.size();
  for (int i = 0; i < size; i++)
    if (name.compare(this->opcode[i]->name) == 0) return true;
  return false;
}

std::string
TableOpcode::extract_opcode(std::vector<std::string> fields) {
  if (fields[0].back() == ':') // Eh label?
    return this->isOpcode(fields[1]) ? fields[1] : ""; // Pega o proximo token
  return this->isOpcode(fields[0]) ? fields[0] : "";
}

int
TableOpcode::get_opcode_value(std::string name) {
  int size = this->opcode.size();
  for (int i = 0; i < size; i++) {
    if (name.compare(this->opcode[i]->name) == 0) return this->opcode[i]->value;
  }
  return -1;
}

std::string
TableOpcode::get_instruction(std::vector<std::string> fields) {
  std::string r; // to return
  if (fields.size() == 0) return "";

  if (fields[0].back() == ':' && fields[0].front() == '_')
    fields.erase(fields.begin()); // Elimina label

  if (fields[0].back() == ':') {
    // do .data
    if (fields.size() >= 4 && fields[1].compare(".data") == 0) {
      if (this->location_counter == this->get_symbol_value(fields[0])) {
        int many = std::stoi(fields[2]);
        for (int i = 0; i < many; i++) {
          r += int_to_hex(this->location_counter);
          r += "        :  ";
          r += string_binary(std::stoi(fields[3])) + ";\n";
          this->location_counter++;
        }
      }
      else{
        std::cerr << "Erro no endereço do símbolo "
          << fields[0] << std::endl;
        exit(EXIT_FAILURE);
      }
    }
  }
  else {
    int binary = this->get_opcode_value(fields[0]) << 11;

    r += int_to_hex(this->location_counter);
    r += "        :  ";
    r += string_binary( (binary & 0xFF00) >> 8 ) + ";\n";
    this->location_counter++;
    /*
     * TODO
     * Inserir os tipos e os bits adicionais
     */
    r += int_to_hex(this->location_counter);
    r += "        :  ";
    r += string_binary( binary & 0x00FF ) + ";\n";
    this->location_counter++;

    if (this->verbose) { // DEBUG
      std::cout << string_binary( (binary & 0xFF00) >> 8 )
        << string_binary( binary & 0x00FF ) << std::endl;
    }

  }

  if (this->verbose) std::cout << r; // DEBUG
  return r;
}

TableOpcode::TableOpcode() {
  // Insere todos os Opcodes em uma tabela
  this->opcode.push_back(new Opcode( EXIT ));
  this->opcode.push_back(new Opcode( LOADI ));
  this->opcode.push_back(new Opcode( STOREI ));
  this->opcode.push_back(new Opcode( ADD ));
  this->opcode.push_back(new Opcode( SUBTRACT ));
  this->opcode.push_back(new Opcode( MULTIPLY ));
  this->opcode.push_back(new Opcode( DIVIDE ));
  this->opcode.push_back(new Opcode( JUMP ));
  this->opcode.push_back(new Opcode( JMPZ ));
  this->opcode.push_back(new Opcode( JMPN ));
  this->opcode.push_back(new Opcode( MOVE ));
  this->opcode.push_back(new Opcode( LOAD ));
  this->opcode.push_back(new Opcode( STORE ));
  this->opcode.push_back(new Opcode( LOADC ));
  this->opcode.push_back(new Opcode( CLEAR ));
  this->opcode.push_back(new Opcode( MOVESP ));
  this->opcode.push_back(new Opcode( SLT ));
  this->opcode.push_back(new Opcode( CALL ));
  this->opcode.push_back(new Opcode( LOADSP ));
  this->opcode.push_back(new Opcode( STORESP ));
  this->opcode.push_back(new Opcode( RET ));
  this->opcode.push_back(new Opcode( LOADRA ));
  this->opcode.push_back(new Opcode( STORERA ));
  this->opcode.push_back(new Opcode( ADDI ));
  this->opcode.push_back(new Opcode( SGT ));
  this->opcode.push_back(new Opcode( SEQ ));
  this->opcode.push_back(new Opcode( JMPP ));
}

// #define EXIT      "exit",     0
// #define LOADI     "loadi",    1
// #define STOREI    "storei",   2
// #define ADD       "add",      3
// #define SUBTRACT  "subtract", 4
// #define MULTIPLY  "multiply", 5
// #define DIVIDE    "divide",   6
// #define JUMP      "jump",     7
// #define JMPZ      "jmpz",     8
// #define JMPN      "jmpn",     9
// #define MOVE      "move",     10
// #define LOAD      "load",     11
// #define STORE     "store",    12
// #define LOADC     "loadc",    13
// #define CLEAR     "clear",    14
// #define MOVESP    "moveSp",   15
// #define SLT       "slt",      16
// #define CALL      "call",     17
// #define LOADSP    "loadSp",   18
// #define STORESP   "storeSp",  19
// #define RET       "ret",      20
// #define LOADRA    "loadRa",   21
// #define STORERA   "storeRa",  22
// #define ADDI      "addi",     23
// #define SGT       "sgt",      24
// #define SEQ       "seq",      25
// #define JMPP      "jmpp",     26
