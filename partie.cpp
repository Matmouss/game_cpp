#include "partie.h"
#include "MonstreLambda.h"
#include "miniBoss.h"
#include "boss.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
using namespace std;

Partie::Partie(Personnage joueur) : joueur(joueur)
{
}

Partie::~Partie()
{
   for (Monstre *m : ennemisPossibles)
      delete m;
}