#include "test.h"
#include <iostream>
#include <vector>
#include "Action.h"
#include "Faction.h"
#include "Effet.h"
#include "Marche.h"
#include "EffetTextuel.h"
#include "Joueur.h"
#include "Pioche.h"
#include "CarteDeBase.h"

void runAllTests() {
    std::cout << "=== EXÉCUTION DE TOUS LES TESTS ===" << std::endl;
    testMelangeActions();
    testMiseAJourActionsVendables();
    testEffetTextuel();
    testDiscardOpponentCard();
    testStunChampion();
    testDrawAndDiscard();
    testPeuxActiverCombo();  // Ajouter le nouveau test
    std::cout << "=== FIN DE TOUS LES TESTS ===" << std::endl;
}

void testMelangeActions() {
    std::cout << "=== Test du mélange des actions ===" << std::endl;
    
    // Créer plusieurs actions avec des noms différents
    Action* taxation = new Action(Faction::FactionJaune, "Taxation", 1, {Effet(2, OR)}, {}, {},{} ,{Effet(6, SOIN)}, {});
    Action* potDeVin = new Action(Faction::FactionBleu, "Pot-de-Vin", 1, {Effet(2, OR)}, {},{}, {}, {Effet(4, DEGAT)}, {});
    Action* intimidation = new Action(Faction::FactionBleu, "Intimidation", 2, {Effet(5, DEGAT)}, {} , {}, {}, {Effet(3, OR)}, {});
    Action* recrutement = new Action(Faction::FactionJaune, "Recrutement", 3, {Effet(1, OR)}, {}, {}, {}, {Effet(2, SOIN)}, {});
    Action* commandement = new Action(Faction::FactionJaune, "Commandement", 2, {Effet(3, DEGAT)}, {}, {}, {}, {Effet(1, OR)}, {});

    // Créer un marché et ajouter les actions
    Marche marcheTestMix;
    marcheTestMix.addStackAction(taxation);
    marcheTestMix.addStackAction(potDeVin);
    marcheTestMix.addStackAction(intimidation);
    marcheTestMix.addStackAction(recrutement);
    marcheTestMix.addStackAction(commandement);
    marcheTestMix.addStackAction(taxation);
    marcheTestMix.addStackAction(potDeVin);
    marcheTestMix.addStackAction(intimidation);
    marcheTestMix.addStackAction(recrutement);
    marcheTestMix.addStackAction(commandement);
    marcheTestMix.addStackAction(taxation);
    marcheTestMix.addStackAction(potDeVin);
    marcheTestMix.addStackAction(intimidation);
    marcheTestMix.addStackAction(recrutement);
    marcheTestMix.addStackAction(commandement);
    
    // Afficher l'ordre AVANT le mélange
    std::cout << "\nOrdre AVANT le mélange :" << std::endl;
    const auto& actionsAvant = marcheTestMix.getStackActions();
    for (size_t i = 0; i < actionsAvant.size(); ++i) {
        std::cout << "  [" << i << "] " << actionsAvant[i]->getNom() << std::endl;
    }
    
    // Effectuer le mélange
    std::cout << "\n--- Mélange en cours ---" << std::endl;
    marcheTestMix.melangeStackActionEtChampion();
    
    // Afficher l'ordre APRÈS le mélange
    std::cout << "\nOrdre APRÈS le mélange :" << std::endl;
    const auto& actionsApres = marcheTestMix.getStackActions();
    for (size_t i = 0; i < actionsApres.size(); ++i) {
        std::cout << "  [" << i << "] " << actionsApres[i]->getNom() << std::endl;
    }
    
    std::cout << "\n=== Fin du test de mélange ===" << std::endl;
}

