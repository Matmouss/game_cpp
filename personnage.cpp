#include "personnage.h"
#include <iostream>
#include "item.h"
#include "monstre.h"
#include "csv.h"
#include "act.h"

// Personnage::Personnage(string nom = "Taieb", int HpMax = 10)
// {
// };

Personnage::Personnage()
{
   this->nom = "Taieb";
   this->HpMax = 10;
   this->Hp = HpMax;
   this->NbTue = 0;
   this->NbEpargne = 0;
   this->nbVictoire = 0;
   this->tailleInventaire = 2;
   this->inventaireItems = new Item*[tailleInventaire];
   this->tailleInventaireACT = 4;
   this->inventaireACT = new ACT*[tailleInventaireACT];
};

bool Personnage::estVivant() {
   if (this->Hp <= 0) {
      return false;
   }
   return true;}

void Personnage::prendreDegats(int degats) {
   this->Hp -= degats;
}

string Personnage::attaquer(Monstre &Monstre){
   return Monstre.prendreDegats(5);
}

int Personnage::getHp() {
   return this->Hp;
}