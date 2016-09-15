#include "util.hpp"

bool
clearLine(std::string& line) {
  using namespace std;
  if (line.find(";") != string::npos) // Retira comentários
    line.erase(line.find(";"), line.size() - line.find(";"));

  while (line.find("\t") != string::npos) // Retira tabs
    line.replace(line.find("\t"), 1, " ");
  while (line.find("  ") != string::npos) // Retira espaços duplos
    line.replace(line.find("  "), 2, " ");
  if (line.find_first_of(" ") == 0)
    line.replace(line.find_first_of(" "), 1, "");
  if (line.find_last_of(" ") == 0)
      line.replace(line.find_last_of(" "), 1, "");
  return line.size() == 0 ? true : false; // Retorna true se a linha ficou vazia
}

void
print(std::vector <std::string> & v)
{
  using namespace std;
  for (size_t n = 0; n < v.size(); n++)
    cout << "\"" << v[ n ] << "\"\n";
  cout << endl;
}
