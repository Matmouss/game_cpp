#pragma once
#include <string>
using namespace std;

class Monstre;

class ACT
{
private:
   string identifiant;
   string texte;
   int impact;

public:
   ACT(string identifiant, string texte, int impact);

   void executer(Monstre &m);
   string afficherTexte();
   string getIdentifiant();
   int getImpact();
};
