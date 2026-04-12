#pragma once
#include <string>


class Item;
class ACT;
class Entite;

class Personnage : public Entite
{
private:
    int nbTue;
    int nbEpargne;
    int nbVictoire;

    Item** inventaireItems;
    int tailleInventaire;

public:
   Personnage() = default;
   
    Personnage(std::string nom, int hpMax, int atk, int def, int mercyGoal, std::string description, ACT** inventaireACT, int tailleInventaireACT, Item** inventaireItems, int tailleInventaire);

    int getNbTue() { return nbTue; }
    int getNbEpargne() { return nbEpargne; }
    int getNbVictoire() { return nbVictoire; }
    Item* getInventaireItems(int i) { return inventaireItems[i]; }
    int getTailleInventaire() { return tailleInventaire; }

    void setNbTue(int valeur) { nbTue = valeur; }
    void setNbEpargne(int valeur) { nbEpargne = valeur; }
    void setNbVictoire(int valeur) { nbVictoire = valeur; }
    bool setInventaireItems(Item* item, int i);


    void gagnerCombat() { nbVictoire++; }
};