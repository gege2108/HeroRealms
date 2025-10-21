#ifndef CARTE_H
#define CARTE_H

#include <string>
#include <vector>
#include "Effet.h"

class Carte {
public:
    Carte() = default;
    Carte(const std::string& nom) : nom(nom) {}
    virtual ~Carte() = default;

    virtual Competence utiliserEffet() = 0;

    const std::string& getNom() const { return nom; }
    void setNom(const std::string& n) { nom = n; }

    std::vector<Effet>& getEffetsBasiqueChoix1() { return ListEffetBasiqueChoix1; }

    std::string toString() const {
        return "Carte: " + nom;
    }

protected:
    std::string nom;
    std::vector<Effet> ListEffetBasiqueChoix1;
};

#endif // CARTE_H