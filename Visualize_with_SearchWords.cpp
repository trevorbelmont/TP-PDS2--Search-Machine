
// REQUESITO: compilar com C++ atualizado (C++ 17 ou mais recente)
//   adicione  -std=c++17 na linha de compilação

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <vector>

using namespace std;

//Função que seria usada quando passada para o utils.cpp e o utils.h
//Comentei aqui porque ela não estava funcionando devido ao jeito que escrevi um arquivo curtinho para testar.
/*
void Accio::VisualizeData()
{
    for(auto it = data.begin(); it != data.end(); it++){
        cout << "Archive: " << it->first << endl;
        cout << "Words inside it: " << endl;
        for (auto ht = it->second.begin(); ht != it->second.end(); ht++){
            cout << *ht << endl;
        }
        cout << endl;
    }
}
*/

/* 
Essa segunda função é referente a busca do arquivo através de palavras
É o que o prof ta pedindo, koroi
OBS: Muito provavelmente não será exatamente essa a função a ser implementada, porque a gente precisa saber EXATAMENTE como o sabe-tudo
do professor vai fazer a merda da busca
Mas pelo menos é algo para começar, fácil de mudar depois
e da para testar se os nossos outros Métodos de Accio estão dando certo
OBS 2: A FUNÇÃO NÃO TA ROBUSTA. SE NÃO COLOCAR PREVIAMENTE O NÚMERO DE PALAVRAS, DA PAU 
*/
/*
Void Accio:SearchAndPrint(int how_many)

  int how_many_words = how many;
  vector<string> words_to_find;
  vector<int> counter;
  int did_it_work = 0;
  
  ESSA LINHA NÃO TEM NESSA VERSÃO COMENTADA ::::::: cout << "Please insert how many words would you like to search: " << endl;
  cin >> how_many_words;
  words_to_find.resize(how_many_words);
  counter.resize(how_many_words);
  
  cout << "Now please insert word per word: " << endl;
  for(int i = 0; i < how_many_words; ++i){
    cin >> words_to_find[i];
  }

  for(auto it = data.begin(); it != data.end(); it++)
  {
    did_it_work = 0;
    
    for(int i = 0; i < how_many_words; ++i)
    {
      counter[i] = 0;

      if(it->second.find(words_to_find[i]) != it->second.end())
      {
        counter[i] += 1;
      }
    }

    for(int i = 0; i < how_many_words; ++i)
    {
      if(counter[i] == 1){
        did_it_work += 1;
      }
    }

    if(did_it_work == how_many_words)
    {
      cout << "Search found in Archive: " << it->first << endl;
    }
                 
  }
*/


int main() {
    map<string, set<string>> data;

    set<string> arch_1 = {"house", "dog", "blue", "sky", "i_hate_university", "day"};
    set<string> arch_2 = {"eating", "shit", "every", "single", "day"};


    data.insert(pair<string,set<string>>("Archive_One", arch_1));
    data.insert(pair<string,set<string>>("Archive_Two", arch_2));

    for(auto it = data.begin(); it != data.end(); it++){
        cout << "Archive: " << it->first << endl;
        cout << "Words inside it: " << endl;
        for (auto ht = it->second.begin(); ht != it->second.end(); ht++){
            cout << *ht << endl;
        }
        cout << endl;
    }



  //Daqui para baixo irei escrever código de procurar igual o tp pede

  int how_many_words = 0;
  vector<string> words_to_find;
  vector<int> counter;
  int did_it_work = 0;
  
  cout << "Please insert how many words would you like to search: " << endl;
  cin >> how_many_words;
  words_to_find.resize(how_many_words);
  counter.resize(how_many_words);
  
  cout << "Now please insert word per word: " << endl;
  for(int i = 0; i < how_many_words; ++i){
    cin >> words_to_find[i];
  }

  for(auto it = data.begin(); it != data.end(); it++)
  {
    did_it_work = 0;
    
    for(int i = 0; i < how_many_words; ++i)
    {
      counter[i] = 0;

      if(it->second.find(words_to_find[i]) != it->second.end())
      {
        counter[i] += 1;
      }
    }

    for(int i = 0; i < how_many_words; ++i)
    {
      if(counter[i] == 1){
        did_it_work += 1;
      }
    }

    if(did_it_work == how_many_words)
    {
      cout << "Search found in Archive: " << it->first << endl;
    }
                 
  }

}

