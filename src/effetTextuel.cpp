#include "EffetTextuel.h"
#include "Joueur.h"
#include "Pioche.h"
#include "MainJoueur.h"
#include <iostream>
#include <algorithm>
#include <random>

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
        case 5: {
            effet.defenseModActivated(joueurJouantLeTour);
            break;
        }
        case 6: {
            effet.drawTwoAndDiscardTwo(joueurJouantLeTour);
            break;
        }
        case 7: {
            effet.gain2HealthPerChampion(joueurJouantLeTour);
            break;
        }
        case 8: {
            effet.gainCombatPerOtherGuard(joueurJouantLeTour);
            break;
        }
        case 9: {
            effet.gainCombatPerOtherChampion(joueurJouantLeTour);
            break;
        }
        case 10: {
            effet.gain1HealthPerChampion(joueurJouantLeTour);
            break;
        }
        case 11: {
            effet.gain2CombatPerChampion(joueurJouantLeTour);
            break;
        }
        case 12: {
            effet.gain1CombatPerOtherChampionWild(joueurJouantLeTour);
            break;
        }
        case 13: { // AJOUT : placer une carte de la défausse sur le dessus de la pioche
            effet.placeCardFromDiscardOnTopOfDraw(joueurJouantLeTour);
            break;
        }
        case 14: { // Put the next action you acquire this turn on top of your deck
            effet.setNextActionAcquiredOnTop(joueurJouantLeTour);
            break;
        }
        default:
            std::cout << "Effet textuel avec ID " << id << " non implémenté." << std::endl;
            break;
    }
}

