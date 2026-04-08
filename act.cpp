#pragma once
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
 
#pragma endregion

#pragma region SerrerMain 

SerrerMain::SerrerMain(): ACT("serrer_main", "Vous serrez la main du monstre.") {}

void SerrerMain::Impact(Personnage &p, Monstre &m) {
    m.setMercy((m.getMercy() + 1)*100);
}

#pragma endregion
