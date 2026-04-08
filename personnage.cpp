#pragma once
#include "personnage.h"
#include <iostream>

Personnage::Personnage(string nom = "Taieb", int Hp = 10, int HpMax = 10, int NbTue = 0, int NbEpargne = 0, int nbVictoire = 0)
{
   this->nom = nom;
   this->Hp = Hp;
   this->HpMax = HpMax;
   this->NbTue = NbTue;
   this->NbEpargne = NbEpargne;
   this->nbVictoire = nbVictoire;
};
bool Personnage::estVivant() {
   cout << "il est vivant!!" << endl;
   return true;}