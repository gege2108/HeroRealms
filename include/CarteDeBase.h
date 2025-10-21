#ifndef CARTEDEBASE_H
#define CARTEDEBASE_H

#include "Carte.h"

class CarteDeBase : public Carte {
public:
    CarteDeBase() = default;
    CarteDeBase(const std::string& nom) : Carte(nom) {}
    Competence utiliserEffet() override;

    std::string toString() const {
        std::string description = Carte::toString();
        description += " (Type: CarteDeBase)";
        return description;
    }
};

#endif // CARTEDEBASE_H