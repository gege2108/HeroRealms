#include "GemmeDeFeu.h"
#include <iostream>

// Initialisation des membres statiques
int GemmeDeFeu::prix = 3;
Effet GemmeDeFeu::effetOr = Effet(2, OR);
Effet GemmeDeFeu::attaqueGemmeDeFeu = Effet(3, DEGAT);

GemmeDeFeu::GemmeDeFeu() : Carte("Gemme de Feu"), isJetable(false) {
    this->effetsBasiqueChoix1 = { Effet(2, OR) };
}

GemmeDeFeu::GemmeDeFeu(const std::string& nom) : Carte(nom), isJetable(false) {
    this->effetsBasiqueChoix1 = { Effet(2, OR) };
}

Effet& GemmeDeFeu::UtiliserEffetOr() {
    // Retourne l'effet +2 or sans sacrifier la gemme
    return effetOr;
}

Effet& GemmeDeFeu::UtiliserAttaque() {
    // Retourne l'effet +3 dégâts et marque la gemme comme sacrifiée
    this->isJetable = true;
    return attaqueGemmeDeFeu;
}

const std::string& GemmeDeFeu::getNom() const {
    static const std::string nomGemme = "Gemme de Feu";
    return nomGemme;
}

std::string GemmeDeFeu::toString() const {
    std::string result = "Gemme de Feu (Prix: " + std::to_string(prix) + ")\n";
    result += "Effets disponibles:\n";
    result += "  - Effet 1: +2 Or\n";
    result += "  - Effet 2 (SACRIFICE): +3 Dégâts (la gemme sera sacrifiée)";
    if (isJetable) {
        result += "\n⚠️  CETTE GEMME A ÉTÉ SACRIFIÉE";
    }
    return result;
}


