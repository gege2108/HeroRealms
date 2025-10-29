#ifndef EFFETTEXTUEL_H
#define EFFETTEXTUEL_H

class EffetTextuel {
public:
    EffetTextuel() : id(0) {}
    explicit EffetTextuel(int id) : id(id) {}
    int getId() const { return id; }
    void setId(int v) { id = v; }

    // placeholder : implémenter toutes les méthodes correspondant aux effets textuels
    void executer() const;

    //1 Draw a card. : utiliser Pioche::piocher(MainJoueur& main)
    void EffetTextuel::discardOpponentCard(Joueur& opponent, MainJoueur& main) const; // 2 Target opponent discards a card.
    void stunChampion(Joueur& opponent) const; // 3 Stun target champion.
    void drawAndDiscard(Joueur& player) const; // 4 You may draw a card, then discard a card.
    void drawAndDiscardTwo(Joueur& player) const; // 5 You may draw up to two cards, then discard that many cards.

    //à faire :
//6 Put the next action you acquire this turn on top of your deck.
//7 Put the next card you acquire this turn into your hand.
//8 Take a champion from your discard pile and put it on top of your deck.
//9 Take a card from your discard pile and put it on top of your deck.
//10 Prepare a champion

    void EffetTextuel::sacrificeUneCarte(Joueur& joueur) const; // 10 You may sacrifice a card from your hand or discard pile.
    void sacrificeDeuxCartes(Joueur& joueur) const; // 11 You may sacrifice up to two cards in your hand and/or discard pile.
    void EffetTextuel::sacrificeFor3Combat(Carte& carte, Joueur& joueur, MainJoueur& main) const; //13 You may sacrifice a card in your hand or discard pile. If you do, gain an additional {3 combat}.
    void EffetTextuel::sacrificeFor2Combat(Carte& carte, Joueur& joueur, MainJoueur& main) const; //14 You may sacrifice a card in your hand or discard pile. If you do, gain an additional {2 combat}.
    
    void EffetTextuel::combat1PerGuard(Carte& carte, Joueur& joueur) const; //15 +{1 combat} for each other guard you have in play.
    void EffetTextuel::combat1PerWild(Carte& carte, Joueur& joueur) const; //16 +{1 combat} for each other {Wild} card you have in play.
    void EffetTextuel::combat1PerChampion(Carte& carte, Joueur& joueur) const; //17 +{1 combat} for each other champion you have in play.
    void EffetTextuel::combat2PerChampion(Carte& carte, Joueur& joueur) const; //18 +{2 combat} for each champion you have in play.
    void EffetTextuel::health1PerChampion(Carte& carte, Joueur& joueur) const; //19 +{1 health} for each champion you have in play.
    void EffetTextuel::health2PerChampion(Carte& carte, Joueur& joueur) const; //20 +{2 health} for each champion you have in play.



    void sacrifice(Carte& carte, MainJoueur& main) const; // 21
     sacrifice

private:
    int id;
};

#endif // EFFETTEXTUEL_H