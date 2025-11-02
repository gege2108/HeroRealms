#include "Initializer.h"
#include "Faction.h"
#include "Effet.h"
#include "EffetTextuel.h"

void Initializer::initializePlateauRef(Plateau& plateau) {
    std::cout << "DEBUG: Début initializePlateauRef" << std::endl;
    
    std::cout << "DEBUG: Création des effets" << std::endl;
    Effet soinPetit(2, SOIN);
    Effet orPetit(2, OR);
    Effet degatPetit(3, DEGAT);

    std::cout << "DEBUG: Initialisation Joueur1" << std::endl;
    // Créer directement dans le plateau via getJoueur1()
    plateau.getJoueur1().setPointDeVie(50);
    plateau.getJoueur1().setArgent(0);
    plateau.getJoueur1().setDegatsStockes(0);
    
    // Créer la main du joueur 1 directement
    for (int i = 0; i < 5; ++i) {
        plateau.getJoueur1().getMain().addCarte(new CarteDeBase("Soin & Or", {soinPetit, orPetit}));
    }
    
    // Créer la pioche du joueur 1 directement
    for (int i = 0; i < 5; ++i) {
        plateau.getJoueur1().getPioche().addCarte(new CarteDeBase("Frappe", {degatPetit}));
    }

    std::cout << "DEBUG: Initialisation Joueur2" << std::endl;
    // Même chose pour joueur 2
    plateau.getJoueur2().setPointDeVie(50);
    plateau.getJoueur2().setArgent(0);
    plateau.getJoueur2().setDegatsStockes(0);
    
    for (int i = 0; i < 5; ++i) {
        plateau.getJoueur2().getMain().addCarte(new CarteDeBase("Soin & Or", {soinPetit, orPetit}));
    }
    
    for (int i = 0; i < 5; ++i) {
        plateau.getJoueur2().getPioche().addCarte(new CarteDeBase("Frappe", {degatPetit}));
    }

    std::cout << "DEBUG: Création du marché" << std::endl;
    
    // Ajouter les gemmes directement au marché du plateau
    for (int i = 0; i < 10; ++i) {
        plateau.getMarche().addGemme(new GemmeDeFeu());
    }
    
    std::cout << "DEBUG: Ajout d'actions au marché" << std::endl;
    
    // Ajouter quelques actions
    for (int i = 0; i < 5; ++i) {
        plateau.getMarche().addStackAction(new Action(
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

    std::cout << "DEBUG: Mise à jour des actions vendables" << std::endl;
    plateau.getMarche().MiseAJourActionsVendables();
    
    std::cout << "DEBUG: Fin initializePlateauRef" << std::endl;
}

// Gardez l'ancienne méthode pour compatibilité
Plateau Initializer::initializePlateau() {
    Plateau plateau;
    initializePlateauRef(plateau);
    return plateau;
}

Joueur Initializer::initializeJoueur() {
    // Créer un joueur avec 50 PV et 0 argent
    Joueur joueur;
    joueur.setPointDeVie(50);
    joueur.setArgent(0);
    joueur.setDegatsStockes(0);
    
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
    // Créer et ajouter les gemmes de feu (spécifier le nombre)
    auto gemmes = createGemmesDeFeu(16);
    
    // Créer les actions et champions
    auto actions = createActions();
    auto champions = createChampions();
    
    // Combiner actions et champions dans une seule stack
    std::vector<Action*> stackComplete = actions;
    for (auto* champion : champions) {
        stackComplete.push_back(champion);
    }
    
    // Créer le marché avec la stack complète et les gemmes
    Marche marche(stackComplete, gemmes);
    
    // Mélanger la stack
    marche.melangeStackActionEtChampion();
    
    // Mettre 5 cartes en vente
    marche.InitialiserActionsVendables(5);
    
    return marche;
}

std::vector<CarteDeBase*> Initializer::createCartesDeBase() {
    std::vector<CarteDeBase*> cartes;
    
    // 8 Cartes "Rubis" (1 or)
    for (int i = 0; i < 8; ++i) {
        cartes.push_back(new CarteDeBase("Rubis", {Effet(8, OR)}));
    }
    
    // 2 Cartes "Dague" (1 dégât)
    for (int i = 0; i < 2; ++i) {
        cartes.push_back(new CarteDeBase("Dague", {Effet(1, DEGAT)}));
    }
    
    return cartes;
}

std::vector<Action*> Initializer::createActions() {
    std::vector<Action*> actions;
    
    // Actions Faction Impériale (Jaune) - 6 actions
    actions.push_back(new Action(Faction::FactionJaune, "Taxation", 1,
        {Effet(2, OR)}, {},
        {}, {},
        {Effet(6, SOIN)}, {}));
    
    actions.push_back(new Action(Faction::FactionJaune, "Recrutement", 3,
        {Effet(1, OR)}, {Effet(2, DEGAT)},
        {}, {},
        {Effet(2, SOIN)}, {}));
    
    actions.push_back(new Action(Faction::FactionJaune, "Commandement", 2,
        {Effet(3, DEGAT)}, {},
        {}, {},
        {Effet(1, OR)}, {}));
    
    actions.push_back(new Action(Faction::FactionJaune, "Diplomatie", 4,
        {Effet(2, OR), Effet(3, SOIN)}, {},
        {EffetTextuel(1, "Piocher une carte")}, {},
        {Effet(4, OR), Effet(5, SOIN)}, {}));
    
    actions.push_back(new Action(Faction::FactionJaune, "Garde Royale", 5,
        {Effet(4, DEGAT)}, {Effet(6, SOIN)},
        {}, {},
        {Effet(6, DEGAT), Effet(4, SOIN)}, {}));
    
    actions.push_back(new Action(Faction::FactionJaune, "Trésor Impérial", 6,
        {Effet(5, OR)}, {},
        {}, {},
        {Effet(8, OR)}, {}));
    
    // Actions Faction Guilde (Bleu) - 6 actions
    actions.push_back(new Action(Faction::FactionBleu, "Pot-de-Vin", 1,
        {Effet(2, OR)}, {},
        {}, {},
        {Effet(4, DEGAT)}, {}));
    
    actions.push_back(new Action(Faction::FactionBleu, "Intimidation", 2,
        {Effet(5, DEGAT)}, {},
        {}, {},
        {Effet(3, OR)}, {}));
    
    actions.push_back(new Action(Faction::FactionBleu, "Espionnage", 3,
        {Effet(2, OR)}, {Effet(3, DEGAT)},
        {EffetTextuel(2, "Défausser adversaire")}, {},
        {Effet(4, OR), Effet(2, DEGAT)}, {}));
    
    actions.push_back(new Action(Faction::FactionBleu, "Contrat d'Assassin", 4,
        {Effet(6, DEGAT)}, {},
        {EffetTextuel(3, "Étourdir champion")}, {},
        {Effet(8, DEGAT)}, {}));
    
    actions.push_back(new Action(Faction::FactionBleu, "Maître Voleur", 5,
        {Effet(3, OR), Effet(2, DEGAT)}, {},
        {EffetTextuel(4, "Piocher puis défausser")}, {},
        {Effet(5, OR), Effet(4, DEGAT)}, {}));
    
    actions.push_back(new Action(Faction::FactionBleu, "Chef de Guilde", 7,
        {Effet(4, OR), Effet(4, DEGAT)}, {},
        {}, {},
        {Effet(6, OR), Effet(6, DEGAT)}, {}));
    
    // Actions Faction Nécros (Rouge) - 6 actions
    actions.push_back(new Action(Faction::FactionRouge, "Magie Noire", 2,
        {Effet(3, DEGAT)}, {Effet(2, OR)},
        {EffetTextuel(2, "Défausser adversaire")}, {},
        {Effet(5, DEGAT)}, {}));
    
    actions.push_back(new Action(Faction::FactionRouge, "Drain de Vie", 3,
        {Effet(2, DEGAT), Effet(2, SOIN)}, {},
        {}, {},
        {Effet(4, DEGAT), Effet(4, SOIN)}, {}));
    
    actions.push_back(new Action(Faction::FactionRouge, "Malédiction", 4,
        {Effet(4, DEGAT)}, {},
        {EffetTextuel(2, "Défausser adversaire")}, {},
        {Effet(6, DEGAT)}, {}));
    
    actions.push_back(new Action(Faction::FactionRouge, "Invocation", 5,
        {Effet(3, DEGAT)}, {Effet(1, OR)},
        {EffetTextuel(1, "Piocher une carte")}, {},
        {Effet(5, DEGAT), Effet(2, OR)}, {}));
    
    actions.push_back(new Action(Faction::FactionRouge, "Rituel Sanglant", 6,
        {Effet(6, DEGAT)}, {},
        {}, {},
        {Effet(8, DEGAT), Effet(3, SOIN)}, {}));
    
    actions.push_back(new Action(Faction::FactionRouge, "Nécrose", 8,
        {Effet(5, DEGAT), Effet(4, SOIN)}, {},
        {EffetTextuel(3, "Étourdir champion")}, {},
        {Effet(8, DEGAT), Effet(6, SOIN)}, {}));
    
    // Actions Faction Sauvage (Vert) - 6 actions
    actions.push_back(new Action(Faction::FactionVert, "Charge Sauvage", 2,
        {Effet(4, DEGAT)}, {},
        {}, {},
        {Effet(6, DEGAT)}, {}));
    
    actions.push_back(new Action(Faction::FactionVert, "Rage Primitive", 3,
        {Effet(5, DEGAT)}, {},
        {}, {},
        {Effet(7, DEGAT)}, {}));
    
    actions.push_back(new Action(Faction::FactionVert, "Guérison Naturelle", 2,
        {Effet(1, OR), Effet(4, SOIN)}, {},
        {}, {},
        {Effet(2, OR), Effet(6, SOIN)}, {}));
    
    actions.push_back(new Action(Faction::FactionVert, "Instinct Animal", 4,
        {Effet(3, DEGAT), Effet(2, SOIN)}, {},
        {EffetTextuel(1, "Piocher une carte")}, {},
        {Effet(5, DEGAT), Effet(3, SOIN)}, {}));
    
    actions.push_back(new Action(Faction::FactionVert, "Meute de Loups", 5,
        {Effet(6, DEGAT)}, {},
        {}, {},
        {Effet(9, DEGAT)}, {}));
    
    actions.push_back(new Action(Faction::FactionVert, "Druide Ancien", 7,
        {Effet(2, OR), Effet(3, DEGAT), Effet(4, SOIN)}, {},
        {EffetTextuel(4, "Piocher puis défausser")}, {},
        {Effet(4, OR), Effet(5, DEGAT), Effet(6, SOIN)}, {}));
    
    return actions;
}

std::vector<Champion*> Initializer::createChampions() {
    std::vector<Champion*> champions;
    
    // Champions Faction Impériale (3 champions)
    champions.push_back(new Champion(Faction::FactionJaune, "Garde Impérial", 4,
        {Effet(3, DEGAT)}, {Effet(2, SOIN)},
        {}, {},
        {Effet(5, DEGAT), Effet(3, SOIN)}, {},
        5, true, true));
    
    champions.push_back(new Champion(Faction::FactionJaune, "Paladin Royal", 6,
        {Effet(2, DEGAT), Effet(3, SOIN)}, {},
        {}, {},
        {Effet(4, DEGAT), Effet(5, SOIN)}, {},
        7, true, true));
    
    champions.push_back(new Champion(Faction::FactionJaune, "Général Impérial", 8,
        {Effet(5, DEGAT), Effet(2, OR)}, {},
        {EffetTextuel(1, "Piocher une carte")}, {},
        {Effet(7, DEGAT), Effet(4, OR)}, {},
        6, false, true));
    
    // Champions Faction Guilde (3 champions)
    champions.push_back(new Champion(Faction::FactionBleu, "Assassin de Guilde", 5,
        {Effet(4, DEGAT)}, {},
        {EffetTextuel(3, "Étourdir champion")}, {},
        {Effet(6, DEGAT)}, {},
        4, false, false));
    
    champions.push_back(new Champion(Faction::FactionBleu, "Maître Espion", 7,
        {Effet(3, DEGAT), Effet(2, OR)}, {},
        {EffetTextuel(2, "Défausser adversaire")}, {},
        {Effet(5, DEGAT), Effet(3, OR)}, {},
        5, false, false));
    
    champions.push_back(new Champion(Faction::FactionBleu, "Seigneur des Voleurs", 9,
        {Effet(4, DEGAT), Effet(3, OR)}, {},
        {EffetTextuel(4, "Piocher puis défausser")}, {},
        {Effet(6, DEGAT), Effet(5, OR)}, {},
        6, false, true));
    
    // Champions Faction Nécros (3 champions)
    champions.push_back(new Champion(Faction::FactionRouge, "Nécromant", 6,
        {Effet(2, DEGAT)}, {Effet(3, SOIN)},
        {EffetTextuel(1, "Piocher une carte")}, {},
        {Effet(4, DEGAT), Effet(2, SOIN)}, {},
        6, false, true));
    
    champions.push_back(new Champion(Faction::FactionRouge, "Liche Ancienne", 8,
        {Effet(4, DEGAT), Effet(2, SOIN)}, {},
        {EffetTextuel(2, "Défausser adversaire")}, {},
        {Effet(6, DEGAT), Effet(4, SOIN)}, {},
        7, false, true));
    
    champions.push_back(new Champion(Faction::FactionRouge, "Seigneur Vampire", 10,
        {Effet(5, DEGAT), Effet(3, SOIN)}, {},
        {EffetTextuel(3, "Étourdir champion")}, {},
        {Effet(8, DEGAT), Effet(5, SOIN)}, {},
        8, false, true));
    
    // Champions Faction Sauvage (3 champions)
    champions.push_back(new Champion(Faction::FactionVert, "Chef de Clan", 5,
        {Effet(4, DEGAT), Effet(1, SOIN)}, {},
        {}, {},
        {Effet(6, DEGAT), Effet(2, SOIN)}, {},
        5, false, false));
    
    champions.push_back(new Champion(Faction::FactionVert, "Druide Suprême", 7,
        {Effet(2, DEGAT), Effet(4, SOIN)}, {},
        {EffetTextuel(1, "Piocher une carte")}, {},
        {Effet(4, DEGAT), Effet(6, SOIN)}, {},
        6, false, true));
    
    champions.push_back(new Champion(Faction::FactionVert, "Alpha des Loups", 9,
        {Effet(6, DEGAT)}, {},
        {EffetTextuel(4, "Piocher puis défausser")}, {},
        {Effet(9, DEGAT), Effet(3, SOIN)}, {},
        7, true, false));
    
    return champions;
}

std::vector<GemmeDeFeu*> Initializer::createGemmesDeFeu(int nombre) {
    std::vector<GemmeDeFeu*> gemmes;
    
    for (int i = 0; i < nombre; ++i) {
        gemmes.push_back(new GemmeDeFeu());
    }
    
    return gemmes;
}
