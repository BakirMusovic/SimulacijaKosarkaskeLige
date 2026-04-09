#pragma once
#include "Osoba.h"
#include <string>
using namespace std;

class Igrac : public Osoba {
private:
    int brojDresa;
    string pozicija;
    int brojPoena;
    int brojOdigranihUtakmica;
    int jacinaNapada;
    int defanzivniRating;

public:
    Igrac();
    Igrac(string ime, string prezime, int godine, int brojDresa, string pozicija,
          int jacinaNapada, int defanzivniRating);

    int getBrojDresa() const;
    string getPozicija() const;
    int getBrojPoena() const;
    int getBrojOdigranihUtakmica() const;
    int getJacinaNapada() const;
    int getDefanzivniRating() const;
    double getProsjekPoena() const;

    void setBrojDresa(int brojDresa);
    void setPozicija(string pozicija);
    void setJacinaNapada(int jacinaNapada);
    void setDefanzivniRating(int defanzivniRating);
    void setBrojPoena(int brojPoena);
    void setBrojOdigranihUtakmica(int brojOdigranihUtakmica);

    void dodajPoene(int poeni);
    void povecajBrojUtakmica();

    void prikaziPodatke() const override;
};