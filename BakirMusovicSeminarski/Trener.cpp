#include "Trener.h"
#include <iostream>
using namespace std;

/*
 Podrazumijevani konstruktor klase Trener.
 Poziva konstruktor bazne klase Osoba() bez parametara i inicijalizuje
 sve atribute na pocetne (default) vrijednosti.
*/
Trener::Trener() : Osoba(), godineIskustva(0), brojPobjeda(0), trenerRating(0) {}

/*
 Parametrizirani konstruktor klase Trener.
 Poziva konstruktor bazne klase Osoba sa proslijedjenim podacima
 (ime, prezime i godine), te inicijalizuje ostale atribute.
 Atribut godineIskustva i trenerRating se postavljaju na zadane vrijednosti,
 dok se broj pobjeda inicijalno postavlja na 0.
*/
Trener::Trener(string ime, string prezime, int godine,
               int godineIskustva, int trenerRating)
    : Osoba(ime, prezime, godine),
      godineIskustva(godineIskustva),
      brojPobjeda(0),
      trenerRating(trenerRating) {
}

int Trener::getGodineIskustva() const {
    return godineIskustva;
}

int Trener::getBrojPobjeda() const {
    return brojPobjeda;
}

int Trener::getTrenerRating() const {
    return trenerRating;
}

void Trener::setGodineIskustva(int godineIskustva) {
    this->godineIskustva = godineIskustva;
}

void Trener::setTrenerRating(int trenerRating) {
    this->trenerRating = trenerRating;
}

void Trener::dodajPobjedu() {
    brojPobjeda++;
}

void Trener::prikaziPodatke() const {
    cout << "Trener: " << ime << " " << prezime
         << " | Godine: " << godine
         << " | Iskustvo: " << godineIskustva
         << " | Pobjede: " << brojPobjeda
         << " | Rating: " << trenerRating
         << endl;
}