#include "StackChampion.h"
#include <algorithm>

StackChampion::StackChampion() = default;
StackChampion::StackChampion(const std::vector<Carte*>& cartes) : cartes(cartes) {}

const std::vector<Carte*>& StackChampion::getCartes() const { return cartes; }
void StackChampion::setCartes(const std::vector<Carte*>& c) { cartes = c; }

void StackChampion::push(Carte* c) { cartes.push_back(c); }

bool StackChampion::pop(Carte* c) {
    for (int i = 0; i < (int)cartes.size(); ++i) {
        if (cartes[i] == c) {
            cartes.erase(cartes.begin() + i);
            return true;
        }
    }
    return false;
}

void StackChampion::clear() { cartes.clear(); }
