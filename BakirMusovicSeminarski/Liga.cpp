#include "Liga.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <limits>

using namespace std;
/*
 Ovo je podrazumijevani konstruktor klase Liga jer ne prima parametre i 
 služi za inicijalizaciju objekta na početne vrijednosti.
*/
Liga::Liga() : trenutnoKolo(0), rasporedGenerisan(false) {
}

vector<Tim>& Liga::getTimovi() {
    return timovi;
}

vector<Utakmica>& Liga::getUtakmice() {
    return utakmice;
}
/*
 Nemutabilni (const) getter koji vraca konstantnu referencu na raspored.
 Omogucava samo pregled podataka bez mogucnosti izmjene.
*/
const vector<vector<ParUtakmice>>& Liga::getRaspored() const {
    return raspored;
}

int Liga::getTrenutnoKolo() const {
    return trenutnoKolo;
}

bool Liga::getRasporedGenerisan() const {
    return rasporedGenerisan;
}

void Liga::dodajTim(const Tim& tim) {
    timovi.push_back(tim);
}

/*
 Mutabilni getter koji vraca referencu na raspored.
 Omogucava citanje i direktnu izmjenu rasporeda bez pravljenja kopije.
*/
vector<vector<ParUtakmice>>& Liga::getRasporedMutable() {
    return raspored;
}

void Liga::setTrenutnoKolo(int trenutnoKolo) {
    this->trenutnoKolo = trenutnoKolo;
}

void Liga::setRasporedGenerisan(bool rasporedGenerisan) {
    this->rasporedGenerisan = rasporedGenerisan;
}

/*
 Funkcija resetujLigu sluzi za vracanje lige na pocetno stanje.
 Brise raspored utakmica, resetuje trenutno kolo i oznaku da li je raspored generisan,
 te uklanja sve odigrane utakmice.

 Nakon toga prolazi kroz sve timove i postavlja njihove statistike
 (pobjede, porazi, dati i primljeni poeni) na pocetne vrijednosti.

 Takodjer za svakog igraca u timu resetuje statistiku,
 odnosno broj poena i broj odigranih utakmica.
*/
void Liga::resetujLigu() {
    raspored.clear();
    trenutnoKolo = 0;
    rasporedGenerisan = false;
    utakmice.clear();

    for (auto& tim : timovi) {
        tim.setBrojPobjeda(0);
        tim.setBrojPoraza(0);
        tim.setDatiPoeni(0);
        tim.setPrimljeniPoeni(0);

        for (auto& igrac : tim.getIgraci()) {
            igrac.setBrojPoena(0);
            igrac.setBrojOdigranihUtakmica(0);
        }
    }
}

/*
 Funkcija koja provjerava da li dati tim zadvoljava uslove za igru(najmanje 5 igraca i trener)
*/
bool Liga::timValidanZaIgru(int indeks) const {
    if (indeks < 0 || indeks >= timovi.size()) return false;

    const Tim& tim = timovi[indeks];

    if (tim.getTrener() == nullptr) return false;
    if (tim.getIgraci().size() < 5) return false;

    return true;
}

/*
 Funkcija koja provjerava da li je moguce generisati raspored
 Provjerava da li je broj timova paran, i da li ih ima vise od 2.
 Takoder provjerava da li su svi timovi validni za igru
*/
bool Liga::mozeGenerisatiRaspored() const {
    if (timovi.size() < 2) return false;
    if (timovi.size() % 2 != 0) return false;

    for (int i = 0; i < timovi.size(); i++) {
        if (!timValidanZaIgru(i)) {
            return false;
        }
    }

    return true;
}

