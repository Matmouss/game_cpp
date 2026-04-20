#include <string>
using std::string;

#include "monstre.h"

class Stat;

Monstre::Monstre(): Entite(){
    resultatCombat = "";
    dialogues = nullptr;
    tailleDialogues = 0;
}

Monstre::Monstre(const Monstre &monstre): Entite(monstre){
    resultatCombat = "";
    dialogues = monstre.dialogues;
    tailleDialogues = monstre.tailleDialogues;
}

Monstre::Monstre(string nom, int hpMax, int atk, int def, int mercyGoal, string description, Act **inventaireACT, int tailleInventaireACT, Stat **stats, int tailleStats, int actPoints, int maxActPoints, string* dialogues, int tailleDialogues)
    : Entite(nom, hpMax, atk, def, mercyGoal, description, inventaireACT, tailleInventaireACT, stats, tailleStats, actPoints, maxActPoints)
{
    this->dialogues = dialogues;
    this->tailleDialogues = tailleDialogues;
    resultatCombat = "";
}

Monstre::~Monstre() = default;

string Monstre::getResultatCombat() { return resultatCombat; }

void Monstre::setResultatCombat(string resultat) { this->resultatCombat = resultat; }
