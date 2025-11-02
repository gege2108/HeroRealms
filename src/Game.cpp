#include "Game.h"
#include <iostream>
#include <iomanip>

Game::Game(Plateau& p) : plateau(p), round(0) {}

void Game::run() {
    std::cout << "╔═══════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║           BIENVENUE DANS HERO REALMS                      ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════════════════╝" << std::endl;
    
    std::cout << "DEBUG: Début de la boucle de jeu" << std::endl;
    
    while (round < 10 && !partieTerminee()) {
        ++round;
        
        afficherEntete();
        afficherInfosJoueurs();
        
        // ==================== TOUR JOUEUR 1 ====================
        std::cout << "\n╔═══════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║         🎮 TOUR DE " << std::left << std::setw(30) << "Joueur 1" << "             ║" << std::endl;
        std::cout << "╚═══════════════════════════════════════════════════════════╝" << std::endl;
        
        afficherMainJoueur("Joueur 1", plateau.getJoueur1());
        
        // NOUVEL AFFICHAGE: Champions en jeu
        afficherChampionsEnJeu("Joueur 1", plateau.getJoueur1());
        
        // ===== PHASE SPÉCIALE: Gestion des Champions =====
        std::cout << "\n┌─ PHASE SPÉCIALE: Champions ────────────────────────────┐" << std::endl;
        std::cout << "│ Gérer vos champions                                     │" << std::endl;
        std::cout << "└─────────────────────────────────────────────────────────┘" << std::endl;
        
        gererChampionsEnMain(plateau.getJoueur1(), plateau.getJoueur2());
        
        phaseCartesDeBase("Joueur 1", plateau.getJoueur1(), plateau.getJoueur2());
        phaseGemmesDeFeu("Joueur 1", plateau.getJoueur1());
        phaseAchatGemmes("Joueur 1", plateau.getJoueur1());
        phaseAchatActions("Joueur 1", plateau.getJoueur1());
        phaseUtilisationEffets("Joueur 1", plateau.getJoueur1(), plateau.getJoueur2());
        phaseUtilisationDegats("Joueur 1", plateau.getJoueur1(), plateau.getJoueur2());
        phaseFinTour("Joueur 1", plateau.getJoueur1());
        
        if (partieTerminee()) break;
        
        // ==================== TOUR JOUEUR 2 ====================
        std::cout << "\n╔═══════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║         🎮 TOUR DE " << std::left << std::setw(30) << "Joueur 2" << "             ║" << std::endl;
        std::cout << "╚═══════════════════════════════════════════════════════════╝" << std::endl;
        
        afficherMainJoueur("Joueur 2", plateau.getJoueur2());
        
        // NOUVEL AFFICHAGE: Champions en jeu
        afficherChampionsEnJeu("Joueur 2", plateau.getJoueur2());
        
        // ===== PHASE SPÉCIALE: Gestion des Champions =====
        std::cout << "\n┌─ PHASE SPÉCIALE: Champions ────────────────────────────┐" << std::endl;
        std::cout << "│ Gérer vos champions                                     │" << std::endl;
        std::cout << "└─────────────────────────────────────────────────────────┘" << std::endl;
        
        gererChampionsEnMain(plateau.getJoueur2(), plateau.getJoueur1());
        
        phaseCartesDeBase("Joueur 2", plateau.getJoueur2(), plateau.getJoueur1());
        phaseGemmesDeFeu("Joueur 2", plateau.getJoueur2());
        phaseAchatGemmes("Joueur 2", plateau.getJoueur2());
        phaseAchatActions("Joueur 2", plateau.getJoueur2());
        phaseUtilisationEffets("Joueur 2", plateau.getJoueur2(), plateau.getJoueur1());
        phaseUtilisationDegats("Joueur 2", plateau.getJoueur2(), plateau.getJoueur1());
        phaseFinTour("Joueur 2", plateau.getJoueur2());
    }
    
    afficherGagnant();
}

void Game::afficherEntete() {
    std::cout << "\n";
    std::cout << "╔═══════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                       TOUR " << std::setw(2) << std::setfill('0') << round << "                             ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════════════════╝" << std::endl;
}

