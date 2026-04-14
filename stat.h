#pragma once
#include <string>
using std::string;

class Stat{
   public:
   string nom;
   int value;

   public:
   Stat(string nom, int value);

   string getnom();
   int getvalue();

   void setnom(string nom);
   void setvalue(int value);

   virtual void EndTurnEffectStat();
};

class Vulnerabilite : public Stat
{
   public:
   Vulnerabilite(string nom, int value);
   
   void EndTurnEffectStat() override;
};
