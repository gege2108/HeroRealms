#include "Effet.h"

Effet::Effet() : competence(), type(DEGAT) {}

Effet::Effet(const Competence& competence, TypeEffet type) : competence(competence), type(type) {}

Competence Effet::getCompetence() const { return competence; }
void Effet::setCompetence(const Competence& c) { competence = c; }

TypeEffet Effet::getType() const { return type; }
void Effet::setType(TypeEffet t) { type = t; }