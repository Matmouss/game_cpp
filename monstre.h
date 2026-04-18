#pragma once
#include <string>
using std::string;

#include "entite.h"

class Personnage;
class Act;
class Stat;

class Monstre: public Entite
{
protected:
    string resultatCombat;
    string type;
    string* dialogues;
    int tailleDialogues;
 
public:
    Monstre();

    Monstre(const Monstre &monstre);

    virtual ~Monstre();

    Monstre(string nom, int hpMax, int atk, int def, int mercyGoal, string description, Act **inventaireACT, int tailleInventaireACT, Stat **stats, int tailleStats, int actPoints,int maxActPoints, string* dialogues, int tailleDialogues);

    string getResultatCombat();
    string getType() { return type; }

    void setResultatCombat(string resultat);
};