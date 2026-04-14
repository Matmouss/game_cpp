#include <string>
#include <map>
#include <vector>
#include <ncurses.h>
#include "affichage.h"

using std::map;
using std::string;
using std::vector;

WINDOW* creer_boite_jeu(int hauteur, int largeur) {
    int starty = (LINES - hauteur) / 2;
    int startx = (COLS - largeur) / 2;

    WINDOW* win = newwin(hauteur, largeur, starty, startx);
    box(win, 0, 0);
    return win;
}

void dessiner_boite_jeu(
    WINDOW* win,
    const vector<string>& state,
    const map<string, string>& data
) {
    werase(win);
    box(win, 0, 0);

    int ligne = 1;
    const string champs[6] = {"Nom", "Hp", "Atk", "Def", "Mercy", "Stats"};

    for (int i = 0; i < 6; ++i) {
        auto it = data.find(champs[i]);
        string valeur = (it != data.end()) ? it->second : "";
        string texte = champs[i] + " : " + valeur;
        mvwprintw(win, ligne, 2, "%s", texte.c_str());
        ligne++;
    }

    if (!state.empty()) {
        int max_y, max_x;
        getmaxyx(win, max_y, max_x);

        int nb_lignes = static_cast<int>(state.size());
        int y_depart = (max_y - nb_lignes) / 2;

        if (y_depart < ligne + 1) {
            y_depart = ligne + 1;
        }

        int largeur_bloc = 0;
        for (const auto& texte : state) {
            int longueur = static_cast<int>(texte.size());
            if (longueur > largeur_bloc) {
                largeur_bloc = longueur;
            }
        }

        int x_depart = (max_x - largeur_bloc) / 2;
        if (x_depart < 1) {
            x_depart = 1;
        }

        for (int i = 0; i < nb_lignes; ++i) {
            int y = y_depart + i;

            if (y < max_y - 1) {
                mvwprintw(win, y, x_depart, "%s", state[i].c_str());
            }
        }
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

    vector<string> state_vide;
    map<string, string> infos_vides;
    dessiner_boite_jeu(jeu, state_vide, infos_vides);

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
    const vector<string>& state,
    const map<string, string>& infos
) {
    if (jeu != nullptr) {
        delwin(jeu);
    }

    jeu = creer_boite_jeu(hauteur, largeur);
    dessiner_boite_jeu(jeu, state, infos);

    return jeu;
}

GameWindow resize_window(
    WINDOW* jeu,
    const vector<string>& state,
    const map<string, string>& infos
) {
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
    dessiner_boite_jeu(jeu, state, infos);

    return {jeu, hauteur, largeur};
}

string getInput(const map<int, string>& keymap) {
    int ch = getch();

    if (ch == KEY_RESIZE) {
        return "resize";
    }

    auto it = keymap.find(ch);
    if (it != keymap.end()) {
        return it->second;
    }

    return std::to_string(ch);
}