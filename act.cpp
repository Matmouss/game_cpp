#include <string>
using std::string;

#include "Act.h"
#include "Entite.h"

#pragma region Act
    
Act **Act::getActionsPossibles()
{
    static Act* actions[2] = {new SerrerMain(), new Dodo()};
    return actions;
}

Act::Act(string identifiant, string texte) {
    this->identifiant = identifiant;
    this->texte = texte;
}

string Act::getIdentifiant() {return identifiant;}

Act::~Act(){}

string Act::Impact(Entite& entite, Entite& entiteCible){
    return this->texte;
}

#pragma endregion

#pragma region SerrerMain 

SerrerMain::SerrerMain() : Act("serrer_main", "Vous serrez la main du monstre.") {}; 

string SerrerMain::Impact(Entite& entite, Entite& entiteCible) {
    entiteCible.setMercy(entiteCible.getMercyGoal());
    return this->texte;
}
#pragma endregion

#pragma region Dodo

Dodo::Dodo() : Act("dodo", "Dodo tah le cours de philo") {}; 

string Dodo::Impact(Entite& entite, Entite& entiteCible) {
    entite.soigner(1);
    return this->texte;
}
#pragma endregion