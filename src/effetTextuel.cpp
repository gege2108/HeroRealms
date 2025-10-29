#include "EffetTextuel.h"
#include "Joueur.h"
#include <iostream>
#include "Champion.h"
#include "Zone.h"
#include "Carte.h"
#include "Pioche.h"
#include "MainJoueur.h"
#include "StackChampion.h"
#include "Defausse.h"
#include <vector>
#include <limits>
#include <string>
#include "Effet.h"
#include "Action.h"

// Comportement
void EffetTextuel::executer() const {
    // Aucun message à afficher — comportement par défaut : no-op
}

//1 Draw a card. : utiliser Pioche::piocher(MainJoueur& main)

//2 Target opponent discards a card.
void EffetTextuel::discardOpponentCard(Joueur& opponent, MainJoueur& main) const {
    if (opponent.getMain().getCartes().empty()) {return;}
    int nombre;
    std::cout << "Choose a card to discard (0 to " << opponent.getMain().getCartes().size() - 1 << "): ";
    std::cin >> nombre;
    if (nombre < 0 || nombre >= opponent.getMain().getCartes().size()) {return;}
    Carte carte = opponent.getMain().getCartes()[nombre];
    opponent.getMain().retirerCarte(carte);
    main.ajouterCarte(carte);
}
//3 Stun target champion.
void EffetTextuel::stunChampion(Joueur& opponent) const {
    if (opponent.getStackChampion().getChampions().empty()) {return;}
    int nombre;
    std::cout << "Choose a champion to stun (0 to " << opponent.getStackChampion().getChampions().size() - 1 << "): ";
    std::cin >> nombre;
    if (nombre < 0 || nombre >= opponent.getStackChampion().getChampions().size()) {return;}
    Champion& champion = opponent.getStackChampion().getChampions()[nombre];
    champion.setIsDefense(false);
}
//4 You may draw a card, then discard a card
void EffetTextuel::drawAndDiscard(Joueur& player) const {
    std::cout << "Tap (1) to draw a card, then discard a card, (0) to cancel" << std::endl;
    int choice;
    std::cin >> choice;
    if (choice == 0) { return; }
    if (player.getPioche().getCartes().empty()) {return;}
    player.getPioche().piocher(player.getMain());
    if (player.getMain().getCartes().empty()) {return;}
    int nombre;
    std::cout << "Choose a card to discard (0 to " << player.getMain().getCartes().size() - 1 << "): ";
    std::cin >> nombre;
    if (nombre < 0 || nombre >= player.getMain().getCartes().size()) {return;}
    Carte carte = player.getMain().getCartes()[nombre];
    player.getMain().retirerCarte(carte);
}
//5 You may draw up to two cards, then discard that many cards.
void EffetTextuel::drawAndDiscardTwo(Joueur& player) const {
    std::cout << "Tap (1) to draw up to two cards, then discard that many cards, (0) to cancel" << std::endl;
    int choice;
    std::cin >> choice;
    if (choice == 0) { return; }
    int drawCount = 0;
    for (int i = 0; i < 2; ++i) {
        if (player.getPioche().getCartes().empty()) {break;}
        player.getPioche().piocher(player.getMain());
        drawCount++;
    }
    for (int i = 0; i < drawCount; ++i) {
        if (player.getMain().getCartes().empty()) {break;}
        int nombre;
        std::cout << "Choose a card to discard (0 to " << player.getMain().getCartes().size() - 1 << "): ";
        std::cin >> nombre;
        if (nombre < 0 || nombre >= player.getMain().getCartes().size()) {continue;}
        Carte carte = player.getMain().getCartes()[nombre];
        player.getMain().retirerCarte(carte);
    }
}
//6 Put the next action you acquire this turn on top of your deck.
//7 Put the next card you acquire this turn into your hand.
//8 Take a champion from your discard pile and put it on top of your deck.
//9 Take a card from your discard pile and put it on top of your deck.
//10 Prepare a champion.

