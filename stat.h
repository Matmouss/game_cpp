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

   virtual ~Stat();

   string getNom();
   int getValue();
   int getInitValue();

   void setNom(string nom);
   void setValue(int valeur);

   static Stat *instancierStat(string nom);

   virtual void endTurnEffectStat();
   };
   void CheckThreshold();

   class Vulnerabilite : public Stat
   {
   public:
   Vulnerabilite();
   
   void endTurnEffectStat() override;
   };

   class Force : public Stat
   {
   public:
      Force();

      void endTurnEffectStat() override;
   };
