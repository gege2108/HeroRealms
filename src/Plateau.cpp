#include "Plateau.h"
#include "Game.h"
#include <iostream>
#include <iomanip>

Plateau::Plateau() = default;

Plateau::Plateau(const Joueur& j1, const Joueur& j2, const Marche& m, const ZoneDeSacrifice& z)
    : joueur1(j1), joueur2(j2), marche(m), zoneDeSacrifice(z) {}

const Joueur& Plateau::getJoueur1() const { return joueur1; }
Joueur& Plateau::getJoueur1() { return joueur1; }
void Plateau::setJoueur1(const Joueur& j) { joueur1 = j; }

const Joueur& Plateau::getJoueur2() const { return joueur2; }
Joueur& Plateau::getJoueur2() { return joueur2; }
void Plateau::setJoueur2(const Joueur& j) { joueur2 = j; }

const Marche& Plateau::getMarche() const { return marche; }
Marche& Plateau::getMarche() { return marche; }
void Plateau::setMarche(const Marche& m) { marche = m; }

const ZoneDeSacrifice& Plateau::getZoneDeSacrifice() const { return zoneDeSacrifice; }
ZoneDeSacrifice& Plateau::getZoneDeSacrifice() { return zoneDeSacrifice; }
void Plateau::setZoneDeSacrifice(const ZoneDeSacrifice& z) { zoneDeSacrifice = z; }

void Plateau::run(Plateau& plateau) {
    // Utiliser un pointeur pour éviter les problèmes de copie
    Game* game = new Game(plateau);
    game->run();
    delete game;
}

void Plateau::utiliserEffetBasiqueJoueur1(const std::vector<CarteDeBase*>& cartes) {
    std::cout << "--- Résolution des effets (Joueur1) ---" << std::endl;
    for (auto* carte : cartes) {
        for (const auto& effet : carte->getEffetsBasiqueChoix1()) {
            switch (effet.getType()) {
                case DEGAT: {
                    int before = joueur1.getDegatsStockes();
                    joueur1.setDegatsStockes(before + effet.getValeur());
                    //joueur2.setPointDeVie(before - effet.getValeur());
                    std::cout << " - " << carte->toString() << " => -" << effet.getValeur()
                              << " degat stockés par le Joueur1 ( " << before << " -> " << joueur1.getDegatsStockes() << " )" << std::endl;
                    break;
                }
                case SOIN: {
                    int before = joueur1.getPointDeVie();
                    joueur1.setPointDeVie(before + effet.getValeur());
                    std::cout << " - " << carte->toString() << " => +" << effet.getValeur()
                              << " PV à Joueur1 ( " << before << " -> " << joueur1.getPointDeVie() << " )" << std::endl;
                    break;
                }
                case OR: {
                    int before = joueur1.getArgent();
                    joueur1.setArgent(before + effet.getValeur());
                    std::cout << " - " << carte->toString() << " => +" << effet.getValeur()
                        << " Or à Joueur1 ( " << before << " -> " << joueur1.getArgent() << " )" << std::endl;
                    break;
                }
                default:
                    std::cout << " - " << carte->toString() << " => effet non géré pour l'instant." << std::endl;
                    break;
            }
        }
    }
    std::cout << "--- Fin résolution (Joueur1) ---" << std::endl;
    std::cout << "Etat courant : Joueur1 PV=" << joueur1.getPointDeVie()
              << " | Joueur2 PV=" << joueur2.getPointDeVie() << std::endl;
}

void Plateau::utiliserEffetBasiqueJoueur2(const std::vector<CarteDeBase*>& cartes) {
    std::cout << "--- Résolution des effets (Joueur2) ---" << std::endl;
    for (auto* carte : cartes) {
        for (const auto& effet : carte->getEffetsBasiqueChoix1()) {
            switch (effet.getType()) {
                case DEGAT: {
                    int before = joueur2.getDegatsStockes();
                    joueur2.setDegatsStockes(before + effet.getValeur());
                    std::cout << " - " << carte->toString() << " => -" << effet.getValeur()
                              << " degat stockés par le Joueur2 ( " << before << " -> " << joueur2.getDegatsStockes() << " )" << std::endl;
                    break;
                }
                case SOIN: {
                    int before = joueur2.getPointDeVie();
                    joueur2.setPointDeVie(before + effet.getValeur());
                    std::cout << " - " << carte->toString() << " => +" << effet.getValeur()
                              << " PV à Joueur2 ( " << before << " -> " << joueur2.getPointDeVie() << " )" << std::endl;
                    break;
                }
                case OR: {
                    int before = joueur2.getArgent();
                    joueur2.setArgent(before + effet.getValeur());
                    std::cout << " - " << carte->toString() << " => +" << effet.getValeur()
                        << " Or à Joueur2 ( " << before << " -> " << joueur2.getArgent() << " )" << std::endl;
                    break;
                }
            }
        }
    }
    std::cout << "--- Fin résolution (Joueur2) ---" << std::endl;
    std::cout << "Etat courant : Joueur1 PV=" << joueur1.getPointDeVie()
              << " | Joueur2 PV=" << joueur2.getPointDeVie() << std::endl;
}

void Plateau::afficherEtat() const {
    std::cout << "=== État du Plateau ===" << std::endl;
    std::cout << "Joueur 1: " << joueur1.getPointDeVie() << " PV, " << joueur1.getArgent() << " Or" << std::endl;
    std::cout << "Joueur 2: " << joueur2.getPointDeVie() << " PV, " << joueur2.getArgent() << " Or" << std::endl;
    std::cout << "Marché: " << marche.getGemmes().size() << " gemmes disponibles" << std::endl;
    std::cout << "Zone de Sacrifice: " << zoneDeSacrifice.getCartes().size() << " cartes sacrifiées" << std::endl;
    std::cout << "======================" << std::endl;
}




