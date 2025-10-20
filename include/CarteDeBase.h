#ifndef CARTEDEBASE_H
#define CARTEDEBASE_H

#include "Carte.h"

class CarteDeBase : public Carte {
public:
    CarteDeBase() = default;
    CarteDeBase(const std::string& nom) : Carte(nom) {}
    void utiliserEffet() override;
};

#endif // CARTEDEBASE_H