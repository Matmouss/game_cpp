#include <iostream>
using namespace std;

struct Item
{
   string nom;
   string type; // ex: "HEAL"
   int valeur;
   int quantite;
};

class Personnage{

   string nom;
   int hpActuel;
   int hpMax;
   int nbTues;
   int nbEpargnes;
   int nbVictoires;
   // vector<Item> inventaire;
   
   Personnage(string nom, int hpMax)
   {
      this->nom = nom;
      this->hpMax = hpMax;
      this->hpActuel = hpMax;
      this->nbTues = 0;
      this->nbEpargnes = 0;
      this->nbVictoires = 0;
   }

   int attaquer()
   {
      // Retourner des dégâts aléatoires entre 0 et hpMax (formule du sujet)
      return 0;
   }

   void prendreDegats(int degats)
   {
      // Réduire hpActuel de degats, borner à 0
   }

   void seSoigner(int valeur)
   {
      // Augmenter hpActuel de valeur, borner à hpMax
   }

   bool utiliserItem(string nomItem)
   {
      // Chercher l'item dans l'inventaire, appliquer son effet, décrémenter quantité
      // Retourner true si l'item a été trouvé et utilisé, false sinon
      return false;
   }

   bool estVivant()
   {
      // Retourner true si hpActuel > 0
      return false;
   }

   void gagnerVictoire()
   {
      // Incrémenter nbVictoires
   }

   void incrementerTue()
   {
      // Incrémenter nbTues
   }

   void incrementerEpargne()
   {
      // Incrémenter nbEpargnes
   }

   void afficherStats()
   {
      // Afficher nom, hpActuel/hpMax, nbTues, nbEpargnes, nbVictoires
   }

   void ajouterItem(Item item)
   {
      // Ajouter l'item à l'inventaire (fusionner la quantité si l'item existe déjà)
   }

   string getNom() { return nom; }
   int getHpActuel() { return hpActuel; }
   int getHpMax() { return hpMax; }
   int getNbTues() { return nbTues; }
   int getNbEpargnes() { return nbEpargnes; }
   int getNbVictoires() { return nbVictoires; }
   // vector<Item> getInventaire() { return inventaire; }
};