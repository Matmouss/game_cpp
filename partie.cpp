#include <string>
#include <utility>
#include <vector>
using std::pair;
using std::string;
using std::vector;
using std::to_string;

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
        actions[i] = Act::getActionsPossibles()[actions_int[i]];
    }

    return {actions, taille};
}

pair<Monstre**, int> initMonstresPossibles() {
    auto monstres = readCSV("data/monstres.csv");

    int nbMonstres = static_cast<int>(monstres.size()) - 1;
    Monstre** bestiaire = new Monstre*[nbMonstres]();
    int actPts;
    
    for (int i = 1; i < static_cast<int>(monstres.size()); i++) {
        pair<Act**, int> actions = initInventaireACT(monstres[i][8]);
        string type = monstres[i][2];
        actPts = stoi(monstres[i][9]);

        if (type == "lambda") {
            bestiaire[i - 1] = new MonstreLambda(
            string(monstres[i][1]),
            stoi(monstres[i][3]),
            stoi(monstres[i][4]),
            stoi(monstres[i][5]),
            stoi(monstres[i][6]),
            string(monstres[i][7]),
            actions.first,
            actions.second,
            nullptr,
            0,
            actPts,
            actPts);
        }
        if (type == "mini") {
            bestiaire[i - 1] = new MiniBoss(
            string(monstres[i][1]),
            stoi(monstres[i][3]),
            stoi(monstres[i][4]),
            stoi(monstres[i][5]),
            stoi(monstres[i][6]),
            string(monstres[i][7]),
            actions.first,
            actions.second,
            nullptr,
            0,
            actPts,
            actPts);
        }
        if (type == "boss") {
            bestiaire[i - 1] = new Boss(
            string(monstres[i][1]),
            stoi(monstres[i][3]),
            stoi(monstres[i][4]),
            stoi(monstres[i][5]),
            stoi(monstres[i][6]),
            string(monstres[i][7]),
            actions.first,
            actions.second,
            nullptr,
            0,
            actPts,
            actPts);
        }
        
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
          inventaire[i][3],
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

   this->tailleBestiaire = 0;
   this->bestiaire = new Monstre*[this->tailleBestiaire]();
   
   this->tailleCatalogueACT = Act::nbActionsPossibles;
   this->catalogueACT = Act::getActionsPossibles();
   
   pair<Item **, int> result2 = initInventaires();
   this->itemPossible = result2.first;
   this->tailleItemPossible = result2.second;

   int tailleInventaireACT = 4;
   Act** inventaireACT = new Act*[tailleInventaireACT]();
   int tailleInventaireItems = 5;
   Item** inventaireItems = new Item*[tailleInventaireItems]();

   int tailleStats = 0;
   Stat** stats = nullptr;
   int maxActPoints = 3;
   int actPoints = maxActPoints;


   this->personnage = new Personnage("Personnage", 100, 10, 10, 10, "le héros", inventaireACT, tailleInventaireACT, inventaireItems, tailleInventaireItems,stats,tailleStats,actPoints,maxActPoints);

   //par défaut commencer avec ces deux objects
    this->personnage->ajouterItem(this->itemPossible[0]);
    this->personnage->ajouterItem(this->itemPossible[3]);

    this->personnage->setAction(this->catalogueACT[0],0);
    this->personnage->setAction(this->catalogueACT[2],1);
    this->personnage->setAction(this->catalogueACT[1],2);
    this->personnage->setAction(this->catalogueACT[1],3);
}

Partie::~Partie()
{
    for (int i = 0; i < tailleMonstresPossibles ; i++)
        delete monstresPossibles[i];
    delete [] monstresPossibles;

    delete [] bestiaire;

    delete [] itemPossible;

    delete personnage;

    Act::DestructActionPossibles();
}

void Partie::ajouterBestiaire(Monstre* &monstre){
   this->tailleBestiaire += 1;
   Monstre** tmpBestiaire = new Monstre*[this->tailleBestiaire]();
   for(int i = 0; i < this->tailleBestiaire - 1; i++){
      tmpBestiaire[i] = this->bestiaire[i];
   }
   tmpBestiaire[this->tailleBestiaire - 1] = monstre;

   delete[] this->bestiaire;
   this->bestiaire = tmpBestiaire;
}

Monstre* Partie::randomMonstre(string type){
    int index = rand() % this->tailleMonstresPossibles;
    bool trouve = false;
    Monstre* monstre;

    while (!trouve){
        monstre = this->monstresPossibles[index%this->tailleMonstresPossibles];
        if (monstre->getType() == type){
            trouve = true;
        } else {
            index += 1;
        }
    }

    return monstre;



}