#ifndef DATOTEKE_H
#define DATOTEKE_H

#include <mutex>
#include "Liga.h"

extern std::mutex fajlMutex;

void spremiPodatkeUFajl(Liga& liga);
void ucitajPodatkeIzFajla(Liga& liga);
void autoSaveFunkcija(Liga& liga, bool& radiAutoSave);

#endif