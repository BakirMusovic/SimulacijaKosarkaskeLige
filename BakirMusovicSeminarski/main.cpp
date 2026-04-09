#include <iostream>
#include <thread>
#include <mutex>

#include "Liga.h"
#include "Utils.h"
#include "TimFunkcije.h"
#include "LigaFunkcije.h"
#include "Datoteke.h"
#include "Meni.h"
#include "TestPodaci.h"

using namespace std;

int main() {
    /*
     Inicijalizacija generatora slucajnih brojeva koji se koristi u simulaciji utakmica.
     Kreira se objekat klase Liga i ucitavaju se testni podaci (timovi, igraci, treneri).
     Pokrece se posebna nit (thread) za automatsko spremanje podataka u fajl.
     Promjenljiva radiAutoSave kontrolise rad ove niti.
     Definise se varijabla izborGlavni koja se koristi za navigaciju kroz glavni meni.
    */
    initRandom();

    Liga liga;
    ucitajTestPodatke(liga);

    bool radiAutoSave = true;
    thread autoSaveNit(autoSaveFunkcija, ref(liga), ref(radiAutoSave));

    int izborGlavni;
    /*
     Glavna petlja programa koja prikazuje glavni meni i omogucava korisniku
     izbor izmedju upravljanja timovima, ligom ili radom sa datotekama.
     Program radi sve dok korisnik ne odabere opciju za izlaz.
    */
    do {
        glavniMeni();
        izborGlavni = unosBroja();

        switch (izborGlavni) {
        /*
         Meni za upravljanje timovima i igracima.
         Omogucava dodavanje timova, trenera i igraca, pregled podataka,
         kao i brisanje igraca i trenera iz tima.
        */
        case 1: {
            int izbor;
            do {
                meniTimovi();
                izbor = unosBroja();

                switch (izbor) {
                case 1: dodajTim(liga.getTimovi()); break;
                case 2: dodajTrenera(liga.getTimovi()); break;
                case 3: dodajIgraca(liga.getTimovi()); break;
                case 4: prikaziTimove(liga.getTimovi()); break;
                case 5: prikaziIgraceTima(liga.getTimovi()); break;
                case 6:
                    prikaziStatistikuIgraca(liga.getTimovi());
                    prikaziTopStrijelca(liga.getTimovi());
                    break;
                case 7: obrisiIgracaIzTima(liga.getTimovi()); break;
                case 8: obrisiTreneraIzTima(liga.getTimovi()); break;
                }
            } while (izbor != 0);
            break;
        }

        case 2: {
            /*
             Meni za upravljanje ligom i utakmicama.
             Omogucava simulaciju utakmica, prikaz rezultata i tabele,
             generisanje rasporeda, simulaciju kola i resetovanje lige.
             Za operacije koje mijenjaju podatke koristi se mutex kako bi se
             sprijecili problemi sa paralelnim pristupom (auto-save nit).
            */
            int izbor;
            do {
                meniLiga();
                izbor = unosBroja();

                switch (izbor) {
                case 1: {
                    lock_guard<mutex> lock(fajlMutex);

                    if (liga.getRasporedGenerisan()) {
                        liga.simulirajUtakmicuIzTrenutnogKola();
                    } else {
                        simulirajUtakmicu(liga.getTimovi(), liga.getUtakmice());
                    }
                    break;
                }
                case 2: prikaziUtakmice(liga.getUtakmice()); break;
                case 3: prikaziTabeluLige(liga.getTimovi()); break;
                case 4: {
                    lock_guard<mutex> lock(fajlMutex);
                    liga.generisiRasporedDoubleRoundRobin();
                    break;
                }
                case 5:
                    liga.prikaziRaspored();
                    break;
                case 6: {
                    lock_guard<mutex> lock(fajlMutex);
                    liga.simulirajNarednoKolo();
                    break;
                }
                case 7: {
                    lock_guard<mutex> lock(fajlMutex);

                    cout << "Da li ste sigurni da zelite resetovati ligu? (1 = DA, 0 = NE): ";
                    int potvrda = unosBroja();

                    if (potvrda == 1) {
                        liga.resetujLigu();
                        cout << "Liga je resetovana." << endl;
                    } else {
                        cout << "Reset otkazan." << endl;
                    }
                    break;
                }
                }
            } while (izbor != 0);
            break;
        }

        case 3: {
            /*
             Meni za rad sa datotekama.
             Omogucava rucno spremanje podataka u fajl i ucitavanje podataka iz fajla.
             Mutex se koristi kako bi se izbjegao konflikt sa auto-save niti.
            */
            int izbor;
            do {
                meniDatoteke();
                izbor = unosBroja();

                switch (izbor) {
                case 1: {
                    lock_guard<mutex> lock(fajlMutex);
                    spremiPodatkeUFajl(liga);
                    break;
                }
                case 2: {
                    lock_guard<mutex> lock(fajlMutex);
                    ucitajPodatkeIzFajla(liga);
                    break;
                }
                }
            } while (izbor != 0);
            break;
        }

        case 0:
            cout << "Izlaz iz aplikacije." << endl;
            break;
        }

    } while (izborGlavni != 0);

    /*
     Zaustavljanje auto-save niti i cekanje da se nit zavrsi prije izlaska iz programa.
    */
    radiAutoSave = false;

    if (autoSaveNit.joinable()) {
        autoSaveNit.join();
    }

    return 0;
}