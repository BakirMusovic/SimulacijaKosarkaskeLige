#include "Utakmica.h"
#include <iostream>
using namespace std;

/*
 Podrazumijevani konstruktor klase Utakmica.
 Poziva se prilikom kreiranja objekta bez argumenata i inicijalizuje
 sve atribute na pocetne (default) vrijednosti.
*/
Utakmica::Utakmica() : domaciTim(""), gostujuciTim(""), poeniDomaci(0), poeniGost(0), datum("") {
}

/*
 Parametrizirani konstruktor klase Utakmica.
 Poziva se prilikom kreiranja objekta sa proslijedjenim podacima
 i inicijalizuje sve atribute (nazive timova, rezultat i datum).
*/
Utakmica::Utakmica(string domaciTim, string gostujuciTim, int poeniDomaci, int poeniGost, string datum)
    : domaciTim(domaciTim), gostujuciTim(gostujuciTim), poeniDomaci(poeniDomaci), poeniGost(poeniGost), datum(datum) {
}

string Utakmica::getDomaciTim() const {
    return domaciTim;
}

string Utakmica::getGostujuciTim() const {
    return gostujuciTim;
}

int Utakmica::getPoeniDomaci() const {
    return poeniDomaci;
}

int Utakmica::getPoeniGost() const {
    return poeniGost;
}

string Utakmica::getDatum() const {
    return datum;
}

/*
 Funkcija za prikaz podataka o utakmici.
 Ispisuje naziv domaceg i gostujuceg tima, rezultat utakmice
 te datum odigravanja.
*/
void Utakmica::prikaziUtakmicu() const {
    cout << domaciTim << " " << poeniDomaci
         << " : " << poeniGost << " " << gostujuciTim
         << " | Datum: " << datum << endl;
}