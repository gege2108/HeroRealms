#include "GemmeDeFeu.h"

// Initialisation des membres statiques
int GemmeDeFeu::prix = 5;
Effet GemmeDeFeu::attaqueGemmeDeFeu = Effet(3, DEGAT);

Effet& GemmeDeFeu::UtiliserAttaque() {
    this->isJetable = true;
    return attaqueGemmeDeFeu;

    // Implémentation de l'attaque
    // TODO: logique pour utiliser l'attaque puis jeter la carte
}


