#include "EffetTextuel.h"

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

//6 Put the next action you acquire this turn on top of your deck.
//7 Put the next card you acquire this turn into your hand.
//8 Take a champion from your discard pile and put it on top of your deck.
//9 Take a card from your discard pile and put it on top of your deck.
//10 Prepare a champion.

//11 You may sacrifice up to two cards in your hand and/or discard pile.
//12 You may sacrifice a card in your hand or discard pile.
//13 You may sacrifice a card in your hand or discard pile. If you do, gain an additional {3 combat}.
//14 You may sacrifice a card in your hand or discard pile. If you do, gain an additional {2 combat}.

//15 +{1 combat} for each other guard you have in play.
//16 +{1 combat} for each other {Wild} card you have in play.
//17 +{1 combat} for each other champion you have in play.
//18 +{2 combat} for each champion you have in play.
//19 +{1 health} for each champion you have in play.
//20 +{1 health} for each champion you have in play.
//21 +{2 health} for each champion you have in play.

//22 sacrifice
void EffetTextuel::sacrifice(Carte& carte, MainJoueur& main) const {
    main.retirerCarte(carte);
    ZoneDeSacrifice::getInstance().ajouterCarte(carte);
}

