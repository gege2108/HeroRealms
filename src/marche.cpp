#include "Marche.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <chrono>

Marche::Marche() = default;
Marche::Marche(const std::vector<Action*>& actions, const std::vector<GemmeDeFeu*>& gemmes)
    : StackActionEtChampion(actions), gemmeDeFeu(gemmes) {}

const std::vector<Action*>& Marche::getStackActions() const { return StackActionEtChampion; }
void Marche::setStackActions(const std::vector<Action*>& a) { StackActionEtChampion = a; }

// Implémentations pour actionEtChampionVendable
const std::vector<Action*>& Marche::getActionsVendables() const { return actionEtChampionVendable; }
void Marche::setActionsVendables(const std::vector<Action*>& a) { actionEtChampionVendable = a; }

const std::vector<GemmeDeFeu*>& Marche::getGemmes() const { return gemmeDeFeu; }
void Marche::setGemmes(const std::vector<GemmeDeFeu*>& g) { gemmeDeFeu = g; }

void Marche::addStackAction(Action* a) { StackActionEtChampion.push_back(a); }
bool Marche::removeStackAction(Action* a) {
    for (int i = 0; i < (int)StackActionEtChampion.size(); ++i) {
        if (StackActionEtChampion[i] == a) {
            StackActionEtChampion.erase(StackActionEtChampion.begin() + i);
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

// Implémentations pour actionEtChampionVendable
void Marche::addActionVendable(Action* a) { actionEtChampionVendable.push_back(a); }
bool Marche::removeActionVendable(Action* a) {
    for (int i = 0; i < (int)actionEtChampionVendable.size(); ++i) {
        if (actionEtChampionVendable[i] == a) {
            actionEtChampionVendable.erase(actionEtChampionVendable.begin() + i);
            return true;
        }
    }
    return false;
}

GemmeDeFeu* Marche::acheterGemme() {
    if (gemmeDeFeu.empty()) return nullptr;

    GemmeDeFeu* gemme = gemmeDeFeu[0];
    removeGemme(gemme);
    return gemme;
}

void Marche::clear() {
    //Changer cette fonction et faire en sorte que les champions qui n'ont pas ete achete aillent dans StackActionEtChampion
    for (auto& action : actionEtChampionVendable) {
        StackActionEtChampion.push_back(action);
    }
    actionEtChampionVendable.clear();
}

void Marche::MiseAJourActionsVendables() {
    std::cout << "Ajout d'une nouvelle carte vendable." << std::endl;
    if (StackActionEtChampion.empty()) {
        std::cout << "Plus de nouvelle carte disponible." << std::endl;
        return;
    }
    std::cout << "Ajout de la carte : " << StackActionEtChampion[0]->getNom() << " qui coûte : " << StackActionEtChampion[0]->getPrix() << std::endl;
    actionEtChampionVendable.push_back(StackActionEtChampion[0]);
    StackActionEtChampion.erase(StackActionEtChampion.begin());
}

void Marche::InitialiserActionsVendables(int nombreActions) {
    // Vider les actions vendables actuelles
    actionEtChampionVendable.clear();
    
    // Prendre les premières actions de la stack pour les mettre en vente
    int actionsAPrendre = std::min(nombreActions, (int)StackActionEtChampion.size());
    
    for (int i = 0; i < actionsAPrendre; ++i) {
        if (!StackActionEtChampion.empty()) {
            Action* action = StackActionEtChampion.back();
            StackActionEtChampion.pop_back();
            actionEtChampionVendable.push_back(action);
        }
    }
}

void Marche::melangeStackActionEtChampion() {
    if (StackActionEtChampion.empty()) return;
    
    srand(time(nullptr));

    for (int i = StackActionEtChampion.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Action* temp = StackActionEtChampion[i];
        StackActionEtChampion[i] = StackActionEtChampion[j];
        StackActionEtChampion[j] = temp;
    }
}
