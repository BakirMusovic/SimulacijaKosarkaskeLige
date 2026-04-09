#include "TimFunkcije.h"
#include "Utils.h"
#include "Trener.h"
#include "Igrac.h"
#include <iostream>

using namespace std;

/*
 Funkcija omogucava unos i dodavanje novog tima.
 Prije dodavanja provjerava se da li tim vec postoji u listi,
 pri cemu se poredi naziv i grad bez obzira na velika i mala slova.
 Ukoliko tim ne postoji, dodaje se u vektor timova.
*/
void dodajTim(vector<Tim>& timovi) {
    string naziv, grad;

    cout << "Unesite naziv tima: ";
    getline(cin >> ws, naziv);

    cout << "Unesite grad: ";
    getline(cin >> ws, grad);

    for (const auto& t : timovi) {
        if (toLower(t.getNaziv()) == toLower(naziv) &&
            toLower(t.getGrad()) == toLower(grad)) {
            cout << "Tim vec postoji!" << endl;
            return;
        }
    }

    Tim noviTim(naziv, grad);
    timovi.push_back(noviTim);
    cout << "Tim dodat." << endl;
}


void prikaziTimove(const vector<Tim>& timovi) {
    if (timovi.empty()) {
        cout << "Nema timova." << endl;
        return;
    }

    for (int i = 0; i < timovi.size(); i++) {
        cout << i + 1 << ". ";
        timovi[i].prikaziTim();
        cout << endl;
    }
}

/*
 Funkcija za prikaz igraca odabranog tima.
 Ukoliko nema unesenih timova, ispisuje se odgovarajuca poruka.
 Prvo se prikazuje lista svih timova sa rednim brojevima,
 nakon cega korisnik bira tim unosom odgovarajuceg broja.
 Na osnovu izbora, prikazuju se svi igraci iz odabranog tima.
*/
void prikaziIgraceTima(const vector<Tim>& timovi) {
    if (timovi.empty()) {
        cout << "Nema unesenih timova." << endl;
        return;
    }

    cout << "\n===== TIMOVI =====" << endl;
    for (int i = 0; i < timovi.size(); i++) {
        cout << i + 1 << ". " << timovi[i].getNaziv()
             << " (" << timovi[i].getGrad() << ")" << endl;
    }

    cout << "Odaberite redni broj tima: ";
    int izbor = unosBrojaOpseg(1, timovi.size());

    cout << "\n===== IGRACI TIMA =====" << endl;
    timovi[izbor - 1].prikaziIgrace();
}

/*
 Funkcija omogucava dodavanje trenera timu.
 Nakon izbora tima i provjere da li vec postoji trener,
 unose se podaci o treneru i dinamicki se kreira novi objekat
 koji se dodjeljuje timu putem pokazivaca.
*/
void dodajTrenera(vector<Tim>& timovi) {
    if (timovi.empty()) {
        cout << "Dodaj prvo tim!" << endl;
        return;
    }

    prikaziTimove(timovi);

    cout << "Izaberi tim: ";
    int i = unosBrojaOpseg(1, timovi.size()) - 1;

    if (timovi[i].getTrener() != nullptr) {
        cout << "Tim vec ima trenera!" << endl;
        return;
    }

    string ime, prezime;
    int godine, iskustvo, rating;

    cout << "Ime: ";
    getline(cin >> ws, ime);

    cout << "Prezime: ";
    getline(cin >> ws, prezime);

    cout << "Godine: ";
    godine = unosBroja();

    cout << "Iskustvo: ";
    iskustvo = unosBroja();

    cout << "Rating: ";
    rating = unosBroja();

    timovi[i].setTrener(new Trener(ime, prezime, godine, iskustvo, rating));

    cout << "Trener dodat." << endl;
}

