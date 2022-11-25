#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "Accio.h"

#include <iostream>
#include <string>

#include "doctest.h"

int nArquivos = 4;
string folder = "Documentos_Teste";

TEST_SUITE("Construtores") {
    TEST_CASE("Testa construtor em pasta") {
        Accio t(folder);  // cria buscador na pasta de teste

        CHECK(t.RootFolder() == folder);  // checa se o buscador foi criado na pasta

        CHECK(t.FileList().size() == nArquivos);  // checa se listou todos os arquivos

        CHECK(t.ReleaseIgnored() == false);  // checa se lista de ignore estava vazia
    }
    TEST_CASE("Testa construtores vazios ") {
        Accio nul;  // cria buscador vazio
        Accio alsoNull(false);

        CHECK(nul.RootFolder() == "");  // checa se não há diretório
        CHECK(alsoNull.RootFolder() == "");

        CHECK(nul.FileList().size() == 0);  // checa se listou nenhum arquvios
        CHECK(alsoNull.FileList().size() == 0);
    }

    TEST_CASE("Testa construtor auto-inicializado") {  // indiretamente testa ignoreDefault()
        Accio t(true);
        CHECK(t.RootFolder() == "./");  // checa se o buscador foi criado na raíz

        CHECK(t.FileList().size() != 0);  // checa se listou todos os arquivos

        CHECK(t.RemoveIgnore(".pdf") == true);  // checa se estava ignorando uma das strings padrão
        CHECK(t.ClearIgnore() > 0);             // checa se havia outras strings ignoradas por padrão
        CHECK(t.ClearIgnore() == 0);            // checa se a lista de ignore foi de fato limpa
    }
}

TEST_SUITE("Funções de Inicialização") {
    TEST_CASE("Testa funcao SetDirectory") {
        Accio t("./");

        CHECK_FALSE(t.RootFolder() == folder);
        // CHECK(t.SetDirectory("_-_Abracadabra_-_") == false);
        CHECK(t.SetDirectory(folder) == true);

        CHECK(t.RootFolder() == folder);
    }

    TEST_CASE("Testa função GetFiles(directory)") {
        Accio nul;

        REQUIRE(nul.FileList().size() == 0);

        nul.GetFiles("./");
        CHECK(nul.FileList().size() > 0);
    }

    TEST_CASE("Testa funcao FileList()") {
        Accio t(folder);

        CHECK(t.FileList().size() == nArquivos);

        t.AddIgnore(".pdf");
        t.ReleaseIgnored();
        CHECK(t.FileList().size() == nArquivos - 1);
    }

    // a função LoadAllFiles(directory) é implementada usando a função LoadFile(path)
    // portanto este test case testa indiretamente ambas as funções
    TEST_CASE("Testa função LoadFiles(directory)") {
        Accio nul;

        nul.ReleaseData();
        REQUIRE(nul.FileList().size() == 0);
        REQUIRE_FALSE(nul.Search("é tudo a mesma coisa") > 0);

        REQUIRE(nul.SetDirectory(folder));
        nul.GetFiles(folder);

        REQUIRE(nul.FileList().size() > 0);
        int nFiles = nul.FileList().size();

        CHECK(nul.LoadAllFiles(nul.FileList()) == nFiles);
        CHECK(nul.Search("tudo") > 0);
    }

    TEST_CASE("Testa Funções de normalizar string") {
        std::string raw = "?Isso eRa % Pr@ $£R um@ sTriNG ZOADA!";

        std::string normalized = Normalize(raw);
        CHECK(normalized == "issoeraprrumstringzoada");

        CHECK(Normalize("fLaTtEn!") == "flatten");
    }
}
TEST_SUITE("Funcionalidades de Busca") {
    TEST_CASE("getNormalizedQuery(string)") {
        std::string uma = "PalavraS";
        std::string outra = "AO";
        std::string vida = "Vento!";

        std::string query = uma + " " + outra + " " + vida;

        REQUIRE(query == "PalavraS AO Vento!");

        Accio nul;

        CHECK(nul.getNormalizedQuery(query).size() == 3);
        CHECK(nul.getNormalizedQuery(query).count("vento") == 1);
        // CHECK(nul.getNormalizedQuery().count("vento") == 1);
    }

    TEST_CASE("Testa Buscas") {
        Accio t(folder);

        CHECK_FALSE(t.Search("não tem isso") > 0);
        CHECK(t.Search("so tem isso") > 0);

        std::string isso_ate_tem = "eating every shit";

        CHECK(t.Search(t.getNormalizedQuery(isso_ate_tem)) > 0);

        // CHECK(t.Search() > 0);
    }
}