std::pair<std::vector<Effet>, std::vector<EffetTextuel>> Plateau::choixUtilisationEffetJ1(){
    joueur1.peuxActiverCombo();

    std::vector<Effet> effetsBasiqueChoisis;
    std::vector<EffetTextuel> effetsTextuelsChoisis;

    const auto& cartes = joueur1.getMain().getCartes();

    std::cout << "\n=== Choix des effets pour le Joueur 1 ===" << std::endl;

    for (size_t carteIndex = 0; carteIndex < cartes.size(); ++carteIndex) {
        Carte* carte = cartes[carteIndex];
        Action* action = dynamic_cast<Action*>(carte);
        Champion* champion = dynamic_cast<Champion*>(carte);

        if (action != nullptr || champion != nullptr) {
            std::cout << "\nCarte " << (carteIndex + 1) << ": " << carte->getNom() << std::endl;
            
            // === ÉTAPE 1: Effets Choix 1 (obligatoires) ===
            std::cout << "\n--- Effets de base (Choix 1) ---" << std::endl;
            std::cout << "Effets basiques: ";
            for(const auto& effet : carte->getEffetsBasiqueChoix1()) {
                std::cout << effet.toString() << " ";
            }
            std::cout << std::endl;
            
            std::cout << "Effets textuels: ";
            if (action != nullptr) {
                for(const auto& effetTextuel : action->getListEffetTextuelChoix1()) {
                    std::cout << effetTextuel.toString() << " ";
                }
            } else if (champion != nullptr) {
                for(const auto& effetTextuel : champion->getListEffetTextuelChoix1()) {
                    std::cout << effetTextuel.toString() << " ";
                }
            }
            std::cout << std::endl;
            
            std::cout << "Voulez-vous utiliser ces effets de base ? (1=Oui, 0=Non): ";
            int choixBase;
            std::cin >> choixBase;
            
            if (choixBase == 1) {
                // Ajouter effets basiques choix 1
                for (const auto& effet : carte->getEffetsBasiqueChoix1()) {
                    effetsBasiqueChoisis.push_back(effet);
                }
                
                // Ajouter effets textuels choix 1
                if (action != nullptr) {
                    for (const auto& effet : action->getListEffetTextuelChoix1()) {
                        effetsTextuelsChoisis.push_back(effet);
                    }
                } else if (champion != nullptr) {
                    for (const auto& effet : champion->getListEffetTextuelChoix1()) {
                        effetsTextuelsChoisis.push_back(effet);
                    }
                }
                std::cout << "Effets de base ajoutés." << std::endl;
            }
            
            // === ÉTAPE 2: Effets Choix 2 (optionnels) ===
            bool hasChoix2 = false;
            if (action != nullptr) {
                hasChoix2 = !action->getListEffetBasiqueChoix2().empty() || !action->getListEffetTextuelChoix2().empty();
            } else if (champion != nullptr) {
                hasChoix2 = !champion->getListEffetBasiqueChoix2().empty() || !champion->getListEffetTextuelChoix2().empty();
            }
            
            if (hasChoix2) {
                std::cout << "\n--- Effets additionnels (Choix 2) ---" << std::endl;
                std::cout << "Effets basiques: ";
                if (action != nullptr) {
                    for(const auto& effet : action->getListEffetBasiqueChoix2()) {
                        std::cout << effet.toString() << " ";
                    }
                } else if (champion != nullptr) {
                    for(const auto& effet : champion->getListEffetBasiqueChoix2()) {
                        std::cout << effet.toString() << " ";
                    }
                }
                std::cout << std::endl;
                
                std::cout << "Effets textuels: ";
                if (action != nullptr) {
                    for(const auto& effetTextuel : action->getListEffetTextuelChoix2()) {
                        std::cout << effetTextuel.toString() << " ";
                    }
                } else if (champion != nullptr) {
                    for(const auto& effetTextuel : champion->getListEffetTextuelChoix2()) {
                        std::cout << effetTextuel.toString() << " ";
                    }
                }
                std::cout << std::endl;
                
                std::cout << "Voulez-vous utiliser ces effets additionnels ? (1=Oui, 0=Non): ";
                int choixAdditionnels;
                std::cin >> choixAdditionnels;
                
                if (choixAdditionnels == 1) {
                    // Ajouter effets basiques choix 2
                    if (action != nullptr) {
                        for (const auto& effet : action->getListEffetBasiqueChoix2()) {
                            effetsBasiqueChoisis.push_back(effet);
                        }
                        for (const auto& effet : action->getListEffetTextuelChoix2()) {
                            effetsTextuelsChoisis.push_back(effet);
                        }
                    } else if (champion != nullptr) {
                        for (const auto& effet : champion->getListEffetBasiqueChoix2()) {
                            effetsBasiqueChoisis.push_back(effet);
                        }
                        for (const auto& effet : champion->getListEffetTextuelChoix2()) {
                            effetsTextuelsChoisis.push_back(effet);
                        }
                    }
                    std::cout << "Effets additionnels ajoutés." << std::endl;
                }
            }
            
            // === ÉTAPE 3: Effets Combo (si disponible) ===
            bool peutCombo = false;
            if (action != nullptr) {
                peutCombo = action->getPeutFaireCombo();
            } else if (champion != nullptr) {
                peutCombo = champion->getPeutFaireCombo();
            }
            
            if (peutCombo) {
                std::cout << "\n--- Effets Combo (disponibles!) ---" << std::endl;
                std::cout << "Effets basiques combo: ";
                if (action != nullptr) {
                    for(const auto& effet : action->getListEffetBasiqueCombo()) {
                        std::cout << effet.toString() << " ";
                    }
                } else if (champion != nullptr) {
                    for(const auto& effet : champion->getListEffetBasiqueCombo()) {
                        std::cout << effet.toString() << " ";
                    }
                }
                std::cout << std::endl;
                
                std::cout << "Effets textuels combo: ";
                if (action != nullptr) {
                    for(const auto& effetTextuel : action->getListEffetTextuelCombo()) {
                        std::cout << effetTextuel.toString() << " ";
                    }
                } else if (champion != nullptr) {
                    for(const auto& effetTextuel : champion->getListEffetTextuelCombo()) {
                        std::cout << effetTextuel.toString() << " ";
                    }
                }
                std::cout << std::endl;
                
                std::cout << "Voulez-vous utiliser les effets combo ? (1=Oui, 0=Non): ";
                int choixCombo;
                std::cin >> choixCombo;
                
                if (choixCombo == 1) {
                    // Ajouter effets combo
                    if (action != nullptr) {
                        for (const auto& effet : action->getListEffetBasiqueCombo()) {
                            effetsBasiqueChoisis.push_back(effet);
                        }
                        for (const auto& effet : action->getListEffetTextuelCombo()) {
                            effetsTextuelsChoisis.push_back(effet);
                        }
                    } else if (champion != nullptr) {
                        for (const auto& effet : champion->getListEffetBasiqueCombo()) {
                            effetsBasiqueChoisis.push_back(effet);
                        }
                        for (const auto& effet : champion->getListEffetTextuelCombo()) {
                            effetsTextuelsChoisis.push_back(effet);
                        }
                    }
                    std::cout << "Effets combo ajoutés!" << std::endl;
                }
            }
        }
    }
    
    std::cout << "\n=== Fin du choix des effets ===" << std::endl;
    std::cout << "Total d'effets basiques choisis: " << effetsBasiqueChoisis.size() << std::endl;
    std::cout << "Total d'effets textuels choisis: " << effetsTextuelsChoisis.size() << std::endl;

    return {effetsBasiqueChoisis, effetsTextuelsChoisis};
}




