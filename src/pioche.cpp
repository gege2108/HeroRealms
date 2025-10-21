#include "Pioche.h"
#include <algorithm>

Pioche::Pioche() = default;
Pioche::Pioche(const std::vector<Carte*>& cartes) : cartes(cartes) {}

const std::vector<Carte*>& Pioche::getCartes() const { return cartes; }
void Pioche::setCartes(const std::vector<Carte*>& c) { cartes = c; }

void Pioche::push(Carte* c) { cartes.push_back(c); }

bool Pioche::draw(Carte* c) {
    for (int i = 0; i < (int)cartes.size(); ++i) {
        if (cartes[i] == c) {
            cartes.erase(cartes.begin() + i);
            return true;
        }
    }
    return false;
}

void Pioche::clear() { cartes.clear(); }
