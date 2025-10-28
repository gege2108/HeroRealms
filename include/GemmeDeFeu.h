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

    //void utiliserEffet() override;

private:
    static int prix;
    static Effet attaqueGemmeDeFeu;
    bool isJetable = false;
};

#endif // GEMMEDEFEU_H