#include "GemmeDeFeu.h"
#include <iostream>

// Initialisation des membres statiques
int GemmeDeFeu::prix = 5;
Effet GemmeDeFeu::attaqueGemmeDeFeu = Effet(3, DEGAT);

Effet& GemmeDeFeu::UtiliserAttaque() {
    this->isJetable = true;
    return attaqueGemmeDeFeu;

    // Implémentation de l'attaque
    // TODO: logique pour utiliser l'attaque puis jeter la carte
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


