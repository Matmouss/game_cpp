#include "entite.h"
#include "act.h"
#include "stat.h"

// Entite::Entite(string nom, int hpMax, int atk, int def, int mercyGoal, string description, Act **inventaireACT, int tailleInventaireACT)
// {
//     this->nom = nom;
//     this->hp = hpMax;
//     this->hpMax = hpMax;
//     this->atk = atk;
//     this->def = def;
//     this->mercy = 0;
//     this->mercyGoal = mercyGoal;
//     this->description = description;
//     this->inventaireACT = inventaireACT;
//     this->tailleInventaireACT = tailleInventaireACT;
// }

Entite::Entite(string nom, int hpMax, int atk, int def, int mercyGoal, string description, Act **inventaireACT, int tailleInventaireACT,Stat** stats, int tailleStats)
{
    this->nom = nom;
    this->hp = hpMax;
    this->hpMax = hpMax;
    this->atk = atk;
    this->def = def;
    this->mercy = 0;
    this->mercyGoal = mercyGoal;
    this->description = description;
    this->inventaireACT = inventaireACT;
    this->tailleInventaireACT = tailleInventaireACT;
    this->stats = stats;
    this->tailleStats = tailleStats;
}

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

