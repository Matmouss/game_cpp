#pragma once
#include <iostream>
#include "item.h"

using namespace std;
class Personnage
{
private:
   string nom;
   int Hp;
   int HpMax;
   int NbTue;
   int NbEpargne;
   int nbVictoire;
   bool EstVivant;
   Item** ItemPossible;
   int TailleItemPossible;
   Item** InventaireItems;
   int TailleInventaire;

public:
   Personnage(string nom,int HpMax);
   Personnage();

   pair<Item **, int> initInventaires();
   int attaquer();
   void utiliserActe();
   bool epargner();
   void prendreDegats(int degats);
   bool estVivant();
   void gagnerCombat();
   void incrementerTue();
   void incrementerEpargne();
   void afficherStats();
};