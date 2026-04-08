#include "boss.h"
#include <iostream>

using namespace std;

Boss::Boss(string nom, int hpMax, int atk, int def, int mercyGoal)
    : Monstre(nom, hpMax, atk, def, mercyGoal)
{
   this->nbActions = 4;
}

int Boss::getNbActions() { return nbActions; }