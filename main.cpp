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
    //-------- Exemplo de Motores genéricos (uso avançado) ---------//

    Accio nul;               // cria motor de busca cru (vazio e não inicializado)
    Accio otherNull(false);  // tb cria motor de busca vazio e não inicializado
    Accio generico(true);    // cria motor de busca inicializado na raiz com ignore padrão

    // inicializa e e carrega os arquivos do motor não inicializado
    nul.SetDirectory("./");
    nul.GetFiles(nul.RootFolder());
    nul.LoadAllFiles();

    //------ EXEMPLO DE IGNORAR DEPOIS DE JÁ CARREGADO -----//

    Accio s("documentos");  // cria um motor de busca na pasta do programa sem ignorar nadA  E CARREGA OS ARQUIVOS

    s.IgnoreDefault();  // adiciona as strings padrão pra lista de ignore (pasta .vscode e .git)

    s.AddIgnore(".cpp");  // adiciona algumas strings a lista de ignore
    s.AddIgnore(".h");    // nesse caso ignorando todos os arquivos de c.
    s.AddIgnore(".pdf");

    s.ReleaseIgnored();
    // int unload = s.ReleaseIgnored();
    //  s.NormalizeData();

    //------- EXEMPLO DE BUSCA (FUNÇÕES TEMPORÁRIAS) -------//

    while (1 > 0) {
        cout << nul.Search() << " files found." << endl;
    }
}