/*
 Funkcija za dodavanje igraca u odabrani tim.
 Ukoliko nema timova, ispisuje se odgovarajuca poruka.
 Prvo se prikazuje lista timova i korisnik bira tim.
 Zatim se unose podaci o igracu (ime, prezime, godine,
 broj dresa, pozicija, napad i odbrana).
 Prije dodavanja vrsi se provjera da li igrac vec postoji u timu
 (po imenu i prezimenu ili broju dresa).
 Ukoliko igrac ne postoji, dodaje se u tim.
*/
void dodajIgraca(vector<Tim>& timovi) {
    if (timovi.empty()) {
        cout << "Dodaj prvo tim!" << endl;
        return;
    }

    prikaziTimove(timovi);

    cout << "Izaberi tim: ";
    int i = unosBrojaOpseg(1, timovi.size()) - 1;

    string ime, prezime, pozicija;
    int godine, dres, napad, odbrana;

    cout << "Ime: ";
    getline(cin >> ws, ime);

    cout << "Prezime: ";
    getline(cin >> ws, prezime);

    cout << "Godine: ";
    godine = unosBroja();

    cout << "Dres: ";
    dres = unosBroja();

    cout << "Pozicija: ";
    getline(cin >> ws, pozicija);

    cout << "Napad: ";
    napad = unosBroja();

    cout << "Odbrana: ";
    odbrana = unosBroja();

    for (const auto& igrac : timovi[i].getIgraci()) {
        if ((toLower(igrac.getIme()) == toLower(ime) &&
             toLower(igrac.getPrezime()) == toLower(prezime)) ||
            igrac.getBrojDresa() == dres) {
            cout << "Igrac vec postoji (ime/prezime ili broj dresa)!" << endl;
            return;
        }
    }

    timovi[i].dodajIgraca(Igrac(ime, prezime, godine, dres, pozicija, napad, odbrana));
    cout << "Igrac dodat." << endl;
}

/*
 Funkcija prikazuje statistiku svih igraca u ligi.
 Za svaki tim prolazi kroz listu igraca i ispisuje njihove podatke
 zajedno sa statistikom.
*/
void prikaziStatistikuIgraca(const vector<Tim>& timovi) {
    if (timovi.empty()) {
        cout << "Nema timova u ligi." << endl;
        return;
    }

    bool imaIgraca = false;

    cout << "\n===== STATISTIKA IGRACA =====" << endl;

    for (const auto& tim : timovi) {
        if (!tim.getIgraci().empty()) {
            imaIgraca = true;
        }

        for (const auto& igrac : tim.getIgraci()) {
            cout << igrac.getIme() << " " << igrac.getPrezime()
                 << " | Tim: " << tim.getNaziv()
                 << " | Poeni: " << igrac.getBrojPoena()
                 << " | Utakmice: " << igrac.getBrojOdigranihUtakmica()
                 << " | Prosjek: " << igrac.getProsjekPoena()
                 << endl;
        }
    }

    if (!imaIgraca) {
        cout << "Nema igraca u ligi." << endl;
    }
}

/*
 Funkcija pronalazi igraca sa najvecim brojem postignutih poena u ligi.
 Iterira kroz sve timove i igrace, te pamti igraca sa najboljim rezultatom.
 Na kraju se ispisuju podaci o najboljem strijelcu zajedno sa pripadajucim timom.
*/
void prikaziTopStrijelca(const vector<Tim>& timovi) {
    if (timovi.empty()) {
        return;
    }

    const Igrac* topIgrac = nullptr;
    string nazivTima;

    for (const auto& tim : timovi) {
        for (const auto& igrac : tim.getIgraci()) {
            if (topIgrac == nullptr || igrac.getBrojPoena() > topIgrac->getBrojPoena()) {
                topIgrac = &igrac;
                nazivTima = tim.getNaziv();
            }
        }
    }

    if (topIgrac == nullptr) {
        return;
    }

    cout << "\n===== NAJBOLJI STRIJELAC =====" << endl;
    cout << topIgrac->getIme() << " " << topIgrac->getPrezime()
         << " | Tim: " << nazivTima
         << " | Poeni: " << topIgrac->getBrojPoena()
         << " | Utakmice: " << topIgrac->getBrojOdigranihUtakmica()
         << " | Prosjek: " << topIgrac->getProsjekPoena()
         << endl;
}