void Game::afficherInfosJoueurs() {
    auto& j1 = plateau.getJoueur1();
    auto& j2 = plateau.getJoueur2();
    
    std::cout << "\n┌─────────────────────────────────────────────────────────┐" << std::endl;
    
    // Joueur 1
    std::cout << "│ JOUEUR 1 │ ";
    std::cout << "❤️  PV: " << j1.getPointDeVie() << " │ ";
    std::cout << "🃏 Main: " << j1.getMain().getCartes().size() << " │ ";
    std::cout << "📚 Pioche: " << j1.getPioche().getCartes().size() << " │ ";
    std::cout << "🗑️  Défausse: " << j1.getDefausse().getCartes().size() << " │" << std::endl;
    
    // Joueur 2
    std::cout << "│ JOUEUR 2 │ ";
    std::cout << "❤️  PV: " << j2.getPointDeVie() << " │ ";
    std::cout << "🃏 Main: " << j2.getMain().getCartes().size() << " │ ";
    std::cout << "📚 Pioche: " << j2.getPioche().getCartes().size() << " │ ";
    std::cout << "🗑️  Défausse: " << j2.getDefausse().getCartes().size() << " │" << std::endl;
    
    std::cout << "└─────────────────────────────────────────────────────────┘" << std::endl;
}

void Game::afficherMainJoueur(const std::string& nomJoueur, Joueur& joueur) {
    std::cout << "\n📋 Main de " << nomJoueur << " (" << joueur.getMain().getCartes().size() << " cartes)" << std::endl;
    std::cout << "   • Cartes de base: " << joueur.getMain().getCartesDeBase().size() << std::endl;
    std::cout << "   • Gemmes de feu: " << joueur.getMain().getGemmesDeFeu().size() << std::endl;
    std::cout << "   • Champions: " << joueur.getMain().getChampions().size() << std::endl;
    std::cout << "   • Actions: " << joueur.getMain().getActions().size() << std::endl;
    std::cout << "   • Gemmes disponibles au marché: " << plateau.getMarche().getGemmes().size() << std::endl;
    
    std::cout << "\n🃏 Cartes en main:" << std::endl;
    int idx = 1;
    for (auto* carte : joueur.getMain().getCartes()) {
        std::cout << "   [" << idx++ << "] " << carte->getNom() << std::endl;
    }
}

void Game::afficherSeparateur(char c, int largeur) {
    std::cout << std::string(largeur, c) << std::endl;
}

void Game::phaseCartesDeBase(const std::string& nomJoueur, Joueur& joueur, Joueur& /* adversaire */) {
    std::cout << "\n┌─ PHASE 1: Cartes de Base ─────────────────────────────┐" << std::endl;
    std::cout << "│ " << nomJoueur << ", voulez-vous utiliser vos cartes de base? │" << std::endl;
    std::cout << "│ [1] Oui  [0] Non                                        │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────┘" << std::endl;
    
    int choix;
    std::cin >> choix;
    
    if (choix == 1) {
        int pv_avant = joueur.getPointDeVie();
        int argent_avant = joueur.getArgent();
        int degats_avant = joueur.getDegatsStockes();
        
        if (nomJoueur == "Joueur 1") {
            plateau.utiliserEffetBasiqueJoueur1(joueur.getMain().getCartesDeBase());
        } else {
            plateau.utiliserEffetBasiqueJoueur2(joueur.getMain().getCartesDeBase());
        }
        
        std::cout << "\n✓ Résultats:" << std::endl;
        std::cout << "  ❤️  PV: " << pv_avant << " → " << joueur.getPointDeVie();
        if (joueur.getPointDeVie() > pv_avant) std::cout << " (+)";
        std::cout << std::endl;
        std::cout << "  💰 Or: " << argent_avant << " → " << joueur.getArgent() << std::endl;
        std::cout << "  ⚔️  Dégâts stockés: " << degats_avant << " → " << joueur.getDegatsStockes() << std::endl;
    } else {
        std::cout << "→ " << nomJoueur << " passe son tour pour les cartes de base." << std::endl;
    }
}

