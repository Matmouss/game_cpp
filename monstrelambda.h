#pragma once
#include <string>
using std::string;

#include "monstre.h"

class MonstreLambda : public Monstre
{
private:
   int nbActions = 2;

public:
   MonstreLambda(string nom = "Monstre", int hpMax = 10, int atk = 5, int def = 1, int mercyGoal = 100, string description = "MonstreLambda");
   int getNbActions() ;
};