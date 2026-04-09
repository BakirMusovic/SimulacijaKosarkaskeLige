#pragma once
#include <vector>
#include <string>
#include "Tim.h"
#include "Utakmica.h"

using namespace std;

struct ParUtakmice {
    int domaci;
    int gost;
    bool odigrano;

    ParUtakmice(int domaci = -1, int gost = -1, bool odigrano = false)
        : domaci(domaci), gost(gost), odigrano(odigrano) {
    }
};

class Liga {
private:
    vector<Tim> timovi;
    vector<Utakmica> utakmice;
    vector<vector<ParUtakmice>> raspored;
    int trenutnoKolo;
    bool rasporedGenerisan;

    bool timValidanZaIgru(int indeks) const;
    void simulirajJednuUtakmicuPoIndeksima(int domaci, int gost);

public:
    Liga();

    vector<Tim>& getTimovi();
    vector<Utakmica>& getUtakmice();
    const vector<vector<ParUtakmice>>& getRaspored() const;

    int getTrenutnoKolo() const;
    bool getRasporedGenerisan() const;

    vector<vector<ParUtakmice>>& getRasporedMutable();
    void setTrenutnoKolo(int trenutnoKolo);
    void setRasporedGenerisan(bool rasporedGenerisan);

    void resetujLigu();

    bool mozeGenerisatiRaspored() const;
    void generisiRasporedDoubleRoundRobin();
    void prikaziRaspored() const;
    void simulirajNarednoKolo();
    void simulirajUtakmicuIzTrenutnogKola();

    void dodajTim(const Tim& tim);
};