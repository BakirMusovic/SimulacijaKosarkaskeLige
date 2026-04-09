#pragma once
#include <string>
#include <vector>
#include "Igrac.h"
#include "Trener.h"

using namespace std;

class Tim {
private:
    string naziv;
    string grad;
    Trener* trener;
    vector<Igrac> igraci;

    int brojPobjeda;
    int brojPoraza;
    int datiPoeni;
    int primljeniPoeni;

public:
    Tim();
    Tim(string naziv, string grad);

    Tim(const Tim& other);
    Tim& operator=(const Tim& other);

    ~Tim();

    string getNaziv() const;
    string getGrad() const;
    Trener* getTrener() const;
    vector<Igrac>& getIgraci();
    const vector<Igrac>& getIgraci() const;

    int getBrojPobjeda() const;
    int getBrojPoraza() const;
    int getDatiPoeni() const;
    int getPrimljeniPoeni() const;
    int getKosRazliku() const;

    void setTrener(Trener* trener);
    void dodajIgraca(const Igrac& igrac);
    void setNaziv(string naziv);
    void setGrad(string grad);
    void setBrojPobjeda(int brojPobjeda);
    void setBrojPoraza(int brojPoraza);
    void setDatiPoeni(int datiPoeni);
    void setPrimljeniPoeni(int primljeniPoeni);

    void dodajPobjedu();
    void dodajPoraz();
    void dodajDatePoene(int poeni);
    void dodajPrimljenePoene(int poeni);

    int getUkupnaJacinaNapada() const;
    int getUkupniDefanzivniRating() const;
    int getTrenerRating() const;

    void prikaziTim() const;
    void prikaziIgrace() const;

    void obrisiTrenera();
};