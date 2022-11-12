
#include "utils.h"

#include <locale.h>

#include <filesystem>
#include <iostream>
#include <string>

using std::cout;
using std::setlocale;
using std::string;

string CleanString(string h) {
    if (h.empty()) {
        return h;  // string vazia. lança exceção?
    }
    for (int i = 0; i < h.length(); i++) {
        char c = h[i];

        // Se não é uma letra comum (não acentuada) é apagado.
        if (!((c >= 65 && c <= 90) || (c >= 97 && c <= 122))) {
            h.erase(h.begin() + i);
            i--;
        }
    }
    return h;
}

// atualmente não é capaz de lidar com palavras acentudas
string FlatString(string h) {
    setlocale(LC_ALL, "Portuguese");
    if (h.length() == 0) {
        return h;
    }
    string s = "";

    string reference = "ÄÅÁÂÀÃäáâàãÉÊËÈéêëèÍÎÏÌíîïìÖÓÔÒÕöóôòõÜÚÛüúûùÇç";
    string replace = "AAAAAAaaaaaEEEEeeeeIIIIiiiiOOOOOoooooUUUuuuuCc";
    for (int i = 0; i < h.length(); i++) {
        for (int j = 0; j < reference.length(); j++) {
            if ((char)h[i] == (char)reference[j]) {
                s = s + replace[j];
                break;
            } else {
                s += h[i];
                break;
            }
        }
    }
    return s;
}

string LeveledString(string h) {
    for (auto i = h.begin(); i != h.end(); i++) {
        *i = ((int)*i >= 65 && (int)*i <= 90) ? *i += 32 : *i;
    }
    return h;
}

string Normalize(string h) {
    h = FlatString(h);
    h = CleanString(h);
    h = LeveledString(h);
    return h;
}