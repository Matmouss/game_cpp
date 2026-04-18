#include <string>
using std::string;

#include "monstre.h"

#include "Boss.h"

Boss::Boss(string nom, int hpMax, int atk, int def, int mercyGoal, string description, Act **inventaireACT, int tailleInventaireACT, Stat **stats, int tailleStats, int actPoints,int maxActPoints): Monstre(nom, hpMax, atk, def, mercyGoal, description, inventaireACT, tailleInventaireACT, stats, tailleStats, actPoints, maxActPoints) {
    this->type = "boss";
}
Boss::~Boss() =default;
