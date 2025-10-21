#include "Plateau.h"
#include <iostream>

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
        std::cout << "Tour " << round << std::endl;
        std::cout << "Joueur1 PV: " << plateau.getJoueur1().getPointDeVie()
                  << " | Joueur2 PV: " << plateau.getJoueur2().getPointDeVie() << std::endl;
        
        std::cout << "C'est au Joueur1 de jouer " << std::endl;
        std::cout << "La main du joueur 1 est composée des cartes de base :" << std::endl;
        for (auto* carte : plateau.getJoueur1().getMain().getCartesDeBase()) {
            std::cout << " - " << carte->toString() << std::endl;
        }
        std::cout << "Joueur 1 appuyez sur 1 si vous voulez utiliser les effets de vos cartes de base." << std::endl;
        int choix;
        std::cin >> choix;
        if (choix == 1) {
            plateau.utiliserEffetBasiqueJoueur1(plateau.getJoueur1().getMain().getCartesDeBase());
        }
        else{
            std::cout << "Joueur 1 n'utilise pas les effets de ces cartes de base cette manche." << std::endl;
        }

        Defausse newDefausseJoueur1 = plateau.getJoueur1().getDefausse();

        for(auto* carte : plateau.getJoueur1().getMain().getCartesDeBase()) {

            newDefausseJoueur1.addCarte(carte);
        }
        plateau.getJoueur1().setDefausse(newDefausseJoueur1);

        MainJoueur newMainJoueur1 = MainJoueur();
        Pioche newPiocheJoueur1 = plateau.getJoueur1().getPioche();


        for(int i = 0; i < 5; ++i) {
            //Si la pioche est vide, on remplit la pioche avec la défausse
            if(newPiocheJoueur1.getCartes().empty()) {
                for(auto* carte : newDefausseJoueur1.getCartes()) {
                    newPiocheJoueur1.addCarte(carte);
                }
                newDefausseJoueur1.clear();
                plateau.getJoueur1().setDefausse(newDefausseJoueur1);
                plateau.getJoueur1().setPioche(newPiocheJoueur1);
            }

            // Si on n'a plus de cartes dans la pioche (après reconstitution), sortir de la boucle
            if (newPiocheJoueur1.getCartes().empty()) break;

            // Prendre la première carte disponible (sécurisé contre out-of-range)
            Carte* carte = newPiocheJoueur1.getCartes()[i % newPiocheJoueur1.getCartes().size()];
            newPiocheJoueur1.tirerCarte(carte);
            newMainJoueur1.addCarte(carte);

        }

        plateau.getJoueur1().setMain(newMainJoueur1);
        plateau.getJoueur1().setPioche(newPiocheJoueur1);

        std::cout << "C'est au Joueur2 de jouer " << std::endl;
        std::cout << "La main du joueur 2 est composée des cartes de base :" << std::endl;
        for (auto* carte : plateau.getJoueur2().getMain().getCartesDeBase()) {
            std::cout << " - " << carte->toString() << std::endl;
        }
        std::cout << "Joueur 2 appuyez sur 1 si vous voulez utiliser les effets de vos cartes de base." << std::endl;
        choix = 0;
        std::cin >> choix;
        if (choix == 1) {
            plateau.utiliserEffetBasiqueJoueur2(plateau.getJoueur2().getMain().getCartesDeBase());
        }
        else{
            std::cout << "Joueur 2 n'utilise pas les effets de ces cartes de base cette manche." << std::endl;
        }

        // --- Ajout: traitement pour le Joueur2 déplacé ici (après son choix) ---
        {
            Defausse newDefausseJoueur2 = plateau.getJoueur2().getDefausse();

            for(auto* carte : plateau.getJoueur2().getMain().getCartesDeBase()) {
                newDefausseJoueur2.addCarte(carte);
            }
            plateau.getJoueur2().setDefausse(newDefausseJoueur2);

            MainJoueur newMainJoueur2 = MainJoueur();
            Pioche newPiocheJoueur2 = plateau.getJoueur2().getPioche();

            for(int i = 0; i < 5; ++i) {
                // Si la pioche est vide, on remplit la pioche avec la défausse
                if(newPiocheJoueur2.getCartes().empty()) {
                    for(auto* carte : newDefausseJoueur2.getCartes()) {
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
        }
        // --- Fin du bloc ajouté pour Joueur2 ---



        // condition d'arrêt simplifiée
        if (plateau.getJoueur1().getPointDeVie() <= 0 || plateau.getJoueur2().getPointDeVie() <= 0) {
            break;
        }
        
        }

        std::cout << "=== Fin de la partie ===" << std::endl;

    }


void Plateau::utiliserEffetBasiqueJoueur1(const std::vector<CarteDeBase*>& cartes) {
    for (auto* carte : cartes) {
        for (const auto& effet : carte->getEffetsBasiqueChoix1()) {
            switch (effet.getType()) {
                case DEGAT:
                    joueur2.setPointDeVie(joueur2.getPointDeVie() - effet.getValeur());
                    std::cout << "La carte " << carte->toString() << " inflige " << effet.getValeur() << " PV de degat à Joueur2." << std::endl;
                    break;
                case SOIN:
                    joueur1.setPointDeVie(joueur1.getPointDeVie() + effet.getValeur());
                    std::cout << "La carte " << carte->toString() << " soigne Joueur1 de " << effet.getValeur() << " PV." << std::endl;
                    break;
                default:
                    // autres types ignorés pour l'instant
                    break;
            }
        }
    }
}

void Plateau::utiliserEffetBasiqueJoueur2(const std::vector<CarteDeBase*>& cartes) {
    for (auto* carte : cartes) {
        for (const auto& effet : carte->getEffetsBasiqueChoix1()) {
            switch (effet.getType()) {
                case DEGAT:
                    joueur1.setPointDeVie(joueur1.getPointDeVie() - effet.getValeur());
                    std::cout << "Joueur1 perd " << effet.getValeur() << " PV (par degat)." << std::endl;
                    break;
                case SOIN:
                    joueur2.setPointDeVie(joueur2.getPointDeVie() + effet.getValeur());
                    std::cout << "Joueur2 gagne " << effet.getValeur() << " PV (par soin)." << std::endl;
                    break;
                default:
                    // autres types ignorés pour l'instant
                    break;
            }
        }
    }
}
