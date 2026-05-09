#include "personnage.h"
#include "item.h"

class Stat;

Personnage::Personnage(): Entite() {
    this->nbTue = 0;
    this->nbEpargne = 0;
    this->nbVictoire = 0;
    this->inventaireItems = nullptr;
    this->tailleInventaire = 0;
}

Personnage::Personnage(std::string nom, int hpMax, int atk, int def, int mercyGoal, std::string description, Act **inventaireACT, int tailleInventaireACT, Item **inventaireItems, int tailleInventaire, Stat **stats, int tailleStats, int actPoints, int maxActPoints)
    : Entite(nom, hpMax, atk, def, mercyGoal, description, inventaireACT, tailleInventaireACT, stats, tailleStats, actPoints, maxActPoints)
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
    if (i < tailleInventaire) {
        inventaireItems[i] = item;
        return true;
    }
    return false;
}


void Personnage::ajouterItem(Item* &item) {
    for (int i = 0; i < tailleInventaire; i++) {
        if (inventaireItems[i] == nullptr) {
            inventaireItems[i] = item;
            return;
        }
    }   
}

void Personnage::retirerItem(int i){
    if (i < tailleInventaire && inventaireItems[i] != nullptr) {
        inventaireItems[i] = nullptr;
    }

    int index = i;
    while (index < tailleInventaire - 1 && inventaireItems[index + 1] != nullptr) {
        inventaireItems[index] = inventaireItems[index + 1];
        inventaireItems[index + 1] = nullptr;
        index++;
    }
}

string Personnage::utiliserItem(int i) {
    if (i < tailleInventaire && inventaireItems[i] != nullptr) {
        string texte = inventaireItems[i]->utiliser(*this);
        retirerItem(i);
        return texte;
    }
    return "Item inconnu";
}
// void Personnage::allStatsUp(int statUpValue){
//     //this->setStatValue("hpMax", this->getStatValue("hpMax") + statUpValue);
//     //this->setStatValue("atk", this->getStatValue("atk") + statUpValue);
//     int a = getStatValue("def") + statUpValue;
//      this->setStatValue("def",a);
// }