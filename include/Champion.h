#ifndef CHAMPION_H
#define CHAMPION_H

#include "Action.h"

class Champion : public Action {
private:
    int pointDeVie;
    int pointDeVieMax;  // NOUVEAU: PV maximum du champion
    bool isGarde;
    bool isDefense;

public:
    Champion(const Faction& faction, const std::string& nom, int prix,
             const std::vector<Effet>& effetsBasiqueChoix1,
             const std::vector<Effet>& effetsBasiqueChoix2,
             const std::vector<EffetTextuel>& effetsTextuelChoix1,
             const std::vector<EffetTextuel>& effetsTextuelChoix2,
             const std::vector<Effet>& effetsAllie,
             const std::vector<EffetTextuel>& effetsTextuelAllie,
             int pointDeVie, int pointDeVieMax, bool isGarde, bool isDefense);  // ✅ Ajout pvMax

    int getPointDeVie() const;
    void setPointDeVie(int pv);
    
    int getPointDeVieMax() const;
    void restaurerPointsDeVie();
    
    bool getIsGarde() const;
    void setIsGarde(bool garde);
    
    bool getIsDefense() const;
    void setIsDefense(bool defense);
};

#endif // CHAMPION_H