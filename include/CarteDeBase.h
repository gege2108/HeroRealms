#ifndef CARTEDEBASE_H
#define CARTEDEBASE_H

#include "Carte.h"
#include "Effet.h"
#include <vector>
#include <string>

class CarteDeBase : public Carte {
public:
    CarteDeBase() = default;
    CarteDeBase(const std::string& nom) : Carte(nom) {}

    // Nouveau constructeur : initialise le nom (via Carte) et copie les effets
    CarteDeBase(const std::string& nom, const std::vector<Effet>& effets)
        : Carte(nom) {
        // Assigne les effets au champ protected hérité depuis la classe Carte
        this->effetsBasiqueChoix1 = effets;
    }

    // Définition inline du destructeur pour éviter déclaration non définie
    virtual ~CarteDeBase() override = default;

    // Implémentation par défaut de la méthode pure virtuelle de Carte.
    // Comportement minimal : ne fait rien (no-op). Modifier si vous voulez appliquer
    // directement les effets (nécessite connaissance des cibles).
    

    // Accesseur pour les effets basiques (utilisé par Plateau)
    const std::vector<Effet>& getEffetsBasiqueChoix1() const override {
        return effetsBasiqueChoix1; // champ hérité de Carte (protected)
    }

    std::string toString() const override {
        std::string description = Carte::toString();
        description += " (Type: CarteDeBase)";
        return description;
    }

private:
    // NOTE: pas d'attribut local `effetsBasiqueChoix1` ici : on utilise le champ protected de Carte.
};

#endif // CARTEDEBASE_H