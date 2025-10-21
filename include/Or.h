#ifndef OR_H
#define OR_H

#include "Competence.h"

class Or : public Competence {
public:
    Or() = default;
    explicit Or(int val) : Competence(val) {}
    std::string toString() const override {
        return std::string("Or: ") + std::to_string(getValeur());
    }
};

#endif // OR_H