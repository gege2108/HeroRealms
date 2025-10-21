#ifndef EFFET_H
#define EFFET_H

#include "TypeEffet.h"
#include "Competence.h"
#include <string>

class Effet {
public:
    Effet();
    Effet(const Competence& competence, TypeEffet type);

    Competence getCompetence() const;
    void setCompetence(const Competence& c);

    TypeEffet getType() const;
    void setType(TypeEffet t);
    std::string toString() const;

private:
    Competence competence;
    TypeEffet type;
};

#endif // EFFET_H