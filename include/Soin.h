#ifndef SOIN_H
#define SOIN_H

#include "Competence.h"

class Soin : public Competence {
public:
    Soin() = default;
    explicit Soin(int val) : Competence(val) {}
};

#endif // SOIN_H