void testMiseAJourActionsVendables() {
    std::cout << "\n=== Test de MiseAJourActionsVendables ===" << std::endl;
    
    // Créer un marché avec des actions pour le test
    Marche marcheTest;
    marcheTest.addStackAction(new Action(Faction::FactionJaune, "Test1", 1, {Effet(1, OR)}, {}, {},{} ,{}, {}));
    marcheTest.addStackAction(new Action(Faction::FactionBleu, "Test2", 2, {Effet(2, OR)}, {}, {},{} ,{}, {}));
    marcheTest.addStackAction(new Action(Faction::FactionRouge, "Test3", 3, {Effet(3, OR)}, {}, {},{} ,{}, {}));
    marcheTest.addStackAction(new Action(Faction::FactionVert, "Test4", 4, {Effet(4, OR)}, {}, {},{} ,{}, {}));
    marcheTest.addStackAction(new Action(Faction::FactionJaune, "Test5", 5, {Effet(5, OR)}, {}, {},{} ,{}, {}));
    
    // Afficher l'état initial des actions vendables
    std::cout << "\nActions vendables AVANT mise à jour :" << std::endl;
    const auto& vendablesAvant = marcheTest.getActionsVendables();
    if (vendablesAvant.empty()) {
        std::cout << "  Aucune action vendable" << std::endl;
    } else {
        for (size_t i = 0; i < vendablesAvant.size(); ++i) {
            std::cout << "  [" << i << "] " << vendablesAvant[i]->getNom() << std::endl;
        }
    }
    
    // Mettre à jour les actions vendables (prendre 3 actions de la stack)
    std::cout << "\n--- Mise à jour des actions vendables (3 actions) ---" << std::endl;
    marcheTest.MiseAJourActionsVendables(3);
    
    // Afficher les actions vendables après mise à jour
    std::cout << "\nActions vendables APRÈS mise à jour :" << std::endl;
    const auto& vendablesApres = marcheTest.getActionsVendables();
    for (size_t i = 0; i < vendablesApres.size(); ++i) {
        std::cout << "  [" << i << "] " << vendablesApres[i]->getNom() << std::endl;
    }
    
    // Afficher l'état de la stack après prélèvement
    std::cout << "\nStack restante après prélèvement :" << std::endl;
    const auto& stackRestante = marcheTest.getStackActions();
    std::cout << "  Nombre d'actions restantes : " << stackRestante.size() << std::endl;
    
    std::cout << "\n=== Fin du test de MiseAJourActionsVendables ===" << std::endl;
}

