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

  Accio s("documentos"); // cria um motor de busca na pasta do programa sem
                         // ignorar nadA  E CARREGA OS ARQUIVOS
  cout << endl;
  
  cout << "Esse é um programa que busca arquivos de texto na pasta documentos." << endl
        << "Em seguida, é possível buscar palavras presentes nesses arquivos e o programa retornara em quais arquivos estão" << endl;
  
  int continuar;
  while (true) {
    cout << "Deseja continuar procurando? Digite 1 se sim e digite 0 se quiser parar" << endl;
    cin >> continuar;
    if(continuar == 0){
      break;
    }
    if(continuar == 1){
    cout << s.Search() << " files found." << endl;
    }
    if(continuar != 1 && continuar != 0){
      cout << "Valor invalido. Por favor, digite um valor valido (0 ou 1)" << endl;
    }
  }
}
