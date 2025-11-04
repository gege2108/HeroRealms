#include "Initializer.h"
#include "Faction.h"
#include "Effet.h"
#include "EffetTextuel.h"

void Initializer::initializePlateauRef(Plateau& plateau) {
 
    
 
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
 

    main1.addCarte(new CarteDeBase("Carte Or", {Effet(1, OR)}));
    main1.addCarte(new CarteDeBase("Carte Or", {Effet(1, OR)}));
    main1.addCarte(new CarteDeBase("Carte Or", {Effet(1, OR)}));

    main1.addCarte(new CarteDeBase("Dague", {Effet(1, DEGAT)}));
    main1.addCarte(new CarteDeBase("Rubis", {Effet(2, OR)}));

 
 
 std::cout << "DEBUG: Main1 créée avec " << main1.getCartes().size() << " cartes" << std::endl;
 std::cout << "DEBUG: Assignation main1" << std::endl;
 main1.melangeMain();
 plateau.getJoueur1().setMain(main1);


 
 // Créer une pioche
 std::cout << "DEBUG: Création pioche1" << std::endl;
 Pioche pioche1;
     pioche1.addCarte(new CarteDeBase("Epée Courte", {Effet(2, DEGAT)}));

    pioche1.addCarte(new CarteDeBase("Carte Or", {Effet(1, OR)}));
    pioche1.addCarte(new CarteDeBase("Carte Or", {Effet(1, OR)}));
    pioche1.addCarte(new CarteDeBase("Carte Or", {Effet(1, OR)}));
    pioche1.addCarte(new CarteDeBase("Carte Or", {Effet(1, OR)}));

 std::cout << "DEBUG: Assignation pioche1" << std::endl;
 plateau.getJoueur1().setPioche(pioche1);

 // Même chose pour joueur 2
 std::cout << "DEBUG: Initialisation directe Joueur2" << std::endl;
 plateau.getJoueur2().setPointDeVie(50);
 plateau.getJoueur2().setArgent(0);
 plateau.getJoueur2().setDegatsStockes(0);
 
 std::cout << "DEBUG: Création main2" << std::endl;
 MainJoueur main2;
 
    main2.addCarte(new CarteDeBase("Carte Or", {Effet(1, OR)}));
    main2.addCarte(new CarteDeBase("Carte Or", {Effet(1, OR)}));
    main2.addCarte(new CarteDeBase("Carte Or", {Effet(1, OR)}));
    main2.addCarte(new CarteDeBase("Carte Or", {Effet(1, OR)}));
 
    main2.addCarte(new CarteDeBase("Rubis", {Effet(2, OR)}));
 
main2.melangeMain();
 
 plateau.getJoueur2().setMain(main2);
 
 std::cout << "DEBUG: Création pioche2" << std::endl;
 Pioche pioche2;
   pioche2.addCarte(new CarteDeBase("Carte Or", {Effet(1, OR)}));
    pioche2.addCarte(new CarteDeBase("Carte Or", {Effet(1, OR)}));
    pioche2.addCarte(new CarteDeBase("Carte Or", {Effet(1, OR)}));

    pioche2.addCarte(new CarteDeBase("Epée Courte", {Effet(2, DEGAT)}));
    pioche2.addCarte(new CarteDeBase("Dague", {Effet(1, DEGAT)}));
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
 std::cout << " - Carte " << (i+1) << " : " << typeIcon << " " << carte->getNom() << std::endl;
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
 
 std::cout << " " << (i+1) << ". " << factionEmoji << " " << typeIcon << " " 
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
 
 Marche marche;
 
 // Créer et ajouter les gemmes de feu (16 gemmes)
 auto gemmes = createGemmesDeFeu(16);
 for (auto* gemme : gemmes) {
 marche.addGemme(gemme);
 }
 
 // ✅ Créer les actions et champions
 auto actions = createActions();
 auto champions = createChampions();
 
 // ✅ Ajouter d'abord TOUTES les actions
 for (auto* action : actions) {
 marche.addStackAction(action);
 }
 
 // ✅ Puis ajouter tous les champions
 for (auto* champion : champions) {
 marche.addStackAction(champion);
 }
 
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
 
 std::cout << " " << (i+1) << ". " << factionEmoji << " " << typeIcon << " " 
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
 
 // Au lieu de 1 exemplaire de chaque, créer 3 exemplaires de chaque action
 //effetBasiqueChoix1, effetBasiqueChoix2, effetTextuelChoix1, effetTextuelChoix2, effetAllie, effetTextuelAllie
 // Faction Jaune (Impériale)
 actions.push_back(new Action(Faction::FactionJaune, "Serrer les Rangs", 3,
 {Effet(5, DEGAT)}, {}, {EffetTextuel(11, "+2 dégât par champion en jeu.")}, {}, {Effet(6, SOIN)}, {}));

 actions.push_back(new Action(Faction::FactionJaune, "Commandement", 5,
 {Effet(2, OR), Effet(3, DEGAT), Effet(4, SOIN)}, {}, {EffetTextuel(1, "Pioche une carte.")}, {}, {}, {}));

 actions.push_back(new Action(Faction::FactionJaune, "Domination", 7,
 {Effet(6, DEGAT), Effet(6, SOIN)}, {}, {EffetTextuel(1, "Pioche une carte.")}, {}, {}, {EffetTextuel(18, "Prépare un champion.")}));

 actions.push_back(new Action(Faction::FactionJaune, "Ralliement des Troupes", 4,
 {Effet(5, DEGAT), Effet(5, SOIN)}, {}, {}, {}, {}, {EffetTextuel(18, "Prépare un champion.")}));

 actions.push_back(new Action(Faction::FactionJaune, "Recrutement", 2,
 {Effet(2, OR), Effet(3, SOIN)}, {}, {EffetTextuel(10, "+1 soin par champion en jeu.")}, {}, {Effet(1, OR)}, {}));
 actions.push_back(new Action(Faction::FactionJaune, "Recrutement", 2,
 {Effet(2, OR), Effet(3, SOIN)}, {}, {EffetTextuel(10, "+1 soin par champion en jeu.")}, {}, {Effet(1, OR)}, {}));
 actions.push_back(new Action(Faction::FactionJaune, "Recrutement", 2,
 {Effet(2, OR), Effet(3, SOIN)}, {}, {EffetTextuel(10, "+1 soin par champion en jeu.")}, {}, {Effet(1, OR)}, {}));

 actions.push_back(new Action(Faction::FactionJaune, "Taxation", 1,
 {Effet(2, OR)}, {}, {}, {}, {Effet(6, SOIN)}, {}));
 actions.push_back(new Action(Faction::FactionJaune, "Taxation", 1,
 {Effet(2, OR)}, {}, {}, {}, {Effet(6, SOIN)}, {}));
 actions.push_back(new Action(Faction::FactionJaune, "Taxation", 1,
 {Effet(2, OR)}, {}, {}, {}, {Effet(6, SOIN)}, {}));

 actions.push_back(new Action(Faction::FactionJaune, "Puissance", 6,
 {}, {}, {EffetTextuel(1, "Pioche une carte."), EffetTextuel(1, "Pioche une 2e carte.")}, {EffetTextuel(19,"Sacrifie cette carte")}, {Effet(5, SOIN)}, {})); // sacrifice à faire

 
 // Faction Bleue (Guilde) - 5 actions × 3 = 15 cartes
 actions.push_back(new Action(Faction::FactionBleu, "Pot-De-Vin", 3,
 {Effet(3, OR)}, {}, {}, {}, {}, {EffetTextuel(14, "Met la prochaine action achetée au dessus de la pioche.")}));
 actions.push_back(new Action(Faction::FactionBleu, "Pot-De-Vin", 3,
 {Effet(3, OR)}, {}, {}, {}, {}, {EffetTextuel(14, "Met la prochaine action achetée au dessus de la pioche.")}));
 actions.push_back(new Action(Faction::FactionBleu, "Pot-De-Vin", 3,
 {Effet(3, OR)}, {}, {}, {}, {}, {EffetTextuel(14, "Met la prochaine action achetée au dessus de la pioche.")}));

 actions.push_back(new Action(Faction::FactionBleu, "Menace de Mort", 3,
 {Effet(1, DEGAT)}, {}, {EffetTextuel(1, "Pioche une carte.")}, {}, {}, {EffetTextuel(2, "Assome un champion.")}));

 actions.push_back(new Action(Faction::FactionBleu, "Fourberie", 5,
 {Effet(2, OR)}, {}, {EffetTextuel(1, "Pioche une carte.")}, {}, {}, {EffetTextuel(14, "Met la prochaine action achetée au dessus de la pioche.")}));

 actions.push_back(new Action(Faction::FactionBleu, "Bombe Incendiaire", 8,
 {Effet(8, DEGAT)}, {Effet(5, DEGAT)}, {EffetTextuel(1, "Pioche une carte."), EffetTextuel(3, "Assome un champion.")}, {EffetTextuel(19,"Sacrifie cette carte")}, {}, {})); // sacrifice à faire

 actions.push_back(new Action(Faction::FactionBleu, "Mise à prix", 4,
 {Effet(7, DEGAT)}, {}, {}, {}, {}, {EffetTextuel(3, "Assome un champion.")}));

 actions.push_back(new Action(Faction::FactionBleu, "Intimidation", 2,
 {Effet(5, DEGAT)}, {}, {}, {}, {Effet(2, OR)}, {}));
 actions.push_back(new Action(Faction::FactionBleu, "Intimidation", 2,
 {Effet(5, DEGAT)}, {}, {}, {}, {Effet(2, OR)}, {}));

 actions.push_back(new Action(Faction::FactionBleu, "Bénéfice", 1,
 {Effet(2, OR)}, {}, {}, {}, {Effet(4, DEGAT)}, {}));
 actions.push_back(new Action(Faction::FactionBleu, "Bénéfice", 1,
 {Effet(2, OR)}, {}, {}, {}, {Effet(4, DEGAT)}, {}));
 actions.push_back(new Action(Faction::FactionBleu, "Bénéfice", 1,
 {Effet(2, OR)}, {}, {}, {}, {Effet(4, DEGAT)}, {}));

 actions.push_back(new Action(Faction::FactionBleu, "Casser et Piller", 6,
 {Effet(6, DEGAT)}, {}, {EffetTextuel(13, "Choisir une carte de la défausse à mettre au dessus de la pioche.")}, {}, {}, {}));
 
 // Faction Rouge (Nécros) - 5 actions × 3 = 15 cartes
 actions.push_back(new Action(Faction::FactionRouge, "Energie Sombre", 4,
 {Effet(7, DEGAT)}, {}, {}, {}, {}, {EffetTextuel(1, "Pioche une carte.")}));

 actions.push_back(new Action(Faction::FactionRouge, "Sombre Récompense", 5,
 {Effet(3, OR)}, {}, {EffetTextuel(15, "peut sacrifier une carte.")}, {}, {Effet(6, DEGAT)}, {}));

 actions.push_back(new Action(Faction::FactionRouge, "Contact Mortel", 1,
 {Effet(2, DEGAT)}, {}, {EffetTextuel(15, "peut sacrifier une carte.")}, {}, {Effet(2, DEGAT)}, {}));
 actions.push_back(new Action(Faction::FactionRouge, "Contact Mortel", 1,
 {Effet(2, DEGAT)}, {}, {EffetTextuel(15, "peut sacrifier une carte.")}, {}, {Effet(2, DEGAT)}, {}));
 actions.push_back(new Action(Faction::FactionRouge, "Contact Mortel", 1,
 {Effet(2, DEGAT)}, {}, {EffetTextuel(15, "peut sacrifier une carte.")}, {}, {Effet(2, DEGAT)}, {}));

 actions.push_back(new Action(Faction::FactionRouge, "Influence", 2,
 {Effet(3, OR)}, {}, {}, {}, {}, {}));
 actions.push_back(new Action(Faction::FactionRouge, "Influence", 2,
 {Effet(3, OR)}, {}, {}, {}, {}, {}));
 actions.push_back(new Action(Faction::FactionRouge, "Influence", 2,
 {Effet(3, OR)}, {}, {}, {}, {}, {})); // sacrifice à faire

 actions.push_back(new Action(Faction::FactionRouge, "Drain de vie", 6,
 {Effet(8, DEGAT)}, {}, {EffetTextuel(15, "peut sacrifier une carte.")}, {}, {}, {EffetTextuel(1, "Pioche une carte.")}));

 actions.push_back(new Action(Faction::FactionRouge, "Putréfaction", 3,
 {Effet(4, DEGAT)}, {}, {EffetTextuel(15, "peut sacrifier une carte.")}, {}, {Effet(3, DEGAT)}, {}));
 actions.push_back(new Action(Faction::FactionRouge, "Putréfaction", 3,
 {Effet(4, DEGAT)}, {}, {EffetTextuel(15, "peut sacrifier une carte.")}, {}, {Effet(3, DEGAT)}, {}));
 
 // Faction Verte (Sauvage) - 5 actions × 3 = 15 cartes
 actions.push_back(new Action(Faction::FactionVert, "Malédiction Elfique", 3,
 {Effet(6, DEGAT)}, {}, {EffetTextuel(2, "L'adversaire se défausse d'une carte.")}, {}, {Effet(3, DEGAT)}, {}));
 actions.push_back(new Action(Faction::FactionVert, "Malédiction Elfique", 3,
 {Effet(6, DEGAT)}, {}, {EffetTextuel(2, "L'adversaire se défausse d'une carte.")}, {}, {Effet(3, DEGAT)}, {}));

 actions.push_back(new Action(Faction::FactionVert, "Don Elfique", 2,
 {Effet(2, OR)}, {}, {EffetTextuel(4, "si piocher une carte, alors se défausser d'une carte")}, {}, {Effet(4, DEGAT)}, {}));
 actions.push_back(new Action(Faction::FactionVert, "Don Elfique", 2,
 {Effet(2, OR)}, {}, {EffetTextuel(4, "si piocher une carte, alors se défausser d'une carte")}, {}, {Effet(4, DEGAT)}, {}));
 actions.push_back(new Action(Faction::FactionVert, "Don Elfique", 2,
 {Effet(2, OR)}, {}, {EffetTextuel(4, "si piocher une carte, alors se défausser d'une carte")}, {}, {Effet(4, DEGAT)}, {}));

 actions.push_back(new Action(Faction::FactionVert, "Don de la nature", 4,
 {Effet(4, OR)}, {}, {}, {EffetTextuel(19,"Sacrifie cette carte")}, {}, {EffetTextuel(2, "L'adversaire se défausse d'une carte.")})); // sacrifice à faire

 actions.push_back(new Action(Faction::FactionVert, "Etincelle", 1,
 {Effet(3, DEGAT)}, {}, {}, {}, {Effet(2, DEGAT)}, {}));
 actions.push_back(new Action(Faction::FactionVert, "Etincelle", 1,
 {Effet(3, DEGAT)}, {}, {}, {}, {Effet(2, DEGAT)}, {}));
 actions.push_back(new Action(Faction::FactionVert, "Etincelle", 1,
 {Effet(3, DEGAT)}, {}, {}, {}, {Effet(2, DEGAT)}, {}));

 actions.push_back(new Action(Faction::FactionVert, "Sauvagerie", 6,
 {Effet(6, DEGAT)}, {}, {EffetTextuel(4, "si piocher une carte, alors se défausser d'une carte"), EffetTextuel(4, "si piocher une 2e carte, alors se défausser d'une 2e carte")}, {}, {}, {}));

 actions.push_back(new Action(Faction::FactionVert, "Forme de Loup", 5,
 {Effet(8, DEGAT)}, {}, {EffetTextuel(2, "L'adversaire se défausse d'une carte.")}, {EffetTextuel(19,"Sacrifie cette carte" )}, {}, {})); // sacrifice à faire
 
 
 std::cout << "✅ " << actions.size() << " actions créées (60 actions TOUTES avec effets de pioche prioritaires)" << std::endl;
 std::cout << " 📊 Répartition : ~30 ID1 (piocher 1), ~15 ID4 (piocher+défausser), ~15 ID6 (piocher 2+défausser 2)" << std::endl;
 
 return actions;
}

