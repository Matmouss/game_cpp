#include "personnage.h"
#include <iostream>
#include "item.h"
#include "monstre.h"
#include "csv.h"

pair<Item **, int> initInventaires()
{
   auto inventaire = readCSV("data/items.csv");

   int nbItem = static_cast<int>(inventaire.size()) - 1;
   Item **Inventaire = new Item *[nbItem];

   for (int i = 1; i < static_cast<int>(inventaire.size()); i++)
   {
      Inventaire[i - 1] = new Item(
          string(inventaire[i][0]),
          string(inventaire[i][1]),
          stoi(inventaire[i][2])
         );
   }

   return {Inventaire, nbItem};
}

Personnage::Personnage(string nom = "Taieb", int HpMax = 10)
{
   this->nom = nom;
   this->HpMax = HpMax;
   this->Hp = this->HpMax;
   this->NbTue = NbTue;
   this->NbEpargne = NbEpargne;
   this->nbVictoire = nbVictoire;
   pair<Item **, int> result = initInventaires();
   this->ItemPossible = result.first;
   this->TailleItemPossible = result.second;
   
   this->InventaireItems = new Item*[TailleInventaire];
};

Personnage::Personnage()
{
   this->nom = "Taieb_Default";
   this->Hp = 0;
   this->HpMax = 10;
   this->NbTue = 0;
   this->NbEpargne = 0;
   this->nbVictoire = 0;
   pair<Item **, int> result = initInventaires();
   this->ItemPossible = result.first;
   this->TailleItemPossible = result.second;
   this->TailleInventaire = 2;
   this->InventaireItems = new Item*[TailleInventaire];

   //par défaut commencer avec ces deux objects
   this->InventaireItems[0] = this->ItemPossible[0];
   this->InventaireItems[1] = this->ItemPossible[1];
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