#include "personnage.h"

class Stat;

Personnage::Personnage(): Entite() {
    this->nbTue = 0;
    this->nbEpargne = 0;
    this->nbVictoire = 0;
    this->inventaireItems = nullptr;
    this->tailleInventaire = 0;
}

Personnage::Personnage(std::string nom, int hpMax, int atk, int def, int mercyGoal, std::string description, Act** inventaireACT, int tailleInventaireACT, Item** inventaireItems, int tailleInventaire, Stat** stats, int tailleStats)
: Entite(nom, hpMax, atk, def, mercyGoal, description, inventaireACT, tailleInventaireACT,stats,tailleStats)
{
    this->nbTue = 0;
    this->nbEpargne = 0;
    this->nbVictoire = 0;
    this->inventaireItems = inventaireItems;
    this->tailleInventaire = tailleInventaire;
}

Personnage::~Personnage() {
    delete[] inventaireItems;
}

bool Personnage::setInventaireItems(Item* &item, int i) { 
    if (i < tailleInventaire &&  inventaireItems[i] == nullptr) {
        inventaireItems[i] = item;
        return true;
    }
    return false;
}