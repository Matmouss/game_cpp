#pragma once
#include <string>
using std::string;
using std::to_string;

class Stat{
   public:
   string nom;
   int valeur;
   int initvaleur;

   public:
   Stat(string nom);
   Stat();
   Stat(Stat &statcopie);

      string getnom();
      int getvalue();

      void setnom(string nom);
      void setvalue(int valeur);

      static Stat *InstancierStat(string nom);

      virtual void EndTurnEffectStat();
   };

class Vulnerabilite : public Stat
{
   public:
   Vulnerabilite();
   
   void EndTurnEffectStat() override;
};
