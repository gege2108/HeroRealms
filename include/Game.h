#ifndef GAME_H
#define GAME_H

#include "Plateau.h"
#include <string>

class Joueur;  // Forward declaration pour éviter les inclusions circulaires

class Game {
private:
    Plateau& plateau;
    int round;
    
    // Méthodes d'affichage
    void afficherEntete();
    void afficherInfosJoueurs();
    void afficherMainJoueur(const std::string& nomJoueur, Joueur& joueur);
    void afficherSeparateur(char c = '-', int largeur = 60);
    
    // Phases de jeu
    void gererChampionsEnMain(Joueur& joueur, Joueur& adversaire);
    void phaseCartesDeBase(const std::string& nomJoueur, Joueur& joueur, Joueur& adversaire);
    void phaseGemmesDeFeu(const std::string& nomJoueur, Joueur& joueur);
    void phaseAchatGemmes(const std::string& nomJoueur, Joueur& joueur);
    void phaseAchatActions(const std::string& nomJoueur, Joueur& joueur);
    void phaseUtilisationEffets(const std::string& nomJoueur, Joueur& joueur, Joueur& adversaire);
    void phaseUtilisationDegats(const std::string& nomJoueur, Joueur& joueur, Joueur& adversaire);
    void phaseFinTour(const std::string& nomJoueur, Joueur& joueur);
    
    // Gestion du tour
    void tourJoueur(const std::string& nomJoueur, Joueur& joueur, Joueur& adversaire);
    
    // Conditions de fin
    bool partieTerminee() const;
    void afficherGagnant() const;
    
public:
    Game(Plateau& p);
    void run();
};

#endif // GAME_H
