// REQUESITO: compilar com C++ atualizado (C++ 17 ou mais recente)
//   adicione  -std=c++17 na linha de compilação

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Accio.h"

using namespace std;

set<string> getNormalizedQuery();

int main() {
    Accio s("documentos");  // cria um motor de busca na pasta do programa sem
                            // ignorar nadA  E CARREGA OS ARQUIVOS
    cout << endl;

    string query;
    do {
        query = "";
        cout << "Digite sua pesquisa ou pressione ENTER para sair:  ";
        getline(cin, query);

        if (query.size() == 0) {
            exit(0);
        }

        cout << s.Search(query) << " files found." << endl;

    } while (query.size() != 0);
}