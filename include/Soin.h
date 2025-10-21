#ifndef SOIN_H
#define SOIN_H

#include "Competence.h"

class Soin : public Competence {
public:
    Soin() = default;
    explicit Soin(int val) : Competence(val) {}
    std::string toString() const override {
        return std::string("Soin: ") + std::to_string(getValeur());
    }
};

#endif // SOIN_H