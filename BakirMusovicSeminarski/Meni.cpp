#include "Meni.h"
#include <iostream>

using namespace std;

void glavniMeni() {
    cout << "\n===== GLAVNI MENI =====" << endl;
    cout << "1. Upravljanje timovima i igracima" << endl;
    cout << "2. Utakmice i liga" << endl;
    cout << "3. Datoteke" << endl;
    cout << "0. Izlaz" << endl;
    cout << "Odabir: ";
}

void meniTimovi() {
    cout << "\n===== UPRAVLJANJE TIMOVIMA I IGRACIMA =====" << endl;
    cout << "1. Dodaj tim" << endl;
    cout << "2. Dodaj trenera timu" << endl;
    cout << "3. Dodaj igraca u tim" << endl;
    cout << "4. Prikazi timove" << endl;
    cout << "5. Prikazi igrace tima" << endl;
    cout << "6. Statistika igraca" << endl;
    cout << "7. Obrisi igraca iz tima" << endl;
    cout << "8. Obrisi trenera iz tima" << endl;
    cout << "0. Nazad" << endl;
    cout << "Odabir: ";
}

void meniLiga() {
    cout << "\n===== UTAKMICE I LIGA =====" << endl;
    cout << "1. Simuliraj utakmicu" << endl;
    cout << "2. Prikazi utakmice" << endl;
    cout << "3. Prikazi tabelu lige" << endl;
    cout << "4. Generisi raspored lige" << endl;
    cout << "5. Prikazi raspored lige" << endl;
    cout << "6. Simuliraj naredno kolo" << endl;
    cout << "7. Resetuj ligu" << endl;
    cout << "0. Nazad" << endl;
    cout << "Odabir: ";
}

void meniDatoteke() {
    cout << "\n===== DATOTEKE =====" << endl;
    cout << "1. Spremi podatke u fajl" << endl;
    cout << "2. Ucitaj podatke iz fajla" << endl;
    cout << "0. Nazad" << endl;
    cout << "Odabir: ";
}