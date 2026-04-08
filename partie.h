#pragma once
#include "personnage.h"
#include "monstre.h"
#include "act.h"
using namespace std;

class Partie
{
   //commentaire

   //comm2
private:
   Personnage personnage;
   Monstre** bestiaire;        // monstres déjà vaincus
   int tailleBestiaire;
   Monstre** monstresPossibles; // chargés depuis monsters.csv
   int tailleMonstresPossibles;
   ACT* catalogueACT;

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
   void chargerMonstres(string fichier);
   void chargerItems(string fichier);
   void initialiserCatalogueACT();
   bool verifierFinPartie();
   void afficherFin();
};