#ifndef ARGENT_H
#define ARGENT_H

#include "Competence.h"

class Argent : public Competence {
public:
    Argent() = default;
    explicit Argent(int val) : Competence(val) {}
};

#endif // ARGENT_H