//11 You may sacrifice up to two cards in your hand and/or discard pile.
void EffetTextuel::sacrificeDeuxCartes(Joueur& joueur) const {
    int sacrificesRestants = 2;
    std::cout << "Tap (1) to sacrifice a card, (0) to cancel" << std::endl;
    int choice;
    std::cin >> choice;
    if (choice == 0) { return; }
    while (sacrificesRestants > 0) {
        std::cout << "Choose source: (1) Hand, (2) Discard Pile: ";
        int source;
        std::cin >> source;
        if (source == 1 && !joueur.getMain().getCartes().empty()) {
            int nombre;
            std::cout << "Choose a card to sacrifice from your hand (0 to " << joueur.getMain().getCartes().size() - 1 << "): ";
            std::cin >> nombre;
            if (nombre >= 0 && nombre < joueur.getMain().getCartes().size()) {
                Carte carte = joueur.getMain().getCartes()[nombre];
                joueur.getMain().retirerCarte(carte);
                ZoneDeSacrifice::getInstance().ajouterCarte(carte);
                sacrificesRestants--;
            }
        } else if (source == 2 && !joueur.getDefausse().getCartes().empty()) {
            int nombre;
            std::cout << "Choose a card to sacrifice from your discard pile (0 to " << joueur.getDefausse().getCartes().size() - 1 << "): ";
            std::cin >> nombre;
            if (nombre >= 0 && nombre < joueur.getDefausse().getCartes().size()) {
                Carte carte = joueur.getDefausse().getCartes()[nombre];
                joueur.getDefausse().retirerCarte(carte);
                ZoneDeSacrifice::getInstance().ajouterCarte(carte);
                sacrificesRestants--;
            }
        } else {
            std::cout << "Invalid choice or no cards available in the chosen source." << std::endl;
        }
    }
}
//12 You may sacrifice a card in your hand or discard pile.
void EffetTextuel::sacrificeUneCarte(Joueur& joueur) const {
    std::cout << "Tap (1) to sacrifice a card, (0) to cancel" << std::endl;
    int choice;
    std::cin >> choice;
    if (choice == 0) { return; }
    std::cout << "Choose source: (1) Hand, (2) Discard Pile: ";
    int source;
    std::cin >> source;
    if (source == 1 && !joueur.getMain().getCartes().empty()) {
        int nombre;
        std::cout << "Choose a card to sacrifice from your hand (0 to " << joueur.getMain().getCartes().size() - 1 << "): ";
        std::cin >> nombre;
        if (nombre >= 0 && nombre < joueur.getMain().getCartes().size()) {
            Carte carte = joueur.getMain().getCartes()[nombre];
            joueur.getMain().retirerCarte(carte);
            ZoneDeSacrifice::getInstance().ajouterCarte(carte);
        }
    } else if (source == 2 && !joueur.getDefausse().getCartes().empty()) {
        int nombre;
        std::cout << "Choose a card to sacrifice from your discard pile (0 to " << joueur.getDefausse().getCartes().size() - 1 << "): ";
        std::cin >> nombre;
        if (nombre >= 0 && nombre < joueur.getDefausse().getCartes().size()) {
            Carte carte = joueur.getDefausse().getCartes()[nombre];
            joueur.getDefausse().retirerCarte(carte);
            ZoneDeSacrifice::getInstance().ajouterCarte(carte);
        }
    } else {
        std::cout << "Invalid choice or no cards available in the chosen source." << std::endl;
    }
}
//13 You may sacrifice a card in your hand or discard pile. If you do, gain an additional {3 combat}.
void EffetTextuel::sacrificeFor3Combat(Carte& carte, Joueur& joueur, MainJoueur& main) const {
    sacrificeUneCarte(joueur);
    carte.getEffetsBasiqueChoix1().emplace_back(Effet(3, DEGAT));
}
//14 You may sacrifice a card in your hand or discard pile. If you do, gain an additional {2 combat}.
void EffetTextuel::sacrificeFor2Combat(Carte& carte, Joueur& joueur, MainJoueur& main) const {
    sacrificeUneCarte(joueur);
    carte.getEffetsBasiqueChoix1().emplace_back(Effet(2, DEGAT));
}

//15 +{1 combat} for each other guard you have in play.
void EffetTextuel::combat1PerGuard(Carte& carte, Joueur& joueur) const {
    int guardCount = 0;
    for (const Champion& champ : joueur.getStackChampion().getChampions()) {
        if (champ.getIsGarde()) {
            guardCount++;
        }
    }
    carte.getEffetsBasiqueChoix1().emplace_back(Effet(guardCount, DEGAT));
}
//16 +{1 combat} for each other {Wild} card you have in play.                  à corriger le FactionVerte ptet
void EffetTextuel::combat1PerWild(Carte& carte, Joueur& joueur) const {
    int wildCount = 0;
    for (const Champion& champ : joueur.getStackChampion().getChampions()) {
        if (champ.getFaction() == FactionVerte) {
            wildCount++;
        }
    }
    for (const Action& action : joueur.getMain()) {     // pas sûr de celle-là
        if (action.getFaction() == FactionVerte) {
            wildCount++;
        }
    }
    carte.getEffetsBasiqueChoix1().emplace_back(Effet(wildCount, DEGAT));
}

//17 +{1 combat} for each other champion you have in play.
void EffetTextuel::combat1PerChampion(Carte& carte, Joueur& joueur) const {
    int championCount = 0;
    for (const Champion& champ : joueur.getStackChampion().getChampions()) {
        championCount++;
    }
    carte.getEffetsBasiqueChoix1().emplace_back(Effet(championCount, DEGAT));
}
//18 +{2 combat} for each champion you have in play.
void EffetTextuel::combat2PerChampion(Carte& carte, Joueur& joueur) const {
    int championCount = 0;
    for (const Champion& champ : joueur.getStackChampion().getChampions()) {
        championCount++;
    }
    carte.getEffetsBasiqueChoix1().emplace_back(Effet(2 * championCount, DEGAT));
}
//19 +{1 health} for each champion you have in play.
void EffetTextuel::health1PerChampion(Carte& carte, Joueur& joueur) const {
    int championCount = 0;
    for (const Champion& champ : joueur.getStackChampion().getChampions()) {
        championCount++;
    }
    carte.getEffetsBasiqueChoix1().emplace_back(Effet(championCount, SOIN));
}

//20 +{2 health} for each champion you have in play.
void EffetTextuel::health2PerChampion(Carte& carte, Joueur& joueur) const {
    int championCount = 0;
    for (const Champion& champ : joueur.getStackChampion().getChampions()) {
        championCount++;
    }
    carte.getEffetsBasiqueChoix1().emplace_back(Effet(2 * championCount, SOIN));
}

//21 sacrifice
void EffetTextuel::sacrifice(Carte& carte, MainJoueur& main) const {
    main.retirerCarte(carte);
    ZoneDeSacrifice::getInstance().ajouterCarte(carte);
}

