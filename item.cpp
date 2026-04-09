#include "item.h"
#include "personnage.h"

using namespace std;

Item::Item(string nom, string type, int valeur)
{
   this->nom = nom;
   this->type = type;
   this->valeur = valeur;
}

string Item::getNom() { return nom; }
string Item::getType() { return type; }
int Item::getValeur() { return valeur; }