#include "Partie.h"
#include "MonstreLambda.h"
#include "MiniBoss.h"
#include "Boss.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
using namespace std;

private:
   Personnage Personnage_Actif;
   vector<Monstre *> bestiaire;        // monstres déjà vaincus
   vector<Monstre *> ennemisPossibles; // chargés depuis monsters.csv
   vector<ACT> catalogueACT;
}

Partie::~Partie()
{
   for (Monstre *m : ennemisPossibles)
      delete m;
   // Note : les monstres du bestiaire pointent vers les mêmes objets, ne pas double-delete
}

// --- Boucle principale ---

void Partie::demarrer()
{
   // Charger les fichiers, initialiser le catalogue ACT, puis lancer la boucle du menu principal
}

void Partie::afficherMenuPrincipal()
{
   // Afficher les options : Bestiaire / Démarrer un combat / Statistiques / Items / Quitter
   // Lire le choix du joueur et appeler la méthode correspondante
}

// --- Options du menu ---

void Partie::afficherBestiaire()
{
   // Afficher tous les monstres présents dans bestiaire avec leurs infos et résultat combat
}

void Partie::afficherStatsPersonnage()
{
   // Déléguer à joueur.afficherStats()
}

void Partie::afficherItems()
{
   // Afficher l'inventaire du joueur et permettre d'utiliser un item
}

// --- Combat ---

void Partie::demarrerCombat()
{
   // Tirer un monstre aléatoire et lancer combattre()
}

bool Partie::combattre(Monstre &m)
{
   // Boucle de combat tant que joueur et monstre sont vivants
   // À chaque tour : afficher menu FIGHT / ACT / ITEM / MERCY, lire choix, appliquer action
   // Puis tour du monstre si toujours vivant
   // Retourner true si le joueur a gagné, false si défaite
   return false;
}

Monstre *Partie::tirerMonstreAleatoire()
{
   // Retourner un pointeur vers un monstre tiré aléatoirement dans ennemisPossibles
   return nullptr;
}

// --- Chargement des fichiers ---

void Partie::chargerMonstres(string fichier)
{
   // Ouvrir fichier, parser chaque ligne (séparateur ;)
   // Créer MonstreLambda / MiniBoss / Boss selon la catégorie
   // Gérer "fichier introuvable" et "ligne mal formée"
}

void Partie::chargerItems(string fichier)
{
   // Ouvrir fichier, parser chaque ligne (séparateur ;)
   // Créer un Item et l'ajouter à l'inventaire du joueur
   // Gérer "fichier introuvable" et "ligne mal formée"
}

// --- Catalogue ACT ---

void Partie::initialiserCatalogueACT()
{
   // Remplir catalogueACT avec au moins 8 ACT pré-définies
   // Au moins 2 avec un impact négatif sur Mercy
   // Exemple :
   // catalogueACT.push_back(ACT("JOKE",       "Tu racontes une blague nulle. Le monstre ricane.", +20));
   // catalogueACT.push_back(ACT("COMPLIMENT",  "Tu complimentes ses chaussures inexistantes.",      +15));
   // catalogueACT.push_back(ACT("INSULT",      "Tu insultes sa mère. Mauvaise idée.",               -25));
   // ...
}

// --- Fin de partie ---

bool Partie::verifierFinPartie()
{
   // Retourner true si joueur.getNbVictoires() >= 10
   return false;
}

void Partie::afficherFin()
{
   // Afficher la fin selon nbTues et nbEpargnes :
   //   nbEpargnes == 0 -> Fin Génocidaire
   //   nbTues     == 0 -> Fin Pacifiste
   //   sinon          -> Fin Neutre
}