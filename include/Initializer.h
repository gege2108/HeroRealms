#ifndef INITIALIZER_H
#define INITIALIZER_H

#include "Plateau.h"
#include "Joueur.h"
#include "Marche.h"
#include "ZoneDeSacrifice.h"
#include "Action.h"
#include "Champion.h"
#include "GemmeDeFeu.h"
#include "CarteDeBase.h"
#include "MainJoueur.h"
#include "Pioche.h"
#include "Defausse.h"

class Initializer {
public:
    static Plateau initializePlateau();    
    static Joueur initializeJoueur();
    static Marche initializeMarche();
    static std::vector<CarteDeBase*> createCartesDeBase();
    static std::vector<Action*> createActions();
    static std::vector<Champion*> createChampions();
    static std::vector<GemmeDeFeu*> createGemmesDeFeu(int nombre = 16);

private:
    Initializer() = default; // Classe utilitaire, pas d'instanciation
};

#endif // INITIALIZER_H
