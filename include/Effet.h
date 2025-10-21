#ifndef EFFET_H
#define EFFET_H

#include "TypeEffet.h"
#include "Competence.h"
#include <string>

class Effet {
public:
    Effet();
    Effet(int valeur, TypeEffet type);

    int getValeur() const;
    void setValeur(int v);

    TypeEffet getType() const;
    void setType(TypeEffet t);
    std::string toString() const;

private:
    int valeur;
    TypeEffet type;
};

#endif // EFFET_H