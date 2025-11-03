#ifndef EFFETTEXTUEL_H
#define EFFETTEXTUEL_H

#include <string>

// Forward declaration pour éviter l'inclusion circulaire
class Joueur;

class EffetTextuel {
public:
    EffetTextuel() : id(0), description("") {}
    explicit EffetTextuel(int id, const std::string& desc) : id(id), description(desc) {}
    int getId() const { return id; }
    void setId(int v) { id = v; }
    std::string getDescription() const { return description; }
    void setDescription(const std::string& desc) { description = desc; }

    
    std::string toString() const {
        return description;
    }

    bool sacrificeFromHand(Joueur& joueur);
    bool sacrificeFromDiscard(Joueur& joueur);


    // Méthodes utilisant Joueur
    static void drawACard(Joueur& joueur); // id : 1
    static void discardOpponentCard(Joueur& opponent); // id : 2
    static void stunChampion(Joueur& opponent); // id : 3
    static void drawAndDiscard(Joueur& joueur); // id : 4
    static void defenseModActivated(Joueur& joueur); // id : 5
    static void drawTwoAndDiscardTwo(Joueur& joueur);  // id : 6

    // Nouveaux effets pour les champions
    static void gain2HealthPerChampion(Joueur& joueur);      // id : 7
    static void gainCombatPerOtherGuard(Joueur& joueur);    // id : 8
    static void gainCombatPerOtherChampion(Joueur& joueur); // id : 9
    static void gain1HealthPerChampion(Joueur& joueur);    // id : 10
    static void gain2CombatPerChampion(Joueur& joueur);    // id : 11
    static void gain1CombatPerOtherChampionWild(Joueur& joueur);  // id : 12
    static void placeCardFromDiscardOnTopOfDraw(Joueur& joueur); // id : 13
    static void setNextActionAcquiredOnTop(Joueur& joueur); // id : 14

    // Fonctions de sacrifice publiques
    bool sacrificeCard(Joueur& joueur);                    // id : 15
    void sacrificeCardForCombat3(Joueur& joueur);         // id : 16
    void sacrificeCardForCombat2(Joueur& joueur);         // id : 17


    static void handleIdEffetTextuel(int id, Joueur& joueur, Joueur& adversaire);

private:
    int id;
    std::string description;
};

#endif // EFFETTEXTUEL_H