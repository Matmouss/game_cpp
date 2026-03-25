#include <iostream>
#include <string>
#include <ncurses.h>
#include <map>

using namespace std;



WINDOW* creer_boite_jeu(int hauteur, int largeur) {
    int starty = (LINES - hauteur) / 2;
    int startx = (COLS - largeur) / 2;

    WINDOW* win = newwin(hauteur, largeur, starty, startx);
    box(win, 0, 0);
    return win;
}

void dessiner_boite_jeu(WINDOW* win, const std::map<std::string, std::string>& data) {
    werase(win);
    box(win, 0, 0);

    int ligne = 1;

    for (const auto& [cle, valeur] : data) {
        std::string texte = cle + " : " + valeur;
        mvwprintw(win, ligne, 2, "%s", texte.c_str());
        ligne++;
    }

    wrefresh(win);
}

int jeu_test() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    int hauteur = LINES - 4;
    int largeur = COLS - 8;

    if (hauteur < 10) hauteur = 10;
    if (largeur < 20) largeur = 20;

    map<string, string> infos = {
    {"Titre", "Into the RAM"},
    {"Score", "150"},
    {"Vie", "3"},
    {"Niveau", "2"},
    {"last_touche", ""}
    };

    WINDOW* jeu = creer_boite_jeu(hauteur, largeur);
    dessiner_boite_jeu(jeu, infos);

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

        dessiner_boite_jeu(jeu, infos);
    }

    delwin(jeu);
    endwin();
    return 0;
}

int test(){

    jeu_test();
    return 0;
}