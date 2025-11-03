#include "Defausse.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <chrono>

Defausse::Defausse() = default;
Defausse::Defausse(const std::vector<Carte*>& cartes) : cartes(cartes) {}

const std::vector<Carte*>& Defausse::getCartes() const { return cartes; }
void Defausse::setCartes(const std::vector<Carte*>& c) { cartes = c; }

void Defausse::addCarte(Carte* c) { cartes.push_back(c); }

bool Defausse::remove(Carte* c) {
    for (int i = 0; i < (int)cartes.size(); ++i) {
        if (cartes[i] == c) {
            cartes.erase(cartes.begin() + i);
            return true;
        }
    }
    return false;
}

void Defausse::removeCarte(Carte* carte) {
    for (auto it = cartes.begin(); it != cartes.end(); ++it) {
        if (*it == carte) {
            cartes.erase(it);
            return;
        }
    }
}

void Defausse::addCarteOnTop(Carte* c) {
    cartes.insert(cartes.begin(), c);
}

void Defausse::clear() { cartes.clear(); }

void Defausse::melangeDefausse() {
    if (cartes.empty()) return;

    srand(time(nullptr));
    for (int i = cartes.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Carte* temp = cartes[i];
        cartes[i] = cartes[j];
        cartes[j] = temp;
    }
}
