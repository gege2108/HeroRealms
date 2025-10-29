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

    //constructeur sans choix
    Action(Faction faction, const std::string& nom, int prix, const std::vector<Effet>& effets1, const std::vector<EffetTextuel>& effetsTextuels1, const std::vector<Effet>& effets2, const std::vector<EffetTextuel>& effetsTextuels2) 
        : Carte(nom, effets1) {
        this->ListEffetTextuelChoix1 = effetsTextuels1;

        this->ListEffetBasiqueCombo = effets2;
        this->ListEffetTextuelCombo = effetsTextuels2;

        this->faction = faction;
        this->prix = prix;
    }

    //constructeur avec choix
    Action(Faction faction, const std::string& nom, int prix, const std::vector<Effet>& effets1, const std::vector<EffetTextuel>& effetsTextuels1, const std::vector<Effet>& effets2, const std::vector<EffetTextuel>& effetsTextuels2, 
        const std::vector<Effet>& effets3, const std::vector<EffetTextuel>& effetsTextuels3) 
        : Carte(nom, effets1) {
        this->ListEffetTextuelChoix1 = effetsTextuels1;

        this->ListEffetBasiqueCombo = effets2;
        this->ListEffetTextuelCombo = effetsTextuels2;

        this->ListEffetBasiqueChoix2 = effets3;
        this->ListEffetTextuelChoix2 = effetsTextuels3;

        this->faction = faction;
        this->prix = prix;
    }


   // void utiliserEffet() override;
    int getPrix() const { return prix; }
    void setPrix(int p) { prix = p; }
    void setPeutFaireCombo(bool b) { peutFaireCombo = b; }
    bool getPeutFaireCombo() const { return peutFaireCombo; }
    void setFaction(Faction f) { faction = f; }
    Faction getFaction() const { return faction; }

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