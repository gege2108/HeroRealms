#include "Plateau.h"
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
    std::cout << "=== Début d'une partie simplifiée ===" << std::endl;
    int round = 0;
    while (round < 10) {
        ++round;

        // En-tête de tour plus lisible
        std::cout << std::endl;
        std::cout << std::string(60, '=') << std::endl;
        std::cout << "                      TOUR " << round << std::endl;
        std::cout << std::string(60, '=') << std::endl;

        // Affichage compact et lisible des informations des joueurs
        auto& j1 = plateau.getJoueur1();
        auto& j2 = plateau.getJoueur2();

        std::cout << std::left << std::setw(20) << "Joueur 1"
                  << "PV: " << std::setw(3) << j1.getPointDeVie()
                  << " | Main: " << std::setw(2) << j1.getMain().getCartesDeBase().size()
                  << " | Pioche: " << std::setw(2) << j1.getPioche().getCartes().size()
                  << " | Defausse: " << std::setw(2) << j1.getDefausse().getCartes().size()
                  << std::endl;

        std::cout << std::left << std::setw(20) << "Joueur 2"
                  << "PV: " << std::setw(3) << j2.getPointDeVie()
                  << " | Main: " << std::setw(2) << j2.getMain().getCartesDeBase().size()
                  << " | Pioche: " << std::setw(2) << j2.getPioche().getCartes().size()
                  << " | Defausse: " << std::setw(2) << j2.getDefausse().getCartes().size()
                  << std::endl;

        std::cout << std::string(60, '-') << std::endl;

        // Tour du joueur 1
        std::cout << "C'est au Joueur1 de jouer" << std::endl;
        std::cout << "La main du joueur 1 est composée des cartes de base :" << std::endl;
        int idx = 1;
        for (auto* carte : plateau.getJoueur1().getMain().getCartesDeBase()) {
            std::cout << "  [" << idx++ << "] " << carte->toString() << std::endl;
        }
        std::cout << "Joueur 1 appuyez sur 1 si vous voulez utiliser les effets de vos cartes de base." << std::endl;
        int choix;
        std::cin >> choix;
        if (choix == 1) {
            // Affichage avant-après pour mieux visualiser l'impact
            int pv1_avant = plateau.getJoueur1().getPointDeVie();
            int pv2_avant = plateau.getJoueur2().getPointDeVie();
            std::cout << "-> Application des effets : PV avant -> Joueur1: " << pv1_avant << " | Joueur2: " << pv2_avant << std::endl;

            plateau.utiliserEffetBasiqueJoueur1(plateau.getJoueur1().getMain().getCartesDeBase());

            int pv1_apres = plateau.getJoueur1().getPointDeVie();
            int pv2_apres = plateau.getJoueur2().getPointDeVie();
            std::cout << "-> Résultat : PV après  -> Joueur1: " << pv1_apres << " | Joueur2: " << pv2_apres << std::endl;
            std::cout << std::string(60, '-') << std::endl;
        }
        else{
            std::cout << "Joueur 1 n'utilise pas les effets de ces cartes de base cette manche." << std::endl;
            std::cout << std::string(60, '-') << std::endl;
        }

        // Déplacement propre des cartes de la main vers la défausse (Joueur1)
        Defausse newDefausseJoueur1 = plateau.getJoueur1().getDefausse();
        MainJoueur updatedMainJ1 = plateau.getJoueur1().getMain(); // copie modifiable

        auto cartesMain = updatedMainJ1.getCartesDeBase();
        for (auto* carte : cartesMain) {
            newDefausseJoueur1.addCarte(carte);
            updatedMainJ1.removeCarte(carte);
        }

        plateau.getJoueur1().setDefausse(newDefausseJoueur1);
        plateau.getJoueur1().setMain(updatedMainJ1);

        // Tirage pour Joueur1 (reprise existante, représentation inchangée)
        MainJoueur newMainJoueur1 = MainJoueur();
        Pioche newPiocheJoueur1 = plateau.getJoueur1().getPioche();

        for(int i = 0; i < 5; ++i) {
            if(newPiocheJoueur1.getCartes().empty()) {
                for(auto* carte : newDefausseJoueur1.getCartes()) {
                    newPiocheJoueur1.addCarte(carte);
                }
                newDefausseJoueur1.clear();
                plateau.getJoueur1().setDefausse(newDefausseJoueur1);
                plateau.getJoueur1().setPioche(newPiocheJoueur1);
            }

            if (newPiocheJoueur1.getCartes().empty()) break;

            Carte* carte = newPiocheJoueur1.getCartes()[i % newPiocheJoueur1.getCartes().size()];
            newPiocheJoueur1.tirerCarte(carte);
            newMainJoueur1.addCarte(carte);
        }

        plateau.getJoueur1().setMain(newMainJoueur1);
        plateau.getJoueur1().setPioche(newPiocheJoueur1);

        // Tour du joueur 2
        std::cout << "C'est au Joueur2 de jouer" << std::endl;
        std::cout << "La main du joueur 2 est composée des cartes de base :" << std::endl;
        idx = 1;
        for (auto* carte : plateau.getJoueur2().getMain().getCartesDeBase()) {
            std::cout << "  [" << idx++ << "] " << carte->toString() << std::endl;
        }
        std::cout << "Joueur 2 appuyez sur 1 si vous voulez utiliser les effets de vos cartes de base." << std::endl;
        choix = 0;
        std::cin >> choix;
        if (choix == 1) {
            int pv1_avant = plateau.getJoueur1().getPointDeVie();
            int pv2_avant = plateau.getJoueur2().getPointDeVie();
            std::cout << "-> Application des effets : PV avant -> Joueur1: " << pv1_avant << " | Joueur2: " << pv2_avant << std::endl;

            plateau.utiliserEffetBasiqueJoueur2(plateau.getJoueur2().getMain().getCartesDeBase());

            int pv1_apres = plateau.getJoueur1().getPointDeVie();
            int pv2_apres = plateau.getJoueur2().getPointDeVie();
            std::cout << "-> Résultat : PV après  -> Joueur1: " << pv1_apres << " | Joueur2: " << pv2_apres << std::endl;
            std::cout << std::string(60, '-') << std::endl;
        }
        else{
            std::cout << "Joueur 2 n'utilise pas les effets de ces cartes de base cette manche." << std::endl;
            std::cout << std::string(60, '-') << std::endl;
        }

        // Déplacement propre des cartes de la main vers la défausse (Joueur2)
        Defausse newDefausseJoueur2 = plateau.getJoueur2().getDefausse();
        MainJoueur updatedMainJ2 = plateau.getJoueur2().getMain(); // copie modifiable

        auto cartesMain2 = updatedMainJ2.getCartesDeBase();
        for (auto* carte : cartesMain2) {
            newDefausseJoueur2.addCarte(carte);
            updatedMainJ2.removeCarte(carte);
        }

        plateau.getJoueur2().setDefausse(newDefausseJoueur2);
        plateau.getJoueur2().setMain(updatedMainJ2);

        // Tirage pour Joueur2 (même logique que pour Joueur1)
        MainJoueur newMainJoueur2 = MainJoueur();
        Pioche newPiocheJoueur2 = plateau.getJoueur2().getPioche();

        for (int i = 0; i < 5; ++i) {
            // Si la pioche est vide, on remplit la pioche avec la défausse
            if (newPiocheJoueur2.getCartes().empty()) {
                for (auto* carte : newDefausseJoueur2.getCartes()) {
                    newPiocheJoueur2.addCarte(carte);
                }
                newDefausseJoueur2.clear();
                plateau.getJoueur2().setDefausse(newDefausseJoueur2);
                plateau.getJoueur2().setPioche(newPiocheJoueur2);
            }

            // Si on n'a plus de cartes dans la pioche (après reconstitution), sortir de la boucle
            if (newPiocheJoueur2.getCartes().empty()) break;

            // Prendre la première carte disponible (sécurisé contre out-of-range)
            Carte* carte = newPiocheJoueur2.getCartes()[i % newPiocheJoueur2.getCartes().size()];
            newPiocheJoueur2.tirerCarte(carte);
            newMainJoueur2.addCarte(carte);
        }

        plateau.getJoueur2().setMain(newMainJoueur2);
        plateau.getJoueur2().setPioche(newPiocheJoueur2);


        // condition d'arrêt simplifiée
        if (plateau.getJoueur1().getPointDeVie() <= 0 || plateau.getJoueur2().getPointDeVie() <= 0) {
            break;
        }

    } // fin while

    std::cout << "=== Fin de la partie ===" << std::endl;
}


