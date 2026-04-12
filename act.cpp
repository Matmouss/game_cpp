#include "act.h"
#include "monstre.h"
#include "personnage.h"
#include "entite.h"

#include <iostream>
using namespace std;
 
#pragma region ACT

ACT** ACT::actionsPossibles = new ACT*[ACT::nbActionsPossibles]{new SerrerMain(), new Dodo()};

ACT::ACT(string identifiant, string texte) {
    this->identifiant = identifiant;
    this->texte = texte;
}

string ACT::getIdentifiant() {return identifiant;}

ACT::~ACT(){}

string ACT::Impact(Entite& entite, Entite& entiteCible){
    return this->texte;
}

#pragma endregion

#pragma region SerrerMain 

SerrerMain::SerrerMain() : ACT("serrer_main", "Vous serrez la main du monstre.") {}; 

string SerrerMain::Impact(Entite& entite, Entite& entiteCible) {
    entiteCible.setMercy(entiteCible.getMercyGoal());
    return this->texte;
}
#pragma endregion

#pragma region Dodo

Dodo::Dodo() : ACT("dodo", "Dodo tah le cours de philo") {}; 

string Dodo::Impact(Entite& entite, Entite& entiteCible) {
    entite.soigner(1);
    return this->texte;
}
#pragma endregion