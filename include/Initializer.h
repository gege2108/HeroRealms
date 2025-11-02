#ifndef INITIALIZER_H
#define INITIALIZER_H

#include "Plateau.h"
#include "Joueur.h"
#include "Marche.h"
#include "CarteDeBase.h"
#include "Action.h"
#include "Champion.h"
#include "GemmeDeFeu.h"
#include <vector>

class Initializer {
public:
    static Plateau initializePlateau();
    static void initializePlateauRef(Plateau& plateau);
    
    // Méthodes auxiliaires
    static Joueur initializeJoueur();
    static Marche initializeMarche();
    static std::vector<CarteDeBase*> createCartesDeBase();
    static std::vector<Action*> createActions();
    static std::vector<Champion*> createChampions();
    static std::vector<GemmeDeFeu*> createGemmesDeFeu(int nombre);
};

#endif // INITIALIZER_H