void Game::phaseGemmesDeFeu(const std::string& nomJoueur, Joueur& joueur) {
    auto gemmes = joueur.getMain().getGemmesDeFeu();
    if (gemmes.empty()) return;
    
    std::cout << "\n┌─ PHASE 2: Gemmes de Feu ───────────────────────────────┐" << std::endl;
    std::cout << "│ " << nomJoueur << " possède " << gemmes.size() << " gemme(s) de feu                │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────┘" << std::endl;
    
    std::vector<GemmeDeFeu*> gemmesASupprimer;
    
    for (size_t idx = 0; idx < gemmes.size(); ++idx) {
        auto* gemme = gemmes[idx];
        
        if (gemme == nullptr) {
            std::cout << "ERREUR: Gemme nulle!" << std::endl;
            continue;
        }
        
        if (gemme->estSacrifiee()) {
            std::cout << "💎 Gemme #" << (idx + 1) << " : Déjà sacrifiée, elle sera défaussée" << std::endl;
            gemmesASupprimer.push_back(gemme);
            continue;
        }
        
        std::cout << "\n💎 Gemme #" << (idx + 1) << ":" << std::endl;
        
        // Étape 1 : Utiliser l'effet +2 or
        std::cout << "  [1] Utiliser pour de l'or (+2 💰)" << std::endl;
        std::cout << "  [0] Ne pas utiliser cet effet" << std::endl;
        std::cout << "→ Votre choix: ";
        
        int choixOr;
        std::cin >> choixOr;
        
        if (choixOr == 1) {
            joueur.setArgent(joueur.getArgent() + 2);
            std::cout << "✓ +2 💰 (Total: " << joueur.getArgent() << ")" << std::endl;
        }
        
        // Étape 2 : Demander si le joueur veut sacrifier pour les dégâts
        std::cout << "\n  Voulez-vous SACRIFIER cette gemme pour +3 ⚔️  dégâts ?" << std::endl;
        std::cout << "  [1] Oui, sacrifier pour +3 dégâts" << std::endl;
        std::cout << "  [0] Non, garder la gemme" << std::endl;
        std::cout << "→ Votre choix: ";
        
        int choixSacrifice;
        std::cin >> choixSacrifice;
        
        if (choixSacrifice == 1) {
            joueur.setDegatsStockes(joueur.getDegatsStockes() + 3);
            std::cout << "✓ +3 ⚔️  dégâts (Total: " << joueur.getDegatsStockes() << ")" << std::endl;
            std::cout << "  🔥 Gemme sacrifiée! Elle sera mise dans la zone de sacrifice." << std::endl;
            
            gemmesASupprimer.push_back(gemme);
            ZoneDeSacrifice zone = plateau.getZoneDeSacrifice();
            zone.add(gemme);
            plateau.setZoneDeSacrifice(zone);
        } else {
            std::cout << "  Gemme conservée en main." << std::endl;
        }
    }
    
    if (!gemmesASupprimer.empty()) {
        MainJoueur mainUpdated = joueur.getMain();
        for (auto* gemme : gemmesASupprimer) {
            mainUpdated.removeCarte(gemme);
        }
        joueur.setMain(mainUpdated);
    }
}

void Game::phaseAchatGemmes(const std::string& /* nomJoueur */, Joueur& joueur) {
    if (joueur.getArgent() < 3 || plateau.getMarche().getGemmes().empty()) return;
    
    std::cout << "\n┌─ PHASE 3: Achat de Gemmes ─────────────────────────────┐" << std::endl;
    std::cout << "│ 💰 Votre or: " << joueur.getArgent() << " | Prix gemme: 3 💰           │" << std::endl;
    std::cout << "│ 💎 Gemmes disponibles: " << plateau.getMarche().getGemmes().size() << "                          │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────┘" << std::endl;
    
    while (joueur.getArgent() >= 3 && !plateau.getMarche().getGemmes().empty()) {
        std::cout << "→ Acheter une gemme? [1] Oui [0] Non: ";
        int choix;
        std::cin >> choix;
        
        if (choix != 1) break;
        
        joueur.setArgent(joueur.getArgent() - 3);
        Defausse defausse = joueur.getDefausse();
        defausse.addCarte(plateau.getMarche().acheterGemme());
        joueur.setDefausse(defausse);
        
        std::cout << "✓ Gemme achetée! Or restant: " << joueur.getArgent() << " 💰" << std::endl;
        std::cout << "  Gemmes restantes au marché: " << plateau.getMarche().getGemmes().size() << std::endl;
    }
}

