#pragma once
#include <string>
using std::string;

#include "entite.h"

class Personnage;
class Act;

class Monstre: public Entite
{
private:
    string resultatCombat;
 
public:
    Monstre(string nom, int hpMax, int atk, int def, int mercyGoal, string description, Act** inventaireACT =nullptr, int tailleInventaireACT = 0)
        : Entite(nom, hpMax, atk, def, mercyGoal, description, inventaireACT, tailleInventaireACT)
    {
        resultatCombat = "";
    }
    
    string getResultatCombat();

    void setResultatCombat(string resultat);
    
    // void modifierMercy(int valeur);
};