#include "CarteDeBase.h"

// Définition out-of-line du destructeur virtuel pour émettre la vtable
CarteDeBase::~CarteDeBase() = default;

// Implémentation de la méthode virtuelle conforme à la signature de la base
Competence CarteDeBase::utiliserEffet() {
    // placeholder: retourne une compétence neutre
    return Competence(0);
}