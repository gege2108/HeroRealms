#ifndef MARCHE_H
#define MARCHE_H

#include <vector>
#include "Action.h"
#include "GemmeDeFeu.h"

class Marche {
public:
    Marche();
    Marche(const std::vector<Action*>& actions, const std::vector<GemmeDeFeu*>& gemmes);

    const std::vector<Action*>& getActions() const;
    void setActions(const std::vector<Action*>& a);

    const std::vector<GemmeDeFeu*>& getGemmes() const;
    void setGemmes(const std::vector<GemmeDeFeu*>& g);

    void addAction(Action* a);
    bool removeAction(Action* a);

    void addGemme(GemmeDeFeu* g);
    bool removeGemme(GemmeDeFeu* g);

    GemmeDeFeu* acheterGemme();

    void clear();

private:
    std::vector<Action*> actionEtChampion;
    std::vector<GemmeDeFeu*> gemmeDeFeu;
};

#endif // MARCHE_H