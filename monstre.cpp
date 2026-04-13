#include <string>
using std::string;

#include "monstre.h"

Monstre::Monstre(): Entite(){
    resultatCombat = "";
}

Monstre::Monstre(const Monstre &monstre): Entite(monstre){
    resultatCombat = "";
}

Monstre::Monstre(string nom, int hpMax, int atk, int def, int mercyGoal, string description, Act** inventaireACT, int tailleInventaireACT)
    : Entite(nom, hpMax, atk, def, mercyGoal, description, inventaireACT, tailleInventaireACT)
{
    resultatCombat = "";
}

Monstre::~Monstre() {}

string Monstre::getResultatCombat() { return resultatCombat; }

void Monstre::setResultatCombat(string resultat) { this->resultatCombat = resultat; }
