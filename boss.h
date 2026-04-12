#pragma once
#include <string>
using std::string;
#include "monstre.h"

class Boss : public Monstre
{
private:
   int nbActions = 4;

public:
   Boss(string nom = "Boss", int hpMax = 80, int atk = 15, int def = 4, int mercyGoal = 100,string description = "Boss");

   int getNbActions();
};