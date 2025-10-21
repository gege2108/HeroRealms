#ifndef MAINJOUEUR_H
#define MAINJOUEUR_H

#include <vector>
#include "Carte.h"

class MainJoueur {
public:
    MainJoueur();
    explicit MainJoueur(const std::vector<Carte*>& cartes);

    const std::vector<Carte*>& getCartes() const;
    void setCartes(const std::vector<Carte*>& c);

    void addCarte(Carte* c);
    bool removeCarte(Carte* c);
    void clear();

private:
    std::vector<Carte*> cartes;
};

#endif // MAINJOUEUR_H