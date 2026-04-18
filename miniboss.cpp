#include <string>
using std::string;

#include "monstre.h"

#include "miniboss.h"

MiniBoss::MiniBoss(string nom, int hpMax, int atk, int def, int mercyGoal, string description, Act **inventaireACT, int tailleInventaireACT, Stat **stats, int tailleStats, int actPoints,int maxActPoints, string* dialogues, int tailleDialogues): Monstre(nom, hpMax, atk, def, mercyGoal, description, inventaireACT, tailleInventaireACT, stats, tailleStats, actPoints, maxActPoints, dialogues, tailleDialogues) {
    this->type = "mini";
}

MiniBoss::~MiniBoss() = default;