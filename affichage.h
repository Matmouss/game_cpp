#include <string>
#include <map>
#include <ncurses.h>

struct GameWindow {
    WINDOW* jeu;
    int hauteur;
    int largeur;
};

WINDOW* creer_boite_jeu(int hauteur, int largeur);
void end_ncurses(WINDOW* jeu);

GameWindow init_ncurses();

void dessiner_boite_jeu(
    WINDOW* win,
    const std::string state = "",
    const std::map<std::string, std::string>& data = {}
);

WINDOW* displayState(
    WINDOW* jeu,
    int hauteur,
    int largeur,
    const std::string& state,
    const std::map<std::string, std::string>& infos = {
        {"Titre", "Into the RAM"},
        {"Score", "150"},
        {"Vie", "3"},
        {"Niveau", "1"},
        {"last_touche", ""}
    }
);

GameWindow resize_window(WINDOW* jeu);

std::string getInput(const std::map<int, std::string>& keymap);
