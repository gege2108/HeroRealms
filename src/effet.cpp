#include "Effet.h"
#include <string>

Effet::Effet() : valeur(0), type(DEGAT) {}

Effet::Effet(int valeur, TypeEffet type) : valeur(valeur), type(type) {}

int Effet::getValeur() const { return valeur; }
void Effet::setValeur(int v) { valeur = v; }

TypeEffet Effet::getType() const { return type; }
void Effet::setType(TypeEffet t) { type = t; }

std::string Effet::toString() const {
    std::string typeStr;
    switch (type) {
        case OR: typeStr = "Or"; break;
        case DEGAT: typeStr = "Degat"; break;
        default: typeStr = "Unknown"; break;
    }
    return std::to_string(valeur) + " (" + typeStr + ")";
}