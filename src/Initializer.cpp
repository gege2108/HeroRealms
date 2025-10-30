#include "Initializer.h"
#include "Faction.h"
#include "Effet.h"
#include "EffetTextuel.h"

Plateau Initializer::initializePlateau() {
    Joueur joueur1 = initializeJoueur();
    Joueur joueur2 = initializeJoueur();
    Marche marche = initializeMarche();
    ZoneDeSacrifice zoneDeSacrifice;
    Plateau plateau(joueur1, joueur2, marche, zoneDeSacrifice);
    
    return plateau;
}

Joueur Initializer::initializeJoueur() {
    // Créer un joueur avec 50 PV et 0 argent
    Joueur joueur;
    joueur.setPointDeVie(50);
    joueur.setArgent(0);
    
    // Créer la main de départ (5 cartes)
    MainJoueur main;
    auto cartesDeBase = createCartesDeBase();
    
    // Donner 5 cartes en main
    for (int i = 0; i < 5 && i < (int)cartesDeBase.size(); ++i) {
        main.addCarte(cartesDeBase[i]);
    }
    joueur.setMain(main);
    
    // Mettre le reste dans la pioche
    Pioche pioche;
    for (size_t i = 5; i < cartesDeBase.size(); ++i) {
        pioche.addCarte(cartesDeBase[i]);
    }
    joueur.setPioche(pioche);
    
    // Défausse vide
    Defausse defausse;
    joueur.setDefausse(defausse);
    
    // Stack de champions vide
    StackChampion stackChampion;
    joueur.setStackChampion(stackChampion);
    
    return joueur;
}

Marche Initializer::initializeMarche() {
    // Créer les actions et champions
    auto actions = createActions();
    auto champions = createChampions();
    auto gemmes = createGemmesDeFeu();
    
    // Combiner actions et champions dans une seule stack
    std::vector<Action*> stackComplete = actions;
    for (auto* champion : champions) {
        stackComplete.push_back(champion);
    }
    
    // Créer le marché
    Marche marche(stackComplete, gemmes);
    
    // Mélanger la stack
    marche.melangeStackActionEtChampion();
    
    // Mettre 5 cartes en vente
    marche.MiseAJourActionsVendables(5);
    
    return marche;
}

std::vector<CarteDeBase*> Initializer::createCartesDeBase() {
    std::vector<CarteDeBase*> cartes;
    
    // 8 Cartes "Rubis" (1 or)
    for (int i = 0; i < 8; ++i) {
        cartes.push_back(new CarteDeBase("Rubis", {Effet(1, OR)}));
    }
    
    // 2 Cartes "Dague" (1 dégât)
    for (int i = 0; i < 2; ++i) {
        cartes.push_back(new CarteDeBase("Dague", {Effet(1, DEGAT)}));
    }
    
    return cartes;
}

std::vector<Action*> Initializer::createActions() {
    std::vector<Action*> actions;
    
    // Actions Faction Impériale (Jaune)
    actions.push_back(new Action(Faction::FactionJaune, "Taxation", 1,
        {Effet(2, OR)}, {},
        {}, {},
        {Effet(6, SOIN)}, {}));
    
    actions.push_back(new Action(Faction::FactionJaune, "Recrutement", 3,
        {Effet(1, OR)}, {Effet(2, DEGAT)},
        {}, {},
        {Effet(2, SOIN)}, {}));
    
    // Actions Faction Guilde (Bleu)
    actions.push_back(new Action(Faction::FactionBleu, "Pot-de-Vin", 1,
        {Effet(2, OR)}, {},
        {}, {},
        {Effet(4, DEGAT)}, {}));
    
    actions.push_back(new Action(Faction::FactionBleu, "Intimidation", 2,
        {Effet(5, DEGAT)}, {},
        {}, {},
        {Effet(3, OR)}, {}));
    
    // Actions Faction Nécros (Rouge)
    actions.push_back(new Action(Faction::FactionRouge, "Magie Noire", 2,
        {Effet(3, DEGAT)}, {Effet(2, OR)},
        {EffetTextuel(2, "Défausser adversaire")}, {},
        {Effet(5, DEGAT)}, {}));
    
    // Actions Faction Sauvage (Vert)
    actions.push_back(new Action(Faction::FactionVert, "Charge Sauvage", 2,
        {Effet(4, DEGAT)}, {},
        {}, {},
        {Effet(6, DEGAT)}, {}));
    
    return actions;
}

std::vector<Champion*> Initializer::createChampions() {
    std::vector<Champion*> champions;
    
    // Champions Faction Impériale
    champions.push_back(new Champion(Faction::FactionJaune, "Garde Impérial", 4,
        {Effet(3, DEGAT)}, {Effet(2, SOIN)},
        {}, {},
        {Effet(5, DEGAT), Effet(3, SOIN)}, {},
        5, true, true));
    
    // Champions Faction Guilde
    champions.push_back(new Champion(Faction::FactionBleu, "Assassin de Guilde", 5,
        {Effet(4, DEGAT)}, {},
        {EffetTextuel(3, "Étourdir champion")}, {},
        {Effet(6, DEGAT)}, {},
        4, false, false));
    
    // Champions Faction Nécros
    champions.push_back(new Champion(Faction::FactionRouge, "Nécromant", 6,
        {Effet(2, DEGAT)}, {Effet(3, SOIN)},
        {EffetTextuel(1, "Piocher une carte")}, {},
        {Effet(4, DEGAT), Effet(2, SOIN)}, {},
        6, false, true));
    
    return champions;
}

std::vector<GemmeDeFeu*> Initializer::createGemmesDeFeu(int nombre) {
    std::vector<GemmeDeFeu*> gemmes;
    
    for (int i = 0; i < nombre; ++i) {
        gemmes.push_back(new GemmeDeFeu());
    }
    
    return gemmes;
}
