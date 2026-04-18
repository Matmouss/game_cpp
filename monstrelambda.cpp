#include <string>
using std::string;

#include "monstre.h"
#include "monstrelambda.h"

MonstreLambda::MonstreLambda(string nom, int hpMax, int atk, int def, int mercyGoal, string description, Act **inventaireACT, int tailleInventaireACT, Stat **stats, int tailleStats, int actPoints,int maxActPoints) 
:Monstre(nom, hpMax, atk, def, mercyGoal, description, inventaireACT, tailleInventaireACT, stats, tailleStats, actPoints, maxActPoints) {
    this->type = "lambda";
}

MonstreLambda::~MonstreLambda() = default;