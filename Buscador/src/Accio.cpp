
#include "Accio.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
using std::cin;
using std::cout;
using std::filesystem::exists;
using std::filesystem::recursive_directory_iterator;

Accio::Accio(string folder) {
    directory = folder;

    GetFiles(directory);

    LoadAllFiles(allFiles);
}

// um Accio Motor de Busca não inicializado
Accio::Accio() {}

Accio::Accio(int auto_initialize) {
    if (auto_initialize > 0) {
        IgnoreDefault();  // auto add .git, .pdf e .vscode to ignore paths

        directory = "./";

        GetFiles(directory);

        LoadAllFiles(allFiles);
    } else if (auto_initialize == 0) {
        Accio raw;
        (*this) = raw;
    }
}

void Accio::GetFiles(string h) {
    directory = h;
    do {
        try {
            allFiles = RetrieveFilePaths(directory, ignoreList);

        } catch (Invalid_Directory e) {
            cout << e.msg << endl;
            cout << "Insert a valid directory path or press Enter to search the "
                    "current folder: ";
            string cmd;
            getline(cin, cmd);

            directory = (cmd.length() == 0) ? "./" : cmd;
            if (exists(directory)) {  // && filesystem::is_directory(directory)) {
                (this)->GetFiles(directory);
                // allFiles = RetrieveFilePaths(directory, ignoreList);
            }
        }

    } while (
        !exists(directory));  // repete enquanto não encontrar um diretório válido
}

bool Accio::GetFiles() {
    if (filesystem::is_directory((*this).RootFolder()) == false) {
        return false;
    } else {
        (*this).GetFiles((this->RootFolder()));
    }
    return true;
}

int Accio::Search(set<string> query) {
    if (query.empty()) {
        return 0;
    }

    int results = 0;

    string menorCardinalidade = *query.begin();
    for (string s : query) {
        if (data[s].size() < data[menorCardinalidade].size()) {
            if (data[s].size() > 0) {
                menorCardinalidade = s;
            } else {
                return 0;  // retorna 0 se qualaquer das palavras tem cardinalidade 0
            }
        }
    }

    set<string> whichFiles;

    // pra cada arquivo que contem a palavra de menor cardinalidade (menor recorrencia)
    for (string fl : data[menorCardinalidade]) {
        int matched = 1;
        for (string word : query) {           // para cada palvra da query
            matched *= data[word].count(fl);  // chega se o arquivo está no set da palavra da query
        }
        if (matched != 0) {  // if matched != 0 (se  aquele documento possui a outra palavra da qurery
            whichFiles.insert(fl);
            results++;
        }
    }

    for (string s : whichFiles) {
        cout << "\t" << s << endl;
    }
    return results;
}

int Accio::Search(string h) { return Search(getNormalizedQuery(h)); }

int Accio::Search() { return Search(getNormalizedQuery()); }

bool Accio::AddIgnore(string h) {
    return (*this).ignoreList.insert(h).second;  // retorna se uma NOVA string foi
                                                 // adicionada ou não.
}

int Accio::AddIgnore(vector<string> h) {
    int i = 0;
    for (string s : h) {
        if (this->ignoreList.insert(s).second) {  // adiciona cada string a lista
            i++;                                  // soma mais um para cada NOVA strin adicionada
        }
    }
    return i;
}

void Accio::IgnoreDefault() {
    (*this).AddIgnore(".vscode/");
    (*this).AddIgnore(".git/");
    (*this).AddIgnore(".pdf");
}

int Accio::ClearIgnore() {
    int cleared = (*this).ignoreList.size();
    (*this).ignoreList.clear();
    return cleared;
}

int Accio::ReleaseIgnored() {
    if (ignoreList.empty()) {
        return 0;
    }
    int ignored = 0;

    for (auto fl = (*this).allFiles.begin(); fl != allFiles.end();) {
        bool erased = false;
        for (auto ignr = (*this).ignoreList.begin();
             ignr != (*this).ignoreList.end(); ignr++) {
            if (static_cast<int>(fl->find(*ignr)) != -1) {
                ignored++;
                fl = allFiles.erase(fl);
                erased = true;
                break;
            }
        }
        if (erased == false) {
            fl++;
        }
    }
    (*this).ReleaseData();
    (*this).LoadAllFiles((*this).allFiles);

    cout << ignored << " ignored files have been unload." << endl;
    return ignored;
}

void Accio::ReleaseData() { this->data.clear(); }

bool Accio::SetDirectory(string folder) {
    if (exists(folder)) {
        (*this).directory = folder;
        return true;
    } else {
        return false;
    }
}

bool Accio::RemoveIgnore(string h) {
    int i = (*this).ignoreList.erase(h);
    return i != 0;
}

bool Accio::Reconsider(string h) { return (*this).RemoveIgnore(h); }

string Accio::RootFolder() const { return (*this).directory; }

set<string> Accio::FileList() const { return (*this).allFiles; }

