#pragma once
#include <string>
using std::string;

class Personnage;

class Item
{
private:
   string nom;
   string type;
   string texte;
   int valeur;

public:
   Item();
   Item(string nom = "Item", string type = "None", string texte = "None" , int valeur = 0);

   string getNom();
   string getType();
   string getTexte();
   int getValeur();

   string utiliser(Personnage &p);
};
