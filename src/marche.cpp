#include "Marche.h"
#include <algorithm>

Marche::Marche() = default;
Marche::Marche(const std::vector<Action*>& actions, const std::vector<GemmeDeFeu*>& gemmes)
    : actionEtChampion(actions), gemmeDeFeu(gemmes) {}

const std::vector<Action*>& Marche::getActions() const { return actionEtChampion; }
void Marche::setActions(const std::vector<Action*>& a) { actionEtChampion = a; }

const std::vector<GemmeDeFeu*>& Marche::getGemmes() const { return gemmeDeFeu; }
void Marche::setGemmes(const std::vector<GemmeDeFeu*>& g) { gemmeDeFeu = g; }

void Marche::addAction(Action* a) { actionEtChampion.push_back(a); }
bool Marche::removeAction(Action* a) {
    for (int i = 0; i < (int)actionEtChampion.size(); ++i) {
        if (actionEtChampion[i] == a) {
            actionEtChampion.erase(actionEtChampion.begin() + i);
            return true;
        }
    }
    return false;
}

void Marche::addGemme(GemmeDeFeu* g) { gemmeDeFeu.push_back(g); }
bool Marche::removeGemme(GemmeDeFeu* g) {
    for (int i = 0; i < (int)gemmeDeFeu.size(); ++i) {
        if (gemmeDeFeu[i] == g) {
            gemmeDeFeu.erase(gemmeDeFeu.begin() + i);
            return true;
        }
    }
    return false;
}

void Marche::clear() {
    actionEtChampion.clear();
    gemmeDeFeu.clear();
}
