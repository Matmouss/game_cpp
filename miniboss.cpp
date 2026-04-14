#include "miniboss.h"
#include <string>
using std::string;

using namespace std;

MiniBoss::MiniBoss(string nom, int hpMax, int atk, int def, int mercyGoal,string description)
    : Monstre(nom, hpMax, atk, def, mercyGoal,description)
{
   this->nbActions = 3;
}

int MiniBoss::getNbActions() { return nbActions; }