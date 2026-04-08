#pragma once
#include "monstre.h"

using namespace std;

class Boss : public Monstre
{
private:
   int nbActions = 4;

public:
   Boss(string nom = "Boss", int hpMax = 80, int atk = 15, int def = 4, int mercyGoal = 100);

   int getNbActions();
};