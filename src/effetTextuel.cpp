#include "EffetTextuel.h"
#include "Joueur.h"
#include "Pioche.h"
#include "MainJoueur.h"
#include <iostream>

//id : 1 - Piocher une carte
void EffetTextuel::drawACard(Joueur& joueur) {  
    Pioche piocheJoueur = joueur.getPioche();
    MainJoueur mainJoueur = joueur.getMain();
    
    if (!piocheJoueur.getCartes().empty()) {
        piocheJoueur.piocher(mainJoueur);
        
        // Remettre les modifications dans le joueur
        joueur.setMain(mainJoueur);
        joueur.setPioche(piocheJoueur);
        
        std::cout << "Vous piochez une carte et la mettez dans votre main." << std::endl;
    } else {
        std::cout << "La pioche est vide, impossible de piocher une carte." << std::endl;
    }
}

// Implémentation de la méthode statique de classe (PAS une fonction libre)
void EffetTextuel::handleIdEffetTextuel(int id, Joueur& joueur) {
    switch (id) {
        case 1: {
            EffetTextuel effet;
            effet.drawACard(joueur);
            break;
        }
        default:
            std::cout << "Effet textuel inconnu avec l'ID: " << id << std::endl;
            break;
    }
}