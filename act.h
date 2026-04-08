#pragma once
#include <string>
#include "personnage.h"
#include "monstre.h"
using namespace std;

class Monstre;

class ACT
{
private:
   string identifiant;
   string texte;

public:
   ACT(string identifiant, string texte);
   ~ACT();
   string getTexte();
   string getIdentifiant();
   virtual void Impact(Personnage &p, Monstre &m);
};

class SerrerMain : public ACT {
public:
    SerrerMain();

    void Impact(Personnage& p, Monstre& m) override;
};
