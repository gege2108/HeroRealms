#ifndef PIOCHE_H
#define PIOCHE_H

#include <vector>
#include "Carte.h"

class Pioche {
public:
    Pioche();
    explicit Pioche(const std::vector<Carte*>& cartes);

    const std::vector<Carte*>& getCartes() const;
    void setCartes(const std::vector<Carte*>& c);

    void push(Carte* c);
    bool draw(Carte* c);
    void clear();

private:
    std::vector<Carte*> cartes;
};

#endif // PIOCHE_H