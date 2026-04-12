#pragma once
#include <string>
using std::string;

#include "monstre.h"


class MiniBoss : public Monstre
{
private:
   int nbActions = 3;

public:
   MiniBoss(string nom = "MiniBoss", int hpMax = 45, int atk = 10, int def = 2, int mercyGoal = 100,string description = "MiniBoss");

   int getNbActions();
};