//id : 3 - Étourdir un champion adversaire
void EffetTextuel::stunChampion(Joueur& opponent) {
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
    std::cout << "Voulez-vous piocher une carte ? [1] Oui [0] Non : ";
    int choixPioche;
    std::cin >> choixPioche;
    if (choixPioche == 1) {
        drawACard(joueur);
    }
    else{
        std::cout << "Vous avez choisi de ne pas piocher de carte." << std::endl;
        return;
    }

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

//id : 5 - Activer le mode défense pour tous les champions en main
void EffetTextuel::defenseModActivated(Joueur& joueur) {
    std::cout << "\n=== Activation du mode défense ===" << std::endl;
    
    // Récupérer tous les champions de la main du joueur
    MainJoueur& main = joueur.getMain();
    std::vector<Carte*> cartesMain = main.getCartes(); 
    std::vector<Champion*> championsEnMain;
    
    // Identifier tous les champions dans la main
    for (size_t i = 0; i < cartesMain.size(); ++i) {
        Champion* champion = dynamic_cast<Champion*>(cartesMain[i]);
        if (champion != nullptr) {
            championsEnMain.push_back(champion);
        }
    }
    
    if (championsEnMain.empty()) {
        std::cout << "Aucun champion dans votre main à mettre en défense." << std::endl;
        return;
    }
    
    std::cout << "Champions disponibles dans votre main :" << std::endl;
    for (size_t i = 0; i < championsEnMain.size(); ++i) {
        std::cout << i + 1 << ". " << championsEnMain[i]->getNom() 
                  << " (PV: " << championsEnMain[i]->getPointDeVie() 
                  << ", Garde: " << (championsEnMain[i]->getIsGarde() ? "Oui" : "Non") << ")" << std::endl;
    }
    
    // Activer le mode défense pour tous les champions de la main
    std::cout << "\nActivation du mode défense pour tous les champions..." << std::endl;
    
    for (Champion* champion : championsEnMain) {
        // Activer le mode défense
        champion->setIsDefense(true);
        
        // Ajouter le champion au StackChampion du joueur
        joueur.getStackChampion().push(champion);
        
        std::cout << "- " << champion->getNom() << " passe en mode défense";
        if (champion->getIsGarde()) {
            std::cout << " (GARDE activé)";
        }
        std::cout << std::endl;
        
        // Retirer le champion de la main
        joueur.getMain().removeCarte(champion);
    }
    
    std::cout << "\nTous les champions ont été transférés en mode défense." << std::endl;
    std::cout << "Champions en jeu: " << joueur.getStackChampion().getChampions().size() << std::endl;
    std::cout << "Gardes actifs: " << joueur.getStackChampion().getGardes().size() << std::endl;
}

//id : 6 - Piocher 2 cartes puis en défausser 2
void EffetTextuel::drawTwoAndDiscardTwo(Joueur& joueur) {
    std::cout << "\n=== Piocher 2 puis défausser 2 ===" << std::endl;
    
    // Piocher 2 cartes
    int cartesPiochees = 0;
    for (int i = 0; i < 2; ++i) {
        Pioche piocheJoueur = joueur.getPioche();
        MainJoueur mainJoueur = joueur.getMain();
        
        if (!piocheJoueur.getCartes().empty()) {
            piocheJoueur.piocher(mainJoueur);
            joueur.setMain(mainJoueur);
            joueur.setPioche(piocheJoueur);
            cartesPiochees++;
            std::cout << "Carte " << (i + 1) << " piochée." << std::endl;
        } else {
            std::cout << "La pioche est vide, impossible de piocher la carte " << (i + 1) << "." << std::endl;
            break;
        }
    }
    
    if (cartesPiochees == 0) {
        std::cout << "Aucune carte piochée, aucune défausse nécessaire." << std::endl;
        return;
    }
    
    // Vérifier s'il y a des cartes à défausser
    if (joueur.getMain().getCartes().empty()) {
        std::cout << "Pas de cartes en main à défausser." << std::endl;
        return;
    }
    
    // Défausser 2 cartes (ou moins si pas assez de cartes)
    int cartesADefausser = std::min(2, static_cast<int>(joueur.getMain().getCartes().size()));
    
    for (int i = 0; i < cartesADefausser; ++i) {
        std::cout << "\n--- Défausser la carte " << (i + 1) << "/" << cartesADefausser << " ---" << std::endl;
        std::cout << "Cartes en main :" << std::endl;
        
        for (size_t j = 0; j < joueur.getMain().getCartes().size(); ++j) {
            std::cout << "  [" << j << "] " << joueur.getMain().getCartes()[j]->getNom() << std::endl;
        }
        
        int choix;
        std::cout << "Choisissez une carte (0 à " << joueur.getMain().getCartes().size() - 1 << "): ";
        std::cin >> choix;
        
        if (choix < 0 || choix >= static_cast<int>(joueur.getMain().getCartes().size())) {
            std::cout << "Choix invalide. Défausse de la première carte par défaut." << std::endl;
            choix = 0;
        }
        
        Carte* carte = joueur.getMain().getCartes()[choix];
        joueur.getMain().removeCarte(carte);
        const_cast<Defausse&>(joueur.getDefausse()).addCarte(carte);
        
        std::cout << "✓ Vous défaussez : " << carte->getNom() << std::endl;
    }
    
    std::cout << "\n✅ Effet terminé : " << cartesPiochees << " carte(s) piochée(s), " 
              << cartesADefausser << " carte(s) défaussée(s)." << std::endl;
}


//id : 7 - Gagner 2 points de vie pour chaque champion en jeu
void EffetTextuel::gain2HealthPerChampion(Joueur& joueur) {
    int nbChampions = joueur.getStackChampion().getChampions().size();
    int healthGain = 2 * nbChampions;
    joueur.gainHealth(healthGain);
    std::cout << "Vous gagnez " << healthGain << " points de vie (2 × " << nbChampions << " champions)" << std::endl;
}


//id : 8 - Gagner 1 combat pour chaque autre garde en jeu
void EffetTextuel::gainCombatPerOtherGuard(Joueur& joueur) {
 int nbGardes = joueur.getStackChampion().getGardes().size() - 1; // -1 pour exclure le champion actuel
 if (nbGardes > 0) {
 joueur.addCombat(nbGardes);
 std::cout << "Vous gagnez " << nbGardes << " points de combat (1 × " << nbGardes << " autres gardes)" << std::endl;
 }
}

//id : 9 - Gagner 1 combat pour chaque autre champion en jeu
void EffetTextuel::gainCombatPerOtherChampion(Joueur& joueur) {
 int nbChampions = joueur.getStackChampion().getChampions().size() - 1; // -1 pour exclure le champion actuel
 if (nbChampions > 0) {
 joueur.addCombat(nbChampions);
 std::cout << "Vous gagnez " << nbChampions << " points de combat (1 × " << nbChampions << " autres champions)" << std::endl;
 }
}

//id : 10 - Gagner 1 point de vie pour chaque champion en jeu
void EffetTextuel::gain1HealthPerChampion(Joueur& joueur) {
 int nbChampions = joueur.getStackChampion().getChampions().size();
 joueur.gainHealth(nbChampions);
 std::cout << "Vous gagnez " << nbChampions << " points de vie (1 × " << nbChampions << " champions)" << std::endl;
}

//id : 11 - Gagner 2 combat pour chaque champion en jeu
void EffetTextuel::gain2CombatPerChampion(Joueur& joueur) {
 int nbChampions = joueur.getStackChampion().getChampions().size(); // -1 pour exclure le champion actuel
 if (nbChampions > 0) {
 joueur.addCombat(nbChampions * 2);
 std::cout << "Vous gagnez " << nbChampions * 2 << " points de combat (2 × " << nbChampions << " autres champions)" << std::endl;
 }
}

//id : 12 - Gagner 1 combat pour chaque autre champion de faction Verte en jeu
void EffetTextuel::gain1CombatPerOtherChampionWild(Joueur& joueur) {
 int nbChampionsWild = 0;
 auto champions = joueur.getStackChampion().getChampions();
 
 // Compter les champions de faction Verte, en excluant le champion actuel (-1)
 for (const auto& champion : champions) {
 if (champion->getFaction() == Faction::FactionVert) {
 nbChampionsWild++;
 }
 }
 nbChampionsWild--; // Exclure le champion actuel

 if (nbChampionsWild > 0) {
 joueur.addCombat(nbChampionsWild);
 std::cout << "Vous gagnez " << nbChampionsWild 
 << " points de combat (1 × " << nbChampionsWild 
 << " autres champions Verts)" << std::endl;
 }
}

// id 13 : "Vous pouvez placer une carte de votre défausse sur le dessus de votre pioche"
void EffetTextuel::placeCardFromDiscardOnTopOfDraw(Joueur& joueur) {
    std::cout << "\n=== Placer une carte de votre défausse sur le dessus de votre pioche ===" << std::endl;
    
    // Récupérer la défausse
    Defausse def = joueur.getDefausse();
    auto defCartes = def.getCartes();
    if (defCartes.empty()) {
        std::cout << "Votre défausse est vide. Aucune carte à placer." << std::endl;
        return;
    }
    
    // Afficher les cartes de la défausse
    std::cout << "Cartes dans votre défausse :" << std::endl;
    for (size_t i = 0; i < defCartes.size(); ++i) {
        std::string nom = defCartes[i] ? defCartes[i]->getNom() : "(Carte invalide)";
        std::cout << "  [" << i << "] " << nom << std::endl;
    }
    
    // Demander le choix (optionnel)
    std::cout << "Voulez-vous placer une carte de votre défausse sur le dessus de votre pioche ? [1] Oui [0] Non : ";
    int choixActiver = 0;
    std::cin >> choixActiver;
    if (choixActiver != 1) {
        std::cout << "Vous avez choisi de ne pas déplacer de carte." << std::endl;
        return;
    }
    
    // Choix de la carte
    int idx = -1;
    std::cout << "Choisissez l'indice de la carte à placer (0 à " << defCartes.size() - 1 << "): ";
    std::cin >> idx;
    if (idx < 0 || idx >= static_cast<int>(defCartes.size())) {
        std::cout << "Indice invalide. Opération annulée." << std::endl;
        return;
    }
    
    Carte* carteChoisie = defCartes[idx];
    if (!carteChoisie) {
        std::cout << "Carte invalide. Opération annulée." << std::endl;
        return;
    }
    
    // Retirer la carte de la défausse (mise à jour locale puis set)
    def.removeCarte(carteChoisie);
    joueur.setDefausse(def);
    
    // Ajouter la carte sur le dessus de la pioche
    Pioche pioche = joueur.getPioche();
    pioche.addCarteOnTop(carteChoisie);
    joueur.setPioche(pioche);
    
    std::cout << "✓ Carte '" << carteChoisie->getNom() << "' placée sur le dessus de votre pioche." << std::endl;
}

// id 14 : Put the next action you acquire this turn on top of your deck
void EffetTextuel::setNextActionAcquiredOnTop(Joueur& joueur) {
    // Active un flag sur le joueur pour ce tour
    joueur.setNextActionOnTop(true);
    std::cout << "Effet activé : La prochaine action que vous achetez ce tour ira sur le dessus de votre pioche." << std::endl;
}

