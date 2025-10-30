#include "Action.h"
#include "EffetTextuel.h"
#include "Joueur.h"
#include "Champion.h"
#include <map>

// Implémentation de toString() déplacée ici pour éviter les problèmes d'inclusion
std::string Action::toString() const {
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
    
    return result;
}