std::pair<std::vector<Effet>, std::vector<EffetTextuel>> Plateau::choixUtilisationEffetJ2(){
    joueur2.peuxActiverCombo();

    std::vector<Effet> effetsBasiqueChoisis;
    std::vector<EffetTextuel> effetsTextuelsChoisis;

    const auto& cartes = joueur2.getMain().getCartes();

    std::cout << "\n=== Choix des effets pour le Joueur 2 ===" << std::endl;

    for (size_t carteIndex = 0; carteIndex < cartes.size(); ++carteIndex) {
        Carte* carte = cartes[carteIndex];
        Action* action = dynamic_cast<Action*>(carte);
        Champion* champion = dynamic_cast<Champion*>(carte);

        if (action != nullptr || champion != nullptr) {
            std::cout << "\nCarte " << (carteIndex + 1) << ": " << carte->getNom() << std::endl;
            
            // === ÉTAPE 1: Effets Choix 1 (obligatoires) ===
            std::cout << "\n--- Effets de base (Choix 1) ---" << std::endl;
            std::cout << "Effets basiques: ";
            for(const auto& effet : carte->getEffetsBasiqueChoix1()) {
                std::cout << effet.toString() << " ";
            }
            std::cout << std::endl;
            
            std::cout << "Effets textuels: ";
            if (action != nullptr) {
                for(const auto& effetTextuel : action->getListEffetTextuelChoix1()) {
                    std::cout << effetTextuel.toString() << " ";
                }
            } else if (champion != nullptr) {
                for(const auto& effetTextuel : champion->getListEffetTextuelChoix1()) {
                    std::cout << effetTextuel.toString() << " ";
                }
            }
            std::cout << std::endl;
            
            std::cout << "Voulez-vous utiliser ces effets de base ? (1=Oui, 0=Non): ";
            int choixBase;
            std::cin >> choixBase;
            
            if (choixBase == 1) {
                // Ajouter effets basiques choix 1
                for (const auto& effet : carte->getEffetsBasiqueChoix1()) {
                    effetsBasiqueChoisis.push_back(effet);
                }
                
                // Ajouter effets textuels choix 1
                if (action != nullptr) {
                    for (const auto& effet : action->getListEffetTextuelChoix1()) {
                        effetsTextuelsChoisis.push_back(effet);
                    }
                } else if (champion != nullptr) {
                    for (const auto& effet : champion->getListEffetTextuelChoix1()) {
                        effetsTextuelsChoisis.push_back(effet);
                    }
                }
                std::cout << "Effets de base ajoutés." << std::endl;
            }
            
            // === ÉTAPE 2: Effets Choix 2 (optionnels) ===
            bool hasChoix2 = false;
            if (action != nullptr) {
                hasChoix2 = !action->getListEffetBasiqueChoix2().empty() || !action->getListEffetTextuelChoix2().empty();
            } else if (champion != nullptr) {
                hasChoix2 = !champion->getListEffetBasiqueChoix2().empty() || !champion->getListEffetTextuelChoix2().empty();
            }
            
            if (hasChoix2) {
                std::cout << "\n--- Effets additionnels (Choix 2) ---" << std::endl;
                std::cout << "Effets basiques: ";
                if (action != nullptr) {
                    for(const auto& effet : action->getListEffetBasiqueChoix2()) {
                        std::cout << effet.toString() << " ";
                    }
                } else if (champion != nullptr) {
                    for(const auto& effet : champion->getListEffetBasiqueChoix2()) {
                        std::cout << effet.toString() << " ";
                    }
                }
                std::cout << std::endl;
                
                std::cout << "Effets textuels: ";
                if (action != nullptr) {
                    for(const auto& effetTextuel : action->getListEffetTextuelChoix2()) {
                        std::cout << effetTextuel.toString() << " ";
                    }
                } else if (champion != nullptr) {
                    for(const auto& effetTextuel : champion->getListEffetTextuelChoix2()) {
                        std::cout << effetTextuel.toString() << " ";
                    }
                }
                std::cout << std::endl;
                
                std::cout << "Voulez-vous utiliser ces effets additionnels ? (1=Oui, 0=Non): ";
                int choixAdditionnels;
                std::cin >> choixAdditionnels;
                
                if (choixAdditionnels == 1) {
                    // Ajouter effets basiques choix 2
                    if (action != nullptr) {
                        for (const auto& effet : action->getListEffetBasiqueChoix2()) {
                            effetsBasiqueChoisis.push_back(effet);
                        }
                        for (const auto& effet : action->getListEffetTextuelChoix2()) {
                            effetsTextuelsChoisis.push_back(effet);
                        }
                    } else if (champion != nullptr) {
                        for (const auto& effet : champion->getListEffetBasiqueChoix2()) {
                            effetsBasiqueChoisis.push_back(effet);
                        }
                        for (const auto& effet : champion->getListEffetTextuelChoix2()) {
                            effetsTextuelsChoisis.push_back(effet);
                        }
                    }
                    std::cout << "Effets additionnels ajoutés." << std::endl;
                }
            }
            
            // === ÉTAPE 3: Effets Combo (si disponible) ===
            bool peutCombo = false;
            if (action != nullptr) {
                peutCombo = action->getPeutFaireCombo();
            } else if (champion != nullptr) {
                peutCombo = champion->getPeutFaireCombo();
            }
            
            if (peutCombo) {
                std::cout << "\n--- Effets Combo (disponibles!) ---" << std::endl;
                std::cout << "Effets basiques combo: ";
                if (action != nullptr) {
                    for(const auto& effet : action->getListEffetBasiqueCombo()) {
                        std::cout << effet.toString() << " ";
                    }
                } else if (champion != nullptr) {
                    for(const auto& effet : champion->getListEffetBasiqueCombo()) {
                        std::cout << effet.toString() << " ";
                    }
                }
                std::cout << std::endl;
                
                std::cout << "Effets textuels combo: ";
                if (action != nullptr) {
                    for(const auto& effetTextuel : action->getListEffetTextuelCombo()) {
                        std::cout << effetTextuel.toString() << " ";
                    }
                } else if (champion != nullptr) {
                    for(const auto& effetTextuel : champion->getListEffetTextuelCombo()) {
                        std::cout << effetTextuel.toString() << " ";
                    }
                }
                std::cout << std::endl;
                
                std::cout << "Voulez-vous utiliser les effets combo ? (1=Oui, 0=Non): ";
                int choixCombo;
                std::cin >> choixCombo;
                
                if (choixCombo == 1) {
                    // Ajouter effets combo
                    if (action != nullptr) {
                        for (const auto& effet : action->getListEffetBasiqueCombo()) {
                            effetsBasiqueChoisis.push_back(effet);
                        }
                        for (const auto& effet : action->getListEffetTextuelCombo()) {
                            effetsTextuelsChoisis.push_back(effet);
                        }
                    } else if (champion != nullptr) {
                        for (const auto& effet : champion->getListEffetBasiqueCombo()) {
                            effetsBasiqueChoisis.push_back(effet);
                        }
                        for (const auto& effet : champion->getListEffetTextuelCombo()) {
                            effetsTextuelsChoisis.push_back(effet);
                        }
                    }
                    std::cout << "Effets combo ajoutés!" << std::endl;
                }
            }
        }
    }
    
    std::cout << "\n=== Fin du choix des effets ===" << std::endl;
    std::cout << "Total d'effets basiques choisis: " << effetsBasiqueChoisis.size() << std::endl;
    std::cout << "Total d'effets textuels choisis: " << effetsTextuelsChoisis.size() << std::endl;

    return {effetsBasiqueChoisis, effetsTextuelsChoisis};
}

