#pragma once
#include <iostream>
#include "personnage.h"
#include "entite.h"
 
using namespace std;
 
class Monstre: public Entite
{
private:
    string resultatCombat;
 
public:
    Monstre(string nom, int hpMax, int atk, int def, int mercyGoal, string description, ACT** inventaireACT, int tailleInventaireACT)
        : Entite(nom, hpMax, atk, def, mercyGoal, description, inventaireACT, tailleInventaireACT)
    {
        resultatCombat = "";
    }
    
    string getResultatCombat();

    void setResultatCombat(string resultat);
 
    string attaquer(Personnage &personnage);
    string prendreDegats(int degats);
    
    void modifierMercy(int valeur);
};