#include <iostream>
#include <vector>

#include "Plateau.h"
#include "Joueur.h"
#include "MainJoueur.h"
#include "Pioche.h"
#include "CarteDeBase.h"
#include "Effet.h"
#include "GemmeDeFeu.h"
#include "Marche.h"
#include "Action.h"
#include "Faction.h"
#include "EffetTextuel.h"
#include "test.h"
#include "Initializer.h"


//TODO : changer l'implementation de sorte à ce que les degats d'attaques soient stockés par le joueur avant d'être utilise
//TODO : faire en sorte que le

int main() {
    std::cout << "=== Test de la nouvelle fonction choixUtilisationEffetJ1 ===" << std::endl;
    
    try {
        testChoixUtilisationEffetJ1NouvelleFonction();
    } catch (const std::exception& e) {
        std::cout << "ERREUR lors du test: " << e.what() << std::endl;
    }

    return 0;
}
