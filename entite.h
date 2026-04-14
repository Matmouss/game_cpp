#pragma once
#include <string>
using std::string;
#include <cmath>
#include "stat.h"

class Act;

// void setActionsDisponibles(string *actions, int nb)
// {
//    delete[] actionsDisponibles;
//    this->nbActionsDisponibles = nb;
//    this->actionsDisponibles = new string[nb];
//    for (int i = 0; i < nb; i++)
//       this->actionsDisponibles[i] = actions[i];
// }

class Entite
{
protected:
    string nom;
    string description;
    int hp;
    int hpMax;
    int atk;
    int def;
    int mercy;
    int mercyGoal;
    Act** inventaireACT;
    int tailleInventaireACT;
    Stat** stats;
    int tailleStats;


public: 

    Entite();

    Entite(const Entite &entite);

    //Entite(string nom, int hpMax, int atk, int def, int mercyGoal, string description, Act** inventaireACT, int tailleInventaireACT);

    Entite(string nom, int hpMax, int atk, int def, int mercyGoal, string description, Act **inventaireACT, int tailleInventaireACT, Stat **stats, int tailleStats);

    ~Entite();

    string getNom() { return nom; }
    int getHp() { return hp; }
    int getHpMax() { return hpMax; }
    int getAtk() { return atk; }
    int getDef() { return def; }
    int getMercy() { return mercy; }
    int getMercyGoal() { return mercyGoal; }
    string getDescription() { return description; }
    int getNbActions() { return tailleInventaireACT; }
    Act* getActions(int i) { return inventaireACT[i]; }
    int getNbStats() { return tailleStats; }
    Stat* getStats(int i) { return stats[i]; }

    int getStatValue(string nom);
    void setStatValue(string nom, int valeur);

    void AddStat(Stat* stat);
    void destructionStats();
    void setMercy(int valeur) { mercy = valeur; }
    void setAction(Act* action, int i) { inventaireACT[i] = action; }

    string afficherInfos(){
        string infos = "Nom: " + this->nom + "\n";
        infos += "HP: " + std::to_string(this->hp) + "/" + std::to_string(this->hpMax) + "\n";
        infos += "Atk: " + std::to_string(this->atk) + "\n";
        infos += "Def: " + std::to_string(this->def) + "\n";
        infos += "Mercy: " + std::to_string(this->mercy) + "/" + std::to_string(this->mercyGoal) + "\n";
        infos += "Description: " + this->description + "\n";
        return infos;
    }

    string attaquer(Entite &entiteCible){
        int degats = std::max(this->atk - entiteCible.getDef(),0);
        return entiteCible.prendreDegats(degats);
    }

    string prendreDegats(int degats){
        this->hp -= degats;
        return this->nom + " prend " + std::to_string(degats) + " degats";
    }

    string soigner(int soin){
        this->hp += soin;
        if (this->hp > this->hpMax)
            this->hp = this->hpMax;
        return this->nom + " se soigne de " + std::to_string(soin) + " points";
    }

    string utiliserAct(int i, Entite &entiteCible);
};