void Plateau::utiliserEffetBasiqueJoueur1(const std::vector<CarteDeBase*>& cartes) {
    std::cout << "--- Résolution des effets (Joueur1) ---" << std::endl;
    for (auto* carte : cartes) {
        for (const auto& effet : carte->getEffetsBasiqueChoix1()) {
            switch (effet.getType()) {
                case DEGAT: {
                    int before = joueur2.getPointDeVie();
                    joueur2.setPointDeVie(before - effet.getValeur());
                    std::cout << " - " << carte->toString() << " => -" << effet.getValeur()
                              << " PV à Joueur2 ( " << before << " -> " << joueur2.getPointDeVie() << " )" << std::endl;
                    break;
                }
                case SOIN: {
                    int before = joueur1.getPointDeVie();
                    joueur1.setPointDeVie(before + effet.getValeur());
                    std::cout << " - " << carte->toString() << " => +" << effet.getValeur()
                              << " PV à Joueur1 ( " << before << " -> " << joueur1.getPointDeVie() << " )" << std::endl;
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
                    int before = joueur1.getPointDeVie();
                    joueur1.setPointDeVie(before - effet.getValeur());
                    std::cout << " - " << carte->toString() << " => -" << effet.getValeur()
                              << " PV à Joueur1 ( " << before << " -> " << joueur1.getPointDeVie() << " )" << std::endl;
                    break;
                }
                case SOIN: {
                    int before = joueur2.getPointDeVie();
                    joueur2.setPointDeVie(before + effet.getValeur());
                    std::cout << " - " << carte->toString() << " => +" << effet.getValeur()
                              << " PV à Joueur2 ( " << before << " -> " << joueur2.getPointDeVie() << " )" << std::endl;
                    break;
                }
                default:
                    std::cout << " - " << carte->toString() << " => effet non géré pour l'instant." << std::endl;
                    break;
            }
        }
    }
    std::cout << "--- Fin résolution (Joueur2) ---" << std::endl;
    std::cout << "Etat courant : Joueur1 PV=" << joueur1.getPointDeVie()
              << " | Joueur2 PV=" << joueur2.getPointDeVie() << std::endl;
}
