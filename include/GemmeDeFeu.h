#ifndef GEMMEDEFEU_H
#define GEMMEDEFEU_H

#include "Carte.h"

class GemmeDeFeu : public Carte {
public:
    GemmeDeFeu();
    explicit GemmeDeFeu(const std::string& nom);

    const std::string& getNom() const override;  // Retourner const std::string& au lieu de std::string
    std::string toString() const override;
    Effet& UtiliserAttaque();

    bool getIsJetable() const { return isJetable; }
    void setIsJetable(bool jetable) { isJetable = jetable; }

    // Implémentation non-ambiguë : renvoie le vecteur membre hérité, pas une variable locale
    const std::vector<Effet>& getEffetsBasiqueChoix1() const override {
        return this->effetsBasiqueChoix1; // champ protected de Carte
    }

private:
    static int prix;
    static Effet attaqueGemmeDeFeu;
    bool isJetable = false;
};

#endif // GEMMEDEFEU_H