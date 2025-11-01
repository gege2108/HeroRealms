#include "StackChampion.h"
#include <algorithm>

StackChampion::StackChampion() = default;
StackChampion::StackChampion(const std::vector<Carte*>& cartes) : cartes(cartes) {}

const std::vector<Carte*>& StackChampion::getCartes() const { return cartes; }
void StackChampion::setCartes(const std::vector<Carte*>& c) { cartes = c; }

void StackChampion::push(Carte* c) {
    cartes.push_back(c);
    
    // Vérifier si c'est un champion avec garde et l'ajouter automatiquement
    Champion* champion = dynamic_cast<Champion*>(c);
    if (champion != nullptr && champion->getIsGarde()) {
        gardes.push_back(champion);
    }
}

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

std::vector<Champion*> StackChampion::getChampions() const {
    std::vector<Champion*> champions;
    for (Carte* carte : cartes) {
        Champion* champion = dynamic_cast<Champion*>(carte);
        if (champion != nullptr) {
            champions.push_back(champion);
        }
    }
    return champions;
}

std::vector<Champion*> StackChampion::getChampions() {
    std::vector<Champion*> champions;
    for (Carte* carte : cartes) {
        Champion* champion = dynamic_cast<Champion*>(carte);
        if (champion != nullptr) {
            champions.push_back(champion);
        }
    }
    return champions;
}

bool StackChampion::removeChampion(Champion* champion) {
    for (auto it = cartes.begin(); it != cartes.end(); ++it) {
        if (*it == champion) {
            cartes.erase(it);
            return true;
        }
    }
    return false;
}

std::vector<Champion*>& StackChampion::getGardes() {
    return gardes;
}

/*const std::vector<Champion*>& StackChampion::getGardes() const {
    return gardes;
}*/

void StackChampion::setGardes(const std::vector<Champion*>& g) {
    gardes = g;
}

void StackChampion::addGarde(Champion* c) {
    if (c != nullptr && c->getIsGarde()) {
        gardes.push_back(c);
    }
}
