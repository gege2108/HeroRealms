#ifndef COMPETENCE_H
#define COMPETENCE_H

class Competence {
public:
    Competence() = default;
    explicit Competence(int val) : valeur(val) {}
    virtual ~Competence() = default;

    int getValeur() const { return valeur; }
    void setValeur(int v) { valeur = v; }

private:
    int valeur = 0;
};

#endif // COMPETENCE_H