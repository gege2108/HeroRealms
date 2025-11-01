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
    while (round < 10 && plateau.getJoueur1().getPointDeVie() > 0 && plateau.getJoueur2().getPointDeVie() > 0) {
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
                  << " | Main: " << std::setw(2) << j1.getMain().getCartes().size()
                  << " | Pioche: " << std::setw(2) << j1.getPioche().getCartes().size()
                  << " | Defausse: " << std::setw(2) << j1.getDefausse().getCartes().size()
                  << std::endl;

        std::cout << std::left << std::setw(20) << "Joueur 2"
                  << "PV: " << std::setw(3) << j2.getPointDeVie()
                  << " | Main: " << std::setw(2) << j2.getMain().getCartes().size()
                  << " | Pioche: " << std::setw(2) << j2.getPioche().getCartes().size()
                  << " | Defausse: " << std::setw(2) << j2.getDefausse().getCartes().size()
                  << std::endl;

        std::cout << std::string(60, '-') << std::endl;

        // Tour du joueur 1
        std::cout << "C'est au Joueur1 de jouer" << std::endl;
        std::cout << "Le joueur 1 a en main " << plateau.getJoueur1().getMain().getCartes().size() << " cartes." << std::endl;
        std::cout << plateau.getJoueur1().getMain().getCartesDeBase().size() << " cartes de base :" << std::endl;
        std::cout << plateau.getJoueur1().getMain().getGemmesDeFeu().size() << " gemmes de feu :" << std::endl;

        std::cout << "La main du joueur 1 est composée des cartes :" << std::endl;
        std::cout << "Il y a " << plateau.getMarche().getGemmes().size() << " gemmes dans le marché." << std::endl;
        int idx = 1;
        for (auto* carte : plateau.getJoueur1().getMain().getCartes()) {
            std::cout << "  [" << idx++ << "] " << carte->getNom() << std::endl;
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
            //int pv2_apres = plateau.getJoueur2().getPointDeVie();
            int argent_apres = plateau.getJoueur1().getArgent();
            int degats_stockes_apres = plateau.getJoueur1().getDegatsStockes();
            std::cout << "-> Résultat : Joueur1 : PV après  -> " << pv1_apres << ", | Argent du Joueur 1: " << argent_apres << ", | Dégâts stockés : " << degats_stockes_apres << std::endl;
            std::cout << std::string(60, '-') << std::endl;
        }
        else{
            std::cout << "Joueur 1 n'utilise pas les effets de ces cartes de base cette manche." << std::endl;
            std::cout << std::string(60, '-') << std::endl;
        }

        //utilisation des gemmes de feu par le joueur 1
        auto gemmesDeFeuJ1 = plateau.getJoueur1().getMain().getGemmesDeFeu(); // Copie pour éviter modification pendant itération
        if (!gemmesDeFeuJ1.empty())
        {
            std::cout << "La main du joueur 1 est composée de " << gemmesDeFeuJ1.size() << " gemmes de feu :" << std::endl;
            idx = 1;
            
            // Utiliser une copie et traiter les suppressions après
            std::vector<GemmeDeFeu*> gemmesASupprimer;
            
            for (auto* gemme : gemmesDeFeuJ1) {
                std::cout << "Joueur 1 appuyez sur 1 si vous voulez utiliser l'effet d'argent de votre gemme de feu numero " << idx <<  ", appuyez sur 2 si vous voulez utiliser l'effet faisant 3 de degats (la carte sera sacrifiée dans ce cas)." << std::endl;
                int choixGemmeP1 = 0;
                std::cin >> choixGemmeP1;

                if (choixGemmeP1 == 1) {
                    std::cout << "Utilisation de l'effet d'or de la gemme de feu numéro " << idx << std::endl;
                    Effet effetGemmeJ1 = gemme->getEffetsBasiqueChoix1()[0];
                    plateau.getJoueur1().setArgent(effetGemmeJ1.getValeur() + plateau.getJoueur1().getArgent());
                    std::cout << "Le joueur 1 gagne " << effetGemmeJ1.getValeur() << " pièces d'or, il a maintenant " << plateau.getJoueur1().getArgent() << " pièces d'or." << std::endl;
                }

                else if(choixGemmeP1 == 2){
                    Effet& effetAttaque = gemme->UtiliserAttaque();
                    std::cout << "Le joueur 1 utilise l'effet d'attaque de la gemme de feu numéro " << idx << " : " << effetAttaque.toString() << std::endl;
                    plateau.getJoueur1().setDegatsStockes(plateau.getJoueur1().getDegatsStockes() + effetAttaque.getValeur());
                 //   plateau.getJoueur2().setPointDeVie(plateau.getJoueur2().getPointDeVie() - effetAttaque.getValeur());
                  //  std::cout << "Le joueur 2 perd " << effetAttaque.getValeur() << " points de vie, il a maintenant " << plateau.getJoueur2().getPointDeVie() << " points de vie." << std::endl;
                    std::cout << "Le total des dégâts stockés du Joueur 1 est maintenant de " << plateau.getJoueur1().getDegatsStockes() << " dégâts." << std::endl;
                    
                    // Marquer pour suppression après la boucle
                    gemmesASupprimer.push_back(gemme);
                    
                    // Déplacer la gemme de feu vers la zone de sacrifice après utilisation de l'attaque
                    ZoneDeSacrifice zoneDeSacrifice = plateau.getZoneDeSacrifice();
                    zoneDeSacrifice.add(gemme);
                    plateau.setZoneDeSacrifice(zoneDeSacrifice);
                }
                idx++;
            }
            
            // Supprimer les gemmes marquées APRÈS la boucle (CORRECTION: du Joueur 1, pas du Joueur 2)
            if (!gemmesASupprimer.empty()) {
                MainJoueur updatedMainJ1 = plateau.getJoueur1().getMain();
                for (auto* gemme : gemmesASupprimer) {
                    updatedMainJ1.removeCarte(gemme);
                }
                plateau.getJoueur1().setMain(updatedMainJ1);
                std::cout << "-> " << gemmesASupprimer.size() << " gemme(s) sacrifiée(s) et retirée(s) de la main du Joueur 1" << std::endl;
            }
        }

        if (plateau.getJoueur1().getArgent()>2){
            int choixGemmeDeFeuJ1;
            std::cout << "Joueur 1 appuyez sur 1 si vous voulez acheter une gemme de feu." << std::endl;
            std::cin >> choixGemmeDeFeuJ1;

            while (choixGemmeDeFeuJ1 == 1 && plateau.getJoueur1().getArgent() > 2 && plateau.getMarche().getGemmes().size() > 0)
            {
                plateau.getJoueur1().setArgent(plateau.getJoueur1().getArgent() - 3);
                Defausse newDefausseJoueur1 = plateau.getJoueur1().getDefausse();
                newDefausseJoueur1.addCarte(plateau.getMarche().acheterGemme());
                plateau.getJoueur1().setDefausse(newDefausseJoueur1);
                std::cout << "Le Joueur 1 achète une gemme de feu et dépense 3 pièces d'or." << std::endl;
                std::cout << "Il reste " << plateau.getJoueur1().getArgent() << " pièces d'or au Joueur 1." << std::endl;
                std::cout << "Le marché contient maintenant " << plateau.getMarche().getGemmes().size() << " gemmes de feu." << std::endl;
                if (plateau.getJoueur1().getArgent() < 3)
                {
                    std::cout << "Le Joueur 1 n'a plus assez d'argent pour acheter une autre gemme de feu." << std::endl;
                    break;
                }
                
                std::cout << "Joueur 1 appuyez sur 1 si vous voulez acheter une autre gemme de feu." << std::endl;
                std::cin >> choixGemmeDeFeuJ1;
            }
        }
        std::cout << std::string(60, '-') << std::endl;

        std::cout << "Phase d'achat d'action et de champion du Joueur 1" << std::endl;

        // Afficher les actions disponibles à l'achat
        for (size_t i = 0; i < plateau.getMarche().getActionsVendables().size(); ++i) {
            Action* action = plateau.getMarche().getActionsVendables()[i];
            std::cout << "  - " << action->getNom() << " (Prix: " << action->getPrix() << " or)" << std::endl;
        }
        plateau.achatActionChampion(plateau.getJoueur1());

        std::cout << std::string(60, '-') << std::endl;
        std::cout << "Phase d'utilisation des effets des cartes actions et champions du Joueur 1" << std::endl;

        // Utiliser les effets des cartes de la main (Joueur1)
        std::cout << "Phase d'utilisation des effets des cartes actions et champions du Joueur 1" << std::endl;
        auto [effetsBasiqueJ1, effetsTextuelsJ1] = plateau.choixUtilisationEffetJ1();
        plateau.appliquerEffetsJ1(effetsBasiqueJ1, effetsTextuelsJ1);

        // Déplacement propre des cartes de la main vers la défausse (Joueur1)
        Defausse newDefausseJoueur1 = plateau.getJoueur1().getDefausse();
        MainJoueur updatedMainJ1 = plateau.getJoueur1().getMain(); // copie modifiable

        auto cartesMain = updatedMainJ1.getCartes();
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
        j1.setArgent(0);
        j1.setDegatsStockes(0);
        std::cout << "Le solde du Joueur 1 retombe à 0" << std::endl;
        std::cout << "Le total des dégâts stockés du Joueur 1 retombe à 0" << std::endl;

        // Tour du joueur 2
        std::cout << "C'est au Joueur2 de jouer" << std::endl;
        std::cout << "Le joueur 2 a en main " << plateau.getJoueur2().getMain().getCartes().size() << " cartes." << std::endl;
        std::cout << plateau.getJoueur2().getMain().getCartesDeBase().size() << " cartes de base :" << std::endl;
        std::cout << plateau.getJoueur2().getMain().getGemmesDeFeu().size() << " gemmes de feu :" << std::endl;
        
        
        if(!plateau.getJoueur2().getMain().getCartes().empty()) {
            idx = 1;
            std::cout << "La main du joueur 2 est composée des cartes :" << std::endl;
            for (auto* carte : plateau.getJoueur2().getMain().getCartes()) {
                //tant que je ne fais pas carte->toString() ça ne plante pas
                std::cout << "  [" << idx++ << "] " << carte->getNom() << std::endl;
            }
            std::cout << "Joueur 2 appuyez sur 1 si vous voulez utiliser les effets de vos cartes de base." << std::endl;
            choix = 0;
            std::cin >> choix;
            if (choix == 1) {
                int pv1_avant = plateau.getJoueur1().getPointDeVie();
                int pv2_avant = plateau.getJoueur2().getPointDeVie();
                std::cout << "-> Application des effets : PV avant -> Joueur1: " << pv1_avant << " | Joueur2: " << pv2_avant << std::endl;

                plateau.utiliserEffetBasiqueJoueur2(plateau.getJoueur2().getMain().getCartesDeBase());

                //int pv1_apres = plateau.getJoueur1().getPointDeVie();
                int pv2_apres = plateau.getJoueur2().getPointDeVie();
                int argent_apres = plateau.getJoueur2().getArgent();
                int degats_stockes_apres = plateau.getJoueur2().getDegatsStockes();
                std::cout << "-> Résultat : Joueur2 : PV après  -> " << pv2_apres << ", | Argent du Joueur 2: " << argent_apres << ", | Dégâts stockés : " << degats_stockes_apres << std::endl;
                //std::cout << "-> Résultat : PV après  -> Joueur1: " << pv1_apres << " | Joueur2: " << pv2_apres << " | Argent du Joueur 2: " << argent_apres << std::endl;
                std::cout << std::string(60, '-') << std::endl;
            }
            else{
                std::cout << "Joueur 2 n'utilise pas les effets de ces cartes de base cette manche." << std::endl;
                std::cout << std::string(60, '-') << std::endl;
            }
        }

        // Gestion des gemmes de feu pour le Joueur2 (VERSION CORRIGÉE)
        auto gemmesDeFeuJ2 = plateau.getJoueur2().getMain().getGemmesDeFeu();
        if (!gemmesDeFeuJ2.empty())
        {
            std::cout << "La main du joueur 2 est composée de " << gemmesDeFeuJ2.size() << " gemmes de feu :" << std::endl;
            idx = 1;
            
            std::vector<GemmeDeFeu*> gemmesASupprimer;
            
            for (auto* gemme : gemmesDeFeuJ2) {
                std::cout << "Joueur 2 appuyez sur 1 si vous voulez utiliser l'effet d'argent de votre gemme de feu numero " << idx <<  ", appuyez sur 2 si vous voulez utiliser l'effet faisant 3 de degats (la carte sera sacrifiée dans ce cas)." << std::endl;
                int choixGemme;
                std::cin >> choixGemme;

               

                if (choixGemme == 1) {
                    const auto& effets = gemme->getEffetsBasiqueChoix1();
                    for (const auto& effet : effets) {
                        std::cout << "Le joueur 2 utilise l'effet de la gemme de feu numéro " << idx << " : " << effet.toString() << std::endl;
                        plateau.getJoueur2().setArgent(effet.getValeur() + plateau.getJoueur2().getArgent());
                        std::cout << "Le joueur 2 gagne " << effet.getValeur() << " pièces d'or, il a maintenant " << plateau.getJoueur2().getArgent() << " pièces d'or." << std::endl;

                    }
                }

                else if(choixGemme == 2){
                    Effet& effetAttaque = gemme->UtiliserAttaque();
                    std::cout << "Le joueur 2 utilise l'effet d'attaque de la gemme de feu numéro " << idx << " : " << effetAttaque.toString() << std::endl;
                    plateau.getJoueur2().setDegatsStockes(plateau.getJoueur2().getDegatsStockes() + effetAttaque.getValeur());
                    std::cout << "Le total des dégâts stockés du Joueur 2 est maintenant de " << plateau.getJoueur2().getDegatsStockes() << " dégâts." << std::endl;
                    //plateau.getJoueur1().setPointDeVie(plateau.getJoueur1().getPointDeVie() - effetAttaque.getValeur());
                    //std::cout << "Le joueur 1 perd " << effetAttaque.getValeur() << " points de vie, il a maintenant " << plateau.getJoueur1().getPointDeVie() << " points de vie." << std::endl;


                    gemmesASupprimer.push_back(gemme);
                    
                    // Déplacer la gemme de feu vers la zone de sacrifice après utilisation de l'attaque
                    ZoneDeSacrifice zoneDeSacrifice = plateau.getZoneDeSacrifice();
                    zoneDeSacrifice.add(gemme);
                    plateau.setZoneDeSacrifice(zoneDeSacrifice);
                }
                idx++;
            }
            
            if (!gemmesASupprimer.empty()) {
                MainJoueur updatedMainJ2 = plateau.getJoueur2().getMain();
                for (auto* gemme : gemmesASupprimer) {
                    updatedMainJ2.removeCarte(gemme);
                }
                plateau.getJoueur2().setMain(updatedMainJ2);
                std::cout << "-> " << gemmesASupprimer.size() << " gemme(s) sacrifiée(s) et retirée(s) de la main du Joueur 2" << std::endl;
            }
        }
        
        

        std::cout << "Il y a " << plateau.getMarche().getGemmes().size() << " gemmes dans le marché." << std::endl;

        if (plateau.getJoueur2().getArgent()>2){
            int choixGemmeDeFeuJ2;
            std::cout << "Joueur 2 appuyez sur 1 si vous voulez acheter une gemme de feu." << std::endl;
            std::cin >> choixGemmeDeFeuJ2;

            while (choixGemmeDeFeuJ2 == 1 && plateau.getJoueur2().getArgent() > 2 && plateau.getMarche().getGemmes().size() > 0)
            {
                plateau.getJoueur2().setArgent(plateau.getJoueur2().getArgent() - 3);
                Defausse newDefausseJoueur2 = plateau.getJoueur2().getDefausse();
                newDefausseJoueur2.addCarte(plateau.getMarche().acheterGemme());
                plateau.getJoueur2().setDefausse(newDefausseJoueur2);
                std::cout << "Le Joueur 2 achète une gemme de feu et dépense 3 pièces d'or." << std::endl;
                std::cout << "Il reste " << plateau.getJoueur2().getArgent() << " pièces d'or au Joueur 2." << std::endl;
                std::cout << "Le marché contient maintenant " << plateau.getMarche().getGemmes().size() << " gemmes de feu." << std::endl;
                if (plateau.getJoueur2().getArgent() < 3)
                {
                    std::cout << "Le Joueur 2 n'a plus assez d'argent pour acheter une autre gemme de feu." << std::endl;
                    break;
                }

                std::cout << "Joueur 2 appuyez sur 1 si vous voulez acheter une autre gemme de feu." << std::endl;
                std::cin >> choixGemmeDeFeuJ2;
            }
        }

        std::cout << std::string(60, '-') << std::endl;

        std::cout << "Phase d'achat d'action et de champion du Joueur 2" << std::endl;

        // Afficher les actions disponibles à l'achat
        for (size_t i = 0; i < plateau.getMarche().getActionsVendables().size(); ++i) {
            Action* action = plateau.getMarche().getActionsVendables()[i];
            std::cout << "  - " << action->getNom() << " (Prix: " << action->getPrix() << " or)" << std::endl;
        }
        plateau.achatActionChampion(plateau.getJoueur2());

        std::cout << std::string(60, '-') << std::endl;
        std::cout << "Phase d'utilisation des effets des cartes actions et champions du Joueur 2" << std::endl;

        // Utiliser les effets des cartes de la main (Joueur2)
        std::cout << "Phase d'utilisation des effets des cartes actions et champions du Joueur 2" << std::endl;
        auto [effetsBasiqueJ2, effetsTextuelsJ2] = plateau.choixUtilisationEffetJ2();
        plateau.appliquerEffetsJ2(effetsBasiqueJ2, effetsTextuelsJ2);


        

        // Déplacement propre des cartes de la main vers la défausse (Joueur2)
        Defausse newDefausseJoueur2 = plateau.getJoueur2().getDefausse();
        MainJoueur updatedMainJ2 = plateau.getJoueur2().getMain(); // copie modifiable

        auto cartesMain2 = updatedMainJ2.getCartes();
        for (auto* carte : cartesMain2) {
            newDefausseJoueur2.addCarte(carte);
            updatedMainJ2.removeCarte(carte);
        }

        plateau.getJoueur2().setDefausse(newDefausseJoueur2);
        plateau.getJoueur2().setMain(updatedMainJ2);

        /*std::cout << "Affichage de la defausse du joueur 2" << std::endl;
        for (size_t i = 0; i < plateau.getJoueur2().getDefausse().getCartes().size(); i++)
        {
            std::cout << " - " << plateau.getJoueur2().getDefausse().getCartes()[i]->toString() << std::endl;
        }*/
        

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
        j2.setArgent(0);
        j2.setDegatsStockes(0);
        std::cout << "Le total des dégâts stockés du Joueur 2 retombe à 0" << std::endl;
        std::cout << "Le solde du Joueur 2 retombe à 0" << std::endl;

        /*
        std::cout << "Affichage de la pioche du joueur 2" << std::endl;
        for (size_t i = 0; i < plateau.getJoueur2().getPioche().getCartes().size(); i++)
        {
            std::cout << " - " << plateau.getJoueur2().getPioche().getCartes()[i]->toString() << std::endl;
        }
*/
        //plateau.getMarche().MiseAJourActionsVendables();
        


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
                int before = joueur2.getPointDeVie();
                joueur2.setPointDeVie(before - effet.getValeur());
                std::cout << " => -" << effet.getValeur()
                          << " PV à Joueur2 ( " << before << " -> " << joueur2.getPointDeVie() << " )" << std::endl;
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
                int before = joueur1.getPointDeVie();
                joueur1.setPointDeVie(before - effet.getValeur());
                std::cout << " => -" << effet.getValeur()
                          << " PV à Joueur1 ( " << before << " -> " << joueur1.getPointDeVie() << " )" << std::endl;
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