/*
 Funkcija za brisanje igraca iz odabranog tima.
 Ukoliko nema timova, ispisuje se odgovarajuca poruka.
 Prvo se prikazuje lista timova, nakon cega korisnik bira tim.
 Zatim se prikazuju igraci tog tima i korisnik bira igraca za brisanje.
 Prije brisanja trazi se potvrda od korisnika.
 Ako je potvrda pozitivna, igrac se uklanja iz vektora igraca.
*/
void obrisiIgracaIzTima(vector<Tim>& timovi) {
    if (timovi.empty()) {
        cout << "Nema unesenih timova." << endl;
        return;
    }

    cout << "\n===== TIMOVI =====" << endl;
    for (int i = 0; i < timovi.size(); i++) {
        cout << i + 1 << ". " << timovi[i].getNaziv()
             << " (" << timovi[i].getGrad() << ")" << endl;
    }

    cout << "Odaberite redni broj tima: ";
    int izborTima = unosBrojaOpseg(1, timovi.size()) - 1;

    vector<Igrac>& igraci = timovi[izborTima].getIgraci();

    if (igraci.empty()) {
        cout << "Tim nema igraca." << endl;
        return;
    }

    cout << "\n===== IGRACI TIMA =====" << endl;
    for (int i = 0; i < igraci.size(); i++) {
        cout << i + 1 << ". "
             << igraci[i].getIme() << " "
             << igraci[i].getPrezime()
             << " | Dres: " << igraci[i].getBrojDresa()
             << " | Pozicija: " << igraci[i].getPozicija()
             << endl;
    }

    cout << "Odaberite redni broj igraca za brisanje: ";
    int izborIgraca = unosBrojaOpseg(1, igraci.size()) - 1;

    cout << "Da li ste sigurni da zelite obrisati igraca "
         << igraci[izborIgraca].getIme() << " "
         << igraci[izborIgraca].getPrezime()
         << "? (1 = DA, 0 = NE): ";

    int potvrda = unosBroja();

    if (potvrda == 1) {
        igraci.erase(igraci.begin() + izborIgraca);
        cout << "Igrac je uspjesno obrisan iz tima." << endl;
    } else {
        cout << "Brisanje otkazano." << endl;
    }
}

/*
 Funkcija za brisanje trenera iz odabranog tima.
 Ukoliko nema timova ili tim nema trenera, ispisuje se odgovarajuca poruka.
 Nakon izbora tima, prikazuju se podaci o treneru i trazi se potvrda
 od korisnika za brisanje.
 Ako je potvrda pozitivna, trener se brise pozivom odgovarajuce metode.
*/
void obrisiTreneraIzTima(vector<Tim>& timovi) {
    if (timovi.empty()) {
        cout << "Nema timova." << endl;
        return;
    }

    cout << "\n===== TIMOVI =====" << endl;
    for (int i = 0; i < timovi.size(); i++) {
        cout << i + 1 << ". " << timovi[i].getNaziv()
             << " (" << timovi[i].getGrad() << ")" << endl;
    }

    cout << "Odaberite tim: ";
    int izbor = unosBrojaOpseg(1, timovi.size()) - 1;

    if (timovi[izbor].getTrener() == nullptr) {
        cout << "Ovaj tim nema trenera." << endl;
        return;
    }

    cout << "Da li zelite obrisati trenera "
         << timovi[izbor].getTrener()->getIme() << " "
         << timovi[izbor].getTrener()->getPrezime()
         << "? (1 = DA, 0 = NE): ";

    int potvrda = unosBroja();

    if (potvrda == 1) {
        timovi[izbor].obrisiTrenera();
        cout << "Trener je obrisan." << endl;
    } else {
        cout << "Brisanje otkazano." << endl;
    }
}