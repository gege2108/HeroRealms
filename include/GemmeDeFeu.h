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
    Effet& UtiliserAttaque();
    
    const std::vector<Effet>& getEffetsBasiqueChoix1() const override {
        return effetsBasiqueChoix1;
    }

private:
    static int prix;
    static Effet attaqueGemmeDeFeu;
    bool isJetable;
};

#endif // GEMMEDEFEU_H