void Game::phaseAchatActions(const std::string& /* nomJoueur */, Joueur& joueur) {
    std::cout << "\n┌─ PHASE 4: Achat d'Actions/Champions ──────────────────┐" << std::endl;
    std::cout << "│ 💰 Or disponible: " << std::setw(2) << joueur.getArgent() << "                                 │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────┘" << std::endl;
    
    // S'assurer qu'il y a toujours 5 cartes vendables
    while (plateau.getMarche().getActionsVendables().size() < 5 && 
           !plateau.getMarche().getStackActions().empty()) {
        plateau.getMarche().MiseAJourActionsVendables();
    }
    
    std::cout << "\n🛒 Cartes disponibles:" << std::endl;
    for (size_t i = 0; i < plateau.getMarche().getActionsVendables().size(); ++i) {
        Action* action = plateau.getMarche().getActionsVendables()[i];
        std::cout << "  • " << action->getNom() << " (" << action->getPrix() << " 💰)" << std::endl;
    }
    
    plateau.achatActionChampion(joueur);
}

void Game::phaseUtilisationEffets(const std::string& nomJoueur, Joueur& /* joueur */, Joueur& /* adversaire */) {
    std::cout << "\n┌─ PHASE 5: Utilisation des Effets ──────────────────────┐" << std::endl;
    std::cout << "│ Choisissez les effets de vos cartes                    │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────┘" << std::endl;
    
    if (nomJoueur == "Joueur 1") {
        auto [effetsBasiques, effetsTextuels] = plateau.choixUtilisationEffetJ1();
        plateau.appliquerEffetsJ1(effetsBasiques, effetsTextuels);
    } else {
        auto [effetsBasiques, effetsTextuels] = plateau.choixUtilisationEffetJ2();
        plateau.appliquerEffetsJ2(effetsBasiques, effetsTextuels);
    }
}

void Game::phaseUtilisationDegats(const std::string& /* nomJoueur */, Joueur& joueur, Joueur& adversaire) {
    if (joueur.getDegatsStockes() <= 0) return;
    
    std::cout << "\n┌─ PHASE 6: Utilisation des Dégâts ──────────────────────┐" << std::endl;
    std::cout << "│ ⚔️  Dégâts disponibles: " << joueur.getDegatsStockes() << "                           │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────┘" << std::endl;
    
    plateau.utiliserDegatsStockes(joueur, adversaire);
}

void Game::phaseFinTour(const std::string& /* nomJoueur */, Joueur& joueur) {
    std::cout << "\n┌─ FIN DU TOUR ───────────────────────────────────────────┐" << std::endl;
    
    // Déplacer cartes vers défausse
    Defausse defausse = joueur.getDefausse();
    MainJoueur main = joueur.getMain();
    
    auto cartesMain = main.getCartes();
    for (auto* carte : cartesMain) {
        defausse.addCarte(carte);
        main.removeCarte(carte);
    }
    
    joueur.setDefausse(defausse);
    joueur.setMain(main);
    
    // Piocher 5 nouvelles cartes
    MainJoueur nouvelleMain;
    Pioche pioche = joueur.getPioche();
    
    for (int i = 0; i < 5; ++i) {
        if (pioche.getCartes().empty()) {
            for (auto* carte : defausse.getCartes()) {
                pioche.addCarte(carte);
            }
            defausse.clear();
            joueur.setDefausse(defausse);
        }
        
        if (pioche.getCartes().empty()) break;
        
        Carte* carte = pioche.getCartes()[0];
        pioche.tirerCarte(carte);
        nouvelleMain.addCarte(carte);
    }
    
    joueur.setMain(nouvelleMain);
    joueur.setPioche(pioche);
    joueur.setArgent(0);
    joueur.setDegatsStockes(0);
    
    std::cout << "│ ✓ Cartes défaussées                                    │" << std::endl;
    std::cout << "│ ✓ 5 nouvelles cartes piochées :                        │" << std::endl;
    
    // Afficher les nouvelles cartes piochées
    int idx = 1;
    for (auto* carte : nouvelleMain.getCartes()) {
        if (carte != nullptr) {
            std::string nomCarte = carte->getNom();
            if (nomCarte.empty()) {
                nomCarte = "(Carte sans nom)";
            }
            std::cout << "│   [" << idx++ << "] " << std::left << std::setw(45) << nomCarte << " │" << std::endl;
        } else {
            std::cout << "│   [" << idx++ << "] " << std::left << std::setw(45) << "(Carte invalide)" << " │" << std::endl;
        }
    }
    
    std::cout << "│ ✓ Ressources réinitialisées                            │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────┘" << std::endl;
}

