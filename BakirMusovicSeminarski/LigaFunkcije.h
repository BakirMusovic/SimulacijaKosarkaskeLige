#ifndef LIGAFUNKCIJE_H
#define LIGAFUNKCIJE_H

#include <vector>
#include "Tim.h"
#include "Utakmica.h"

void simulirajUtakmicu(std::vector<Tim>& timovi, std::vector<Utakmica>& utakmice);
void prikaziUtakmice(const std::vector<Utakmica>& utakmice);
void prikaziTabeluLige(const std::vector<Tim>& timovi);

#endif