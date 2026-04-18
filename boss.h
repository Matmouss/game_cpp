#pragma once
#include <string>
using std::string;

#include "monstre.h"

class Boss : public Monstre
{
public:
   Boss(string nom, int hpMax, int atk, int def, int mercyGoal, string description, Act **inventaireACT, int tailleInventaireACT, Stat **stats, int tailleStats, int actPoints,int maxActPoints, string* dialogues, int tailleDialogues);
   ~Boss();
};