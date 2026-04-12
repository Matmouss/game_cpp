#include "monstre.h"
#include "personnage.h"
#include <iostream>

using namespace std;


string Monstre::getResultatCombat() { return resultatCombat; }

void Monstre::setResultatCombat(string resultat) { this->resultatCombat = resultat; }
