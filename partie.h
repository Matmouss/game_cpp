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
   Personnage joueur;
   Monstre** bestiaire;        // monstres déjà vaincus
   int TailleBestiaire;
   Monstre* ennemisPossibles; // chargés depuis monsters.csv
   int TailleEnnemisPossibles;
   ACT* catalogueACT;

public:
   Partie(Personnage joueur);
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