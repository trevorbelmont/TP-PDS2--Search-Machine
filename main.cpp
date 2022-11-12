// REQUESITO: compilar com C++ atualizado (C++ 17 ou mais recente)
//   adicione  -std=c++17 na linha de compilação

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "utils.h"

using namespace std;

int main() {
    ifstream file;

    file.open(RetriveFilePaths("/mnt/")[0], fstream::in);

    string line;
    file >> line;

    string query;
    do {
        cout << "Insira string a ser limpada:" << endl;
        cin >> query;

        query = Normalize(query);

        cout << query << endl;

    } while (query.length() > 1);

    cout << "--------> " << line;
}
