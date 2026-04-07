

#include <iostream>
#include <memory>
using namespace std;

class ACT
{

private:
   string identifiant;
   string texte;
   int impact;

public:
   ACT(string identifiant, string texte, int impact)
   {
      this->identifiant = identifiant;
      this->texte = texte;
      this->impact = impact;
   }

   ACT(string identifiant = "act", int impact = 0)
   {
      this->identifiant = identifiant;
      this->texte = "";
      this->impact = impact;
   }

   //void executer(Monstre &m) {}
   void afficherTexte() {}
};