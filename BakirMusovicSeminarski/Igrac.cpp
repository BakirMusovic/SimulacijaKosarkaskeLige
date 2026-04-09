#include "Igrac.h"
#include <iostream>
using namespace std;

/*
 Podrazumijevani konstruktor koji se poziva kada se pravi objekat bez argumenata.
 Poziva konstruktor bazne klase Osoba() bez parametara i postavlja sve atribute
 na njihove podrazumijevane (default) vrijednosti.
*/
Igrac::Igrac() : Osoba(), brojDresa(0), pozicija(""), brojPoena(0),
    brojOdigranihUtakmica(0), jacinaNapada(0), defanzivniRating(0) {
}

/*
 Parametrizirani konstruktor koji se poziva kada se pravi objekat sa proslijeđenim argumentima.
 Poziva konstruktor bazne klase Osoba(ime, prezime, godine) i inicijalizuje atribute
 objekta sa zadanim vrijednostima. Atributi brojPoena i brojOdigranihUtakmica
 se postavljaju na pocetne (default) vrijednosti.
*/
Igrac::Igrac(string ime, string prezime, int godine, int brojDresa, string pozicija,
             int jacinaNapada, int defanzivniRating)
    : Osoba(ime, prezime, godine),
      brojDresa(brojDresa),
      pozicija(pozicija),
      brojPoena(0),
      brojOdigranihUtakmica(0),
      jacinaNapada(jacinaNapada),
      defanzivniRating(defanzivniRating) {
}

int Igrac::getBrojDresa() const {
    return brojDresa;
}

string Igrac::getPozicija() const {
    return pozicija;
}

int Igrac::getBrojPoena() const {
    return brojPoena;
}

int Igrac::getBrojOdigranihUtakmica() const {
    return brojOdigranihUtakmica;
}

int Igrac::getJacinaNapada() const {
    return jacinaNapada;
}

int Igrac::getDefanzivniRating() const {
    return defanzivniRating;
}

/*
 Koristi se static_cast<double> kako bi se izbjeglo cjelobrojno dijeljenje
 i dobio tacan decimalni rezultat.
*/
double Igrac::getProsjekPoena() const {
    if (brojOdigranihUtakmica == 0) return 0.0;
    return static_cast<double>(brojPoena) / brojOdigranihUtakmica;
}

void Igrac::setBrojDresa(int brojDresa) {
    this->brojDresa = brojDresa;
}

void Igrac::setPozicija(string pozicija) {
    this->pozicija = pozicija;
}

void Igrac::setJacinaNapada(int jacinaNapada) {
    this->jacinaNapada = jacinaNapada;
}

void Igrac::setDefanzivniRating(int defanzivniRating) {
    this->defanzivniRating = defanzivniRating;
}

void Igrac::setBrojPoena(int brojPoena) {
    this->brojPoena = brojPoena;
}

void Igrac::setBrojOdigranihUtakmica(int brojOdigranihUtakmica) {
    this->brojOdigranihUtakmica = brojOdigranihUtakmica;
}

void Igrac::dodajPoene(int poeni) {
    brojPoena += poeni;
}

void Igrac::povecajBrojUtakmica() {
    brojOdigranihUtakmica++;
}

void Igrac::prikaziPodatke() const {
    cout << "Igrac: " << ime << " " << prezime
         << " | Godine: " << godine
         << " | Dres: " << brojDresa
         << " | Pozicija: " << pozicija
         << " | Poeni: " << brojPoena
         << " | Utakmice: " << brojOdigranihUtakmica
         << " | Napad: " << jacinaNapada
         << " | Odbrana: " << defanzivniRating
         << endl;
}