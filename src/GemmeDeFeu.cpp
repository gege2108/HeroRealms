#include "GemmeDeFeu.h"
#include <iostream>

// Initialisation des membres statiques
int GemmeDeFeu::prix = 3;  // Prix : 3 or
Effet GemmeDeFeu::attaqueGemmeDeFeu = Effet(3, DEGAT);

GemmeDeFeu::GemmeDeFeu() : Carte("Gemme de Feu"), isJetable(false) {
    this->effetsBasiqueChoix1 = { Effet(2, OR) };
}

GemmeDeFeu::GemmeDeFeu(const std::string& nom) : Carte(nom), isJetable(false) {
    this->effetsBasiqueChoix1 = { Effet(2, OR) };
}

Effet& GemmeDeFeu::UtiliserAttaque() {
    this->isJetable = true;
    return attaqueGemmeDeFeu;
}

const std::string& GemmeDeFeu::getNom() const {
    static const std::string nomGemme = "Gemme de Feu";
    return nomGemme;
}

std::string GemmeDeFeu::toString() const {
    std::string result = "Gemme de Feu (Prix: " + std::to_string(prix) + ")\n";
    result += "Effets basiques:\n";
    for (const auto& effet : getEffetsBasiqueChoix1()) {
        result += "  - " + effet.toString() + "\n";
    }
    result += "Effet d'attaque (sacrifice): 3 dégâts";
    return result;
}


