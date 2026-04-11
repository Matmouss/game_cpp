#include "partie.h"
#include "MonstreLambda.h"
#include "miniBoss.h"
#include "boss.h"
#include "csv.h"
#include "act.h"
#include "personnage.h"
#include "item.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
using namespace std;

pair<Monstre**, int> initMonstresPossibles() {
    auto monstres = readCSV("data/monstres.csv");

    int nbMonstres = static_cast<int>(monstres.size()) - 1;
    Monstre** bestiaire = new Monstre*[nbMonstres];

    for (int i = 1; i < static_cast<int>(monstres.size()); i++) {
        bestiaire[i - 1] = new Monstre(
            string(monstres[i][1]),
            stoi(monstres[i][2]),
            stoi(monstres[i][3]),
            stoi(monstres[i][4]),
            stoi(monstres[i][5]),
            string(monstres[i][6])
        );
    }

    return {bestiaire, nbMonstres};
}


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


Partie::Partie()
{
   pair<Monstre**, int> result = initMonstresPossibles();
   this->monstresPossibles = result.first;
   this->tailleMonstresPossibles = result.second;
   this->tailleBestiaire = 1;
   this->bestiaire = new Monstre*[this->tailleBestiaire];
   this->personnage = Personnage();
   this->tailleCatalogueACT = 1;
   this->catalogueACT = new ACT*[tailleCatalogueACT];
   this->catalogueACT[0] = new Dodo();
   this->catalogueACT[1] = new SerrerMain();

   this->bestiaire[0] = this->monstresPossibles[0];

   pair<Item **, int> result2 = initInventaires();
   this->itemPossible = result2.first;
   this->tailleItemPossible = result2.second;

   //par défaut commencer avec ces deux objects
   this->personnage.inventaireItems[0] = this->itemPossible[0];
   this->personnage.inventaireItems[1] = this->itemPossible[1];

   this->personnage.inventaireACT[1] = this->catalogueACT[0];
   this->personnage.inventaireACT[2] = this->catalogueACT[0];
   this->personnage.inventaireACT[3] = this->catalogueACT[0];
   this->personnage.inventaireACT[0] = this->catalogueACT[1];
}

Partie::~Partie()
{
    for (int i = 0; i < tailleMonstresPossibles ; i++)
        delete monstresPossibles[i];
    delete monstresPossibles;

    delete bestiaire;

    for (int i = 0; i < tailleCatalogueACT; i++)
        delete catalogueACT[i];
    delete[] catalogueACT;
}

void Partie::ajouterBestiaire(Monstre* monstre){
   this->tailleBestiaire += 1;
   Monstre** tmpBestiaire = new Monstre*[this->tailleBestiaire];
   for(int i = 0; i < this->tailleBestiaire - 1; i++){
      tmpBestiaire[i] = this->bestiaire[i];
   }
   tmpBestiaire[this->tailleBestiaire - 1] = monstre;
   delete[] this->bestiaire;
   this->bestiaire = tmpBestiaire;
}