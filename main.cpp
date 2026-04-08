#include <iostream>
#include "affichage.h"
#include "monstre.h"
#include "csv.h"
#include <string>
#include <map>
#include <vector>
#include <utility>

using namespace std;

string Menu(
    GameWindow& gw,
    const map<int, string>& keymap,
    map<string, string>& infos,
    const vector<string>& options = {"Figth", "Bestiaire", "Quit"}
) {
    bool choisi = false;
    int choix = 0;

    while (!choisi) {
        vector<string> display;

        for (int i = 0; i < static_cast<int>(options.size()); i++) {
            if (i == choix) {
                display.push_back("> " + options[i]);
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

pair<Monstre**, int> initBestiaire() {
    auto monstres = readCSV("data/monstres.csv");

    int nbMonstres = static_cast<int>(monstres.size()) - 1;
    Monstre** bestiaire = new Monstre*[nbMonstres];

    for (int i = 1; i < static_cast<int>(monstres.size()); i++) {
        bestiaire[i - 1] = new Monstre(
            string(monstres[i][1]),
            stoi(monstres[i][2]),
            stoi(monstres[i][3]),
            stoi(monstres[i][4]),
            stoi(monstres[i][5])
        );
    }

    return {bestiaire, nbMonstres};
}


void game() {
    pair<Monstre**, int> result = initBestiaire();
    Monstre** bestiaire = result.first;
    int nbMonstres = result.second;

    GameWindow gw = init_ncurses();

    map<int, string> keymap = {
        {KEY_UP, "up"},
        {KEY_DOWN, "down"},
        {KEY_LEFT, "left"},
        {KEY_RIGHT, "right"},
        {'q', "quit"},
        {10, "enter"},
        {KEY_ENTER, "enter"}
    };

    map<string, string> infos = {
        {"Titre", "Into the RAM"},
        {"Score", "0"},
        {"Vie", "3"},
        {"Niveau", "1"},
        {"last_touche", ""}
    };

    string state = "menu";

    gw.jeu = displayState(gw.jeu, gw.hauteur, gw.largeur, {"menu"}, infos);

    bool running = true;

    while (running) {
        string choix = Menu(gw, keymap, infos, {"Fight", "Bestiaire", "Quit"});

        if (choix == "quit" || choix == "Quit") {
            running = false;
        }
        else if (choix == "Bestiaire") {
            vector<string> options;

            for (int i = 0; i < nbMonstres; i++) {
                    options.push_back(bestiaire[i]->getNom() + ":\t"+ to_string(bestiaire[i]->getAtk()) + "\t"+ to_string(bestiaire[i]->getDef()) + "\t" + to_string(bestiaire[i]->getHpMax()) + "\t" + to_string(bestiaire[i]->getMercyGoal()));                   
            }

            options.push_back("Retour");

            string choix_bestiaire = Menu(gw, keymap, infos, options);

            if (choix_bestiaire == "quit" || choix_bestiaire == "Quit") {
                running = false;
            }
        }
        else if (choix == "Fight") {
            state = "menu";
        }
    }

    end_ncurses(gw.jeu);
}

int main() {
    //test();

    game();
    // auto data = readCSV("data/monstres.csv");
    
    // for (const auto& row : data) {
    //     for (const auto& cell : row) {
    //         std::cout << cell << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // return 0;
}