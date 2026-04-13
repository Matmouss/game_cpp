#include "entite.h"
#include "act.h"

Entite::Entite()
{
    nom = "";
    description = "";
    hp = 0;
    hpMax = 0;
    atk = 0;
    def = 0;
    mercy = 0;
    mercyGoal = 0;
    inventaireACT = nullptr;
    tailleInventaireACT = 0;
}

Entite::Entite(const Entite &entite) {
    this->nom = entite.nom;
    this->hp = entite.hp;
    this->hpMax = entite.hpMax;
    this->atk = entite.atk;
    this->def = entite.def;
    this->mercy = entite.mercy;
    this->mercyGoal = entite.mercyGoal;
    this->description = entite.description;

    this->tailleInventaireACT = entite.tailleInventaireACT;

    if (entite.inventaireACT != nullptr && tailleInventaireACT > 0) {
        this->inventaireACT = new Act*[tailleInventaireACT];
        for (int i = 0; i < tailleInventaireACT; i++) {
            this->inventaireACT[i] = entite.inventaireACT[i]; 
        }
    } else {
        this->inventaireACT = nullptr;
    }
}

Entite::~Entite(){
    delete[] inventaireACT;
}

string Entite::utiliserAct(int i, Entite &entiteCible){
    return this->inventaireACT[i]->Impact((*this), entiteCible);
};

