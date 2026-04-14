#include <string>
#include <map>
#include <vector>
#include <utility>
#include <ncurses.h>
#include "affichage.h"
#include "monstre.h"
#include "partie.h"
#include "personnage.h"
#include "csv.h"
#include "act.h"
#include "entite.h"
#include "item.h"

using std::map;
using std::string;
using std::to_string;
using std::vector;

map<int, string> keymap;
map<string, string> infos;

void updateInfos(Personnage &personnage, map<string, string> &infos) {
    infos["Nom"] = personnage.getNom();
    infos["Hp"] = to_string(personnage.getHp());
    infos["Atk"] = to_string(personnage.getAtk());
    infos["Def"] = to_string(personnage.getDef());
    infos["Mercy"] = to_string(personnage.getMercy());
    infos["Stats"] = "pas configuré";
}

string Menu(GameWindow &gw, map<int, string> &keymap, map<string, string> &infos, vector<string> &options, string &title)
{
    bool choisi = false;
    int choix = 0;

    while (!choisi) {
        vector<string> display;
        display.push_back(title);
        display.push_back("- - -");
        display.push_back("");

        for (int i = 0; i < static_cast<int>(options.size()); i++) {
            if (i == choix) {
                display.push_back("> " + options[i] + "<");
            } else {
                display.push_back(options[i]);
            }
        }

        gw.jeu = displayState(gw.jeu, gw.hauteur, gw.largeur, display, infos);

        string input = getInput(keymap);

        if (input == "quit") {
            return "quit";
        }
        else if (input == "resize") {
            gw = resize_window(gw.jeu, display, infos);
        }
        else if (input == "up") {
            choix = (choix - 1 + static_cast<int>(options.size())) % static_cast<int>(options.size());
        }
        else if (input == "down") {
            choix = (choix + 1) % static_cast<int>(options.size());
        }
        else if (input == "enter") {
            choisi = true;
        }
    }

    return options[choix];
}

bool FightJoueur(Monstre &monstre, Personnage &personnage,GameWindow &gw, map<int, string> &keymap, map<string, string> &infos) {
    bool pass = false;
    bool bypass = false;
    vector<string> display;

    int menuSize = 4;
    string* menu = new string[menuSize]{"Attaquer", "Act", "Item", "Pass"};

    display = { monstre.getNom()+ "\tHP: " + to_string(monstre.getHp()) + "\t" + to_string(monstre.getMercy()) + "% de merci"};
    string choix = "";
    int index = 0;

    while (choix != "quit" && choix != "enter") {
        string menuAffiche = "";

        for (int i = 0; i < menuSize; i++) {
            if (i == index) {
                menuAffiche += ">" + menu[i] + "< ";
            } else {
                menuAffiche += menu[i] + "\t";
            }
        }

        vector<string> displayTemp = display;
        displayTemp.push_back(menuAffiche);

        gw.jeu = displayState(gw.jeu, gw.hauteur, gw.largeur, displayTemp, infos);
        choix = getInput(keymap);

        if (choix == "left") {
            index = (index - 1 + menuSize) % menuSize;
        } else if (choix == "right") {
            index = (index + 1) % menuSize;
        }
    }

    if (choix == "enter") {
        if (menu[index] == "Attaquer") {
            display.push_back(personnage.attaquer(monstre));

            display[0] = monstre.getNom()+ "\tHP: " + to_string(monstre.getHp()) + "\t" + to_string(monstre.getMercy()) + "% de merci";
            display.push_back("Appuyer sur enter pour continuer");

        } else if (menu[index] == "Act"){
            vector<string> options;
            for (int i = 0; i < personnage.getNbActions(); i++){
                if (personnage.getActions(i) != nullptr)
                {
                    options.push_back(personnage.getActions(i)->identifiant + " : " + personnage.getActions(i)->texte);
                }
                else{
                    options.push_back("nullAction");
                }
            }
            options.push_back("Retour");

            choix = Menu(gw, keymap, infos, options, menu[index]);
            if (choix != "quit" && choix != "Retour") {

                for (int i = 0; i < personnage.getNbActions(); i++)
                {
                    if (options[i] == choix && choix != "")
                    {
                        display.push_back(personnage.utiliserAct(i, monstre));

                        display[0] = monstre.getNom() + "\tHP: " + to_string(monstre.getHp()) + "\t" + to_string(monstre.getMercy()) + "% de merci";
                        display.push_back("Appuyer sur enter pour continuer");

                        break;
                    }
                }
            } else {
                bypass = true;
            }
            

        } else if (menu[index] == "Item") {
            display.push_back("Vous utilisez un item");
            display.push_back("Appuyer sur enter pour continuer");
        }
        else if (menu[index] == "Pass") {
            display.push_back("Vous passez votre tour");
            display.push_back("Appuyer sur enter pour continuer");
            pass = true;
        }

        updateInfos(personnage, infos);
         gw.jeu = displayState(gw.jeu, gw.hauteur, gw.largeur, display, infos);

        if (!bypass){
            string input = getInput(keymap);
            while (input != "enter" and input != "quit") {
                input = getInput(keymap);
            }
        }
    }

    delete[] menu;
    return pass;
}