void Liga::generisiRasporedDoubleRoundRobin() {
    if (!mozeGenerisatiRaspored()) {
        cout << "Raspored nije moguce generisati." << endl;
        cout << "Provjeri da li:" << endl;
        cout << "- postoji paran broj timova" << endl;
        cout << "- svaki tim ima trenera" << endl;
        cout << "- svaki tim ima najmanje 5 igraca" << endl;
        return;
    }

    /*
     Resetovanje podataka lige na pocetno stanje prije generisanja novog rasporeda.
     Brise se prethodni raspored, resetuje trenutno kolo i oznaka da je raspored generisan,
     te se uklanjaju prethodno odigrane utakmice.
    */
    raspored.clear();
    trenutnoKolo = 0;
    rasporedGenerisan = false;
    utakmice.clear();

    vector<int> indeksi;
    for (int i = 0; i < timovi.size(); i++) {
        indeksi.push_back(i);
    }

    /*
     Izracunavanje pomocnih vrijednosti potrebnih za generisanje prvog dijela
     round-robin rasporeda: broj timova, broj kola i broj utakmica po kolu.
    */
    int brojTimova = indeksi.size();
    int brojKolaJedanDio = brojTimova - 1;
    int utakmicaPoKolu = brojTimova / 2;

    /*
     Generisanje parova za prvi dio round-robin sistema.
     U svakom kolu formiraju se parovi timova na osnovu trenutnog rasporeda indeksa,
     nakon cega se indeksi rotiraju kako bi se dobila nova kombinacija parova
     za naredno kolo.
    */
    for (int kolo = 0; kolo < brojKolaJedanDio; kolo++) {
        vector<ParUtakmice> jednoKolo;

        for (int i = 0; i < utakmicaPoKolu; i++) {
            int domaci = indeksi[i];
            int gost = indeksi[brojTimova - 1 - i];

            if (kolo % 2 == 1 && i == 0) {
                swap(domaci, gost);
            }

            jednoKolo.push_back(ParUtakmice(domaci, gost, false));
        }

        raspored.push_back(jednoKolo);

        vector<int> novi = indeksi;
        for (int i = 1; i < brojTimova; i++) {
            novi[i] = indeksi[i - 1];
        }
        novi[1] = indeksi[brojTimova - 1];
        novi[0] = indeksi[0];
        indeksi = novi;
    }

    /*
     Generisanje drugog dijela round-robin rasporeda tako sto se za svaki par
     iz prvog dijela zamjenjuju uloge domaceg i gostujuceg tima.
    */
    int velicinaPrvogDijela = raspored.size();
    for (int i = 0; i < velicinaPrvogDijela; i++) {
        vector<ParUtakmice> drugoKolo;

        for (const auto& par : raspored[i]) {
            drugoKolo.push_back(ParUtakmice(par.gost, par.domaci, false));
        }

        raspored.push_back(drugoKolo);
    }

    rasporedGenerisan = true;

    cout << "Double round robin raspored je uspjesno generisan." << endl;
    cout << "Ukupno kola: " << raspored.size() << endl;
}

/*
 Funkcija za prikaz rasporeda lige po kolima.
 Ukoliko raspored nije generisan ili je prazan, ispisuje se odgovarajuca poruka.

 Prolazi se kroz sva kola i za svako kolo se ispisuje njegov redni broj.
 Trenutno kolo se posebno oznacava kao naredno, dok se prethodna kola
 oznacavaju kao odigrana.

 Za svako kolo prikazuju se parovi timova (domaci i gostujuci tim),
 te se dodatno oznacava ako je utakmica vec odigrana.
*/
void Liga::prikaziRaspored() const {
    if (!rasporedGenerisan || raspored.empty()) {
        cout << "Raspored jos nije generisan." << endl;
        return;
    }

    cout << "\n===== RASPORED LIGE =====" << endl;

    for (int i = 0; i < raspored.size(); i++) {
        cout << "\nKolo " << i + 1;

        if (i < trenutnoKolo) {
            cout << " [ODIGRANO]";
        } else if (i == trenutnoKolo) {
            cout << " [NAREDNO]";
        }

        cout << endl;

        for (const auto& par : raspored[i]) {
            cout << "- " << timovi[par.domaci].getNaziv()
                 << " vs "
                 << timovi[par.gost].getNaziv();

            if (par.odigrano) {
                cout << " [odigrano]";
            }

            cout << endl;
        }
    }
}

