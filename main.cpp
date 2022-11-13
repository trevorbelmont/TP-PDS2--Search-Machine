// REQUESITO: compilar com C++ atualizado (C++ 17 ou mais recente)
//   adicione  -std=c++17 na linha de compilação

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "utils.h"

using namespace std;

int main() {
    string query;
    Accio s;

    do {
        cout << "Insira string a ser limpada:" << endl;
        cin >> query;

        query = Normalize(query);

        cout << query << endl;

    } while (query.length() > 1);
}
