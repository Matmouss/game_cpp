#include <string>
using std::string;

#include "boss.h"

Boss::Boss(string nom, int hpMax, int atk, int def, int mercyGoal, string description)
    : Monstre(nom, hpMax, atk, def, mercyGoal, description)
{
   this->nbActions = 4;
}

int Boss::getNbActions() { return nbActions; }