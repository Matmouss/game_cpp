#pragma once
#include <iostream>

using namespace std;
class Personnage
{
private:
   string nom;
   int Hp;
   int HpMax;
   int NbTue;
   int NbEpargne;
   int nbVictoire;
   bool EstVivant;

public:
   Personnage(string nom    = "Hero", int Hp = 10, int HpMax = 10, int NbTue = 0, int NbEpargne = 0, int nbVictoire = 0);
   Personnage(string nom = "Hero", int HpMax = 10);

   int attaquer();
   void utiliserActe();
   bool epargner();
   void prendreDegats(int degats);
   bool estVivant();
   void gagnerCombat();
   void incrementerTue();
   void incrementerEpargne();
   void afficherStats();
};