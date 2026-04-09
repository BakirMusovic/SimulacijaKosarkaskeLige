#include "LigaFunkcije.h"
#include "TimFunkcije.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

void simulirajUtakmicu(vector<Tim>& timovi, vector<Utakmica>& utakmice) {
    if (timovi.size() < 2) {
        cout << "Potrebna su najmanje 2 tima." << endl;
        return;
    }

    int a;
    /*
     Dio za validaciju prvog tima, to jeste da tim mora imati najmanje 5 igraca, i trenera
    */
    while (true) {
        prikaziTimove(timovi);

        cout << "Domaci tim: ";
        a = unosBrojaOpseg(1, timovi.size()) - 1;

        Tim& A = timovi[a];

        if (A.getTrener() == nullptr) {
            cout << "Tim nema trenera! Izaberi ponovo.\n" << endl;
            continue;
        }

        if (A.getIgraci().size() < 5) {
            cout << "Tim nema dovoljno igraca (minimum 5)! Izaberi ponovo.\n" << endl;
            continue;
        }

        break;
    }

    int b;
    /*Dio za validaciju drugog tima, ne moze biti isti tim, te najmanje 5 igraca i trener*/
    while (true) {
        cout << "Gostujuci tim: ";
        b = unosBrojaOpseg(1, timovi.size()) - 1;

        if (a == b) {
            cout << "Ne mozes izabrati isti tim!" << endl;
            continue;
        }

        Tim& B = timovi[b];

        if (B.getTrener() == nullptr) {
            cout << "Tim nema trenera! Izaberi ponovo." << endl;
            continue;
        }

        if (B.getIgraci().size() < 5) {
            cout << "Tim nema dovoljno igraca (minimum 5)! Izaberi ponovo." << endl;
            continue;
        }

        break;
    }
    /*Referenca koja pokazuje izabrane timove*/
    Tim& A = timovi[a];
    Tim& B = timovi[b];
    /*Potrebni podaci za simulaciju*/
    int napadA = A.getUkupnaJacinaNapada();
    int odbranaA = A.getUkupniDefanzivniRating();
    int trenerA = A.getTrenerRating();
    int brojIgracaA = A.getIgraci().size();

    int napadB = B.getUkupnaJacinaNapada();
    int odbranaB = B.getUkupniDefanzivniRating();
    int trenerB = B.getTrenerRating();
    int brojIgracaB = B.getIgraci().size();

    /*Algoritam za simulaciju utakmice*/
    int scoreA = 40 + (napadA / A.getIgraci().size()) + (trenerA / 2) - (odbranaB / (A.getIgraci().size()-2)) + rand() % 50;
    int scoreB = 40 + (napadB / B.getIgraci().size()) + (trenerB / 2) - (odbranaA / (B.getIgraci().size()-2)) + rand() % 50;

    if (scoreA < 0) scoreA = 0;
    if (scoreB < 0) scoreB = 0;

    /*U slucaju da nakon utakmice imamo izjednacen rezultat, simulacija za produžetak*/
    while (scoreA == scoreB) {
        cout << "Rezultat je nerijesen. Idemo u produžetke" << endl;

        int dodatakA = ((napadA / brojIgracaA) + (trenerA / 2) - (odbranaB / brojIgracaA) / 4) + rand() % 10;
        int dodatakB = ((napadB / brojIgracaB) + (trenerB / 2) - (odbranaA / brojIgracaB) / 4) + rand() % 10;

        if (dodatakA < 1) dodatakA = 1;
        if (dodatakB < 1) dodatakB = 1;

        scoreA += dodatakA;
        scoreB += dodatakB;
    }

    cout << "\nREZULTAT: " << endl;
    cout << A.getNaziv() << " " << scoreA << " : " << scoreB << " " << B.getNaziv() << endl;
    /* 
     Ažuriranje rezultata i statistike timova nakon odigrane utakmice
     pomocu metoda klase Tim (pobjede, porazi, dati i primljeni poeni).
    */
    if (scoreA > scoreB) {
        A.dodajPobjedu();
        B.dodajPoraz();
    } else {
        B.dodajPobjedu();
        A.dodajPoraz();
    }

    A.dodajDatePoene(scoreA);
    A.dodajPrimljenePoene(scoreB);

    B.dodajDatePoene(scoreB);
    B.dodajPrimljenePoene(scoreA);

    /*
     Za svaki tim racuna se ukupna jacina napada, nakon cega se poeni
     raspodjeljuju igracima proporcionalno njihovoj jacini napada.
 
     Svakom igracu se dodaje odgovarajuci broj poena i azurira broj
     odigranih utakmica.
    */
    int sumaNapadA = A.getUkupnaJacinaNapada();
    for (auto& igrac : A.getIgraci()) {
        int poeni = (igrac.getJacinaNapada() * scoreA) / sumaNapadA;
        igrac.dodajPoene(poeni);
        igrac.povecajBrojUtakmica();
    }

    int sumaNapadB = B.getUkupnaJacinaNapada();
    for (auto& igrac : B.getIgraci()) {
        int poeni = (igrac.getJacinaNapada() * scoreB) / sumaNapadB;
        igrac.dodajPoene(poeni);
        igrac.povecajBrojUtakmica();
    }

    /*
     Unos datuma odigrane utakmice i spremanje utakmice u listu utakmica.
     Kreira se novi objekat klase Utakmica i dodaje u vektor utakmice
     zajedno sa podacima o timovima, rezultatu i datumu.
    */
    string datum;
    cout << "Unesite datum (npr 07.04.2026): ";
    getline(cin >> ws, datum);

    Utakmica u(A.getNaziv(), B.getNaziv(), scoreA, scoreB, datum);
    utakmice.push_back(u);

    cout << "Utakmica sacuvana." << endl;
}

