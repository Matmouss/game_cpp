#include "entite.h"
#include "act.h"
#include "stat.h"
#include <cmath>

Entite::Entite(string nom, int hpMax, int atk, int def, int mercyGoal, string description, Act **inventaireACT, int tailleInventaireACT, Stat **stats, int tailleStats, int actPoints,int maxActPoints)
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
    this->actPoints = actPoints;
    this->maxActPoints = maxActPoints;
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
    actPoints = 0;
    maxActPoints = 0;
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
    this->actPoints = entite.actPoints;
    this->maxActPoints = entite.maxActPoints;

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
    Act* act = this->inventaireACT[i];

    if (this->setAct(act->actPointsCost)){

        return act->Impact((*this), entiteCible);
    }
    return "Nope you don't have enough act points";

};

bool Entite::setAct(int actCout){
    if (this->actPoints-actCout >= 0)
    {
        this->actPoints -= actCout;
        return true;
    }
    return false;
}

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
    if (tailleStats != 0){
        for (int i = 0; i < this->tailleStats; i++)
        {
            if (this->stats[i]->getNom() == nom)
            {
                return this->stats[i]->getValue();
            }
        }
    }
    Stat* temp = Stat::instancierStat(nom);
    this->AddStat(temp);
    return temp->getValue();
};

void Entite::setStatValue(string nom, int valeur){

    if (tailleStats != 0){
    for (int i = 0; i < this->tailleStats; i++)
        {
            if (this->stats[i]->getNom() == nom)
            {
                this->stats[i]->setValue(valeur);
            }
        }
    }
};

void Entite::EndTurn()
{
    Stat **temp = this->stats;
    int taille = this->getNbStats();
    
    for (int i = 0; i < taille; i++)
    {
        this->getStats(i)->endTurnEffectStat();

        if (this->getStats(i)->getValue() <= this->getStats(i)->getInitValue()){

            temp = new Stat *[getNbStats()-1];

            for (int j = 0; j < getNbStats();j++){
                if (i != j){
                    temp[j] = getStats(j);
                }
            }
            this->tailleStats -= 1;
        }
    }
        this->actPoints = this->maxActPoints;
        this->stats = temp;
        
}