std::vector<Champion*> Initializer::createChampions() {
 std::vector<Champion*> champions;
 
 // ✅ Garder seulement 1 exemplaire de chaque champion (8 champions uniques)
 //effetBasiqueChoix1, effetBasiqueChoix2, effetTextuelChoix1, effetTextuelChoix2, effetAllie, effetTextuelAllie
 // Faction Jaune - 2 champions
 champions.push_back(new Champion(Faction::FactionJaune, "Arkus, Dragon Impérial", 8,
 {Effet(5, DEGAT)}, {}, {EffetTextuel(1, "Pioche carte.")}, {}, {Effet(6, SOIN)}, {},
 6, 6, true, false));
 
 champions.push_back(new Champion(Faction::FactionJaune, "Cristov, le Juste Royal", 5,
 {Effet(2, DEGAT), Effet(3, SOIN)}, {}, {}, {}, {}, {EffetTextuel(1, "Pioche carte.")},
 5, 5, true, false));
 
 champions.push_back(new Champion(Faction::FactionJaune, "Darian, Mage de Guerre", 4,
 {}, {}, {EffetTextuel(22, "Gagner 3 d'attaque ou 4 de vie")}, {}, {}, {},
 5, 5, false, false)); //avec choix
 
 champions.push_back(new Champion(Faction::FactionJaune, "Kraka, Grand prêtre", 6,
 {Effet(2, SOIN)}, {}, {EffetTextuel(1, "Pioche carte.")}, {}, {}, {EffetTextuel(7, "+2 soin par champion en jeu.")},
 6, 6, false, false));

 champions.push_back(new Champion(Faction::FactionJaune, "Homme d'Armes", 3,
 {Effet(2, DEGAT)}, {}, {EffetTextuel(8, "+1 dégât par autres gardes.")}, {}, {}, {},
 4, 4, true, false));
 champions.push_back(new Champion(Faction::FactionJaune, "Homme d'Armes", 3,
 {Effet(2, DEGAT)}, {}, {EffetTextuel(8, "+1 dégât par autres gardes.")}, {}, {}, {},
 4, 4, true, false));

 champions.push_back(new Champion(Faction::FactionJaune, "Maître Weyan", 4,
 {Effet(3, DEGAT)}, {}, {EffetTextuel(9, "+1 dégât par autres champions.")}, {}, {}, {},
 4, 4, true, false));

 champions.push_back(new Champion(Faction::FactionJaune, "Percepteur de Dime", 2,
 {}, {}, {}, {EffetTextuel(21, "1 d'or ou +1 soin par champion en jeu.")}, {}, {},
 3, 3, false, false)); //avec choix
  champions.push_back(new Champion(Faction::FactionJaune, "Percepteur de Dime", 2,
 {}, {}, {}, {EffetTextuel(21, "1 d'or ou +1 soin par champion en jeu.")}, {}, {},
 3, 3, false, false));//avec choix
 

 //effetBasiqueChoix1, effetBasiqueChoix2, effetTextuelChoix1, effetTextuelChoix2, effetAllie, effetTextuelAllie
 // Faction Bleue
 champions.push_back(new Champion(Faction::FactionBleu, "Borg, Mercenaire Ogre", 6,
 {Effet(4, DEGAT)}, {}, {}, {}, {}, {},
 6, 6, true, false));

 champions.push_back(new Champion(Faction::FactionBleu, "Myros, Mage de la Guilde", 5,
 {Effet(3, OR)}, {}, {}, {}, {Effet(4, DEGAT)}, {},
 3, 3, true, false));

 champions.push_back(new Champion(Faction::FactionBleu, "Parov, l'Executeur", 5,
 {Effet(3, DEGAT)}, {}, {}, {}, {}, {EffetTextuel(1, "Pioche carte.")},
 5, 5, true, false));

 champions.push_back(new Champion(Faction::FactionBleu, "Rake, Maître assassin", 7,
 {Effet(4, DEGAT)}, {}, {EffetTextuel(3, "Assome champion.")}, {}, {}, {},
 7, 7, true, false));
 
 champions.push_back(new Champion(Faction::FactionBleu, "Rasmus, le Contrebandier", 4,
 {Effet(2, OR)}, {}, {}, {}, {}, {EffetTextuel(13, "Met prochaine carte obtenue au dessus de la pioche.")},
 5, 5, false, false));

 champions.push_back(new Champion(Faction::FactionBleu, "Bandit des Rues", 3,
 {Effet(1, OR)}, {Effet(2, DEGAT)}, {}, {}, {}, {},
 4, 4, false, false));
 champions.push_back(new Champion(Faction::FactionBleu, "Bandit des Rues", 3,
 {}, {}, {EffetTextuel(23, "Gagner 1 d'or ou 2 de dégât.")}, {}, {}, {},
 4, 4, false, false)); // avec choix
 

 //effetBasiqueChoix1, effetBasiqueChoix2, effetTextuelChoix1, effetTextuelChoix2, effetAllie, effetTextuelAllie
 // Faction Rouge
 champions.push_back(new Champion(Faction::FactionRouge, "Prêtre du Culte", 3,
 {Effet(1, OR)}, {Effet(1, DEGAT)}, {}, {}, {Effet(4, DEGAT)}, {},
 4, 4, false, false));
 champions.push_back(new Champion(Faction::FactionRouge, "Prêtre du Culte", 3,
 {}, {}, {EffetTextuel(24, "Gagner 1 d'or ou 1 dégât.")}, {}, {}, {},
 4, 4, false, false)); // avec choix

 champions.push_back(new Champion(Faction::FactionRouge, "Krythos, Maître Vampire", 7,
 {Effet(3, DEGAT)}, {}, {EffetTextuel(16, "+3 dégât si sacrifier carte de main ou défausse.")}, {}, {}, {},
 6, 6, false, false));

 champions.push_back(new Champion(Faction::FactionRouge, "Lys, l'Inapparent", 6,
 {Effet(2, DEGAT)}, {}, {EffetTextuel(17, "+2 dégât si sacrifier carte de main ou défausse.")}, {}, {}, {},
 5, 5, true, false));

 champions.push_back(new Champion(Faction::FactionRouge, "Rayla, Tisseuse de Fins", 4,
 {Effet(3, DEGAT)}, {}, {}, {}, {}, {EffetTextuel(1, "Pioche carte.")},
 4, 4, false, false));

 champions.push_back(new Champion(Faction::FactionRouge, "Tyrannor, le Dévoreur", 8,
 {Effet(4, DEGAT)}, {}, {EffetTextuel(15, "Sacrifie 1ère carte"), EffetTextuel(15, "Sacrifie 2ème carte.")}, {}, {}, {EffetTextuel(1, "Pioche carte.")},
 6, 6, true, false));

 champions.push_back(new Champion(Faction::FactionRouge, "Varrick, le Nécromancien", 5,
 {}, {}, {EffetTextuel(14, "Choisissez un champion pour mettre au-dessus de la pioche.")}, {}, {}, {EffetTextuel(1, "Pioche carte.")},
 3, 3, false, false)); // faire EffetTextuel("choisis un champion pour mettre au dessus de la pioche.")

 champions.push_back(new Champion(Faction::FactionRouge, "Cultiste de la Mort", 2,
 {Effet(2, DEGAT)}, {}, {}, {}, {}, {},
 3, 3, true, false));
 champions.push_back(new Champion(Faction::FactionRouge, "Cultiste de la Mort", 2,
 {Effet(2, DEGAT)}, {}, {}, {}, {}, {},
 3, 3, true, false));


 // Faction Verte
 champions.push_back(new Champion(Faction::FactionVert, "Broelyn, Tisseuse de Savoirs", 4,
 {Effet(2, OR)}, {}, {}, {}, {}, {EffetTextuel(2, "L'adversaire défausse une carte.")},
 6, 6, false, false));

 champions.push_back(new Champion(Faction::FactionVert, "Cron, le Berserker", 6,
 {Effet(5, DEGAT)}, {}, {}, {}, {}, {EffetTextuel(1, "Pioche carte.")},
 6, 6, false, false));

 champions.push_back(new Champion(Faction::FactionVert, "Loup Terrifiant", 5,
 {Effet(3, DEGAT)}, {}, {}, {}, {Effet(4, DEGAT)}, {},
 5, 5, true, false));

 champions.push_back(new Champion(Faction::FactionVert, "Grak, Géant de la Tempête", 8,
 {Effet(6, DEGAT)}, {}, {}, {}, {}, {EffetTextuel(4, "Piocher et défausser une carte.")},
 7, 7, true, false));

 champions.push_back(new Champion(Faction::FactionVert, "Grognard Orque", 3,
 {Effet(2, DEGAT)}, {}, {}, {}, {}, {EffetTextuel(1, "Pioche carte.")},
 3, 3, true, false));
 champions.push_back(new Champion(Faction::FactionVert, "Grognard Orque", 3,
 {Effet(2, DEGAT)}, {}, {}, {}, {}, {EffetTextuel(1, "Pioche carte.")},
 3, 3, true, false));

 champions.push_back(new Champion(Faction::FactionVert, "Torgen Brise-Pierre", 7,
 {Effet(4, DEGAT)}, {}, {}, {}, {}, {EffetTextuel(2, "L'adversaire défausse une carte.")},
 7, 7, true, false));

 champions.push_back(new Champion(Faction::FactionVert, "Shamane des Loups", 2,
 {Effet(2, DEGAT)}, {}, {}, {}, {}, {EffetTextuel(12, "+1 dégât par autre Sauvage.")},
 4, 4, false, false));
 champions.push_back(new Champion(Faction::FactionVert, "Shamane des Loups", 2,
 {Effet(2, DEGAT)}, {}, {}, {}, {}, {EffetTextuel(12, "+1 dégât par autre Sauvage.")},
 4, 4, false, false));
 
 std::cout << "✅ " << champions.size() << " champions créés (27 champions uniques)" << std::endl;
 
 return champions;
}


std::vector<GemmeDeFeu*> Initializer::createGemmesDeFeu(int nombre) {
 std::vector<GemmeDeFeu*> gemmes;
 
 for (int i = 0; i < nombre; ++i) {
 gemmes.push_back(new GemmeDeFeu());
 }
 
 return gemmes;
}

