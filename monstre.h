#pragma once
#include <iostream>
 
using namespace std;
 
class Monstre
{
private:
    string nom;
    int hp;
    int hpMax;
    int atk;
    int def;
    int mercy;
    int mercyGoal;
    string resultatCombat;
    string* actionsDisponibles;
    int nbActionsDisponibles;
 
public:
    Monstre(string nom = "Monstre", int hpMax = 10, int atk = 5, int def = 1, int mercyGoal = 100);
    virtual ~Monstre();
 
    string getNom();
    int getHp();
    int getHpMax();
    int getAtk();
    int getDef();
    int getMercy();
    int getMercyGoal();
    string getResultatCombat();
    string* getActionsDisponibles();
    int getNbActionsDisponibles();
 
    void setResultatCombat(string resultat);
    void setActionsDisponibles(string* actions, int nb);
    void setMercy(int Mercy);
 
    int attaquer();
    void prendreDegats(int degats);
    void modifierMercy(int valeur);
    bool peutEtreEpargne();
    bool estVivant();
    void afficherInfos();
 
    int getNbActions();
};