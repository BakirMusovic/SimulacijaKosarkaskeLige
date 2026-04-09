#include "Utils.h"
#include <iostream>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

void initRandom() {
    srand(time(0));
}

/*
 Funkcija za siguran unos cijelog broja.
 Provjerava da li je unos ispravan, te u slucaju greske trazi ponovni unos.
 Takodjer cisti ulazni buffer nakon unosa.
*/
int unosBroja() {
    int broj;
    while (true) {
        cin >> broj;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Pogresan unos! Unesite broj: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return broj;
        }
    }
}

/*
 Funkcija za unos cijelog broja unutar zadatog opsega.
 Provjerava ispravnost unosa i da li se broj nalazi u dozvoljenom rasponu.
 U slucaju greske trazi ponovni unos.
*/
int unosBrojaOpseg(int min, int max) {
    int broj;

    while (true) {
        cin >> broj;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Pogresan unos! Unesite broj: ";
        }
        else if (broj < min || broj > max) {
            cout << "Unesite broj izmedju " << min << " i " << max << ": ";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return broj;
        }
    }
}

/*
 Funkcija koja pretvara sva slova stringa u mala slova.
 Koristi se za poredjenje stringova bez obzira na velika i mala slova.
*/
string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}