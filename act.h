#pragma once
#include <string>
using std::string;

class Entite;

class Act
{
public:
   static const int nbActionsPossibles = 2;
   static Act **getActionsPossibles();

   string identifiant;
   string texte;

public:
   Act();
   Act(string identifiant, string texte);
   ~Act();
   string getTexte();
   string getIdentifiant();
   virtual string Impact(Entite& entite, Entite& entiteCible);
};

class SerrerMain : public Act {
public:
    SerrerMain();

    string Impact(Entite& entite, Entite& entiteCible) override;
};

class Dodo : public Act {
public:
    Dodo();

   string Impact(Entite& entite, Entite& entiteCible) override;
};