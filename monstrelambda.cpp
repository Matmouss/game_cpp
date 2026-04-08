#pragma once
#include "monstrelambda.h"
#include <iostream>

using namespace std;

MonstreLambda::MonstreLambda(string nom, int hpMax, int atk, int def, int mercyGoal)
    : Monstre(nom, hpMax, atk, def, mercyGoal)
{
   this->nbActions = 2;
}

int MonstreLambda::getNbActions() { return nbActions; }