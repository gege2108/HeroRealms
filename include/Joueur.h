#ifndef JOUEUR_H
#define JOUEUR_H

#include "MainJoueur.h"
#include "Pioche.h"
#include "StackChampion.h"
#include "Defausse.h"
#include "Champion.h"

class Joueur {
public:
	// Remplacement du constructeur par défaut par un constructeur qui initialise tous les attributs.
	Joueur(const MainJoueur& m = MainJoueur(),
	       const Pioche& p = Pioche(),
	       const StackChampion& s = StackChampion(),
	       const Defausse& d = Defausse(),
	       int pv = 30)
	    : mainJoueur(m), pioche(p), stackChampion(s), defausse(d), pointDeVie(pv) {}

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
	int pointDeVie;
};

#endif // JOUEUR_H