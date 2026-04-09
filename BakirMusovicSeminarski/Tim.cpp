#include "Tim.h"
#include <iostream>
using namespace std;

/*
 Podrazumijevani konstruktor klase Tim.
 Poziva se prilikom kreiranja objekta bez argumenata i inicijalizuje
 sve atribute na pocetne vrijednosti, dok se pokazivac na trenera
 postavlja na nullptr.
*/
Tim::Tim() : naziv(""), grad(""), trener(nullptr),
    brojPobjeda(0), brojPoraza(0), datiPoeni(0), primljeniPoeni(0) {
}

/*
 Parametrizirani konstruktor klase Tim.
 Poziva se prilikom kreiranja objekta sa proslijedjenim nazivom i gradom,
 dok se ostali atributi inicijalizuju na pocetne vrijednosti,
 a pokazivac na trenera postavlja na nullptr.
*/
Tim::Tim(string naziv, string grad) : naziv(naziv), grad(grad), trener(nullptr),
    brojPobjeda(0), brojPoraza(0), datiPoeni(0), primljeniPoeni(0) {
}

/*
 Kopirni konstruktor klase Tim.
 Kreira novi objekat kao kopiju postojeceg objekta.
 Svi osnovni atributi i lista igraca se kopiraju,
 dok se trener kopira dubokom kopijom (deep copy) kako bi svaki objekat
 imao vlastiti primjerak trenera.
*/
Tim::Tim(const Tim& other) {
    naziv = other.naziv;
    grad = other.grad;
    brojPobjeda = other.brojPobjeda;
    brojPoraza = other.brojPoraza;
    datiPoeni = other.datiPoeni;
    primljeniPoeni = other.primljeniPoeni;
    igraci = other.igraci;

    if (other.trener != nullptr) {
        trener = new Trener(*other.trener);
    } else {
        trener = nullptr;
    }
}

/*
 Operator dodjele koji omogucava kopiranje jednog objekta u drugi.
 Prvo se oslobadja postojeci trener kako bi se izbjeglo curenje memorije,
 zatim se kopiraju svi atributi i igraci.
 Trener se ponovo kreira dubokom kopijom ako postoji.
*/
Tim& Tim::operator=(const Tim& other) {
    if (this != &other) {
        delete trener;

        naziv = other.naziv;
        grad = other.grad;
        brojPobjeda = other.brojPobjeda;
        brojPoraza = other.brojPoraza;
        datiPoeni = other.datiPoeni;
        primljeniPoeni = other.primljeniPoeni;
        igraci = other.igraci;

        if (other.trener != nullptr) {
            trener = new Trener(*other.trener);
        } else {
            trener = nullptr;
        }
    }

    return *this;
}

Tim::~Tim() {
    obrisiTrenera();
}

string Tim::getNaziv() const {
    return naziv;
}

string Tim::getGrad() const {
    return grad;
}

Trener* Tim::getTrener() const {
    return trener;
}

vector<Igrac>& Tim::getIgraci() {
    return igraci;
}

const vector<Igrac>& Tim::getIgraci() const {
    return igraci;
}

int Tim::getBrojPobjeda() const {
    return brojPobjeda;
}

int Tim::getBrojPoraza() const {
    return brojPoraza;
}

int Tim::getDatiPoeni() const {
    return datiPoeni;
}

int Tim::getPrimljeniPoeni() const {
    return primljeniPoeni;
}

int Tim::getKosRazliku() const {
    return datiPoeni - primljeniPoeni;
}

/*
 Setter funkcija za postavljanje trenera timu.
 Ako tim vec ima trenera, prethodni objekat se brise kako bi se
 izbjeglo curenje memorije.
 Nakon toga se postavlja novi trener (pokazivac).
*/
void Tim::setTrener(Trener* noviTrener) {
    if (trener != nullptr) {
        delete trener;
    }
    trener = noviTrener;
}

void Tim::dodajIgraca(const Igrac& igrac) {
    igraci.push_back(igrac);
}

void Tim::setNaziv(string naziv) {
    this->naziv = naziv;
}

void Tim::setGrad(string grad) {
    this->grad = grad;
}

void Tim::setBrojPobjeda(int brojPobjeda) {
    this->brojPobjeda = brojPobjeda;
}

void Tim::setBrojPoraza(int brojPoraza) {
    this->brojPoraza = brojPoraza;
}

void Tim::setDatiPoeni(int datiPoeni) {
    this->datiPoeni = datiPoeni;
}

void Tim::setPrimljeniPoeni(int primljeniPoeni) {
    this->primljeniPoeni = primljeniPoeni;
}

void Tim::dodajPobjedu() {
    brojPobjeda++;
    if (trener != nullptr) {
        trener->dodajPobjedu();
    }
}

void Tim::dodajPoraz() {
    brojPoraza++;
}

void Tim::dodajDatePoene(int poeni) {
    datiPoeni += poeni;
}

void Tim::dodajPrimljenePoene(int poeni) {
    primljeniPoeni += poeni;
}

int Tim::getUkupnaJacinaNapada() const {
    int suma = 0;
    for (const auto& igrac : igraci) {
        suma += igrac.getJacinaNapada();
    }
    return suma;
}

int Tim::getUkupniDefanzivniRating() const {
    int suma = 0;
    for (const auto& igrac : igraci) {
        suma += igrac.getDefanzivniRating();
    }
    return suma;
}

int Tim::getTrenerRating() const {
    if (trener != nullptr) {
        return trener->getTrenerRating();
    }
    return 0;
}

/*
 Funkcija za prikaz osnovnih podataka o timu.
 Ispisuje naziv i grad tima, zatim podatke o treneru ukoliko postoji,
 a u suprotnom ispisuje odgovarajucu poruku.
 Nakon toga se prikazuje statistika tima (pobjede, porazi,
 dati i primljeni poeni).
*/
void Tim::prikaziTim() const {
    cout << "Tim: " << naziv << " (" << grad << ")" << endl;

    if (trener != nullptr) {
        trener->prikaziPodatke();
    } else {
        cout << "Nema trenera" << endl;
    }

    cout << "Pobjede: " << brojPobjeda
         << " | Porazi: " << brojPoraza
         << " | Dati poeni: " << datiPoeni
         << " | Primljeni poeni: " << primljeniPoeni
         << endl;
}

/*
 Funkcija za prikaz svih igraca u timu.
 Ukoliko tim nema igraca, ispisuje se odgovarajuca poruka.
 U suprotnom, prolazi se kroz sve igrace i poziva se metoda
 za prikaz njihovih podataka.
*/
void Tim::prikaziIgrace() const {
    if (igraci.empty()) {
        cout << "Nema igraca u timu." << endl;
        return;
    }

    for (const auto& igrac : igraci) {
        igrac.prikaziPodatke();
    }
}

/*
 Funkcija za brisanje trenera iz tima.
 Ako trener postoji, oslobadja se dinamicka memorija i
 pokazivac se postavlja na nullptr kako bi se izbjegle greske
 pri daljem koristenju.
*/
void Tim::obrisiTrenera() {
    if (trener != nullptr) {
        delete trener;
        trener = nullptr;
    }
}