void Plateau::appliquerEffetsJ1(const std::vector<Effet>& effetsBasique, const std::vector<EffetTextuel>& effetsTextuel){
    std::cout << "\n--- Application des effets basiques du Joueur 1 ---" << std::endl;
    for (const auto& effet : effetsBasique) {
        switch (effet.getType()) {
            case DEGAT: {
                int before = joueur1.getDegatsStockes();
                joueur1.addDegatsStockes(effet.getValeur());
                //joueur2.setPointDeVie(before - effet.getValeur());
                std::cout << " => +" << effet.getValeur()
                          << " Degats stockes à Joueur1 ( " << before << " -> " << joueur1.getDegatsStockes() << " )" << std::endl;
                break;
            }
            case SOIN: {
                int before = joueur1.getPointDeVie();
                joueur1.setPointDeVie(before + effet.getValeur());
                std::cout << " => +" << effet.getValeur()
                          << " PV à Joueur1 ( " << before << " -> " << joueur1.getPointDeVie() << " )" << std::endl;
                break;
            }
            case OR: {
                int before = joueur1.getArgent();
                joueur1.setArgent(before + effet.getValeur());
                std::cout << " => +" << effet.getValeur()
                    << " Or à Joueur1 ( " << before << " -> " << joueur1.getArgent() << " )" << std::endl;
                break;
            }
            default:
                std::cout << " => effet non géré pour l'instant." << std::endl;
                break;
        }
    }
    std::cout << "--- Fin application des effets basiques du Joueur 1 ---" << std::endl;

    std::cout << "\n--- Application des effets textuels du Joueur 1 ---" << std::endl;
    for (const auto& effetTextuel : effetsTextuel) {
        EffetTextuel::handleIdEffetTextuel(effetTextuel.getId(), joueur1,joueur2);
    }
    std::cout << "--- Fin application des effets textuels du Joueur 1 ---" << std::endl;
}

