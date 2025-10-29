#include "Joueur.h"


int Joueur::getPointDeVie() const { return pointDeVie; }
void Joueur::setPointDeVie(int v) { pointDeVie = v; }
void Joueur::subirDegats(int degats) { pointDeVie -= degats; }
void Joueur::soigner(int soin) { pointDeVie += soin; }

const MainJoueur& Joueur::getMain() const { return mainJoueur; }
void Joueur::setMain(const MainJoueur& m) { mainJoueur = m; }

const Pioche& Joueur::getPioche() const { return pioche; }
void Joueur::setPioche(const Pioche& p) { pioche = p; }

const StackChampion& Joueur::getStackChampion() const { return stackChampion; }
void Joueur::setStackChampion(const StackChampion& s) { stackChampion = s; }

const Defausse& Joueur::getDefausse() const { return defausse; }
void Joueur::setDefausse(const Defausse& d) { defausse = d; }

