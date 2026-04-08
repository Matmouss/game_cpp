#include "partie.h"
#include "MonstreLambda.h"
#include "miniBoss.h"
#include "boss.h"
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
            stoi(monstres[i][5])
        );
    }

    return {bestiaire, nbMonstres};
}

Partie::Partie()
{
   pair<Monstre**, int> result = this->initMonstresPossibles();
   this->monstresPossibles = result.first;
   this->tailleMonstresPossibles = result.second;
   this->tailleBestiaire = 0;
   this->bestiaire = new Monstre*[this->tailleBestiaire];
   this->personnage = Personnage();
   this->catalogueACT = new ACT[1]{SerrerMain()};
}


Partie::~Partie()
{
   for (Monstre *m : ennemisPossibles)
      delete m;
}