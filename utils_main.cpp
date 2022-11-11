#include <locale.h>

#include <filesystem>
#include <iostream>
#include <string>

#include "utils.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Portuguese");
    string myString;

    do {
        cout << "Insira string a ser limpada:" << endl;
        cin >> myString;

        myString = Normalize(myString);

        cout << myString << endl;

    } while (myString.length() > 0);
}
