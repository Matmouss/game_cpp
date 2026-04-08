#include "monstre.h"
#include <iostream>

using namespace std;

Monstre::Monstre(string nom, int hpMax, int atk, int def, int mercyGoal)
{
   //commentaire
   this->nom = nom;
   this->hp = hpMax;
   this->hpMax = hpMax;
   this->atk = atk;
   this->def = def;
   this->mercy = 0;
   this->mercyGoal = mercyGoal;
   this->resultatCombat = "";
   this->actionsDisponibles = nullptr;
   this->nbActionsDisponibles = 0;
}

Monstre::~Monstre()
{
   delete[] actionsDisponibles;
}

string Monstre::getNom() { return nom; }
int Monstre::getHp() { return hp; }
int Monstre::getHpMax() { return hpMax; }
int Monstre::getAtk() { return atk; }
int Monstre::getDef() { return def; }
int Monstre::getMercy() { return mercy; }
int Monstre::getMercyGoal() { return mercyGoal; }
string Monstre::getResultatCombat() { return resultatCombat; }
string *Monstre::getActionsDisponibles() { return actionsDisponibles; }
int Monstre::getNbActionsDisponibles() { return nbActionsDisponibles; }

void Monstre::setResultatCombat(string resultat) { this->resultatCombat = resultat; }
void Monstre::setActionsDisponibles(string *actions, int nb)
{
   delete[] actionsDisponibles;
   this->nbActionsDisponibles = nb;
   this->actionsDisponibles = new string[nb];
   for (int i = 0; i < nb; i++)
      this->actionsDisponibles[i] = actions[i];
}