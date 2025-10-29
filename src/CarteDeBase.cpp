#include "CarteDeBase.h"
#include "GemmeDeFeu.h"

// Définition out-of-line du destructeur virtuel pour émettre la vtable

/*Gemme de Feu (16)
Or (28, 7 par joueur)
Épée Courte (4, 1 par joueur)
Dague (4, 1 par joueur)
Rubis (4, 1 par joueur)*/

CarteDeBase or("Or", { Effet(1, OR) });
CarteDeBase epeeCourte("Épée Courte", { Effet(2, DEGAT) });
CarteDeBase dague("Dague", { Effet(1, DEGAT) });
CarteDeBase rubis("Rubis", { Effet(2, OR) });