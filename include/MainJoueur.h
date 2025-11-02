#ifndef MAINJOUEUR_H
#define MAINJOUEUR_H

#include <vector>
#include "Carte.h"
#include "CarteDeBase.h"
#include "GemmeDeFeu.h"
#include "Champion.h"
#include "Action.h"

class MainJoueur {
public:
    MainJoueur();
    explicit MainJoueur(const std::vector<Carte*>& cartes);

    const std::vector<Carte*>& getCartes() const;
    void setCartes(const std::vector<Carte*>& c);

    void addCarte(Carte* c);
    bool removeCarte(Carte* c);
    void clear();

    // Retourne une liste de pointeurs vers les CartesDeBase présentes dans la main
    std::vector<CarteDeBase*> getCartesDeBase() const;
    std::vector<GemmeDeFeu*> getGemmesDeFeu() const;
    std::vector<Champion*> getChampions() const;  // Ajouter cette ligne
    std::vector<Action*> getActions() const;      // Ajouter cette ligne

private:
    std::vector<Carte*> cartes;
};

#endif // MAINJOUEUR_H