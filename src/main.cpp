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

int main() {
   // runTests();

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
    Plateau plateau; // utilise constructeur par défaut
    plateau.setJoueur1(j1);
    plateau.setJoueur2(j2);

    // Créer un marché avec 100 cartes GemmeDeFeu
    Marche marche;
    for (int i = 0; i < 100; ++i) {
        marche.addGemme(new GemmeDeFeu());
    }
    plateau.setMarche(marche);
    

    GemmeDeFeu gemmeTest("Gemme de Feu Test");
    std::cout << "Test de la gemme de feu : " << gemmeTest.toString() << std::endl;
    std::cout << "Prix de la gemme de feu : " << gemmeTest.getPrix() << std::endl;
    std::cout << "Effets basiques de la gemme de feu : " << std::endl;
    for (const auto& effet : gemmeTest.getEffetsBasiqueChoix1()) {
        std::cout << " - " << effet.toString() << std::endl;
    }

    Effet effetGemmeTest = gemmeTest.getEffetsBasiqueChoix1()[0];
    std::cout << "Utilisation de l'effet d'or de la gemme de feu test : " << effetGemmeTest.toString() << std::endl;

    // Lancer la boucle de jeu (utilise std::cin pour les choix)
    plateau.run(plateau);

    return 0;
}
