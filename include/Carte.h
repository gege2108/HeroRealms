#ifndef CARTE_H
#define CARTE_H

#include <string>
#include <vector>
#include "Effet.h"

class Carte {
public:
    Carte() = default;
    Carte(const std::string& nom) : nom(nom) {}
    Carte(const std::string& nom, const std::vector<Effet>& effets)
        : nom(nom), listEffetsBasiqueChoix1(effets) {}
    virtual ~Carte() = default;

    virtual void utiliserEffet() = 0;

    // rendre virtual pour permettre l'override dans les classes dérivées
    virtual const std::string& getNom() const { return nom; }
    virtual void setNom(const std::string& n) { nom = n; }

    // versions non-const et const pour autoriser l'override selon le besoin
    virtual std::vector<Effet>& getEffetsBasiqueChoix1() { return listEffetsBasiqueChoix1; }
    virtual const std::vector<Effet>& getEffetsBasiqueChoix1() const { return listEffetsBasiqueChoix1; }

    virtual std::string toString() const {
        std::string res = "Carte: " + nom;
        if (!listEffetsBasiqueChoix1.empty()) {
            res += " [";
            for (size_t i = 0; i < listEffetsBasiqueChoix1.size(); ++i) {
                if (i) res += ", ";
                res += listEffetsBasiqueChoix1[i].toString();
            }
            res += "]";
        }
        return res;
    }

protected:
    std::string nom;
    // renommé pour correspondre aux usages dans d'autres fichiers
    std::vector<Effet> listEffetsBasiqueChoix1;
};

#endif // CARTE_H