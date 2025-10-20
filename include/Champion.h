#ifndef CHAMPION_H
#define CHAMPION_H

#include "Action.h"

class Champion : public Action {
public:
    Champion() = default;
    Champion(const std::string& nom) : Action(nom) {}

    int getPointDeVie() const { return pointDeVie; }
    void setPointDeVie(int v) { pointDeVie = v; }

    bool getIsGarde() const { return isGarde; }
    void setIsGarde(bool b) { isGarde = b; }

    bool getIsDefense() const { return isDefense; }
    void setIsDefense(bool b) { isDefense = b; }

private:
    int pointDeVie = 0;
    bool isGarde = false;
    bool isDefense = false;
};

#endif // CHAMPION_H