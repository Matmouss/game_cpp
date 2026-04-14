#pragma once
#include <string>
using std::string;
using std::to_string;

class Stat{
   public:
   string nom;
   int valeur;
   int initValeur;

   public:
   Stat(string nom);
   Stat();
   Stat(Stat &statcopie);

      string getNom();
      int getValue();

      void setNom(string nom);
      void setValue(int valeur);

      static Stat *instancierStat(string nom);

      virtual void endTurnEffectStat();
   };

class Vulnerabilite : public Stat
{
   public:
   Vulnerabilite();
   
   void endTurnEffectStat() override;
};
