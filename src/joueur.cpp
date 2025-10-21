#include "Joueur.h"

Joueur::Joueur() = default;

int Joueur::getPointDeVie() const { return pointDeVie; }
void Joueur::setPointDeVie(int v) { pointDeVie = v; }

const MainJoueur& Joueur::getMain() const { return mainJoueur; }
void Joueur::setMain(const MainJoueur& m) { mainJoueur = m; }

const Pioche& Joueur::getPioche() const { return pioche; }
void Joueur::setPioche(const Pioche& p) { pioche = p; }

const StackChampion& Joueur::getStackChampion() const { return stackChampion; }
void Joueur::setStackChampion(const StackChampion& s) { stackChampion = s; }

const Defausse& Joueur::getDefausse() const { return defausse; }
void Joueur::setDefausse(const Defausse& d) { defausse = d; }

