#include "Datoteke.h"
#include "Trener.h"
#include "Igrac.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;

mutex fajlMutex;
/*
Funkcija spremiPodatkeUFajl sluzi za spremanje svih podataka lige u fajl "liga.txt".

Najprije se otvara izlazni fajl pomocu objekta ofstream. Nakon toga se iz
objekta klase Liga preuzimaju podaci o timovima, utakmicama i rasporedu.

Za svaki tim u fajl se upisuju osnovni podaci o timu, zatim podaci o treneru
ako trener postoji, te svi igraci tog tima sa svojim atributima.

Nakon spremanja timova, upisuju se sve odigrane utakmice sa osnovnim podacima.

Na kraju funkcija upisuje informacije o rasporedu lige, odnosno da li je
raspored generisan, koje je trenutno kolo, te parove utakmica po kolima
zajedno sa informacijom da li je pojedina utakmica odigrana.
*/
void spremiPodatkeUFajl(Liga& liga) {
    ofstream izlaz("liga.txt");

    if (!izlaz) {
        cout << "Greska pri otvaranju fajla za spremanje." << endl;
        return;
    }

    vector<Tim>& timovi = liga.getTimovi();
    vector<Utakmica>& utakmice = liga.getUtakmice();
    const vector<vector<ParUtakmice>>& raspored = liga.getRaspored();

    izlaz << timovi.size() << endl;

    for (const auto& tim : timovi) {
        izlaz << tim.getNaziv() << endl;
        izlaz << tim.getGrad() << endl;
        izlaz << tim.getBrojPobjeda() << endl;
        izlaz << tim.getBrojPoraza() << endl;
        izlaz << tim.getDatiPoeni() << endl;
        izlaz << tim.getPrimljeniPoeni() << endl;

        if (tim.getTrener() != nullptr) {
            izlaz << 1 << endl;
            izlaz << tim.getTrener()->getIme() << endl;
            izlaz << tim.getTrener()->getPrezime() << endl;
            izlaz << tim.getTrener()->getGodine() << endl;
            izlaz << tim.getTrener()->getGodineIskustva() << endl;
            izlaz << tim.getTrener()->getTrenerRating() << endl;
        } else {
            izlaz << 0 << endl;
        }

        izlaz << tim.getIgraci().size() << endl;

        for (const auto& igrac : tim.getIgraci()) {
            izlaz << igrac.getIme() << endl;
            izlaz << igrac.getPrezime() << endl;
            izlaz << igrac.getGodine() << endl;
            izlaz << igrac.getBrojDresa() << endl;
            izlaz << igrac.getPozicija() << endl;
            izlaz << igrac.getJacinaNapada() << endl;
            izlaz << igrac.getDefanzivniRating() << endl;
            izlaz << igrac.getBrojPoena() << endl;
            izlaz << igrac.getBrojOdigranihUtakmica() << endl;
        }
    }

    izlaz << utakmice.size() << endl;

    for (const auto& utakmica : utakmice) {
        izlaz << utakmica.getDomaciTim() << endl;
        izlaz << utakmica.getGostujuciTim() << endl;
        izlaz << utakmica.getPoeniDomaci() << endl;
        izlaz << utakmica.getPoeniGost() << endl;
        izlaz << utakmica.getDatum() << endl;
    }

    izlaz << liga.getRasporedGenerisan() << endl;
    izlaz << liga.getTrenutnoKolo() << endl;
    izlaz << raspored.size() << endl;

    for (const auto& kolo : raspored) {
        izlaz << kolo.size() << endl;

        for (const auto& par : kolo) {
            izlaz << par.domaci << endl;
            izlaz << par.gost << endl;
            izlaz << par.odigrano << endl;
        }
    }

    izlaz.close();
    cout << "Podaci su uspjesno spremljeni u fajl." << endl;
}
/*Funkcija ucitajPodatkeIzFajla sluzi za ucitavanje podataka lige iz fajla "liga.txt"
 
 Prvo uzmemo sve podatke iz klase liga za timove utakmice i raspored, 
 te uradimo clear ako postoji nesto u memoriji

 Nakon toga radimo obrnuti pustupak iz spremanja u fajl, to jeste ucitavamo iz njega
 Prvo timove, podatke o njima preko settera iz klase tim.
 Nakon toga trenera za taj tim, uzimamo iz filea vrijednosti sa getline,
 te pravimo novu instancu Trener klase za taj tim.
 Isti postupak za igrace, te ih dodajemo u tim

 Zatim učitavamo broj odigranih utakmica iz fajla i za svaku kreiramo objekat 
 Utakmica sa rezultatom i datumom.

 Na kraju učitavamo raspored lige: trenutno kolo, broj kola, te za svako kolo dodajemo
 sve parove utakmica u vektor ParUtakmice, pri čemu flag `odigrano` označava koje utakmice 
 su već odigrane.
*/
void ucitajPodatkeIzFajla(Liga& liga) {
    ifstream ulaz("liga.txt");

    if (!ulaz) {
        cout << "Fajl ne postoji ili se ne moze otvoriti." << endl;
        return;
    }

    vector<Tim>& timovi = liga.getTimovi();
    vector<Utakmica>& utakmice = liga.getUtakmice();
    vector<vector<ParUtakmice>>& raspored = liga.getRasporedMutable();

    timovi.clear();
    utakmice.clear();
    raspored.clear();
    liga.setTrenutnoKolo(0);
    liga.setRasporedGenerisan(false);

    int brojTimova;
    ulaz >> brojTimova;
    ulaz.ignore();

    for (int i = 0; i < brojTimova; i++) {
        string naziv, grad;
        int brojPobjeda, brojPoraza, datiPoeni, primljeniPoeni;

        getline(ulaz, naziv);
        getline(ulaz, grad);

        ulaz >> brojPobjeda;
        ulaz >> brojPoraza;
        ulaz >> datiPoeni;
        ulaz >> primljeniPoeni;
        ulaz.ignore();

        Tim tim(naziv, grad);
        tim.setBrojPobjeda(brojPobjeda);
        tim.setBrojPoraza(brojPoraza);
        tim.setDatiPoeni(datiPoeni);
        tim.setPrimljeniPoeni(primljeniPoeni);

        int imaTrenera;
        ulaz >> imaTrenera;
        ulaz.ignore();

        if (imaTrenera == 1) {
            string ime, prezime;
            int godine, iskustvo, rating;

            getline(ulaz, ime);
            getline(ulaz, prezime);
            ulaz >> godine;
            ulaz >> iskustvo;
            ulaz >> rating;
            ulaz.ignore();

            tim.setTrener(new Trener(ime, prezime, godine, iskustvo, rating));
        }

        int brojIgraca;
        ulaz >> brojIgraca;
        ulaz.ignore();

        for (int j = 0; j < brojIgraca; j++) {
            string ime, prezime, pozicija;
            int godine, brojDresa, napad, odbrana, poeni, brojUtakmica;

            getline(ulaz, ime);
            getline(ulaz, prezime);
            ulaz >> godine;
            ulaz >> brojDresa;
            ulaz.ignore();
            getline(ulaz, pozicija);
            ulaz >> napad;
            ulaz >> odbrana;
            ulaz >> poeni;
            ulaz >> brojUtakmica;
            ulaz.ignore();

            Igrac igrac(ime, prezime, godine, brojDresa, pozicija, napad, odbrana);
            igrac.setBrojPoena(poeni);
            igrac.setBrojOdigranihUtakmica(brojUtakmica);

            tim.dodajIgraca(igrac);
        }

        timovi.push_back(tim);
    }

    int brojUtakmica;
    ulaz >> brojUtakmica;
    ulaz.ignore();

    for (int i = 0; i < brojUtakmica; i++) {
        string domaciTim, gostujuciTim, datum;
        int poeniDomaci, poeniGost;

        getline(ulaz, domaciTim);
        getline(ulaz, gostujuciTim);
        ulaz >> poeniDomaci;
        ulaz >> poeniGost;
        ulaz.ignore();
        getline(ulaz, datum);

        utakmice.push_back(Utakmica(domaciTim, gostujuciTim, poeniDomaci, poeniGost, datum));
    }

    int rasporedGenerisan;
    int trenutnoKolo;
    int brojKola;

    ulaz >> rasporedGenerisan;
    ulaz >> trenutnoKolo;
    ulaz >> brojKola;
    ulaz.ignore();

    liga.setRasporedGenerisan(rasporedGenerisan);
    liga.setTrenutnoKolo(trenutnoKolo);

    for (int i = 0; i < brojKola; i++) {
        int brojParova;
        ulaz >> brojParova;
        ulaz.ignore();

        vector<ParUtakmice> jednoKolo;

        for (int j = 0; j < brojParova; j++) {
            int domaci, gost, odigrano;

            ulaz >> domaci;
            ulaz >> gost;
            ulaz >> odigrano;
            ulaz.ignore();

            jednoKolo.push_back(ParUtakmice(domaci, gost, odigrano));
        }

        raspored.push_back(jednoKolo);
    }

    ulaz.close();
    cout << "Podaci su uspjesno ucitani iz fajla." << endl;
}

/*
 Funkcija radi autosave ako je flag radiAutoSave true.
 Funkcija pauzira 30 sekundi između svakog ciklusa koristeći `sleep_for`.
 Mutex (`fajlMutex`) osigurava da samo jedan thread u isto vrijeme pristupa fajlu, 
 sprječavajući race condition, te se spasava pomocu prethodne 
 funkcije spremiPodatkeUFajl
*/
void autoSaveFunkcija(Liga& liga, bool& radiAutoSave) {
    while (radiAutoSave) {
        this_thread::sleep_for(chrono::seconds(30));

        if (!radiAutoSave) {
            break;
        }

        lock_guard<mutex> lock(fajlMutex);
        spremiPodatkeUFajl(liga);
        cout << "\n[Auto-save] Podaci su automatski spremljeni.\n";
    }
}