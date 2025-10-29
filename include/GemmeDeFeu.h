#ifndef GEMMEDEFEU_H
#define GEMMEDEFEU_H

#include "Carte.h"

class GemmeDeFeu : public Carte {
public:
    // Constructeur par défaut : impose l'effet basique { Effet(2, OR) }
    GemmeDeFeu()
        : isJetable(false)
    {
        this->effetsBasiqueChoix1 = { Effet(2, OR) };
    }

    // Nouveau constructeur : initialise le nom et impose l'effet basique { Effet(2, OR) }
    GemmeDeFeu(const std::string& nom)
        : Carte(nom), isJetable(false)
    {
        this->effetsBasiqueChoix1 = { Effet(2, OR) };
    }

    int getPrix() const { return prix; }
    void setPrix(int p) { prix = p; }

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