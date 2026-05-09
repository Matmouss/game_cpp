#include <string>
using std::string;

#include "Act.h"
#include "Entite.h"
#include "Personnage.h"

#pragma region Act
    
Act::Act() {
    this->identifiant = "identifiant";
    this->texte = "texte";
}

Act **Act::getActionsPossibles()
{
    static Act *actions[] = {new Attaquer(), new Dodo() ,new SerrerMain(), new Soigner(), new Sport(), new Pleurer()};
    return actions;
}

Act::Act(string identifiant, string texte, int actPointsCost) {
    this->identifiant = identifiant;
    this->texte = texte;
    this->actPointsCost = actPointsCost;
}

string Act::getIdentifiant() {return identifiant;}

void Act::DestructActionPossibles()
{
    for (int i = 0; i < nbActionsPossibles; i++)
        delete getActionsPossibles()[i];
        //ne pas détruire tout le tableau prcq static
}

Act::~Act() = default;

string Act::Impact(Entite&, Entite&){
    return this->texte;
}

#pragma endregion

#pragma region SerrerMain 

SerrerMain::SerrerMain() : Act("serrer_main", "Vous serrez la main du monstre.",2) {}; 

string SerrerMain::Impact(Entite&, Entite& entiteCible) {

    entiteCible.setMercy(entiteCible.getMercyGoal());
    return entiteCible.getNom() + " est amadoué par ce serrage de main, sa Mercy est au MAX!";
}

#pragma endregion

#pragma region Dodo

Dodo::Dodo() : Act("dodo", "Dodo tah le cours de philo",1) {}; 

string Dodo::Impact(Entite& entite, Entite&) {
    return entite.soigner(1);
}
#pragma endregion

#pragma region Attaquer

Attaquer::Attaquer() : Act("Attaquer Simple", "ptit attaque tranquilloubilou", 1) {};

string Attaquer::Impact(Entite &entite, Entite &entiteCible)
{
    return entite.attaquer(entiteCible);
}

#pragma endregion

#pragma region Soigner

Soigner::Soigner() : Act("Soigner", "ptit soin tranquilloubilou", 2) {};

string Soigner::Impact(Entite &entite, Entite&)
{
    return entite.soigner(20);
}

#pragma endregion

#pragma region Sport

Sport::Sport() : Act("Sport", "Un petit footing ça fait pas de mal!", 1) {};

string Sport::Impact(Entite &entite, Entite&)
{
    entite.setStatValue("Force", entite.getStatValue("Force") + 10);
    return entite.getNom() + " fait du sport et gagne 10 points de force";
}

#pragma endregion

#pragma region Pleurer

Pleurer::Pleurer() : Act("Pleurer", "Un petit pleurage ca fait pas de mal!", 1) {};

string Pleurer::Impact(Entite &entite, Entite&)
{
    entite.setStatValue("Vulnerabilite", entite.getStatValue("Vulnerabilite") + 10);
    return entite.getNom() + " pleure et gagne 10 points de vulnerabilité";
}