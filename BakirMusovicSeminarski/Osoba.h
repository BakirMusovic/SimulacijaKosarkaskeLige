#pragma once
#include <string>
using namespace std;

class Osoba {
protected:
    string ime;
    string prezime;
    int godine;

public:
    Osoba();
    Osoba(string ime, string prezime, int godine);
    virtual ~Osoba();

    string getIme() const;
    string getPrezime() const;
    int getGodine() const;

    void setIme(string ime);
    void setPrezime(string prezime);
    void setGodine(int godine);

    virtual void prikaziPodatke() const = 0;
};