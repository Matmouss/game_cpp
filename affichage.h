#include <string>
#include <map>
#include <vector>
#include <ncurses.h>

struct GameWindow {
    WINDOW* jeu;
    int hauteur;
    int largeur;
};

WINDOW* creer_boite_jeu(int hauteur, int largeur);

void dessiner_boite_jeu(
    WINDOW* win,
    const std::vector<std::string>& state,
    const std::map<std::string, std::string>& data
);

GameWindow init_ncurses();

void end_ncurses(WINDOW* jeu);

WINDOW* displayState(
    WINDOW* jeu,
    int hauteur,
    int largeur,
    const std::vector<std::string>& state,
    const std::map<std::string, std::string>& infos
);

GameWindow resize_window(
    WINDOW* jeu,
    const std::vector<std::string>& state,
    const std::map<std::string, std::string>& infos
);

std::string getInput(const std::map<int, std::string>& keymap);
