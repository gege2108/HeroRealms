#ifndef GEMMEDEFEU_H
#define GEMMEDEFEU_H

#include "Carte.h"

class GemmeDeFeu : public Carte {
public:
    GemmeDeFeu();
    explicit GemmeDeFeu(const std::string& nom);

    int getPrix() const { return prix; }
    void setPrix(int p) { prix = p; }

    const std::string& getNom() const override;
    std::string toString() const override;
    
    // Méthodes pour utiliser les effets séparément
    Effet& UtiliserEffetOr();      // Utilise l'effet +2 or
    Effet& UtiliserAttaque();      // Utilise l'effet +3 dégâts et sacrifie la gemme
    
    bool estSacrifiable() const { return !isJetable; }  // Vérifie si la gemme peut être sacrifiée
    bool estSacrifiee() const { return isJetable; }     // Vérifie si la gemme a été sacrifiée
    
    const std::vector<Effet>& getEffetsBasiqueChoix1() const override {
        return effetsBasiqueChoix1;
    }

private:
    static int prix;
    static Effet effetOr;          // Effet +2 or
    static Effet attaqueGemmeDeFeu; // Effet +3 dégâts
    bool isJetable;
};

#endif // GEMMEDEFEU_H