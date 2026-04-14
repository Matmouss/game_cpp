#pragma once
#include <string>
using std::string;

#include "entite.h"

class Item;
class Act;

class Personnage : public Entite
{
private:
    int nbTue;
    int nbEpargne;
    int nbVictoire;

    Item** inventaireItems;
    int tailleInventaire;

public:
   Personnage();

   Personnage(string nom, int hpMax, int atk, int def, int mercyGoal, string description, Act **inventaireACT, int tailleInventaireACT, Item **inventaireItems, int tailleInventaire, Stat **stats, int tailleStats);

   ~Personnage();

   int getNbTue() { return nbTue; }
   int getNbEpargne() { return nbEpargne; }
   int getNbVictoire() { return nbVictoire; }
   Item *getInventaireItems(int i) { return inventaireItems[i]; }
   int getTailleInventaire() { return tailleInventaire; }

   void setNbTue(int valeur) { nbTue = valeur; }
   void setNbEpargne(int valeur) { nbEpargne = valeur; }
   void setNbVictoire(int valeur) { nbVictoire = valeur; }
   bool setInventaireItems(Item *&item, int i);

   void gagnerCombat() { nbVictoire++; }
};