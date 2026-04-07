
#include <iostream>
#include <memory>
using namespace std;

class Joueur{

   private:
   string nom;
   int Hp;
   int HpMax;
   int NbTue;
   int NbEpargne;
   int nbVictoire;
   bool EstVivant = false;

   public:
   Joueur(string nom = "Hero", int Hp = 10, int HpMax = 10, int NbTue = 0, int NbEpargne = 0, int nbVictoire= 0)
   {
      this->nom = nom;
      this->Hp = Hp;
      this->HpMax = HpMax;
      this->NbTue = NbTue;
      this->NbEpargne = NbEpargne;
      this->nbVictoire = nbVictoire;
   };
   Joueur(string nom = "Hero", int HpMax = 10) {
      this->nom = nom;
      this->HpMax = HpMax;
      Hp = HpMax;
      NbTue = 0;
      NbEpargne = 0;
      nbVictoire = 0;
   };

   void attaquer() {}
   void utiliserActe() {}
   bool epargner() { return false; }
   void prendreDegats(int degats) {}
   bool estVivant() { return false; }
   void gagnerCombat() {}
   void incrementerTue() {}
   void incrementerEpargne() {}
   void afficherStats() {}
};
