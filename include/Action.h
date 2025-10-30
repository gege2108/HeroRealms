#ifndef ACTION_H
#define ACTION_H

#include <vector>
#include "Carte.h"
#include "EffetTextuel.h"
#include "Faction.h"

class Action : public Carte {
public:
    Action() = default;
    Action(const std::string& nom) : Carte(nom) {}

    // Nouveau constructeur pour correspondre aux paramètres utilisés dans action.cpp
    Action(Faction _faction, const std::string& nom, int prix,
           const std::vector<Effet>& effetsBasiques1,
           const std::vector<Effet>& effetsBasiques2,
           const std::vector<EffetTextuel>& effetsTextuels1,
           const std::vector<EffetTextuel>& effetsTextuels2,
           const std::vector<Effet>& effetsCombo,
           const std::vector<EffetTextuel>& effetsTextuelsCombo)
        : Carte(nom), faction(_faction), prix(prix)
    {
        this->effetsBasiqueChoix1 = effetsBasiques1;
        this->ListEffetBasiqueChoix2 = effetsBasiques2;
        this->ListEffetTextuelChoix1 = effetsTextuels1;
        this->ListEffetTextuelChoix2 = effetsTextuels2;
        this->ListEffetBasiqueCombo = effetsCombo;
        this->ListEffetTextuelCombo = effetsTextuelsCombo;
    }

    // void utiliserEffet() override;

    int getPrix() const { return prix; }
    void setPrix(int p) { prix = p; }

    // Getter pour la faction
    Faction getFaction() const { return faction; }
    
    // Setter pour peutFaireCombo
    void setPeutFaireCombo(bool b) { peutFaireCombo = b; }
    
    // Getter pour peutFaireCombo
    bool getPeutFaireCombo() const { return peutFaireCombo; }

    std::vector<Effet>& getListEffetBasiqueChoix2() { return ListEffetBasiqueChoix2; }
    std::vector<EffetTextuel>& getListEffetTextuelChoix1() { return ListEffetTextuelChoix1; }
    std::vector<EffetTextuel>& getListEffetTextuelChoix2() { return ListEffetTextuelChoix2; }
    
    // Getters pour les effets combo
    const std::vector<Effet>& getListEffetBasiqueCombo() const { return ListEffetBasiqueCombo; }
    const std::vector<EffetTextuel>& getListEffetTextuelCombo() const { return ListEffetTextuelCombo; }

    // Déclaration seulement (implémentation dans action.cpp)
    std::string toString() const override;

protected:
    Faction faction;
    int prix = 0;

    std::vector<Effet> ListEffetBasiqueChoix2;
    std::vector<EffetTextuel> ListEffetTextuelChoix1;
    std::vector<EffetTextuel> ListEffetTextuelChoix2;

    bool peutFaireCombo = false;
    std::vector<Effet> ListEffetBasiqueCombo;
    std::vector<EffetTextuel> ListEffetTextuelCombo;
};

#endif // ACTION_H