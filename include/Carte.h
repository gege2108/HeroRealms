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

    virtual std::string toString() const {
        std::string res = "Carte: " + nom;
        if (!ListEffetBasiqueChoix1.empty()) {
            res += " [";
            for (size_t i = 0; i < ListEffetBasiqueChoix1.size(); ++i) {
                if (i) res += ", ";
                res += ListEffetBasiqueChoix1[i].toString();
            }
            res += "]";
        }
        return res;
    }

protected:
    std::string nom;
    std::vector<Effet> ListEffetBasiqueChoix1;
};

#endif // CARTE_H