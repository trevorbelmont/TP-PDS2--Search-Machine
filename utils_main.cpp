#include <locale.h>

#include <filesystem>
#include <iostream>
#include <string>

#include "utils.h"

using namespace std;

int main() {
    string query;
    do {
        cout << "Insira string a ser limpada:" << endl;
        cin >> query;

        query = Normalize(query);

        cout << query << endl;

    } while (query.length() > 0);
}
