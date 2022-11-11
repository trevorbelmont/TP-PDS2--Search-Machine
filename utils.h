#include <filesystem>
#include <string>

using std::string;

// retorna a string normalizada no interalo char a-z [97,122]
string Normalize(string h);

// remove characteres especiais (pontuação,símbolos e etc)
string CleanString(string h);

// Remove acentos (e substitui pelas pobres letras americanas)
string FlatString(string h);
