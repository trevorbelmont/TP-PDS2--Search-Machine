
#include "utils.h"

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
    NormalizeData();
}

// um Accio Motor de Busca não inicializado
Accio::Accio() {
}

Accio::Accio(int auto_initialize) {
    if (auto_initialize > 0) {
        IgnoreDefault();  // auto add .git e .vscode to ignore paths

        directory = "./";

        GetFiles(directory);

        LoadAllFiles(allFiles);
        NormalizeData();
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
            cout << "Insert a valid directory path or press Enter to search the current folder: ";
            string cmd;
            getline(cin, cmd);

            directory = (cmd.length() == 0) ? "./" : cmd;
            if (exists(directory)) {  // && filesystem::is_directory(directory)) {
                (this)->GetFiles(directory);
                // allFiles = RetrieveFilePaths(directory, ignoreList);
            }
        }

    } while (!exists(directory));  // repete enquanto não encontrar um diretório válido
}

void Accio::NormalizeData() {
    for (auto it = (*this).data.begin(); it != (*this).data.end(); it++) {
        set<string> normalized;
        for (auto st = it->second.begin(); st != it->second.end(); st++) {
            normalized.insert(Normalize(*st));
        }
        it->second = normalized;
    }
}
bool Accio::AddIgnore(string h) {
    return (*this).ignoreList.insert(h).second;  // retorna se uma NOVA string foi adicionada ou não.
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

    for (auto it = (*this).data.begin(); it != (*this).data.end();) {
        bool entryRemoved = false;
        for (string s : (*this).ignoreList) {
            if (it->first.find(s) != -1) {  // se alguma substring bate com uma das strings na ignoreList
                (*this).allFiles.erase(it->first);
                it = (*this).data.erase(it);  // apaga a entrada it e assinala next a próxima entrada válida
                entryRemoved = true;
                ignored++;
                break;
            }
        }
        if (entryRemoved == false) {
            it++;
        }
    }
    return ignored;
}

void Accio::ReleaseData() {
    this->data.clear();
    this->allFiles.clear();
}

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

bool Accio::Reconsider(string h) {
    return (*this).RemoveIgnore(h);
}

string Accio::RootFolder() {
    return (*this).directory;
}

set<string> Accio::FileList() {
    return (*this).allFiles;
}

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

    for (const auto& file : recursive_directory_iterator(directory)) {
        bool skip = false;

        if (igList.size() != 0) {
            for (string ig : igList) {
                // testa se há alguma substring que bate com a lista de ignore em path
                if (static_cast<string>(file.path()).find(ig) != -1) {  // find retorna -1 caso não encontre a substring
                    skip = true;
                }
            }
            // caso este caminho esteja na lista de ignore, não adiciona ele a lista de arquivos
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
    cout << arquivos.size() << " file names retrieved from \"" << directory << "\". " << ignored << " ignored." << endl;
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
        // "insert - insere a palavra com chave "path" sem repetições
        data[path].insert(word);
    }

    // adiciona o arquivo lido a lista de arquivos
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
    cout << loaded << "/" << list_of_files.size() << " files sucessfully loaded from \"" << (*this).directory << "\"." << endl;
    return loaded;
}

string CleanString(string h) {
    if (h.empty()) {
        return h;  // string vazia. lança exceção?
    }
    for (int i = 0; i < h.length(); i++) {
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
    for (int i = 0; i < h.length(); i++) {
        for (int j = 0; j < reference.length(); j++) {
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