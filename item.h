#pragma once
#include <iostream>

using namespace std;

class Personnage;

class    Item
{
private:
   string nom;
   string type;
   int valeur;

public:
   Item(string nom = "Item", string type = "HEAL", int valeur = 0);

   string getNom();
   string getType();
   int getValeur();

   bool estDisponible();
   bool utiliser(Personnage &p);
   void afficherInfos();
};
