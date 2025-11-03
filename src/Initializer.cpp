#include "Initializer.h"
#include "Faction.h"
#include "Effet.h"
#include "EffetTextuel.h"

void Initializer::initializePlateauRef(Plateau& plateau) {
    std::cout << "DEBUG: Début initializePlateauRef" << std::endl;
    
    std::cout << "DEBUG: Création des effets" << std::endl;
    Effet soinPetit(2, SOIN);
    //temporaire
    Effet orPetit(8, OR);
    Effet degatPetit(3, DEGAT);

    std::cout << "DEBUG: Initialisation directe Joueur1" << std::endl;
    plateau.getJoueur1().setPointDeVie(50);
    plateau.getJoueur1().setArgent(0);
    plateau.getJoueur1().setDegatsStockes(0);
    
    // Créer une main avec 3 cartes de base et 2 gemmes
    std::cout << "DEBUG: Création main1" << std::endl;
    MainJoueur main1;
    
    // Ajouter 3 cartes de base
    for (int i = 0; i < 3; ++i) {
        main1.addCarte(new CarteDeBase("Soin & Or", {soinPetit, orPetit}));
    }
    
    // Ajouter 2 gemmes de feu
    for (int i = 0; i < 2; ++i) {
        main1.addCarte(new GemmeDeFeu());
    }
    
    std::cout << "DEBUG: Main1 créée avec " << main1.getCartes().size() << " cartes" << std::endl;
    std::cout << "DEBUG: Assignation main1" << std::endl;
    plateau.getJoueur1().setMain(main1);
    
    // Créer une pioche
    std::cout << "DEBUG: Création pioche1" << std::endl;
    Pioche pioche1;
    for (int i = 0; i < 5; ++i) {
        pioche1.addCarte(new CarteDeBase("Frappe", {degatPetit}));
    }
    std::cout << "DEBUG: Assignation pioche1" << std::endl;
    plateau.getJoueur1().setPioche(pioche1);

    // Même chose pour joueur 2
    std::cout << "DEBUG: Initialisation directe Joueur2" << std::endl;
    plateau.getJoueur2().setPointDeVie(50);
    plateau.getJoueur2().setArgent(0);
    plateau.getJoueur2().setDegatsStockes(0);
    
    std::cout << "DEBUG: Création main2" << std::endl;
    MainJoueur main2;
    
    for (int i = 0; i < 3; ++i) {
        main2.addCarte(new CarteDeBase("Soin & Or", {soinPetit, orPetit}));
    }
    
    for (int i = 0; i < 2; ++i) {
        main2.addCarte(new GemmeDeFeu());
    }
    
    plateau.getJoueur2().setMain(main2);
    
    std::cout << "DEBUG: Création pioche2" << std::endl;
    Pioche pioche2;
    for (int i = 0; i < 5; ++i) {
        pioche2.addCarte(new CarteDeBase("Frappe", {degatPetit}));
    }
    plateau.getJoueur2().setPioche(pioche2);

    std::cout << "DEBUG: Création du marché" << std::endl;
    Marche marche;
    
    std::cout << "DEBUG: Ajout de 16 gemmes" << std::endl;
    for (int i = 0; i < 16; ++i) {
        marche.addGemme(new GemmeDeFeu());
    }
    
    // ✅ CORRECTION : Ajouter les actions ET les champions
    std::cout << "DEBUG: Ajout d'actions au marché" << std::endl;
    auto actions = createActions();
    for (auto* action : actions) {
        marche.addStackAction(action);
    }
    
    std::cout << "DEBUG: Ajout de champions au marché" << std::endl;
    auto champions = createChampions();
    for (auto* champion : champions) {
        marche.addStackAction(champion);
    }

    std::cout << "DEBUG: Nombre total de cartes dans la stack : " << marche.getStackActions().size() << std::endl;
    
    std::cout << "DEBUG: Mélange du marché" << std::endl;
    marche.melangeStackActionEtChampion();
    
    std::cout << "DEBUG: Affichage des 10 premières cartes après mélange :" << std::endl;
    for (int i = 0; i < 10 && i < static_cast<int>(marche.getStackActions().size()); ++i) {
        Action* carte = marche.getStackActions()[i];
        Champion* champ = dynamic_cast<Champion*>(carte);
        std::string typeIcon = champ ? "🎖️" : "📜";
        std::cout << "  - Carte " << (i+1) << " : " << typeIcon << " " << carte->getNom() << std::endl;
    }
    
    std::cout << "DEBUG: Mise à jour des actions vendables (initialisation à 5 cartes)" << std::endl;
    // Initialiser avec exactement 5 cartes vendables
    for (int i = 0; i < 5 && !marche.getStackActions().empty(); ++i) {
        Action* carte = marche.getStackActions().front();
        marche.addActionVendable(carte);
        marche.removeStackAction(carte);
    }
    
    std::cout << "DEBUG: Nombre de cartes vendables initialisées: " << marche.getActionsVendables().size() << std::endl;
    std::cout << "DEBUG: Cartes vendables au démarrage :" << std::endl;
    for (size_t i = 0; i < marche.getActionsVendables().size(); ++i) {
        Action* action = marche.getActionsVendables()[i];
        
        std::string factionEmoji;
        switch(action->getFaction()) {
            case Faction::FactionJaune: factionEmoji = "👑"; break;
            case Faction::FactionBleu: factionEmoji = "🗡️"; break;
            case Faction::FactionRouge: factionEmoji = "💀"; break;
            case Faction::FactionVert: factionEmoji = "🐺"; break;
            default: factionEmoji = "⚪"; break;
        }
        
        Champion* champ = dynamic_cast<Champion*>(action);
        std::string typeIcon = champ ? "🎖️" : "📜";
        
        std::cout << "  " << (i+1) << ". " << factionEmoji << " " << typeIcon << " " 
                  << action->getNom() << " (" << action->getPrix() << " 💰)" << std::endl;
    }
    
    std::cout << "DEBUG: Assignation marché au plateau" << std::endl;
    plateau.setMarche(marche);
    
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
    std::cout << "Initialisation du marché..." << std::endl;
    
    Marche marche;
    
    // Créer et ajouter les gemmes de feu (16 gemmes)
    auto gemmes = createGemmesDeFeu(16);
    for (auto* gemme : gemmes) {
        marche.addGemme(gemme);
    }
    
    // ✅ Créer les actions et champions
    auto actions = createActions();
    auto champions = createChampions();
    
    std::cout << "📊 Composition du marché:" << std::endl;
    std::cout << "   • Actions: " << actions.size() << std::endl;
    std::cout << "   • Champions: " << champions.size() << std::endl;
    
    // ✅ Ajouter d'abord TOUTES les actions
    for (auto* action : actions) {
        marche.addStackAction(action);
    }
    
    // ✅ Puis ajouter tous les champions
    for (auto* champion : champions) {
        marche.addStackAction(champion);
    }
    
    std::cout << "Nombre total de cartes avant mélange: " << marche.getStackActions().size() << std::endl;
    
    // ✅ MÉLANGER la stack COMPLÈTE
    std::cout << "Mélange du marché en cours..." << std::endl;
    marche.melangeStackActionEtChampion();
    std::cout << "✅ Marché mélangé!" << std::endl;
    
    // Initialiser 5 cartes vendables
    std::cout << "Initialisation des cartes vendables..." << std::endl;
    for (int i = 0; i < 5 && !marche.getStackActions().empty(); ++i) {
        Action* carte = marche.getStackActions().front();
        marche.addActionVendable(carte);
        marche.removeStackAction(carte);
    }
    
    std::cout << "✅ Marché initialisé avec " << marche.getActionsVendables().size() << " cartes vendables." << std::endl;
    std::cout << "🎴 Cartes vendables au démarrage:" << std::endl;
    for (size_t i = 0; i < marche.getActionsVendables().size(); ++i) {
        Action* action = marche.getActionsVendables()[i];
        std::string factionEmoji;
        switch(action->getFaction()) {
            case Faction::FactionJaune: factionEmoji = "👑"; break;
            case Faction::FactionBleu: factionEmoji = "🗡️"; break;
            case Faction::FactionRouge: factionEmoji = "💀"; break;
            case Faction::FactionVert: factionEmoji = "🐺"; break;
            default: factionEmoji = "⚪"; break;
        }
        
        Champion* champ = dynamic_cast<Champion*>(action);
        std::string typeIcon = champ ? "🎖️" : "📜";
        
        std::cout << "  " << (i+1) << ". " << factionEmoji << " " << typeIcon << " " 
                  << action->getNom() << " (" << action->getPrix() << " 💰)" << std::endl;
    }
    
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
    
    // ✅ TEMPORAIRE : Toutes les actions avec effets de pioche (ID 1, 4 ou 6)
    // Au lieu de 1 exemplaire de chaque, créer 3 exemplaires de chaque action
    
    // Faction Jaune (Impériale) - 5 actions × 3 = 15 cartes
    for (int copy = 0; copy < 3; ++copy) {
        actions.push_back(new Action(Faction::FactionJaune, "Taxation", 1,
            {Effet(2, OR)}, {}, {EffetTextuel(18, "Preparez un champion.")}, {}, {Effet(6, SOIN)}, {}));
        
        actions.push_back(new Action(Faction::FactionJaune, "Recrutement", 3,
            {Effet(1, OR)}, {Effet(2, DEGAT)}, {EffetTextuel(18, "Preparez un champion.")}, {}, {Effet(2, OR), Effet(3, SOIN)}, {}));
        
        actions.push_back(new Action(Faction::FactionJaune, "Commandement", 2,
            {Effet(3, DEGAT)}, {}, {EffetTextuel(18, "Preparez un champion.")}, {}, {Effet(1, OR)}, {}));
        
        actions.push_back(new Action(Faction::FactionJaune, "Garde Royale", 4,
            {Effet(2, OR), Effet(2, SOIN)}, {}, {EffetTextuel(18, "Preparez un champion.")}, {}, {Effet(3, OR), Effet(3, SOIN)}, {}));
        
        actions.push_back(new Action(Faction::FactionJaune, "Bannière Impériale", 5,
            {Effet(3, DEGAT), Effet(2, SOIN)}, {}, {EffetTextuel(18, "Preparez un champion.")}, {}, {Effet(5, DEGAT), Effet(4, SOIN)}, {}));
    }
    
    // Faction Bleue (Guilde) - 5 actions × 3 = 15 cartes
    for (int copy = 0; copy < 3; ++copy) {
        actions.push_back(new Action(Faction::FactionBleu, "Pot-de-Vin", 1,
            {Effet(2, OR)}, {}, {EffetTextuel(13,"Vous pouvez placer une carte de votre défausse sur le dessus de votre pioche")}, {}, {Effet(4, DEGAT)}, {}));
        
        actions.push_back(new Action(Faction::FactionBleu, "Intimidation", 2,
            {Effet(5, DEGAT)}, {}, {EffetTextuel(18, "Preparez un champion.")}, {}, {Effet(3, OR)}, {}));
        
        actions.push_back(new Action(Faction::FactionBleu, "Espionnage", 3,
            {Effet(2, OR), Effet(2, DEGAT)}, {}, {EffetTextuel(18, "Preparez un champion.")}, {}, {Effet(4, OR), Effet(3, DEGAT)}, {}));
        
        actions.push_back(new Action(Faction::FactionBleu, "Contrat d'Assassin", 4,
                {Effet(4, DEGAT)}, {}, {EffetTextuel(13,"Vous pouvez placer une carte de votre défausse sur le dessus de votre pioche")}, {}, {Effet(6, DEGAT), Effet(2, OR)}, {}));
            
        actions.push_back(new Action(Faction::FactionBleu, "Trahison", 5,
            {Effet(3, DEGAT), Effet(2, OR)}, {}, {EffetTextuel(18, "Preparez un champion.")}, {}, {Effet(5, DEGAT), Effet(4, OR)}, {}));
    }
    
    // Faction Rouge (Nécros) - 5 actions × 3 = 15 cartes
    for (int copy = 0; copy < 3; ++copy) {
        actions.push_back(new Action(Faction::FactionRouge, "Magie Noire", 2,
            {Effet(3, DEGAT)}, {}, {EffetTextuel(18, "Preparez un champion.")}, {}, {Effet(2, DEGAT)}, {}));
        
        actions.push_back(new Action(Faction::FactionRouge, "Sacrifice", 3,
            {Effet(4, DEGAT)}, {Effet(2, SOIN)}, {EffetTextuel(4, "Piocher puis défausser")}, {}, {Effet(6, DEGAT), Effet(3, SOIN)}, {}));
        
        actions.push_back(new Action(Faction::FactionRouge, "Rituel Sombre", 4,
            {Effet(3, DEGAT)}, {Effet(2, SOIN)}, {EffetTextuel(18, "Preparez un champion.")}, {}, {Effet(5, DEGAT), Effet(3, SOIN)}, {}));
        
        actions.push_back(new Action(Faction::FactionRouge, "Invocation", 5,
            {Effet(5, DEGAT), Effet(2, SOIN)}, {}, {EffetTextuel(18, "Preparez un champion.")}, {}, {Effet(7, DEGAT), Effet(4, SOIN)}, {}));
        
        actions.push_back(new Action(Faction::FactionRouge, "Malédiction", 3,
            {Effet(4, DEGAT)}, {}, {EffetTextuel(4, "Piocher puis défausser")}, {}, {Effet(6, DEGAT)}, {}));
    }
    
    // Faction Verte (Sauvage) - 5 actions × 3 = 15 cartes
    for (int copy = 0; copy < 3; ++copy) {
        actions.push_back(new Action(Faction::FactionVert, "Charge Sauvage", 2,
            {Effet(4, DEGAT)}, {}, {EffetTextuel(18, "Preparez un champion.")}, {}, {Effet(6, DEGAT)}, {}));
        
        actions.push_back(new Action(Faction::FactionVert, "Rage du Loup", 3,
            {Effet(3, DEGAT), Effet(2, SOIN)}, {}, {EffetTextuel(18, "Preparez un champion.")}, {}, {Effet(5, DEGAT), Effet(4, SOIN)}, {}));
        
        actions.push_back(new Action(Faction::FactionVert, "Instinct Animal", 4,
            {Effet(2, DEGAT), Effet(3, SOIN)}, {}, {EffetTextuel(18, "Preparez un champion.")}, {}, {Effet(4, DEGAT), Effet(5, SOIN)}, {}));
        
        actions.push_back(new Action(Faction::FactionVert, "Hurlement du Pack", 4,
            {Effet(4, DEGAT)}, {}, {EffetTextuel(18, "Preparez un champion.")}, {}, {Effet(6, DEGAT), Effet(2, SOIN)}, {}));
        
        actions.push_back(new Action(Faction::FactionVert, "Sagesse Druidique", 5,
            {Effet(2, SOIN), Effet(2, OR)}, {}, {EffetTextuel(18, "Preparez un champion.")}, {}, {Effet(4, SOIN), Effet(4, OR)}, {}));
    }
    
    std::cout << "✅ " << actions.size() << " actions créées (60 actions TOUTES avec effets de pioche prioritaires)" << std::endl;
    std::cout << "   📊 Répartition : ~30 ID1 (piocher 1), ~15 ID4 (piocher+défausser), ~15 ID6 (piocher 2+défausser 2)" << std::endl;
    
    return actions;
}

