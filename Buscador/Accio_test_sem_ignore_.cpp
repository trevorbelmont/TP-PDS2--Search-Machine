#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "Accio.h"
#include "doctest.h"
#include <string>

// Accio(string folder);

TEST_CASE("Testa construtor") {
  Accio t("Documentos_Teste"); // cria buscador na pasta de teste

  CHECK(t.RootFolder() == "Documentos_Teste"); // checa se o buscador foi criado na pasta

  CHECK(t.FileList().size() == 3); // checa se carregou todos os arquivos
}

TEST_CASE("Testa funcao RootFolder") {
  Accio t("Documentos_Teste");
  CHECK(t.RootFolder() == "Documentos_Teste");
}

TEST_CASE("Testa funcao SetDirectory") {
  Accio t("./");
  CHECK(t.SetDirectory("Abracadabra") == false);
  CHECK(t.SetDirectory("Documentos_Teste") == true);

  t.SetDirectory("Documentos_Teste");
  CHECK(t.RootFolder() == "Documentos_Teste");
}

// set<string> Accio::FileList() { return (*this).allFiles; }
// set<string> allFiles;
TEST_CASE("Testa funcao FileList") {
  Accio t("Documentos_Teste");
  CHECK(t.FileList().size() == 3);
}

TEST_CASE("Testa funcao GetFiles"){
  Accio t("Documentos_Teste");
  CHECK_NOTHROWS(t.GetFiles("Documentos_Teste"));
  CHECK_THROWS(t.GetFiles("PastaNaoExistente"));
}

TEST_CASE("Testa funcao LoadFromFile"){
  CHECK_THROWS(Accio("Documentos_Teste").LoadFromFile("ArquivoInexistente"));
  CHECK(Accio("Documentos_Teste").LoadFromFile("chama_assim") == true);
}

TEST_CASE("Testa funcao LoadAllFiles"){
  //Como nessa versão não tem construtor vazio, testei dessa forma
  CHECK(Accio("Documentos_Teste").LoadAllFiles("Documentos_Teste") == 3);
}

TEST_CASE("Testa a funcao Search"){
  Accio t("Documentos_Teste");
  CHECK(t.serach("tem") == 1);
}

TEST_CASE("Testa funcao CleanString"){
  string teste = "abra#cada3bra";
  CHECK(CleanString(teste) == "abracadabra");
}

TEST_CASE("Testa funcao FlatString"){
  string teste = "maceió";
  CHECK(FlatString(teste) == "maeio");
}

TEST_CASE("Testa funcao LeveledString"){
  string teste = "ABRACADABRA";
  CHECK(LeveledString(teste) == "abracadabra");
}

TEST_CASE("Testa funcao Normalize"){
  string teste = "ABRAC#AdABRá";
  CHECK(Normalized(teste) == "abracadabra");
}







  
