#include "act.h"
#include "monstre.h"
#include "personnage.h"
#include <iostream>
using namespace std;
 
#pragma region ACT
ACT::ACT(string identifiant, string texte) {
    this->identifiant = identifiant;
    this->texte = texte;
}

string ACT::getIdentifiant() {return identifiant;}

ACT::~ACT(){}

string ACT::Impact(Personnage &p, Monstre &m){
    return this->texte;
}

#pragma endregion

#pragma region SerrerMain 

SerrerMain::SerrerMain() : ACT("serrer_main", "Vous serrez la main du monstre.") {}; 

string SerrerMain::Impact(Personnage &p, Monstre &m) {
    m.setMercy((m.getMercy() + 1)*100);
    return this->texte;
}
#pragma endregion

#pragma region Dodo

Dodo::Dodo() : ACT("dodo", "Dodo tah le cours de philo") {}; 

string Dodo::Impact(Personnage &p, Monstre &m) {
    p.Hp = p.Hp + 1;
    return this->texte;
}
#pragma endregion