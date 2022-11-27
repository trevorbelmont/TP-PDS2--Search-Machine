Este trabalho foi feito em dupla pelos alunos Felipe Francisco Ferreira de Lima e Marcos Antônio Dias. Optamos por cda um de nós submeter o mesmo trabalho em seu usuário no moodle por que a tarefa aparece para nós dois. Então, por via das dúvidas...

O código foi desenvolvido e testado nos sistemas operacionais Debian 10 x86-64 e Ubunto 20.04 x86-64.
Os compiladores utilizados foram fundamentalmente o GCC 10.3 e o Clang 12.0 - sempre utilizando C++20. Para compilar os códigos é necessário utilizar C++17 ou superior.

Os comandos do makefile são:

make run        : Compila e linka o código do buscador (se necessário) e executa a aplicação
make            : Compila o executável do buscador (Buscador.exe)
make run_test   : Compila o código dos Testes de Unidade (se necessário) e executa todos os Testes
make testado    : Compila os Testes de Unidade (Testes.exe)
make clear      : Remove os executáveis gerados (tanto do Bsucador quanto dos Testes), mantém os objetos compiladores
make clear_all  : Remove tanto os executáveis quanto os objetos já compilados

*Como esperado, nenhum dos comandos make recompilam ou linkam objetos ou executáveis que estejam atualizados.
**As funcionalidades adicionais (como AddIgnore, RemoveIgnore, ReleaseData ReleaseIgnored) não são utilizadas, uma vez que não são necessárias para este trabalho.
Porém todas elas estão implementadas e testadas no arquivo de Testes de Unidades - que pode ser usado como referência de sintaxe para eles. 