void testEffetTextuel() {
    std::cout << "\n=== Test des EffetTextuel ===" << std::endl;
    
    // Instancier un effet textuel avec id=1 et description "Piocher une carte"
    EffetTextuel effetPioche(1, "Piocher une carte");
    
    std::cout << "Effet textuel créé :" << std::endl;
    std::cout << "  ID: " << effetPioche.getId() << std::endl;
    std::cout << "  Description: " << effetPioche.toString() << std::endl;
    
    // Créer un joueur de test
    Joueur joueurTest;
    joueurTest.setPointDeVie(20);
    
    // Créer une pioche avec quelques cartes pour le test
    Pioche piocheTest;
    piocheTest.addCarte(new CarteDeBase("Carte Test 1", {Effet(1, OR)}));
    piocheTest.addCarte(new CarteDeBase("Carte Test 2", {Effet(2, DEGAT)}));
    piocheTest.addCarte(new CarteDeBase("Carte Test 3", {Effet(1, SOIN)}));
    joueurTest.setPioche(piocheTest);
    
    // Afficher l'état AVANT l'utilisation de l'effet textuel
    std::cout << "\n--- État AVANT l'utilisation de l'effet textuel ---" << std::endl;
    std::cout << "Main du joueur : " << joueurTest.getMain().getCartes().size() << " cartes" << std::endl;
    if (!joueurTest.getMain().getCartes().empty()) {
        for (size_t i = 0; i < joueurTest.getMain().getCartes().size(); ++i) {
            std::cout << "  - " << joueurTest.getMain().getCartes()[i]->getNom() << std::endl;
        }
    } else {
        std::cout << "  (main vide)" << std::endl;
    }
    
    std::cout << "Pioche du joueur : " << joueurTest.getPioche().getCartes().size() << " cartes" << std::endl;
    if (!joueurTest.getPioche().getCartes().empty()) {
        for (size_t i = 0; i < joueurTest.getPioche().getCartes().size(); ++i) {
            std::cout << "  - " << joueurTest.getPioche().getCartes()[i]->getNom() << std::endl;
        }
    } else {
        std::cout << "  (pioche vide)" << std::endl;
    }
    
    // Utiliser l'effet textuel via handleIdEffetTextuel
    std::cout << "\n--- Utilisation de l'effet textuel ---" << std::endl;
    EffetTextuel::handleIdEffetTextuel(effetPioche.getId(), joueurTest);
    
    // Afficher l'état APRÈS l'utilisation de l'effet textuel
    std::cout << "\n--- État APRÈS l'utilisation de l'effet textuel ---" << std::endl;
    std::cout << "Main du joueur : " << joueurTest.getMain().getCartes().size() << " cartes" << std::endl;
    if (!joueurTest.getMain().getCartes().empty()) {
        for (size_t i = 0; i < joueurTest.getMain().getCartes().size(); ++i) {
            std::cout << "  - " << joueurTest.getMain().getCartes()[i]->getNom() << std::endl;
        }
    } else {
        std::cout << "  (main vide)" << std::endl;
    }
    
    std::cout << "Pioche du joueur : " << joueurTest.getPioche().getCartes().size() << " cartes" << std::endl;
    if (!joueurTest.getPioche().getCartes().empty()) {
        for (size_t i = 0; i < joueurTest.getPioche().getCartes().size(); ++i) {
            std::cout << "  - " << joueurTest.getPioche().getCartes()[i]->getNom() << std::endl;
        }
    } else {
        std::cout << "  (pioche vide)" << std::endl;
    }
    
    std::cout << "\n=== Fin du test des EffetTextuel ===" << std::endl;
}

void testDiscardOpponentCard() {
    std::cout << "\n=== Test de discardOpponentCard ===" << std::endl;
    
    // Instancier un effet textuel avec id=2 et description appropriée
    EffetTextuel effetDefausse(2, "Défausse l'une des cartes que l'adversaire a en main");
    
    std::cout << "Effet textuel créé :" << std::endl;
    std::cout << "  ID: " << effetDefausse.getId() << std::endl;
    std::cout << "  Description: " << effetDefausse.toString() << std::endl;
    
    // Créer deux joueurs : un adversaire avec des cartes en main
    Joueur adversaire;
    adversaire.setPointDeVie(20);
    
    // Donner des cartes à l'adversaire
    MainJoueur mainAdversaire;
    mainAdversaire.addCarte(new CarteDeBase("Carte Adversaire 1", {Effet(1, OR)}));
    mainAdversaire.addCarte(new CarteDeBase("Carte Adversaire 2", {Effet(2, DEGAT)}));
    mainAdversaire.addCarte(new CarteDeBase("Carte Adversaire 3", {Effet(1, SOIN)}));
    adversaire.setMain(mainAdversaire);
    
    // Afficher l'état AVANT l'utilisation de l'effet textuel
    std::cout << "\n--- État AVANT l'effet de défausse ---" << std::endl;
    std::cout << "Main de l'adversaire : " << adversaire.getMain().getCartes().size() << " cartes" << std::endl;
    for (size_t i = 0; i < adversaire.getMain().getCartes().size(); ++i) {
        std::cout << "  - " << adversaire.getMain().getCartes()[i]->getNom() << std::endl;
    }
    std::cout << "Défausse de l'adversaire : " << adversaire.getDefausse().getCartes().size() << " cartes" << std::endl;
    
    // Utiliser l'effet textuel via handleIdEffetTextuel
    std::cout << "\n--- Utilisation de l'effet de défausse (choisir carte 1) ---" << std::endl;
    EffetTextuel::handleIdEffetTextuel(effetDefausse.getId(), adversaire);
    
    // Afficher l'état APRÈS l'utilisation de l'effet textuel
    std::cout << "\n--- État APRÈS l'effet de défausse ---" << std::endl;
    std::cout << "Main de l'adversaire : " << adversaire.getMain().getCartes().size() << " cartes" << std::endl;
    if (!adversaire.getMain().getCartes().empty()) {
        for (size_t i = 0; i < adversaire.getMain().getCartes().size(); ++i) {
            std::cout << "  - " << adversaire.getMain().getCartes()[i]->getNom() << std::endl;
        }
    } else {
        std::cout << "  (main vide)" << std::endl;
    }
    
    std::cout << "Défausse de l'adversaire : " << adversaire.getDefausse().getCartes().size() << " cartes" << std::endl;
    if (!adversaire.getDefausse().getCartes().empty()) {
        for (size_t i = 0; i < adversaire.getDefausse().getCartes().size(); ++i) {
            std::cout << "  - " << adversaire.getDefausse().getCartes()[i]->getNom() << std::endl;
        }
    } else {
        std::cout << "  (défausse vide)" << std::endl;
    }
    
    std::cout << "\n=== Fin du test de discardOpponentCard ===" << std::endl;
}