void Plateau::appliquerEffetsJ2(const std::vector<Effet>& effetsBasique, const std::vector<EffetTextuel>& effetsTextuel){
    std::cout << "\n--- Application des effets basiques du Joueur 2 ---" << std::endl;
    for (const auto& effet : effetsBasique) {
        switch (effet.getType()) {
            case DEGAT: {
                int before = joueur2.getDegatsStockes();
                joueur2.addDegatsStockes(effet.getValeur());
                //joueur1.setPointDeVie(before - effet.getValeur());
                std::cout << " => +" << effet.getValeur()
                          << " Degats stockes à Joueur1 ( " << before << " -> " << joueur1.getDegatsStockes() << " )" << std::endl;
                break;
            }
            case SOIN: {
                int before = joueur2.getPointDeVie();
                joueur2.setPointDeVie(before + effet.getValeur());
                std::cout << " => +" << effet.getValeur()
                          << " PV à Joueur2 ( " << before << " -> " << joueur2.getPointDeVie() << " )" << std::endl;
                break;
            }
            case OR: {
                int before = joueur2.getArgent();
                joueur2.setArgent(before + effet.getValeur());
                std::cout << " => +" << effet.getValeur()
                    << " Or à Joueur2 ( " << before << " -> " << joueur2.getArgent() << " )" << std::endl;
                break;
            }
            default:
                std::cout << " => effet non géré pour l'instant." << std::endl;
                break;
        }
    }
    std::cout << "--- Fin résolution (Joueur2) ---" << std::endl;

    std::cout << "\n--- Application des effets textuels du Joueur 2 ---" << std::endl;
    for (const auto& effetTextuel : effetsTextuel) {
        EffetTextuel::handleIdEffetTextuel(effetTextuel.getId(), joueur2, joueur1);
    }
    std::cout << "--- Fin application des effets textuels du Joueur 2 ---" << std::endl;
}



void Plateau::achatActionChampion(Joueur& joueur) {
        bool continuerAchat = true;
        
        while (continuerAchat && !marche.getActionsVendables().empty()) {
            bool aAcheteQuelqueChose = false;
            bool peutAcheter = false;
            
            // Créer une copie de la liste des actions vendables pour éviter les modifications pendant l'itération
            auto actionsVendablesCopie = marche.getActionsVendables();
            
            for (Action* action : actionsVendablesCopie) {
                if (action->getPrix() <= joueur.getArgent())
                {
                    peutAcheter = true;
                    std::cout << "Action disponible : " << action->getNom() << " pour " << action->getPrix() << " pieces d'or." << std::endl;
                    int choix;
                    std::cout << "appuyez sur 1 pour acheter cette action, appuyez sur 0 pour passer." << std::endl;
                    std::cin >> choix;
                    if (choix == 1)
                    {
                        joueur.setArgent(joueur.getArgent() - action->getPrix());
                        marche.removeActionVendable(action);
                        Defausse defausseJ = joueur.getDefausse();
                        defausseJ.addCarte(action);
                        joueur.setDefausse(defausseJ);
                        std::cout << "Vous avez acheté " << action->getNom() << " et dépensé " << action->getPrix() << " pièces d'or." << std::endl;
                        std::cout << "Il vous reste " << joueur.getArgent() << " pièces d'or." << std::endl;
                        
                        // ajout dès qu'un joueur vient d'acheter une carte
                        if (!marche.getStackActions().empty()) {
                            Action* nouvelleCarte = marche.getStackActions().front();
                            marche.addActionVendable(nouvelleCarte);
                            // Créer une copie de la stack sans le premier élément
                            auto stackCopie = marche.getStackActions();
                            stackCopie.erase(stackCopie.begin());
                            marche.setStackActions(stackCopie);
                            std::cout << "Ajout d'une nouvelle carte vendable." << std::endl;
                            std::cout << "Ajout de la carte : " << nouvelleCarte->getNom() << std::endl;
                        } else {
                            std::cout << "Plus de cartes disponibles dans la stack du marché." << std::endl;
                        }
                        
                        aAcheteQuelqueChose = true;
                        break; 
                    }
                }
                else{
                    std::cout << "Vous n'avez pas assez d'or pour l'action : " << action->getNom() << " qui coûte " << action->getPrix() << " pièces d'or." << std::endl;
                }
            }

            if (!peutAcheter)
            {
                std::cout << "Aucune action disponible à l'achat." << std::endl;
                continuerAchat = false;
            }
            
           
            // Si le joueur n'a rien acheté dans ce tour, proposer d'arrêter
            else if (!aAcheteQuelqueChose) {
                std::cout << "Voulez-vous continuer vos achats ? (1 = oui, 0 = non)" << std::endl;
                int choixContinuer;
                std::cin >> choixContinuer;
                continuerAchat = (choixContinuer == 1);
            }
            if (continuerAchat)
            {
                std::cout << std::endl;
                std::cout << std::string(60, '-') << std::endl;
                std::cout << std::endl;
                std::cout << "Cartes vendables dans le marche :" << std::endl;
                for (const auto& action : marche.getActionsVendables()) {
                    std::cout << " - " << action->getNom() << " (coût : " << action->getPrix() << " pièces d'or)" << std::endl;
                }
            }

        }
}