void Game::tourJoueur(const std::string& nomJoueur, Joueur& joueur, Joueur& adversaire) {
    std::cout << "\n\n";
    std::cout << "╔═══════════════════════════════════════════════════════════╗" << std::endl;
    // Limiter la longueur et utiliser std::right pour l'alignement
    std::string nomAffiche = nomJoueur.length() > 15 ? nomJoueur.substr(0, 15) : nomJoueur;
    std::cout << "║         🎮 TOUR DE " << std::setfill(' ') << std::left << std::setw(15) << nomAffiche 
              << "                      ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════════════════╝" << std::endl;
    
    afficherMainJoueur(nomJoueur, joueur);
    
    phaseCartesDeBase(nomJoueur, joueur, adversaire);
    phaseGemmesDeFeu(nomJoueur, joueur);
    phaseUtilisationEffets(nomJoueur, joueur, adversaire);  // Déplacé ici
    phaseAchatGemmes(nomJoueur, joueur);
    phaseAchatActions(nomJoueur, joueur);
    phaseUtilisationDegats(nomJoueur, joueur, adversaire);
    phaseFinTour(nomJoueur, joueur);
}

bool Game::partieTerminee() const {
    return plateau.getJoueur1().getPointDeVie() <= 0 || 
           plateau.getJoueur2().getPointDeVie() <= 0;
}

void Game::afficherGagnant() const {
    std::cout << "\n\n";
    std::cout << "╔═══════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                    FIN DE LA PARTIE                       ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════════════════╝" << std::endl;
    
    if (plateau.getJoueur1().getPointDeVie() > 0) {
        std::cout << "\n🏆 JOUEUR 1 REMPORTE LA VICTOIRE! 🏆" << std::endl;
        std::cout << "   PV restants: " << plateau.getJoueur1().getPointDeVie() << " ❤️" << std::endl;
    } else {
        std::cout << "\n🏆 JOUEUR 2 REMPORTE LA VICTOIRE! 🏆" << std::endl;
        std::cout << "   PV restants: " << plateau.getJoueur2().getPointDeVie() << " ❤️" << std::endl;
    }
    
    std::cout << "\nStatistiques finales:" << std::endl;
    std::cout << "  Tours joués: " << round << std::endl;
}

