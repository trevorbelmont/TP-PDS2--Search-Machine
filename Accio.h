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
    // cria um buscador vazio. Sem autoinicialização. equivale a "Accio(FALSE)"
    Accio();

    // cria um motor que busca na pasta na pasta especificada ignorando apenas arquivos sem extensão
    Accio(string folder);

    // Se TRUE - Cria um motor que busca na pasta local (onde o executável está). Usa configurações de ignore padrão
    Accio(int mode);  // ignora pastas com /.vscode/ e /.git/

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

    // limpa totalmente a lista de ignore e retorna o número string removidas da lista
    int ClearIgnore();

    // Remove da data os arquivos carregados que contem substrings das strings a serem ignoradas
    int ReleaseIgnored();

    // Remove todo o conteúdo carregado na data
    void ReleaseData();

    // Estabelece um novo diretório raiz de busca. NÃO ATUALIZA OU CARREGA NOVOS ARQUIVOS
    bool SetDirectory(string folder);

    // retorna um set com endereço de todos os arquivos encontrados
    set<string> FileList();

    void GetFiles(string h);

    // carrega as palavras de um arquivo individual, path, na data usando o nome do arquivo como chave
    bool LoadFromFile(string path);  // retorno true = carregou com sucesso. false = alguma falha

    // carrega as palavras de todos os arquivos encontrados e mapeia por nome de arquivo
    int LoadAllFiles(set<string> list_of_files);  // retorna o número de arquivos lidos com sucesso.

    //carrega e mapeia as palavras da lista de arquivos atual e retorna o número de arquivos carregados
    int LoadAllFiles();

    // método que normaliza todos os dados carregados. na prática é um resquício da implementação anterior (índice direto)
    void NormalizeData();

    // busca e lista os resultados a partir de um conjunto de palavras. retorna o número de resultados encontrados
    int Search(set<string> query);

    // busca e lista os resultados a partir de uma string, retorna o número de arquivos encontrados
    int Search(string query);

    // Lê um string, lista os resultados encontrados e devolve o nḿero de arquivos encontrados.
    int Search();

    // remove characteres especiais (pontuação, símbolos e etc)
    friend string CleanString(string h);

    // Remove acentos (e substitui pelas pobres letras americanas)
    friend string FlatString(string h);

    // torna todos os caracteres maiúsculos em minúsculos
    friend string LeveledString(string h);

    // retorna a string normalizada no interalo char a-z [97,122]
    friend string Normalize(string h);  // usa as strings declaradas anteriormente

    // retorna o nome de todos os arquivos nos subdiretórios da pasta especificada
    friend set<string> RetrieveFilePaths(string directory, set<string> igList);

   private:
    // container de conjunto de arquvivos (set) mapeadas por palavras. (em quais arquivos a palavra (chave) aparece)
    map<string, set<string>> data;

    // nome e caminho dos arquivos, relativo a pasta de busca especificada
    set<string> allFiles;

    set<string> ignoreList;
    // diretório raíz para a busca
    string directory;
};

// demanda a entrada de uma string que será normalizada e partida em palavras e retornada num set
set<string> getNormalizedQuery();

// retorna a string h normalizada e dividade em palavras no formato de um set
set<string> getNormalizedQuery(string h);

// sobrecarrega o operadoro operador * para multiplicar strings por ela msm n vezes
// se n for negativo, multiplica pelo inverso da string
string operator*(string str, int n);

string CleanString(string h);
string LeveledString(string h);
set<string> RetrieveFilePaths(string directory, set<string> igList);
string Normalize(string h);
