#ifndef JOUEUR_H
#define JOUEUR_H

#include "MainJoueur.h"
#include "Pioche.h"
#include "StackChampion.h"
#include "Defausse.h"

class Joueur {
public:
	// Remplacement du constructeur par défaut par un constructeur qui initialise tous les attributs.
	Joueur(const MainJoueur& m = MainJoueur(),
	       const Pioche& p = Pioche(),
	       const StackChampion& s = StackChampion(),
	       const Defausse& d = Defausse(),
	       int pv = 30, int _argent = 0)
	    : mainJoueur(m), pioche(p), stackChampion(s), defausse(d), argent(_argent), pointDeVie(pv) {}

	int getPointDeVie() const;
	void setPointDeVie(int v);

	// Versions non-const
	MainJoueur& getMain();
	Pioche& getPioche();
	Defausse& getDefausse();

	// Versions const  
	const MainJoueur& getMain() const;
	const Pioche& getPioche() const;
	const Defausse& getDefausse() const;

	// Setters
	void setMain(const MainJoueur& m);
	void setPioche(const Pioche& p);
	void setDefausse(const Defausse& d);

	int getArgent() const;
	void setArgent(int a);

	const StackChampion& getStackChampion() const;
	void setStackChampion(const StackChampion& s);

private:
	MainJoueur mainJoueur;
	Pioche pioche;
	StackChampion stackChampion;
	Defausse defausse;
	int argent = 0;      
	int pointDeVie = 0;
};

#endif // JOUEUR_H