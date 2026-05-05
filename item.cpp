#include <string>
using std::string;

#include "item.h"
#include "stat.h"
#include "personnage.h"

Item::Item()
{
   this->nom = "Item";
   this->type = "None";
   this->texte = "None";
   this->valeur = 0;
}

Item::Item(string nom, string type, string texte, int valeur)
{
   this->nom = nom;
   this->type = type; //peut être ajouter une verfication si la stat existe dès le début ??
   this->texte = texte;
   this->valeur = valeur;
}

string Item::getNom() { return nom; }
string Item::getType() { return type; }
string Item::getTexte() { return texte; }
int Item::getValeur() { return valeur; }

string Item::utiliser(Personnage &p) {
   //mapping de toutes les stats avec tout les types
   string erreur = "";
   if (type == "HP"){
      p.soigner(valeur);
   } 
   else if (type == "Vulnerabilite"){
      int somme = p.getStatValue("Vulnerabilite") + valeur;
      p.setStatValue("Vulnerabilite", somme);
   } else if (type == "Force"){
      int somme = p.getStatValue("Force") + valeur;
      p.setStatValue("Force", somme);
   } 
   else {
      erreur = " --> Type d'item non reconnu: " + type;
   }
   return texte + erreur;
}
