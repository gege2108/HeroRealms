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

void Joueur::peuxActiverCombo() {
    // Compteur des factions présentes dans la main
    std::map<Faction, int> factionCount;
    
    // Parcourir toutes les cartes en main
    const auto& cartes = mainJoueur.getCartes();
    
    // Compter les factions des Actions et Champions
    for (Carte* carte : cartes) {
        Action* action = dynamic_cast<Action*>(carte);
        Champion* champion = dynamic_cast<Champion*>(carte);
        
        if (action != nullptr) {
            factionCount[action->getFaction()]++;
        } else if (champion != nullptr) {
            factionCount[champion->getFaction()]++;
        }
    }
    
    // Activer peutFaireCombo pour les cartes ayant au moins une autre carte de même faction
    for (Carte* carte : cartes) {
        Action* action = dynamic_cast<Action*>(carte);
        Champion* champion = dynamic_cast<Champion*>(carte);
        
        if (action != nullptr) {
            // Si il y a au moins 2 cartes de cette faction (incluant cette carte)
            action->setPeutFaireCombo(factionCount[action->getFaction()] >= 2);
        } else if (champion != nullptr) {
            // Si il y a au moins 2 cartes de cette faction (incluant cette carte)
            champion->setPeutFaireCombo(factionCount[champion->getFaction()] >= 2);
        }
    }
    
    std::cout << "Activation des combos basée sur les factions présentes :" << std::endl;
    for (const auto& pair : factionCount) {
        if (pair.second >= 2) {
            std::string factionName;
            switch(pair.first) {
                case Faction::FactionJaune: factionName = "Impériale"; break;
                case Faction::FactionBleu: factionName = "Guilde"; break;
                case Faction::FactionRouge: factionName = "Nécros"; break;
                case Faction::FactionVert: factionName = "Sauvage"; break;
            }
            std::cout << "  - Faction " << factionName << ": " << pair.second << " cartes (combo activé)" << std::endl;
        }
    }
}

