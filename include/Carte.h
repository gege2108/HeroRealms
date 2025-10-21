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

    virtual void utiliserEffet() = 0;

    // rendre virtual pour permettre l'override dans les classes dérivées
    virtual const std::string& getNom() const { return nom; }
    virtual void setNom(const std::string& n) { nom = n; }

    // versions non-const et const pour autoriser l'override selon le besoin
    virtual std::vector<Effet>& getEffetsBasiqueChoix1() { return effetsBasiqueChoix1; }
    virtual const std::vector<Effet>& getEffetsBasiqueChoix1() const { return effetsBasiqueChoix1; }

    virtual std::string toString() const {
        std::string res = "Carte: " + nom;
        if (!effetsBasiqueChoix1.empty()) {
            res += " [";
            for (size_t i = 0; i < effetsBasiqueChoix1.size(); ++i) {
                if (i) res += ", ";
                res += effetsBasiqueChoix1[i].toString();
            }
            res += "]";
        }
        return res;
    }

protected:
    std::string nom;
    // renommé pour correspondre aux usages dans d'autres fichiers
    std::vector<Effet> effetsBasiqueChoix1;
};

#endif // CARTE_H