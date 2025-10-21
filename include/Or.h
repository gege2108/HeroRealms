#ifndef OR_H
#define OR_H

#include "Competence.h"

class Or : public Competence {
public:
    Or() = default;
    explicit Or(int val) : Competence(val) {}
};

#endif // OR_H