void Liga::simulirajJednuUtakmicuPoIndeksima(int domaci, int gost) {
    /*
     Na osnovu proslijedjenih indeksa uzimaju se domaci i gostujuci tim.
     Zatim se racunaju osnovni parametri potrebni za simulaciju utakmice:
     jacina napada, odbrane i trenerov rating za oba tima.
    */
    Tim& A = timovi[domaci];
    Tim& B = timovi[gost];

    int napadA = A.getUkupnaJacinaNapada();
    int odbranaA = A.getUkupniDefanzivniRating();
    int trenerA = A.getTrenerRating();

    int napadB = B.getUkupnaJacinaNapada();
    int odbranaB = B.getUkupniDefanzivniRating();
    int trenerB = B.getTrenerRating();

    /*
     Racunanje rezultata za oba tima na osnovu napada, odbrane,
     trenera i slucajnog faktora (rand).
    */
    int scoreA = 40 + (napadA / A.getIgraci().size()) + (trenerA / 2) - (odbranaB / (A.getIgraci().size()-2)) + rand() % 50;
    int scoreB = 40 + (napadB / B.getIgraci().size()) + (trenerB / 2) - (odbranaA / (B.getIgraci().size()-2)) + rand() % 50;

    if (scoreA < 0) scoreA = 0;
    if (scoreB < 0) scoreB = 0;


    /*
     Ako je rezultat nerijesen, simulira se produzetak
     dok se ne dobije pobjednik.
    */
    while (scoreA == scoreB) {
        cout << "Rezultat je nerijesen. Igra se produzetak" << endl;
        int dodatakA = ((napadA / A.getIgraci().size()) + (trenerA / 2) - (odbranaB / (A.getIgraci().size()-2)) / 8) + rand() % 12;
        int dodatakB = ((napadB / B.getIgraci().size()) + (trenerB / 2) - (odbranaA / (B.getIgraci().size()-2)) / 8) + rand() % 12;

        if (dodatakA < 1) dodatakA = 1;
        if (dodatakB < 1) dodatakB = 1;

        scoreA += dodatakA;
        scoreB += dodatakB;
    }

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
     Poeni se raspodjeljuju igracima proporcionalno njihovoj jacini napada.
     Takodjer se svakom igracu povecava broj odigranih utakmica.
     Provjerava se da ukupna jacina napada nije nula kako bi se izbjegla greska.
    */
    int sumaNapadA = A.getUkupnaJacinaNapada();
    if (sumaNapadA > 0) {
        for (auto& igrac : A.getIgraci()) {
            int poeni = (igrac.getJacinaNapada() * scoreA) / sumaNapadA;
            igrac.dodajPoene(poeni);
            igrac.povecajBrojUtakmica();
        }
    }

    int sumaNapadB = B.getUkupnaJacinaNapada();
    if (sumaNapadB > 0) {
        for (auto& igrac : B.getIgraci()) {
            int poeni = (igrac.getJacinaNapada() * scoreB) / sumaNapadB;
            igrac.dodajPoene(poeni);
            igrac.povecajBrojUtakmica();
        }
    }

    /*
     Kreira se zapis o utakmici i dodaje u listu utakmica.
     Datum se postavlja kao trenutno kolo.
    */
    string datum = "Kolo " + to_string(trenutnoKolo + 1);

    utakmice.push_back(Utakmica(
        A.getNaziv(),
        B.getNaziv(),
        scoreA,
        scoreB,
        datum
    ));

    cout << A.getNaziv() << " " << scoreA
         << " : "
         << scoreB << " " << B.getNaziv() << endl;
}

