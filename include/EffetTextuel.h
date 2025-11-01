#ifndef EFFETTEXTUEL_H
#define EFFETTEXTUEL_H

#include <string>

// Forward declaration pour éviter l'inclusion circulaire
class Joueur;

class EffetTextuel {
public:
    EffetTextuel() : id(0), description("") {}
    explicit EffetTextuel(int id, const std::string& desc) : id(id), description(desc) {}
    int getId() const { return id; }
    void setId(int v) { id = v; }
    std::string getDescription() const { return description; }
    void setDescription(const std::string& desc) { description = desc; }

    
    std::string toString() const {
        return description;
    }

    // Méthodes utilisant Joueur
    //TODO: fix cette methode car elle provoque une erreur à la compilation (invalid pointer)
    void drawACard(Joueur& joueur); // id : 1
    void discardOpponentCard(Joueur& opponent);  // id : 2
    void stunChampion(Joueur& opponent) const;  // id : 3
    void drawAndDiscard(Joueur& joueur); // id : 4
    static void handleIdEffetTextuel(int id, Joueur& joueurJouantLeTour, Joueur& adversaire);

private:
    int id;
    std::string description;
};

#endif // EFFETTEXTUEL_H