void prikaziUtakmice(const vector<Utakmica>& utakmice) {
    if (utakmice.empty()) {
        cout << "Nema utakmica." << endl;
        return;
    }

    for (const auto& u : utakmice) {
        u.prikaziUtakmicu();
    }
}

void prikaziTabeluLige(const vector<Tim>& timovi) {
    if (timovi.empty()) {
        cout << "Nema timova u ligi." << endl;
        return;
    }
    /*
     Pravi se kopija vektora timova kako bi se izbjegla promjena originalnog poretka.
     Nakon toga se vrsi sortiranje timova pomocu funkcije sort.
 
     Timovi se sortiraju opadajuce po broju pobjeda, a u slucaju istog broja
     pobjeda koristi se kos razlika kao dodatni kriterij za poredak.
    */
    vector<Tim> sortiraniTimovi = timovi;

    sort(sortiraniTimovi.begin(), sortiraniTimovi.end(), [](const Tim& a, const Tim& b) {
        if (a.getBrojPobjeda() != b.getBrojPobjeda())
            return a.getBrojPobjeda() > b.getBrojPobjeda();

        return a.getKosRazliku() > b.getKosRazliku();
    });
    /*
     Ispis tabele lige na ekran.
     Prikazuje se redni broj (pozicija), naziv tima, broj pobjeda i poraza,
     kao i dati, primljeni poeni i kos razlika.
 
     Timovi se ispisuju u vec sortiranom redoslijedu.
    */
    cout << "\n===== TABELA LIGE =====" << endl;
    cout << "Poz\tTim\tPob\tPor\tDati\tPrimlj\tRazlika" << endl;

    for (int i = 0; i < sortiraniTimovi.size(); i++) {
        cout << i + 1 << "\t"
             << sortiraniTimovi[i].getNaziv() << "\t"
             << sortiraniTimovi[i].getBrojPobjeda() << "\t"
             << sortiraniTimovi[i].getBrojPoraza() << "\t"
             << sortiraniTimovi[i].getDatiPoeni() << "\t"
             << sortiraniTimovi[i].getPrimljeniPoeni() << "\t"
             << sortiraniTimovi[i].getKosRazliku() << endl;
    }
}