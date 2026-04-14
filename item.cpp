#include <string>
using std::string;

#include "item.h"

Item::Item()
{
   this->nom = "Item";
   this->type = "HEAL";
   this->valeur = 0;
}

Item::Item(string nom, string type, int valeur)
{
   this->nom = nom;
   this->type = type;
   this->valeur = valeur;
}

string Item::getNom() { return nom; }
string Item::getType() { return type; }
int Item::getValeur() { return valeur; }

