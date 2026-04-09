#include "TestPodaci.h"
#include "Tim.h"
#include "Trener.h"
#include "Igrac.h"

void ucitajTestPodatke(Liga& liga) {
    Tim t1("Bosna", "Sarajevo");
    t1.setTrener(new Trener("Amar", "Hadzic", 45, 20, 85));
    t1.dodajIgraca(Igrac("Kenan", "Music", 24, 7, "Bek", 80, 70));
    t1.dodajIgraca(Igrac("Adin", "Basic", 27, 12, "Centar", 75, 85));
    t1.dodajIgraca(Igrac("Emir", "Kovacevic", 22, 5, "Krilo", 78, 72));
    t1.dodajIgraca(Igrac("Tarik", "Smajic", 25, 9, "Bek", 82, 68));
    t1.dodajIgraca(Igrac("Haris", "Delic", 23, 11, "Krilo", 76, 74));
    liga.getTimovi().push_back(t1);

    Tim t2("Spars", "Sarajevo");
    t2.setTrener(new Trener("Mirza", "Beganovic", 50, 25, 88));
    t2.dodajIgraca(Igrac("Aldin", "Zukic", 26, 4, "Bek", 79, 71));
    t2.dodajIgraca(Igrac("Nermin", "Husic", 28, 15, "Centar", 77, 84));
    t2.dodajIgraca(Igrac("Jasmin", "Kurtic", 24, 6, "Krilo", 81, 73));
    t2.dodajIgraca(Igrac("Alen", "Hodzic", 23, 10, "Bek", 83, 69));
    t2.dodajIgraca(Igrac("Eldar", "Memic", 25, 8, "Krilo", 75, 76));
    liga.getTimovi().push_back(t2);

    Tim t3("Igokea", "Laktasi");
    t3.setTrener(new Trener("Dragan", "Markovic", 55, 30, 90));
    t3.dodajIgraca(Igrac("Stefan", "Jovic", 29, 3, "Bek", 84, 72));
    t3.dodajIgraca(Igrac("Nikola", "Vukovic", 27, 14, "Centar", 78, 86));
    t3.dodajIgraca(Igrac("Milos", "Petrovic", 26, 13, "Krilo", 80, 75));
    t3.dodajIgraca(Igrac("Luka", "Radic", 24, 2, "Bek", 82, 70));
    t3.dodajIgraca(Igrac("Ivan", "Simic", 25, 16, "Krilo", 77, 74));
    liga.getTimovi().push_back(t3);

    Tim t4("Sloboda", "Tuzla");
    t4.setTrener(new Trener("Adnan", "Kovacevic", 48, 22, 87));
    t4.dodajIgraca(Igrac("Damir", "Hodzic", 28, 1, "Bek", 81, 73));
    t4.dodajIgraca(Igrac("Samir", "Delic", 27, 18, "Centar", 76, 85));
    t4.dodajIgraca(Igrac("Mirza", "Suljic", 24, 20, "Krilo", 79, 74));
    t4.dodajIgraca(Igrac("Faruk", "Begic", 23, 22, "Bek", 83, 68));
    t4.dodajIgraca(Igrac("Hamed", "Basic", 26, 17, "Krilo", 78, 75));
    liga.getTimovi().push_back(t4);
}