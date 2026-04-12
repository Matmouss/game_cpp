#pragma once
#include <iostream>
#include <cmath>
#include "act.h"

using namespace std;

class ACT;

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
    ACT** inventaireACT;
    int tailleInventaireACT;


public: 
    Entite()
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

    Entite(string nom, int hpMax, int atk, int def, int mercyGoal, string description, ACT** inventaireACT, int tailleInventaireACT) {
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
    }
    
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
    ACT* getActions(int i) { return inventaireACT[i]; }

    void setMercy(int valeur) { mercy = valeur; }
    void setAction(ACT* action, int i) { inventaireACT[i] = action; }

    string afficherInfos(){
        string infos = "Nom: " + this->nom + "\n";
        infos += "HP: " + to_string(this->hp) + "/" + to_string(this->hpMax) + "\n";
        infos += "Atk: " + to_string(this->atk) + "\n";
        infos += "Def: " + to_string(this->def) + "\n";
        infos += "Mercy: " + to_string(this->mercy) + "/" + to_string(this->mercyGoal) + "\n";
        infos += "Description: " + this->description + "\n";
        return infos;
    }

    string attaquer(Entite &entiteCible){
        int degats = max(this->atk - entiteCible.getDef(),0);
        return entiteCible.prendreDegats(degats);
    }

    string prendreDegats(int degats){
        this->hp -= degats;
        return this->nom + " prend " + to_string(degats) + " degats";
    }

    string soigner(int soin){
        this->hp += soin;
        if (this->hp > this->hpMax)
            this->hp = this->hpMax;
        return this->nom + " se soigne de " + to_string(soin) + " points";
    }

    string utiliserAct(int i, Entite &entiteCible);
};