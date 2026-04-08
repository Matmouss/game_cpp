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
   int quantite;

public:
   Item(string nom = "Item", string type = "HEAL", int valeur = 0, int quantite = 1);

   string getNom();
   string getType();
   int getValeur();
   int getQuantite();

   bool estDisponible();
   bool utiliser(Personnage &p);
   void afficherInfos();
};
