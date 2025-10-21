#ifndef ACTION_H
#define ACTION_H

#include <vector>
#include "Carte.h"
#include "EffetTextuel.h"

class Action : public Carte {
public:
    //Temporaire pour l'instant Instancier toutes les differentes factions possibles dans un autre fichier
    //TODO : déplacer cette énumération dans un fichier approprié et bien l'initialiser 
    enum Faction { FactionJaune, FactionRouge, FactionBleue, FactionVerte, NEUTRE };

    Action() = default;
    Action(const std::string& nom) : Carte(nom) {}

   // void utiliserEffet() override;

    int getPrix() const { return prix; }
    void setPrix(int p) { prix = p; }

    std::vector<Effet>& getListEffetBasiqueChoix2() { return ListEffetBasiqueChoix2; }
    std::vector<EffetTextuel>& getListEffetTextuelChoix1() { return ListEffetTextuelChoix1; }
    std::vector<EffetTextuel>& getListEffetTextuelChoix2() { return ListEffetTextuelChoix2; }

protected:
    Faction faction = FactionJaune;
    int prix = 0;

    std::vector<Effet> ListEffetBasiqueChoix2;
    std::vector<EffetTextuel> ListEffetTextuelChoix1;
    std::vector<EffetTextuel> ListEffetTextuelChoix2;

    bool peutFaireCombo = false;
    std::vector<Effet> ListEffetBasiqueCombo;
    std::vector<EffetTextuel> ListEffetTextuelCombo;
};

#endif // ACTION_H