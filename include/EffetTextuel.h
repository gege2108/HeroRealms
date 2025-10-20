#ifndef EFFETTEXTUEL_H
#define EFFETTEXTUEL_H

class EffetTextuel {
public:
    EffetTextuel() : id(0) {}
    explicit EffetTextuel(int id) : id(id) {}
    int getId() const { return id; }
    void setId(int v) { id = v; }

    // placeholder : implémenter toutes les méthodes correspondant aux effets textuels
    void executer() const;

private:
    int id;
};

#endif // EFFETTEXTUEL_H