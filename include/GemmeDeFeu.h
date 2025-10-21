#ifndef GEMMEDEFEU_H
#define GEMMEDEFEU_H

#include "Carte.h"

class GemmeDeFeu : public Carte {
public:
    GemmeDeFeu() = default;
    GemmeDeFeu(const std::string& nom) : Carte(nom) {}

    static int getPrix() { return prix; }
    static void setPrix(int p) { prix = p; }

    void UtiliserAttaque(); // utilise l'attaque mais jette la Carte

    //void utiliserEffet() override;

private:
    static int prix;
    static Effet attaqueGemmeDeFeu;
};

#endif // GEMMEDEFEU_H