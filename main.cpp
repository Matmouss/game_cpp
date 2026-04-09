#include <iostream>
#include "affichage.h"
#include "monstre.h"
#include "partie.h"
#include "csv.h"
#include <string>
#include <map>
#include <vector>
#include <utility>

using namespace std;

map<int, string> keymap;
map<string, string> infos;

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



bool Fight(GameWindow &gw, map<int, string> &keymap, map<string, string> &infos, Monstre &monstre, Personnage &personnage) {
    bool combat = true;
    bool victoire = false;

    vector<string> display = {monstre.getNom(), "\tHP: " + to_string(monstre.getHp())};
    vector<string> menu = {"Attaquer", "Act", "Item", "Mercy"};

    gw.jeu = displayState(gw.jeu, gw.hauteur, gw.largeur, display, infos);

    while (combat) {
        display = {monstre.getNom(), "\tHP: " + to_string(monstre.getHp())};
        string choix = "";
        int index = 0;

        while (choix != "quit" && choix != "enter") {
            string menuAffiche = "";

            for (int i = 0; i < static_cast<int>(menu.size()); i++) {
                if (i == index) {
                    menuAffiche += ">" + menu[i] + "< ";
                } else {
                    menuAffiche += menu[i] + " ";
                }
            }

            vector<string> displayTemp = display;
            displayTemp.push_back(menuAffiche);

            gw.jeu = displayState(gw.jeu, gw.hauteur, gw.largeur, displayTemp, infos);
            choix = getInput(keymap);

            if (choix == "left") {
                index = (index - 1 + static_cast<int>(menu.size())) % static_cast<int>(menu.size());
            } else if (choix == "right") {
                index = (index + 1) % static_cast<int>(menu.size());
            }
        }

        if (choix == "quit") {
            combat = false;
        } else if (choix == "enter") {
            if (menu[index] == "Attaquer") {
                personnage.attaquer(monstre);
            }
        }

        if (monstre.getHp() <= 0) {
            combat = false;
            victoire = true;
        }

        gw.jeu = displayState(gw.jeu, gw.hauteur, gw.largeur, display, infos);
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
        {"Titre", "Into the RAM"},
        {"Score", "0"},
        {"Vie", "3"},
        {"Niveau", "1"}
    };
}

void game() {

    string state = "menu";

    GameWindow gw = init_ncurses();

    initBinds();

    Partie partie_en_cours = Partie();

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

            Fight(gw, keymap, infos, *partie_en_cours.monstresPossibles[1], partie_en_cours.personnage);
        }
        else if (choix == "Inventaire")
        {
            state = "Inventaire";

            options = {};

            if (partie_en_cours.personnage.TailleInventaire == 0)
            {
                options.push_back("Tu n'a rien dans tes poches sale étudiant!");
            }
            else{
                options.push_back("Nom\t\tType\tValeur");
                for (int i = 0; i < partie_en_cours.personnage.TailleInventaire; i++)
                {
                    options.push_back(partie_en_cours.personnage.InventaireItems[i]->getNom() + "\t" + partie_en_cours.personnage.InventaireItems[i]->getType() + "\t" + to_string(partie_en_cours.personnage.InventaireItems[i]->getValeur()));
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