#ifndef STACKCHAMPION_H
#define STACKCHAMPION_H

#include <vector>
#include "Carte.h"
#include "Champion.h"

class StackChampion {
public:
    StackChampion();
    explicit StackChampion(const std::vector<Carte*>& cartes);

    const std::vector<Carte*>& getCartes() const;
    void setCartes(const std::vector<Carte*>& c);

    void push(Carte* c);
    bool pop(Carte* c);
    void clear();

    // Fonction pour récupérer les champions de la stack
    std::vector<Champion*> getChampions() const;
    std::vector<Champion*> getChampions();

    std::vector<Champion*>& getGardes();
    //const std::vector<Champion*>& getGardes() const;
    void setGardes(const std::vector<Champion*>& g);
    void addGarde(Champion* c);

    // Fonction pour enlever un champion spécifique
    bool removeChampion(Champion* champion);

private:
    std::vector<Carte*> cartes;
    std::vector<Champion*> gardes;
};

#endif // STACKCHAMPION_H