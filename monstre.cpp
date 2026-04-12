#include <string>
using std::string;

#include "monstre.h"

string Monstre::getResultatCombat() { return resultatCombat; }

void Monstre::setResultatCombat(string resultat) { this->resultatCombat = resultat; }
