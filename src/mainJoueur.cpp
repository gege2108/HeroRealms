#include "MainJoueur.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <chrono>


MainJoueur::MainJoueur() = default;

MainJoueur::MainJoueur(const std::vector<Carte*>& cartes)
    : cartes(cartes) {}

const std::vector<Carte*>& MainJoueur::getCartes() const {
    return cartes;
}

void MainJoueur::setCartes(const std::vector<Carte*>& c) {
    cartes = c;
}

void MainJoueur::addCarte(Carte* c) {
    cartes.push_back(c);
}

bool MainJoueur::removeCarte(Carte* c) {
    for (size_t i = 0; i < cartes.size(); ++i) {
        if (cartes[i] == c) {
            cartes.erase(cartes.begin() + i);
            return true;
        }
    }
    return false;
}

void MainJoueur::clear() {
    cartes.clear();
}

std::vector<CarteDeBase*> MainJoueur::getCartesDeBase() const {
    std::vector<CarteDeBase*> res;
    for (Carte* c : cartes) {
        if (auto cb = dynamic_cast<CarteDeBase*>(c)) {
            res.push_back(cb);
        }
    }
    return res;
}

std::vector<GemmeDeFeu*> MainJoueur::getGemmesDeFeu() const {
    std::vector<GemmeDeFeu*> res;
    for (Carte* c : cartes) {
        if (auto gf = dynamic_cast<GemmeDeFeu*>(c)) {
            res.push_back(gf);
        }
    }
    return res;
}

std::vector<Champion*> MainJoueur::getChampions() const {
    std::vector<Champion*> champions;
    for (auto* carte : cartes) {
        Champion* champion = dynamic_cast<Champion*>(carte);
        if (champion != nullptr) {
            champions.push_back(champion);
        }
    }
    return champions;
}

std::vector<Action*> MainJoueur::getActions() const {
    std::vector<Action*> actions;
    for (auto* carte : cartes) {
        // Vérifier que ce n'est pas un Champion avant de caster en Action
        if (dynamic_cast<Champion*>(carte) == nullptr) {
            Action* action = dynamic_cast<Action*>(carte);
            if (action != nullptr) {
                actions.push_back(action);
            }
        }
    }
    return actions;
}

void MainJoueur::melangeMain() {
    if (cartes.empty()) return;

    srand(time(nullptr));
    for (int i = cartes.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Carte* temp = cartes[i];
        cartes[i] = cartes[j];
        cartes[j] = temp;
    }
}
