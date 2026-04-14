#include <string>
using std::string;

#include "stat.h"

Stat::Stat(string nom, int value){
this->nom = nom;
this->value = value;
}

string Stat::getnom(){return this->nom;}

int Stat::getvalue(){return this->value;}

void Stat::setnom(string nom) { this->nom = nom;};
void Stat::setvalue(int value){this->value = value;};

void Stat::EndTurnEffectStat(){
   setvalue(getvalue()-1);
}

Vulnerabilite::Vulnerabilite(string nom, int value) : Stat(nom, value){};

void Vulnerabilite::EndTurnEffectStat()
{
   setvalue(getvalue() - 1);
}