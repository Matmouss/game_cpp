#pragma once
#include <string>
using std::string;

class Entite;

class Act
{
public:
   static const int nbActionsPossibles = 3;
   static Act **getActionsPossibles();
   static void DestructActionPossibles();
   string identifiant;
   string texte;
   int actPointsCost;

public:
   Act();
   Act(string identifiant, string texte,int actPointCost);
   virtual ~Act();
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

class Attaquer : public Act {
   public:
   Attaquer();

   string Impact(Entite &entite, Entite &entiteCible) override;
};