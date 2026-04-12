#pragma once
#include "personnage.h"

class Item;
class Act;
class Monstre;

class Partie
{
public:
   Personnage personnage = Personnage();
   Monstre** bestiaire;        // monstres déjà vaincus
   int tailleBestiaire;
   Monstre** monstresPossibles; // chargés depuis monsters.csv
   int tailleMonstresPossibles;
   Act** catalogueACT;    
   int tailleCatalogueACT; // nombre d’éléments dans le tableau
   Item** itemPossible;
   int tailleItemPossible;


public:
   Partie();
   ~Partie();

   void demarrer();
   void afficherMenuPrincipal();
   void demarrerCombat();
   bool combattre(Monstre &Monstre);
   Monstre* tirerMonstreAleatoire();
   void afficherBestiaire();
   void afficherStatsPersonnage();
   void afficherItems();
   void initialiserCatalogueACT();
   bool verifierFinPartie();
   void afficherFin();
   void ajouterBestiaire(Monstre* monstre);
};