#include "StackChampion.h"
#include <algorithm>
#include <iostream>

StackChampion::StackChampion() = default;
StackChampion::StackChampion(const std::vector<Carte*>& cartes) : cartes(cartes) {}

const std::vector<Carte*>& StackChampion::getCartes() const { return cartes; }
void StackChampion::setCartes(const std::vector<Carte*>& c) {
    std::cout << "DEBUG setCartes(): Filtrage de " << c.size() << " cartes" << std::endl;
    
    cartes.clear();
    gardes.clear();
    
    // Filtrer UNIQUEMENT les Champions
    for (auto* carte : c) {
        Champion* champion = dynamic_cast<Champion*>(carte);
        if (champion != nullptr) {
            cartes.push_back(champion);
            if (champion->getIsGarde()) {
                gardes.push_back(champion);
            }
        } else if (carte != nullptr) {
            std::cout << "  ⚠️  Carte non-champion ignorée: " << carte->getNom() << std::endl;
        }
    }
    
    std::cout << "  ✓ Résultat: " << cartes.size() << " champions, " 
              << gardes.size() << " gardes" << std::endl;
}

void StackChampion::push(Carte* c) {
    if (c == nullptr) {
        std::cout << "⚠️  push(): Carte NULL rejetée" << std::endl;
        return;
    }
    
    // VÉRIFICATION CRITIQUE: C'est bien un Champion ?
    Champion* champion = dynamic_cast<Champion*>(c);
    
    if (champion == nullptr) {
        std::cout << "❌ push(): REJET de '" << c->getNom() 
                  << "' - CE N'EST PAS UN CHAMPION!" << std::endl;
        return;  // NE PAS AJOUTER
    }
    
    // OK, c'est un vrai Champion, on peut l'ajouter
    cartes.push_back(champion);
    std::cout << "✅ push(): Champion ajouté: " << champion->getNom();
    
    // Si c'est un garde, l'ajouter au vecteur gardes
    if (champion->getIsGarde()) {
        gardes.push_back(champion);
        std::cout << " [GARDE]";
    }
    std::cout << std::endl;
}

bool StackChampion::pop(Carte* c) {
    for (int i = 0; i < (int)cartes.size(); ++i) {
        if (cartes[i] == c) {
            cartes.erase(cartes.begin() + i);
            return true;
        }
    }
    return false;
}

void StackChampion::clear() { cartes.clear(); }

std::vector<Champion*> StackChampion::getChampions() const {
    std::vector<Champion*> champions;
    for (Carte* carte : cartes) {
        Champion* champion = dynamic_cast<Champion*>(carte);
        if (champion != nullptr) {
            champions.push_back(champion);
        }
    }
    return champions;
}

std::vector<Champion*> StackChampion::getChampions() {
    std::vector<Champion*> champions;
    for (Carte* carte : cartes) {
        Champion* champion = dynamic_cast<Champion*>(carte);
        if (champion != nullptr) {
            champions.push_back(champion);
        }
    }
    return champions;
}

bool StackChampion::removeChampion(Champion* champion) {
    if (champion == nullptr) return false;
    
    std::cout << "DEBUG removeChampion(): Retrait de " << champion->getNom() << std::endl;
    
    // Retirer de la liste des cartes
    for (auto it = cartes.begin(); it != cartes.end(); ++it) {
        if (*it == champion) {
            cartes.erase(it);
            std::cout << "✓ Champion retiré de cartes" << std::endl;
            
            // Si c'est un garde, le retirer aussi du vecteur gardes
            if (champion->getIsGarde()) {
                for (auto gardeIt = gardes.begin(); gardeIt != gardes.end(); ++gardeIt) {
                    if (*gardeIt == champion) {
                        gardes.erase(gardeIt);
                        std::cout << "🛡️  Garde retiré (restants: " << gardes.size() << ")" << std::endl;
                        break;
                    }
                }
            }
            
            return true;
        }
    }
    return false;
}

std::vector<Champion*>& StackChampion::getGardes() {
    return gardes;
}

void StackChampion::setGardes(const std::vector<Champion*>& g) {
    gardes = g;
}

void StackChampion::addGarde(Champion* c) {
    if (c != nullptr && c->getIsGarde()) {
        gardes.push_back(c);
    }
}
