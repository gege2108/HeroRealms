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


//id : 2 - Défausser une carte de la main de l'adversaire
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
    
    Carte* carte = mainOpponent.getCartes()[nombre];
    mainOpponent.removeCarte(carte);
    const Defausse& defausseOpponent = opponent.getDefausse();
    const_cast<Defausse&>(defausseOpponent).addCarte(carte);
    
    std::cout << "L'adversaire défausse : " << carte->getNom() << std::endl;
}


void EffetTextuel::handleIdEffetTextuel(int id, Joueur& joueurJouantLeTour, Joueur& adversaire) {
    EffetTextuel effet;
    switch (id) {    
        case 1: {
            effet.drawACard(joueurJouantLeTour);
            break;
        }
        case 2: {
            //Dans ce contexte, joueur correspond à l'adversaire
            effet.discardOpponentCard(adversaire);
            break;
        }
        case 3: {
            //Dans ce contexte, joueur correspond à l'adversaire
            effet.stunChampion(adversaire);
            break;
        }
        case 4: {
            effet.drawAndDiscard(joueurJouantLeTour);
            break;
        }
        default:
            std::cout << "Effet textuel inconnu avec l'ID: " << id << std::endl;
            break;
    }
}

//id : 3 - Étourdir un champion adversaire
void EffetTextuel::stunChampion(Joueur& opponent) const {
    if (opponent.getStackChampion().getChampions().empty()) {
        std::cout << "L'adversaire n'a pas de champions à étourdir." << std::endl;
        return;
    }
    
    std::cout << "Champions de l'adversaire :" << std::endl;
    auto champions = opponent.getStackChampion().getChampions();
    for (size_t i = 0; i < champions.size(); ++i) {
        std::cout << "  [" << i << "] " << champions[i]->getNom() << std::endl;
    }
    
    int nombre;
    std::cout << "Choisissez un champion à étourdir (0 à " << champions.size() - 1 << "): ";
    std::cin >> nombre;
    
    if (nombre < 0 || nombre >= static_cast<int>(champions.size())) {
        std::cout << "Indice invalide. Aucun champion étourdi." << std::endl;
        return;
    }
    
    // Utiliser un pointeur au lieu d'une référence
    Champion* champion = champions[nombre];
    champion->setIsDefense(false);
    
    // Utiliser const_cast pour obtenir une référence non-const
    const_cast<StackChampion&>(opponent.getStackChampion()).removeChampion(champion);
    opponent.getDefausse().addCarte(champion);
    
    std::cout << "Le champion " << champion->getNom() << " est étourd. Il perd sa défense et retourne dans la defausse du joueur." << std::endl;
}


//id : 4 - Vous pouvez piocher une carte, puis en défausser une
void EffetTextuel::drawAndDiscard(Joueur& joueur) {
    // Piocher une carte
    drawACard(joueur);
    
    // Vérifier s'il y a des cartes à défausser
    if (joueur.getMain().getCartes().empty()) {
        std::cout << "Pas de cartes en main à défausser." << std::endl;
        return;
    }
    
    // Défausser une carte
    std::cout << "\nChoisissez une carte à défausser de votre main :" << std::endl;
    for (size_t i = 0; i < joueur.getMain().getCartes().size(); ++i) {
        std::cout << "  [" << i << "] " << joueur.getMain().getCartes()[i]->getNom() << std::endl;
    }
    
    int choix;
    std::cout << "Choisissez une carte (0 à " << joueur.getMain().getCartes().size() - 1 << "): ";
    std::cin >> choix;
    
    if (choix < 0 || choix >= static_cast<int>(joueur.getMain().getCartes().size())) {
        std::cout << "Choix invalide. Aucune carte défaussée." << std::endl;
        return;
    }
    
    Carte* carte = joueur.getMain().getCartes()[choix];
    joueur.getMain().removeCarte(carte);
    const_cast<Defausse&>(joueur.getDefausse()).addCarte(carte);
    
    std::cout << "Vous défaussez : " << carte->getNom() << std::endl;
}