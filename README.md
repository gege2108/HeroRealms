# Hero Realms (C++)

Hero Realms est une adaptation console du jeu de deckbuilding Hero Realms, développée en C++ avec une architecture orientée objet.

## Sommaire
- [Description](#description)
- [Fonctionnalités](#fonctionnalités)
- [Structure du projet](#structure-du-projet)
- [Installation](#installation)
- [Utilisation](#utilisation)
- [Tests](#tests)
- [Contribuer](#contribuer)
- [Auteurs](#auteurs)
- [Licence](#licence)

---

## Description

Ce projet propose une version numérique du jeu de cartes Hero Realms. Deux joueurs s'affrontent en construisant leur deck, achetant des cartes au marché, et utilisant des champions et des actions pour vaincre l'adversaire.

Le jeu met en avant :
- Une structure orientée objet (Joueur, Carte, Champion, Action, Marché, Plateau, etc.)
- Une interface console interactive
- Un système d'effets et de combos fidèle au jeu original

---

## Fonctionnalités

- Gestion complète du tour de jeu (pioche, main, défausse, achats, utilisation des cartes)
- Système de marché dynamique
- Effets textuels et basiques sur les cartes
- Champions avec compétences et mode défense
- Combos de factions
- Mode "Godmode" 
- Mélange des decks et défausses

---

## Structure du projet

- `src/` : Code source principal
- `include/` : Fichiers d'en-tête
- `main.cpp` : Point d'entrée du jeu
- `README.md` : Ce fichier
- `Makefile` : Compilation

---

## Installation

### Prérequis

- C++17 ou plus
- Make

### Compilation

```bash
make clean   # Supprime les fichiers objets (.o) et l'exécutable existant
make        # Compile le projet (g++ compile tous les fichiers sources)
make run    # Exécute le binaire HeroRealms (équivalent à ./HeroRealms)
```

---

## Utilisation

Lancez le jeu depuis la console :

```bash
./HeroRealms
```

Suivez les instructions à l'écran pour jouer, acheter des cartes, utiliser vos champions et tenter de vaincre votre adversaire.

---

## Tests

Des tests unitaires peuvent être ajoutés dans le dossier `tests/` (non inclus par défaut).

---


---

## Licence

Ce projet est sous licence MIT.


