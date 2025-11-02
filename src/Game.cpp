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
        std::cout << "DEBUG: Début du tour " << round << std::endl;
        
        afficherEntete();
        afficherInfosJoueurs();
        
        std::cout << "DEBUG: Avant tour Joueur 1" << std::endl;
        // Tour du Joueur 1
        tourJoueur("Joueur 1", plateau.getJoueur1(), plateau.getJoueur2());
        
        if (partieTerminee()) break;
        
        std::cout << "DEBUG: Avant tour Joueur 2" << std::endl;
        // Tour du Joueur 2
        tourJoueur("Joueur 2", plateau.getJoueur2(), plateau.getJoueur1());
        
        std::cout << "DEBUG: Fin du tour " << round << std::endl;
    }
    
    std::cout << "DEBUG: Affichage du gagnant" << std::endl;
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
    int idx = 1;
    
    for (auto* gemme : gemmes) {
        std::cout << "\n💎 Gemme #" << idx << ":" << std::endl;
        std::cout << "  [1] Utiliser pour de l'or (+2 💰)" << std::endl;
        std::cout << "  [2] Sacrifier pour des dégâts (+3 ⚔️ )" << std::endl;
        std::cout << "  [0] Passer" << std::endl;
        std::cout << "→ Votre choix: ";
        
        int choix;
        std::cin >> choix;
        
        if (choix == 1) {
            Effet effet = gemme->getEffetsBasiqueChoix1()[0];
            joueur.setArgent(joueur.getArgent() + effet.getValeur());
            std::cout << "✓ +" << effet.getValeur() << " 💰 (Total: " << joueur.getArgent() << ")" << std::endl;
        } else if (choix == 2) {
            Effet& effetAttaque = gemme->UtiliserAttaque();
            joueur.setDegatsStockes(joueur.getDegatsStockes() + effetAttaque.getValeur());
            std::cout << "✓ +" << effetAttaque.getValeur() << " ⚔️  dégâts (Total: " << joueur.getDegatsStockes() << ")" << std::endl;
            std::cout << "  🔥 Gemme sacrifiée!" << std::endl;
            
            gemmesASupprimer.push_back(gemme);
            ZoneDeSacrifice zone = plateau.getZoneDeSacrifice();
            zone.add(gemme);
            plateau.setZoneDeSacrifice(zone);
        }
        idx++;
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
