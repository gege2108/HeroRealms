#ifndef ZONEDESACRIFICE_H
#define ZONEDESACRIFICE_H

#include <vector>
#include "Carte.h"

class ZoneDeSacrifice {
public:
    ZoneDeSacrifice();
    explicit ZoneDeSacrifice(const std::vector<Carte*>& cartes);

    const std::vector<Carte*>& getCartes() const;
    void setCartes(const std::vector<Carte*>& c);

    void add(Carte* c);
    bool remove(Carte* c);
    void clear();

private:
    std::vector<Carte*> cartes;
};

#endif // ZONEDESACRIFICE_H