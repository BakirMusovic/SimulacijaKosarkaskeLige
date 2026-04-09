#ifndef TIMFUNKCIJE_H
#define TIMFUNKCIJE_H

#include <vector>
#include "Tim.h"

void dodajTim(std::vector<Tim>& timovi);
void prikaziTimove(const std::vector<Tim>& timovi);
void prikaziIgraceTima(const std::vector<Tim>& timovi);
void dodajTrenera(std::vector<Tim>& timovi);
void dodajIgraca(std::vector<Tim>& timovi);
void prikaziStatistikuIgraca(const std::vector<Tim>& timovi);
void prikaziTopStrijelca(const std::vector<Tim>& timovi);
void obrisiIgracaIzTima(std::vector<Tim>& timovi);
void obrisiTreneraIzTima(std::vector<Tim>& timovi);

#endif