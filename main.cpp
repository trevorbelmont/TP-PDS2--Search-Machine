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

    //-------- Exemplo de Motor genéricos ---------//

    Accio nul;               // cria motor de busca cru (vazio e não inicializado)
    Accio otherNull(false);  // tb cria moor de busca vazio e não inicializado
    Accio generico(true);    // cria motor de busca inicializado na raiz com ignore padrão

    nul.SetDirectory("./");
    nul.GetFiles(nul.RootFolder());

    //------ EXEMPLO DE IGNORAR DEPOIS DE JÁ CARREGADO -----//

    Accio s("cassss");  // cria um motor de busca na pasta do programa sem ignorar nadA  E CARREGA OS ARQUIVOS

    s.IgnoreDefault();  // adiciona as strings padrão pra lista de ignore (pasta .vscode e .git)

    s.AddIgnore(".cpp");  // adiciona algumas strings a lista de ignore
    s.AddIgnore(".h");    // nesse caso ignorando todos os arquivos de c.

    s.ReleaseIgnored();  // remove do banco de dados todos os arquivos da lista de ignorância.

    do {
        cout << "Insira string a ser limpada ou aperte Enter para sair:" << endl;
        getline(cin, query);

        query = Normalize(query);

        cout << query << endl;

    } while (query.length() > 0);
}