void testStunChampion() {
    std::cout << "\n=== Test de stunChampion ===" << std::endl;
    
    // Instancier un effet textuel avec id=3 et description appropriée
    EffetTextuel effetStun(3, "Étourdir un champion adversaire");
    
    std::cout << "Effet textuel créé :" << std::endl;
    std::cout << "  ID: " << effetStun.getId() << std::endl;
    std::cout << "  Description: " << effetStun.toString() << std::endl;
    
    // Créer un adversaire avec des champions
    Joueur adversaire;
    adversaire.setPointDeVie(20);
    
    // Créer des champions pour l'adversaire
    Champion* champion1 = new Champion("Champion Guerrier");
    champion1->setPointDeVie(5);
    champion1->setIsDefense(true);
    
    Champion* champion2 = new Champion("Champion Mage");
    champion2->setPointDeVie(3);
    champion2->setIsDefense(true);
    
    // Ajouter les champions à la stack de l'adversaire
    StackChampion stackAdversaire;
    stackAdversaire.push(champion1);
    stackAdversaire.push(champion2);
    adversaire.setStackChampion(stackAdversaire);
    
    // Afficher l'état AVANT l'utilisation de l'effet textuel
    std::cout << "\n--- État AVANT l'effet d'étourdissement ---" << std::endl;
    std::cout << "Champions de l'adversaire : " << adversaire.getStackChampion().getChampions().size() << " champions" << std::endl;
    auto championsAvant = adversaire.getStackChampion().getChampions();
    for (size_t i = 0; i < championsAvant.size(); ++i) {
        std::cout << "  - " << championsAvant[i]->getNom() 
                  << " (Défense: " << (championsAvant[i]->getIsDefense() ? "Oui" : "Non") << ")" << std::endl;
    }
    std::cout << "Défausse de l'adversaire : " << adversaire.getDefausse().getCartes().size() << " cartes" << std::endl;
    
    // Utiliser l'effet textuel stunChampion
    std::cout << "\n--- Utilisation de l'effet d'étourdissement (choisir champion 0) ---" << std::endl;
    EffetTextuel effet;
    effet.stunChampion(adversaire);
    
    // Afficher l'état APRÈS l'utilisation de l'effet textuel
    std::cout << "\n--- État APRÈS l'effet d'étourdissement ---" << std::endl;
    std::cout << "Champions de l'adversaire : " << adversaire.getStackChampion().getChampions().size() << " champions" << std::endl;
    auto championsApres = adversaire.getStackChampion().getChampions();
    if (!championsApres.empty()) {
        for (size_t i = 0; i < championsApres.size(); ++i) {
            std::cout << "  - " << championsApres[i]->getNom() 
                      << " (Défense: " << (championsApres[i]->getIsDefense() ? "Oui" : "Non") << ")" << std::endl;
        }
    } else {
        std::cout << "  (aucun champion restant)" << std::endl;
    }
    
    std::cout << "Défausse de l'adversaire : " << adversaire.getDefausse().getCartes().size() << " cartes" << std::endl;
    if (!adversaire.getDefausse().getCartes().empty()) {
        for (size_t i = 0; i < adversaire.getDefausse().getCartes().size(); ++i) {
            std::cout << "  - " << adversaire.getDefausse().getCartes()[i]->getNom() << std::endl;
        }
    }
    
    std::cout << "\n=== Fin du test de stunChampion ===" << std::endl;
}

