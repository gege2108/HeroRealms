#ifndef JOUEUR_H
#define JOUEUR_H

#include "MainJoueur.h"
#include "Pioche.h"
#include "StackChampion.h"
#include "Defausse.h"
#include "Champion.h"

class Joueur {
public:
    Joueur();

    int getPointDeVie() const;
    void setPointDeVie(int v);

    // getters et setters pour les containers
    const MainJoueur& getMain() const;
    void setMain(const MainJoueur& m);

    const Pioche& getPioche() const;
    void setPioche(const Pioche& p);

    const StackChampion& getStackChampion() const;
    void setStackChampion(const StackChampion& s);

    const Defausse& getDefausse() const;
    void setDefausse(const Defausse& d);



   

private:
    MainJoueur mainJoueur;
    Pioche pioche;
    StackChampion stackChampion;
    Defausse defausse;
    int pointDeVie = 0;
};

#endif // JOUEUR_H