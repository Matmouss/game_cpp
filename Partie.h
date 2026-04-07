#pragma once
#include "Personnage.h"
#include "Monstre.h"
#include "ACT.h"
#include <vector>
#include <memory>
using namespace std;

class Partie
{

private:
   Personnage joueur;
   vector<Monstre *> bestiaire;        // monstres déjà vaincus
   vector<Monstre *> ennemisPossibles; // chargés depuis monsters.csv
   vector<ACT> catalogueACT;

public:
   Partie(Personnage joueur);
   ~Partie();

   void demarrer();
   void afficherMenuPrincipal();
   void demarrerCombat();
   bool combattre(Monstre &m);
   Monstre *tirerMonstreAleatoire();
   void afficherBestiaire();
   void afficherStatsPersonnage();
   void afficherItems();
   void chargerMonstres(string fichier);
   void chargerItems(string fichier);
   void initialiserCatalogueACT();
   bool verifierFinPartie();
   void afficherFin();
};