void testDrawAndDiscard() {
    std::cout << "\n=== Test de drawAndDiscard ===" << std::endl;
    
    // Instancier un effet textuel avec id=4 et description appropriée
    EffetTextuel effetDrawDiscard(4, "Piocher une carte puis défausser une carte");
    
    std::cout << "Effet textuel créé :" << std::endl;
    std::cout << "  ID: " << effetDrawDiscard.getId() << std::endl;
    std::cout << "  Description: " << effetDrawDiscard.toString() << std::endl;
    
    // Créer un joueur de test
    Joueur joueurTest;
    joueurTest.setPointDeVie(20);
    
    // Donner quelques cartes en main au joueur
    MainJoueur mainTest;
    mainTest.addCarte(new CarteDeBase("Carte Main 1", {Effet(1, OR)}));
    mainTest.addCarte(new CarteDeBase("Carte Main 2", {Effet(2, DEGAT)}));
    joueurTest.setMain(mainTest);
    
    // Créer une pioche avec des cartes
    Pioche piocheTest;
    piocheTest.addCarte(new CarteDeBase("Carte Pioche 1", {Effet(1, SOIN)}));
    piocheTest.addCarte(new CarteDeBase("Carte Pioche 2", {Effet(3, OR)}));
    joueurTest.setPioche(piocheTest);
    
    // Afficher l'état AVANT l'utilisation de l'effet textuel
    std::cout << "\n--- État AVANT drawAndDiscard ---" << std::endl;
    std::cout << "Main du joueur : " << joueurTest.getMain().getCartes().size() << " cartes" << std::endl;
    for (size_t i = 0; i < joueurTest.getMain().getCartes().size(); ++i) {
        std::cout << "  - " << joueurTest.getMain().getCartes()[i]->getNom() << std::endl;
    }
    std::cout << "Pioche du joueur : " << joueurTest.getPioche().getCartes().size() << " cartes" << std::endl;
    std::cout << "Défausse du joueur : " << joueurTest.getDefausse().getCartes().size() << " cartes" << std::endl;
    
    // Utiliser l'effet textuel drawAndDiscard
    std::cout << "\n--- Utilisation de drawAndDiscard (piocher puis défausser carte 1) ---" << std::endl;
    EffetTextuel::handleIdEffetTextuel(effetDrawDiscard.getId(), joueurTest);
    
    // Afficher l'état APRÈS l'utilisation de l'effet textuel
    std::cout << "\n--- État APRÈS drawAndDiscard ---" << std::endl;
    std::cout << "Main du joueur : " << joueurTest.getMain().getCartes().size() << " cartes" << std::endl;
    if (!joueurTest.getMain().getCartes().empty()) {
        for (size_t i = 0; i < joueurTest.getMain().getCartes().size(); ++i) {
            std::cout << "  - " << joueurTest.getMain().getCartes()[i]->getNom() << std::endl;
        }
    } else {
        std::cout << "  (main vide)" << std::endl;
    }
    
    std::cout << "Pioche du joueur : " << joueurTest.getPioche().getCartes().size() << " cartes" << std::endl;
    std::cout << "Défausse du joueur : " << joueurTest.getDefausse().getCartes().size() << " cartes" << std::endl;
    if (!joueurTest.getDefausse().getCartes().empty()) {
        for (size_t i = 0; i < joueurTest.getDefausse().getCartes().size(); ++i) {
            std::cout << "  - " << joueurTest.getDefausse().getCartes()[i]->getNom() << std::endl;
        }
    }
    
    std::cout << "\n=== Fin du test de drawAndDiscard ===" << std::endl;
}

