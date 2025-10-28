#ifndef EFFET_H
#define EFFET_H

#include "TypeEffet.h"
#include "Competence.h"
#include <string>

class Effet {
public:
    Effet();
    Effet(int valeur, TypeEffet type);
    Effet(int valeur, TypeEffet type, const std::string& desc) : valeur(valeur), type(type), description(desc) {}

    int getValeur() const;
    void setValeur(int v);

    TypeEffet getType() const;
    void setType(TypeEffet t);
    std::string toString() const;
    std::string getDescription() const { return description; }
    void setDescription(const std::string& desc) { description = desc; }

private:
    int valeur;
    TypeEffet type;
    std::string description;
};

#endif // EFFET_H