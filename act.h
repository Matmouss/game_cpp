#pragma once
#include <string>
#include "personnage.h"
#include "monstre.h"
#include "entite.h"

using namespace std;

class Entite;

class ACT
{
public:
   static const int nbActionsPossibles = 2;
    static ACT** actionsPossibles;

   string identifiant;
   string texte;

public:
   ACT(string identifiant, string texte);
   virtual ~ACT();
   string getTexte();
   string getIdentifiant();
   virtual string Impact(Entite& entite, Entite& entiteCible);
};

class SerrerMain : public ACT {
public:
    SerrerMain();

    string Impact(Entite& entite, Entite& entiteCible) override;
};

class Dodo : public ACT {
public:
    Dodo();

   string Impact(Entite& entite, Entite& entiteCible) override;
};