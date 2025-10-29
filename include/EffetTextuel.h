#ifndef EFFETTEXTUEL_H
#define EFFETTEXTUEL_H

#include <string>

class EffetTextuel {
public:
    EffetTextuel() : id(0), description("") {}
    explicit EffetTextuel(int id, const std::string& desc) : id(id), description(desc) {}
    int getId() const { return id; }
    void setId(int v) { id = v; }
    std::string getDescription() const { return description; }
    void setDescription(const std::string& desc) { description = desc; }

    // Méthode toString pour afficher la description
    std::string toString() const {
        return description;
    }

    // placeholder : implémenter toutes les méthodes correspondant aux effets textuels
    void executer() const;

private:
    int id;
    std::string description;
};

#endif // EFFETTEXTUEL_H