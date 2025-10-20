#ifndef ATTAQUE_H
#define ATTAQUE_H

#include "Competence.h"

class Attaque : public Competence {
public:
    Attaque() = default;
    explicit Attaque(int val) : Competence(val) {}
};

#endif // ATTAQUE_H