#include "Joueur.h"

int Joueur::getPointDeVie() const { return pointDeVie; }
void Joueur::setPointDeVie(int v) { pointDeVie = v; }

// Versions non-const (garder seulement ces lignes)
MainJoueur& Joueur::getMain() { return mainJoueur; }
Pioche& Joueur::getPioche() { return pioche; }
Defausse& Joueur::getDefausse() { return defausse; }
StackChampion& Joueur::getStackChampion() { return stackChampion; }

// Versions const (garder seulement ces lignes)
const MainJoueur& Joueur::getMain() const { return mainJoueur; }
const Pioche& Joueur::getPioche() const { return pioche; }
const Defausse& Joueur::getDefausse() const { return defausse; }
const StackChampion& Joueur::getStackChampion() const { return stackChampion; }

// Setters
void Joueur::setMain(const MainJoueur& m) { mainJoueur = m; }
void Joueur::setPioche(const Pioche& p) { pioche = p; }
void Joueur::setDefausse(const Defausse& d) { defausse = d; }
void Joueur::setStackChampion(const StackChampion& s) { stackChampion = s; }

int Joueur::getArgent() const { return argent; }
void Joueur::setArgent(int a) { argent = a; }

