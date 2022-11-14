#include <filesystem>
#include <map>
#include <set>
#include <string>
#include <vector>

using std::map;
using std::set;
using std::string;
using std::vector;

class Accio {  // referencia de Harry Potter, lol
   public:
    struct Invalid_Directory {
        string directory;
        string msg;
    };
    struct Invalid_File {
        string filename;
        string msg;
    };

    // ativa o fileIgnore
    bool ignoring;

    // Cria um motor que busca na pasta local (onde o executável está) com configurações de ignore padrão
    Accio();

    // cria um motor que busca na pasta na pasta especificada
    Accio(string folder);

    // return the name of the root folder to be searched
    string RootFolder();

    // adiciona a string "h" a lista de ignore. Retorna false se a string já foi ignorada.
    bool AddIgnore(string h);

    // adiciona todas as strings do vetor a lista de ignora. Retorna o número de NOVAS strings adicionadas
    int AddIgnore(vector<string> h);

    // adiciona as pastas padrão ( ".vscode/" e ".git/") a lista de ignore
    void IgnoreDefault();

    // remove a string h da lista de ignore. Sem atualizar os arquivos.
    bool RemoveIgnore(string h);  // Retorna true se alguma string foi excluida da lista de ignore
    // sintaxe alternativa para removeIgnore.
    bool Reconsider(string h);

    // limpa totalmente a lista de ignore
    void ClearIgnore();

    // retorna vetor com  nome dos arquivos encontrados
    vector<string> FileList();

    // carrega as palavras de um arquivo individual, path, na data usando o nome do arquivo como chave
    bool LoadFromFile(string path);  // retorno true = carregou com sucesso. false = alguma falha

    // carrega as palavras de todos os arquivos encontrados e mapeia por nome de arquivo
    int LoadAllFiles(vector<string> list_of_files);  // retorna o número de arquivos lidos com sucesso.

    void NormalizeData();

    // remove characteres especiais (pontuação, símbolos e etc)
    friend string CleanString(string h);

    // Remove acentos (e substitui pelas pobres letras americanas)
    friend string FlatString(string h);

    // torna todos os caracteres maiúsculos em minúsculos
    friend string LeveledString(string h);

    // retorna a string normalizada no interalo char a-z [97,122]
    friend string Normalize(string h);  // usa as strings declaradas anteriormente

    // retorna o nome de todos os arquivos nos subdiretórios da pasta especificada
    friend vector<string> RetriveFilePaths(string directory);

   private:
    // container de palavras mapeadas por nome de arquivo
    map<string, set<string>> data;

    // nome e caminho dos arquivos, relativo a pasta de busca especificada
    vector<string> allFiles;

    set<string> ignoreList;
    // diretório raíz para a busca
    string directory;
};

// sobrecarrega o operadoro operador * para multiplicar strings por ela msm n vezes
// se n for negativo, multiplica pelo inverso da string
string operator*(string str, int n);

string CleanString(string h);
string LeveledString(string h);
vector<string> RetriveFilePaths(string directory);
string Normalize(string h);
