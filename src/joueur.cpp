#include "Joueur.h"


int Joueur::getPointDeVie() const { return pointDeVie; }
void Joueur::setPointDeVie(int v) { pointDeVie = v; }

MainJoueur& Joueur::getMain() { return mainJoueur; }
const MainJoueur& Joueur::getMain() const { return mainJoueur; }

Pioche& Joueur::getPioche() { return pioche; }
const Pioche& Joueur::getPioche() const { return pioche; }

const StackChampion& Joueur::getStackChampion() const { return stackChampion; }
void Joueur::setStackChampion(const StackChampion& s) { stackChampion = s; }

const Defausse& Joueur::getDefausse() const { return defausse; }
void Joueur::setDefausse(const Defausse& d) { defausse = d; }

int Joueur::getArgent() const { return argent; }
void Joueur::setArgent(int a) { argent = a; }

void Joueur::setMain(const MainJoueur& m) { mainJoueur = m; }
void Joueur::setPioche(const Pioche& p) { pioche = p; }

