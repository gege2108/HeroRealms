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

    std::vector<Effet>& getListEffetBasiqueChoix2() { return ListEffetBasiqueChoix2; }
    std::vector<EffetTextuel>& getListEffetTextuelChoix1() { return ListEffetTextuelChoix1; }
    std::vector<EffetTextuel>& getListEffetTextuelChoix2() { return ListEffetTextuelChoix2; }

    // Méthode toString pour afficher tous les attributs
    std::string toString() const override {
        std::string result = "Action: " + nom;
        
        // Affichage de la faction
        result += " | Faction: ";
        switch(faction) {
            case Faction::FactionJaune: result += "Impériale"; break;
            case Faction::FactionBleu: result += "Guilde"; break;
            case Faction::FactionRouge: result += "Nécros"; break;
            case Faction::FactionVert: result += "Sauvage"; break;
        }
        
        result += " | Prix: " + std::to_string(prix) + " or";
        
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