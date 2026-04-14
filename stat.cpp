#include <string>
using std::string;

#include "stat.h"

Stat::Stat(string nom){
this->nom = nom;
}
Stat::Stat(){
   this->nom = "Default";
   this->valeur = 0;
   this->initvaleur = 0;
}

Stat::Stat(Stat &statcopie){
   this->nom = statcopie.nom;
   this->valeur = statcopie.valeur;
   this->initvaleur = statcopie.initvaleur;

}
string Stat::getnom(){return this->nom;}

int Stat::getvalue(){return this->valeur;}

void Stat::setnom(string nom) { this->nom = nom;}
void Stat::setvalue(int valeur){this->valeur = valeur;}

Stat* Stat::InstancierStat(string nom){
   if (nom == "Vulnerabilite")
      return new Vulnerabilite();
   return nullptr;
}

void Stat::EndTurnEffectStat(){
   setvalue(getvalue()-1);
}

Vulnerabilite::Vulnerabilite() : Stat("Vulnerabilite"){ 
   this->valeur = 0;
   this->initvaleur = this->valeur;
}

void Vulnerabilite::EndTurnEffectStat()
{
   setvalue(getvalue() - 1);
}