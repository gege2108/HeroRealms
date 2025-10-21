#ifndef DEGATS_H
#define DEGATS_H

#include "Competence.h"

class Degats : public Competence {
public:
    Degats() = default;
    explicit Degats(int val) : Competence(val) {}
};

#endif // DEGATS_H