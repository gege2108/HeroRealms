#ifndef GAME_H
#define GAME_H

#include "Plateau.h"
#include <string>

class Joueur;  // Forward declaration pour éviter les inclusions circulaires

class Game {
public:
    explicit Game(Plateau& plateau);
    
    void run();
    
private:
    Plateau& plateau;
    int round;
    
    void afficherEntete();
    void afficherInfosJoueurs();
    void afficherMainJoueur(const std::string& nomJoueur, Joueur& joueur);
    void afficherSeparateur(char c = '-', int largeur = 60);
    
    void phaseCartesDeBase(const std::string& nomJoueur, Joueur& joueur, Joueur& adversaire);
    void phaseGemmesDeFeu(const std::string& nomJoueur, Joueur& joueur);
    void phaseAchatGemmes(const std::string& nomJoueur, Joueur& joueur);
    void phaseAchatActions(const std::string& nomJoueur, Joueur& joueur);
    void phaseUtilisationEffets(const std::string& nomJoueur, Joueur& joueur, Joueur& adversaire);
    void phaseUtilisationDegats(const std::string& nomJoueur, Joueur& joueur, Joueur& adversaire);
    void phaseFinTour(const std::string& nomJoueur, Joueur& joueur);
    
    void tourJoueur(const std::string& nomJoueur, Joueur& joueur, Joueur& adversaire);
    
    bool partieTerminee() const;
    void afficherGagnant() const;
};

#endif // GAME_H
