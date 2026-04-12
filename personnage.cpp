#include "personnage.h"
#include <iostream>
#include "item.h"
#include "act.h"


Personnage::Personnage(std::string nom, int hpMax, int atk, int def, int mercyGoal, std::string description, ACT** inventaireACT, int tailleInventaireACT, Item** inventaireItems, int tailleInventaire)
: Entite(nom, hpMax, atk, def, mercyGoal, description, inventaireACT, tailleInventaireACT)
{
    this->nbTue = 0;
    this->nbEpargne = 0;
    this->nbVictoire = 0;
    this->inventaireItems = inventaireItems;
    this->tailleInventaire = tailleInventaire;
}



bool Personnage::setInventaireItems(Item* item, int i) { 
    if (i < tailleInventaire &&  inventaireItems[i] == nullptr) {
        inventaireItems[i] = item;
        return true;
    }
    return false;
}