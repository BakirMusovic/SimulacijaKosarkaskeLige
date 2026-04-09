#pragma once
#include <string>
using namespace std;

class Utakmica {
private:
    string domaciTim;
    string gostujuciTim;
    int poeniDomaci;
    int poeniGost;
    string datum;

public:
    Utakmica();
    Utakmica(string domaciTim, string gostujuciTim, int poeniDomaci, int poeniGost, string datum);

    string getDomaciTim() const;
    string getGostujuciTim() const;
    int getPoeniDomaci() const;
    int getPoeniGost() const;
    string getDatum() const;

    void prikaziUtakmicu() const;
};