#pragma once
#include "monstreLambda.h"
using namespace std;

MonstreLambda::MonstreLambda(string nom, int hpMax, int atk, int def, int mercyGoal, int* idsActions)
    : Monstre(nom, hpMax, atk, def, mercyGoal, idsActions)
{

}

int MonstreLambda::getNbActions()
{
   return NB_ACTIONS;
}
