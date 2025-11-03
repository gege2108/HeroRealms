#include "Champion.h"
#include "Effet.h"
#include "EffetTextuel.h"
#include <iostream>

Champion::Champion(const Faction& faction, const std::string& nom, int prix,
                   const std::vector<Effet>& effetsBasiqueChoix1,
                   const std::vector<Effet>& effetsBasiqueChoix2,
                   const std::vector<EffetTextuel>& effetsTextuelChoix1,
                   const std::vector<EffetTextuel>& effetsTextuelChoix2,
                   const std::vector<Effet>& effetsAllie,
                   const std::vector<EffetTextuel>& effetsTextuelAllie,
                   int pointDeVie, int pointDeVieMax, bool isGarde, bool isDefense)
    : Action(faction, nom, prix, effetsBasiqueChoix1, effetsBasiqueChoix2,
             effetsTextuelChoix1, effetsTextuelChoix2, effetsAllie, effetsTextuelAllie),
      pointDeVie(pointDeVie), 
      pointDeVieMax(pointDeVieMax),
      isGarde(isGarde), 
      isDefense(isDefense),
      effetsUtilisesCeTour(false) {
          peutRejouer = false;
      }  // ✅ Initialiser à false

int Champion::getPointDeVie() const { return pointDeVie; }
void Champion::setPointDeVie(int pv) { 
    if (pv > pointDeVieMax && pointDeVieMax > 0) {
        std::cout << "⚠️  ALERTE: Tentative de définir " << pv << " PV pour " << getNom() 
                  << " (max: " << pointDeVieMax << "). Limitation à " << pointDeVieMax << std::endl;
        pointDeVie = pointDeVieMax;
    } else {
        pointDeVie = pv;
    }
}

int Champion::getPointDeVieMax() const { return pointDeVieMax; }

void Champion::restaurerPointsDeVie() {
    pointDeVie = pointDeVieMax;
}

bool Champion::getIsGarde() const { return isGarde; }
void Champion::setIsGarde(bool garde) { isGarde = garde; }

bool Champion::getIsDefense() const { return isDefense; }
void Champion::setIsDefense(bool defense) { isDefense = defense; }

bool Champion::getEffetsUtilisesCeTour() const { return effetsUtilisesCeTour; }
void Champion::setEffetsUtilisesCeTour(bool utilises) { effetsUtilisesCeTour = utilises; }
void Champion::resetEffetsTour() { effetsUtilisesCeTour = false; }