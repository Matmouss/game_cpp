#include "miniboss.h"
#include <iostream>

using namespace std;

MiniBoss::MiniBoss(string nom, int hpMax, int atk, int def, int mercyGoal)
    : Monstre(nom, hpMax, atk, def, mercyGoal)
{
   this->nbActions = 3;
}

int MiniBoss::getNbActions() { return nbActions; }