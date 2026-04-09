#include "Osoba.h"

/*
 Podrazumijevani konstruktor klase Osoba.
 Poziva se prilikom kreiranja objekta bez proslijedjenih argumenata
 i inicijalizuje sve atribute na pocetne (default) vrijednosti.
*/
Osoba::Osoba() : ime(""), prezime(""), godine(0) {}

/*
 Parametrizirani konstruktor klase Osoba.
 Poziva se prilikom kreiranja objekta sa proslijedjenim podacima
 i inicijalizuje atribute ime, prezime i godine sa zadanim vrijednostima.
*/
Osoba::Osoba(string ime, string prezime, int godine)
    : ime(ime), prezime(prezime), godine(godine) {
}

/*
 Parametrizirani konstruktor klase Osoba.
 Poziva se prilikom kreiranja objekta sa proslijedjenim podacima
 i inicijalizuje atribute ime, prezime i godine sa zadanim vrijednostima.
*/
Osoba::~Osoba() {}

string Osoba::getIme() const {
    return ime;
}

string Osoba::getPrezime() const {
    return prezime;
}

int Osoba::getGodine() const {
    return godine;
}

void Osoba::setIme(string ime) {
    this->ime = ime;
}

void Osoba::setPrezime(string prezime) {
    this->prezime = prezime;
}

void Osoba::setGodine(int godine) {
    this->godine = godine;
}