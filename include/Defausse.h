#ifndef DEFAUSSE_H
#define DEFAUSSE_H

#include <vector>
#include "Carte.h"

class Defausse {
public:
    Defausse();
    explicit Defausse(const std::vector<Carte*>& cartes);

    const std::vector<Carte*>& getCartes() const;
    void setCartes(const std::vector<Carte*>& c);

    void addCarte(Carte* c);
    bool remove(Carte* c);
    void clear();
    void removeCarte(Carte* carte);
    void melangeDefausse();
    void addCarteOnTop(Carte* c);

private:
    std::vector<Carte*> cartes;
};

#endif // DEFAUSSE_H