/*S
void Plateau::utiliserDegatsStockes(Joueur& joueur, Joueur& adversaire) {
    int degats = joueur.getDegatsStockes();

    if(adversaire.getStackChampion().getChampions().empty()){
        std::cout << "Le joueur n'a pas de champion en jeu, les dégâts stockés." << std::endl;
        std::cout << "Le joueur subit " << degats << " dégâts stockés directement." << std::endl;
        adversaire.setPointDeVie(adversaire.getPointDeVie() - degats);
        joueur.setDegatsStockes(0);
        }

    else if(adversaire.getStackChampion().getGardes().empty()){
        std::cout << "Il n'a pas de garde wallah." << std::endl;
        while(joueur.getDegatsStockes() > 0){
        std::cout << "Le joueur n'a pas de garde en jeu." << std::endl;
        std::cout << "Vous pouvez choisir un champion à attaquer parmi les suivants :" << std::endl;
        const auto& champions = adversaire.getStackChampion().getChampions();
        std::vector<Champion*> ciblesPossibles;
        for (size_t i = 0; i < champions.size(); ++i) {
            std::cout << i + 1 << ". " << champions[i]->getNom() << " (PV : " << champions[i]->getPointDeVie() << ")" << std::endl;
            if (champions[i]->getPointDeVie() <= joueur.getDegatsStockes())
            {
                ciblesPossibles.push_back(champions[i]);
            }
            else
            {
                std::cout << "   (Ne peut pas être ciblé, PV trop élevés)" << std::endl;
            }
        }
        if (ciblesPossibles.empty()) {
            std::cout << "Aucun champion ne peut être ciblé avec les dégâts stockés." << std::endl;
            std::cout << "Le joueur subit " << joueur.getDegatsStockes() << " dégâts stockés directement." << std::endl;
            adversaire.setPointDeVie(adversaire.getPointDeVie() - joueur.getDegatsStockes());
            joueur.setDegatsStockes(0);
        }
        else{
            
                std::cout << "Appuyez sur 0 si vous souhaitez infliger les dégâts directement au joueur adverse." << std::endl;
            int choix;
            std::cin >> choix;
            if (choix == 0) {
                std::cout << "Le joueur subit " << joueur.getDegatsStockes() << " dégâts stockés directement." << std::endl;
                joueur.setDegatsStockes(0);
            } 
            else{
                for (size_t i = 0; i < ciblesPossibles.size(); i++)
                {
                    std::cout << "Appuyez sur " << i + 1 << " pour cibler " << ciblesPossibles[i]->getNom() << " (PV : " << ciblesPossibles[i]->getPointDeVie() << ")" << std::endl;
                }
                std::cin >> choix;
                
                for(size_t i = 0; i < ciblesPossibles.size(); ++i){
                    if(choix == static_cast<int>(i) + 1){
                        Champion* cible = ciblesPossibles[i];
                        int before = cible->getPointDeVie();
                        cible->setPointDeVie(0);
                        std::cout << "Le champion " << cible->getNom() << " subit " << joueur.getDegatsStockes() - before << " dégâts stockés (PV : " << before << " -> " << cible->getPointDeVie() << ")" << std::endl;
                        joueur.setDegatsStockes(joueur.getDegatsStockes() - before);
                        break;
                        }
                    }
                }
            }
        }
    }
    else{
        std::cout << "Le joueur a " << adversaire.getStackChampion().getGardes().size() << " garde(s) en jeu." << std::endl;
        std::cout << "Les dégâts stockés vont être infligés aux gardes." << std::endl;
        std::vector<Champion*> ciblesPossibles;
        for (size_t i = 0; i < adversaire.getStackChampion().getGardes().size(); ++i) {
            Champion* garde = adversaire.getStackChampion().getGardes()[i];
            std::cout << i + 1 << ". " << garde->getNom() << " (PV : " << garde->getPointDeVie() << ")" << std::endl;
            if (garde->getPointDeVie() <= joueur.getDegatsStockes())
            {
                ciblesPossibles.push_back(garde);
            }
            else
            {
                std::cout << "   (Ne peut pas être ciblé, PV trop élevés)" << std::endl;
            }
        }

        if (ciblesPossibles.empty()) {
            std::cout << "Aucun garde ne peut être ciblé avec les dégâts stockés." << std::endl;
            return;
        }
        else{
            while (!ciblesPossibles.empty() && joueur.getDegatsStockes() > 0)
            {
                std::cout << "Choisissez un garde à attaquer parmi les suivants :" << std::endl;
                for (size_t i = 0; i < ciblesPossibles.size(); ++i) {
                    std::cout << i + 1 << ". " << ciblesPossibles[i]->getNom() << " (PV : " << ciblesPossibles[i]->getPointDeVie() << ")" << std::endl;
                }
                int choix;
                std::cin >> choix;
                
                for(size_t i = 0; i < ciblesPossibles.size(); ++i){
                    if(choix == static_cast<int>(i) + 1){
                        Champion* cible = ciblesPossibles[i];
                        int before = cible->getPointDeVie();
                        cible->setPointDeVie(0);
                        std::cout << "Le garde " << cible->getNom() << " subit " << joueur.getDegatsStockes() - before << " dégâts stockés (PV : " << before << " -> " << cible->getPointDeVie() << ")" << std::endl;
                        joueur.setDegatsStockes(joueur.getDegatsStockes() - before);
                        ciblesPossibles.erase(ciblesPossibles.begin() + i);
                        
                    }
                }
                if(ciblesPossibles.empty()){
                    std::cout << "Il reste " << joueur.getDegatsStockes() << " dégâts stockés à utiliser." << std::endl;
                    adversaire.setPointDeVie(adversaire.getPointDeVie() - joueur.getDegatsStockes());
                    std::cout << "Le joueur adverse subit " << joueur.getDegatsStockes() << " dégâts stockés directement." << std::endl;
                    joueur.setDegatsStockes(0);
                    return;
                }
                else{
                    std::vector<Champion*> ciblesNewPossibles;
                    bool found = false;
                    for (size_t i = 0; i < ciblesPossibles.size(); i++)
                        {
                            Champion* garde = ciblesPossibles[i];
                            if(garde->getPointDeVie() <= joueur.getDegatsStockes())
                            {
                                ciblesNewPossibles.push_back(garde);
                                found = true;
                            }
                        }
                    if (found)
                        {
                            ciblesPossibles = ciblesNewPossibles;
                        }
                }
                break;
                
                //prendre en compte le cas où il reste une cible mais que le joueur n'a plus assez de dégâts stockés, dans ce cas ne pas infliger les degats restants au joueur adverse
                else if(joueur.getDegatsStockes() > 0 )
                    {

                        std::cout << "Aucun autre garde ne peut être ciblé avec les dégâts stockés." << std::endl;
                        adversaire.setPointDeVie(adversaire.getPointDeVie() - joueur.getDegatsStockes());
                        std::cout << "Le joueur adverse subit " << joueur.getDegatsStockes() << " dégâts stockés directement." << std::endl;
                        joueur.setDegatsStockes(0);
                        return;
                
            
        }
    }
}

}
*/

