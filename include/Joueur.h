#ifndef JOUEUR_H
#define JOUEUR_H

#include "Main.h"
#include "Pioche.h"
#include "StackChampion.h"
#include "Defausse.h"
#include "Champion.h"

class Joueur {
public:
    Joueur() = default;

    int getPointDeVie() const { return pointDeVie; }
    void setPointDeVie(int v) { pointDeVie = v; }

    Main main;
    Pioche pioche;
    StackChampion stackChampion;
    Defausse defausse;
    Champion champion;

private:
    int pointDeVie = 0;
};

#endif // JOUEUR_H