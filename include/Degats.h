#ifndef DEGATS_H
#define DEGATS_H

#include "Competence.h"

class Degats : public Competence {
public:
    Degats() = default;
    explicit Degats(int val) : Competence(val) {}
    std::string toString() const override {
        return std::string("Degats: ") + std::to_string(getValeur());
    }
};

#endif // DEGATS_H