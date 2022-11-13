
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

Accio::Accio() {
    directory = "documentos";
    do {
        try {
            allFiles = RetriveFilePaths(directory);
        } catch (Invalid_Directory e) {
            cout << e.msg << endl;
            cout << "Insert a valid directory path or press Enter to search the current folder: ";
            string cmd;
            cin >> cmd;
            directory = (cmd.length() == 0) ? "./" : cmd;
        }
    } while (allFiles.size() == 0);
}

Accio::Accio(string folder) {
    directory = folder;
    do {
        try {
            allFiles = RetriveFilePaths(directory);
        } catch (Invalid_Directory e) {
            cout << e.msg << endl;
            cout << "Insert a valid directory path or press Enter to search the current folder: ";
            string cmd;
            getline(cin, cmd);

            directory = (cmd.length() == 0) ? "./" : cmd;
        }
    } while (allFiles.size() == 0);
    (*this).LoadAllFiles(allFiles);
}

string Accio::RootFolder() {
    return (*this).directory;
}

vector<string> Accio::FileList() {
    return (*this).allFiles;
}

vector<string> RetriveFilePaths(string directory) {
    // lança exceção caso nenhum diretório tenha sido especificado
    if (directory.empty()) {
        Accio::Invalid_Directory e{"", "Diretório não especificado!"};
        throw(e);
    }
    // Lança exceção se o diretório não foi encontrado
    if (exists(directory) == false) {
        Accio::Invalid_Directory e{directory};
        e.msg = "O diretório /" + e.directory + "/ não foi encontrado!";
        throw(e);
    }

    vector<string> arquivos;
    int counter = 0;

    for (const auto& file : recursive_directory_iterator(directory)) {
        counter++;
        if (static_cast<string>(file.path()).find("/.vscode/") != -1) {
            continue;
        }
        // Condicional que filtra apenas caminhos com alguma extensão no nome
        if (static_cast<string>(file.path()).find(".") != -1) {  // ou seja: ignora pastas
            // cout << file.path() << endl;
            arquivos.insert(arquivos.end(), file.path());
        }
    }
    cout << arquivos.size() << " file names retrieved from " << directory << endl;
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
        return false;
    }
    while (file >> word) {
        // "insert a chave se ela  já não estiver presente no set
        // [] sobreescreve a chave, caso já tenah sido sa nnoooooooo
        data[path].insert(word);
    }
    return true;
}

int Accio::LoadAllFiles(vector<string> list_of_files) {
    int loaded = 0;
    for (string file : list_of_files) {
        if ((*this).LoadFromFile(file)) {
            loaded++;
        }
    }
    cout << loaded << "/" << list_of_files.size() << " files loaded from " << (*this).directory << endl;
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