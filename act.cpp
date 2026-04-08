#pragma once
#include "act.h"
#include "monstre.h"
#include <iostream>
using namespace std;
 
ACT::ACT(string identifiant, string texte, int impact) {
    this->identifiant = identifiant;
    this->texte = texte;
    this->impact = impact;
}

string ACT::getIdentifiant() {return identifiant;}
 
int ACT::getImpact() {return impact;}
 