std::vector<Champion*> Initializer::createChampions() {
    std::vector<Champion*> champions;
    
    // ✅ Garder seulement 1 exemplaire de chaque champion (8 champions uniques)
    
    // Faction Jaune - 2 champions
    champions.push_back(new Champion(Faction::FactionJaune, "Général Impérial", 8,
        {Effet(5, DEGAT), Effet(2, OR)}, {}, {}, {}, {Effet(7, DEGAT), Effet(4, OR)}, {},
        6, 6, false, false));
    
    champions.push_back(new Champion(Faction::FactionJaune, "Paladin Royal", 6,
        {Effet(3, DEGAT), Effet(3, SOIN)}, {}, {}, {}, {Effet(5, DEGAT), Effet(5, SOIN)}, {},
        5, 5, true, false));
    
    // Faction Bleue - 2 champions
    champions.push_back(new Champion(Faction::FactionBleu, "Maître Espion", 7,
        {Effet(4, DEGAT), Effet(2, OR)}, {}, {}, {}, {Effet(6, DEGAT), Effet(4, OR)}, {},
        5, 5, false, false));
    
    champions.push_back(new Champion(Faction::FactionBleu, "Seigneur des Voleurs", 9,
        {Effet(4, DEGAT), Effet(3, OR)}, {}, {}, {}, {Effet(6, DEGAT), Effet(5, OR)}, {},
        6, 6, false, false));
    
    // Faction Rouge - 2 champions
    champions.push_back(new Champion(Faction::FactionRouge, "Nécromant", 6,
        {Effet(3, DEGAT), Effet(2, SOIN)}, {}, {}, {}, {Effet(5, DEGAT), Effet(4, SOIN)}, {},
        5, 5, false, false));
    
    champions.push_back(new Champion(Faction::FactionRouge, "Seigneur Vampire", 10,
        {Effet(6, DEGAT), Effet(3, SOIN)}, {}, {}, {}, {Effet(9, DEGAT), Effet(5, SOIN)}, {},
        7, 7, false, false));
    
    // Faction Verte - 2 champions
    champions.push_back(new Champion(Faction::FactionVert, "Alpha des Loups", 9,
        {Effet(6, DEGAT)}, {}, {}, {}, {Effet(9, DEGAT), Effet(3, SOIN)}, {},
        7, 7, true, false));
    
    champions.push_back(new Champion(Faction::FactionVert, "Druide Suprême", 7,
        {Effet(2, DEGAT), Effet(4, SOIN)}, {}, {}, {}, {Effet(4, DEGAT), Effet(6, SOIN)}, {},
        6, 6, false, false));

        champions.push_back(new Champion(Faction::FactionJaune, "Général Impérial", 8,
        {Effet(5, DEGAT), Effet(2, OR)}, {}, {}, {}, {Effet(7, DEGAT), Effet(4, OR)}, {},
        6, 6, false, false));
    
    champions.push_back(new Champion(Faction::FactionJaune, "Paladin Royal", 6,
        {Effet(3, DEGAT), Effet(3, SOIN)}, {}, {}, {}, {Effet(5, DEGAT), Effet(5, SOIN)}, {},
        5, 5, true, false));
    
    // Faction Bleue - 2 champions
    champions.push_back(new Champion(Faction::FactionBleu, "Maître Espion", 7,
        {Effet(4, DEGAT), Effet(2, OR)}, {}, {}, {}, {Effet(6, DEGAT), Effet(4, OR)}, {},
        5, 5, false, false));
    
    champions.push_back(new Champion(Faction::FactionBleu, "Seigneur des Voleurs", 9,
        {Effet(4, DEGAT), Effet(3, OR)}, {}, {}, {}, {Effet(6, DEGAT), Effet(5, OR)}, {},
        6, 6, false, false));
    
    // Faction Rouge - 2 champions
    champions.push_back(new Champion(Faction::FactionRouge, "Nécromant", 6,
        {Effet(3, DEGAT), Effet(2, SOIN)}, {}, {}, {}, {Effet(5, DEGAT), Effet(4, SOIN)}, {},
        5, 5, false, false));
    
    champions.push_back(new Champion(Faction::FactionRouge, "Seigneur Vampire", 10,
        {Effet(6, DEGAT), Effet(3, SOIN)}, {}, {}, {}, {Effet(9, DEGAT), Effet(5, SOIN)}, {},
        7, 7, false, false));
    
    // Faction Verte - 2 champions
    champions.push_back(new Champion(Faction::FactionVert, "Alpha des Loups", 9,
        {Effet(6, DEGAT)}, {}, {}, {}, {Effet(9, DEGAT), Effet(3, SOIN)}, {},
        7, 7, true, false));
    
    champions.push_back(new Champion(Faction::FactionVert, "Druide Suprême", 7,
        {Effet(2, DEGAT), Effet(4, SOIN)}, {}, {}, {}, {Effet(4, DEGAT), Effet(6, SOIN)}, {},
        6, 6, false, false));

        champions.push_back(new Champion(Faction::FactionJaune, "Général Impérial", 8,
        {Effet(5, DEGAT), Effet(2, OR)}, {}, {}, {}, {Effet(7, DEGAT), Effet(4, OR)}, {},
        6, 6, false, false));
    
    champions.push_back(new Champion(Faction::FactionJaune, "Paladin Royal", 6,
        {Effet(3, DEGAT), Effet(3, SOIN)}, {}, {}, {}, {Effet(5, DEGAT), Effet(5, SOIN)}, {},
        5, 5, true, false));
    
    // Faction Bleue - 2 champions
    champions.push_back(new Champion(Faction::FactionBleu, "Maître Espion", 7,
        {Effet(4, DEGAT), Effet(2, OR)}, {}, {}, {}, {Effet(6, DEGAT), Effet(4, OR)}, {},
        5, 5, false, false));
    
    champions.push_back(new Champion(Faction::FactionBleu, "Seigneur des Voleurs", 9,
        {Effet(4, DEGAT), Effet(3, OR)}, {}, {}, {}, {Effet(6, DEGAT), Effet(5, OR)}, {},
        6, 6, false, false));
    
    // Faction Rouge - 2 champions
    champions.push_back(new Champion(Faction::FactionRouge, "Nécromant", 6,
        {Effet(3, DEGAT), Effet(2, SOIN)}, {}, {}, {}, {Effet(5, DEGAT), Effet(4, SOIN)}, {},
        5, 5, false, false));
    
    champions.push_back(new Champion(Faction::FactionRouge, "Seigneur Vampire", 10,
        {Effet(6, DEGAT), Effet(3, SOIN)}, {}, {}, {}, {Effet(9, DEGAT), Effet(5, SOIN)}, {},
        7, 7, false, false));
    
    // Faction Verte - 2 champions
    champions.push_back(new Champion(Faction::FactionVert, "Alpha des Loups", 9,
        {Effet(6, DEGAT)}, {}, {}, {}, {Effet(9, DEGAT), Effet(3, SOIN)}, {},
        7, 7, true, false));
    
    champions.push_back(new Champion(Faction::FactionVert, "Druide Suprême", 7,
        {Effet(2, DEGAT), Effet(4, SOIN)}, {}, {}, {}, {Effet(4, DEGAT), Effet(6, SOIN)}, {},
        6, 6, false, false));
    
    std::cout << "✅ " << champions.size() << " champions créés (8 champions uniques)" << std::endl;
    
    return champions;
}


std::vector<GemmeDeFeu*> Initializer::createGemmesDeFeu(int nombre) {
    std::vector<GemmeDeFeu*> gemmes;
    
    for (int i = 0; i < nombre; ++i) {
        gemmes.push_back(new GemmeDeFeu());
    }
    
    return gemmes;
}