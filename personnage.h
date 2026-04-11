#pragma once
#include <iostream>
#include "item.h"

using namespace std;

class ACT;

class Monstre;

class Personnage
{
public:
   string nom;
   int Hp;
   int HpMax;
   int NbTue;
   int NbEpargne;
   int nbVictoire;
   bool EstVivant;
   Item** inventaireItems;
   int tailleInventaire;
   ACT** inventaireACT;
   int tailleInventaireACT;

public:
   Personnage(string nom,int HpMax);
   Personnage();
   int getHp();
   string attaquer(Monstre &monstre);
   void utiliserActe();
   bool epargner();
   void prendreDegats(int degats);
   bool estVivant();
   void gagnerCombat();
   void incrementerTue();
   void incrementerEpargne();
   void afficherStats();
};