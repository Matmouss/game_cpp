#include <string>
using std::string;

#include "Act.h"
#include "Entite.h"

#pragma region Act
    
Act::Act() {
    this->identifiant = "identifiant";
    this->texte = "texte";
}

Act **Act::getActionsPossibles()
{
    static Act *actions[] = {new Attaquer(), new Dodo() ,new SerrerMain()};
    return actions;
}

Act::Act(string identifiant, string texte, int actPointsCost) {
    this->identifiant = identifiant;
    this->texte = texte;
    this->actPointsCost = actPointsCost;
}

string Act::getIdentifiant() {return identifiant;}

void Act::DestructActionPossibles()
{
    for (int i = 0; i < nbActionsPossibles; i++)
        delete getActionsPossibles()[i];
        //ne pas détruire tout le tableau prcq static
}

Act::~Act() = default;

string Act::Impact(Entite&, Entite&){
    return this->texte;
}

#pragma endregion

#pragma region SerrerMain 

SerrerMain::SerrerMain() : Act("serrer_main", "Vous serrez la main du monstre.",2) {}; 

string SerrerMain::Impact(Entite&, Entite& entiteCible) {
    entiteCible.setMercy(entiteCible.getMercyGoal());
    return this->texte;
}
#pragma endregion

#pragma region Dodo

Dodo::Dodo() : Act("dodo", "Dodo tah le cours de philo",1) {}; 

string Dodo::Impact(Entite& entite, Entite&) {
    entite.soigner(1);
    return this->texte;
}
#pragma endregion

#pragma region Attaquer

Attaquer::Attaquer() : Act("Attaquer Simple", "ptit attaque tranquilloubilou", 1) {};

string Attaquer::Impact(Entite &entite, Entite &entiteCible)
{
    entite.attaquer(entiteCible);
    return this->texte;
}