set<string> RetrieveFilePaths(string directory, set<string> igList) {
    // lança exceção caso nenhum diretório tenha sido especificado
    if (directory.empty()) {
        Accio::Invalid_Directory e{"", "Diretório não especificado!"};
        throw(e);
    }
    // Lança exceção se o diretório não foi encontrado
    if (exists(directory) == false) {
        Accio::Invalid_Directory e{directory};
        e.msg = "O diretório \"/" + e.directory + "/\" não foi encontrado!";
        throw(e);
    }
    if (filesystem::is_directory(directory) == false) {
        Accio::Invalid_Directory e;
        e.directory = directory;
        e.msg = "That's not a directory, dumbass!!!";
        throw(e);
    }

    set<string> arquivos;
    int loaded = 0;
    int ignored = 0;

    for (const auto &file : recursive_directory_iterator(directory)) {
        bool skip = false;

        if (igList.size() != 0) {
            for (string ig : igList) {
                // testa se há alguma substring que bate com a lista de ignore em path
                if ((int)(static_cast<string>(file.path()).find(ig)) !=
                    -1) {  // find retorna -1 caso não encontre a substring
                    skip = true;
                }
            }
            // caso este caminho esteja na lista de ignore, não adiciona ele a lista
            // de arquivos
            if (skip) {
                ignored++;
                continue;
            }
        }

        // Testa se o caminho na lista pertence a um arquivo
        if (filesystem::is_regular_file(file) == true) {  // ou seja: ignora pastas
            // cout << file.path() << endl;
            arquivos.insert(arquivos.end(), file.path());
            loaded++;
        }
    }
    cout << arquivos.size() << " file names retrieved from \"" << directory
         << "\". " << ignored << " ignored." << endl;
    return arquivos;
}

bool Accio::LoadFromFile(string path) {
    if (path.length() <= 0) {
        Invalid_File e{"", "Empty file name!"};
        throw(e);
    }

    if (exists(path) == false) {
        Invalid_File e{path, "The file " + path + "doesn't exist!"};
        throw(e);
    }

    fstream file;
    file.open(path);
    string word;
    if (file.is_open() == false) {
        // cout << "Couldn't open " << path << endl;
        return false;
    }
    while (file >> word) {
        word = Normalize(word);
        //  "insert - insere a o caminho "path" na chave "word" repetições
        data[word].insert(path);
    }
    // adiciona o arquivo lido a lista de arquivos se ele já não estiver lá
    if (!allFiles.count(path)) {
        allFiles.insert(path);
    }

    return true;
}

int Accio::LoadAllFiles(set<string> list_of_files) {
    int loaded = 0;
    for (string file : list_of_files) {
        if ((*this).LoadFromFile(file)) {
            loaded++;
        }
    }
    cout << loaded << "/" << list_of_files.size()
         << " files sucessfully loaded from \"" << (*this).directory << "\"."
         << endl;
    return loaded;
}

int Accio::LoadAllFiles() { return (*this).LoadAllFiles((*this).allFiles); }

string CleanString(string h) {
    if (h.empty()) {
        return h;  // string vazia. lança exceção?
    }
    for (int i = 0; i < (int)(h.length()); i++) {
        char c = h[i];

        // Se não é uma letra comum (não acentuada) é apagado.
        if (!((c >= 65 && c <= 90) || (c >= 97 && c <= 122))) {
            h.erase(h.begin() + i);
            i--;
        }
    }
    return h;
}

// atualmente não é capaz de lidar com palavras acentudas
string FlatString(string h) {
    if (h.length() == 0) {
        return h;
    }
    string s = "";

    string reference = "ÄÅÁÂÀÃäáâàãÉÊËÈéêëèÍÎÏÌíîïìÖÓÔÒÕöóôòõÜÚÛüúûùÇç";
    string replace = "AAAAAAaaaaaEEEEeeeeIIIIiiiiOOOOOoooooUUUuuuuCc";
    for (int i = 0; i < (int)h.length(); i++) {
        for (int j = 0; j < (int)reference.length(); j++) {
            if ((char)h[i] == (char)reference[j]) {
                s = s + replace[j];
                break;
            } else {
                s += h[i];
                break;
            }
        }
    }
    return s;
}

string LeveledString(string h) {
    for (auto i = h.begin(); i != h.end(); i++) {
        *i = ((int)*i >= 65 && (int)*i <= 90) ? *i += 32 : *i;
    }
    return h;
}

string Normalize(string h) {
    h = FlatString(h);
    h = CleanString(h);
    h = LeveledString(h);
    return h;
}

set<string> Accio::getNormalizedQuery() {
    set<string> tokens;
    string query;
    do {
        tokens.clear();

        string query;
        cout << "Insira string a ser pesquisada:" << endl;
        getline(cin, query);

        // constrói um stream de string a partir da string query
        stringstream tempStream(query);
        string tempString;
        while (getline(tempStream, tempString, ' ')) {
            tempString = Normalize(tempString);
            if (!tempString.empty())
                tokens.insert(tempString);
        }

    } while (tokens.size() == 0);
    return tokens;
}

set<string> Accio::getNormalizedQuery(string h) {
    stringstream tempStream(h);
    string tempstring;
    set<string> tokens;
    while (getline(tempStream, tempstring, ' ')) {
        tempstring = Normalize(tempstring);
        if (!tempstring.empty())
            tokens.insert(tempstring);
    }
    return tokens;
}

// multiplicador de string
string operator*(string str, int n) {
    if (n < 0) {
        string reverse = "";
        for (int i = str.length() - 1; i >= 0; i--) {
            reverse += str[i];
        }
        str = reverse;
        n = -n;
    }

    if (n == 0) {
        return "";
    } else if (n == 1) {
        return str;
    } else {
        string repeat = str;
        for (int i = 2; i <= n; i++)
            str += repeat;

        return str;
    }
}