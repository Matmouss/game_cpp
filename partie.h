#pragma once

class Item;
class Act;
class Monstre;
class Personnage;
class Stat;

class Partie
{
public:
   Personnage* personnage;
   Monstre** bestiaire;        // monstres déjà vaincus
   int tailleBestiaire;
   Monstre** monstresPossibles; // chargés depuis monsters.csv
   int tailleMonstresPossibles;
   Act** catalogueACT;    
   int tailleCatalogueACT; // nombre d’éléments dans le tableau
   Item** itemPossible;
   int tailleItemPossible;

public:
   Partie(int hpMax = 100, int tailleInventaireACT = 4, int tailleInventaireItems = 5, int maxActPoints = 3, int atk = 10, int def = 10, int mercyGoal = 100, string nom = "Le Stagiaire", string description = "le héros de l'histoire");
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
   void ajouterBestiaire(Monstre* &monstre);
   Monstre* randomMonstre(string type);
};