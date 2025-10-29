#include <iostream>
#include <vector>

//extern void runTests();

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

int main() {
   // runTests();

    // Test du mélange des actions dans le marché
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

    // Test de la fonction MiseAJourActionsVendables
    std::cout << "\n=== Test de MiseAJourActionsVendables ===" << std::endl;
    
    // Afficher l'état initial des actions vendables
    std::cout << "\nActions vendables AVANT mise à jour :" << std::endl;
    const auto& vendablesAvant = marcheTestMix.getActionsVendables();
    if (vendablesAvant.empty()) {
        std::cout << "  Aucune action vendable" << std::endl;
    } else {
        for (size_t i = 0; i < vendablesAvant.size(); ++i) {
            std::cout << "  [" << i << "] " << vendablesAvant[i]->getNom() << std::endl;
        }
    }
    
    // Mettre à jour les actions vendables (prendre 5 actions de la stack)
    std::cout << "\n--- Mise à jour des actions vendables (5 actions) ---" << std::endl;
    marcheTestMix.MiseAJourActionsVendables(5);
    
    // Afficher les actions vendables après mise à jour
    std::cout << "\nActions vendables APRÈS mise à jour :" << std::endl;
    const auto& vendablesApres = marcheTestMix.getActionsVendables();
    for (size_t i = 0; i < vendablesApres.size(); ++i) {
        std::cout << "  [" << i << "] " << vendablesApres[i]->getNom() << std::endl;
    }
    
    // Afficher l'état de la stack après prélèvement
    std::cout << "\nStack restante après prélèvement :" << std::endl;
    const auto& stackRestante = marcheTestMix.getStackActions();
    std::cout << "  Nombre d'actions restantes : " << stackRestante.size() << std::endl;
    
    std::cout << "\n=== Fin du test de MiseAJourActionsVendables ===" << std::endl;

    // Test des fonctions EffetTextuel
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

    // Créer deux joueurs et initialiser les PV à 30
    Joueur j1;
    Joueur j2;
    j1.setPointDeVie(30);
    j2.setPointDeVie(30);

    // Préparer une main de 5 cartes de base personnalisées pour chaque joueur
    MainJoueur main1;
    MainJoueur main2;

    // exemples d'effets réutilisables
    Effet degatPetite(3, DEGAT);
    Effet degatMoyen(5, DEGAT);
    Effet soinPetit(2, SOIN);
    Effet orPetit(2, OR);  // Nouvel effet pour donner de l'or
    Effet orMoyen(3, OR);

    // main joueur 1 (création directe de CarteDeBase avec nom + effets)
    main1.addCarte(new CarteDeBase("Soin & Or", {soinPetit, orPetit}));
    main1.addCarte(new CarteDeBase("Soin & Or", {soinPetit, orPetit}));
    main1.addCarte(new CarteDeBase("Soin & Or", {soinPetit, orPetit}));
    main1.addCarte(new CarteDeBase("Trésor", {orMoyen}));
    main1.addCarte(new CarteDeBase("Soin & Or", {soinPetit, orPetit}));

    // main joueur 2 (différente composition avec plus de cartes d'or)
    main2.addCarte(new CarteDeBase("Soin & Or", {soinPetit, orPetit}));
    main2.addCarte(new CarteDeBase("Soin & Or", {soinPetit, orPetit}));
    main2.addCarte(new CarteDeBase("Soin & Or", {soinPetit, orPetit}));
    main2.addCarte(new CarteDeBase("Trésor", {orMoyen}));
    main2.addCarte(new CarteDeBase("Soin & Or", {soinPetit, orPetit}));


    // Préparer une pioche de 23 cartes de base personnalisées pour chaque joueur
    Pioche pioche1;
    Pioche pioche2;

    // Remplir les pioches avec une variété de cartes (exemples)
    for (int i = 0; i < 10; ++i) {
        pioche1.addCarte(new CarteDeBase("Frappe légère", {degatPetite}));
        pioche2.addCarte(new CarteDeBase("Frappe légère", {degatPetite}));
    }
    for (int i = 0; i < 8; ++i) {
        pioche1.addCarte(new CarteDeBase("Coup moyen", {degatMoyen}));
        pioche2.addCarte(new CarteDeBase("Coup moyen", {degatMoyen}));
    }
    for (int i = 0; i < 5; ++i) {
        pioche1.addCarte(new CarteDeBase("Soin mineur", {soinPetit}));
        pioche2.addCarte(new CarteDeBase("Soin mineur", {soinPetit}));
    }

    // Assigner main et pioche aux joueurs
    j1.setMain(main1);
    j1.setPioche(pioche1);

    j2.setMain(main2);
    j2.setPioche(pioche2);

    // Construire un plateau et y assigner les joueurs
    Plateau plateau;
    plateau.setJoueur1(j1);
    plateau.setJoueur2(j2);

    // Créer un marché avec 100 cartes GemmeDeFeu
    Marche marche;
    for (int i = 0; i < 16; ++i) {
        marche.addGemme(new GemmeDeFeu());
    }
    
    // Ajouter 3 exemplaires de Taxation au marché (comme spécifié)
    for (int i = 0; i < 3; ++i) {
        marche.addStackAction(new Action(
            Faction::FactionJaune,
            "Taxation",
            1,
            { Effet(2, OR) },
            {},
            {},
            {},
            { Effet(6, SOIN) },
            {}
        ));
    }


    
    plateau.setMarche(marche);
    
/*
    GemmeDeFeu gemmeTest("Gemme de Feu Test");
    std::cout << "Test de la gemme de feu : " << gemmeTest.toString() << std::endl;
    std::cout << "Prix de la gemme de feu : " << gemmeTest.getPrix() << std::endl;
    std::cout << "Effets basiques de la gemme de feu : " << std::endl;
    for (const auto& effet : gemmeTest.getEffetsBasiqueChoix1()) {
        std::cout << " - " << effet.toString() << std::endl;
    }

    Effet effetGemmeTest = gemmeTest.getEffetsBasiqueChoix1()[0];
    std::cout << "Utilisation de l'effet d'or de la gemme de feu test : " << effetGemmeTest.toString() << std::endl;
*/
    // Lancer la boucle de jeu (utilise std::cin pour les choix)
    //plateau.run(plateau);

    return 0;
}
