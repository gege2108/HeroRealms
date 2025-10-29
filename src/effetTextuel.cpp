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


//2 Target opponent discards a card. (Supprimer const de la signature)
void EffetTextuel::discardOpponentCard(Joueur& opponent) {
    MainJoueur& mainOpponent = opponent.getMain();
    if (mainOpponent.getCartes().empty()) {
        std::cout << "L'adversaire n'a pas de cartes à défausser." << std::endl;
        return;
    }
    
    std::cout << "Cartes de l'adversaire :" << std::endl;
    for (size_t i = 0; i < mainOpponent.getCartes().size(); ++i) {
        std::cout << "  [" << i << "] " << mainOpponent.getCartes()[i]->getNom() << std::endl;
    }
    
    int nombre;
    std::cout << "Choisissez une carte à défausser (indice de 0 à " << mainOpponent.getCartes().size() - 1 << "): ";
    std::cin >> nombre;
    
    if (nombre < 0 || nombre >= static_cast<int>(mainOpponent.getCartes().size())) {
        std::cout << "Indice invalide. Aucune carte défaussée." << std::endl;
        return;
    }
    
    // Utiliser un pointeur au lieu d'une valeur
    Carte* carte = mainOpponent.getCartes()[nombre];
    
    // Retirer la carte de la main de l'adversaire
    mainOpponent.removeCarte(carte);
    
    // Maintenant cela devrait fonctionner directement
    const Defausse& defausseOpponent = opponent.getDefausse();
    const_cast<Defausse&>(defausseOpponent).addCarte(carte);
    
    std::cout << "L'adversaire défausse : " << carte->getNom() << std::endl;
}


// Implémentation de la méthode statique de classe (PAS une fonction libre)
void EffetTextuel::handleIdEffetTextuel(int id, Joueur& joueur) {
    EffetTextuel effet;
    switch (id) {    
        case 1: {
            effet.drawACard(joueur);
            break;
        }
        case 2: {
            //Dans ce contexte, joueur correspond à l'adversaire
            effet.discardOpponentCard(joueur);
            break;
        }
        default:
            std::cout << "Effet textuel inconnu avec l'ID: " << id << std::endl;
            break;
    }
}
