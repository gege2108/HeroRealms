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
#include "Game.h"


//TODO : changer l'implementation de sorte à ce que les degats d'attaques soient stockés par le joueur avant d'être utilise
//TODO : faire en sorte que le

int main() {
    // Exécuter tous les tests en une seule ligne
    //testAchatActionChampionNouveauFonctionnement();
    //testAchatActionChampion();
    


    // Créer deux joueurs et initialiser les PV à 30
    
    
    /* Joueur j1;
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
    
    
    */
   Plateau plateau;
    Initializer::initializePlateauRef(plateau);  // Initialisation par référence
    
    Game game(plateau);
    game.run();

    return 0;
}
