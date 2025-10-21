#include <iostream>
#include "CarteDeBase.h"
#include "Effet.h"
#include "Pioche.h"
#include "MainJoueur.h"
/*
void runTests() {
    // Carte sur la pile (stack) - objet local
    CarteDeBase cb("TestCard");
    cb.getEffetsBasiqueChoix1().push_back(Effet(5, OR));
    cb.getEffetsBasiqueChoix1().push_back(Effet(3, DEGAT));
    std::cout << "Carte locale: " << cb.toString() << std::endl;

    // Carte allouée dynamiquement pour tester Pioche/Main
    CarteDeBase* heapCard = new CarteDeBase("HeapCard");
    heapCard->getEffetsBasiqueChoix1().push_back(Effet(2, ATTAQUE));

    // Création de plusieurs cartes supplémentaires
    CarteDeBase* heapCard2 = new CarteDeBase("HeapCard2");
    heapCard2->getEffetsBasiqueChoix1().push_back(Effet(1, OR));

    CarteDeBase* heapCard3 = new CarteDeBase("HeapCard3");
    heapCard3->getEffetsBasiqueChoix1().push_back(Effet(4, DEGAT));

    CarteDeBase* heapCard4 = new CarteDeBase("HeapCard4");
    heapCard4->getEffetsBasiqueChoix1().push_back(Effet(6, ATTAQUE));

    Pioche p;
    p.addCarte(heapCard);
    p.addCarte(heapCard2);
    p.addCarte(heapCard3);
    p.addCarte(heapCard4);

    std::cout << "Pioche size après addCarte: " << p.getCartes().size() << std::endl;

    MainJoueur m;
    m.addCarte(heapCard);
    std::cout << "MainJoueur size après addCarte: " << m.getCartes().size() << std::endl;

    bool drawn = p.tirerCarte(heapCard);
    std::cout << "Draw depuis la pioche réussi: " << (drawn ? "oui" : "non")
              << ", taille pioche: " << p.getCartes().size() << std::endl;

    bool removed = m.removeCarte(heapCard);
    std::cout << "Retiré de la main: " << (removed ? "oui" : "non")
              << ", taille main: " << m.getCartes().size() << std::endl;

    // Retirer et supprimer proprement les cartes restantes ajoutées pour le test
    CarteDeBase* extras[] = {heapCard2, heapCard3, heapCard4};
    for (CarteDeBase* ptr : extras) {
        // tenter de retirer de la pioche si présent
        if (p.tirerCarte(ptr)) {
            std::cout << "Retiré de la pioche: " << ptr->getNom() << std::endl;
        }
        // tenter de retirer de la main au cas où
        if (m.removeCarte(ptr)) {
            std::cout << "Retiré de la main: " << ptr->getNom() << std::endl;
        }
        delete ptr;
    }

    delete heapCard;
}
*/