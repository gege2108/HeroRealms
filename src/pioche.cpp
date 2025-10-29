#include "Pioche.h"


Pioche::Pioche() = default;
Pioche::Pioche(const std::vector<Carte*>& cartes) : cartesPioche(cartes) {}

const std::vector<Carte*>& Pioche::getCartes() const { return cartesPioche; }
void Pioche::setCartes(const std::vector<Carte*>& c) { cartesPioche = c; }

void Pioche::addCarte(Carte* c) { cartesPioche.push_back(c); }

bool Pioche::tirerCarte(Carte* c) {
    for (int i = 0; i < (int)cartesPioche.size(); ++i) {
        if (cartesPioche[i] == c) {
            cartesPioche.erase(cartesPioche.begin() + i);
            return true;
        }
    }
    return false;
}

void Pioche::piocher(MainJoueur& main) {
    if (cartesPioche.empty()) return;
    Carte* carte = cartesPioche[0];
    cartesPioche.erase(cartesPioche.begin());
    main.addCarte(carte);
}


void Pioche::clear() { cartesPioche.clear(); }
