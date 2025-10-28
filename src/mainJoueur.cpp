#include "MainJoueur.h"

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