void Game::gererChampionsEnMain(Joueur& joueur, Joueur& adversaire) {
    auto champions = joueur.getMain().getChampions();
    
    if (champions.empty()) {
        std::cout << "   Aucun champion en main." << std::endl;
        return;
    }
    
    std::cout << "\n   Vous avez " << champions.size() << " champion(s) en main." << std::endl;
    
    // Parcourir tous les champions en main
    for (size_t i = 0; i < champions.size(); ++i) {
        Champion* champion = champions[i];
        
        // Ignorer les champions déjà en défense
        if (champion->getIsDefense()) {
            continue;
        }
        
        std::cout << "\n🎖️  Champion #" << (i + 1) << ": " << champion->getNom() << std::endl;
        std::cout << "   💰 Prix: " << champion->getPrix() << std::endl;
        std::cout << "   ❤️  PV: " << champion->getPointDeVie() << std::endl;
        std::cout << "   🛡️  Garde: " << (champion->getIsGarde() ? "Oui" : "Non") << std::endl;
        
        std::cout << "   📋 Effets (Choix 1): ";
        for (const auto& effet : champion->getEffetsBasiqueChoix1()) {
            std::cout << effet.toString() << " ";
        }
        std::cout << std::endl;
        
        if (!champion->getListEffetTextuelChoix1().empty()) {
            std::cout << "   📜 Effets textuels: ";
            for (const auto& effet : champion->getListEffetTextuelChoix1()) {
                std::cout << effet.toString() << " ";
            }
            std::cout << std::endl;
        }
        
        std::cout << "\n   Voulez-vous jouer ce champion ce tour?" << std::endl;
        std::cout << "   [1] Oui  [0] Non" << std::endl;
        std::cout << "   → Votre choix: ";
        
        int choix;
        std::cin >> choix;
        
        if (choix == 1) {
            std::cout << "\n   ✅ Vous jouez " << champion->getNom() << "!" << std::endl;
            
            // 1. Appliquer les effets du champion (Choix 1)
            std::cout << "   📋 Application des effets:" << std::endl;
            
            for (const auto& effet : champion->getEffetsBasiqueChoix1()) {
                switch (effet.getType()) {
                    case OR:
                        joueur.setArgent(joueur.getArgent() + effet.getValeur());
                        std::cout << "      💰 +" << effet.getValeur() << " or (Total: " << joueur.getArgent() << ")" << std::endl;
                        break;
                    case DEGAT:
                        joueur.setDegatsStockes(joueur.getDegatsStockes() + effet.getValeur());
                        std::cout << "      ⚔️  +" << effet.getValeur() << " dégâts (Total: " << joueur.getDegatsStockes() << ")" << std::endl;
                        break;
                    case SOIN:
                        joueur.setPointDeVie(joueur.getPointDeVie() + effet.getValeur());
                        std::cout << "      ❤️  +" << effet.getValeur() << " PV (Total: " << joueur.getPointDeVie() << ")" << std::endl;
                        break;
                }
            }
            
            // 2. Appliquer les effets textuels (Choix 1)
            for (const auto& effetTextuel : champion->getListEffetTextuelChoix1()) {
                EffetTextuel::handleIdEffetTextuel(effetTextuel.getId(), joueur, adversaire);
            }
            
            // ORDRE IMPORTANT:
            // 1. Retirer de la main D'ABORD
            MainJoueur main = joueur.getMain();
            main.removeCarte(champion);
            joueur.setMain(main);
            std::cout << "  ➡️  Champion retiré de la main" << std::endl;
            
            // 2. Activer le mode défense
            champion->setIsDefense(true);
            std::cout << "  ➡️  Mode défense activé" << std::endl;
            
            // 3. Ajouter au StackChampion (qui filtrera automatiquement)
            StackChampion stackChamp = joueur.getStackChampion();
            
            std::cout << "  📊 Avant push(): " << stackChamp.getChampions().size() 
                      << " champions, " << stackChamp.getGardes().size() << " gardes" << std::endl;
            
            stackChamp.push(champion);  // push() vérifie et ajoute aux gardes
            
            std::cout << "  📊 Après push(): " << stackChamp.getChampions().size() 
                      << " champions, " << stackChamp.getGardes().size() << " gardes" << std::endl;
            
            joueur.setStackChampion(stackChamp);
            
            std::cout << "  ➡️  StackChampion mis à jour" << std::endl;
            
            // Mettre à jour la liste des champions (car un a été retiré)
            champions = joueur.getMain().getChampions();
            --i; // Ajuster l'index car le vecteur a changé
        } else {
            std::cout << "   ⏭️  Champion gardé en main." << std::endl;
        }
    }
    
    // Afficher un résumé des champions en jeu
    if (!joueur.getStackChampion().getChampions().empty()) {
        std::cout << "\n   🎖️  Champions actuellement en jeu:" << std::endl;
        for (const auto& champ : joueur.getStackChampion().getChampions()) {
            std::cout << "      • " << champ->getNom() 
                      << " (❤️  " << champ->getPointDeVie() << " PV)";
            if (champ->getIsGarde()) {
                std::cout << " 🛡️  [GARDE]";
            }
            std::cout << std::endl;
        }
    }
}

void Game::afficherChampionsEnJeu(const std::string& nomJoueur, Joueur& joueur) {
    auto champions = joueur.getStackChampion().getChampions();
    auto gardes = joueur.getStackChampion().getGardes();
    
    if (champions.empty()) {
        std::cout << "\n🎖️  " << nomJoueur << " n'a aucun champion en jeu." << std::endl;
        return;
    }
    
    std::cout << "\n┌─ 🎖️  CHAMPIONS EN JEU (" << nomJoueur << ") ─────────────┐" << std::endl;
    std::cout << "│ Total: " << champions.size() << " champion(s)";
    if (!gardes.empty()) {
        std::cout << " dont " << gardes.size() << " garde(s) 🛡️";
    }
    std::cout << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────┘" << std::endl;
    
    for (size_t i = 0; i < champions.size(); ++i) {
        Champion* champ = champions[i];
        std::cout << "   " << (i + 1) << ". " << champ->getNom();
        std::cout << " (❤️  " << champ->getPointDeVie() << " PV)";
        
        if (champ->getIsGarde()) {
            std::cout << " 🛡️  [GARDE]";
        }
        
        if (champ->getIsDefense()) {
            std::cout << " [Mode Défense]";
        }
        
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