void Plateau::utiliserDegatsStockes(Joueur& joueur, Joueur& adversaire) {
        int degats = joueur.getDegatsStockes();

        if(adversaire.getStackChampion().getChampions().empty()){
            std::cout << "Le joueur n'a pas de champion en jeu." << std::endl;
            std::cout << "Le joueur subit " << degats << " dégâts stockés directement." << std::endl;
            adversaire.setPointDeVie(adversaire.getPointDeVie() - degats);
            joueur.setDegatsStockes(0);
            return;
        }

        else if(adversaire.getStackChampion().getGardes().empty()){
            std::cout << "Le joueur n'a pas de garde en jeu." << std::endl;
            
            while(joueur.getDegatsStockes() > 0){
                std::cout << "\n=== Dégâts restants: " << joueur.getDegatsStockes() << " ===" << std::endl;
                
                // Vérifier s'il reste des champions non-gardes
                const auto& champions = adversaire.getStackChampion().getChampions();
                if(champions.empty()){
                    std::cout << "Tous les champions sont éliminés." << std::endl;
                    std::cout << "Le joueur adverse subit " << joueur.getDegatsStockes() << " dégâts stockés directement." << std::endl;
                    adversaire.setPointDeVie(adversaire.getPointDeVie() - joueur.getDegatsStockes());
                    joueur.setDegatsStockes(0);
                    break;
                }
                
                std::cout << "Choisissez votre action :" << std::endl;
                std::cout << "0. Infliger tous les dégâts restants (" << joueur.getDegatsStockes() << ") directement au joueur adverse" << std::endl;
                
                std::vector<Champion*> ciblesPossibles;
                for (size_t i = 0; i < champions.size(); ++i) {
                    std::cout << i + 1 << ". Attaquer " << champions[i]->getNom() << " (PV : " << champions[i]->getPointDeVie() << ")";
                    if (champions[i]->getPointDeVie() <= joueur.getDegatsStockes())
                    {
                        std::cout << " [Peut être éliminé]" << std::endl;
                        ciblesPossibles.push_back(champions[i]);
                    }
                    else
                    {
                        std::cout << " (Ne peut pas être éliminé, PV trop élevés)" << std::endl;
                    }
                }
                
                int choix;
                std::cout << "\nVotre choix: ";
                std::cin >> choix;
                
                if (choix == 0) {
                    std::cout << "Le joueur adverse subit " << joueur.getDegatsStockes() << " dégâts directement." << std::endl;
                    adversaire.setPointDeVie(adversaire.getPointDeVie() - joueur.getDegatsStockes());
                    joueur.setDegatsStockes(0);
                    break;
                } 
                else if(choix > 0 && choix <= static_cast<int>(champions.size())){
                    Champion* cible = champions[choix - 1];
                    
                    // Vérifier si le champion peut être éliminé
                    if(cible->getPointDeVie() <= joueur.getDegatsStockes()){
                        int before = cible->getPointDeVie();
                        cible->setPointDeVie(0);
                        std::cout << "Le champion " << cible->getNom() << " subit " << before << " dégâts (PV : " << before << " -> " << cible->getPointDeVie() << ")" << std::endl;
                        joueur.setDegatsStockes(joueur.getDegatsStockes() - before);
                        
                        // Retirer le champion éliminé du stackChampion
                        adversaire.getStackChampion().removeChampion(cible);
                        std::cout << "Le champion " << cible->getNom() << " est éliminé et retiré du jeu." << std::endl;
                    }
                    else{
                        std::cout << "Vous n'avez pas assez de dégâts pour éliminer ce champion. Veuillez choisir une autre cible." << std::endl;
                    }
                }
                else{
                    std::cout << "Choix invalide. Veuillez réessayer." << std::endl;
                }
            }
        }
        else{
            std::cout << "Le joueur a " << adversaire.getStackChampion().getGardes().size() << " garde(s) en jeu." << std::endl;
            std::cout << "Les dégâts stockés DOIVENT être infligés aux gardes en priorité." << std::endl;
            std::vector<Champion*> ciblesPossibles;
            for (size_t i = 0; i < adversaire.getStackChampion().getGardes().size(); ++i) {
                Champion* garde = adversaire.getStackChampion().getGardes()[i];
                std::cout << i + 1 << ". " << garde->getNom() << " (PV : " << garde->getPointDeVie() << ")";
                if (garde->getPointDeVie() <= joueur.getDegatsStockes())
                {
                    std::cout << " [Peut être éliminé]" << std::endl;
                    ciblesPossibles.push_back(garde);
                }
                else
                {
                    std::cout << " (PV trop élevés)" << std::endl;
                }
            }

            if (ciblesPossibles.empty()) {
                std::cout << "Aucun garde ne peut être éliminé avec les dégâts stockés." << std::endl;
                std::cout << "Les dégâts restants sont perdus." << std::endl;
                joueur.setDegatsStockes(0);
                return;
            }
            else{
                while (!ciblesPossibles.empty() && joueur.getDegatsStockes() > 0)
                {
                    std::cout << "\nDégâts restants: " << joueur.getDegatsStockes() << std::endl;
                    std::cout << "Choisissez un garde à attaquer parmi les suivants :" << std::endl;
                    for (size_t i = 0; i < ciblesPossibles.size(); ++i) {
                        std::cout << i + 1 << ". " << ciblesPossibles[i]->getNom() << " (PV : " << ciblesPossibles[i]->getPointDeVie() << ")" << std::endl;
                    }
                    int choix;
                    std::cin >> choix;
                    
                    if(choix > 0 && choix <= static_cast<int>(ciblesPossibles.size())){
                        Champion* cible = ciblesPossibles[choix - 1];
                        int before = cible->getPointDeVie();
                        cible->setPointDeVie(0);
                        std::cout << "Le garde " << cible->getNom() << " subit " << before << " dégâts (PV : " << before << " -> " << cible->getPointDeVie() << ")" << std::endl;
                        joueur.setDegatsStockes(joueur.getDegatsStockes() - before);
                        
                        // Retirer le garde éliminé du stackChampion (et du vecteur gardes automatiquement)
                        adversaire.getStackChampion().removeChampion(cible);
                        std::cout << "Le garde " << cible->getNom() << " est éliminé et retiré du jeu." << std::endl;
                        
                        ciblesPossibles.erase(ciblesPossibles.begin() + (choix - 1));
                    }
                    else{
                        std::cout << "Choix invalide. Veuillez réessayer." << std::endl;
                        continue;
                    }
                    
                    if(joueur.getDegatsStockes() > 0 && !ciblesPossibles.empty()){
                        // Mettre à jour les cibles possibles
                        std::vector<Champion*> ciblesNewPossibles;
                        for (size_t i = 0; i < ciblesPossibles.size(); i++)
                        {
                            Champion* garde = ciblesPossibles[i];
                            if(garde->getPointDeVie() <= joueur.getDegatsStockes())
                            {
                                ciblesNewPossibles.push_back(garde);
                            }
                        }
                        
                        if(ciblesNewPossibles.empty() && !ciblesPossibles.empty()){
                            std::cout << "Aucun autre garde ne peut être éliminé avec les dégâts restants (" << joueur.getDegatsStockes() << ")." << std::endl;
                            std::cout << "Les dégâts restants sont perdus." << std::endl;
                            joueur.setDegatsStockes(0);
                            break;
                        }
                        ciblesPossibles = ciblesNewPossibles;
                    }
                    else if(joueur.getDegatsStockes() > 0 && ciblesPossibles.empty()){
                        std::cout << "Tous les gardes sont éliminés. Il reste " << joueur.getDegatsStockes() << " dégâts stockés." << std::endl;
                        
                        // Maintenant on peut choisir entre champions et joueur
                        const auto& championsRestants = adversaire.getStackChampion().getChampions();
                        if(championsRestants.empty()){
                            std::cout << "Le joueur adverse subit " << joueur.getDegatsStockes() << " dégâts stockés directement." << std::endl;
                            adversaire.setPointDeVie(adversaire.getPointDeVie() - joueur.getDegatsStockes());
                            joueur.setDegatsStockes(0);
                            break;
                        }
                        
                        // Retour au cas "pas de gardes" pour gérer les champions restants
                        std::cout << "Plus de gardes ! Vous pouvez maintenant cibler les autres champions ou le joueur." << std::endl;
                        while(joueur.getDegatsStockes() > 0 && !adversaire.getStackChampion().getChampions().empty()){
                            std::cout << "\n=== Dégâts restants: " << joueur.getDegatsStockes() << " ===" << std::endl;
                            std::cout << "Choisissez votre action :" << std::endl;
                            std::cout << "0. Infliger tous les dégâts restants au joueur adverse" << std::endl;
                            
                            const auto& champs = adversaire.getStackChampion().getChampions();
                            for (size_t i = 0; i < champs.size(); ++i) {
                                std::cout << i + 1 << ". Attaquer " << champs[i]->getNom() << " (PV : " << champs[i]->getPointDeVie() << ")";
                                if (champs[i]->getPointDeVie() <= joueur.getDegatsStockes()) {
                                    std::cout << " [Peut être éliminé]" << std::endl;
                                } else {
                                    std::cout << " (PV trop élevés)" << std::endl;
                                }
                            }
                            
                            int choixFinal;
                            std::cout << "\nVotre choix: ";
                            std::cin >> choixFinal;
                            
                            if (choixFinal == 0) {
                                adversaire.setPointDeVie(adversaire.getPointDeVie() - joueur.getDegatsStockes());
                                std::cout << "Le joueur adverse subit " << joueur.getDegatsStockes() << " dégâts directement." << std::endl;
                                joueur.setDegatsStockes(0);
                                break;
                            }
                            else if(choixFinal > 0 && choixFinal <= static_cast<int>(champs.size())){
                                Champion* cibleChamp = champs[choixFinal - 1];
                                if(cibleChamp->getPointDeVie() <= joueur.getDegatsStockes()){
                                    int pvBefore = cibleChamp->getPointDeVie();
                                    cibleChamp->setPointDeVie(0);
                                    joueur.setDegatsStockes(joueur.getDegatsStockes() - pvBefore);
                                    adversaire.getStackChampion().removeChampion(cibleChamp);
                                    std::cout << "Le champion " << cibleChamp->getNom() << " est éliminé (" << pvBefore << " dégâts)." << std::endl;
                                }
                                else{
                                    std::cout << "Pas assez de dégâts pour éliminer ce champion." << std::endl;
                                }
                            }
                        }
                        
                        if(joueur.getDegatsStockes() > 0 && adversaire.getStackChampion().getChampions().empty()){
                            adversaire.setPointDeVie(adversaire.getPointDeVie() - joueur.getDegatsStockes());
                            std::cout << "Tous les champions éliminés. Le joueur adverse subit " << joueur.getDegatsStockes() << " dégâts." << std::endl;
                            joueur.setDegatsStockes(0);
                        }
                        break;
                    }
                    else{
                        break;
                    }
                }
            }
        }
    }