TEST_SUITE("Testa ignore features") {
    TEST_CASE("Testa AddIgnore(string)") {
        Accio nul;

        nul.SetDirectory(folder);
        nul.GetFiles();
        REQUIRE(nul.FileList().find(".pdf") != nul.FileList().end());

        nul.ReleaseData();  // limpa a data carregada

        Accio alsoNull;
        nul = alsoNull;  // reseta totalmente null

        CHECK(nul.AddIgnore(".pdf"));

        nul.SetDirectory(folder);
        nul.GetFiles();
        CHECK_FALSE(nul.FileList().find(".pdf") == nul.FileList().end());
    }

    // testa removeIgnore(string) e indiretamente testa ignoreDefault(), que é usada no construtor autoInicializado;
    TEST_CASE("removeIgnore(string)") {  // indiretamente testa a função reconsider(string)

        Accio auto_(true);  // por padrão ignora arquivos .pdf

        bool ignorou = true;
        for (string h : auto_.FileList()) {
            if (h.find(".pdf") != -1) {
                ignorou = false;
                break;
            }
        }
        CHECK(ignorou);

        CHECK(auto_.RemoveIgnore(".pdf"));

        auto_.GetFiles();

        ignorou = true;
        for (string h : auto_.FileList()) {
            if (h.find(".pdf") != -1) {
                ignorou = false;
                break;
            }
        }
        CHECK(ignorou == false);
    }

    TEST_CASE("clearIgnore()") {
        Accio auto_(true);

        auto_.AddIgnore("ignore");
        auto_.AddIgnore(".pdf");
        auto_.GetFiles();

        bool ignorou = true;
        for (string h : auto_.FileList()) {
            if (h.find(".pdf") != -1) {
                ignorou = false;
                break;
            }
        }
        REQUIRE(ignorou);
        REQUIRE_FALSE(auto_.AddIgnore("ignore"));

        CHECK(auto_.ClearIgnore());

        auto_.GetFiles();

        ignorou = true;
        for (string h : auto_.FileList()) {
            if (h.find(".pdf") != -1) {
                ignorou = false;
                break;
            }
        }
        CHECK(ignorou == false);
        CHECK_FALSE(auto_.RemoveIgnore("ignore"));
    }

    TEST_CASE("Testa ReleaseIgnored") {
        Accio t(folder);

        bool ignorou = true;
        for (string h : t.FileList()) {  // testa se deixou de carregar o arquivo com extensão .pdf
            if (h.find(".pdf") != -1) {
                ignorou = false;
                break;
            }
        }
        REQUIRE_FALSE(ignorou);  // o arquivo .pdf foi carregado

        t.AddIgnore(".pdf");
        CHECK(t.ReleaseIgnored() > 0);

        ignorou = true;
        for (string h : t.FileList()) {  // testa se deixou de carregar o arquivo com extensão .pdf
            if (h.find(".pdf") != -1) {
                ignorou = false;
                break;
            }
        }
        CHECK(ignorou);
    }
}

TEST_CASE("Testa ReleaseData()") {
    Accio t(folder);
    REQUIRE(t.Search("tem") > 0);

    t.ReleaseData();
    CHECK_FALSE(t.Search("tem") > 0);
}