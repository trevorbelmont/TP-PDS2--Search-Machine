#include <filesystem>
#include <string>
#include <vector>

using std::string;
using std::vector;

// class Accio {  // referencia de Harry Potter, lol

// remove characteres especiais (pontuação,símbolos e etc)
string CleanString(string h);

// Remove acentos (e substitui pelas pobres letras americanas)
string FlatString(string h);

// torna todos os caracteres maiúsculos em minúsculos
string LeveledString(string h);

// retorna a string normalizada no interalo char a-z [97,122]
string Normalize(string h);  // usa as strings declaradas anteriormente

vector<string> RetriveFilePaths(string directory);


//};