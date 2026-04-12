#include "entite.h"
#include "act.h"

Entite::~Entite(){
    // for (int i = 0; i < tailleInventaireACT; i++)
    //     delete inventaireACT[i];
    delete[] inventaireACT;
}

string Entite::utiliserAct(int i, Entite &entiteCible){
    return this->inventaireACT[i]->Impact((*this), entiteCible);
};

