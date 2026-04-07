#include <iostream>
#include "affichage.h"
#include "csv.h"

using namespace std;
void game() {
    GameWindow gw = init_ncurses();

    std::map<int, std::string> keymap = {
        {KEY_UP, "up"},
        {KEY_DOWN, "down"},
        {KEY_LEFT, "left"},
        {KEY_RIGHT, "right"},
        {'q', "quit"}
    };

    std::map<std::string, std::string> infos = {
        {"Titre", "Into the RAM"},
        {"Score", "0"},
        {"Vie", "3"},
        {"Niveau", "1"},
        {"last_touche", ""}
    };

    std::string state = "menu";
    bool running = true;

    while (running) {
        gw.jeu = displayState(gw.jeu, gw.hauteur, gw.largeur, state, infos);

        std::string input = getInput(keymap);

        if (input == "quit") {
            running = false;
        } 
        else if (input == "resize") {
            gw = resize_window(gw.jeu);
        } 
        else if (!input.empty()) {
            infos["last_touche"] = input;
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
