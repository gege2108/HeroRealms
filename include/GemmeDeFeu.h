#ifndef GEMMEDEFEU_H
#define GEMMEDEFEU_H

#include "Carte.h"

class GemmeDeFeu : public Carte {
public:
    GemmeDeFeu() = default;
    GemmeDeFeu(const std::string& nom) : Carte(nom), isJetable(false) {}

    int getPrix() const { return prix; }
    void setPrix(int p) { prix = p; }

    Effet& UtiliserAttaque();

    bool getIsJetable() const { return isJetable; }
    void setIsJetable(bool jetable) { isJetable = jetable; }

    // Implémentation de la méthode pure virtuelle de Carte
    virtual void utiliserEffet() override{
        //TODO enlever cette fonction pour toutes les cartes car mauvaise implementation
    }

    const std::vector<Effet>& getEffetsBasiqueChoix1() const override {
        return effetsBasiqueChoix1; // champ hérité de Carte (protected)
    }

private:
    static int prix;
    static Effet attaqueGemmeDeFeu;
    bool isJetable = false;
};

#endif // GEMMEDEFEU_H