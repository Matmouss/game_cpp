#include <iostream>
#include <string>
#include <map>
#include <ncurses.h>
#include "affichage.h"

using namespace std;

WINDOW* creer_boite_jeu(int hauteur, int largeur) {
    int starty = (LINES - hauteur) / 2;
    int startx = (COLS - largeur) / 2;

    WINDOW* win = newwin(hauteur, largeur, starty, startx);
    box(win, 0, 0);
    return win;
}

void dessiner_boite_jeu(
    WINDOW* win,
    const std::string state,
    const std::map<std::string, std::string>& data
) {
    werase(win);
    box(win, 0, 0);

    int ligne = 1;
    const std::string champs[5] = {"Titre", "Score", "Vie", "Niveau", "last_touche"};

    for (int i = 0; i < 5; ++i) {
        auto it = data.find(champs[i]);
        std::string valeur = (it != data.end()) ? it->second : "";
        std::string texte = champs[i] + " : " + valeur;
        mvwprintw(win, ligne, 2, "%s", texte.c_str());
        ligne++;
    }

    if (!state.empty()) {
        int max_y, max_x;
        getmaxyx(win, max_y, max_x);

        int y = max_y / 2;
        int x = (max_x - state.size()) / 2;

        if (x < 1) x = 1;

        mvwprintw(win, y, x, "%s", state.c_str());
    }

    wrefresh(win);
}

GameWindow init_ncurses() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    int hauteur = LINES - 4;
    int largeur = COLS - 8;

    if (hauteur < 10) hauteur = 10;
    if (largeur < 20) largeur = 20;

    WINDOW* jeu = creer_boite_jeu(hauteur, largeur);
    dessiner_boite_jeu(jeu);

    return {jeu, hauteur, largeur};
}

void end_ncurses(WINDOW* jeu) {
    if (jeu != nullptr) {
        delwin(jeu);
    }
    endwin();
}

WINDOW* displayState(
    WINDOW* jeu,
    int hauteur,
    int largeur,
    const std::string& state,
    const std::map<std::string, std::string>& infos) {

    if (jeu != nullptr) {
        delwin(jeu);
    }

    jeu = creer_boite_jeu(hauteur, largeur);
    dessiner_boite_jeu(jeu, state, infos);

    return jeu;
}

GameWindow resize_window(WINDOW* jeu) {
    if (jeu != nullptr) {
        delwin(jeu);
    }

    clear();
    refresh();

    int hauteur = LINES - 4;
    int largeur = COLS - 8;

    if (hauteur < 10) hauteur = 10;
    if (largeur < 20) largeur = 20;

    jeu = creer_boite_jeu(hauteur, largeur);
    dessiner_boite_jeu(jeu);

    return {jeu, hauteur, largeur};
}

string getInput(const std::map<int, std::string>& keymap) {
    int ch = getch();

    if (ch == KEY_RESIZE) {
        return "resize";
    }

    auto it = keymap.find(ch);
    if (it != keymap.end()) {
        return it->second;
    }

    return to_string(ch);
}

int jeu_test() {
    GameWindow gw = init_ncurses();

    int hauteur = gw.hauteur;
    int largeur = gw.largeur;

    map<string, string> infos = {
    {"Titre", "Into the RAM"},
    {"Score", "150"},
    {"Vie", "3"},
    {"Niveau", "1"},
    {"last_touche", ""}
    };

    WINDOW* jeu = creer_boite_jeu(hauteur, largeur);
    dessiner_boite_jeu(jeu, "", infos);

    int ch;
    while ((ch = getch()) != 'q') {
        if (ch == KEY_RESIZE) {
            delwin(jeu);
            clear();
            refresh();

            hauteur = LINES - 4;
            largeur = COLS - 8;

            if (hauteur < 10) hauteur = 10;
            if (largeur < 20) largeur = 20;

            jeu = creer_boite_jeu(hauteur, largeur);
        } else {
            infos["last_touche"] = to_string(ch);
        }

        dessiner_boite_jeu(jeu, "",infos);
    }

    delwin(jeu);
    endwin();
    return 0;
}
