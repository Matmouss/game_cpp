#pragma once
#include <string>
#include "personnage.h"
#include "monstre.h"
using namespace std;

class ACT
{
public:
   string identifiant;
   string texte;

public:
   ACT(string identifiant, string texte);
   virtual ~ACT();
   string getTexte();
   string getIdentifiant();
   virtual string Impact(Personnage &p, Monstre &m);
};

class SerrerMain : public ACT {
public:
    SerrerMain();

    string Impact(Personnage& p, Monstre& m) override;
};

class Dodo : public ACT {
public:
    Dodo();

   string Impact(Personnage& p, Monstre& m) override;
};