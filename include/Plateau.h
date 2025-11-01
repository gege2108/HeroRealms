#ifndef PLATEAU_H
#define PLATEAU_H

#include "Joueur.h"
#include "Marche.h"
#include "ZoneDeSacrifice.h"
#include "CarteDeBase.h"

class Plateau {
public:
    Plateau();
    Plateau(const Joueur& j1, const Joueur& j2, const Marche& m, const ZoneDeSacrifice& z);

    const Joueur& getJoueur1() const;
    Joueur& getJoueur1();
    void setJoueur1(const Joueur& j);

    const Joueur& getJoueur2() const;
    Joueur& getJoueur2();
    void setJoueur2(const Joueur& j);

    const Marche& getMarche() const;
    Marche& getMarche();
    void setMarche(const Marche& m);

    const ZoneDeSacrifice& getZoneDeSacrifice() const;
    ZoneDeSacrifice& getZoneDeSacrifice();
    void setZoneDeSacrifice(const ZoneDeSacrifice& z);

    // méthode statique pour lancer une boucle de jeu simple
    static void run(Plateau& plateau);

    // utilise les effets des cartes de base du joueur 1
    void utiliserEffetBasiqueJoueur1(const std::vector<CarteDeBase*>& cartes);

    // utilise les effets des cartes de base du joueur 2
    void utiliserEffetBasiqueJoueur2(const std::vector<CarteDeBase*>& cartes);

    void afficherEtat() const;

    // Fonction pour choisir les effets du Joueur 1
    std::pair<std::vector<Effet>, std::vector<EffetTextuel>> choixUtilisationEffetJ1();


 

    //choix utilisation effet pour une seule carte
    std::pair<std::vector<Effet>, std::vector<EffetTextuel>> choixUtilisationEffetJ2();

    // Fonctions pour appliquer les effets choisis
    void appliquerEffetsJ1(const std::vector<Effet>& effetsBasique, const std::vector<EffetTextuel>& effetsTextuel);
    void appliquerEffetsJ2(const std::vector<Effet>& effetsBasique, const std::vector<EffetTextuel>& effetsTextuel);

    void achatActionChampion(Joueur& joueur); 

private:
    Joueur joueur1;
    Joueur joueur2;
    Marche marche;
    ZoneDeSacrifice zoneDeSacrifice;
};

#endif // PLATEAU_H