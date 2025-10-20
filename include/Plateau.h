#ifndef PLATEAU_H
#define PLATEAU_H

#include "Joueur.h"
#include "Marche.h"
#include "ZoneDeSacrifice.h"

class Plateau {
public:
    Joueur joueur1;
    Joueur joueur2;
    Marche marche;
    ZoneDeSacrifice zoneDeSacrifice;
};

#endif // PLATEAU_H