void testPeuxActiverCombo() {
    std::cout << "\n=== Test de peuxActiverCombo ===" << std::endl;
    
    // Créer un joueur de test
    Joueur joueurTest;
    joueurTest.setPointDeVie(20);
    
    // Créer des actions de différentes factions
    Action* actionJaune1 = new Action(Faction::FactionJaune, "Taxation", 1, {Effet(2, OR)}, {}, {}, {}, {Effet(6, SOIN)}, {});
    Action* actionJaune2 = new Action(Faction::FactionJaune, "Recrutement", 3, {Effet(1, OR)}, {}, {}, {}, {Effet(2, SOIN)}, {});
    Action* actionBleu1 = new Action(Faction::FactionBleu, "Pot-de-Vin", 1, {Effet(2, OR)}, {}, {}, {}, {Effet(4, DEGAT)}, {});
    Action* actionRouge1 = new Action(Faction::FactionRouge, "Magie Noire", 2, {Effet(3, DEGAT)}, {}, {}, {}, {Effet(2, DEGAT)}, {});
    
    // Créer une main avec ces actions
    MainJoueur mainTest;
    mainTest.addCarte(actionJaune1);
    mainTest.addCarte(actionJaune2);
    mainTest.addCarte(actionBleu1);
    mainTest.addCarte(actionRouge1);
    joueurTest.setMain(mainTest);
    
    // Afficher l'état AVANT activation des combos
    std::cout << "\n--- État AVANT peuxActiverCombo ---" << std::endl;
    std::cout << "Cartes en main :" << std::endl;
    for (size_t i = 0; i < joueurTest.getMain().getCartes().size(); ++i) {
        Action* action = dynamic_cast<Action*>(joueurTest.getMain().getCartes()[i]);
        if (action != nullptr) {
            std::string factionName;
            switch(action->getFaction()) {
                case Faction::FactionJaune: factionName = "Impériale"; break;
                case Faction::FactionBleu: factionName = "Guilde"; break;
                case Faction::FactionRouge: factionName = "Nécros"; break;
                case Faction::FactionVert: factionName = "Sauvage"; break;
            }
            std::cout << "  - " << action->getNom() << " (Faction: " << factionName 
                      << ", Combo: " << (action->getPeutFaireCombo() ? "Activé" : "Désactivé") << ")" << std::endl;
        }
    }
    
    // Activer la fonction peuxActiverCombo
    std::cout << "\n--- Activation de peuxActiverCombo ---" << std::endl;
    joueurTest.peuxActiverCombo();
    
    // Afficher l'état APRÈS activation des combos
    std::cout << "\n--- État APRÈS peuxActiverCombo ---" << std::endl;
    std::cout << "Cartes en main :" << std::endl;
    for (size_t i = 0; i < joueurTest.getMain().getCartes().size(); ++i) {
        Action* action = dynamic_cast<Action*>(joueurTest.getMain().getCartes()[i]);
        if (action != nullptr) {
            std::string factionName;
            switch(action->getFaction()) {
                case Faction::FactionJaune: factionName = "Impériale"; break;
                case Faction::FactionBleu: factionName = "Guilde"; break;
                case Faction::FactionRouge: factionName = "Nécros"; break;
                case Faction::FactionVert: factionName = "Sauvage"; break;
            }
            std::cout << "  - " << action->getNom() << " (Faction: " << factionName 
                      << ", Combo: " << (action->getPeutFaireCombo() ? "Activé" : "Désactivé") << ")" << std::endl;
        }
    }
    
    std::cout << "\n=== Fin du test de peuxActiverCombo ===" << std::endl;
}