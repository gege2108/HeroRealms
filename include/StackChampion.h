#ifndef STACKCHAMPION_H
#define STACKCHAMPION_H

#include <vector>
#include "Carte.h"

class StackChampion {
public:
    StackChampion();
    explicit StackChampion(const std::vector<Carte*>& cartes);

    const std::vector<Carte*>& getCartes() const;
    void setCartes(const std::vector<Carte*>& c);

    void push(Carte* c);
    bool pop(Carte* c);
    void clear();

private:
    std::vector<Carte*> cartes;
};

#endif // STACKCHAMPION_H