void FightMonstre(Monstre &monstre,Personnage &personnage,GameWindow &gw, map<int, string> &keymap, map<string, string> &infos) {
    vector<string> display = {""};

    display.push_back(monstre.attaquer(personnage));
    display[0] = monstre.getNom()+ "\tHP: " + to_string(monstre.getHp()) + "\t" + to_string(monstre.getMercy()) + "% de merci";
    display.push_back("Appuyer sur enter pour continuer");

    updateInfos(personnage, infos);
    gw.jeu = displayState(gw.jeu, gw.hauteur, gw.largeur, display, infos);

    string input = getInput(keymap);
    while (input != "enter" and input != "quit") {
        input = getInput(keymap);
    }
}

bool VictoireCondition(Personnage &personnage){
    if (personnage.getHp() <= 0){
        return false;
    }
    return true; 
       
}

bool combatEnCours(Monstre &monstre, Personnage &personnage) {
    if (monstre.getHp() <= 0 ||  monstre.getMercy() >= monstre.getMercyGoal() || personnage.getHp() <= 0) {
        return false;
    }
    return true;
}

bool Fight(Monstre monstre, Personnage &personnage, GameWindow &gw, map<int, string> &keymap, map<string, string> &infos) {
    bool combatEnCours_b = true;
    bool victoire = false;
    
    while (combatEnCours_b) {
        //pour le moment le seul moyen de terminer le tour est de passer
        while (!FightJoueur(monstre, personnage, gw, keymap, infos) && combatEnCours(monstre, personnage)) {} 
        combatEnCours_b = combatEnCours(monstre, personnage);
        
        if (combatEnCours_b){FightMonstre(monstre, personnage, gw, keymap, infos);} 
        combatEnCours_b = combatEnCours(monstre, personnage);
    }

    victoire = VictoireCondition(personnage);
    
    vector<string> display = {"Vous avez battu le monstre:",monstre.getNom() + "\t hp:" + to_string(monstre.getHp()) + "\t Mercy:" + to_string(monstre.getMercy()), "Appuyer sur enter pour continuer"};
    updateInfos(personnage, infos);
    gw.jeu = displayState(gw.jeu, gw.hauteur, gw.largeur, display, infos);

    string input = getInput(keymap);
    while (input != "enter" and input != "quit") {
        input = getInput(keymap);
    }

    return victoire;
}

void initBinds(){
       keymap = {
        {KEY_UP, "up"},
        {KEY_DOWN, "down"},
        {KEY_LEFT, "left"},
        {KEY_RIGHT, "right"},
        {'q', "quit"},
        {10, "enter"},
        {KEY_ENTER, "enter"}
    };

        infos = {
        {"Nom", "Personnage"},
        {"Hp", "0"},
        {"Atk", "0"},
        {"Def", "0"},
        {"Mercy", "0"},
        {"Stats", "0"}
    };
}

void game() {

    string state = "menu";

    GameWindow gw = init_ncurses();

    initBinds();

    Partie partie_en_cours = Partie();

    updateInfos((*partie_en_cours.personnage), infos);

    bool running = true;

    vector<string> options;
    while (running) {
        state = "menu";
        options = {"Fight", "Bestiaire", "Inventaire","Quit"};
        string choix = Menu(gw, keymap, infos, options,state);

        if (choix == "quit" || choix == "Quit") {
            running = false;
        }
        else if (choix == "Bestiaire") {
            state = "bestiaire";
            options = {};

            if (partie_en_cours.tailleBestiaire == 0)
            {
                options.push_back("Tu n'a rien Tué?");
            }
            else
            {
                options.push_back("Nom\tAtk\tDef\tHp\tMercy Goal\tDescription");
                for (int i = 0; i < partie_en_cours.tailleBestiaire; i++)
                {
                    options.push_back(partie_en_cours.bestiaire[i]->getNom() + "\t" + to_string(partie_en_cours.bestiaire[i]->getAtk()) + "\t" + to_string(partie_en_cours.bestiaire[i]->getDef()) + "\t" + to_string(partie_en_cours.bestiaire[i]->getHpMax()) + "\t" + to_string(partie_en_cours.bestiaire[i]->getMercyGoal()) + "\t\t" + partie_en_cours.bestiaire[i]->getDescription());
                }
            }

            options.push_back("Retour");
            choix = Menu(gw, keymap, infos, options, state);

            if (choix == "quit" || choix == "Quit") {
                running = false;
            }
        }
        else if (choix == "Fight") {
            state = "Fight";

            Monstre* monstre = partie_en_cours.monstresPossibles[1];

            if (Fight( *monstre, *partie_en_cours.personnage, gw, keymap, infos)){
                partie_en_cours.ajouterBestiaire(monstre);
            } else {
                //logique de gameover
            }
        }
        else if (choix == "Inventaire")
        {
            state = "Inventaire";

            options = {};

            if (partie_en_cours.personnage->getTailleInventaire() == 0)
            {
                options.push_back("Tu n'a rien dans tes poches sale étudiant!");
            }
            else{
                options.push_back("Nom\t\tType\tValeur");
                for (int i = 0; i < partie_en_cours.personnage->getTailleInventaire(); i++)
                {
                    Item* item = partie_en_cours.personnage->getInventaireItems(i);
                    options.push_back(item->getNom() + "\t" + item->getType() + "\t" + to_string(item->getValeur()));
                }
            }

            options.push_back("Retour");
            choix = Menu(gw, keymap, infos, options, state);
        }
    }

    end_ncurses(gw.jeu);
}

int main() {
    game();
}