/*
 Funkcija za simulaciju narednog kola lige.
 Ukoliko raspored nije generisan ili je vec odigrano sve,
 ispisuje se odgovarajuca poruka.
 Za trenutno kolo prolazi se kroz sve parove timova i
 simuliraju se utakmice koje jos nisu odigrane.
 Nakon simulacije, utakmice se oznacavaju kao odigrane,
 te se prelazi na naredno kolo.
*/
void Liga::simulirajNarednoKolo() {
    if (!rasporedGenerisan || raspored.empty()) {
        cout << "Raspored nije generisan." << endl;
        return;
    }

    if (trenutnoKolo >= raspored.size()) {
        cout << "Sva kola su vec odigrana." << endl;
        return;
    }

    cout << "\n===== SIMULACIJA KOLA " << trenutnoKolo + 1 << " =====" << endl;

    for (auto& par : raspored[trenutnoKolo]) {
        if (!par.odigrano) {
            simulirajJednuUtakmicuPoIndeksima(par.domaci, par.gost);
            par.odigrano = true;
        }
    }

    trenutnoKolo++;
    cout << "Kolo je uspjesno odigrano." << endl;
}

void Liga::simulirajUtakmicuIzTrenutnogKola() {
    /*
     Provjerava se da li je raspored generisan i da li postoje utakmice.
     Takodjer se provjerava da li su sva kola vec odigrana.
    */
    if (!rasporedGenerisan || raspored.empty()) {
        cout << "Raspored nije generisan." << endl;
        return;
    }

    if (trenutnoKolo >= raspored.size()) {
        cout << "Sva kola su vec odigrana." << endl;
        return;
    }

    /*
      Formira se lista neodigranih utakmica u trenutnom kolu.
      Prolazi se kroz sve parove timova i provjerava da li je utakmica odigrana.
      Ukoliko nije odigrana, njen indeks se dodaje u listu neodigranih utakmica,
      te se istovremeno ispisuje par timova sa rednim brojem za odabir.
      Na ovaj nacin korisniku se prikazuju samo utakmice koje jos nisu odigrane.
    */
    vector<int> neodigraneUtakmice;

    cout << "\n===== Kolo " << trenutnoKolo + 1 << " =====" << endl;

    for (int i = 0; i < raspored[trenutnoKolo].size(); i++) {
        const auto& par = raspored[trenutnoKolo][i];

        if (!par.odigrano) {
            neodigraneUtakmice.push_back(i);

            cout << neodigraneUtakmice.size() << ". "
                 << timovi[par.domaci].getNaziv()
                 << " vs "
                 << timovi[par.gost].getNaziv()
                 << endl;
        }
    }

    if (neodigraneUtakmice.empty()) {
        cout << "Sve utakmice ovog kola su vec odigrane." << endl;
        trenutnoKolo++;
        return;
    }

    /*
     Korisnik bira utakmicu za simulaciju.
     Vrsi se provjera ispravnosti unosa kako bi se izbjegle greske.
    */
    cout << "Odaberite utakmicu za simulaciju: ";
    int izbor;
    cin >> izbor;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); /* Cisti ulazni buffer do kraja linije kako bi se izbjegle greske pri unosu.*/
        cout << "Pogresan unos." << endl;
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (izbor < 1 || izbor > neodigraneUtakmice.size()) {
        cout << "Nevazeci izbor." << endl;
        return;
    }

    /*
     Na osnovu izbora uzima se odgovarajuci par timova
     i vrsi se simulacija utakmice.
     Nakon toga se utakmica oznacava kao odigrana.
    */
    int indeksPara = neodigraneUtakmice[izbor - 1];
    auto& par = raspored[trenutnoKolo][indeksPara];

    simulirajJednuUtakmicuPoIndeksima(par.domaci, par.gost);
    par.odigrano = true;

    /*
     Provjerava se da li su sve utakmice trenutnog kola odigrane.
     Ukoliko jesu, ispisuje se poruka i prelazi se na naredno kolo.
    */
    bool sveOdigrane = true;
    for (const auto& p : raspored[trenutnoKolo]) {
        if (!p.odigrano) {
            sveOdigrane = false;
            break;
        }
    }

    if (sveOdigrane) {
        cout << "Sve utakmice kola " << trenutnoKolo + 1 << " su odigrane." << endl;
        trenutnoKolo++;
    }
}