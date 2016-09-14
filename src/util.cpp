#include "util.hpp"

bool // Remove comentários, "\t" e espaços na linha da string
clearLine(std::string line) {
  using namespace std;
  if (line.find(";") != string::npos) // Retira comentários
    line.erase(line.find(";"), line.size() - line.find(";"));

  while (line.find("\t") != string::npos)
    line.replace(line.find("\t"), 1, " ");
  while (line.find("  ") != string::npos)
    line.replace(line.find("  "), 2, " ");
  if (line.find_first_of(" ") == 0)
    line.replace(line.find_first_of(" "), 1, "");
  if (line.find_last_of(" ") == 0)
      line.replace(line.find_last_of(" "), 1, "");
  return line.size() == 0 ? true : false;
}
