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
    stats = nullptr;
    tailleStats = 0;
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
    
    this->tailleStats = entite.tailleStats;
    this->tailleInventaireACT = entite.tailleInventaireACT;

    if (entite.inventaireACT != nullptr && tailleInventaireACT > 0) {
        this->inventaireACT = new Act*[tailleInventaireACT]();
        for (int i = 0; i < tailleInventaireACT; i++) {
            this->inventaireACT[i] = entite.inventaireACT[i]; 
        }
    } else {
        this->inventaireACT = nullptr;
    }

    if (entite.stats != nullptr && tailleStats > 0)
    {
        this->stats = new Stat *[tailleStats];
        for (int i = 0; i < tailleStats; i++)
        {
            this->stats[i] = new Stat(*entite.stats[i]);
        }
    }
    else
    {
        this->stats = nullptr;
    }
}

Entite::~Entite(){
    delete[] inventaireACT;
    destructionStats();
}

void Entite::destructionStats(){
    
    for (int i = 0; i < tailleStats; i++)
    {
        delete stats[i];
    }
    delete[] stats;
    this->stats = nullptr;
    this->tailleStats = 0;
}
string Entite::utiliserAct(int i, Entite &entiteCible){
    return this->inventaireACT[i]->Impact((*this), entiteCible);
};

void Entite::AddStat(Stat* stat){

    this->tailleStats += 1;
    Stat** tempStats = new Stat *[this->tailleStats]();

    for (int i = 0; i < this->tailleStats - 1; i++)
    {
        tempStats[i] = this->stats[i];
    }
    tempStats[this->tailleStats - 1] = stat;

    delete[] this->stats;
    this->stats = tempStats;
}

int Entite::getStatValue(string nom)
{
    for (int i = 0; i < this->tailleStats; i++)
    {
        if (this->stats[i]->getNom() == nom)
        {
            return this->stats[i]->getValue();
        }
    }
    Stat* temp = Stat::instancierStat(nom);
    this->AddStat(temp);
    return temp->getValue();
};

void Entite::setStatValue(string nom, int valeur){
    for (int i = 0; i < this->tailleStats; i++)
    {
        if (this->stats[i]->getNom() == nom)
        {
            this->stats[i]->setValue(valeur);
        }
    }
};

