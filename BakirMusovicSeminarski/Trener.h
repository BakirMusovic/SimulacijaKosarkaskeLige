#pragma once
#include "Osoba.h"
#include <string>
using namespace std;

class Trener : public Osoba {
private:
    int godineIskustva;
    int brojPobjeda;
    int trenerRating;

public:
    Trener();
    Trener(string ime, string prezime, int godine,
           int godineIskustva, int trenerRating);

    int getGodineIskustva() const;
    int getBrojPobjeda() const;
    int getTrenerRating() const;

    void setGodineIskustva(int godineIskustva);
    void setTrenerRating(int trenerRating);

    void dodajPobjedu();

    void prikaziPodatke() const override;
};