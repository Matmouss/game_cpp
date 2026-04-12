#include <string>
#include <utility>
#include <vector>
using std::pair;
using std::string;
using std::vector;

#include <fstream>
#include <sstream>
#include <random>

#include "partie.h"
#include "MonstreLambda.h"
#include "miniBoss.h"
#include "boss.h"
#include "monstre.h"
#include "csv.h"
#include "act.h"
#include "personnage.h"
#include "item.h"
#include "entite.h"

pair<Act**,int> initInventaireACT(string actions_str) {
    size_t pos = 0;
    size_t start = 0;
    vector<int> actions_int;

    while ((pos = actions_str.find(";", start)) != string::npos) {
        actions_int.push_back(stoi(actions_str.substr(start, pos - start)));
        start = pos + 1;
    }

    int taille = static_cast<int>(actions_int.size());

    Act** actions = new Act*[taille];
    
    for (int i = 0; i < taille; i++) {
        actions[i] = Act::actionsPossibles[actions_int[i]];
    }

    return {actions, taille};
}

pair<Monstre**, int> initMonstresPossibles() {
    auto monstres = readCSV("data/monstres.csv");

    int nbMonstres = static_cast<int>(monstres.size()) - 1;
    Monstre** bestiaire = new Monstre*[nbMonstres];

    for (int i = 1; i < static_cast<int>(monstres.size()); i++) {
        pair<Act**, int> actions = initInventaireACT(monstres[i][7]);
        bestiaire[i - 1] = new Monstre(
            string(monstres[i][1]),
            stoi(monstres[i][2]),
            stoi(monstres[i][3]),
            stoi(monstres[i][4]),
            stoi(monstres[i][5]),
            string(monstres[i][6]),
            actions.first,
            actions.second
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
   this->bestiaire[0] = this->monstresPossibles[0];
   
   this->tailleCatalogueACT = Act::nbActionsPossibles;
   this->catalogueACT = Act::actionsPossibles;
   
   pair<Item **, int> result2 = initInventaires();
   this->itemPossible = result2.first;
   this->tailleItemPossible = result2.second;

   this->personnage = Personnage("Personnage", 100, 10, 10, 10, "le héros", new Act*[4](), 4, new Item*[2](), 2);

   //par défaut commencer avec ces deux objects
   this->personnage.setInventaireItems(this->itemPossible[0], 0);
   this->personnage.setInventaireItems(this->itemPossible[1], 1);

    this->personnage.setAction(this->catalogueACT[1],0);
    this->personnage.setAction(this->catalogueACT[0],1);
    this->personnage.setAction(this->catalogueACT[0],2);
    this->personnage.setAction(this->catalogueACT[0],3);
}

Partie::~Partie()
{
    for (int i = 0; i < tailleMonstresPossibles ; i++)
        delete monstresPossibles[i];
    delete [] monstresPossibles;

    delete [] bestiaire;

    // for (int i = 0; i < tailleCatalogueACT; i++)
    //     delete catalogueACT[i];
    // delete[] catalogueACT;
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