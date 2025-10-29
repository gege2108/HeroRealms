#ifndef MARCHE_H
#define MARCHE_H

#include <vector>
#include "Action.h"
#include "GemmeDeFeu.h"

class Marche {
public:
    Marche();
    Marche(const std::vector<Action*>& actions, const std::vector<GemmeDeFeu*>& gemmes);

    const std::vector<Action*>& getStackActions() const;
    void setStackActions(const std::vector<Action*>& a);

    // Méthodes pour actionEtChampionVendable
    const std::vector<Action*>& getActionsVendables() const;
    void setActionsVendables(const std::vector<Action*>& a);

    const std::vector<GemmeDeFeu*>& getGemmes() const;
    void setGemmes(const std::vector<GemmeDeFeu*>& g);

    void addStackAction(Action* a);
    bool removeStackAction(Action* a);

    // Méthodes pour actionEtChampionVendable
    void addActionVendable(Action* a);
    bool removeActionVendable(Action* a);

    void addGemme(GemmeDeFeu* g);
    bool removeGemme(GemmeDeFeu* g);

    GemmeDeFeu* acheterGemme();

    void clear();

private:
    std::vector<Action*> StackActionEtChampion;
    std::vector<GemmeDeFeu*> gemmeDeFeu;
    std::vector<Action*> actionEtChampionVendable;
};

#endif // MARCHE_H