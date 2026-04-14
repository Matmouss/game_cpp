#include <string>
using std::string;

#include "stat.h"

Stat::Stat(string nom){
this->nom = nom;
}
Stat::Stat(){
   this->nom = "Default";
   this->valeur = 0;
   this->initValeur = 0;
}

Stat::Stat(Stat &statcopie){
   this->nom = statcopie.nom;
   this->valeur = statcopie.valeur;
   this->initValeur = statcopie.initValeur;

}
string Stat::getNom(){return this->nom;}

int Stat::getValue(){return this->valeur;}

void Stat::setNom(string nom) { this->nom = nom;}
void Stat::setValue(int valeur){this->valeur = valeur;}

Stat* Stat::instancierStat(string nom){
   if (nom == "Vulnerabilite")
      return new Vulnerabilite();
   return nullptr;
}

void Stat::endTurnEffectStat(){
   setValue(getValue()-1);
}

Vulnerabilite::Vulnerabilite() : Stat("Vulnerabilite"){ 
   this->valeur = 0;
   this->initValeur = this->valeur;
}

void Vulnerabilite::endTurnEffectStat()
{
   setValue(getValue() - 1);
}