#include "ZoneDeSacrifice.h"
#include <algorithm>

ZoneDeSacrifice::ZoneDeSacrifice() = default;
ZoneDeSacrifice::ZoneDeSacrifice(const std::vector<Carte*>& cartes) : cartes(cartes) {}

const std::vector<Carte*>& ZoneDeSacrifice::getCartes() const { return cartes; }
void ZoneDeSacrifice::setCartes(const std::vector<Carte*>& c) { cartes = c; }

void ZoneDeSacrifice::add(Carte* c) { cartes.push_back(c); }

bool ZoneDeSacrifice::remove(Carte* c) {
    for (int i = 0; i < (int)cartes.size(); ++i) {
        if (cartes[i] == c) {
            cartes.erase(cartes.begin() + i);
            return true;
        }
    }
    return false;
}

void ZoneDeSacrifice::clear() { cartes.clear(); }
