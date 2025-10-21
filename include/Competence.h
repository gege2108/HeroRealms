#ifndef COMPETENCE_H
#define COMPETENCE_H

#include <string>

class Competence {
public:
    Competence() = default;
    explicit Competence(int val) : valeur(val) {}
    virtual ~Competence() = default;

    int getValeur() const { return valeur; }
    void setValeur(int v) { valeur = v; }

    // Méthode virtuelle fournie par la classe de base : héritée par défaut
    virtual std::string toString() const {
        return std::to_string(valeur);
    }

private:
    int valeur = 0;
};

#endif // COMPETENCE_H