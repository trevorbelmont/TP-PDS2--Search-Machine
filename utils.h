#include <filesystem>
#include <string>

using std::string;

// remove characteres especiais (pontuação,símbolos e etc)
string CleanString(string h);

// Remove acentos (e substitui pelas pobres letras americanas)
string FlatString(string h);

// torna todos os caracteres maiúsculos em minúsculos
string LeveledString(string h);

// retorna a string normalizada no interalo char a-z [97,122]
string Normalize(string h);  // usa as strings declaradas anteriormente
