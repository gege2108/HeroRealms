#ifndef CHAMPION_H
#define CHAMPION_H

#include "Action.h"

class Champion : public Action {
public:
    Champion() = default;
    Champion(const std::string& nom) : Action(nom) {}
    Champion(Faction _faction, const std::string& nom, int prix,
             const std::vector<Effet>& effetsBasiques1,
             const std::vector<Effet>& effetsBasiques2,
             const std::vector<EffetTextuel>& effetsTextuels1,
             const std::vector<EffetTextuel>& effetsTextuels2,
             const std::vector<Effet>& effetsCombo,
             const std::vector<EffetTextuel>& effetsTextuelsCombo,
             int pv, bool garde = false, bool defense = false)
        : Action(_faction, nom, prix, effetsBasiques1, effetsBasiques2,
                 effetsTextuels1, effetsTextuels2, effetsCombo, effetsTextuelsCombo),
          pointDeVie(pv), isGarde(garde), isDefense(defense) {}

    int getPointDeVie() const { return pointDeVie; }
    void setPointDeVie(int v) { pointDeVie = v; }

    bool getIsGarde() const { return isGarde; }
    void setIsGarde(bool b) { isGarde = b; }

    bool getIsDefense() const { return isDefense; }
    void setIsDefense(bool b) { isDefense = b; }

    // Ajouter les méthodes pour le combo et la faction
    Faction getFaction() const { return faction; }
    void setFaction(Faction f) { faction = f; }
    
    bool getPeutFaireCombo() const { return peutFaireCombo; }
    void setPeutFaireCombo(bool b) { peutFaireCombo = b; }

    std::string toString() const override {
        std::string result = "Champion: " + nom;

        // Affichage de la faction
        result += " | Faction: ";
        switch(faction) {
            case Faction::FactionJaune: result += "Impériale"; break;
            case Faction::FactionBleu: result += "Guilde"; break;
            case Faction::FactionRouge: result += "Nécros"; break;
            case Faction::FactionVert: result += "Sauvage"; break;
        }

        result += " | Prix: " + std::to_string(prix) + " or";
        result += " | Points de Vie: " + std::to_string(pointDeVie);
        result += " | Garde: " + std::string(isGarde ? "Oui" : "Non");
        result += " | Défense: " + std::string(isDefense ? "Oui" : "Non");

        // Affichage de peutFaireCombo
        result += " | Peut faire combo: ";
        result += (peutFaireCombo ? "Oui" : "Non");
        
        // Effets basiques choix 1
        if (!effetsBasiqueChoix1.empty()) {
            result += " | Effets basiques choix 1: [";
            for (size_t i = 0; i < effetsBasiqueChoix1.size(); ++i) {
                if (i > 0) result += ", ";
                result += effetsBasiqueChoix1[i].toString();
            }
            result += "]";
        }
        
        // Effets basiques choix 2
        if (!ListEffetBasiqueChoix2.empty()) {
            result += " | Effets basiques choix 2: [";
            for (size_t i = 0; i < ListEffetBasiqueChoix2.size(); ++i) {
                if (i > 0) result += ", ";
                result += ListEffetBasiqueChoix2[i].toString();
            }
            result += "]";
        }
        
        // Effets combo
        if (!ListEffetBasiqueCombo.empty()) {
            result += " | Effets Combo: [";
            for (size_t i = 0; i < ListEffetBasiqueCombo.size(); ++i) {
                if (i > 0) result += ", ";
                result += ListEffetBasiqueCombo[i].toString();
            }
            result += "]";
        }
        
        // Effets textuels choix 1
        if (!ListEffetTextuelChoix1.empty()) {
            result += " | Effets textuels choix 1: [";
            for (size_t i = 0; i < ListEffetTextuelChoix1.size(); ++i) {
                if (i > 0) result += ", ";
                result += ListEffetTextuelChoix1[i].toString();
            }
            result += "]";
        }
        
        // Effets textuels choix 2
        if (!ListEffetTextuelChoix2.empty()) {
            result += " | Effets textuels choix 2: [";
            for (size_t i = 0; i < ListEffetTextuelChoix2.size(); ++i) {
                if (i > 0) result += ", ";
                result += ListEffetTextuelChoix2[i].toString();
            }
            result += "]";
        }

        return result;
    }

private:
    int pointDeVie = 0;
    bool isGarde = false;
    bool isDefense = false;
};

#endif // CHAMPION_H