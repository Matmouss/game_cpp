#pragma once
#include <string>
using std::string;

#include "monstrelambda.h"

MonstreLambda::MonstreLambda(string nom, int hpMax, int atk, int def, int mercyGoal, string description)
    : Monstre(nom, hpMax, atk, def, mercyGoal,description)
{
   this->nbActions = 2;
}

int MonstreLambda::getNbActions() { return nbActions; }